#!/bin/bash

WHAT=$1
r1=$($(dirname $0)/tlife-transform rotate $WHAT)
r2=$($(dirname $0)/tlife-transform rotate $r1)
r3=$($(dirname $0)/tlife-transform rotate $r2)

h=$($(dirname $0)/tlife-transform horizontal-flip $WHAT)
v=$($(dirname $0)/tlife-transform vertical-flip $WHAT)

rh=$($(dirname $0)/tlife-transform rotate $h)
rv=$($(dirname $0)/tlife-transform rotate $v)


echo $( ( echo $WHAT ; echo $r1; echo $r2; echo $r3; echo $h; echo $v; echo $rh; echo $rv ) | sort -n | uniq )