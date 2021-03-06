#include <iostream>
#include <cstring>

using namespace std;

int main_index(int argc, char *argv[]);
int main_find(int argc, char *argv[]);

int main_usage()
{
    cerr << "Usage:\tklocate [index|find] -h" << endl;
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return main_usage();

    if (strcmp(argv[1], "index") == 0)
        return main_index(argc - 1, argv + 1);
    else if (strcmp(argv[1], "find") == 0)
        return main_find(argc - 1, argv + 1);
    else
        return main_usage();
}
