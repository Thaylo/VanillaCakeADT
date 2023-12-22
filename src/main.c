#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "DataObject.h"

int main()
{
    // open the file logo.txt and print it to the screen
    FILE * file = fopen("adtAsciiArtLogo.txt", "r");
    
    if (file != NULL)
    {
        printf("\n\n");
        int c;
        while ((c = fgetc(file)) != EOF) {
            printf("%c", c);
        }
        fclose(file);
        printf("\n\n");
    }
    
    return 0;
}
