CXX=g++
CXXFLAGS=-std=c++11 -Wall -O3 -I./bwa/ -I./KMC
LIBS=-L./bwa
LDFLAGS=-lbwa -lm -lz # -lpthread -lsdsl -ldivsufsort -ldivsufsort64 # -lrt

all: klocate

klocate: index.o find.o main.o \
		./KMC/kmc_api/kmc_file.o ./KMC/kmc_api/kmer_api.o ./KMC/kmc_api/mmer.o
	@echo "* Linking $@"
	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	@echo '* Compiling $<'
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf *.o kmap
