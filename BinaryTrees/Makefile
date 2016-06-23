# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

# $^ is an auto variable that means "all dependencies",
#   which are test.cpp and $(BIN_DIR)/fib.o in this case
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
bst: bst.h
	$(CC) $(CPPFLAGS) $^ -o $@

rbbst: rbbst.h bst.h
	$(CC) $(CPPFLAGS) $^ -o $@

map: map.cpp mapcoloring.h rbbst.h bst.h
	$(CC) $(CPPFLAGS) $^ -o $@

