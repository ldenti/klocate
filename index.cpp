#include <iostream>
#include <cstring>

#include <bwa.h>

using namespace std;

static const char *INDEX_USAGE_MESSAGE =
    "Usage: kmap index [-h] <reference.fa>\n"
    "\n"
    "      -h, --help                        display this help and exit\n"
    // "      -v, --verbose                     output COVS and GTS in INFO column (default: false)\n"
    // "      -t, --threads                     number of threads (default: 1)\n"
    "\n";

// Wrapper for bwa index
int main_index(int argc, char *argv[])
{
    int c;
    while ((c = getopt(argc, argv, "h")) >= 0)
    {
        switch (c)
        {
        case 'h':
            cerr << INDEX_USAGE_MESSAGE;
            return 0;
        default:
            cerr << INDEX_USAGE_MESSAGE;
            return 1;
        }
    }
    if (argc - optind < 1)
    {
        cerr << INDEX_USAGE_MESSAGE;
        return 1;
    }

    char *fa_path = argv[optind];
    int algo_type = 0;
    int block_size = 10000000;

    char *prefix = (char *)malloc(strlen(fa_path) + 4);
    strcpy(prefix, fa_path);

    bwa_idx_build(fa_path, prefix, algo_type, block_size);

    free(prefix);

    return 0;
}