SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:

MAKEFLAGS := $(MAKEFLAGS)
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
else
  .RECIPEPREFIX = >
endif

NAME  := syntax_analyzer

MKDIR := mkdir -p
RM    := rm -f
RMDIR := rm -fr
TOUCH := touch -ap

SRC_DIR := ./source
INC_DIR := -I ./include
OBJ_DIR := ./build

SOURCES_SUB_DIRS := $(shell find $(SRC_DIR) -type d)
OBJECTS_SUB_DIRS := $(SOURCES_SUB_DIRS:$(SRC_DIR)%=$(OBJ_DIR)%)


SOURCES := $(shell find $(SRC_DIR) -type f -name "*.cpp")

OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS    := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.d)

CXX           := g++
CXX_WARNINGS  := -Wall -Wextra -Wpedantic
CXXFLAGS      := -std=c++20
LDFLAGS       := -lpthread -lrt

CXX_DEPS      =   -MT $(OBJ_DIR)/$*.o -MP -MMD  -MF $(OBJ_DIR)/$*.d
CXX_DEBUG     :=  -g3 -ggdb3
CXX_OPTIMIZE  :=  -O2 -march=native

CXXFLAGS := $(CXXFLAGS) $(CXX_DEBUG) $(CXX_OPTIMIZE) $(CXX_WARNINGS) $(INC_DIR)

LDFLAGS := $(LDFLAGS)

ifdef DEBUG_FLAG
  CXXFLAGS += -DDEBUG
endif


WHITE	    =			\e[0m
RED		    =			\e[38;5;203m
DARK_RED	= 		\e[38;5;160m
ORANGE	  =			\e[1;33m
GREEN	    =			\e[1;32m
DARK_BLUE	= 		\e[38;5;26m
CYAN 	    =			\e[38;5;51m
BOLD	    =			\e[1m

all: intro $(NAME)

intro:
>	@ printf "$(DARK_RED)$(BOLD)+---------------------------------------------------------+\n$(WHITE)"
>	@ printf "$(DARK_RED)$(BOLD)|█▀ █▄█ █▄░█ ▀█▀ ▄▀█ ▀▄▀   ▄▀█ █▄░█ ▄▀█ █░░ █▄█ ▀█ █▀  █▀█|\n$(WHITE)"
>	@ printf "$(DARK_RED)$(BOLD)|▄█ ░█░ █░▀█ ░█░ █▀█ █░█   █▀█ █░▀█ █▀█ █▄▄ ░█░ █▄ ██▄ █▀▄|\n$(WHITE)"
>	@ printf "$(DARK_RED)$(BOLD)+---------------------------------------------------------+\n$(WHITE)"

$(NAME): $(OBJECTS)
> @ $(CXX) $^ $(LDFLAGS) -o $@
> @ printf "$(ORANGE)$@ linking success\n$(WHITE)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJECTS_SUB_DIRS)
> @$(CXX) $(CXXFLAGS) $(CXX_DEPS) -c $< -o $@
> @ printf "$(DARK_BLUE)Compiling [$(CYAN)$@$(WHITE)$(DARK_BLUE)]$(WHITE)\n"

$(OBJECTS_SUB_DIRS):
> @$(MKDIR) $(OBJECTS_SUB_DIRS)


test:
> @$(SHELL) ./functional_tests.sh

clean:
> @$(RMDIR) $(OBJ_DIR)
> @ printf "$(RED)Removing object files.$(WHITE)\n"

fclean: clean
> @$(RM) $(NAME)
> @ printf "$(RED)Removing binary file.$(WHITE)\n"

re: fclean all

-include $(DEPS)

.PHONY: all test clean fclean re