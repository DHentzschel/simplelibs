SRC:=$(wildcard *.cpp)
INC:=-I../SimpleCore/
LIB:=../bin/
OBJ:=$(patsubst %.cpp,%.o,$(SRC))
BIN:=simplecore-test
CXX:=g++ -Wall -Wextra -g --std=c++17
CPPFLAGS+=-ISIMPLELIBS_TEST

.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

$(BIN): $(OBJ)
	$(CXX) $(INC) -L$(LIB) -l:simplecore -o $@ $^ -lc
	mv $(BIN) ../bin/

.PHONY: clean
clean:
	rm -rf *.o ../bin/$(BIN)
