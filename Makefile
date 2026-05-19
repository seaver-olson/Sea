CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
CPPFLAGS ?= -Iinclude

TARGET := sea
SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
