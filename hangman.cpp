#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Include the algorithm header for std::find

using namespace std;

// Function to print the current state of the word
void displayWord(const string& secretWord, const vector<char>& guessedLetters) {
    for (char letter : secretWord) {
        if (find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end()) {
            cout << letter << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

// Function to check if the player has guessed the entire word
bool isWordGuessed(const string& secretWord, const vector<char>& guessedLetters) {
    for (char letter : secretWord) {
        if (find(guessedLetters.begin(), guessedLetters.end(), letter) == guessedLetters.end()) {
            return false;
        }
    }
    return true;
}

int main() {
    // List of words for the game with associated synonyms
    vector<pair<string, vector<string>>> wordsWithSynonyms = {
        {"programming", {"coding", "software development", "coding"}},
        {"hangman", {"guessing game", "word puzzle", "word game"}},
        {"computer", {"electronic device", "machine", "PC"}},
        {"cplusplus", {"programming language", "C++", "software language"}},
        {"developer", {"software creator", "programmer", "coder"}},
        {"learning", {"acquiring knowledge", "study", "education"}}
    };

    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    // Select a random word and its associated synonyms from the list
    int randomIndex = rand() % wordsWithSynonyms.size();
    string secretWord = wordsWithSynonyms[randomIndex].first;
    vector<string> synonyms = wordsWithSynonyms[randomIndex].second;

    // Randomly select one synonym to display as a hint
    int randomSynonymIndex = rand() % synonyms.size();
    string hint = synonyms[randomSynonymIndex];

    // Vector to store guessed letters
    vector<char> guessedLetters;

    // Maximum number of incorrect guesses allowed
    const int maxIncorrectGuesses = 6;
    int incorrectGuesses = 0;

    cout << "Welcome to Hangman!" << endl;
    cout << "Hint: Synonyms for the word - " << hint << endl;

    while (incorrectGuesses < maxIncorrectGuesses) {
        cout << "\nCurrent Word: ";
        displayWord(secretWord, guessedLetters);

        // Display guessed letters
        if (!guessedLetters.empty()) {
            cout << "Guessed Letters: ";
            for (char letter : guessedLetters) {
                cout << letter << " ";
            }
            cout << endl;
        }

        // Get a guess from the player
        cout << "Enter a letter: ";
        char guess;
        cin >> guess;

        // Convert the guess to lowercase
        guess = tolower(guess);

        // Check if the letter has already been guessed
        if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            cout << "You already guessed that letter. Try again." << endl;
            continue;
        }

        // Add the letter to the guessed letters vector
        guessedLetters.push_back(guess);

        // Check if the guessed letter is in the secret word
        if (secretWord.find(guess) != string::npos) {
            cout << "Correct guess!" << endl;

            // Check if the entire word has been guessed
            if (isWordGuessed(secretWord, guessedLetters)) {
                cout << "Congratulations! You guessed the word: " << secretWord << endl;
                break;
            }
        } else {
            cout << "Incorrect guess. Try again." << endl;
            incorrectGuesses++;

            // Display hangman figure
            switch (incorrectGuesses) {
                case 1:
                    cout << "   O" << endl;
                    break;
                case 2:
                    cout << "   O" << endl;
                    cout << "   |" << endl;
                    break;
                case 3:
                    cout << "   O" << endl;
                    cout << "  /|" << endl;
                    break;
                case 4:
                    cout << "   O" << endl;
                    cout << "  /|\\ " << endl;
                    break;
                case 5:
                    cout << "   O" << endl;
                    cout << "  /|\\ " << endl;
                    cout << "  / " << endl;
                    break;
                case 6:
                    cout << "   O" << endl;
                    cout << "  /|\\ " << endl;
                    cout << "  / \\ " << endl;
                    cout << "Game Over! The correct word was: " << secretWord << endl;
                    break;
            }
        }
    }

    return 0;
}
