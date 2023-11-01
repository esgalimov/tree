CXX ?= g++

CXXFLAGS ?= -std=c++17 -O2
#-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

tree.o: tree.cpp tree.hpp
	$(CXX) $(CXXFLAGS) tree.cpp  -o $@

.PHONY: clean
clean:
	rm -rf *.o
