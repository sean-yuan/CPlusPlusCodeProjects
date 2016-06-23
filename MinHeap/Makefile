# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

# $^ is an auto variable that means "all dependencies",
#   which are test.cpp and $(BIN_DIR)/fib.o in this case
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
minheap: minheap.h minheap.cpp
	$(CC) $(CPPFLAGS) $^ -o $@

hash: hash.cpp hash.h minheap.cpp minheap.h
	$(CC) $(CPPFLAGS) $^ -o $@

doublet: doublet.cpp minheap.cpp hash.cpp 
	$(CC) $(CPPFLAGS) $^ -o $@

