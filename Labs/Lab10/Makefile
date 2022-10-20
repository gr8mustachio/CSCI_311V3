run: main.o  priorityqueue.o 
	g++ -o run main.o  priorityqueue.o 
priorityqueue.o: priorityqueue.cpp priorityqueue.h  item.h
	g++ -c -Wall -pedantic -g -std=c++11 priorityqueue.cpp
main.o: main.cpp  priorityqueue.h 
	g++ -c -Wall -pedantic -g -std=c++11 main.cpp
clean: 
	rm main.o priorityqueue.o run
