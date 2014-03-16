#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *str = "Hello World";

int main(void)
{
    char *test = malloc(strlen(str) + 1);

    if (!test)
        return 1;

    test = strcpy(test, str);

    printf("String %s\n", test);

    free(test);

    return 0;
}
