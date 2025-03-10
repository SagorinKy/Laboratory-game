PROJECT = myGame

LIBPROJECT = lib$(PROJECT).a

AR = ar
AFLAGS = rsv

CXX = g++
CXXFLAGS = -I. -std=c++17 -Werror -Wpedantic -Wall -g -fPIC

LDXXFLAGS = $(CXXFLAGS) -L. -l$(PROJECT)
LDGTESTFLAGS = $(CXXFLAGS) -lgtest -lgtest_main -lpthread

DEPS = $(wildcard *.h)
SOURSES = $(wildcard *.cpp)
OBJ = $(SOURSES:.cpp=.o)

TEST_SOURSES = $(wildcard tests/*.cpp)
TEST_OBJ = $(TEST_SOURSES:.cpp=.o)

.PHONY: default run test clean

default: run test

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/%.o: tests/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(LIBPROJECT): $(OBJ) 
	$(AR) $(AFLAGS) $@ $^



$(PROJECT): $(OBJ) $(LIBPROJECT)
	$(CXX) -o $@ $(OBJ) $(CXXFLAGS)


run: $(PROJECT)
	./$(PROJECT)

test: $(TEST_OBJ) $(LIBPROJECT) 
	$(CXX) $(TEST_OBJ) -o runTest $(LDGTESTFLAGS) -L. -lmyGame
	./runTest

clean:
	rm -f *.o
	rm -f $(PROJECT)
	rm -f $(LIBPROJECT)
	rm -f runTest
