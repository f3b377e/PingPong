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
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/francesco/Projects/realtime/pingpong/src/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/francesco/Projects/realtime/pingpong/src/cpp

# Include any dependencies generated for this target.
include CMakeFiles/second_unnamed.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/second_unnamed.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/second_unnamed.dir/flags.make

CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.o: CMakeFiles/second_unnamed.dir/flags.make
CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.o: unnamed\ semaphore/second.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/francesco/Projects/realtime/pingpong/src/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.o -c "/home/francesco/Projects/realtime/pingpong/src/cpp/unnamed semaphore/second.cpp"

CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/francesco/Projects/realtime/pingpong/src/cpp/unnamed semaphore/second.cpp" > CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.i

CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/francesco/Projects/realtime/pingpong/src/cpp/unnamed semaphore/second.cpp" -o CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.s

# Object files for target second_unnamed
second_unnamed_OBJECTS = \
"CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.o"

# External object files for target second_unnamed
second_unnamed_EXTERNAL_OBJECTS =

bin/second_unnamed: CMakeFiles/second_unnamed.dir/unnamed_semaphore/second.cpp.o
bin/second_unnamed: CMakeFiles/second_unnamed.dir/build.make
bin/second_unnamed: CMakeFiles/second_unnamed.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/francesco/Projects/realtime/pingpong/src/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/second_unnamed"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/second_unnamed.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/second_unnamed.dir/build: bin/second_unnamed

.PHONY : CMakeFiles/second_unnamed.dir/build

CMakeFiles/second_unnamed.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/second_unnamed.dir/cmake_clean.cmake
.PHONY : CMakeFiles/second_unnamed.dir/clean

CMakeFiles/second_unnamed.dir/depend:
	cd /home/francesco/Projects/realtime/pingpong/src/cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/francesco/Projects/realtime/pingpong/src/cpp /home/francesco/Projects/realtime/pingpong/src/cpp /home/francesco/Projects/realtime/pingpong/src/cpp /home/francesco/Projects/realtime/pingpong/src/cpp /home/francesco/Projects/realtime/pingpong/src/cpp/CMakeFiles/second_unnamed.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/second_unnamed.dir/depend

