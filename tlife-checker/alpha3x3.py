#!/usr/bin/env python

import string
answer = []

f = open("3x3-viable.txt")
for line in f.readlines():
    (a,b,c) = line.strip().split(',')
    answer.append('{'+a+','+b+'} -> {'+b+','+c+'}')
print "directed graph " + string.join(answer,', ')
