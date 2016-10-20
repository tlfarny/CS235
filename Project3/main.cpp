#include <math.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <fstream>
#include "Tile.h"


using namespace std;

void AlphaChecker(string& LineIn){
    int i=0;
    while (LineIn[i]) {
        if (isalpha(LineIn[i])) {
        }
        else {
            replace(LineIn.begin(), LineIn.end(), LineIn[i], ' ');
        }
        i++;
    }
}  //4

void AlphaLower(string& LineIn){
    int i=0;
    while (LineIn[i]) {
        LineIn[i] = tolower(LineIn[i]);
        i++;
    }
}  //2

void ImportDictionary(string DictionaryName, set<string>& Dictionary){
    ifstream in;
    string WordToAddToDictionary;
    in.open(DictionaryName);
    while (getline(in, WordToAddToDictionary)) {
        AlphaChecker(WordToAddToDictionary);
        AlphaLower(WordToAddToDictionary);
        Dictionary.insert(WordToAddToDictionary);
    }
    in.close();
}  //2

void ImportBoard(string BoardName, vector<string>& LettersToArray){
    ifstream BoardIn;
    string LetterToAdd;
    BoardIn.open(BoardName);
    while (BoardIn>>LetterToAdd) {
        AlphaChecker(LetterToAdd);
        AlphaLower(LetterToAdd);
        LettersToArray.push_back(LetterToAdd);
    }
}  //2

void FindBoardSize(int& Size, vector<string>& LettersToArray){
    int ArraySize;
    Size = LettersToArray.size();
    ArraySize = sqrt(Size);
    Size = ArraySize;
}  //1

bool CheckDictionaryForWord(string Prefix, set<string>& Dictionary, set<string>& WordsOnBoard){
    set<string>::const_iterator iter = Dictionary.lower_bound(Prefix);
    if (Prefix.size()==0) {
        return true;
    }
    else if (iter==Dictionary.end()) {
        return false;
    }
    else if(*iter==Prefix){
        if (Prefix.size()>3) {
            WordsOnBoard.insert(Prefix);
        }
        return true;
    }
    else{
        string cand = *iter;
        if (cand.substr(0, Prefix.size())==Prefix) {
            return true;
            
        }
        else{
            return false;
            
        }
    }
}  //8

void Find(vector<vector<Tile>>& MyBoard, int r, int c, string WordBeingBuilt, set<string>& Dictionary, set<string>& WordsOnBoard){
    if (r >= MyBoard.size() || c >= MyBoard.size() || r < 0 || c < 0) {
        return;
    }
    if (MyBoard[r][c].getVisited()==true) {
        return;
    }
    WordBeingBuilt.append(MyBoard[r][c].getTile());
    if (CheckDictionaryForWord(WordBeingBuilt, Dictionary, WordsOnBoard)==false) {
        return;
    }
    MyBoard[r][c].setUsed();
    
    Find(MyBoard, (r-1), (c-1), WordBeingBuilt, Dictionary, WordsOnBoard);
    Find(MyBoard, (r-1), c, WordBeingBuilt, Dictionary, WordsOnBoard);
    Find(MyBoard, (r-1), (c+1), WordBeingBuilt, Dictionary, WordsOnBoard);
    Find(MyBoard, r, (c-1), WordBeingBuilt, Dictionary, WordsOnBoard);
    Find(MyBoard, r, (c+1), WordBeingBuilt, Dictionary, WordsOnBoard);
    Find(MyBoard, (r+1), (c-1), WordBeingBuilt, Dictionary, WordsOnBoard);
    Find(MyBoard, (r+1), c, WordBeingBuilt, Dictionary, WordsOnBoard);
    Find(MyBoard, (r+1), (c+1), WordBeingBuilt, Dictionary, WordsOnBoard);
    
    MyBoard[r][c].ClearUsed();
}  //4

void FindWordsOnBoard(vector<vector<Tile>>& MyBoard, set<string>& Dictionary, set<string>& WordsOnBoard){
    for (int r = 0; MyBoard.size()>r; r++) {
        for (int c = 0; MyBoard.size()>c; c++) {
            string Word = "";
            Find(MyBoard, r, c, Word, Dictionary, WordsOnBoard);
        }
    }
}  //5

void PrintBoard(vector<vector<Tile>>& MyBoard, ofstream& OutFile){
    for (int i = 0; MyBoard.size()>i; i++) {
        for (int j = 0; MyBoard.size()>j; j++) {
            if (j==MyBoard.size()-1) {
                OutFile<<MyBoard[i][j].getTile()<<endl;
            }
            else{
                OutFile<<MyBoard[i][j].getTile()<<" ";
            }
        }
    }
    OutFile<<endl;
}  //5

void CreateBoard(int& SIZE, vector<string>& LettersToArray, vector<vector<Tile>>& MyBoard){
    int i=0;
    while (LettersToArray.size()>i) {
        for (int r=0; SIZE>r; r++) {
            vector<Tile> TempVector;
            for (int c=0; SIZE>c; c++) {
                TempVector.push_back(LettersToArray[i]);
                i++;
            }
            MyBoard.push_back(TempVector);
        }
    }
}  //4

void OutputWords(set<string>& WordsOnBoard, ofstream& OutFile){
    for (set<string>::iterator i = WordsOnBoard.begin(); i!= WordsOnBoard.end(); i++) {
        OutFile<<*i<<endl;
    }
}  //2

int main(int argc, const char * argv[]){
    int SIZE;
    set<string> Dictionary;
    vector<string> LettersToArray;
    set<string> WordsOnBoard;
    vector<vector<Tile>> MyBoard;
    ofstream Outfile;
    ImportDictionary(argv[1], Dictionary);
    ImportBoard(argv[2], LettersToArray);
    FindBoardSize(SIZE, LettersToArray);
    CreateBoard(SIZE, LettersToArray, MyBoard);
    FindWordsOnBoard(MyBoard, Dictionary, WordsOnBoard);
    Outfile.open(argv[3]);
    PrintBoard(MyBoard, Outfile);
    OutputWords(WordsOnBoard, Outfile);
}  //1

