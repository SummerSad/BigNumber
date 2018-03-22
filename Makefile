CC = g++
CFLAGS = -Wall -Wextra -Wshadow -Wfloat-equal -g
SRCS = $(wildcard *.cpp)

all:
	$(CC) $(CFLAGS) $(SRCS)

mem:
	$(CC) $(CFLAGS) $(SRCS)
	drmemory.exe a.exe

clean:
	del *.exe
