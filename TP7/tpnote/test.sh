#!/bin/bash

#
# Usage : ./test.sh [small] [large] [errs]
#

# Environnement:
# VERB=0 affichage complet (défaut)
# VERB=1 masque sortie et erreur standard
# VERB=2 affiche uniquement le code de retour
VERB=${VERB:-1}

# FIXME: see in this file

# utilitaires
test $(uname -s) = "Linux"
ISLINUX=$?
NORMAL="$(tput sgr0)"
GREEN="$(tput setaf 2)$(tput bold)"
RED="$(tput setaf 1)$(tput bold)"
YELLOW="$(tput setaf 3)$(tput bold)"
CLINE="$(tput el)"

function notimeout () {
    shift
    shift
    echo "${YELLOW}! Warning : ni timeout ni gtimeout, Control-C en cas de blocage${NORMAL}"
    "$@"
}
if command -v timeout > /dev/null 2>&1; then
    TIMEOUT=timeout
elif command -v gtimeout > /dev/null 2>&1; then
    TIMEOUT=gtimeout
else
    TIMEOUT=notimeout
fi

function patience () { # message
    local m=$1
    if test $VERB -ne 2; then
        printf "[  ] %s... (en cours d'exécution)\r" $m
    fi
}
function message () { # exitcode message
    local c=$1
    local m=$2
    if test $VERB -eq 2; then
        echo $c
    else
        if test $c -eq 0; then
            echo "${CLINE}[${GREEN}OK${NORMAL}]" "$m"
        elif test $c -eq 1; then
            echo "${CLINE}[${RED}KO${NORMAL}]" "$m"
        else
            echo "${CLINE}[${YELLOW}??${NORMAL}]" "$m"
        fi
    fi
}

# executable
PROG=$(dirname $0)/fltr
if ! test -x $PROG; then
    message 1 "impossible de trouver l'exécutable $PROG"
    exit 1
fi
# temp dir
TEMP=$(mktemp -d)
if test $? -ne 0; then
    message 1 "impossible de créer un répertoire temporaire"
    exit 1
fi
trap 'rm -rf $TEMP' EXIT
# standard channels, muted if QUIET>0
if test $VERB -gt 0; then
    STDOUT=$TEMP/stdout
    STDERR=$TEMP/stderr
else # dummy redirect
    STDOUT=/dev/stdout
    STDERR=/dev/stderr
fi
# arguments (default is: small)
if test $# -eq 0; then
    ARGS=small
else
    ARGS="$@"
fi

#
# test simple
#
function small () {

    local xc

    cat > $TEMP/small.entree <<EOF
#####.#
...####
.#..#.#
#..###.
###.###
.#.##..
.##..#.
###.###
#.#..#.
#.####.
EOF
    cat > $TEMP/small.rebut.ref <<EOF
1111101
1110111
0101100
0110010
1110111
EOF
    cat > $TEMP/small.sortie.ref <<EOF
     1	0001111
     2	0100101
     3	1001110
     4	1010010
     5	1011110
EOF

    $TIMEOUT --preserve-status 5s \
            $PROG $TEMP/small.entree $TEMP/small.rebut $TEMP/small.sortie \
            > $STDOUT 2> $STDERR
    xc=$?

    if test $xc -eq 143; then
        message 1 "le programme met trop de temps (sûrement bloqué)"
        return 1
    elif test $xc -ge 128; then
        message 1 "programme interrompu par un signal (sûrement crash)"
        return 1
    elif test $xc -ne 0; then
        message 1 "le programme devrait retourner 0 (et pas $xc)"
        return 1
    elif ! cmp -s $TEMP/small.rebut $TEMP/small.rebut.ref; then
        message 1 "le fichier rebut n'est pas correct"
        if test $VERB -eq 0; then
            echo "==== votre fichier est :"
            cat $TEMP/small.rebut
            echo "==== il devrait être :"
            cat $TEMP/small.rebut.ref
            echo "==== différence :"
            diff $TEMP/small.rebut $TEMP/small.rebut.ref
        fi
        return 1
    elif ! cmp -s $TEMP/small.sortie $TEMP/small.sortie.ref; then
        message 1 "le fichier sortie n'est pas correct"
        if test $VERB -eq 0; then
            echo "==== votre fichier est :"
            cat $TEMP/small.sortie
            echo "==== il devrait être :"
            cat $TEMP/small.sortie.ref
            echo "==== différence :"
            diff $TEMP/small.sortie $TEMP/small.sortie.ref
        fi
        return 1
    else
        message 0 "small"
        return 0
    fi
}
#
# test long
#
function large () {

    local xc junk outp

    if ! mkfifo $TEMP/large.entree; then
        message 1 "impossible de créer un tube nommé (entrée)"
        return 1
    fi
    if ! mkfifo $TEMP/large.rebut; then
        message 1 "impossible de créer un tube nommé (rebut)"
        return 1
    fi
    if ! mkfifo $TEMP/large.sortie; then
        message 1 "impossible de créer un tube nommé (sortie)"
        return 1
    fi

    N=1000000
    ( for ((i=0;i<N;i++)) do printf "#.....#\n#......\n.......\n"; done ) \
        > $TEMP/large.entree &
    wc -l < $TEMP/large.rebut > $TEMP/large.rebut.wc &
    wc -l < $TEMP/large.sortie > $TEMP/large.sortie.wc &

    patience "large"
    $TIMEOUT --preserve-status 30s \
            $PROG $TEMP/large.entree $TEMP/large.rebut $TEMP/large.sortie \
            > $STDOUT 2> $STDERR
    xc=$?
    if test $xc -ne 0; then
        message 1 "le programme devrait retourner 0 (et pas $xc)"
        return 1
    fi

    wait

    junk=$(cat $TEMP/large.rebut.wc)
    outp=$(cat $TEMP/large.sortie.wc)

    if test $junk -ne $((2*N)); then
        message 1 "le fichier rebut n'a pas la bonne taille ($junk)"
        return 1
    elif test $outp -ne $((1*N)); then
        message 1 "le fichier de sortie n'a pas la bonne taille ($outp)"
        return 1
    else
        message 0 "large"
        return 0
    fi
}
#
# cas d'erreurs
#
function errs1aux () { # msg expect nom

    local m=$1
    local x=$2
    local n=$3

    $PROG $TEMP/$n.entree $TEMP/$n.rebut $TEMP/$n.sortie \
          > $STDOUT 2> $STDERR
    xc=$?
    if test $xc -ne $x; then
        message 1 "$m: devrait retourner $x (et pas $xc)"
        return 1
    else
        message 0 "$m"
        return 0
    fi
}
function errs1 () {

    local ret=0
    # arguments ? (inutile)
    # entree inexistante
    rm -f $TEMP/inex.entree
    errs1aux "entrée inexistante" 1 inex || ret=1
    # redirection sortie impossible (dir)
    printf ".......\n" > $TEMP/edir.entree
    mkdir $TEMP/edir.sortie
    errs1aux "sortie impossible à créer" 1 edir || ret=1
    # entrée tronquée
    printf "#.....#\n#......\n...." > $TEMP/tron.entree
    errs1aux "entrée tronquée" 1 tron || ret=1

    return $ret
}

CFLAGS="-Wall -Wextra -Werror"
function erss2fake () { # msg expect nom fake

    local m=$1
    local x=$2
    local n=$3
    local f=$4

    if test $ISLINUX -eq 1; then
        message 2 "$m: ${YELLOW}ne peut fonctionner que sous Linux${NORMAL}"
        return 1
    fi

    if ! gcc $CFLAGS -shared -fPIC $TEMP/$f.c -o $TEMP/$f.so; then
        message 1 "impossible de compiler $f"
        return 1
    fi
    LD_PRELOAD=$TEMP/$f.so \
              $PROG $TEMP/$n.entree $TEMP/$n.rebut $TEMP/$n.sortie \
              > $STDOUT 2> $STDERR
    xc=$?
    if test $xc -ne $x; then
        message 1 "$m: devrait retourner $x (et pas $xc)"
        return 1
    else
        message 0 "$m"
        return 0
    fi
}
function errs2path () { # msg expect nom fake

    local m=$1
    local x=$2
    local n=$3
    local f=$4

    if ! gcc $CFLAGS $TEMP/$f.c -o $TEMP/$f; then
        message 1 "impossible de compiler $f"
        return 1
    fi
    PATH=$TEMP:$PATH \
              $PROG $TEMP/$n.entree $TEMP/$n.rebut $TEMP/$n.sortie \
              > $STDOUT 2> $STDERR
    xc=$?
    if test $xc -ne $x; then
        message 1 "$m: devrait retourner $x (et pas $xc)"
        return 1
    else
        message 0 "$m"
        return 0
    fi
}
function errs2 () {

    cat > $TEMP/dummy.entree <<EOF
#.#.#.#
##..##.
EOF
    # erreur sur pipe
    cat > $TEMP/fakepipe.c <<EOF
#include <errno.h>
int pipe(int p[2]) { (void)p; errno = ELIBBAD; return -1; }
EOF
    erss2fake "pipe échoue" 1 dummy fakepipe || ret=1
    # erreur sur dup
    cat > $TEMP/fakedup.c <<EOF
#include <errno.h>
int dup(int o) { (void)o; errno = ELIBBAD; return -1; }
int dup2(int o, int n) { (void)o; (void)n; errno = ELIBBAD; return -1; }
EOF
    erss2fake "dup échoue" 1 dummy fakedup || ret=1
    # erreur sur fork
    cat > $TEMP/fakefork.c <<EOF
#include <sys/types.h>
#include <errno.h>
pid_t fork (void) { errno = ELIBBAD; return -1; }
EOF
    erss2fake "fork échoue" 1 dummy fakefork || ret=1
    # erreur sur exec (FIXME: execve semble impossible à intercepter)
    cat > $TEMP/fakeexec.c <<EOF
#include <errno.h>
int execl(const char *f, const char *a, ...)
{ (void)f; (void)a; errno = ELIBBAD; return -1; }
int execlp(const char *f, const char *a, ...)
{ (void)f; (void)a; errno = ELIBBAD; return -1; }
int execv(const char *f, char *const a[])
{ (void)f; (void)a; errno = ELIBBAD; return -1; }
int execvp(const char *f, char *const a[])
{ (void)f; (void)a; errno = ELIBBAD; return -1; }
int execve(const char *f, char *const a[], char *const e[])
{ (void)f; (void)a; (void)e; errno = ELIBBAD; return -1; }
EOF
    erss2fake "exec échoue" 1 dummy fakeexec || ret=1
    # fils signalé
    cat > $TEMP/fakeexec.c <<EOF
#include <errno.h>
int execl(const char *f, const char *a, ...)
{ (void)f; (void)a; int * p = 0; int x = * p; (void)x; return -1; }
int execlp(const char *f, const char *a, ...)
{ (void)f; (void)a; int * p = 0; int x = * p; (void)x; return -1; }
int execv(const char *f, char *const a[])
{ (void)f; (void)a; int * p = 0; int x = * p; (void)x; return -1; }
int execvp(const char *f, char *const a[])
{ (void)f; (void)a; int * p = 0; int x = * p; (void)x; return -1; }
int execve(const char *f, char *const a[], char *const e[])
{ (void)f; (void)a; (void)e; int * p = 0; int x = * p; (void)x; return -1; }
EOF
    erss2fake "exec provoque un signal" 2 dummy fakeexec || ret=1

    # tr échoue
    cat > $TEMP/tr.c <<EOF
#include <stdlib.h>
int main () { exit (1); }
EOF
    errs2path "tr appelle exit(1)" 1 dummy tr || ret=1
    rm -f $TEMP/tr
    # cat échoue
    cat > $TEMP/cat.c <<EOF
#include <stdlib.h>
int main () { exit (1); }
EOF
    errs2path "cat appelle exit(1)" 2 dummy cat || ret=1
    rm -f $TEMP/cat
    # tr signale
    cat > $TEMP/tr.c <<EOF
#include <stdlib.h>
int main () { abort (); }
EOF
    errs2path "tr terminé par un signal" 2 dummy tr || ret=1
    rm -f $TEMP/tr
    # cat signale
    cat > $TEMP/cat.c <<EOF
#include <stdlib.h>
int main () { abort (); }
EOF
    errs2path "cat terminé par un signal" 2 dummy cat || ret=1
    rm -f $TEMP/cat

    return $ret
}


r=0
for a in $ARGS; do
    case $a in
        small) small || r=1;;
        large) large || r=1;;
        errs) errs1 || r=1; errs2 || r=1;;
        *) message 1 "argument inconnu $a (ignoré)";;
    esac
done

exit $r
