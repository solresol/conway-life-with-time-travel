#!/bin/bash

export TLIFE_CONTINUE_PROGRESS="Year 3 calc: "
YEAR3=$($(dirname $0)/tlife-continue $1 $2)
for option in $YEAR3
do
    export TLIFE_CONTINUE_PROGRESS="Trying $option: "
    $(dirname $0)/tlife-continue $2 $option
done