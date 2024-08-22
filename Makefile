
#   Makefile

#   **************************************************************************
#   This makefile:
#   1.  [make build] Builds all object files and places them into an object
#       directory
#   2.  [make link] Links object files to create main executable
#   3.  [make run] Runs the main executable
#   4.  [make clean] Clears all files and directories created

#   **************************************************************************
#   Compiler variables
CXX = g++
CXXFLAGS =  -std=c++17 -Wall -Wextra -pedantic -Wshadow -Wconversion \
            -Werror=vla -Werror=old-style-cast -Werror=return-type \
            -Werror=missing-declarations -fsanitize=address -g3

#   **************************************************************************
#   User variables
_EXEC_NAME = RetroGrade
_OBJS_DIR_NAME = obj
_SRC_DIR_NAME = src

#   **************************************************************************
#   File variables
SRCS := $(shell find $(_SRC_DIR_NAME) -name '*.cpp')
OBJS := $(addprefix \
    $(_OBJS_DIR_NAME)/, $(notdir $(patsubst %.cpp, %.o, $(SRCS))) \
)
DEPS := $(patsubst %.o, %.d, $(OBJS))

#   **************************************************************************
#   Recipes
-include $(DEPS)

run: link
	@echo ["Project start: $(_EXEC_NAME)"]
	@./$(_EXEC_NAME)

link: build
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(_EXEC_NAME)
	@echo ["Project linked: $(_EXEC_NAME)"]

build: build_dir $(OBJS)
	@echo ["Build finished"]

build_dir:
	@mkdir -p $(_OBJS_DIR_NAME)
	@echo ["Object directory created"]

clean:
	@rm -f $(_OBJS_DIR_NAME)/*
	@echo ["Object and dependency files deleted"]
	@rmdir -p $(_OBJS_DIR_NAME)
	@echo ["Object directory deleted"]
	@rm -f $(_EXEC_NAME)
	@echo ["Project executable deleted: $(_EXEC_NAME)"]
	@echo ["Project cleaned"]

$(_OBJS_DIR_NAME)/%.o: $(_SRC_DIR_NAME)/%.cpp Makefile
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -MD -MP
	@echo "[Files created: $*.o, $*.d]"

