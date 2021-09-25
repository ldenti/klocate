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
gunzip data/dros.4.fa.gz

./kmap index data/dros.4.fa
./kmap map -k 23 -f 0 data/dros.4.fa data/query.k23.txt
```
