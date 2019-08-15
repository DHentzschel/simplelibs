SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
BIN := libsimplecore.so
CXX := g++ -Wall -Wextra -g --std=c++17 -fPIC

.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

$(BIN): $(OBJ)
	$(CXX) -shared -Wl,-soname,simplecore.so.1 -o $@ $^ -lc
	mv $(BIN) ../bin/

.PHONY: clean
clean:
	rm -rf ../bin/$(BIN) $(OBJ)
