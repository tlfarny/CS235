#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <list>
#include <sstream>
#include <fstream>
#include <set>

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


void ImportDocument(string DocName,map<string, list<int> >& MisspelledWords, set<string>& Dictionary){
    vector<string> WordVector;
    ifstream DocumentIn;
    string LineIn, Word;
    int LineNumber=0;
    DocumentIn.open(DocName);
    while (getline(DocumentIn, LineIn)) {
        list<int> Locations;
        AlphaChecker(LineIn);
        AlphaLower(LineIn);
        LineNumber++;
        stringstream WordToCheck(LineIn);
        while (WordToCheck>>Word) {
            WordVector.push_back(Word);
        }
        for (int i=0; WordVector.size()>i; i++) {
            if (Dictionary.count(WordVector[i])==0){
                MisspelledWords[WordVector[i]].push_back(LineNumber);
            }
        }
        while (WordVector.size()>0) {
            WordVector.erase(WordVector.begin());
        }
    }
    DocumentIn.close();
}  //6

string OutputMisspelledWords(map<string, list<int> >& MisspelledWords){
    stringstream ss;
    typedef map<string, list<int>>::const_iterator MapIterator;
    for(MapIterator iter  = MisspelledWords.begin(); iter !=MisspelledWords.end(); iter++){
        ss<<iter->first<<":";
        //list<int> temp = iter -> second;
        typedef list<int>::const_iterator ListIterator;
        for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++){
             ss << " " << *list_iter;
        }
        ss<<endl;
    }
    return ss.str();
}

int main(int argc, const char * argv[]){
    set<string> Dictionary;
    map<string, list<int> > MisspelledWords;
    ofstream OutFile;
    ImportDictionary(argv[1], Dictionary);
    ImportDocument(argv[2], MisspelledWords, Dictionary);
    OutFile.open(argv[3]);
    OutFile<<OutputMisspelledWords(MisspelledWords);
    OutFile.close();
    return 0;
}
