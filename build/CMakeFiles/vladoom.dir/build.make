# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/agucs/Desktop/main/cpp/OpenGL/vladoom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build

# Include any dependencies generated for this target.
include CMakeFiles/vladoom.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/vladoom.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/vladoom.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vladoom.dir/flags.make

CMakeFiles/vladoom.dir/codegen:
.PHONY : CMakeFiles/vladoom.dir/codegen

CMakeFiles/vladoom.dir/src/ENG/convert.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/convert.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/convert.cpp
CMakeFiles/vladoom.dir/src/ENG/convert.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/convert.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/convert.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/convert.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/convert.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/convert.cpp

CMakeFiles/vladoom.dir/src/ENG/convert.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/convert.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/convert.cpp > CMakeFiles/vladoom.dir/src/ENG/convert.cpp.i

CMakeFiles/vladoom.dir/src/ENG/convert.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/convert.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/convert.cpp -o CMakeFiles/vladoom.dir/src/ENG/convert.cpp.s

CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Cube.cpp
CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Cube.cpp

CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Cube.cpp > CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.i

CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Cube.cpp -o CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.s

CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/EBO.cpp
CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/EBO.cpp

CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/EBO.cpp > CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.i

CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/EBO.cpp -o CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.s

CMakeFiles/vladoom.dir/src/ENG/glew.c.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/glew.c.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/glew.c
CMakeFiles/vladoom.dir/src/ENG/glew.c.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/vladoom.dir/src/ENG/glew.c.o"
	/usr/local/bin/gcc-14 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/glew.c.o -MF CMakeFiles/vladoom.dir/src/ENG/glew.c.o.d -o CMakeFiles/vladoom.dir/src/ENG/glew.c.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/glew.c

CMakeFiles/vladoom.dir/src/ENG/glew.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/vladoom.dir/src/ENG/glew.c.i"
	/usr/local/bin/gcc-14 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/glew.c > CMakeFiles/vladoom.dir/src/ENG/glew.c.i

CMakeFiles/vladoom.dir/src/ENG/glew.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/vladoom.dir/src/ENG/glew.c.s"
	/usr/local/bin/gcc-14 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/glew.c -o CMakeFiles/vladoom.dir/src/ENG/glew.c.s

CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Plane.cpp
CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Plane.cpp

CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Plane.cpp > CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.i

CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Plane.cpp -o CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.s

CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/programShader.cpp
CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/programShader.cpp

CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/programShader.cpp > CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.i

CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/programShader.cpp -o CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.s

CMakeFiles/vladoom.dir/src/ENG/stb.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/stb.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/stb.cpp
CMakeFiles/vladoom.dir/src/ENG/stb.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/stb.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/stb.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/stb.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/stb.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/stb.cpp

CMakeFiles/vladoom.dir/src/ENG/stb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/stb.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/stb.cpp > CMakeFiles/vladoom.dir/src/ENG/stb.cpp.i

CMakeFiles/vladoom.dir/src/ENG/stb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/stb.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/stb.cpp -o CMakeFiles/vladoom.dir/src/ENG/stb.cpp.s

CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Texture.cpp
CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Texture.cpp

CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Texture.cpp > CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.i

CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Texture.cpp -o CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.s

CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VAO.cpp
CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VAO.cpp

CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VAO.cpp > CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.i

CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VAO.cpp -o CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.s

CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VBO.cpp
CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VBO.cpp

CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VBO.cpp > CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.i

CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VBO.cpp -o CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.s

CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VPlane.cpp
CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VPlane.cpp

CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VPlane.cpp > CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.i

CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/VPlane.cpp -o CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.s

CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Symbol.cpp
CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Symbol.cpp

CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Symbol.cpp > CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.i

CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/Symbol.cpp -o CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.s

CMakeFiles/vladoom.dir/src/ENG/image.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/ENG/image.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/image.cpp
CMakeFiles/vladoom.dir/src/ENG/image.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/vladoom.dir/src/ENG/image.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/ENG/image.cpp.o -MF CMakeFiles/vladoom.dir/src/ENG/image.cpp.o.d -o CMakeFiles/vladoom.dir/src/ENG/image.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/image.cpp

CMakeFiles/vladoom.dir/src/ENG/image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/ENG/image.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/image.cpp > CMakeFiles/vladoom.dir/src/ENG/image.cpp.i

CMakeFiles/vladoom.dir/src/ENG/image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/ENG/image.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/ENG/image.cpp -o CMakeFiles/vladoom.dir/src/ENG/image.cpp.s

CMakeFiles/vladoom.dir/src/Hud.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/Hud.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/Hud.cpp
CMakeFiles/vladoom.dir/src/Hud.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/vladoom.dir/src/Hud.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/Hud.cpp.o -MF CMakeFiles/vladoom.dir/src/Hud.cpp.o.d -o CMakeFiles/vladoom.dir/src/Hud.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/Hud.cpp

CMakeFiles/vladoom.dir/src/Hud.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/Hud.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/Hud.cpp > CMakeFiles/vladoom.dir/src/Hud.cpp.i

CMakeFiles/vladoom.dir/src/Hud.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/Hud.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/Hud.cpp -o CMakeFiles/vladoom.dir/src/Hud.cpp.s

CMakeFiles/vladoom.dir/src/enemy.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/enemy.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/enemy.cpp
CMakeFiles/vladoom.dir/src/enemy.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/vladoom.dir/src/enemy.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/enemy.cpp.o -MF CMakeFiles/vladoom.dir/src/enemy.cpp.o.d -o CMakeFiles/vladoom.dir/src/enemy.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/enemy.cpp

CMakeFiles/vladoom.dir/src/enemy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/enemy.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/enemy.cpp > CMakeFiles/vladoom.dir/src/enemy.cpp.i

CMakeFiles/vladoom.dir/src/enemy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/enemy.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/enemy.cpp -o CMakeFiles/vladoom.dir/src/enemy.cpp.s

CMakeFiles/vladoom.dir/src/inputs.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/inputs.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/inputs.cpp
CMakeFiles/vladoom.dir/src/inputs.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/vladoom.dir/src/inputs.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/inputs.cpp.o -MF CMakeFiles/vladoom.dir/src/inputs.cpp.o.d -o CMakeFiles/vladoom.dir/src/inputs.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/inputs.cpp

CMakeFiles/vladoom.dir/src/inputs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/inputs.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/inputs.cpp > CMakeFiles/vladoom.dir/src/inputs.cpp.i

CMakeFiles/vladoom.dir/src/inputs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/inputs.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/inputs.cpp -o CMakeFiles/vladoom.dir/src/inputs.cpp.s

CMakeFiles/vladoom.dir/src/gun.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/gun.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/gun.cpp
CMakeFiles/vladoom.dir/src/gun.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/vladoom.dir/src/gun.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/gun.cpp.o -MF CMakeFiles/vladoom.dir/src/gun.cpp.o.d -o CMakeFiles/vladoom.dir/src/gun.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/gun.cpp

CMakeFiles/vladoom.dir/src/gun.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/gun.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/gun.cpp > CMakeFiles/vladoom.dir/src/gun.cpp.i

CMakeFiles/vladoom.dir/src/gun.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/gun.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/gun.cpp -o CMakeFiles/vladoom.dir/src/gun.cpp.s

CMakeFiles/vladoom.dir/src/Door.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/Door.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/Door.cpp
CMakeFiles/vladoom.dir/src/Door.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/vladoom.dir/src/Door.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/Door.cpp.o -MF CMakeFiles/vladoom.dir/src/Door.cpp.o.d -o CMakeFiles/vladoom.dir/src/Door.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/Door.cpp

CMakeFiles/vladoom.dir/src/Door.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/Door.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/Door.cpp > CMakeFiles/vladoom.dir/src/Door.cpp.i

CMakeFiles/vladoom.dir/src/Door.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/Door.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/Door.cpp -o CMakeFiles/vladoom.dir/src/Door.cpp.s

CMakeFiles/vladoom.dir/src/game.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/game.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/game.cpp
CMakeFiles/vladoom.dir/src/game.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/vladoom.dir/src/game.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/game.cpp.o -MF CMakeFiles/vladoom.dir/src/game.cpp.o.d -o CMakeFiles/vladoom.dir/src/game.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/game.cpp

CMakeFiles/vladoom.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/game.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/game.cpp > CMakeFiles/vladoom.dir/src/game.cpp.i

CMakeFiles/vladoom.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/game.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/game.cpp -o CMakeFiles/vladoom.dir/src/game.cpp.s

CMakeFiles/vladoom.dir/src/main.cpp.o: CMakeFiles/vladoom.dir/flags.make
CMakeFiles/vladoom.dir/src/main.cpp.o: /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/main.cpp
CMakeFiles/vladoom.dir/src/main.cpp.o: CMakeFiles/vladoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Building CXX object CMakeFiles/vladoom.dir/src/main.cpp.o"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vladoom.dir/src/main.cpp.o -MF CMakeFiles/vladoom.dir/src/main.cpp.o.d -o CMakeFiles/vladoom.dir/src/main.cpp.o -c /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/main.cpp

CMakeFiles/vladoom.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vladoom.dir/src/main.cpp.i"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/main.cpp > CMakeFiles/vladoom.dir/src/main.cpp.i

CMakeFiles/vladoom.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vladoom.dir/src/main.cpp.s"
	/usr/local/bin/g++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/src/main.cpp -o CMakeFiles/vladoom.dir/src/main.cpp.s

# Object files for target vladoom
vladoom_OBJECTS = \
"CMakeFiles/vladoom.dir/src/ENG/convert.cpp.o" \
"CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.o" \
"CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.o" \
"CMakeFiles/vladoom.dir/src/ENG/glew.c.o" \
"CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.o" \
"CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.o" \
"CMakeFiles/vladoom.dir/src/ENG/stb.cpp.o" \
"CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.o" \
"CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.o" \
"CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.o" \
"CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.o" \
"CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.o" \
"CMakeFiles/vladoom.dir/src/ENG/image.cpp.o" \
"CMakeFiles/vladoom.dir/src/Hud.cpp.o" \
"CMakeFiles/vladoom.dir/src/enemy.cpp.o" \
"CMakeFiles/vladoom.dir/src/inputs.cpp.o" \
"CMakeFiles/vladoom.dir/src/gun.cpp.o" \
"CMakeFiles/vladoom.dir/src/Door.cpp.o" \
"CMakeFiles/vladoom.dir/src/game.cpp.o" \
"CMakeFiles/vladoom.dir/src/main.cpp.o"

# External object files for target vladoom
vladoom_EXTERNAL_OBJECTS =

vladoom: CMakeFiles/vladoom.dir/src/ENG/convert.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/Cube.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/EBO.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/glew.c.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/Plane.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/programShader.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/stb.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/Texture.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/VAO.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/VBO.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/VPlane.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/Symbol.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/ENG/image.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/Hud.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/enemy.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/inputs.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/gun.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/Door.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/game.cpp.o
vladoom: CMakeFiles/vladoom.dir/src/main.cpp.o
vladoom: CMakeFiles/vladoom.dir/build.make
vladoom: /usr/local/lib/libglfw.dylib
vladoom: /Library/Developer/CommandLineTools/SDKs/MacOSX14.4.sdk/System/Library/Frameworks/OpenGL.framework
vladoom: CMakeFiles/vladoom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_21) "Linking CXX executable vladoom"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vladoom.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vladoom.dir/build: vladoom
.PHONY : CMakeFiles/vladoom.dir/build

CMakeFiles/vladoom.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vladoom.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vladoom.dir/clean

CMakeFiles/vladoom.dir/depend:
	cd /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/agucs/Desktop/main/cpp/OpenGL/vladoom /Users/agucs/Desktop/main/cpp/OpenGL/vladoom /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build /Users/agucs/Desktop/main/cpp/OpenGL/vladoom/build/CMakeFiles/vladoom.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/vladoom.dir/depend
