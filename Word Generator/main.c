#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "main.h"
#include "settings_loader.h"

int main (int argc, char** argv) {
    bool loaded_correctly = Load_General_Settings(DEFAULT_GENERAL_SETTINGS_LOCATION);
    loaded_correctly = Load_WG_Settings(DEFAULT_WG_SETTINGS_LOCATION);

    Export_General_Settings ();
    Export_WG_Settings ();

    printf("DONE\n");

    
    
    // system("cls");
    // Title_Screen();

    // Loading_Screen();

    // system("cls");
    // Menu();
    
    return 0;
}



void Title_Screen () {
    printf("			 _	 _  ________  ______   _____\n");
    printf("			| |	| |/   __   \\|      \\ |  _  \\\n");
    printf("			| |     | |   /	 \\   |  <_>  || | \\  \\\n");
    printf("			| |  _  | |  |	  |  |  __  / | |  |  |\n");
    printf("			| |_| |_| |   \\__/   | |  \\ \\ | |_/  /\n");
    printf("			|_________|\\________/|_|   \\_\\|_____/\n\n\n");

    printf("  ______  ______ __    _ ______ ______       ____  _________  ________  ______\n");
    printf(" /  ___ \\| _____|  \\  | | _____|      \\     / __ \\|___   ___|/   __   \\|      \\\n");
    printf("|  /   \\_| |__  | | \\ | | |__  |  <_>  |   / /  \\ \\   | |   |   /  \\   |  <_>  |\n");
    printf("| |   ___|  __| | |\\ \\| |  __| |  __  /   / /____\\ \\  | |   |  |    |  |  __  /\n");
    printf("|  \\__\\  | |____| | \\ | | |____| |  \\ \\  / ________ \\ | |   |   \\__/   | |  \\ \\\n");
    printf(" \\______/|______|_|  \\__|______|_|   \\_\\/_/        \\_\\|_|    \\________/|_|   \\_\\\n\n");
    printf("________________________________________________________________________________\n\n");
    printf("Loading ");
}

void Menu () {
    printf("MAIN MENU\n\n");

    printf("1. Generate Words\n");
    printf("2. Word Generation Settings\n");
    printf("3. General Settings\n");
    printf("4. Export Word Generation Settings\n");
    printf("5. Export General Settings\n");
    printf("6. Exit\n");

    printf("> ");

    char c;

    do {
        fscanf(stdin, "%c", &c);
            if (!isspace(c) && c >= 49 && c <= 54) {
                printf("your input: %c\n", c);
            } else {
                printf("> ");
            }
        
    } while (c != '6');

    printf("Have a good day\n\n");
}

void Loading_Screen () {
    clock_t time;
    time = clock();

    bool loaded_correctly = Load_General_Settings(DEFAULT_GENERAL_SETTINGS_LOCATION);
    if (!loaded_correctly)  exit(1);

    while (clock() - time < 750);
    printf(". ");

    loaded_correctly = Load_WG_Settings(DEFAULT_WG_SETTINGS_LOCATION);
    if (!loaded_correctly) exit(1);

    while (clock() - time < 1500);
    printf(". ");

    while (clock() - time < 2250);
    printf(". ");

    while (clock() - time < 3000);
}

void Export_General_Settings () {
    FILE* file;
    file = fopen(EXPORT_GENERAL_SETTINGS_LOCATION, "w");

    if (file == NULL)   exit(1);

    char* key;
    char* value;

    key = "word-count";
    value = malloc(sizeof(int));
    sprintf(value, "%d", general_settings.word_count);
    fprintf(file, "%s: %s\n", key, value);

    key = "output-as-list";
    value = general_settings.output_as_list ? "yes" : "no";
    fprintf(file, "%s: %s\n", key, value);

    key = "allow-duplicates";
    value = general_settings.allow_duplicates ? "yes" : "no";
    fprintf(file, "%s: %s\n", key, value);

    key = "file-as-output";
    value = general_settings.file_as_output ? "yes" : "no";
    fprintf(file, "%s: %s", key, value);

    fclose(file);

    free(file);
    free(key);
    free(value);
}

void Export_WG_Settings () {
    FILE* file;
    file = fopen(EXPORT_WG_SETTINGS_LOCATION, "w");

    if (file == NULL)   exit(1);

    char* key;
    char* value = NULL;

    key = "character-group";
    for (int i = 0; i < wg_settings.character_group_data.character_group_count; i++) {
        value = realloc(value, sizeof(char) * 1000);
        sprintf(value, "%s: ", wg_settings.character_group_data.character_groups[i][0]);

        for (int j = 1; j < wg_settings.character_group_data.character_group_sizes[i]; j++) {
            strcat(value, wg_settings.character_group_data.character_groups[i][j]);
            strcat(value, " ");
        }

        fprintf(file, "%s: %s\n", key, value);
    }

    key = "pattern";
    value = realloc(value, sizeof(char) * strlen(wg_settings.pattern_data.pattern) + 1);
    sprintf(value, "%s", wg_settings.pattern_data.pattern);
    fprintf(file, "%s: %s\n", key, value);

    key = "min-syllables";
    value = realloc(value, sizeof(int));
    sprintf(value, "%d", wg_settings.min_syllables);
    fprintf(file, "%s: %s\n", key, value);

    key = "max-syllables";
    sprintf(value, "%d", wg_settings.max_syllables);
    fprintf(file, "%s: %s", key, value);

    fclose(file);

    free(file);
    free(key);
    free(value);
}

void Generate_Words () {
    // char* parsed_pattern;
    // for (int i = 0; )
}
