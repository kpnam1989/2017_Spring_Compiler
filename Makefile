GCC=g++
CFLAGS=-std=c++11 -g
BIN=bin/
SRC=src/
scanner:
	$(GCC) $(CFLAGS) -o $(BIN)$@  $(SRC)Scanner/Scanner.cpp

parser: 
	$(GCC) $(CFLAGS) -o $(BIN)$@ $(SRC)Parser/Parser.cpp

reader: 
	$(GCC) $(CFLAGS) -o $(BIN)$@ $(SRC)IRreader/IRreader.cpp

clean:
	rm $(BIN)parser $(BIN)scanner
