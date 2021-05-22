CC=g++
INC_PATH=-Iinclude
CFLAGS=-lglfw -lGL -ldl

build: src/main.cpp
	@mkdir -p bin
	$(CC) src/main.cpp src/glad.c $(INC_PATH) $(CFLAGS) -o bin/$@

run: build
	@./bin/build

clean:
	@rm -rf bin

# -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
