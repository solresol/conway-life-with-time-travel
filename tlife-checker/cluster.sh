#!/bin/bash

(while read line
 do
   $(dirname $0)/all-variants.sh $line
 done
) | sort -n | uniq