raytracer: src/*.cpp src/*.hpp src/*.h
	g++ -O2 -Wall src/main.cpp -o raytracer

clean:
	rm -f raytracer

.PHONY: clean
