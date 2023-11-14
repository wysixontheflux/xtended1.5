#!/bin/bash

cc="gcc -fcommon -include inc.h -I./include"

uANY=false
uFEATUREUNSAFE=false
DEBUG=false
DEFINES=""

while getopts “du” qo
do
	case $qo in
	d)
		DEBUG=true
		;;
	u)
		uFEATUREUNSAFE=true
		uANY=true
		;;
	esac
done

echo "Call of Duty Patch 1.5"

if [ $DEBUG = true ]; then
echo "{ CODEXTENDED DEVELOPMENT BUILD }"
else
echo "{ CODEXTENDED RELEASE BUILD }"
fi

if [ $uANY = true ]; then
echo "Using: "
fi

if [ $uFEATUREUNSAFE = true ]; then
	echo -n "Unsafe features, "
fi

if [ $uANY = true ]; then
echo ""
fi

#Compiling CoDExtended

compiler="$cc -Os -O1 -O3 -s -fvisibility=hidden -w -Wl,--exclude-libs,ALL"

if [ $DEBUG = true ]; then
compiler="$cc -g -w -Wl,--exclude-libs,ALL"
fi

if [ $uFEATUREUNSAFE = true ]; then
DEFINES+="-DuFEATUREUNSAFE "
fi

DEFINES+="-DCODPATCH=5 "

params="$DEFINES -std=c99 -I. -m32 -fPIC -Wno-write-strings"

mkdir -p ../bin
mkdir -p obj

echo -e "\nCOMPILING"

echo "[ROOT]"
$compiler $params -c init.c -o obj/init.o
$compiler $params -c librarymodule.c -o obj/librarymodule.o
$compiler $params -c codextended.c -o obj/codextended.o
echo "[COMMON]"
$compiler $params -c cvar.c -o obj/cvar.o
$compiler $params -c msg.c -o obj/msg.o
echo "[GAME]"
$compiler $params -c shared.c -o obj/shared.o
echo "[SERVER]"
$compiler $params -c sv_client.c -o obj/sv_client.o
$compiler $params -c sv_init.c -o obj/sv_init.o
$compiler $params -c net_chan.c -o obj/net_chan.o
$compiler $params -c sv_main.c -o obj/sv_main.o

obj="$(ls obj/*.o)"

if [ $DEBUG = true ]; then
$compiler -m32 -shared -L/lib32 -L./lib -o ../bin/codextended.so $obj -lz -ldl -lm -Wall
else
$compiler -m32 -shared -L/lib32 -L./lib -o ../bin/codextended.so $obj -Os -s -lz -ldl -lm -Wall
fi
find ./obj -name '*.o' ! -name 'duktape.o' -delete
echo "Done."
