#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>

using namespace std;

// Hangman drawing
void drawHangman(int attempts) {
    switch(attempts) {
        case 6:
            cout << "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n";
            break;
        case 5:
            cout << "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n";
            break;
        case 4:
            cout << "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n";
            break;
        case 3:
            cout << "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n";
            break;
        case 2:
            cout << "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n";
            break;
        case 1:
            cout << "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n";
            break;
        case 0:
            cout << "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n";
            break;
    }
}

int main() {
    const int NUM_WORDS = 5;
    string words[NUM_WORDS] = {"apple", "banana", "computer", "programming", "hangman"};
    
    srand(time(0));
    int index = rand() % NUM_WORDS;
    string word = words[index];

    cout << "DEBUG Word: " << word << endl;

    string guessed = "";
    for (int i = 0; i < word.length(); i++) {
    guessed += '_';
    }
    //guessed[word.length()] = '\0';  // null terminate
    guessed += '\0';
    string usedLetters = "";
    string wrongLetters = "";

    int attempts = 6;
    char guess;
    bool found;

    cout << "\n=== HANGMAN GAME ===\n";

    while (attempts > 0 && guessed != word) {
        drawHangman(attempts);

        cout << "\nWord: ";
        for (char c : guessed) cout << c << " ";

        cout << "\nUsed letters: " << usedLetters;
        cout << "\nWrong letters: " << wrongLetters;

        cout << "\nAttempts left: " << attempts;
        cout << "\nEnter a letter: ";
        cin >> guess;

        guess = tolower(guess);

        // ✅ LOOP METHOD instead of find()
        bool alreadyUsed = false;
        for (char c : usedLetters) {
            if (c == guess) {
                alreadyUsed = true;
                break;
            }
        }

        if (alreadyUsed) {
            cout << "Already guessed!\n";
            continue;
        }

        usedLetters += guess;
        found = false;

        for (int i = 0; i < word.length(); i++) {
            if (word[i] == guess) {
                guessed[i] = guess;
                found = true;
            }
        }

        if (!found) {
            attempts--;
            wrongLetters += guess;
            cout << "Wrong guess!\n";
        } else {
            cout << "Correct guess!\n";
        }
    }

    if (guessed == word) {
        cout << "\nYou Won! Word: " << word << endl;
    } else {
        drawHangman(0);
        cout << "\nGame Over! Word: " << word << endl;
    }

    return 0;
}