SRC := writer.c
TARGET:=writer
OBJS:=$(SRC:.c=.o)
CC:=gcc
CROSS_COMPILE?=

.PHONY: all
.PHONY: clean

default: all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CROSS_COMPILE)$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CROSS_COMPILE)$(CC) -c $< -o $@

clean:
	rm -f *.o $(TARGET)