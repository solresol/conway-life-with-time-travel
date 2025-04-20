#!/bin/bash

y1=$1
y2=$2
export TLIFE_CONTINUE_PROGRESS="Year 3 calc: "
YEAR3=$($(dirname $0)/tlife-continue $y1 $y2)
for y3 in $YEAR3
do
    export TLIFE_CONTINUE_PROGRESS="Trying $y3:             "
    YEAR4=$($(dirname $0)/tlife-continue $y2 $y3)
    for y4 in $YEAR4
    do
	export TLIFE_CONTINUE_PROGRESS="Find year5... $y1 $y2 $y3 $y4: "
	ANSWER=$($(dirname $0)/tlife-continue $y3 $y4)
	if [ "$ANSWER" != "" ]
	then
	    echo 
	    for answer in $ANSWER
	    do
		echo "$y1 $y2 $y3 $y4 $answer"
	    done
	    exit 0
	fi
    done
done