
#include <stdlib.h>
#include "../../headers/results/writefile.h"

void writefile()
{
    printf("file result ok");
    if(access("../results/results.csv", F_OK) != -1)
    {
        //FILE * file_result = fopen("../results/results.csv");
    }
}