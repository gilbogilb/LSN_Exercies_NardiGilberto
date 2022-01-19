CC = g++

all: main acceptancetest\

main: main.o random.o DataBlocks.o;\
	$(CC) $^ -o $@

main.o: main.cpp random.h DataBlocks.h Metropolis.h FunzioniScalari.h;\
	$(CC) $< -c

acceptancetest: acceptancetest.o random.o;\
	$(CC) $^ -o $@

acceptancetest.o: acceptancetest.cpp random.h Metropolis.h FunzioniScalari.h;\
	$(CC) $< -c

clean:;\
  rm *.o