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
include server/libs/CMakeFiles/libs.dir/depend.make

# Include the progress variables for this target.
include server/libs/CMakeFiles/libs.dir/progress.make

# Include the compile flags for this target's objects.
include server/libs/CMakeFiles/libs.dir/flags.make

server/libs/CMakeFiles/libs.dir/connection/connection.cpp.o: server/libs/CMakeFiles/libs.dir/flags.make
server/libs/CMakeFiles/libs.dir/connection/connection.cpp.o: ../server/libs/connection/connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lexolordan/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object server/libs/CMakeFiles/libs.dir/connection/connection.cpp.o"
	cd /Users/lexolordan/webserver/cmake-build-debug/server/libs && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libs.dir/connection/connection.cpp.o -c /Users/lexolordan/webserver/server/libs/connection/connection.cpp

server/libs/CMakeFiles/libs.dir/connection/connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libs.dir/connection/connection.cpp.i"
	cd /Users/lexolordan/webserver/cmake-build-debug/server/libs && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lexolordan/webserver/server/libs/connection/connection.cpp > CMakeFiles/libs.dir/connection/connection.cpp.i

server/libs/CMakeFiles/libs.dir/connection/connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libs.dir/connection/connection.cpp.s"
	cd /Users/lexolordan/webserver/cmake-build-debug/server/libs && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lexolordan/webserver/server/libs/connection/connection.cpp -o CMakeFiles/libs.dir/connection/connection.cpp.s

# Object files for target libs
libs_OBJECTS = \
"CMakeFiles/libs.dir/connection/connection.cpp.o"

# External object files for target libs
libs_EXTERNAL_OBJECTS =

server/libs/liblibs.a: server/libs/CMakeFiles/libs.dir/connection/connection.cpp.o
server/libs/liblibs.a: server/libs/CMakeFiles/libs.dir/build.make
server/libs/liblibs.a: server/libs/CMakeFiles/libs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lexolordan/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblibs.a"
	cd /Users/lexolordan/webserver/cmake-build-debug/server/libs && $(CMAKE_COMMAND) -P CMakeFiles/libs.dir/cmake_clean_target.cmake
	cd /Users/lexolordan/webserver/cmake-build-debug/server/libs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server/libs/CMakeFiles/libs.dir/build: server/libs/liblibs.a

.PHONY : server/libs/CMakeFiles/libs.dir/build

server/libs/CMakeFiles/libs.dir/clean:
	cd /Users/lexolordan/webserver/cmake-build-debug/server/libs && $(CMAKE_COMMAND) -P CMakeFiles/libs.dir/cmake_clean.cmake
.PHONY : server/libs/CMakeFiles/libs.dir/clean

server/libs/CMakeFiles/libs.dir/depend:
	cd /Users/lexolordan/webserver/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lexolordan/webserver /Users/lexolordan/webserver/server/libs /Users/lexolordan/webserver/cmake-build-debug /Users/lexolordan/webserver/cmake-build-debug/server/libs /Users/lexolordan/webserver/cmake-build-debug/server/libs/CMakeFiles/libs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : server/libs/CMakeFiles/libs.dir/depend

