# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/HKUST_DDM_MSDM5002_final.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/HKUST_DDM_MSDM5002_final.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HKUST_DDM_MSDM5002_final.dir/flags.make

CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.o: CMakeFiles/HKUST_DDM_MSDM5002_final.dir/flags.make
CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.o: ../src/mcst/hello.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.o -c /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/src/mcst/hello.cpp

CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/src/mcst/hello.cpp > CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.i

CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/src/mcst/hello.cpp -o CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.s

CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.o: CMakeFiles/HKUST_DDM_MSDM5002_final.dir/flags.make
CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.o: ../src/mcst/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.o -c /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/src/mcst/test.cpp

CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/src/mcst/test.cpp > CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.i

CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/src/mcst/test.cpp -o CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.s

CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.o: CMakeFiles/HKUST_DDM_MSDM5002_final.dir/flags.make
CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.o: ../src/mcst/mcst_helper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.o -c /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/src/mcst/mcst_helper.cpp

CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/src/mcst/mcst_helper.cpp > CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.i

CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/src/mcst/mcst_helper.cpp -o CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.s

# Object files for target HKUST_DDM_MSDM5002_final
HKUST_DDM_MSDM5002_final_OBJECTS = \
"CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.o" \
"CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.o" \
"CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.o"

# External object files for target HKUST_DDM_MSDM5002_final
HKUST_DDM_MSDM5002_final_EXTERNAL_OBJECTS =

HKUST_DDM_MSDM5002_final: CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/hello.cpp.o
HKUST_DDM_MSDM5002_final: CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/test.cpp.o
HKUST_DDM_MSDM5002_final: CMakeFiles/HKUST_DDM_MSDM5002_final.dir/src/mcst/mcst_helper.cpp.o
HKUST_DDM_MSDM5002_final: CMakeFiles/HKUST_DDM_MSDM5002_final.dir/build.make
HKUST_DDM_MSDM5002_final: CMakeFiles/HKUST_DDM_MSDM5002_final.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable HKUST_DDM_MSDM5002_final"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HKUST_DDM_MSDM5002_final.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HKUST_DDM_MSDM5002_final.dir/build: HKUST_DDM_MSDM5002_final
.PHONY : CMakeFiles/HKUST_DDM_MSDM5002_final.dir/build

CMakeFiles/HKUST_DDM_MSDM5002_final.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HKUST_DDM_MSDM5002_final.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HKUST_DDM_MSDM5002_final.dir/clean

CMakeFiles/HKUST_DDM_MSDM5002_final.dir/depend:
	cd /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/cmake-build-release /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/cmake-build-release /Users/chenzifeng/Workspace/5002/final_project/HKUST_DDM_MSDM5002_final/cmake-build-release/CMakeFiles/HKUST_DDM_MSDM5002_final.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HKUST_DDM_MSDM5002_final.dir/depend
