CC := gcc
CFLAGS := -g -Wall -Wextra -Wpedantic
TARGET := a
LIBS := -lm
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,%,$(SRCS))

all: $(OBJS)
%: %.c
	$(CC) $(CFLAGS) -o $(TARGET) $< $(LIBS)
clean:
	rm -rf $(TARGET)