# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.0.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.0.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/jongan/Dropbox/HiWi job stuffs/hypro"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build"

# Include any dependencies generated for this target.
include examples/CMakeFiles/example_ppl_nncPolyhedra.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/example_ppl_nncPolyhedra.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/example_ppl_nncPolyhedra.dir/flags.make

examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o: examples/CMakeFiles/example_ppl_nncPolyhedra.dir/flags.make
examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o: ../examples/example_ppl_nncPolyhedra.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o"
	cd "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/examples" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o -c "/Users/jongan/Dropbox/HiWi job stuffs/hypro/examples/example_ppl_nncPolyhedra.cpp"

examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.i"
	cd "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/examples" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/Users/jongan/Dropbox/HiWi job stuffs/hypro/examples/example_ppl_nncPolyhedra.cpp" > CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.i

examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.s"
	cd "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/examples" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/Users/jongan/Dropbox/HiWi job stuffs/hypro/examples/example_ppl_nncPolyhedra.cpp" -o CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.s

examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o.requires:
.PHONY : examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o.requires

examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o.provides: examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/example_ppl_nncPolyhedra.dir/build.make examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o.provides.build
.PHONY : examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o.provides

examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o.provides.build: examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o

# Object files for target example_ppl_nncPolyhedra
example_ppl_nncPolyhedra_OBJECTS = \
"CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o"

# External object files for target example_ppl_nncPolyhedra
example_ppl_nncPolyhedra_EXTERNAL_OBJECTS =

bin/example_ppl_nncPolyhedra: examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o
bin/example_ppl_nncPolyhedra: examples/CMakeFiles/example_ppl_nncPolyhedra.dir/build.make
bin/example_ppl_nncPolyhedra: lib/libhypro.dylib
bin/example_ppl_nncPolyhedra: /usr/local/lib/libcarl.0.1.0.dylib
bin/example_ppl_nncPolyhedra: /usr/local/lib/libgmpxx.dylib
bin/example_ppl_nncPolyhedra: /usr/local/lib/liblog4cplus.dylib
bin/example_ppl_nncPolyhedra: /usr/local/lib/liblog4cplus.dylib
bin/example_ppl_nncPolyhedra: /usr/local/Cellar/cln/1.3.3/lib/libcln.dylib
bin/example_ppl_nncPolyhedra: /usr/local/lib/libmpfr.dylib
bin/example_ppl_nncPolyhedra: /usr/local/lib/libgmp.dylib
bin/example_ppl_nncPolyhedra: /usr/local/lib/libppl.dylib
bin/example_ppl_nncPolyhedra: /usr/local/lib/libppl_c.dylib
bin/example_ppl_nncPolyhedra: examples/CMakeFiles/example_ppl_nncPolyhedra.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/example_ppl_nncPolyhedra"
	cd "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/examples" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example_ppl_nncPolyhedra.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/example_ppl_nncPolyhedra.dir/build: bin/example_ppl_nncPolyhedra
.PHONY : examples/CMakeFiles/example_ppl_nncPolyhedra.dir/build

examples/CMakeFiles/example_ppl_nncPolyhedra.dir/requires: examples/CMakeFiles/example_ppl_nncPolyhedra.dir/example_ppl_nncPolyhedra.cpp.o.requires
.PHONY : examples/CMakeFiles/example_ppl_nncPolyhedra.dir/requires

examples/CMakeFiles/example_ppl_nncPolyhedra.dir/clean:
	cd "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/examples" && $(CMAKE_COMMAND) -P CMakeFiles/example_ppl_nncPolyhedra.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/example_ppl_nncPolyhedra.dir/clean

examples/CMakeFiles/example_ppl_nncPolyhedra.dir/depend:
	cd "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/jongan/Dropbox/HiWi job stuffs/hypro" "/Users/jongan/Dropbox/HiWi job stuffs/hypro/examples" "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build" "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/examples" "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/examples/CMakeFiles/example_ppl_nncPolyhedra.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : examples/CMakeFiles/example_ppl_nncPolyhedra.dir/depend

