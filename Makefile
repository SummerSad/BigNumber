CC = g++
CFLAGS = -g -Wall -Wextra -Wshadow
SRCS = $(wildcard *.cpp)

all:
	$(CC) $(CFLAGS) $(SRCS)

mem:
	drmemory.exe a.exe

clean:
	del *.exe