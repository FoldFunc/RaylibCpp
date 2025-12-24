CXX := g++
SRC := src
BUILD := build
TARGET := $(BUILD)/game

# Find all cpp files recursively
SRCS := $(shell find $(SRC) -name '*.cpp')

# Map src/foo/bar.cpp -> build/foo/bar.o
OBJS := $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SRCS))

# raylib flags
CPPFLAGS := -I$(SRC) $(shell pkg-config --cflags raylib)
LDLIBS  := $(shell pkg-config --libs raylib)

CXXFLAGS := -std=c++23 -Wall -Wextra -O2 -MMD -MP

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $^ -o $@ $(LDLIBS)

# Compile rule (creates subdirectories automatically)
$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Include generated dependency files
-include $(OBJS:.o=.d)

clean:
	rm -rf $(BUILD)

