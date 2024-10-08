# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /home/thomas/Projects/clox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomas/Projects/clox

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/thomas/Projects/clox/CMakeFiles /home/thomas/Projects/clox//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/thomas/Projects/clox/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named clox

# Build rule for target.
clox: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clox
.PHONY : clox

# fast build rule for target.
clox/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/build
.PHONY : clox/fast

src/chunk.o: src/chunk.cpp.o
.PHONY : src/chunk.o

# target to build an object file
src/chunk.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/chunk.cpp.o
.PHONY : src/chunk.cpp.o

src/chunk.i: src/chunk.cpp.i
.PHONY : src/chunk.i

# target to preprocess a source file
src/chunk.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/chunk.cpp.i
.PHONY : src/chunk.cpp.i

src/chunk.s: src/chunk.cpp.s
.PHONY : src/chunk.s

# target to generate assembly for a file
src/chunk.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/chunk.cpp.s
.PHONY : src/chunk.cpp.s

src/compiler.o: src/compiler.cpp.o
.PHONY : src/compiler.o

# target to build an object file
src/compiler.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/compiler.cpp.o
.PHONY : src/compiler.cpp.o

src/compiler.i: src/compiler.cpp.i
.PHONY : src/compiler.i

# target to preprocess a source file
src/compiler.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/compiler.cpp.i
.PHONY : src/compiler.cpp.i

src/compiler.s: src/compiler.cpp.s
.PHONY : src/compiler.s

# target to generate assembly for a file
src/compiler.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/compiler.cpp.s
.PHONY : src/compiler.cpp.s

src/debug.o: src/debug.cpp.o
.PHONY : src/debug.o

# target to build an object file
src/debug.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/debug.cpp.o
.PHONY : src/debug.cpp.o

src/debug.i: src/debug.cpp.i
.PHONY : src/debug.i

# target to preprocess a source file
src/debug.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/debug.cpp.i
.PHONY : src/debug.cpp.i

src/debug.s: src/debug.cpp.s
.PHONY : src/debug.s

# target to generate assembly for a file
src/debug.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/debug.cpp.s
.PHONY : src/debug.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/scanner.o: src/scanner.cpp.o
.PHONY : src/scanner.o

# target to build an object file
src/scanner.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/scanner.cpp.o
.PHONY : src/scanner.cpp.o

src/scanner.i: src/scanner.cpp.i
.PHONY : src/scanner.i

# target to preprocess a source file
src/scanner.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/scanner.cpp.i
.PHONY : src/scanner.cpp.i

src/scanner.s: src/scanner.cpp.s
.PHONY : src/scanner.s

# target to generate assembly for a file
src/scanner.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/scanner.cpp.s
.PHONY : src/scanner.cpp.s

src/value.o: src/value.cpp.o
.PHONY : src/value.o

# target to build an object file
src/value.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/value.cpp.o
.PHONY : src/value.cpp.o

src/value.i: src/value.cpp.i
.PHONY : src/value.i

# target to preprocess a source file
src/value.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/value.cpp.i
.PHONY : src/value.cpp.i

src/value.s: src/value.cpp.s
.PHONY : src/value.s

# target to generate assembly for a file
src/value.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/value.cpp.s
.PHONY : src/value.cpp.s

src/vm.o: src/vm.cpp.o
.PHONY : src/vm.o

# target to build an object file
src/vm.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/vm.cpp.o
.PHONY : src/vm.cpp.o

src/vm.i: src/vm.cpp.i
.PHONY : src/vm.i

# target to preprocess a source file
src/vm.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/vm.cpp.i
.PHONY : src/vm.cpp.i

src/vm.s: src/vm.cpp.s
.PHONY : src/vm.s

# target to generate assembly for a file
src/vm.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/clox.dir/build.make CMakeFiles/clox.dir/src/vm.cpp.s
.PHONY : src/vm.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... clox"
	@echo "... src/chunk.o"
	@echo "... src/chunk.i"
	@echo "... src/chunk.s"
	@echo "... src/compiler.o"
	@echo "... src/compiler.i"
	@echo "... src/compiler.s"
	@echo "... src/debug.o"
	@echo "... src/debug.i"
	@echo "... src/debug.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/scanner.o"
	@echo "... src/scanner.i"
	@echo "... src/scanner.s"
	@echo "... src/value.o"
	@echo "... src/value.i"
	@echo "... src/value.s"
	@echo "... src/vm.o"
	@echo "... src/vm.i"
	@echo "... src/vm.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

