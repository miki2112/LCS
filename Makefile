OBJS = lcs.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
all:
	$(CC) main.cpp -o lcs
