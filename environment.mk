CXX := g++

LD_LIBS := -lGL   \
           -lglfw \
           -lGLEW \

LD_DIRS := -L/usr/lib     \
           -L/usr/include \

SRC_DIR   := source
INC_DIR   := include
OBJ_DIR   := objects
LIB_DIR   := lib
RES_DIR   := resources
BUILD_DIR := build

ENGINE_DIR := GlobalEngine
ENGINE_LIB := libglobalengine.a

CXXFLAGS := -I$(INC_DIR) -I$(ENGINE_DIR)/$(INC_DIR) -g -Wall -Wextra -Werror --std=c++2a
LD_FLAGS := $(LD_DIRS) $(LD_LIBS)
LD_ENGINE_FLAGS := -L$(LIB_DIR) -lglobalengine

INCS := $(shell find $(INC_DIR) -name "*.h")
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
