CXX=g++
CXXFLAGS=-std=c++11 -Wall -g -O0 -I./bwa/
LIBS=-L./bwa
LDFLAGS=-lbwa -lm -lz # -lpthread -lsdsl -ldivsufsort -ldivsufsort64 # -lrt

all: kmap

kmap: index.o map.o main.o
	@echo "* Linking $@"
	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	@echo '* Compiling $<'
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf *.o kmap
