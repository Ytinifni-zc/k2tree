# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.7.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.7.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/infinity/Workspace/BDSA/k2tree/libk2tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_bitarray.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_bitarray.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_bitarray.dir/flags.make

tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o: tests/CMakeFiles/test_bitarray.dir/flags.make
tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o: ../tests/test_bitarray.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_bitarray.dir/test_bitarray.cc.o -c /Users/infinity/Workspace/BDSA/k2tree/libk2tree/tests/test_bitarray.cc

tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_bitarray.dir/test_bitarray.cc.i"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/infinity/Workspace/BDSA/k2tree/libk2tree/tests/test_bitarray.cc > CMakeFiles/test_bitarray.dir/test_bitarray.cc.i

tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_bitarray.dir/test_bitarray.cc.s"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/infinity/Workspace/BDSA/k2tree/libk2tree/tests/test_bitarray.cc -o CMakeFiles/test_bitarray.dir/test_bitarray.cc.s

tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o.requires:

.PHONY : tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o.requires

tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o.provides: tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o.requires
	$(MAKE) -f tests/CMakeFiles/test_bitarray.dir/build.make tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o.provides.build
.PHONY : tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o.provides

tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o.provides.build: tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o


tests/CMakeFiles/test_bitarray.dir/queries.cc.o: tests/CMakeFiles/test_bitarray.dir/flags.make
tests/CMakeFiles/test_bitarray.dir/queries.cc.o: ../tests/queries.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/test_bitarray.dir/queries.cc.o"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_bitarray.dir/queries.cc.o -c /Users/infinity/Workspace/BDSA/k2tree/libk2tree/tests/queries.cc

tests/CMakeFiles/test_bitarray.dir/queries.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_bitarray.dir/queries.cc.i"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/infinity/Workspace/BDSA/k2tree/libk2tree/tests/queries.cc > CMakeFiles/test_bitarray.dir/queries.cc.i

tests/CMakeFiles/test_bitarray.dir/queries.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_bitarray.dir/queries.cc.s"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/infinity/Workspace/BDSA/k2tree/libk2tree/tests/queries.cc -o CMakeFiles/test_bitarray.dir/queries.cc.s

tests/CMakeFiles/test_bitarray.dir/queries.cc.o.requires:

.PHONY : tests/CMakeFiles/test_bitarray.dir/queries.cc.o.requires

tests/CMakeFiles/test_bitarray.dir/queries.cc.o.provides: tests/CMakeFiles/test_bitarray.dir/queries.cc.o.requires
	$(MAKE) -f tests/CMakeFiles/test_bitarray.dir/build.make tests/CMakeFiles/test_bitarray.dir/queries.cc.o.provides.build
.PHONY : tests/CMakeFiles/test_bitarray.dir/queries.cc.o.provides

tests/CMakeFiles/test_bitarray.dir/queries.cc.o.provides.build: tests/CMakeFiles/test_bitarray.dir/queries.cc.o


# Object files for target test_bitarray
test_bitarray_OBJECTS = \
"CMakeFiles/test_bitarray.dir/test_bitarray.cc.o" \
"CMakeFiles/test_bitarray.dir/queries.cc.o"

# External object files for target test_bitarray
test_bitarray_EXTERNAL_OBJECTS =

tests/test_bitarray: tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o
tests/test_bitarray: tests/CMakeFiles/test_bitarray.dir/queries.cc.o
tests/test_bitarray: tests/CMakeFiles/test_bitarray.dir/build.make
tests/test_bitarray: gtest/libgtest.a
tests/test_bitarray: gtest/libgtest_main.a
tests/test_bitarray: gtest/libgtest.a
tests/test_bitarray: src/libk2tree.dylib
tests/test_bitarray: /usr/local/lib/libboost_system.dylib
tests/test_bitarray: /usr/local/lib/libboost_filesystem.dylib
tests/test_bitarray: /usr/local/lib/libboost_regex.dylib
tests/test_bitarray: /usr/local/lib/libcds2.dylib
tests/test_bitarray: dacs/libdacs.dylib
tests/test_bitarray: tests/CMakeFiles/test_bitarray.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_bitarray"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_bitarray.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_bitarray.dir/build: tests/test_bitarray

.PHONY : tests/CMakeFiles/test_bitarray.dir/build

tests/CMakeFiles/test_bitarray.dir/requires: tests/CMakeFiles/test_bitarray.dir/test_bitarray.cc.o.requires
tests/CMakeFiles/test_bitarray.dir/requires: tests/CMakeFiles/test_bitarray.dir/queries.cc.o.requires

.PHONY : tests/CMakeFiles/test_bitarray.dir/requires

tests/CMakeFiles/test_bitarray.dir/clean:
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_bitarray.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_bitarray.dir/clean

tests/CMakeFiles/test_bitarray.dir/depend:
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/infinity/Workspace/BDSA/k2tree/libk2tree /Users/infinity/Workspace/BDSA/k2tree/libk2tree/tests /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/tests /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/tests/CMakeFiles/test_bitarray.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_bitarray.dir/depend

