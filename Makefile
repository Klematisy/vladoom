build:
	clear
	g++-14 -g Source\ files/*.cpp Source\ files//*.c -w -o Output\ files/main -I./Dependencies/include -I./Header\ files -L./Dependencies/library ./Dependencies/library/libglfw.3.4.dylib -framework OpenGL -framework Cocoa
run:
	clear
	./Output\ files/main