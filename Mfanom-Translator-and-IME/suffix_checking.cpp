#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector <string> dictionary;

void return_syllables (string word);

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
    cout << "Input characters to get syllables that start with that suffix:\n";
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
                return_syllables (word);
                cout << endl;
            }
        }
    }
}

void return_syllables (string word)
{
    for (int i = 0; i < dictionary.size (); i++)
    {
        if (dictionary [i].find (word) == 0)
        {
            cout << dictionary [i] << endl;
        }
    }
}