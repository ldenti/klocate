import sys

def load_kloc(fpath):
    hits = set()
    for line in open(fpath):
        line = line.strip("\n").split("\t")
        ref, p, idx, strand = line[0], line[1], line[3], line[5]
        hits.add(f"{idx}|{ref}:{p}|{strand}")
    return hits

def load_fastmap(fpath):
    hits = set()
    idx = ""
    for line in open(fpath):
        if line.startswith("SQ"):
            idx = line.strip("\n").split("\t")[1]
        elif line.startswith("EM"):
            for m in line.strip("\n").split("\t")[4:]:
                ref, pos = m.split(":")
                strand = pos[0]
                p = pos[1:]
                p = int(p)-1
                hits.add(f"{idx}|{ref}:{p}|{strand}")
    return hits

def load_burst(fpath):
    hits = set()
    for line in open(fpath):
        line = line.strip("\n").split("\t")
        idx = line[0]
        ref = line[1].split(" ")[0]
        ps, pe = line[8], line[9]
        p = ps
        strand = "+"
        if ps > pe:
            p = pe
            strand = "-"
        hits.add(f"{idx}|{ref}:{p}|{strand}")
    return hits

def main():
    kloc_path = sys.argv[1]
    fastmap_path = sys.argv[2]
    burst_path = sys.argv[3]

    kloc_hits = load_kloc(kloc_path)
    fastmap_hits = load_fastmap(fastmap_path)
    burst_hits = load_burst(burst_path)

    print("kloc:", len(kloc_hits), sep="\t")
    print("bwafm:", len(fastmap_hits), sep="\t")
    print("burst:", len(burst_hits), sep="\t")
    print("")
    print("kloc vs bwafm vs burst:", len(kloc_hits & fastmap_hits & burst_hits), sep="\t")
    print("kloc vs bwafm:", len(kloc_hits & fastmap_hits), sep="\t")
    print("kloc vs burst:", len(kloc_hits & burst_hits), sep="\t")
    print("bwafm vs burst:", len(fastmap_hits & burst_hits), sep="\t")
    print("")
    print("")
    for e in kloc_hits - burst_hits:
        print(e)
    # print("")
    # for e in fastmap_hits - burst_hits:
    #     print(e)
    
    
        
    

if __name__ == "__main__":
    main()