
.PHONY: all debug release clean

all: debug release

debug: main_UDP-dbg

hello-dbg: main_UDP.cpp
	g++ -g -O0 main_UDP.cpp -o main_UDP-dbg -Wall

release: hello

hello: hello.cpp
	g++ -O2 main_UDP.cpp -o main_UDP -DNDEBUG -Wall

clean:
	rm -f main_UDP-dbg main_UDP