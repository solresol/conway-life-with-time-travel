#!/usr/bin/env python

import sys

f = open("3x3-simpler.txt")
print 'strict digraph "" {'
for line in f.readlines():
    (a,b,c) = line.strip().split(',')
    print ' "'+a+','+b+'" -> "'+b+','+c+'"'
print "}"
