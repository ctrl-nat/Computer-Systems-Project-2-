################################################################################
# Makefile for Computer Systems Project 2
# Created by Natalie Kong (nkong1, 904997)
# Adapted from http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor
################################################################################

CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -I. -O3
DEPS = sha256.h compute.h
OBJ = sha256.o compute.o crack.o
EXE = crack

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

##Create executable linked file from object files.
$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

##Delete object files
clean:
	/bin/rm $(OBJ)
	
##Performs clean (i.e. delete object files) and deletes executable
clobber: clean
	/bin/rm $(EXE)
