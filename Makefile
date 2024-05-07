.DEFAULT_GOAL := all

CXX := g++
CCBUILDFLAGS := -o

RFLAGS := -lraylib

SRC_PATH := src
INC_PATH := src/include

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
	@$(CXX) $(CCBUILDFLAGS) $@ $(SRC) $(RFLAGS)
	@echo "Built Successfully!"

.PHONY: run
run: all
	@./$(TARGET)

clean:
	rm -f $(TARGET)
