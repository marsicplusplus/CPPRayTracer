CC = g++
CFLAGS = -g -Wall
TARGET = tracer.out

OBJ_DIR = Objects
SRC_DIR = Source

.PHONY: directories

default: directories ${TARGET}

directories: ${OBJ_DIR}

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${TARGET}: ${OBJ_DIR}/main.o
	${CC} ${CFLAGS} 
		${SRC_DIR}/main.cpp
		${SRC_DIR}/hittable_list.cpp
		${SRC_DIR}/camera.cpp
		${SRC_DIR}/main.cpp
