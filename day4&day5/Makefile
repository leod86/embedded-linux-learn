TARGET = cpu_monitor
SRCS = main.c cpu.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -g

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) $(OBJS)
