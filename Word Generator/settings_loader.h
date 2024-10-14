#include <stdbool.h>

#define DEFAULT_GENERAL_SETTINGS_LOCATION   ".\\config files\\general.txt"
#define DEFAULT_WG_SETTINGS_LOCATION        ".\\config files\\word generation.txt"

#define CHARACTER_GROUP_NAME_MAX_SIZE           5
#define CHARACTER_GROUP_VALUE_MAX_SIZE          6

// structs for storing config data
struct character_group_data_s {
    char*** character_groups;
    int character_group_count;
    int* character_group_sizes;
};

struct pattern_data_s {
    char* pattern;
    char** parsed_pattern;
    int group_in_pattern_count;
};



struct general_settings_s {
    int word_count;
    bool output_as_list;
    bool allow_duplicates;
    bool file_as_output;
};

struct wg_settings_s {
    struct character_group_data_s character_group_data;
    struct pattern_data_s pattern_data;
    int min_syllables;
    int max_syllables;
};

// struct variables to store config file information
struct general_settings_s general_settings;
struct wg_settings_s wg_settings;

// function prototypes for loading settings at the beginning of the program
bool Load_General_Settings (char* settings_file);
bool Load_WG_Settings (char* settings_file);
