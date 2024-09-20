#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "settings_loader.h"

bool Load_General_Settings (char* settings_file) {
    // open general settings text file
    FILE* file;
    file = fopen(settings_file,"r+");

    // temporary variables to store data from text files
    char key[20];
    char value[1000];

    // return false if the file cannot be opened
    if (file == NULL)   return false;
    // each line should have the format "key: value"
    while (fscanf(file, "%[^:] %*c %[^\n]", key, value) == 2) {
        // remove any leading newline characters from the key variable
        __int8 offset_idx = 0;
        while (key[offset_idx] == '\n')     offset_idx++;
        for (int i = 0; i < strlen(key); i++)   key[i] = key[i + offset_idx];

        // store the data in value based on the data in key
        if (strcmp(key, "word-count") == 0) {
            general_settings.word_count = atoi(value);
        } else if (strcmp(key, "output-as-list") == 0) {
            general_settings.output_as_list = strcmp(value, "yes") == 0 ? true : false;
        } else if (strcmp(key, "allow-duplicates") == 0) {
            general_settings.allow_duplicates = strcmp(value, "yes") == 0 ? true : false;
        } else if (strcmp(key, "file-as-output") == 0) {
            general_settings.file_as_output = strcmp(value, "yes") == 0 ? true : false;
        }

        if (feof(file))     break;
    }

    // close the file and return true to load was successful
    fclose(file);
    free(file);
    return true;
}

bool Load_WG_Settings (char* settings_file) {
    // open word generation settings text file
    FILE* file;
    file = fopen(settings_file, "r+");
    
    // temporary variables to store data from text files
    char key[20];
    char value[1000];

    // initialize number of character groups to 0
    wg_settings.character_group_data.character_group_count = 0;

    // return false if the file cannot be opened
    if (file == NULL)   return false;
    // each line should have the format "key: value"
    while (fscanf(file, "%[^:] %*c %[^\n]", key, value) == 2) {
        // remove any leading newline characters from the key variable
        __int8 offset_idx = 0;
        while (key[offset_idx] == '\n')     offset_idx++;
        for (int i = 0; i < strlen(key); i++)   key[i] = key[i + offset_idx];

        // store the data in value based on the data in key
        if (strcmp(key, "character-group") == 0) {
            // temporary variables to stokenize data in value variable
            char group_name[5];
            char group_values[995];
            char* single_value;

            // split data in value variable between group name and group values
            sscanf(value, "%[^,] %*c %[^\n]", group_name, group_values);

            // initialize the counter for this group's characters
            wg_settings.character_group_data.character_group_sizes = realloc(wg_settings.character_group_data.character_group_sizes, sizeof(int) * (wg_settings.character_group_data.character_group_count + 1));
            wg_settings.character_group_data.character_group_sizes[wg_settings.character_group_data.character_group_count] = 0;

            // reallocate more space to add another character group in the 2d list
            wg_settings.character_group_data.character_groups = realloc(wg_settings.character_group_data.character_groups, sizeof(char**) * (wg_settings.character_group_data.character_group_count + 1));

            // store the character group's name
            wg_settings.character_group_data.character_groups[wg_settings.character_group_data.character_group_count] = malloc(sizeof(char*) * 2);
            wg_settings.character_group_data.character_groups[wg_settings.character_group_data.character_group_count][0] = malloc(sizeof(char) * CHARACTER_GROUP_NAME_MAX_SIZE);
            strcpy(wg_settings.character_group_data.character_groups[wg_settings.character_group_data.character_group_count][0], group_name);

            // tokenize every character in the group, and add it to the current group's list
            single_value = strtok(group_values, " ");
            while(single_value != NULL) {
                wg_settings.character_group_data.character_groups[wg_settings.character_group_data.character_group_count] = realloc(
                    wg_settings.character_group_data.character_groups[wg_settings.character_group_data.character_group_count], sizeof(char*) * (1 + ++wg_settings.character_group_data.character_group_sizes[wg_settings.character_group_data.character_group_count]));
                wg_settings.character_group_data.character_groups[wg_settings.character_group_data.character_group_count][wg_settings.character_group_data.character_group_sizes[wg_settings.character_group_data.character_group_count]] = malloc(
                    sizeof(char) * CHARACTER_GROUP_VALUE_MAX_SIZE);

                strcpy(wg_settings.character_group_data.character_groups[wg_settings.character_group_data.character_group_count][wg_settings.character_group_data.character_group_sizes[wg_settings.character_group_data.character_group_count]], single_value);
                single_value = strtok(NULL, ", ");
            }            

            wg_settings.character_group_data.character_group_sizes[wg_settings.character_group_data.character_group_count]++;
            wg_settings.character_group_data.character_group_count++;
            free(single_value);
        } else if (strcmp(key, "pattern") == 0) {
            wg_settings.pattern_data.pattern = malloc(sizeof(char) * strlen(value) + 1);
            strcpy(wg_settings.pattern_data.pattern, value);

            wg_settings.pattern_data.parsed_pattern = NULL;
            wg_settings.pattern_data.group_in_pattern_count = 0;
            char current_pattern_group[7];
            int cpg_idx = 0;
            bool temp_char_appear = false;

            for (int i = 0; i < strlen(wg_settings.pattern_data.pattern); i++) {
                if (wg_settings.pattern_data.pattern[i] == '(') {
                    if (!temp_char_appear) {
                        if (cpg_idx != 0) {
                            wg_settings.pattern_data.parsed_pattern = realloc(wg_settings.pattern_data.parsed_pattern, sizeof(char*) * (wg_settings.pattern_data.group_in_pattern_count + 1));
                            wg_settings.pattern_data.parsed_pattern[wg_settings.pattern_data.group_in_pattern_count] = malloc(sizeof(char) * strlen(current_pattern_group));
                            strcpy(wg_settings.pattern_data.parsed_pattern[wg_settings.pattern_data.group_in_pattern_count], current_pattern_group);
                            wg_settings.pattern_data.group_in_pattern_count++;
                        }

                        temp_char_appear = true;
                        cpg_idx = 0;
                        for (int i = 0; i < 7; i++)     current_pattern_group[i] = '\0';
                        current_pattern_group[cpg_idx++] = '~';
                    } else {
                        return false;
                    }
                } else if (wg_settings.pattern_data.pattern[i] == ')') {
                    if (temp_char_appear) {
                        wg_settings.pattern_data.parsed_pattern = realloc(wg_settings.pattern_data.parsed_pattern, sizeof(char*) * (wg_settings.pattern_data.group_in_pattern_count + 1));
                        wg_settings.pattern_data.parsed_pattern[wg_settings.pattern_data.group_in_pattern_count] = malloc(sizeof(char) * strlen(current_pattern_group));
                        strcpy(wg_settings.pattern_data.parsed_pattern[wg_settings.pattern_data.group_in_pattern_count], current_pattern_group);
                        wg_settings.pattern_data.group_in_pattern_count++;

                        temp_char_appear = false;
                        cpg_idx = 0;
                        for (int i = 0; i < 7; i++)     current_pattern_group[i] = '\0';
                    } else {
                        return false;
                    }
                } else {
                    current_pattern_group[cpg_idx++] = wg_settings.pattern_data.pattern[i];

                    if (i == strlen(wg_settings.pattern_data.pattern) - 1) {
                        wg_settings.pattern_data.parsed_pattern = realloc(wg_settings.pattern_data.parsed_pattern, sizeof(char*) * (wg_settings.pattern_data.group_in_pattern_count + 1));
                        wg_settings.pattern_data.parsed_pattern[wg_settings.pattern_data.group_in_pattern_count] = malloc(sizeof(char) * strlen(current_pattern_group));
                        strcpy(wg_settings.pattern_data.parsed_pattern[wg_settings.pattern_data.group_in_pattern_count], current_pattern_group);
                        wg_settings.pattern_data.group_in_pattern_count++;
                    }
                }
            }
        } else if (strcmp(key, "min-syllables") == 0) {
            wg_settings.min_syllables = atoi(value);
        } else if (strcmp(key, "max-syllables") == 0) {
            wg_settings.max_syllables = atoi(value);
        }

        if (feof(file))     break;
    }


    
    // close the file and return true to load was successful
    fclose(file);
    free(file);
    return true;
}