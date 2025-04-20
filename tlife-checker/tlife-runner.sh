#!/bin/bash

let good=0
let bad=0
let total=0

while true
do
    let total=total+1
    OUTPUT=found-grids/$(date +%Y%m%d%H%M%S.grid)
    ./tlife-checker > $OUTPUT
    if test -s $OUTPUT
    then
	let good=good+1
	alternatives=$(expr $(wc -l < $OUTPUT) / 7)
	echo "$alternatives alternatives"
	svn add $OUTPUT
	svn commit -m"Automatically found $good out of $total so far." $OUTPUT
    else
	let bad=bad+1
	rm $OUTPUT
	echo "Good: $good. Bad $bad. Total: $total"
    fi
done
