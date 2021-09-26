# kmap

Standalone tool based on the [bwa](https://github.com/lh3/bwa) index to locate a set of kmers along a reference genome. `kmap` searches each kmer (full and perfect match) in the index and outputs all positions the kmer maps to (output to sdtout in bed format).

### Download and installation
```
git clone --recursive https://github.com/ldenti/kmap.git
cd kmap/bwa
make
cd ../KMC
make
cd ..
make
```

### Usage
```
kmap -h

kmap index -h

kmap map -h
```

### Example
```
# Index the reference genome
./kmap index data/dros.4.fa

# Mapping from a list of kmers (txt mode)
./kmap map -k 23 -f 0 data/dros.4.fa data/query.k23.txt > txt.bed

# Mapping from fasta/q of kmers (fx mode)
./kmap map -k 23 -f 1 data/dros.4.fa data/query.k23.fa > fa.bed
./kmap map -k 23 -f 1 data/dros.4.fa data/query.k23.fq > fq.bed

# Mapping from KMC database (kmc mode)
./kmap map -k 23 -f 2 data/dros.4.fa data/query.k23 > kmc.bed
```

### TODO
* extensive experimental evaluation
* kmer sequence in output bed
* option to map (k-1)-mers
* verbose mode
* test a different index (?)
* multithreading (?)
