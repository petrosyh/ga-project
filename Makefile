all : 
	g++ Graph.cpp -c -O3
	g++ Gene.cpp -c -O3
	g++ Gasolver.cpp -c -O3
	g++ mcalgo.cpp -o mcut Gasolver.o Gene.o Graph.o -O3
debug : 
	g++ Graph.cpp -c -O3 -g
	g++ Gene.cpp -c -O3 -g
	g++ Gasolver.cpp -c -O3 -g
	g++ mcalgo.cpp -o mcut Gasolver.o Gene.o Graph.o -O3 -g

clean :
	rm *.o *.out mcut

run :
	./mcut maxcut.in > maxcut.out
