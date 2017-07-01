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

if ! [[ $ARG =~ ^(arc|abc)[0-9]{3}_[abcd]$ ]]; then
    usage
fi

DOMAIN=$(echo $ARG | cut -d '_' -f 1).contest.atcoder.jp
URL=http://$DOMAIN/tasks/$ARG

cp -n ./template.rs ./src/bin/$ARG.rs 
curl $URL | tr -d \\r | python3 ./scripts/parse.py ./resource/$ARG
code ./src/bin/$ARG.rs
