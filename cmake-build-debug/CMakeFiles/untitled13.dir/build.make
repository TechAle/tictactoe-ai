# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alessandro/CLionProjects/TicTacToeMiniMax

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alessandro/CLionProjects/TicTacToeMiniMax/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/untitled13.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled13.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled13.dir/flags.make

CMakeFiles/untitled13.dir/main.cpp.o: CMakeFiles/untitled13.dir/flags.make
CMakeFiles/untitled13.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alessandro/CLionProjects/TicTacToeMiniMax/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/untitled13.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/untitled13.dir/main.cpp.o -c /Users/alessandro/CLionProjects/TicTacToeMiniMax/main.cpp

CMakeFiles/untitled13.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled13.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alessandro/CLionProjects/TicTacToeMiniMax/main.cpp > CMakeFiles/untitled13.dir/main.cpp.i

CMakeFiles/untitled13.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled13.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alessandro/CLionProjects/TicTacToeMiniMax/main.cpp -o CMakeFiles/untitled13.dir/main.cpp.s

# Object files for target untitled13
untitled13_OBJECTS = \
"CMakeFiles/untitled13.dir/main.cpp.o"

# External object files for target untitled13
untitled13_EXTERNAL_OBJECTS =

untitled13: CMakeFiles/untitled13.dir/main.cpp.o
untitled13: CMakeFiles/untitled13.dir/build.make
untitled13: CMakeFiles/untitled13.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alessandro/CLionProjects/TicTacToeMiniMax/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable untitled13"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled13.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled13.dir/build: untitled13

.PHONY : CMakeFiles/untitled13.dir/build

CMakeFiles/untitled13.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled13.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled13.dir/clean

CMakeFiles/untitled13.dir/depend:
	cd /Users/alessandro/CLionProjects/TicTacToeMiniMax/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alessandro/CLionProjects/TicTacToeMiniMax /Users/alessandro/CLionProjects/TicTacToeMiniMax /Users/alessandro/CLionProjects/TicTacToeMiniMax/cmake-build-debug /Users/alessandro/CLionProjects/TicTacToeMiniMax/cmake-build-debug /Users/alessandro/CLionProjects/TicTacToeMiniMax/cmake-build-debug/CMakeFiles/untitled13.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/untitled13.dir/depend

