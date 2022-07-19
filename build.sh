#!/bin/sh

set -x

DEPS="./libopen.a ./libbaba.a"
OPENSSL_DIR="/root/github/openssl-1.0.2"
BABASSL_DIR="/root/github/BabaSSL"
OPENSSL_INC="-I$OPENSSL_DIR/include"
BABASSL_INC="-I$BABASSL_DIR/include"
INCS="$OPENSSL_INC $BABASSL_INC"
DEFINE=""
for i in "$@"
do
    if [ "xdepend_babassl_first" = "x$i" ]; then
        DEPS="./libbaba.a ./libopen.a"
        INCS="$BABASSL_INC $OPENSSL_INC"
    else
        DEFINE="$DEFINE $i"
    fi
done

gcc -Wall -g -c -o ./lopen.o ./lopen.c $OPENSSL_INC -fPIC $DEFINE
ar rvs ./lopen.a ./lopen.o

gcc -Wall -g -c -o ./lbaba.o ./lbaba.c $BABASSL_INC -fPIC $DEFINE
ar rvs ./lbaba.a ./lbaba.o

ar -M <<EOM
VERBOSE
CREATE libopen.a
ADDLIB $OPENSSL_DIR/libcrypto.a
ADDLIB ./lopen.a
SAVE
END
EOM

ar -M <<EOM
CREATE libbaba.a
ADDLIB $BABASSL_DIR/libcrypto.a
ADDLIB ./lbaba.a
SAVE
END
EOM

gcc -Wall -g -o ./test ./test.c -I./ $INCS $DEPS $DEFINE -lpthread -ldl
