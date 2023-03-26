.PHONY: all debug release clean

all: debug release

debug: main_TCP-dbg

hello-dbg: main_TCP.cpp
	g++ -g -O0 main_TCP.cpp -o main_TCP-dbg -Wall

release: main_TCP

hello: main_TCP.cpp
	g++ -O2 main_TCP.cpp -o main_TCP -DNDEBUG -Wall

clean:
	rm -f main_TCP-dbg main_TCP
