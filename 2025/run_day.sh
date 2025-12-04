#! /usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR="$SCRIPT_DIR/build"
RUN_DAY_USAGE="run_day.sh <day-to-run> [arguments]"

if [ "$#" -lt 1 ]; then
    echo "Error: invalid number of arguments";
    echo $RUN_DAY_USAGE
    exit 1;
fi

if [[ $1 =~ ^[0-9]+$ ]]; then
    DAY="day$1"
elif [[ ${1,,} =~ [dD]"ay"[0-9]+$ ]]; then
    DAY=${1,,}
else
    echo "Error: Invalid day argument"
    echo $RUN_DAY_USAGE
    exit 1
fi
shift;
exec $BUILD_DIR/$DAY/$DAY $@