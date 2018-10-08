#include <stdbool.h>

struct tiling{
    int lines;
    int columns;
    bool ** values;
};

void get_dimensions(char* buffer, int* i_width, int* i_height);
struct tiling* loadTiling(char * filePath);
