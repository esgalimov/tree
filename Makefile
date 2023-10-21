CXX ?= g++

CXXFLAGS ?= -std=c++17 -O2

tree.o: tree.cpp tree.hpp
	$(CXX) $(CXXFLAGS) tree.cpp -o $@

.PHONY: clean
clean:
	rm -rf *.o
