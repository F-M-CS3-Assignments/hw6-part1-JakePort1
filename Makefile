comp: 
	g++ -Wall RedBlackTree.cpp RedBlackTreeTests.cpp -o tests

run: 
	./tests

testFirstSteps: 
	g++ -Wall RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp -o r
	./r

all: comp run