#define EXPORT_GENERAL_SETTINGS_LOCATION    ".\\output files\\general.txt"
#define EXPORT_WG_SETTINGS_LOCATION         ".\\output files\\word generation.txt"

#define MAX_GENERATED_WORD_SIZE             100

// function prototypes for program main sequence load up
void Loading_Screen (clock_t time);
void Title_Screen ();
void Menu ();

// function prototypes to export settings as text files
void Export_General_Settings ();
void Export_WG_Settings ();

// function prototype to generate words given the previously loaded files
void Generate_Words (clock_t time);
