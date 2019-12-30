ANALYSIS = src/analysis/analyzer.o
SRC_FILE =  $(ANALYSIS) src/main.o

CC=g++ -std=c++14
CPPFLAGS=-Wall -pedantic -O3
LDFLAGS= -lm
EXEC=arraylist_analysis

all: $(EXEC)

arraylist_analysis: $(SRC_FILE)
	$(CC) -o $@ $^ $(LDFLAGS)


clean:
	rm -rf src/*.o src/analysis/*.o 
	rm -rf *~
	rm -rf arraylist_analysis


%.o: %.cpp
	$(CC) -Iinclude/ $(CPPFLAGS) -c $< $(LIB_PATH) $(LIBS) -o $@
