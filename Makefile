CC = g++
CFLAGS = -g -Wall - O2
OBJS = compiler.o lexical.o parser.o symbol_table.o code_generator.o
TARGET = Compiler2021

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)
	rm -f *.o

clean : 
	rm -f $(TARGET)
