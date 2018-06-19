CC = g++
CFLAGS = -Wall -Wextra -Wshadow -Wfloat-equal
SRCS = $(wildcard src/*.cpp)
NAME = 1612180_1612628_1612403.exe

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

debug:
	$(CC) $(CFLAGS) $(SRCS) -g -o $(NAME)

mem: all
	drmemory.exe $(NAME)

int: all
	$(NAME) int int_1.txt int_2.txt

float: all
	$(NAME) float float_1.txt float_2.txt

clean:
	del *.exe
