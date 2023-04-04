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
PROG=$(dirname $0)/xort
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

# FIXME: tester l'existence de mkfifo/timeout/sort/...?

#
# test simple
#
function small () {

    local xc

    cat > $TEMP/small.in1 <<EOF
2xxxx
6xxxx
0xxxx
8xxxx
4xxxx
EOF
    cat > $TEMP/small.in2 <<EOF
5xxxx
7xxxx
3xxxx
9xxxx
1xxxx
EOF
    cat > $TEMP/small.out.ref <<EOF
0xxxx
1xxxx
2xxxx
3xxxx
4xxxx
5xxxx
6xxxx
7xxxx
8xxxx
9xxxx
EOF

    $TIMEOUT --preserve-status 5s \
            $PROG $TEMP/small.in1 $TEMP/small.in2 $TEMP/small.out \
            > $STDOUT 2> $STDERR
    xc=$?

    if test $xc -eq 143; then
        message 1 "small: le programme met trop de temps (sûrement bloqué)"
        return 1
    elif test $xc -ge 128; then
        message 1 "small: programme interrompu par un signal (sûrement crash)"
        return 1
    elif test $xc -ne 0; then
        message 1 "small: le programme devrait retourner 0 (et pas $xc)"
        return 1
    elif ! cmp -s $TEMP/small.out $TEMP/small.out.ref; then
        message 1 "small: le fichier sortie n'est pas correct"
        if test $VERB -eq 0; then
            echo "==== votre fichier est :"
            cat $TEMP/small.out
            echo "==== il devrait être :"
            cat $TEMP/small.out.ref
            echo "==== différence :"
            diff $TEMP/small.out $TEMP/small.out.ref
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

    local N i
    local pin1 pin2 pout ptee psrt pwcl xc xsrt

    if ! mkfifo $TEMP/large.in1; then
        message 2 "large: impossible de créer un tube nommé avec mkfifo (in1)"
        return 1
    fi
    if ! mkfifo $TEMP/large.in2; then
        message 2 "large: impossible de créer un tube nommé avec mkfifo (in2)"
        return 1
    fi
    if ! mkfifo $TEMP/large.out; then
        message 2 "large: impossible de créer un tube nommé avec mkfifo (out)"
        return 1
    fi
    if ! mkfifo $TEMP/large.srt; then
        message 2 "large: impossible de créer un tube nommé avec mkfifo (srt)"
        return 1
    fi
    if ! mkfifo $TEMP/large.cnt; then
        message 2 "large: impossible de créer un tube nommé avec mkfifo (cnt)"
        return 1
    fi

    N=750000
    for (( i=0 ; i<N ; i++ )); do
        printf "%05d\n" $RANDOM
    done > $TEMP/large.in1 &
    pin1=$!
    for (( i=0 ; i<N ; i++ )); do
        printf "%05d\n" $RANDOM
    done > $TEMP/large.in2 &
    pin2=$!

    patience "large"
    $TIMEOUT --preserve-status 30s \
            $PROG $TEMP/large.in1 $TEMP/large.in2 $TEMP/large.out \
            > $STDOUT 2> $STDERR &
    pout=$!

    tee $TEMP/large.cnt < $TEMP/large.out > $TEMP/large.srt &
    ptee=$!

    sort --check=quiet < $TEMP/large.srt & # ! may exit early, breaking pipes
    psrt=$!
    wc -l < $TEMP/large.cnt > $TEMP/large.wc &
    pwcl=$!


    wait $psrt
    xsrt=$?
    wait $pwcl
    wait $ptee
    wait $pout
    xc=$?
    wait $pin1
    wait $pin2


    # must be tested in this order, for pipes may break
    if test $xsrt -ne 0; then
        message 1 "large: la sortie n'est pas correctement triée"
        return 1
    elif test $(cat $TEMP/large.wc) -ne $(( N * 2 )); then
        message 1 "large: la sortie n'est pas complète"
        return 1
    elif test $xc -ne 0; then
        message 1 "large: le programme devrait retourner 0 (et pas $xc)"
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
    local xc

    $PROG $TEMP/$n.in1 $TEMP/$n.in2 $TEMP/$n.out \
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
    printf "0xxxx\n" > $TEMP/inex.in1
    rm -f $TEMP/inex.in2
    errs1aux "entrée inexistante" 1 inex || ret=1
    # redirection sortie impossible (dir)
    printf "0xxxx\n" > $TEMP/edir.in1
    printf "1xxxx\n" > $TEMP/edir.in2
    mkdir $TEMP/edir.out
    errs1aux "sortie impossible à créer" 1 edir || ret=1
    # entrée tronquée
    printf "0xxxx\n2xx" > $TEMP/tron.in1
    printf "1xxxx\n3xxxx\n" > $TEMP/tron.in2
    errs1aux "entrée tronquée" 2 tron || ret=1 # FIXME:

    return $ret
}

CFLAGS="-Wall -Wextra -Werror"
function erss2fake () { # msg expect nom fake

    local m=$1
    local x=$2
    local n=$3
    local f=$4
    local xc

    if test $ISLINUX -eq 1; then
        message 2 "$m: ${YELLOW}ne peut fonctionner que sous Linux${NORMAL}"
        return 1
    fi

    if ! gcc $CFLAGS -shared -fPIC $TEMP/$f.c -o $TEMP/$f.so; then
        message 2 "impossible de compiler $f"
        return 1
    fi
    LD_PRELOAD=$TEMP/$f.so \
              $PROG $TEMP/$n.in1 $TEMP/$n.in2 $TEMP/$n.out \
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
              $PROG $TEMP/$n.in1 $TEMP/$n.in2 $TEMP/$n.out \
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

    cat > $TEMP/dummy.in1 <<EOF
0xxxx
EOF
    cat > $TEMP/dummy.in2 <<EOF
1xxxx
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

    # sort échoue
    cat > $TEMP/sort.c <<EOF
#include <stdlib.h>
int main () { exit (1); }
EOF
    errs2path "sort appelle exit(1)" 1 dummy sort || ret=1
    rm -f $TEMP/tr

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
