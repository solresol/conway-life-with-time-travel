.DUMMY: all

CFLAGS=-O2 -Wall

all: tlife-checker tlife-continue tlife-oscillator tlife-find-oscillator montecarlo tlife-between tlife-terminals tlife3-brute 3x3-viable.png tlife-transform
	echo All built

3x3-cluster.txt: 3x3-simpler.txt cluster.sh
	cut -f1 -d, 3x3-simpler.txt  | sort | uniq | ./cluster.sh > 3x3-cluster.txt

3x3-viable.alpha: 3x3-viable.txt alpha3x3.py
	python alpha3x3.py > 3x3-viable.alpha

3x3-viable.png: 3x3-viable.dot
	dot -Tpng 3x3-viable.dot > 3x3-viable.png

3x3-viable.dot: 3x3-simpler.txt graph3x3.py
	python graph3x3.py > 3x3-viable.dot

3x3-simpler.txt: 3x3-viable.txt tlife3-simplify.py
	python tlife3-simplify.py > 3x3-simpler.txt

3x3-viable.txt: 3x3-all.txt tlife3-extend.py
	python tlife3-extend.py > 3x3-viable.txt

3x3-all.txt: tlife3-brute
	./tlife3-brute > 3x3-all.txt

tlife3-brute: tlife3-brute.o tlife3-engine.o
	cc tlife3-brute.o tlife3-engine.o -o tlife3-brute

tlife-checker: tlife-checker.o tlife-engine.o
	cc tlife-checker.o tlife-engine.o -o tlife-checker

tlife-continue: tlife-continue.o tlife-engine.o
	cc tlife-continue.o tlife-engine.o -o tlife-continue

tlife-oscillator: tlife-oscillator.o tlife-engine.o
	cc tlife-oscillator.o tlife-engine.o -o tlife-oscillator

tlife-find-oscillator: tlife-find-oscillator.o tlife-engine.o
	cc tlife-find-oscillator.o tlife-engine.o -o tlife-find-oscillator

montecarlo: montecarlo.o tlife-engine.o
	cc montecarlo.o tlife-engine.o -o montecarlo

tlife-between: tlife-between.o tlife-engine.o
	cc tlife-between.o tlife-engine.o -o tlife-between

tlife-terminals: tlife-terminals.o tlife-engine.o
	cc tlife-terminals.o tlife-engine.o -o tlife-terminals

tlife-transform: tlife-transform.o tlife3-engine.o
	cc tlife-transform.o tlife3-engine.o -o tlife-transform

tlife-checker.o: tlife-checker.c
	cc -c -O2 tlife-checker.c

tlife-engine.o: tlife-engine.c
	cc -c -O2 tlife-engine.c

tlife-continue.o: tlife-continue.c
	cc -c -O2 tlife-continue.c

tlife-oscillator.o: tlife-oscillator.c
	cc -c -O2 tlife-oscillator.c

tlife-find-oscillator.o: tlife-find-oscillator.c
	cc -c -O2 tlife-find-oscillator.c

montecarlo.o: montecarlo.c
	cc -c -O2 montecarlo.c

tlife-between.o: tlife-between.c
	cc -c -O2 tlife-between.c

tlife-terminals.o: tlife-terminals.c
	cc -c -O2 tlife-terminals.c

tlife-transform.o: tlife-transform.c
	cc -c -O2 tlife-transform.c

