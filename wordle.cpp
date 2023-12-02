#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <random>
#include <ctime>
#include <iterator>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main() {
    bool newGame = true, inputValid = false, guessed = false;
    int guesses = 0;
    string inputS;
    vector<string> dictionaryVector;
    unordered_set<string> dictionarySet;

    srand(time(NULL));

    //#section: read dircionary;
    ifstream textSource("wordlist.txt", ifstream::in);

    while (!textSource.eof()) {
        getline(textSource, inputS);
        dictionarySet.insert(inputS);
        dictionaryVector.push_back(inputS);
    }


    while (newGame) {
        //#section: Generate Word
        string goal = dictionaryVector[rand() % dictionaryVector.size()];

        //#section: Game Main
        guessed = false;
        guesses = 0;
        while (!guessed) {
            guesses++;

            //#section: Input Guess
            inputValid = false;
            while (!inputValid) {
                cout << "Please enter your guess (5 letters) or type \"giveup\" to give up: ";
                cin >> inputS;

                for (int i = 0; i < inputS.size(); i++) {inputS[i] = tolower(inputS[i]);}

                if (inputS == "giveup") {cout << "Gave up on " << guesses - 1 << " try" << endl << "The answer is \"" << goal << "\"." << endl; goto giveup;}
                if (inputS.size() != 5) {cout << "Invalid input. Please retry." << endl; continue;}
                if (dictionarySet.find(inputS) == dictionarySet.end()) {cout << "Word not in list." << endl; continue;}
                inputValid = true;
            }

            //#section: Check Letters
            if (goal == inputS) {
                cout << "\033[A\33[2K\rT";
                cout << "Please enter your guess (5 letters) or type \"giveup\" to give up: ";
                cout << "\e[4;32m" << inputS << "\033[0m" <<endl;
                guessed = true; continue;
            } 
            //letterCorrect[i] 0 = grey / 1 = yellow / 2 = green
            vector<int> letterCorrect(5, 0);
            unordered_map<char,int> letterCount;

            int green = 0, yellow = 0;
            for (int i = 0; i < 5; i++) {letterCount[goal[i]]++;}
            for (int i = 0; i < 5; i++) {if (goal[i] == inputS[i]) {green++; letterCorrect[i] = 2; letterCount[goal[i]]--;}}
            for (int i = 0; i < 5; i++) {
                if (letterCorrect[i] == 2) {continue;}
                for (int j = 0; j < 5; j++) {
                    if (letterCount.find(inputS[i]) != letterCount.end() && letterCount[inputS[i]] != 0) {
                        letterCorrect[i] = 1;
                        letterCount[inputS[i]]--;
                    }
                }
            }

            //#section: Print Colours
            cout << "\033[A\33[2K\r";
            cout << "Please enter your guess (5 letters) or type \"giveup\" to give up: ";
            for (int i = 0; i < 5; i++) {
                if (letterCorrect[i] == 2) {cout << "\e[4;32m" << inputS[i] << "\033[0m";}
                else if (letterCorrect[i] == 1) {cout << "\e[4;33m" << inputS[i] << "\033[0m";}
                else {cout << inputS[i];}
            }
            cout << endl;
        }

        cout << "You've guessed the answer in " << guesses << " guesses!" << endl;

        giveup:
        //#section: New Game
        inputValid = false;
        while (!inputValid) {
            cout << "New Game? (Y/N): ";
            cin >> inputS;
            if (inputS == "Y" || inputS == "y") {inputValid = true; newGame = true;}
            else if (inputS == "N" || inputS == "n") {inputValid = true; newGame = false;}
            else {cout << "Invalid input. Please retry." << endl;}
        }
    }


    return 0;    
}