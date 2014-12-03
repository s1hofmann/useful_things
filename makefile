##################################################
# Author: Simon Hofmann <mail@simon-hofmann.org>
# Date:   2014-08-13
##################################################

# Declaration of variables
CC = g++
CC_FLAGS = -std=c++11 -g

PKG = #pkg-config?

SOURCEDIR = src
BINDIR = bin

TARGET = #Give me a cool name!

# File names
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
INCLUDES = $(SOURCES:.cpp=.h)
OBJECTS = $(SOURCES:$(SOURCEDIR)/%.cpp=$(BINDIR)/%.o)

# Main target
$(TARGET): $(OBJECTS)
	$(CC) $(PKG) $(OBJECTS) -o $(TARGET)

# To obtain object files
$(OBJECTS): $(SOURCES)
	@mkdir -p $(@D)
	$(CC) $(PKG) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(TARGET) $(OBJECTS)
