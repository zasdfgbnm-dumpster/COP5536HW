hashtagcounter:hashtagcounter.cpp fibonacci.hpp
	g++ -std=c++11 hashtagcounter.cpp -O2 -o hashtagcounter


.PHONY: updatehpp

updatehpp:
	curl https://raw.githubusercontent.com/zasdfgbnm/cppfibonacci/master/fibonacci.hpp > fibonacci.hpp
