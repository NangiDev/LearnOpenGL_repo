CC=g++
INC_PATH=-Iinclude
CFLAGS=-lglfw -lGL -ldl 

output: src/main.cpp
	@mkdir build
	$(CC) src/main.cpp src/glad.c $(INC_PATH) $(CFLAGS) -o build/$@

# -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
