# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = "/Users/emilienlemaire/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/emilienlemaire/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Volumes/LaCie/CLionProjects/42ngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Volumes/LaCie/CLionProjects/42ngine/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/42ngine_unity.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/42ngine_unity.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/42ngine_unity.dir/flags.make

cotire/42ngine_CXX_unity.cxx: 42ngine_CXX_cotire.cmake
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Volumes/LaCie/CLionProjects/42ngine/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating CXX unity source cotire/42ngine_CXX_unity.cxx"
	cd /Volumes/LaCie/CLionProjects/42ngine && "/Users/emilienlemaire/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/CLion.app/Contents/bin/cmake/mac/bin/cmake" -DCOTIRE_BUILD_TYPE:STRING=Release -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /Volumes/LaCie/CLionProjects/42ngine/cmake/modules/cotire.cmake unity /Volumes/LaCie/CLionProjects/42ngine/cmake-build-release/42ngine_CXX_cotire.cmake /Volumes/LaCie/CLionProjects/42ngine/cmake-build-release/cotire/42ngine_CXX_unity.cxx

CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.o: CMakeFiles/42ngine_unity.dir/flags.make
CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.o: cotire/42ngine_CXX_unity.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/LaCie/CLionProjects/42ngine/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.o -c /Volumes/LaCie/CLionProjects/42ngine/cmake-build-release/cotire/42ngine_CXX_unity.cxx

CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Volumes/LaCie/CLionProjects/42ngine/cmake-build-release/cotire/42ngine_CXX_unity.cxx > CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.i

CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Volumes/LaCie/CLionProjects/42ngine/cmake-build-release/cotire/42ngine_CXX_unity.cxx -o CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.s

# Object files for target 42ngine_unity
42ngine_unity_OBJECTS = \
"CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.o"

# External object files for target 42ngine_unity
42ngine_unity_EXTERNAL_OBJECTS =

lib42ngine.a: CMakeFiles/42ngine_unity.dir/cotire/42ngine_CXX_unity.cxx.o
lib42ngine.a: CMakeFiles/42ngine_unity.dir/build.make
lib42ngine.a: CMakeFiles/42ngine_unity.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Volumes/LaCie/CLionProjects/42ngine/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library lib42ngine.a"
	$(CMAKE_COMMAND) -P CMakeFiles/42ngine_unity.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/42ngine_unity.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/42ngine_unity.dir/build: lib42ngine.a

.PHONY : CMakeFiles/42ngine_unity.dir/build

CMakeFiles/42ngine_unity.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/42ngine_unity.dir/cmake_clean.cmake
.PHONY : CMakeFiles/42ngine_unity.dir/clean

CMakeFiles/42ngine_unity.dir/depend: cotire/42ngine_CXX_unity.cxx
	cd /Volumes/LaCie/CLionProjects/42ngine/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Volumes/LaCie/CLionProjects/42ngine /Volumes/LaCie/CLionProjects/42ngine /Volumes/LaCie/CLionProjects/42ngine/cmake-build-release /Volumes/LaCie/CLionProjects/42ngine/cmake-build-release /Volumes/LaCie/CLionProjects/42ngine/cmake-build-release/CMakeFiles/42ngine_unity.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/42ngine_unity.dir/depend

