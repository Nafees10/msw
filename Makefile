CC = gcc
CFLAGS = -Wall -Wextra -static
TARGET = msw

RELEASE_CFLAGS = -O2 -DNDEBUG
DEBUG_CFLAGS = -O0 -g

all: release

release: $(TARGET)

debug: clean
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -o $(TARGET) msw.c

$(TARGET): msw.c
	$(CC) $(CFLAGS) $(RELEASE_CFLAGS) -o $(TARGET) msw.c

clean:
	rm -f $(TARGET)
