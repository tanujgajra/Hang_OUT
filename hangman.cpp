#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

/* FILE TO SAVE LEVEL PROGRESS */
const string saveFile = "progress.txt";

/* WORDS */
vector<string> easy = {"cat","dog","sun","bat","pen","car"};
vector<string> medium = {"apple","chair","table","clock","bread","plant"};
vector<string> hard = {"javascript","developer","function","variable"};

struct GameState {
    string difficulty;
    int levelUnlocked;
};

/* LOAD LEVEL */
int loadLevel(const string &difficulty){
    ifstream fin(saveFile);
    string diff;
    int lvl;
    while(fin >> diff >> lvl){
        if(diff == difficulty){
            fin.close();
            return lvl;
        }
    }
    fin.close();
    return 1; // default first level unlocked
}

/* SAVE LEVEL */
void saveLevel(const string &difficulty, int level){
    vector<GameState> data;
    ifstream fin(saveFile);
    string diff;
    int lvl;
    while(fin >> diff >> lvl){
        data.push_back({diff,lvl});
    }
    fin.close();

    bool found = false;
    for(auto &d : data){
        if(d.difficulty == difficulty){
            if(level > d.levelUnlocked) d.levelUnlocked = level;
            found = true;
            break;
        }
    }
    if(!found){
        data.push_back({difficulty,level});
    }

    ofstream fout(saveFile);
    for(auto &d : data){
        fout << d.difficulty << " " << d.levelUnlocked << endl;
    }
    fout.close();
}

/* DISPLAY WORD */
void displayWord(const string &word, const vector<bool> &revealed){
    for(size_t i=0;i<word.size();i++){
        if(revealed[i]) cout << word[i] << " ";
        else cout << "_ ";
    }
    cout << endl;
}

/* CHECK WIN */
bool checkWin(const vector<bool> &revealed){
    return find(revealed.begin(),revealed.end(),false) == revealed.end();
}

/* PLAY LEVEL */
void playLevel(const string &difficulty, int level){
    string word;
    if(difficulty=="easy") word = easy[(level-1)%easy.size()];
    else if(difficulty=="medium") word = medium[(level-1)%medium.size()];
    else word = hard[(level-1)%hard.size()];

    vector<bool> revealed(word.size(),false);
    int attempts = 6;
    int hints = 2;

    while(attempts>0){
        cout << "\nWord: "; displayWord(word,revealed);
        cout << "Attempts left: " << attempts << " | Hints left: " << hints << endl;
        cout << "Guess a letter (or type ? for hint): ";
        char ch;
        cin >> ch;
        if(ch=='?'){
            if(hints>0){
                for(size_t i=0;i<word.size();i++){
                    if(!revealed[i]){ revealed[i]=true; break; }
                }
                hints--;
                continue;
            }else{
                cout << "No hints left!" << endl;
                continue;
            }
        }
        ch = tolower(ch);
        bool correct=false;
        for(size_t i=0;i<word.size();i++){
            if(word[i]==ch){ revealed[i]=true; correct=true; }
        }
        if(!correct){
            attempts--;
            cout << "Wrong guess!" << endl;
        }

        if(checkWin(revealed)){
            cout << "\n🎉 YOU WIN LEVEL " << level << " 🎉" << endl;
            saveLevel(difficulty, level+1); // unlock next
            break;
        }
    }

    if(attempts==0){
        cout << "\n💀 YOU LOSE! Word was: " << word << endl;
    }
}

int main(){
    srand(time(0));
    string name;
    cout << "Enter your name: ";
    getline(cin,name);
    cout << "Welcome " << name << " to Hangman Ultra!" << endl;

    string difficulty;
    cout << "\nSelect difficulty (easy, medium, hard): ";
    cin >> difficulty;

    int unlocked = loadLevel(difficulty);
    cout << "Levels unlocked: " << unlocked << endl;

    int levelChoice;
    cout << "Choose level to play (1-" << unlocked << "): ";
    cin >> levelChoice;
    if(levelChoice>unlocked) levelChoice = unlocked;

    playLevel(difficulty, levelChoice);

    cout << "\nDo you want to play another level? (y/n): ";
    char again;
    cin >> again;
    if(again=='y' || again=='Y'){
        main(); // restart
    }

    cout << "\nThanks for playing!" << endl;
    return 0;
}