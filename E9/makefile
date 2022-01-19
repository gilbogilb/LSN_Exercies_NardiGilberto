all: main\

main.o: main.cpp tsp.h random.h;\
  g++ $< -c -g

main: main.o random.o;\
  g++ $^ -o $@

selectiontest: selectiontest.o random.o;\
  g++ $^ -o $@

selectiontest.o: selectiontest.cpp tsp.h random.h;\
  g++ $< -c

test: test.o random.o;\
  g++ $^ -o $@

test.o: test.cpp tsp.h random.h;\
  g++ $< -c