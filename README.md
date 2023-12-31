# Red-black tree
There are two levels of this task:
* level_1: `k key` - adds key to tree, `q start stop` - print number of elements between start and stop.
* level_2: `k key` - adds key to tree, `m pos` - print key on position pos, `n key` - print number of elements lower than key

How to launch:
1. `cmake -B build` or if graphviz is installed on your computer `cmake -B build -DCMAKE_CXX_FLAGS="-DDUMP"` to have tree graphviz dumps in dumps directory.
2. `cd build`.
3. `make`.
4. use `./tree` to run my red-black tree. Commands: `k key` - adds key to tree, `q start stop` - print number of elements between start and stop.
5. use `./tree_comp` to have answers and time comparing with std::set.
6. you can run tests from build dir by command: `bash ../tests/tests.sh`.

Dump example:
![tree_dump0](https://github.com/esgalimov/tree/assets/74832034/0dfb8a07-c737-480f-9f13-330d07e3a543)
