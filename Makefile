Hanoi: stack.o board.o hanoi.o
	g++ -c stack.cpp board.cpp hanoi.cpp
	g++ -o Hanoi stack.o board.o hanoi.o

clean:
	rm *.o Hanoi