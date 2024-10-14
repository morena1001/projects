#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "main.h"
#include "settings_loader.h"

int main (int argc, char** argv) {
    clock_t time;
    time = clock();

    bool loaded_correctly = Load_General_Settings(DEFAULT_GENERAL_SETTINGS_LOCATION);
    loaded_correctly = Load_WG_Settings(DEFAULT_WG_SETTINGS_LOCATION);


    while (clock() - time < 3000);
    Generate_Words(time);
    // system("cls");
    // Title_Screen();

    // Loading_Screen(time);

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

void Loading_Screen (clock_t time) {
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

void Generate_Words (clock_t time) {
    // variable to store the generated words
    char** words = malloc(sizeof(char*) * general_settings.word_count);
    
    // 1st loop, loops so that a word_count amount of words are generated
    for (int i = 0; i < general_settings.word_count; i++) {
        // allocate space of 100 characters per element in words
        words[i] = malloc(sizeof(char) * MAX_GENERATED_WORD_SIZE);

        // seed the random number variable according to how much time has passed in the program
        srand((i * 1000 - (clock() - time)) % 17);
        // 2nd loop, loops are randomized number of times in the range of the minimum and maximum syllables allowed for a word
        for (int j = 0; j < (rand() % (wg_settings.max_syllables - wg_settings.min_syllables)) + wg_settings.min_syllables; j++) {
            // 3rd loop, iterate through the pattern
            for (int k = 0; k < wg_settings.pattern_data.group_in_pattern_count; k++) {
                // if a group in the pattern optional, generate a random to see if to skip it or not
                if (wg_settings.pattern_data.parsed_pattern[k][0] == '~') {
                    srand((i + j + k * 1000 - (clock() - time)) % 17);
                    if (rand() % 2) {
                        // 4th loop, iterate through the groups to find the correct character group 
                        for (int l = 0; l < wg_settings.character_group_data.character_group_count; l++) {
                            if (wg_settings.pattern_data.parsed_pattern[k][1] == wg_settings.character_group_data.character_groups[l][0][0]) {
                                srand((i + j + k + l * 1000 - (clock() - time)) % 17);
                                words[i] = wg_settings.character_group_data.character_groups[l][(rand() % (wg_settings.character_group_data.character_group_sizes[l] - 1)) + 1];
                            }
                        }
                    } else {
                        continue;
                    }
                } else {
                    for (int l = 0; l < wg_settings.character_group_data.character_group_count; l++) {
                        if (wg_settings.pattern_data.parsed_pattern[k][0] == wg_settings.character_group_data.character_groups[l][0][0]) {
                            srand((i + j + k + l * 1000 - (clock() - time)) % 17);
                            words[i] = wg_settings.character_group_data.character_groups[l][(rand() % (wg_settings.character_group_data.character_group_sizes[l] - 1)) + 1];
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < general_settings.word_count; i++) {
        printf("%s%s", words[i], general_settings.output_as_list ? "\n" : " ");
    }
}
