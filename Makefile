build:
	clear
	g++-14 -g src/*.cpp src/ENG/*.c -w -o build/main -I./deps/include -I./src/ENG -I./headers -L./deps/library ./deps/library/libglfw.3.4.dylib -framework OpenGL -framework Cocoa
run:
	clear
	./build/main