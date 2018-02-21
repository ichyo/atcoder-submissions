#!/bin/bash

set -eu

function usage {
    echo "Example: ./new.sh arc075_a"
    exit 1
}

if [ $# -ne 1 ]; then
    usage
fi

ARG=$1

CONTEST=$(echo $ARG | cut -d '_' -f 1)
URL=https://beta.atcoder.jp/contests/$CONTEST/tasks/$ARG

cp -n ./template.rs ./src/bin/$ARG.rs 
curl $URL --cookie ./cookies.txt | tr -d \\r | python3 ./scripts/parse.py ./resource/$ARG
