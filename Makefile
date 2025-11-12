PROJECT = myGame
LIBPROJECT = lib$(PROJECT).a

AR = ar
AFLAGS = rsv

CXX = g++
CXXFLAGS = -Iinclude -std=c++17 -Werror -Wpedantic -Wall -g -fPIC
LDXXFLAGS = $(CXXFLAGS) -L. -l$(PROJECT)
LDGTESTFLAGS = $(CXXFLAGS) -lgtest -lgtest_main -lpthread

SRC_DIRS = src/characters src/consoleInterface src/effects src/fight src/menu
INCLUDE_DIRS = include/characters include/consoleInterface include/effects include/fight include/menu

SOURCES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp)) main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

TEST_SOURCES = $(wildcard tests/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

.PHONY: default run test clean

default: $(PROJECT)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(LIBPROJECT): $(OBJECTS)
	$(AR) $(AFLAGS) $@ $^

$(PROJECT): $(OBJECTS) $(LIBPROJECT)
	$(CXX) -o $@ $(OBJECTS) $(CXXFLAGS)

run: $(PROJECT)
	./$(PROJECT)

test: $(TEST_OBJECTS) $(LIBPROJECT)
	$(CXX) $(TEST_OBJECTS) -o runTest $(LDGTESTFLAGS) -L. -lmyGame
	./runTest

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS)
	rm -f $(PROJECT) $(LIBPROJECT) runTest
