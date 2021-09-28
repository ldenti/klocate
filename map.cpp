#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <zlib.h>

#include "bwa.h"
#include "bwt.h"
#include "kseq.h"
#include "kmc_api/kmc_file.h"

KSEQ_INIT(gzFile, gzread)

using namespace std;

static const char *MAP_USAGE_MESSAGE =
    "Usage: kmap map [-h] -k <klen> -f <0|1|2> <reference.fa> <query>\n"
    "\n"
    "      -k, --klen                        k-mer size (default: 23)\n"
    "      -f, --format                      input file format (0: txt mode; 1: fx mode; 2: kmc mode; default: 0)\n"
    "      -h, --help                        display this help and exit\n"
    // "      -v, --verbose                     output COVS and GTS in INFO column (default: false)\n"
    // "      -t, --threads                     number of threads (default: 1)\n"
    "\n";

void search(bwaidx_t *idx, const char *name, char *kmer, const uint k)
{
    for (uint i = 0; i < k; ++i)
        kmer[i] = nst_nt4_table[(int)kmer[i]];

    bwtint_t *sa_begin = (bwtint_t *)malloc(sizeof(bwtint_t));
    bwtint_t *sa_end = (bwtint_t *)malloc(sizeof(bwtint_t));
    bwt_match_exact(idx->bwt, k, (const ubyte_t *)kmer, sa_begin, sa_end);

    bwtint_t pos;
    int len = k, is_rev, ref_id;
    for (uint i = *sa_begin; i <= *sa_end; ++i)
    {
        pos = bns_depos(idx->bns, bwt_sa(idx->bwt, i), &is_rev);
        if (is_rev)
            pos -= k - 1;
        bns_cnt_ambi(idx->bns, pos, len, &ref_id);
        cout << idx->bns->anns[ref_id].name << "\t" << pos - idx->bns->anns[ref_id].offset << "\t" << pos - idx->bns->anns[ref_id].offset + k << "\t"
             << name
             << "\t"
             << "0"
             << "\t"
             << "+-"[is_rev] << endl;
    }
    free(sa_begin);
    free(sa_end);
}

int map_txt(bwaidx_t *idx, char *fpath, const uint k)
{
    FILE *fp;
    char *kmer = (char *)malloc(sizeof(char) * (k + 1));
    size_t len = 0;
    ssize_t read;

    fp = fopen(fpath, "r");
    if (fp == NULL)
        return EXIT_FAILURE;

    int i = 0;
    while ((read = getline(&kmer, &len, fp)) != -1)
        search(idx, to_string(i++).c_str(), kmer, k);
    fclose(fp);

    free(kmer);
    return EXIT_SUCCESS;
}

int map_fx(bwaidx_t *idx, char *fpath, const uint k)
{
    gzFile fp = gzopen(fpath, "r");
    kseq_t *seq = kseq_init(fp);
    int l;
    while ((l = kseq_read(seq)) >= 0)
        search(idx, seq->name.s, seq->seq.s, k);
    kseq_destroy(seq);
    gzclose(fp);
    return EXIT_SUCCESS;
}

int map_kmc(bwaidx_t *idx, char *fpath, const uint k)
{

    CKMCFile kmer_db;
    if (!kmer_db.OpenForListing(fpath))
    {
        cerr << "Unable to open kmer database" << endl;
        return EXIT_FAILURE;
    }
    uint32 klen, mode, min_counter, pref_len, sign_len, min_c, counter;
    uint64 tot_kmers, max_c;
    kmer_db.Info(klen, mode, min_counter, pref_len, sign_len, min_c, max_c, tot_kmers);
    CKmerAPI kmer_obj(klen);
    char *kmer = (char *)malloc(sizeof(char) * (k + 1));
    int i = 0;
    while (kmer_db.ReadNextKmer(kmer_obj, counter))
    {
        kmer_obj.to_string(kmer);
        search(idx, to_string(i++).c_str(), kmer, k);
    }

    free(kmer);
    return EXIT_SUCCESS;
}

int main_map(int argc, char *argv[])
{
    int c;
    uint k = 21, f = 0;
    while ((c = getopt(argc, argv, "k:f:h")) >= 0)
    {
        switch (c)
        {
        case 'k':
            k = atoi(optarg);
            break;
        case 'f':
            f = atoi(optarg);
            break;
        case 'h':
            cerr << MAP_USAGE_MESSAGE;
            return 0;
        default:
            cerr << MAP_USAGE_MESSAGE;
            return 1;
        }
    }
    if (argc - optind < 2)
    {
        cerr << MAP_USAGE_MESSAGE;
        return 1;
    }
    char *fa_path = argv[optind++];
    char *query_path = argv[optind];

    bwaidx_t *idx = bwa_idx_load(fa_path, BWA_IDX_ALL);
    if (NULL == idx)
    {
        cerr << "Index load failed." << endl;
        return 1;
    }
    cerr << "Index load." << endl;

    if (f == 0)
        return map_txt(idx, query_path, k);
    else if (f == 1)
        return map_fx(idx, query_path, k);
    else if (f == 2)
        return map_kmc(idx, query_path, k);
    else
    {
        cerr << "Unknown file format" << endl;
        return 1;
    }

    return 0;
}