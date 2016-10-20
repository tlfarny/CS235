#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <sstream>
#include <fstream>
#include "Student.h"

using namespace std;

void ImportStudents(string Filename, vector<Student>& AllStudents){
    ifstream Filein;
    string StudentID, Name, Address, PhoneNumber;
    Filein.open(Filename);
    while (getline(Filein, StudentID)) {
        getline(Filein, Name);
        getline(Filein, Address);
        getline(Filein, PhoneNumber);
        AllStudents.push_back(Student(StudentID, Name, Address, PhoneNumber));
    }
}  //2

void InitializeSize (vector<int>& Querysize){
    Querysize.push_back(4);
    Querysize.push_back(2);
    Querysize.push_back(1);
}  //1

void ImportQuery(string QueryFile, vector<Student>& AllQueries){
    ifstream FileIn;
    string Query;
    FileIn.open(QueryFile);
    while (getline(FileIn, Query)) {
        Student temp(Query, "Null", "Null", "Null");
        AllQueries.push_back(temp);
    }
}  //2

void SelectionSort(vector<Student>& AllStudents, vector<int>& QuerySize, string Filename, ofstream& OutFile){
    OutFile<<"Selection Sort"<<endl;
    for (int g=0; QuerySize.size()>g; g++) {
        AllStudents.clear();
        ImportStudents(Filename, AllStudents);
        for (int i=0; ((AllStudents.size()/QuerySize[g])-1)>i; i++) {
            int LowestID = i;
            for (int j=i+1; ((AllStudents.size()/QuerySize[g]))>j; j++) {
                if (AllStudents[j]<AllStudents[i]) {
                    LowestID = j;
                }
            }
            Student temp = AllStudents[i];
            AllStudents[i] = AllStudents[LowestID];
            AllStudents[LowestID] = temp;
        }
        if (AllStudents.size()>0) {
            OutFile<<"size: "<<AllStudents.size()/QuerySize[g]<<"    compares: "<<AllStudents[0].getCompareCount()<<endl;
            AllStudents[AllStudents.size()].ClearCount();
        }
    }
}  //6

void InsertionSort(vector<Student>& AllStudents, vector<int>& QuerySize, string Filename, ofstream& OutFile){
    OutFile<<"Insertion Sort"<<endl;
    for (int g=0; QuerySize.size()>g; g++) {
        AllStudents.clear();
        ImportStudents(Filename, AllStudents);
        for (int i=1; (AllStudents.size()/QuerySize[g])>i; i++) {
            Student temp = AllStudents[i];
            int j = i;
            while (j>0 && temp < AllStudents[j-1]) {
                AllStudents[j] = AllStudents[j-1];
                j--;
            }
            AllStudents[j] = temp;
        }
        if (AllStudents.size()>0) {
            OutFile<<"size: "<<AllStudents.size()/QuerySize[g]<<"    compares: "<<AllStudents[0].getCompareCount()<<endl;
            AllStudents[AllStudents.size()].ClearCount();
        }
    }
}  //5

void StandardSort(vector<Student>& AllStudents, vector<int> QuerySize, string Filename, ofstream& OutFile){
    OutFile<<"std::sort"<<endl;
    for (int i=0; QuerySize.size()>i; i++) {
        AllStudents.clear();
        ImportStudents(Filename, AllStudents);
        vector<Student> AllStudentsBySize;
        for (int j = 0; (AllStudents.size()/QuerySize[i])>j; j++) {
            AllStudentsBySize.push_back(AllStudents[j]);
        }
        sort(AllStudentsBySize.begin(), AllStudentsBySize.end());
        if (AllStudentsBySize.size()>0) {
            OutFile<<"size: "<<AllStudentsBySize.size()<<"    compares: "<<AllStudentsBySize[0].getCompareCount()<<endl;
            AllStudentsBySize[0].ClearCount();
        }
    }
}  //4

void ListMaker(list<Student>& AllStudentsList, vector<Student>& AllStudents, int QuerySizeIteration){
    AllStudentsList.clear();
    for (int i = 0; AllStudents.size() / QuerySizeIteration>i; i++) {
        AllStudentsList.push_back(AllStudents[i]);
    }
}  //2

void ListSort(vector<Student>& AllStudents, vector<int>& QuerySize, string Filename, ofstream& OutFile){
    OutFile<<"std::list.sort"<<endl;
    list<Student> AllStudentsList;
    for (int i=0; QuerySize.size()>i; i++) {
        AllStudents.clear();
        ImportStudents(Filename, AllStudents);
        ListMaker(AllStudentsList, AllStudents, QuerySize[i]);
        AllStudentsList.sort();
        if (AllStudents.size()>0) {
            OutFile<<"size: "<<AllStudentsList.size()<<"    compares: "<<AllStudents[0].getCompareCount()<<endl;
            AllStudents[AllStudents.size()].ClearCount();
        }
        
    }
    
}  //3

void ActualLinearSearch(vector<Student>& AllStudentsToSearch, vector<Student>& AllQueriesToSearch){
    for (int j = 0; (AllQueriesToSearch.size())>j ; j++) {
        for (int k=0; AllStudentsToSearch.size()>k; k++) {
            if (AllStudentsToSearch[k]==AllQueriesToSearch[j]) {
                break;
            }
        }
    }
}  //4

void LinearSearch(vector<Student>& AllStudents, vector<int>& QuerySize, vector<Student>& AllQueries, string Filename, ofstream& OutFile){
    OutFile<<"Linear Search"<<endl;
    vector<Student> AllStudentsToSearch;
    vector<Student> AllQueriesToSearch;
    for (int i = 0; QuerySize.size()>i; i++) {
        AllStudentsToSearch.clear();
        AllQueriesToSearch.clear();
        for (int j=0; (AllStudents.size()/QuerySize[i])>j; j++) {
            AllStudentsToSearch.push_back(AllStudents[j]);
        }
        for (int j=0; (AllQueries.size()/QuerySize[i])>j; j++) {
            AllQueriesToSearch.push_back(AllQueries[j]);
        }
        ActualLinearSearch(AllStudentsToSearch, AllQueriesToSearch);
        if (AllStudentsToSearch.size()>0) {
            OutFile<<"size: "<<AllStudentsToSearch.size()<<"    compares: "<<AllStudentsToSearch[0].getCompareCount()/AllQueriesToSearch.size()<<endl;
            AllStudentsToSearch[0].ClearCount();
        }
    }
}  //5

void StandardFind(vector<Student>& AllStudents, vector<int>& QuerySize, vector<Student>& AllQueries, string Filename, ofstream& OutFile){
    OutFile<<"std::find"<<endl;
    AllStudents.clear();
    ImportStudents(Filename, AllStudents);
    for (int i=0; QuerySize.size()>i; i++) {
        vector<Student> AllStudentsBySize;
        vector<Student> AllQueriesToSearch;
        AllStudentsBySize.clear();
        AllQueriesToSearch.clear();
        for (int j = 0; (AllStudents.size()/QuerySize[i])>j; j++) {
            AllStudentsBySize.push_back(AllStudents[j]);
        }
        for (int j=0; (AllQueries.size()/QuerySize[i])>j; j++) {
            AllQueriesToSearch.push_back(AllQueries[j]);
        }
        for (int j=0; AllStudentsBySize.size()>j; j++) {
            find(AllStudentsBySize.begin(), AllStudentsBySize.end(), AllQueriesToSearch[j]);
        }
        if (AllStudentsBySize.size()>0) {
            OutFile<<"size: "<<AllStudentsBySize.size()<<"    compares: "<<AllStudentsBySize[0].getCompareCount()/AllQueriesToSearch.size()<<endl;
            AllStudentsBySize[0].ClearCount();
        }
    }
}  //6

void SetMaker(set<Student>& AllStudentsSet, vector<Student>& AllStudents, int QuerySizeIteration){
    AllStudentsSet.clear();
    for (int i = 0; AllStudents.size() / QuerySizeIteration>i; i++) {
        AllStudentsSet.insert(AllStudents[i]);
    }
    AllStudents[0].ClearCount();
}  //2

void SetFind(vector<Student>& AllStudents, vector<int>& QuerySize, vector<Student>& AllQueries, string Filename, ofstream& OutFile){
    OutFile<<"std::set.find"<<endl;
    set<Student> AllStudentsSet;
    for (int i=0; QuerySize.size()>i; i++) {
        AllStudents.clear();
        ImportStudents(Filename, AllStudents);
        SetMaker(AllStudentsSet, AllStudents, QuerySize[i]);
        for (int j=0; AllQueries.size() / QuerySize[i]>j; j++) {
            AllStudentsSet.find(AllQueries[j]);
        }
        if (AllStudentsSet.size()>0) {
            OutFile<<"size: "<<AllStudentsSet.size()<<"    compares: "<<AllQueries[0].getCompareCount()/(AllQueries.size()/QuerySize[i])<<endl;
            AllQueries[0].ClearCount();
        }
        
    }
}

int main(int argc, const char * argv[]){
    ofstream OutFile;
    vector<int> QuerySize;
    vector<Student> AllStudents;
    vector<Student> AllQueries;
    InitializeSize(QuerySize);
    ImportStudents(argv[1], AllStudents);
    ImportQuery(argv[2], AllQueries);
    OutFile.open(argv[3]);
    SelectionSort(AllStudents, QuerySize, argv[1], OutFile);
    InsertionSort(AllStudents, QuerySize, argv[1], OutFile);
    StandardSort(AllStudents, QuerySize, argv[1], OutFile);
    ListSort(AllStudents, QuerySize, argv[1], OutFile);
    LinearSearch(AllStudents, QuerySize, AllQueries, argv[1], OutFile);
    StandardFind(AllStudents, QuerySize, AllQueries, argv[1], OutFile);
    SetFind(AllStudents, QuerySize, AllQueries, argv[1], OutFile);
    OutFile.close();
}  //1



