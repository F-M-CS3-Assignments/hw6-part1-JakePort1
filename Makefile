comp: 
	g++ -Wall RedBlackTree.cpp RedBlackTreeTests.cpp -o tests

run: 
	./tests

testFirstSteps: 
	g++ -Wall RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp -o r
	./r

testLeaks: 
	valgrind --leak-check=full ./tests

all: comp run