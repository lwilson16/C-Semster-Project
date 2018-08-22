CC=g++

#compiler flags
CFLAGS= -Wall -I . -c -g


PA9: main.o Reader.o PunctAndCap.o WordStem.o ReadingLevel.o TFIDF.o
	$(CC) -g -o PA9 main.o Reader.o PunctAndCap.o ReadingLevel.o TFIDF.o WordStem.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Reader.o: Reader.cpp Reader.h
	$(CC) $(CFLAGS) Reader.cpp

PunctAndCap.o: PunctAndCap.cpp PunctAndCap.h
	$(CC) $(CFLAGS) PunctAndCap.cpp

WordStem.o: WordStem.cpp WordStem.h
	$(CC) $(CFLAGS) WordStem.cpp

ReadingLevel.o: ReadingLevel.cpp ReadingLevel.h
	$(CC) $(CFLAGS) ReadingLevel.cpp

TFIDF.o: TFIDF.cpp TFIDF.h
	$(CC) $(CFLAGS) TFIDF.cpp
	
clean:
	rm *.o PA9

