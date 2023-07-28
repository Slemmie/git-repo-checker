CXX = g++
CXX_FLAGS = -Wshadow -Wall -std=c++2a
CXX_FLAGS_RELEASE = -O2
CXX_FLAGS_DEBUG = -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG

all: release

release:
	$(CXX) $(CXX_FLAGS) script.cpp -o checker $(CXX_FLAGS_RELEASE)

debug:
	$(CXX) $(CXX_FLAGS) script.cpp -o checker_debug $(CXX_FLAGS_DEBUG)
