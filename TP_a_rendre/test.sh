#!/bin/sh

# Ce script lance votre programme dans un certain nombre de
# situations, et vérifie son comportement et ses résultats. Il doit
# être lancé avec
#
#    ./test.sh
#
# ou via "make test". Pour chaque test, ce script affiche l'appel
# de votre programme qu'il effectue
#
# Pour tester votre programme, ce script utilise un certain nombre de
# fichiers (qu'il produit lui-même). Tous ces fichiers sont placés
# dans le répertoire
#
#    ./test.dir
#
# Si il rencontre un problème, ce script affiche un message
# d'explication, et laisse le répertoire ./test.dir en l'état. Vous
# pouvez ainsi reproduire le dernier appel qui a posé problème.
#
# Sinon, il se termine en supprimant tous les fichiers qu'il a créés,
# sauf test.log (qui peut être supprimé avec "make clean").
#
# Toutes les commandes exécutées par ce script (les appels de votre
# programme et toutes les autres commandes) sont listées dans le
# fichier
#
#    ./test.log
#
# que vous pouvez consulter pour avoir le détail des tests.


set -u # échec en cas d'accès à une variable indéfinie

PROG=${PROG:-./exdir} # exdir dans le répertoire courant
if ! test -x $PROG; then
    echo "==> exécutable $PROG introuvable"
    exit 1
fi
if ! test -r $PROG.c; then
    echo "==> source $PROG.c introuvable"
    exit 1
fi


TMP=test.dir		# chemin de base des fichiers utilisés
OUT=$TMP/stdout		# sortie du programme
ERR=$TMP/stderr		# pour les tests de msg d'erreur
DIRES="/tmp/`id -u`"    # répertoire contenant les résultats
LOG=test.log	        # log : dans le répertoire courant
rm -f $LOG

if test -d $TMP; then
    rm -rf $TMP
fi
mkdir $TMP
rm -rf $DIRES


# quelques fonctions utilitaires

NUMERO=1
annoncer () # message
{
    set +x
    printf "%2d. %s\n" $NUMERO "$1"
    NUMERO=$((NUMERO + 1))
    set -x
}

run_prog () # exit-attendu args
{
    local xcode=$1 xc
    shift
    echo "    \$ $PROG" "$@" "> $OUT 2> $ERR"
    $PROG "$@" > $OUT 2> $ERR
    xc=$?
    if test $xc -ne $xcode; then
        echo "==> Code de retour erronné ($xc au lieu de $xcode)"
        exit 1
    fi
}

test_file () # répertoire-résultat nombre-attendu
{
    local actual
    actual=$(ls -l $1 | wc -l)
    if ! test $((actual - 1)) -eq $2; then
	echo "==> Problème sur le nombre de fichiers générés"
        echo "==> $((actual - 1)) au lieu de $2"
	exit 1
    fi
}

test_stderr () # fichier-stderr
{
    if ! test $(wc -l < "$1") -gt 0; then
	echo "==> Erreur standard vide, devrait contenir un message"
	exit 1
    fi
}

creer_fichiers ()
{
    local pathname="$1" nbfichiers="$2" nbexe="$3"
    local i=0 random=`shuf -i 1-500 -n 1`

    while [ $i -lt "$nbfichiers" ]; do
	touch $pathname/$i.$random
	i=$((i+1))
    done

    i=0
    for entry in "$pathname"/*; do
	if [ $i -lt $nbexe ]; then
	    chmod +x "$entry"
	    i=$((i+1))	    
	fi
    done
}

creer_arbo ()
{
    set +x

    local pathname="$1" level="$2" nbfichiers="$3" nbexe="$4"
    local i=0 j=0

    mkdir $pathname
    creer_fichiers $pathname $nbfichiers $nbexe
    while [ $i -lt $level ]; do
	pathname=$pathname/$i.d
	mkdir $pathname
	creer_fichiers $pathname $nbfichiers $nbexe
	i=$(($i+1))
    done

    set -x
}

creer_arbo_long ()
{
    set +x

    local level="$1"
    local pathname="$TMP"/files/ i=0 j=0

    while [ $i -lt $level ]; do
	j=0
	while [ $j -lt 255 ]; do
	    pathname="$pathname"a
	    j=$(($j+1))
	done
	pathname="$pathname"/
	i=$(($i+1))
    done
    mkdir -p $pathname
    touch "$TMP"/files/toto
    chmod +x "$TMP"/files/toto
    
    set -x
}

CATEGORIES=0

# demander au shell la trace des commandes exécutées (dans $LOG)
exec 2> $LOG
set -x

###############################################################################
# 1. Tester la syntaxe : le code de retour en cas d'erreur doit être != 0
#

annoncer "Syntaxe invalide : pas d'argument"
run_prog 1
test_stderr $ERR

annoncer "Syntaxe invalide : trop d'arguments"
run_prog 1 a b c
test_stderr $ERR

annoncer "Syntaxe invalide : fichier inexistant"
run_prog 1 $TMP/nonexistant
test_stderr $ERR

annoncer "Syntaxe invalide : fichier régulier"
touch $TMP/regulier
run_prog 1 $TMP/regulier
test_stderr $ERR
rm -f $TMP/regulier

annoncer "Syntaxe invalide : répertoire non lisible"
mkdir $TMP/illisible ; chmod -r $TMP/illisible
run_prog 1 $TMP/illisible
test_stderr $ERR
rm -rf $TMP/illisible

annoncer "Syntaxe invalide : répertoire non exe"
mkdir $TMP/noxbit ; chmod -x $TMP/noxbit
run_prog 1 $TMP/noxbit
test_stderr $ERR
rm -rf $TMP/noxbit

###############################################################################
# 2. Tester le comportement basique sur un unique répertoire
#

annoncer "Un répertoire vide"
creer_arbo $TMP/files 0 0 0
run_prog 0 $TMP/files
test_file $DIRES 0
rm -rf $TMP/files $DIRES

annoncer "Un répertoire contenant un fichier non exe"
creer_arbo $TMP/files 0 1 0
run_prog 0 $TMP/files
test_file $DIRES 0
rm -rf $TMP/files $DIRES

annoncer "Un répertoire contenant un fichier exe"
creer_arbo $TMP/files 0 1 1
run_prog 0 $TMP/files
test_file $DIRES 1
rm -rf $TMP/files $DIRES

annoncer "Un répertoire contenant un lien symb"
mkdir $TMP/files ; ln -s /usr/bin/ls $TMP/files/ls
run_prog 0 $TMP/files
test_file $DIRES 0
rm -rf $TMP/files $DIRES

annoncer "Un répertoire contenant un mix"
creer_arbo $TMP/files 0 35 15
run_prog 0 $TMP/files
test_file $DIRES 15
rm -rf $TMP/files $DIRES

###############################################################################
# 3. Tester le comportement sur une arborescence de fichiers
#

annoncer "Une hiérarchie à 2 niveaux"
creer_arbo $TMP/files 1 15 7
run_prog 0 $TMP/files
test_file $DIRES 14
rm -rf $TMP/files $DIRES

annoncer "Une hiérarchie à 2 niveaux avec un répertoire non lisible"
creer_arbo $TMP/files 1 15 7 ; chmod -r $TMP/files/0.d
run_prog 0 $TMP/files
test_file $DIRES 7
chmod +r $TMP/files/0.d
rm -rf $TMP/files $DIRES

annoncer "Une hiérarchie à 2 niveaux avec un répertoire non exe"
creer_arbo $TMP/files 1 15 7 ; chmod -x $TMP/files/0.d
run_prog 0 $TMP/files
test_file $DIRES 7
chmod +x $TMP/files/0.d
rm -rf $TMP/files $DIRES

annoncer "Une hiérarchie à plusieurs niveaux"
creer_arbo $TMP/files 10 50 25
run_prog 0 $TMP/files
test_file $DIRES 275
rm -rf $TMP/files $DIRES

###############################################################################
# 4. Tester le comportement sur une arborescence de fichiers
#

annoncer "Une hiérarchie avec un nom très long"
creer_arbo_long 20
run_prog 1 $TMP/files
test_file $DIRES 1
test_stderr $ERR

annoncer "Test avec valgrind"
VALG="valgrind --leak-check=full --error-exitcode=100 $PROG $TMP/files"
echo "    \$ $VALG > $OUT 2> $ERR"
$VALG > $OUT 2> $ERR
# peu importe le code de retour de la commande, c'est le code de retour
# de valgrind qui nous intéresse
if test $? = 100; then
    echo "==> valgrind détecte des erreurs (voir fichier $ERR)"
    exit 1
fi

printf "\n=== Succès pour tous les tests\n\n"
rm -rf $TMP/files $DIRES
rm -rf $TMP

exit 0
