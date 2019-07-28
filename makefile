CXXFLAGS += -fPIC
CXXFLAGS += -O3
CXXFLAGS += -std=c++17
simplelibs.so: *.o
	g++ -shared $^ -o $@
