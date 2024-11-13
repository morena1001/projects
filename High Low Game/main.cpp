#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

#include <stdio.h>

using namespace std;

bool is_digits (string &str);

int main () {
    srand (static_cast<int> (time (NULL)));

    int targetNumber = rand () % 100;
    char key;
    // string key;

    cout << "Let's play a Number Guessing Game!\nPress Enter to continue...";
    // cin >> key;
    // cout << "\n";
    key = getc (stdin);
    printf ("\n");

    vector<int> guesses;
    bool correct = false;
    string input;
    int guess;
    
    while (!correct) {
        printf ("Guess a number between 1 and 100: ");
        cin >> input;
        
        if (!is_digits (input)) {
            continue;
        }
        guess = stoi (input);

        guesses.push_back (guess);

        if (guesses.size() == 3) {
            break;
        }

        if (guess == targetNumber) {
            correct = true;
            break;
        } else if (guess < targetNumber) {
            cout << "Your guess is too low. Try again\n";
        } else {
            cout << "Your guess is too high. Try again\n";
        }
    }

    if (correct) {
        cout << "\nCongrats!!! You were correct!\n";
    } else {
        cout << "\nYOU SUCK :(\n";
        cout << targetNumber << "\n";
    }
}

bool is_digits (string &str) {
    for (char ch : str) {
        if (!isdigit (ch))      return false;
    }

    return true;
}
