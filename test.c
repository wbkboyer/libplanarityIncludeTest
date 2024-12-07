#include "test.h"

int main(void)
{
    int retVal = 0;

    printf("Hello, world!\n");

    graphP theGraph = gp_New();
    retVal = gp_InitGraph(theGraph, 8);
    if (retVal != OK)
    {
        printf("Oh boy, couldn't initialie graph!\n");
        return retVal;
    }

    printf("Successfully initialized graphP!\n");

    return retVal;
}