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
include CMakeFiles/CppToUnity.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CppToUnity.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CppToUnity.dir/flags.make

CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.o: CMakeFiles/CppToUnity.dir/flags.make
CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.o: dll/CppToUnity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/francesco/Projects/realtime/pingpong/src/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.o -c /home/francesco/Projects/realtime/pingpong/src/cpp/dll/CppToUnity.cpp

CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/francesco/Projects/realtime/pingpong/src/cpp/dll/CppToUnity.cpp > CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.i

CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/francesco/Projects/realtime/pingpong/src/cpp/dll/CppToUnity.cpp -o CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.s

# Object files for target CppToUnity
CppToUnity_OBJECTS = \
"CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.o"

# External object files for target CppToUnity
CppToUnity_EXTERNAL_OBJECTS =

libCppToUnity.so: CMakeFiles/CppToUnity.dir/dll/CppToUnity.cpp.o
libCppToUnity.so: CMakeFiles/CppToUnity.dir/build.make
libCppToUnity.so: /usr/local/lib/libopencv_dnn.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_gapi.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_ml.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_objdetect.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_shape.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_stitching.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_superres.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_videostab.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_photo.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_video.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_calib3d.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_features2d.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_flann.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_highgui.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_videoio.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_imgcodecs.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_imgproc.so.4.0.0
libCppToUnity.so: /usr/local/lib/libopencv_core.so.4.0.0
libCppToUnity.so: CMakeFiles/CppToUnity.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/francesco/Projects/realtime/pingpong/src/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libCppToUnity.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CppToUnity.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CppToUnity.dir/build: libCppToUnity.so

.PHONY : CMakeFiles/CppToUnity.dir/build

CMakeFiles/CppToUnity.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CppToUnity.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CppToUnity.dir/clean

CMakeFiles/CppToUnity.dir/depend:
	cd /home/francesco/Projects/realtime/pingpong/src/cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/francesco/Projects/realtime/pingpong/src/cpp /home/francesco/Projects/realtime/pingpong/src/cpp /home/francesco/Projects/realtime/pingpong/src/cpp /home/francesco/Projects/realtime/pingpong/src/cpp /home/francesco/Projects/realtime/pingpong/src/cpp/CMakeFiles/CppToUnity.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CppToUnity.dir/depend

