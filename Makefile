all: pattern1 slow_pattern1 clean

slow_pattern1: slow_display.o pattern1.o
	g++ pattern1.o slow_display.o -lwiringPi -pthread -o slow_pattern1

pattern1: display.o pattern1.o
	g++ pattern1.o display.o -lwiringPi -pthread -o pattern1

pattern1.o: demos/pattern1.cpp
	g++ -c demos/pattern1.cpp -o pattern1.o

ssnake.o: snake/SSnake.cpp snake/SSnake.h
	g++ -c snake/SSnake.cpp -o ssnake.o

display.o: display/Display.cpp display/Display.h
	g++ -c display/Display.cpp -o display.o

slow_display.o: display/Display.cpp display/Display.h
	g++ -c display/Display.cpp -lwiringPi -pthread -o slow_display.o -D SLOW

uint4.o: util/uint4.cpp util/uint4.h
	g++ -c util/uint4.cpp -o uint4.o

clean:
	rm uint4.o slow_display.o display.o ssnake.o pattern1.o
