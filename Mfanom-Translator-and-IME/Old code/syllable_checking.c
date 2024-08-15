#include <stdio.h>             
#include <stdlib.h>            
#include <string.h> 
#include <stdbool.h>

#define MAX_SYLLABLE_LENGTH 5
#define MAX_SYLLABLE_NUM 2480
#define MAX_INPUT_LENGTH 256

char dictionary [MAX_SYLLABLE_NUM] [MAX_SYLLABLE_LENGTH];

bool search_for_syllables (char word [MAX_INPUT_LENGTH]);
char* substring (char *word, int i);
char *subtract_substring (char *word, int i);

int main (int argc, char **argv)
{    
    FILE *syllable_database;
    syllable_database = fopen ("syllable_database.txt", "r");

    int i = 0;
    char line [MAX_SYLLABLE_LENGTH];
    while (fgets (line, MAX_SYLLABLE_LENGTH, syllable_database) != NULL) 
    {
        if (!strcmp (line, "\n"))
            continue;

        if (line [strlen (line) - 1] == '\n')
            line [strlen (line) - 1] = '\0';

        strncpy (dictionary [i], line, MAX_SYLLABLE_LENGTH);
        i++;
    }

    system ("cls");
    fprintf (stdout, "Input word to get syllables:\n");
    char input [MAX_INPUT_LENGTH];
    while (fgets (input, sizeof (input), stdin))
    {
        // system ("cls");
        if (*input == '.')
            break;

        else
        {
            char *token = strtok (input, " \n");

            while (token != NULL)
            {   
                // fprintf (stdout, "%s\n", token);
                search_for_syllables (token);
                token = strtok (NULL, " \n");
            }
            printf("\n");
        }
    }
}



bool search_for_syllables (char word [MAX_INPUT_LENGTH])
{
    if (!strcmp (word, ""))
        return true;

    for (int i = 1; i < strlen (word) + 1; i++)
    {
        char substr [MAX_INPUT_LENGTH];
        for (int k = 0; k < i; k++)
            substr [k] = word [k];

        for (int j = 0; j < MAX_SYLLABLE_NUM; j++)
        {
            if (!strcmp (substr, dictionary [j]))
            {
                char new_substr [MAX_INPUT_LENGTH]; 
                for (int y = i, z = 0; y < strlen (word) + 1; y++, z++)
                    new_substr [z] = word [y];
                // printf("%s", substr);
                if (search_for_syllables (new_substr))
                {
                    printf("%s\t%s\n", substr, new_substr);
                    // return true;
                }
            }
        }
    }

    return false;
}

char* substring (char *word, int i)
{
    char *substr = malloc (sizeof (char) * sizeof (word));

    for (int j = 0; j < i; j++)
        substr [j] = word [j];

    return substr;
}  

char* subtract_substring (char *word, int i)
{
    char *substr = malloc (sizeof (char) * sizeof (word));

    for (int j = i, k = 0; j < strlen (word) + 1; j++, k++)
        substr [k] = word [j]; 

    return substr;
}