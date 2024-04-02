.DEFAULT_GOAL := all

CXX := g++
CCBUILDFLAGS := -o

SDL_FLAGS := -lSDL2
SDL_FLAGS += -lSDL2_image


SRC_PATH := src
INC_PATH := include

TARGET_NAME := game

ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
endif

SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
INC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.h*)))

TARGET := $(TARGET_NAME)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRC) $(INC)
	$(CXX) $(CCBUILDFLAGS) $@ $(SRC) $(SDL_FLAGS)

.PHONY: run
run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
