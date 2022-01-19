main: main.o DataBlocks.o random.o;\
  g++ $^ -o $@

main.o: main.cpp DataBlocks.h Metropolis.h random.h Funzioni.h;\
  g++ $< -c

test: test.o DataBlocks.o random.o;\
  g++ $^ -o $@

test.o: test.cpp DataBlocks.h Metropolis.h random.h Funzioni.h;\
  g++ $< -c

clean:;\
  rm *.o