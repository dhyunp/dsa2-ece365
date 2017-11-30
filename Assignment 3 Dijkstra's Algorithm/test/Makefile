minPath.out: minPath.o
	g++ -o minPath.out minPath.o graph.o heap.o hashlist.o

minPath.o: minPath.cpp graph.o
	g++ -c minPath.cpp

graph.o: graph.cpp graph.h heap.o
	g++ -c graph.cpp

heap.o: heap.cpp heap.h hashlist.o
	g++ -c heap.cpp

hashlist.o: hashlist.cpp hashlist.h
	g++ -c hashlist.cpp

test: minPath.out
	rm -f test*
	echo -e "graph.txt\nv1\ntestv1.txt" | ./minPath.out
	diff testv1.txt outv1.txt
	echo -e "graph.txt\nv5\ntestv5.txt" | ./minPath.out
	diff testv5.txt outv5.txt

bigtest: minPath.out
	rm -f big_graph
	python makegraph.py
	echo -e "big_graph\nv888\ntestbig.txt" | ./minPath.out

debug:
	g++ -g -o minPathDebug.out minPath.cpp graph.cpp heap.cpp hashlist.cpp

clean:
	rm -f *.out *.o *.stackdump *~ test*
