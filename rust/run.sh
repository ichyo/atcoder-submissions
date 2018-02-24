#!/bin/bash

set -eu
shopt -s nullglob

REMOVE_DEAD=true

function usage {
    echo "Example: ./run.sh arc075_a"
    exit 1
}

if [ $# -ne 1 ]; then
    usage
fi

ARG=$1

cargo +1.15.1 build --bin $ARG

FAILED=0
function failed {
    FAILED=1
    echo "...Failed"
}

for file in $(find ./resource/$ARG/input/ -type f | sort); do
    IDX=$(basename $file)
    INPUT="./resource/$ARG/input/$IDX"
    OUTPUT="./resource/$ARG/output/$IDX"
    echo " --- Case $IDX --- "
    (./target/debug/$ARG < $INPUT | diff - $OUTPUT && echo "OK") || failed
done

if [ $FAILED == 0 ]; then
    if [ $REMOVE_DEAD = 'true' ]; then
        cargo +1.21.0 check --bin $ARG --message-format=json | cargo script remove_dead.rs ./src/bin/$ARG.rs | rustfmt | xclip -selection clipboard
    else
        cat ./src/bin/$ARG.rs | xclip -selection clipboard
    fi

    CONTEST=$(echo $ARG | cut -d '_' -f 1)
    URL="https://beta.atcoder.jp/contests/$CONTEST/submit?taskScreenName=$ARG"
    python -m webbrowser -t "$URL"
fi
