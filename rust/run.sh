#!/bin/bash

set -eu
shopt -s nullglob

function usage {
    echo "Example: ./run.sh arc075_a"
    exit 1
}

if [ $# -ne 1 ]; then
    usage
fi

ARG=$1

if ! [[ $ARG =~ ^(arc|abc)[0-9]{3}_[abcd]$ ]]; then
    usage
fi

cargo build --bin $ARG

FAILED=0
function failed {
    FAILED=1
    echo "...Failed"
}

for file in $(find ./resource/$ARG/input/ -type f); do
    IDX=$(basename $file)
    INPUT="./resource/$ARG/input/$IDX"
    OUTPUT="./resource/$ARG/output/$IDX"
    echo " --- Case $IDX --- "
    (./target/debug/$ARG < $INPUT | diff - $OUTPUT && echo "OK") || failed
done

if [ $FAILED == 0 ]; then
    cat ./src/bin/$ARG.rs | pbcopy
    DOMAIN=$(echo $ARG | cut -d '_' -f 1).contest.atcoder.jp
    URL=http://$DOMAIN/submit
    open $URL
fi