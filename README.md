# kmap

Standalone tool based on the [bwa](https://github.com/lh3/bwa) index to locate a set of kmers along a reference genome. `klocate` searches each kmer (full and perfect match) in the index and outputs all positions the kmer maps to (output to sdtout in bed format).

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
klocate -h

klocate index -h

klocate map -h
```

### Example
```
# Index the reference genome
./klocate index data/dros.4.fa

# Locate kmers from txt list (txt mode)
./klocate find -k 23 -f 0 data/dros.4.fa data/query.k23.txt > txt.bed

# Locate kmers from fasta/q file (fx mode)
./klocate find -k 23 -f 1 data/dros.4.fa data/query.k23.fa > fa.bed
./klocate find -k 23 -f 1 data/dros.4.fa data/query.k23.fq > fq.bed

# Locate kmers from KMC database (kmc mode)
./klocate find -k 23 -f 2 data/dros.4.fa data/query.k23 > kmc.bed
```

### TODO
* extensive experimental evaluation
* kmer sequence in output bed
* option to map (k-1)-mers
* verbose mode
* test a different index (?)
* multithreading (?)
