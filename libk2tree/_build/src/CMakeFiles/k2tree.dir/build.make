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
include src/CMakeFiles/k2tree.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/k2tree.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/k2tree.dir/flags.make

src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o: src/CMakeFiles/k2tree.dir/flags.make
src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o: ../src/libk2tree/builder/k2tree_builder.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o -c /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/builder/k2tree_builder.cc

src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.i"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/builder/k2tree_builder.cc > CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.i

src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.s"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/builder/k2tree_builder.cc -o CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.s

src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o.requires:

.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o.requires

src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o.provides: src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o.requires
	$(MAKE) -f src/CMakeFiles/k2tree.dir/build.make src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o.provides.build
.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o.provides

src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o.provides.build: src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o


src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o: src/CMakeFiles/k2tree.dir/flags.make
src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o: ../src/libk2tree/builder/k2tree_partition_builder.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o -c /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/builder/k2tree_partition_builder.cc

src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.i"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/builder/k2tree_partition_builder.cc > CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.i

src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.s"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/builder/k2tree_partition_builder.cc -o CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.s

src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o.requires:

.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o.requires

src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o.provides: src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o.requires
	$(MAKE) -f src/CMakeFiles/k2tree.dir/build.make src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o.provides.build
.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o.provides

src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o.provides.build: src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o


src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o: src/CMakeFiles/k2tree.dir/flags.make
src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o: ../src/libk2tree/compressed_hybrid.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o -c /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compressed_hybrid.cc

src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.i"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compressed_hybrid.cc > CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.i

src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.s"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compressed_hybrid.cc -o CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.s

src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o.requires:

.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o.requires

src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o.provides: src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o.requires
	$(MAKE) -f src/CMakeFiles/k2tree.dir/build.make src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o.provides.build
.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o.provides

src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o.provides.build: src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o


src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o: src/CMakeFiles/k2tree.dir/flags.make
src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o: ../src/libk2tree/compressed_partition.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o -c /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compressed_partition.cc

src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.i"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compressed_partition.cc > CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.i

src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.s"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compressed_partition.cc -o CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.s

src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o.requires:

.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o.requires

src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o.provides: src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o.requires
	$(MAKE) -f src/CMakeFiles/k2tree.dir/build.make src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o.provides.build
.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o.provides

src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o.provides.build: src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o


src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o: src/CMakeFiles/k2tree.dir/flags.make
src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o: ../src/libk2tree/compression/hash.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o -c /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compression/hash.cc

src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.i"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compression/hash.cc > CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.i

src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.s"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compression/hash.cc -o CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.s

src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o.requires:

.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o.requires

src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o.provides: src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o.requires
	$(MAKE) -f src/CMakeFiles/k2tree.dir/build.make src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o.provides.build
.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o.provides

src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o.provides.build: src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o


src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o: src/CMakeFiles/k2tree.dir/flags.make
src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o: ../src/libk2tree/compression/vocabulary.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o -c /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compression/vocabulary.cc

src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.i"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compression/vocabulary.cc > CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.i

src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.s"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/compression/vocabulary.cc -o CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.s

src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o.requires:

.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o.requires

src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o.provides: src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o.requires
	$(MAKE) -f src/CMakeFiles/k2tree.dir/build.make src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o.provides.build
.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o.provides

src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o.provides.build: src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o


src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o: src/CMakeFiles/k2tree.dir/flags.make
src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o: ../src/libk2tree/hybrid_k2tree.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o -c /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/hybrid_k2tree.cc

src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.i"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/hybrid_k2tree.cc > CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.i

src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.s"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/hybrid_k2tree.cc -o CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.s

src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o.requires:

.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o.requires

src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o.provides: src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o.requires
	$(MAKE) -f src/CMakeFiles/k2tree.dir/build.make src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o.provides.build
.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o.provides

src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o.provides.build: src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o


src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o: src/CMakeFiles/k2tree.dir/flags.make
src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o: ../src/libk2tree/k2tree_partition.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o -c /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/k2tree_partition.cc

src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.i"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/k2tree_partition.cc > CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.i

src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.s"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/k2tree_partition.cc -o CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.s

src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o.requires:

.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o.requires

src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o.provides: src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o.requires
	$(MAKE) -f src/CMakeFiles/k2tree.dir/build.make src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o.provides.build
.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o.provides

src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o.provides.build: src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o


src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o: src/CMakeFiles/k2tree.dir/flags.make
src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o: ../src/libk2tree/utils/utils.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o -c /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/utils/utils.cc

src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.i"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/utils/utils.cc > CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.i

src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.s"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src/libk2tree/utils/utils.cc -o CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.s

src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o.requires:

.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o.requires

src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o.provides: src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o.requires
	$(MAKE) -f src/CMakeFiles/k2tree.dir/build.make src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o.provides.build
.PHONY : src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o.provides

src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o.provides.build: src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o


# Object files for target k2tree
k2tree_OBJECTS = \
"CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o" \
"CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o" \
"CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o" \
"CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o" \
"CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o" \
"CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o" \
"CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o" \
"CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o" \
"CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o"

# External object files for target k2tree
k2tree_EXTERNAL_OBJECTS =

src/libk2tree.dylib: src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o
src/libk2tree.dylib: src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o
src/libk2tree.dylib: src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o
src/libk2tree.dylib: src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o
src/libk2tree.dylib: src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o
src/libk2tree.dylib: src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o
src/libk2tree.dylib: src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o
src/libk2tree.dylib: src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o
src/libk2tree.dylib: src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o
src/libk2tree.dylib: src/CMakeFiles/k2tree.dir/build.make
src/libk2tree.dylib: /usr/local/lib/libcds2.dylib
src/libk2tree.dylib: dacs/libdacs.dylib
src/libk2tree.dylib: src/CMakeFiles/k2tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX shared library libk2tree.dylib"
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/k2tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/k2tree.dir/build: src/libk2tree.dylib

.PHONY : src/CMakeFiles/k2tree.dir/build

src/CMakeFiles/k2tree.dir/requires: src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_builder.cc.o.requires
src/CMakeFiles/k2tree.dir/requires: src/CMakeFiles/k2tree.dir/libk2tree/builder/k2tree_partition_builder.cc.o.requires
src/CMakeFiles/k2tree.dir/requires: src/CMakeFiles/k2tree.dir/libk2tree/compressed_hybrid.cc.o.requires
src/CMakeFiles/k2tree.dir/requires: src/CMakeFiles/k2tree.dir/libk2tree/compressed_partition.cc.o.requires
src/CMakeFiles/k2tree.dir/requires: src/CMakeFiles/k2tree.dir/libk2tree/compression/hash.cc.o.requires
src/CMakeFiles/k2tree.dir/requires: src/CMakeFiles/k2tree.dir/libk2tree/compression/vocabulary.cc.o.requires
src/CMakeFiles/k2tree.dir/requires: src/CMakeFiles/k2tree.dir/libk2tree/hybrid_k2tree.cc.o.requires
src/CMakeFiles/k2tree.dir/requires: src/CMakeFiles/k2tree.dir/libk2tree/k2tree_partition.cc.o.requires
src/CMakeFiles/k2tree.dir/requires: src/CMakeFiles/k2tree.dir/libk2tree/utils/utils.cc.o.requires

.PHONY : src/CMakeFiles/k2tree.dir/requires

src/CMakeFiles/k2tree.dir/clean:
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src && $(CMAKE_COMMAND) -P CMakeFiles/k2tree.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/k2tree.dir/clean

src/CMakeFiles/k2tree.dir/depend:
	cd /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/infinity/Workspace/BDSA/k2tree/libk2tree /Users/infinity/Workspace/BDSA/k2tree/libk2tree/src /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src /Users/infinity/Workspace/BDSA/k2tree/libk2tree/_build/src/CMakeFiles/k2tree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/k2tree.dir/depend
