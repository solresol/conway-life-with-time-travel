#!/usr/bin/python

relative_positions = [
    (0,0),   # 1 

    (-1,0),  # 1 
    (-1,-1),(0,-1),(1,-1),  # 2,3,4 
    (1,0),(1,1),   # 5,6 
    (0,1),(-1,1),  # 7,8 
    
#    (-2,1),(-2,0),(-2,-1),(-2,-2),  # 9,10,11,12 
#    (-1,-2),(0,-2),(1,-2),(2,-2),   # 13,14,15,16 
#    (2,-1),(2,0),(2,1),(2,2),      # 17,18,19,20 
#    (1,2),(0,2),(-1,2),(-2,2)      # 21,22,23,24 
    # I do need to add a few more here.
]

import sys
import string
import math

try:
    boardnum = string.atoi(sys.argv[1])
except IndexError:
    sys.exit("Must supply a board number as an argument")
except ValueError:
    sys.exit("Board number should be an integer")


lowest_x = 0
lowest_y = 0
largest_x = 0
largest_y = 0
bit = 1
grid = {}

for i in range(len(relative_positions)):
    (x,y) = relative_positions[i]
    if (boardnum & bit) > 0:
        grid[(x,y)] = True
    else:
        grid[(x,y)] = False
    if (x < lowest_x): lowest_x = x
    if (y < lowest_y): lowest_y = y
    if (x > largest_x): largest_x = x
    if (y > largest_y): largest_y = y
    bit = bit * 2

for y in range(lowest_y,largest_y+1):
    for x in range(lowest_x,largest_x+1):
        if grid.has_key((x,y)) and grid[(x,y)]:
            print "x",
        else:
            print ".",
        if x == largest_x:
            print
        



    
