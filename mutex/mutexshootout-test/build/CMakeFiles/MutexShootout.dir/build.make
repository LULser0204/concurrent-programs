# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/build

# Include any dependencies generated for this target.
include CMakeFiles/MutexShootout.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MutexShootout.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MutexShootout.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MutexShootout.dir/flags.make

CMakeFiles/MutexShootout.dir/main.cpp.o: CMakeFiles/MutexShootout.dir/flags.make
CMakeFiles/MutexShootout.dir/main.cpp.o: ../main.cpp
CMakeFiles/MutexShootout.dir/main.cpp.o: CMakeFiles/MutexShootout.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MutexShootout.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MutexShootout.dir/main.cpp.o -MF CMakeFiles/MutexShootout.dir/main.cpp.o.d -o CMakeFiles/MutexShootout.dir/main.cpp.o -c /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/main.cpp

CMakeFiles/MutexShootout.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MutexShootout.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/main.cpp > CMakeFiles/MutexShootout.dir/main.cpp.i

CMakeFiles/MutexShootout.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MutexShootout.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/main.cpp -o CMakeFiles/MutexShootout.dir/main.cpp.s

CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.o: CMakeFiles/MutexShootout.dir/flags.make
CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.o: ../MurmurHash3.cpp
CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.o: CMakeFiles/MutexShootout.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.o -MF CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.o.d -o CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.o -c /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/MurmurHash3.cpp

CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/MurmurHash3.cpp > CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.i

CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/MurmurHash3.cpp -o CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.s

CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.o: CMakeFiles/MutexShootout.dir/flags.make
CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.o: ../skinny_mutex/skinny_mutex.c
CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.o: CMakeFiles/MutexShootout.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.o -MF CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.o.d -o CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.o -c /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/skinny_mutex/skinny_mutex.c

CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/skinny_mutex/skinny_mutex.c > CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.i

CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/skinny_mutex/skinny_mutex.c -o CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.s

# Object files for target MutexShootout
MutexShootout_OBJECTS = \
"CMakeFiles/MutexShootout.dir/main.cpp.o" \
"CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.o" \
"CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.o"

# External object files for target MutexShootout
MutexShootout_EXTERNAL_OBJECTS =

MutexShootout: CMakeFiles/MutexShootout.dir/main.cpp.o
MutexShootout: CMakeFiles/MutexShootout.dir/MurmurHash3.cpp.o
MutexShootout: CMakeFiles/MutexShootout.dir/skinny_mutex/skinny_mutex.c.o
MutexShootout: CMakeFiles/MutexShootout.dir/build.make
MutexShootout: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
MutexShootout: CMakeFiles/MutexShootout.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable MutexShootout"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MutexShootout.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MutexShootout.dir/build: MutexShootout
.PHONY : CMakeFiles/MutexShootout.dir/build

CMakeFiles/MutexShootout.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MutexShootout.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MutexShootout.dir/clean

CMakeFiles/MutexShootout.dir/depend:
	cd /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/build /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/build /home/vision/linux2024/todo_git/concurrent-programs/mutex/mutexshootout-test/build/CMakeFiles/MutexShootout.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MutexShootout.dir/depend
