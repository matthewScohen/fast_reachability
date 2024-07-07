all:
	g++ -o main.out main.cpp Graph/Node.cpp Graph/Graph.cpp solver.cpp

clean:
	rm *.out
	make all