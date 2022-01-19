CC = g++

EUpricing: EUpricing.o random.o;\
  $(CC) $^ -o $@

EUpricing.o: EUpricing.cpp random.h;\
  $(CC) $< -c

clean:;\
  rm *.o
