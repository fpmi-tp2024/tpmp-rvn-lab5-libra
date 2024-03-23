compiler = g++
flags = 

obj/main.o: obj src/main.cpp
	$(compiler) $(flags) -c src/main.cpp -o obj/main.o

obj/park.o: obj src/park.cpp
	$(compiler) $(flags) -c src/park.cpp -o obj/park.o

bin:
	mkdir bin

obj:
	mkdir obj

build: bin obj/main.o obj/park.o
	$(compiler) $(flags) obj/main.o obj/park.o -o bin/program

run: build test
	./bin/program

test: obj/park.o
	$(compiler) $(flags) -o bin/tests tests/tests.cpp obj/park.o
	./bin/tests

clean:
	rm -rf obj/*.o bin/*