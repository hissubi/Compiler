CC = g++
CFLAGS = -g -Wall
OBJS = compiler.o lexical.o
TARGET = Compiler2021

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean : 
	rm -f *.o
	rm -f $(TARGET)
	rm *.code
	rm *.symbol
