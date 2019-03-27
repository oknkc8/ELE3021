# Compiler and Compile options.
CC = gcc

#Macros specifying path for compile.
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

# Compile command.
TARGET = shell
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Delete binary & object files.
clean:
	rm $(TARGET) $(OBJS)
