SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
CXX := g++ -Wall -Wextra -g --std=c++17 -fPIC

.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

SimpleCore.so: $(OBJECTS)
	$(CXX) -shared -Wl,-soname,SimpleCore.so.1 -o $@ $^ -lc

#simplecore.so: SimpleCore.so
#	g++ -DSIMPLELIBS_EXPORTS --std=c++17 -shared $(inputs) -o $(output)
