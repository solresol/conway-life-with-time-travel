#!/usr/bin/env python

import sys

f = open("3x3-viable.txt")

possible_boards = {}
triples = []
for line in f.readlines():
    (a_str,b_str,c_str) = line.strip().split(',')
    a = int(a_str)
    b = int(b_str)
    c = int(c_str)
    possible_boards[b] = True
    triples.append((a,b,c))

db = {}
continuers = {}
for (a,b,c) in triples:
    if a not in possible_boards: continue
    if b not in possible_boards: continue
    if c not in possible_boards: continue
    if (a,b) in db: db[(a,b)].append(c)
    else: db[(a,b)] = [c]
    continuers[(b,c)] = None

cs = continuers.keys()
sys.stderr.write("There are "+`len(cs)`+" possible continuations\n")

count_level_4 = 0
over_count = 0

for (b,c) in continuers.keys():
    if (b,c) in db:
        continuers[(b,c)] = db[(b,c)]
        count_level_4 += len(db[(b,c)])
    else:
        over_count += 1

sys.stderr.write("But "+`over_count`+" of these had no continuation\n")
sys.stderr.write("This leaves "+`count_level_4`+" 4-length sequences\n")
    
######################################################################

reduction_round = 0
while True:
    reduction_round += 1
    possible_boards = {}
    reachable_boards = {}
    for (a,b) in db.keys():
        possible_boards[b] = True
        for c in db[(a,b)]:
            reachable_boards[c] = True

    reduction_count = 0
    for (a,b) in db.keys():
        replacement_list = []
        for c in db[(a,b)]:
            if (b,c) in db and a in possible_boards and b in possible_boards and c in possible_boards and a in reachable_boards and b in reachable_boards and c in reachable_boards:
                replacement_list.append(c)
            else:
                reduction_count += 1
        db[(a,b)] = replacement_list[:]
        if len(db[(a,b)]) == 0:
            del db[(a,b)]
    if reduction_count > 0:
        sys.stderr.write("Reduction round "+`reduction_round`+" removed "+`reduction_count`+" elements leaving "+`len(db.keys())`+" elements\n")
    else:
        break

for (a,b) in db.keys():
    for c in db[(a,b)]:
        print `a`+","+`b`+","+`c`
