#include <stdio.h>             
#include <stdlib.h>            
#include <string.h> 
#include <stdbool.h>

int main (int argc, char **argv)
{
    FILE *text_file;
    FILE *output_file;
    char line[5];
    int i = 1;

    text_file = fopen("loop.txt", "r");
    output_file = fopen("final.txt", "a");

    while (fgets(line, sizeof(line), text_file))
    {
        if (i <= 75)
            line[3] = 'm';
        else if (i <= 150)
            line[3] = 'n';
        else if (i <= 225)
            line[3] = 'p';
        else if (i <= 300)
            line[3] = 'f';
        else if (i <= 375)
            line[3] = 't';
        else if (i <= 450)
            line[3] = 'd';
        else if (i <= 525)
            line[3] = 's';
        else if (i <= 600)
            line[3] = 'q';
        else if (i <= 675)
            line[3] = 'r';
        else if (i <= 750)
            line[3] = 'l';
        else if (i <= 825)
            line[3] = 'y';
        else if (i <= 900)
            line[3] = 'k';
        else if (i <= 975)
            line[3] = 'g';
        else if (i <= 1050)
            line[3] = 'h';
        else if (i <= 1125)
            line[3] = 'j';
        
        printf("%s\n", line);
        fprintf(output_file, "%s\n", line);
        i++;
    }
}