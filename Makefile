all: base_sqlite.o main.o ProcessKey.o SuperClass.o sqlite3.o arraywork.o sorts.o linklist.o
	g++ -g base_sqlite.o main.o ProcessKey.o SuperClass.o sqlite3.o  arraywork.o sorts.o linklist.o -ldl -lpthread

ProcessKey.o : ProcessKey.cpp
	g++ -g -c ProcessKey.cpp

SuperClass.o : SuperClass.cpp
	g++ -g -c SuperClass.cpp

linklist.o: linklist.c
	g++ -g -c linklist.c

base_sqlite.o : base_sqlite.cpp
	g++ -g -c base_sqlite.cpp 

arraywork.o : arraywork.c
	g++ -g -c arraywork.c

sorts.o : sorts.c
	g++ -g -c sorts.c

main.o : main.cpp
	g++ -g -c main.cpp

sqlite3.o : sqlite3.c
	gcc -c sqlite3.c -lpthread -ldl

clean:
	rm -rf *.o *~

