OBJS = main.cpp
CC = g++
OBJ_NAME = HoyienGame
COMPILER_FLAGS = -w
LINNKER_FLAGS = -framework SDL2
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINNKER_FLAGS) -o $(OBJ_NAME)
