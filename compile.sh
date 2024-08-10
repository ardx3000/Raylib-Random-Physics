#!/bin/bash

#Add Dirs
SRC_DIR=src
INCLUDE_DIR=include

#Output exec

OUTPUT=PhysiscsSim

#Compiler and flags
CC=gcc
CFLAGS="-I${INCLUDE_DIR} -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL"

#Find all files in the src dir
SRC_FILES=$(find ${SRC_DIR} -name '*.c')

#Compile the project
${CC} -o ${OUTPUT} ${SRC_FILES} ${CFLAGS}
