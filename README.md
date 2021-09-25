# kmap

Small bwa wrapper to map (perfectly) a set of kmers against a reference genome.

### Download and installation
```
git clone --recursive https://github.com/ldenti/kmap.git
cd kmap/bwa
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
./kmap index data/dros.4.fa
# Mapping from list of kmers (txt mode)
./kmap map -k 23 -f 0 data/dros.4.fa data/query.k23.txt > txt.bed
# Mapping from fasta/q (fx mode)
./kmap map -k 23 -f 1 data/dros.4.fa data/query.k23.fa > fa.bed
./kmap map -k 23 -f 1 data/dros.4.fa data/query.k23.fq > fq.bed
# Mapping from KMC databse (kmc mode)
./kmap map -k 23 -f 1 data/dros.4.fa data/query.k23 > kmc.bed
```
