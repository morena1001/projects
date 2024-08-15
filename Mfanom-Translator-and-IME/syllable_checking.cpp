#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector <string> dictionary;
vector <string> syllables;

bool search_for_syllables (string word);

int main ()
{    
    fstream syllable_database;
    syllable_database.open ("syllable_database.txt", ios::in);

    string line;
    while (getline (syllable_database, line)) 
    {
        if (line == "\n")
            continue;

        if (line [line.length () - 1] == '\n')
            line [line.length () - 1] = '\0';
        dictionary.push_back (line);
    }
    syllable_database.close ();
    
    system ("cls");
    cout << "Input word to get syllables:\n";
    while (cin >> line)
    {
        if (line == ".")
            break;

        else
        {
            string word;
            stringstream words (line);

            while (words >> word)
            {
                syllables.clear ();
                string syllables_together = "";
                search_for_syllables (word);
                for (int i = syllables.size () - 1; i >= 0; i--)
                {
                    cout << syllables [i] + "\t";
                    syllables_together += syllables[i];
                    if (syllables_together == word)
                    {
                        cout << endl;
                        syllables_together = "";
                    }
                    cout << endl;
                }
            }
        }
    }
}



bool search_for_syllables (string word)
{
    bool is_word = false;
    if (word == "")     return true;

    for (int i = 1; i < word.length () + 1; i++)
    {
        string substring = word.substr (0, i);
        for (int j = 0; j < dictionary.size (); j++)
        {
            if (substring == dictionary [j])
            {
                string remaining_substring = word.substr (i, word.length ());
                if (search_for_syllables (remaining_substring))
                {
                    syllables.push_back (substring);
                    is_word = true;
                }
            }
        }
    }

    if (!is_word)   return false;
    else    return true;
}