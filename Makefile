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
CMAKE_SOURCE_DIR = /home/rubuntu/Documents/MIfImage/Projetim/Delaunay

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rubuntu/Documents/MIfImage/Projetim/Delaunay

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
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rubuntu/Documents/MIfImage/Projetim/Delaunay/CMakeFiles /home/rubuntu/Documents/MIfImage/Projetim/Delaunay//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rubuntu/Documents/MIfImage/Projetim/Delaunay/CMakeFiles 0
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
# Target rules for targets named test

# Build rule for target.
test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test
.PHONY : test

# fast build rule for target.
test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/build
.PHONY : test/fast

includes/Imgui/backends/imgui_impl_glfw.o: includes/Imgui/backends/imgui_impl_glfw.cpp.o
.PHONY : includes/Imgui/backends/imgui_impl_glfw.o

# target to build an object file
includes/Imgui/backends/imgui_impl_glfw.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/backends/imgui_impl_glfw.cpp.o
.PHONY : includes/Imgui/backends/imgui_impl_glfw.cpp.o

includes/Imgui/backends/imgui_impl_glfw.i: includes/Imgui/backends/imgui_impl_glfw.cpp.i
.PHONY : includes/Imgui/backends/imgui_impl_glfw.i

# target to preprocess a source file
includes/Imgui/backends/imgui_impl_glfw.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/backends/imgui_impl_glfw.cpp.i
.PHONY : includes/Imgui/backends/imgui_impl_glfw.cpp.i

includes/Imgui/backends/imgui_impl_glfw.s: includes/Imgui/backends/imgui_impl_glfw.cpp.s
.PHONY : includes/Imgui/backends/imgui_impl_glfw.s

# target to generate assembly for a file
includes/Imgui/backends/imgui_impl_glfw.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/backends/imgui_impl_glfw.cpp.s
.PHONY : includes/Imgui/backends/imgui_impl_glfw.cpp.s

includes/Imgui/backends/imgui_impl_opengl3.o: includes/Imgui/backends/imgui_impl_opengl3.cpp.o
.PHONY : includes/Imgui/backends/imgui_impl_opengl3.o

# target to build an object file
includes/Imgui/backends/imgui_impl_opengl3.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/backends/imgui_impl_opengl3.cpp.o
.PHONY : includes/Imgui/backends/imgui_impl_opengl3.cpp.o

includes/Imgui/backends/imgui_impl_opengl3.i: includes/Imgui/backends/imgui_impl_opengl3.cpp.i
.PHONY : includes/Imgui/backends/imgui_impl_opengl3.i

# target to preprocess a source file
includes/Imgui/backends/imgui_impl_opengl3.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/backends/imgui_impl_opengl3.cpp.i
.PHONY : includes/Imgui/backends/imgui_impl_opengl3.cpp.i

includes/Imgui/backends/imgui_impl_opengl3.s: includes/Imgui/backends/imgui_impl_opengl3.cpp.s
.PHONY : includes/Imgui/backends/imgui_impl_opengl3.s

# target to generate assembly for a file
includes/Imgui/backends/imgui_impl_opengl3.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/backends/imgui_impl_opengl3.cpp.s
.PHONY : includes/Imgui/backends/imgui_impl_opengl3.cpp.s

includes/Imgui/imgui.o: includes/Imgui/imgui.cpp.o
.PHONY : includes/Imgui/imgui.o

# target to build an object file
includes/Imgui/imgui.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui.cpp.o
.PHONY : includes/Imgui/imgui.cpp.o

includes/Imgui/imgui.i: includes/Imgui/imgui.cpp.i
.PHONY : includes/Imgui/imgui.i

# target to preprocess a source file
includes/Imgui/imgui.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui.cpp.i
.PHONY : includes/Imgui/imgui.cpp.i

includes/Imgui/imgui.s: includes/Imgui/imgui.cpp.s
.PHONY : includes/Imgui/imgui.s

# target to generate assembly for a file
includes/Imgui/imgui.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui.cpp.s
.PHONY : includes/Imgui/imgui.cpp.s

includes/Imgui/imgui_demo.o: includes/Imgui/imgui_demo.cpp.o
.PHONY : includes/Imgui/imgui_demo.o

# target to build an object file
includes/Imgui/imgui_demo.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_demo.cpp.o
.PHONY : includes/Imgui/imgui_demo.cpp.o

includes/Imgui/imgui_demo.i: includes/Imgui/imgui_demo.cpp.i
.PHONY : includes/Imgui/imgui_demo.i

# target to preprocess a source file
includes/Imgui/imgui_demo.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_demo.cpp.i
.PHONY : includes/Imgui/imgui_demo.cpp.i

includes/Imgui/imgui_demo.s: includes/Imgui/imgui_demo.cpp.s
.PHONY : includes/Imgui/imgui_demo.s

# target to generate assembly for a file
includes/Imgui/imgui_demo.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_demo.cpp.s
.PHONY : includes/Imgui/imgui_demo.cpp.s

includes/Imgui/imgui_draw.o: includes/Imgui/imgui_draw.cpp.o
.PHONY : includes/Imgui/imgui_draw.o

# target to build an object file
includes/Imgui/imgui_draw.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_draw.cpp.o
.PHONY : includes/Imgui/imgui_draw.cpp.o

includes/Imgui/imgui_draw.i: includes/Imgui/imgui_draw.cpp.i
.PHONY : includes/Imgui/imgui_draw.i

# target to preprocess a source file
includes/Imgui/imgui_draw.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_draw.cpp.i
.PHONY : includes/Imgui/imgui_draw.cpp.i

includes/Imgui/imgui_draw.s: includes/Imgui/imgui_draw.cpp.s
.PHONY : includes/Imgui/imgui_draw.s

# target to generate assembly for a file
includes/Imgui/imgui_draw.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_draw.cpp.s
.PHONY : includes/Imgui/imgui_draw.cpp.s

includes/Imgui/imgui_tables.o: includes/Imgui/imgui_tables.cpp.o
.PHONY : includes/Imgui/imgui_tables.o

# target to build an object file
includes/Imgui/imgui_tables.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_tables.cpp.o
.PHONY : includes/Imgui/imgui_tables.cpp.o

includes/Imgui/imgui_tables.i: includes/Imgui/imgui_tables.cpp.i
.PHONY : includes/Imgui/imgui_tables.i

# target to preprocess a source file
includes/Imgui/imgui_tables.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_tables.cpp.i
.PHONY : includes/Imgui/imgui_tables.cpp.i

includes/Imgui/imgui_tables.s: includes/Imgui/imgui_tables.cpp.s
.PHONY : includes/Imgui/imgui_tables.s

# target to generate assembly for a file
includes/Imgui/imgui_tables.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_tables.cpp.s
.PHONY : includes/Imgui/imgui_tables.cpp.s

includes/Imgui/imgui_widgets.o: includes/Imgui/imgui_widgets.cpp.o
.PHONY : includes/Imgui/imgui_widgets.o

# target to build an object file
includes/Imgui/imgui_widgets.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_widgets.cpp.o
.PHONY : includes/Imgui/imgui_widgets.cpp.o

includes/Imgui/imgui_widgets.i: includes/Imgui/imgui_widgets.cpp.i
.PHONY : includes/Imgui/imgui_widgets.i

# target to preprocess a source file
includes/Imgui/imgui_widgets.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_widgets.cpp.i
.PHONY : includes/Imgui/imgui_widgets.cpp.i

includes/Imgui/imgui_widgets.s: includes/Imgui/imgui_widgets.cpp.s
.PHONY : includes/Imgui/imgui_widgets.s

# target to generate assembly for a file
includes/Imgui/imgui_widgets.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/includes/Imgui/imgui_widgets.cpp.s
.PHONY : includes/Imgui/imgui_widgets.cpp.s

src/Core/ImgApp.o: src/Core/ImgApp.cpp.o
.PHONY : src/Core/ImgApp.o

# target to build an object file
src/Core/ImgApp.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Core/ImgApp.cpp.o
.PHONY : src/Core/ImgApp.cpp.o

src/Core/ImgApp.i: src/Core/ImgApp.cpp.i
.PHONY : src/Core/ImgApp.i

# target to preprocess a source file
src/Core/ImgApp.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Core/ImgApp.cpp.i
.PHONY : src/Core/ImgApp.cpp.i

src/Core/ImgApp.s: src/Core/ImgApp.cpp.s
.PHONY : src/Core/ImgApp.s

# target to generate assembly for a file
src/Core/ImgApp.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Core/ImgApp.cpp.s
.PHONY : src/Core/ImgApp.cpp.s

src/ImgEditorEngine/ImgEditorEngine.o: src/ImgEditorEngine/ImgEditorEngine.cpp.o
.PHONY : src/ImgEditorEngine/ImgEditorEngine.o

# target to build an object file
src/ImgEditorEngine/ImgEditorEngine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/ImgEditorEngine/ImgEditorEngine.cpp.o
.PHONY : src/ImgEditorEngine/ImgEditorEngine.cpp.o

src/ImgEditorEngine/ImgEditorEngine.i: src/ImgEditorEngine/ImgEditorEngine.cpp.i
.PHONY : src/ImgEditorEngine/ImgEditorEngine.i

# target to preprocess a source file
src/ImgEditorEngine/ImgEditorEngine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/ImgEditorEngine/ImgEditorEngine.cpp.i
.PHONY : src/ImgEditorEngine/ImgEditorEngine.cpp.i

src/ImgEditorEngine/ImgEditorEngine.s: src/ImgEditorEngine/ImgEditorEngine.cpp.s
.PHONY : src/ImgEditorEngine/ImgEditorEngine.s

# target to generate assembly for a file
src/ImgEditorEngine/ImgEditorEngine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/ImgEditorEngine/ImgEditorEngine.cpp.s
.PHONY : src/ImgEditorEngine/ImgEditorEngine.cpp.s

src/Models/Canvas.o: src/Models/Canvas.cpp.o
.PHONY : src/Models/Canvas.o

# target to build an object file
src/Models/Canvas.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Models/Canvas.cpp.o
.PHONY : src/Models/Canvas.cpp.o

src/Models/Canvas.i: src/Models/Canvas.cpp.i
.PHONY : src/Models/Canvas.i

# target to preprocess a source file
src/Models/Canvas.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Models/Canvas.cpp.i
.PHONY : src/Models/Canvas.cpp.i

src/Models/Canvas.s: src/Models/Canvas.cpp.s
.PHONY : src/Models/Canvas.s

# target to generate assembly for a file
src/Models/Canvas.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Models/Canvas.cpp.s
.PHONY : src/Models/Canvas.cpp.s

src/Openglutils/Buffers.o: src/Openglutils/Buffers.cpp.o
.PHONY : src/Openglutils/Buffers.o

# target to build an object file
src/Openglutils/Buffers.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Openglutils/Buffers.cpp.o
.PHONY : src/Openglutils/Buffers.cpp.o

src/Openglutils/Buffers.i: src/Openglutils/Buffers.cpp.i
.PHONY : src/Openglutils/Buffers.i

# target to preprocess a source file
src/Openglutils/Buffers.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Openglutils/Buffers.cpp.i
.PHONY : src/Openglutils/Buffers.cpp.i

src/Openglutils/Buffers.s: src/Openglutils/Buffers.cpp.s
.PHONY : src/Openglutils/Buffers.s

# target to generate assembly for a file
src/Openglutils/Buffers.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Openglutils/Buffers.cpp.s
.PHONY : src/Openglutils/Buffers.cpp.s

src/Openglutils/Program.o: src/Openglutils/Program.cpp.o
.PHONY : src/Openglutils/Program.o

# target to build an object file
src/Openglutils/Program.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Openglutils/Program.cpp.o
.PHONY : src/Openglutils/Program.cpp.o

src/Openglutils/Program.i: src/Openglutils/Program.cpp.i
.PHONY : src/Openglutils/Program.i

# target to preprocess a source file
src/Openglutils/Program.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Openglutils/Program.cpp.i
.PHONY : src/Openglutils/Program.cpp.i

src/Openglutils/Program.s: src/Openglutils/Program.cpp.s
.PHONY : src/Openglutils/Program.s

# target to generate assembly for a file
src/Openglutils/Program.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Openglutils/Program.cpp.s
.PHONY : src/Openglutils/Program.cpp.s

src/Openglutils/Texture.o: src/Openglutils/Texture.cpp.o
.PHONY : src/Openglutils/Texture.o

# target to build an object file
src/Openglutils/Texture.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Openglutils/Texture.cpp.o
.PHONY : src/Openglutils/Texture.cpp.o

src/Openglutils/Texture.i: src/Openglutils/Texture.cpp.i
.PHONY : src/Openglutils/Texture.i

# target to preprocess a source file
src/Openglutils/Texture.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Openglutils/Texture.cpp.i
.PHONY : src/Openglutils/Texture.cpp.i

src/Openglutils/Texture.s: src/Openglutils/Texture.cpp.s
.PHONY : src/Openglutils/Texture.s

# target to generate assembly for a file
src/Openglutils/Texture.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Openglutils/Texture.cpp.s
.PHONY : src/Openglutils/Texture.cpp.s

src/RenderContext/ImGuiAppContext.o: src/RenderContext/ImGuiAppContext.cpp.o
.PHONY : src/RenderContext/ImGuiAppContext.o

# target to build an object file
src/RenderContext/ImGuiAppContext.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/RenderContext/ImGuiAppContext.cpp.o
.PHONY : src/RenderContext/ImGuiAppContext.cpp.o

src/RenderContext/ImGuiAppContext.i: src/RenderContext/ImGuiAppContext.cpp.i
.PHONY : src/RenderContext/ImGuiAppContext.i

# target to preprocess a source file
src/RenderContext/ImGuiAppContext.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/RenderContext/ImGuiAppContext.cpp.i
.PHONY : src/RenderContext/ImGuiAppContext.cpp.i

src/RenderContext/ImGuiAppContext.s: src/RenderContext/ImGuiAppContext.cpp.s
.PHONY : src/RenderContext/ImGuiAppContext.s

# target to generate assembly for a file
src/RenderContext/ImGuiAppContext.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/RenderContext/ImGuiAppContext.cpp.s
.PHONY : src/RenderContext/ImGuiAppContext.cpp.s

src/RenderContext/OpenGLContext.o: src/RenderContext/OpenGLContext.cpp.o
.PHONY : src/RenderContext/OpenGLContext.o

# target to build an object file
src/RenderContext/OpenGLContext.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/RenderContext/OpenGLContext.cpp.o
.PHONY : src/RenderContext/OpenGLContext.cpp.o

src/RenderContext/OpenGLContext.i: src/RenderContext/OpenGLContext.cpp.i
.PHONY : src/RenderContext/OpenGLContext.i

# target to preprocess a source file
src/RenderContext/OpenGLContext.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/RenderContext/OpenGLContext.cpp.i
.PHONY : src/RenderContext/OpenGLContext.cpp.i

src/RenderContext/OpenGLContext.s: src/RenderContext/OpenGLContext.cpp.s
.PHONY : src/RenderContext/OpenGLContext.s

# target to generate assembly for a file
src/RenderContext/OpenGLContext.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/RenderContext/OpenGLContext.cpp.s
.PHONY : src/RenderContext/OpenGLContext.cpp.s

src/TP/Mesh.o: src/TP/Mesh.cpp.o
.PHONY : src/TP/Mesh.o

# target to build an object file
src/TP/Mesh.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/Mesh.cpp.o
.PHONY : src/TP/Mesh.cpp.o

src/TP/Mesh.i: src/TP/Mesh.cpp.i
.PHONY : src/TP/Mesh.i

# target to preprocess a source file
src/TP/Mesh.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/Mesh.cpp.i
.PHONY : src/TP/Mesh.cpp.i

src/TP/Mesh.s: src/TP/Mesh.cpp.s
.PHONY : src/TP/Mesh.s

# target to generate assembly for a file
src/TP/Mesh.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/Mesh.cpp.s
.PHONY : src/TP/Mesh.cpp.s

src/TP/MeshHelper.o: src/TP/MeshHelper.cpp.o
.PHONY : src/TP/MeshHelper.o

# target to build an object file
src/TP/MeshHelper.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/MeshHelper.cpp.o
.PHONY : src/TP/MeshHelper.cpp.o

src/TP/MeshHelper.i: src/TP/MeshHelper.cpp.i
.PHONY : src/TP/MeshHelper.i

# target to preprocess a source file
src/TP/MeshHelper.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/MeshHelper.cpp.i
.PHONY : src/TP/MeshHelper.cpp.i

src/TP/MeshHelper.s: src/TP/MeshHelper.cpp.s
.PHONY : src/TP/MeshHelper.s

# target to generate assembly for a file
src/TP/MeshHelper.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/MeshHelper.cpp.s
.PHONY : src/TP/MeshHelper.cpp.s

src/TP/Mesh_IO.o: src/TP/Mesh_IO.cpp.o
.PHONY : src/TP/Mesh_IO.o

# target to build an object file
src/TP/Mesh_IO.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/Mesh_IO.cpp.o
.PHONY : src/TP/Mesh_IO.cpp.o

src/TP/Mesh_IO.i: src/TP/Mesh_IO.cpp.i
.PHONY : src/TP/Mesh_IO.i

# target to preprocess a source file
src/TP/Mesh_IO.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/Mesh_IO.cpp.i
.PHONY : src/TP/Mesh_IO.cpp.i

src/TP/Mesh_IO.s: src/TP/Mesh_IO.cpp.s
.PHONY : src/TP/Mesh_IO.s

# target to generate assembly for a file
src/TP/Mesh_IO.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/Mesh_IO.cpp.s
.PHONY : src/TP/Mesh_IO.cpp.s

src/TP/Vertices.o: src/TP/Vertices.cpp.o
.PHONY : src/TP/Vertices.o

# target to build an object file
src/TP/Vertices.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/Vertices.cpp.o
.PHONY : src/TP/Vertices.cpp.o

src/TP/Vertices.i: src/TP/Vertices.cpp.i
.PHONY : src/TP/Vertices.i

# target to preprocess a source file
src/TP/Vertices.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/Vertices.cpp.i
.PHONY : src/TP/Vertices.cpp.i

src/TP/Vertices.s: src/TP/Vertices.cpp.s
.PHONY : src/TP/Vertices.s

# target to generate assembly for a file
src/TP/Vertices.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/TP/Vertices.cpp.s
.PHONY : src/TP/Vertices.cpp.s

src/UiWindows/Dockspace.o: src/UiWindows/Dockspace.cpp.o
.PHONY : src/UiWindows/Dockspace.o

# target to build an object file
src/UiWindows/Dockspace.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/Dockspace.cpp.o
.PHONY : src/UiWindows/Dockspace.cpp.o

src/UiWindows/Dockspace.i: src/UiWindows/Dockspace.cpp.i
.PHONY : src/UiWindows/Dockspace.i

# target to preprocess a source file
src/UiWindows/Dockspace.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/Dockspace.cpp.i
.PHONY : src/UiWindows/Dockspace.cpp.i

src/UiWindows/Dockspace.s: src/UiWindows/Dockspace.cpp.s
.PHONY : src/UiWindows/Dockspace.s

# target to generate assembly for a file
src/UiWindows/Dockspace.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/Dockspace.cpp.s
.PHONY : src/UiWindows/Dockspace.cpp.s

src/UiWindows/GlobalStates.o: src/UiWindows/GlobalStates.cpp.o
.PHONY : src/UiWindows/GlobalStates.o

# target to build an object file
src/UiWindows/GlobalStates.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/GlobalStates.cpp.o
.PHONY : src/UiWindows/GlobalStates.cpp.o

src/UiWindows/GlobalStates.i: src/UiWindows/GlobalStates.cpp.i
.PHONY : src/UiWindows/GlobalStates.i

# target to preprocess a source file
src/UiWindows/GlobalStates.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/GlobalStates.cpp.i
.PHONY : src/UiWindows/GlobalStates.cpp.i

src/UiWindows/GlobalStates.s: src/UiWindows/GlobalStates.cpp.s
.PHONY : src/UiWindows/GlobalStates.s

# target to generate assembly for a file
src/UiWindows/GlobalStates.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/GlobalStates.cpp.s
.PHONY : src/UiWindows/GlobalStates.cpp.s

src/UiWindows/ImgEditor.o: src/UiWindows/ImgEditor.cpp.o
.PHONY : src/UiWindows/ImgEditor.o

# target to build an object file
src/UiWindows/ImgEditor.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/ImgEditor.cpp.o
.PHONY : src/UiWindows/ImgEditor.cpp.o

src/UiWindows/ImgEditor.i: src/UiWindows/ImgEditor.cpp.i
.PHONY : src/UiWindows/ImgEditor.i

# target to preprocess a source file
src/UiWindows/ImgEditor.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/ImgEditor.cpp.i
.PHONY : src/UiWindows/ImgEditor.cpp.i

src/UiWindows/ImgEditor.s: src/UiWindows/ImgEditor.cpp.s
.PHONY : src/UiWindows/ImgEditor.s

# target to generate assembly for a file
src/UiWindows/ImgEditor.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/ImgEditor.cpp.s
.PHONY : src/UiWindows/ImgEditor.cpp.s

src/UiWindows/UiCompUtils.o: src/UiWindows/UiCompUtils.cpp.o
.PHONY : src/UiWindows/UiCompUtils.o

# target to build an object file
src/UiWindows/UiCompUtils.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/UiCompUtils.cpp.o
.PHONY : src/UiWindows/UiCompUtils.cpp.o

src/UiWindows/UiCompUtils.i: src/UiWindows/UiCompUtils.cpp.i
.PHONY : src/UiWindows/UiCompUtils.i

# target to preprocess a source file
src/UiWindows/UiCompUtils.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/UiCompUtils.cpp.i
.PHONY : src/UiWindows/UiCompUtils.cpp.i

src/UiWindows/UiCompUtils.s: src/UiWindows/UiCompUtils.cpp.s
.PHONY : src/UiWindows/UiCompUtils.s

# target to generate assembly for a file
src/UiWindows/UiCompUtils.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/UiWindows/UiCompUtils.cpp.s
.PHONY : src/UiWindows/UiCompUtils.cpp.s

src/Utils/Helper.o: src/Utils/Helper.cpp.o
.PHONY : src/Utils/Helper.o

# target to build an object file
src/Utils/Helper.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Utils/Helper.cpp.o
.PHONY : src/Utils/Helper.cpp.o

src/Utils/Helper.i: src/Utils/Helper.cpp.i
.PHONY : src/Utils/Helper.i

# target to preprocess a source file
src/Utils/Helper.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Utils/Helper.cpp.i
.PHONY : src/Utils/Helper.cpp.i

src/Utils/Helper.s: src/Utils/Helper.cpp.s
.PHONY : src/Utils/Helper.s

# target to generate assembly for a file
src/Utils/Helper.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Utils/Helper.cpp.s
.PHONY : src/Utils/Helper.cpp.s

src/Utils/Imloader.o: src/Utils/Imloader.cpp.o
.PHONY : src/Utils/Imloader.o

# target to build an object file
src/Utils/Imloader.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Utils/Imloader.cpp.o
.PHONY : src/Utils/Imloader.cpp.o

src/Utils/Imloader.i: src/Utils/Imloader.cpp.i
.PHONY : src/Utils/Imloader.i

# target to preprocess a source file
src/Utils/Imloader.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Utils/Imloader.cpp.i
.PHONY : src/Utils/Imloader.cpp.i

src/Utils/Imloader.s: src/Utils/Imloader.cpp.s
.PHONY : src/Utils/Imloader.s

# target to generate assembly for a file
src/Utils/Imloader.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Utils/Imloader.cpp.s
.PHONY : src/Utils/Imloader.cpp.s

src/Utils/Mat.o: src/Utils/Mat.cpp.o
.PHONY : src/Utils/Mat.o

# target to build an object file
src/Utils/Mat.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Utils/Mat.cpp.o
.PHONY : src/Utils/Mat.cpp.o

src/Utils/Mat.i: src/Utils/Mat.cpp.i
.PHONY : src/Utils/Mat.i

# target to preprocess a source file
src/Utils/Mat.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Utils/Mat.cpp.i
.PHONY : src/Utils/Mat.cpp.i

src/Utils/Mat.s: src/Utils/Mat.cpp.s
.PHONY : src/Utils/Mat.s

# target to generate assembly for a file
src/Utils/Mat.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Utils/Mat.cpp.s
.PHONY : src/Utils/Mat.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... test"
	@echo "... includes/Imgui/backends/imgui_impl_glfw.o"
	@echo "... includes/Imgui/backends/imgui_impl_glfw.i"
	@echo "... includes/Imgui/backends/imgui_impl_glfw.s"
	@echo "... includes/Imgui/backends/imgui_impl_opengl3.o"
	@echo "... includes/Imgui/backends/imgui_impl_opengl3.i"
	@echo "... includes/Imgui/backends/imgui_impl_opengl3.s"
	@echo "... includes/Imgui/imgui.o"
	@echo "... includes/Imgui/imgui.i"
	@echo "... includes/Imgui/imgui.s"
	@echo "... includes/Imgui/imgui_demo.o"
	@echo "... includes/Imgui/imgui_demo.i"
	@echo "... includes/Imgui/imgui_demo.s"
	@echo "... includes/Imgui/imgui_draw.o"
	@echo "... includes/Imgui/imgui_draw.i"
	@echo "... includes/Imgui/imgui_draw.s"
	@echo "... includes/Imgui/imgui_tables.o"
	@echo "... includes/Imgui/imgui_tables.i"
	@echo "... includes/Imgui/imgui_tables.s"
	@echo "... includes/Imgui/imgui_widgets.o"
	@echo "... includes/Imgui/imgui_widgets.i"
	@echo "... includes/Imgui/imgui_widgets.s"
	@echo "... src/Core/ImgApp.o"
	@echo "... src/Core/ImgApp.i"
	@echo "... src/Core/ImgApp.s"
	@echo "... src/ImgEditorEngine/ImgEditorEngine.o"
	@echo "... src/ImgEditorEngine/ImgEditorEngine.i"
	@echo "... src/ImgEditorEngine/ImgEditorEngine.s"
	@echo "... src/Models/Canvas.o"
	@echo "... src/Models/Canvas.i"
	@echo "... src/Models/Canvas.s"
	@echo "... src/Openglutils/Buffers.o"
	@echo "... src/Openglutils/Buffers.i"
	@echo "... src/Openglutils/Buffers.s"
	@echo "... src/Openglutils/Program.o"
	@echo "... src/Openglutils/Program.i"
	@echo "... src/Openglutils/Program.s"
	@echo "... src/Openglutils/Texture.o"
	@echo "... src/Openglutils/Texture.i"
	@echo "... src/Openglutils/Texture.s"
	@echo "... src/RenderContext/ImGuiAppContext.o"
	@echo "... src/RenderContext/ImGuiAppContext.i"
	@echo "... src/RenderContext/ImGuiAppContext.s"
	@echo "... src/RenderContext/OpenGLContext.o"
	@echo "... src/RenderContext/OpenGLContext.i"
	@echo "... src/RenderContext/OpenGLContext.s"
	@echo "... src/TP/Mesh.o"
	@echo "... src/TP/Mesh.i"
	@echo "... src/TP/Mesh.s"
	@echo "... src/TP/MeshHelper.o"
	@echo "... src/TP/MeshHelper.i"
	@echo "... src/TP/MeshHelper.s"
	@echo "... src/TP/Mesh_IO.o"
	@echo "... src/TP/Mesh_IO.i"
	@echo "... src/TP/Mesh_IO.s"
	@echo "... src/TP/Vertices.o"
	@echo "... src/TP/Vertices.i"
	@echo "... src/TP/Vertices.s"
	@echo "... src/UiWindows/Dockspace.o"
	@echo "... src/UiWindows/Dockspace.i"
	@echo "... src/UiWindows/Dockspace.s"
	@echo "... src/UiWindows/GlobalStates.o"
	@echo "... src/UiWindows/GlobalStates.i"
	@echo "... src/UiWindows/GlobalStates.s"
	@echo "... src/UiWindows/ImgEditor.o"
	@echo "... src/UiWindows/ImgEditor.i"
	@echo "... src/UiWindows/ImgEditor.s"
	@echo "... src/UiWindows/UiCompUtils.o"
	@echo "... src/UiWindows/UiCompUtils.i"
	@echo "... src/UiWindows/UiCompUtils.s"
	@echo "... src/Utils/Helper.o"
	@echo "... src/Utils/Helper.i"
	@echo "... src/Utils/Helper.s"
	@echo "... src/Utils/Imloader.o"
	@echo "... src/Utils/Imloader.i"
	@echo "... src/Utils/Imloader.s"
	@echo "... src/Utils/Mat.o"
	@echo "... src/Utils/Mat.i"
	@echo "... src/Utils/Mat.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
