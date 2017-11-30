.PHONY: clean debug run

dijkstra.exe: dijkstra.o graph.o heap.o hash.o
	g++ -std=c++11 -o dijkstra.exe dijkstra.o graph.o heap.o hash.o

dijkstra.o: dijkstra.cpp
	g++ -std=c++11 -c dijkstra.cpp

graph.o: graph.cpp graph.h
	g++ -std=c++11 -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -std=c++11 -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp

debug:
	g++ -std=c++11 -g -o dijkstra.exe dijkstra.cpp hash.cpp heap.cpp graph.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
