CC=g++
CFLAGS=-lvlc

run: app
	@echo "running app..."
	./app

app: main.cpp
	@echo "compiling main.cpp..."
	$(CC) $^ $(CFLAGS) -o $@
