CC = g++
CFLAGS = -g -Wall - O2
OBJS = compiler.o lexical.o parser.o symboltable.o code_generator.o
TARGET = Compiler2021

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean : 
	rm -f *.o
	rm -f $(TARGET)
	rm *.code
	rm *.symbol
