# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lexolordan/webserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lexolordan/webserver/cmake-build-debug

# Include any dependencies generated for this target.
include server/build/libs/daemons/CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include server/build/libs/daemons/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include server/build/libs/daemons/CMakeFiles/main.dir/flags.make

server/build/libs/daemons/CMakeFiles/main.dir/main.cpp.o: server/build/libs/daemons/CMakeFiles/main.dir/flags.make
server/build/libs/daemons/CMakeFiles/main.dir/main.cpp.o: ../server/daemons/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lexolordan/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object server/build/libs/daemons/CMakeFiles/main.dir/main.cpp.o"
	cd /Users/lexolordan/webserver/cmake-build-debug/server/build/libs/daemons && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/main.cpp.o -c /Users/lexolordan/webserver/server/daemons/main.cpp

server/build/libs/daemons/CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	cd /Users/lexolordan/webserver/cmake-build-debug/server/build/libs/daemons && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lexolordan/webserver/server/daemons/main.cpp > CMakeFiles/main.dir/main.cpp.i

server/build/libs/daemons/CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	cd /Users/lexolordan/webserver/cmake-build-debug/server/build/libs/daemons && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lexolordan/webserver/server/daemons/main.cpp -o CMakeFiles/main.dir/main.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

server/build/libs/daemons/main: server/build/libs/daemons/CMakeFiles/main.dir/main.cpp.o
server/build/libs/daemons/main: server/build/libs/daemons/CMakeFiles/main.dir/build.make
server/build/libs/daemons/main: server/build/libs/daemons/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lexolordan/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main"
	cd /Users/lexolordan/webserver/cmake-build-debug/server/build/libs/daemons && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server/build/libs/daemons/CMakeFiles/main.dir/build: server/build/libs/daemons/main

.PHONY : server/build/libs/daemons/CMakeFiles/main.dir/build

server/build/libs/daemons/CMakeFiles/main.dir/clean:
	cd /Users/lexolordan/webserver/cmake-build-debug/server/build/libs/daemons && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : server/build/libs/daemons/CMakeFiles/main.dir/clean

server/build/libs/daemons/CMakeFiles/main.dir/depend:
	cd /Users/lexolordan/webserver/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lexolordan/webserver /Users/lexolordan/webserver/server/daemons /Users/lexolordan/webserver/cmake-build-debug /Users/lexolordan/webserver/cmake-build-debug/server/build/libs/daemons /Users/lexolordan/webserver/cmake-build-debug/server/build/libs/daemons/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : server/build/libs/daemons/CMakeFiles/main.dir/depend

