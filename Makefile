PROJECT = myGame

LIBPROJECT = lib$(PROJECT).a

AR = ar
AFLAGS = rsv

CXX = g++
CXXFLAGS = -I. -std=c++17 -Werror -Wpedantic -Wall -g -fPIC

LDXXFLAGS = $(CXXFLAGS) -L. -l:$(LIBPROJECT)
LDGTEESTFLAGS = $(CXXFLAGS) -lgtest -lgtest_main -lpthread

DEPS = $(wildcard *.h)
SOURSES = $(wildcard *.cpp)
OBJ = $(SOURSES .cpp = .o)

TEST_SOURSES = $(wildcard tests/*.cpp)
TEST_OBJ = $(TEST_SOURSES .cpp = .o)

.PHONY: default run test

defalt: run test

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TEST_SOURSES)%.o: $(TEST_SOURSES)%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $-


$(LIBPROJECT): $(OBJ) $(TEST_OBJ)
	$(AR) $(AFLAGS) $@ $^



$(PROJECT): main.o $(LIBPROJECT)
	$(CXX) -o $@ main.o $(CXXFLAGS)


run: $(PROJECT)

test: $(LIBPROJECT) $(TEST_OBJ)
	$(CXX) -o runTest $(TEST_OBJ) $(LDGTESTFLAGS)


clean:
	rm -f *.o
	rm -f $(PROJECT)
	rm -f $(LIBPROJECT)
	rm -f runTest
