main: main.o transaction.o
	g++ -o main main.o transaction.o -lcrypto

main.o: main.cpp transaction.h
	g++ -c main.cpp

transaction.o: transaction.cpp transaction.h
	g++ -c transaction.cpp 

clean:
	rm -f main main.o transaction.o