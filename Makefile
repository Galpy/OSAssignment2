#IDIR = ../include	 if include files are in a dir
CC=g++
CFLAGS=-I.
MAKE = make
RM = rm
DEPS = toLowerCase.cpp		#if you have .h files that .o files are dependent on
OBJ = client.o toLowerCase.o server.o	#.o files included here

# ODIR = obj 	this is .o file dir
# LDIR = ../lib 	this is local lib dir

LIBS = -lm

# _DEPS = hellomake.h
# DEPS = $(patsubst %,$(IDIR)/%,%(_DEPS)) 

# _OBJ = hellomake.o hellofunc.o
# OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# 	$(ODIR)/%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

# 	hellomake: $(OBJ)
#	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: client.cpp server.cpp
	$(CC) -o server server.cpp toLowerCase.cpp
	$(CC) -o client client.cpp toLowerCase.cpp
	gnome-terminal -t server_target --working-directory=/home/galpy/CMSC4153/Assignment2
	gnome-terminal -t client_target --working-directory=/home/galpy/CMSC4153/Assignment2
	sleep 4s

server_target:
	./server &

client_target: 
	./client test2.txt

clean:
	rm server 
	rm client

