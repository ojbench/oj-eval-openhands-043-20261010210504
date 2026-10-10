code: sample.cpp
	g++ -std=c++17 -O2 -pipe -static -s -o code sample.cpp

clean:
	rm -f code
