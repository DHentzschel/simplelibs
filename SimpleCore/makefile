CXXFLAGS += -fPIC
CXXFLAGS += -O3
CXXFLAGS += -std=c++17
simplelibs.so: *.o
	$(CXX) -shared $^ -o $@ -Wl,--whole-archive -lAlgatorc -Wl,--no-whole-archive

*.o: CXXFLAGS+=-fPIC
