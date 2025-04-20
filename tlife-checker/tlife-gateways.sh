#!/bin/bash

terminals=$($(dirname $0)/tlife-terminals)
for terminal in $terminals
do
    echo $terminal: $($(dirname $0)/tlife-continue.sh $terminal $terminal)
done