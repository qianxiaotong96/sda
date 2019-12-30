ANALYSIS = src/analysis/analyzer.o
STRUCTURES = src/structures/tas_binaire.o
SRC_FILE =  $(STRUCTURES) $(ANALYSIS) src/main.o

CC=gcc
CFLAGS=-Wall -pedantic -O3
LDFLAGS= -lm
EXEC=tas_binaire_analysis

all: $(EXEC)

tas_binaire_analysis: $(SRC_FILE)
	$(CC) -o $@ $^ $(LDFLAGS)


clean:
	rm -rf src/*.o src/analysis/*.o src/structures/*.o
	rm -rf *~
	rm -rf tas_binaire_analysis


%.o: %.c
	$(CC) -Iinclude/ $(CFLAGS) -c $< $(LIB_PATH) $(LIBS) -o $@
