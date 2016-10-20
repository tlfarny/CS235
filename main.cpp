#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include "Student.h"

using namespace std;

void GPACalculator(vector<Grade>& GradeList, vector<Student>& StudentList, string StudentID){ //7
    double TotalClassScore=0;
    double TotalNumberOfClasses=0;
    double GPA=0;
    map<string, double> LetterGrades;
    LetterGrades["A"] = 4.0;
    LetterGrades["A-"] = 3.7;
    LetterGrades["B+"] = 3.4;
    LetterGrades["B"] = 3.0;
    LetterGrades["B-"] = 2.7;
    LetterGrades["C+"] = 2.4;
    LetterGrades["C"] = 2.0;
    LetterGrades["C-"] = 1.7;
    LetterGrades["D+"] = 1.4;
    LetterGrades["D"] = 1.0;
    LetterGrades["D-"] = 0.7;
    LetterGrades["E"] = 0.0;
    for (int i=0; GradeList.size()>i; i++) {
        if (GradeList[i].getGradeID()==StudentID) {
            TotalNumberOfClasses++;
            TotalClassScore+=LetterGrades[GradeList[i].getGrade()];
        }
    }
    if (TotalNumberOfClasses==0) {
        GPA=0.00;
    }
    else{
        GPA=TotalClassScore/TotalNumberOfClasses;
    }
    for (int i=0; StudentList.size()>i; i++) {
        if (StudentList[i].getStudentID()==StudentID) {
            StudentList[i].SetGPA(GPA);
        }
    }
} //7

void SortStudents(vector<Student> &StudentList){
    sort(StudentList.begin() , StudentList.end());
}//1

void SortGrades(vector<Grade> &GradeList){
    sort(GradeList.begin(), GradeList.end());
} //1

string ImportStudents(vector<Student> &StudentList, string StudentFile){
    string Name, StudentID, PhoneNumber, Address;
    ifstream StudentsIn;
    StudentsIn.open(StudentFile);
    while (getline(StudentsIn, StudentID)) {
        getline(StudentsIn, Name);
        getline(StudentsIn, Address);
        getline(StudentsIn, PhoneNumber);
        StudentList.push_back(Student(StudentID, Name, Address, PhoneNumber));
    }
    StudentsIn.close();
    stringstream AllStudents;
    if (StudentList.size()>0) {
        sort(StudentList.begin(), StudentList.end());
        for (int i = 0; StudentList.size()>i; i++) {
            AllStudents<<StudentList[i].toString();
        }
    }
    AllStudents<<endl;
    return AllStudents.str();
} //3

string ImportGrades(vector<Grade>& GradeList, string GradeFile){
    string ClassName, ClassGrade, GradeID;
    ifstream GradesIn;
    GradesIn.open(GradeFile);
    while (getline(GradesIn, ClassName)) {
        getline(GradesIn, GradeID);
        getline(GradesIn, ClassGrade);
        GradeList.push_back(Grade(ClassName, ClassGrade, GradeID));
    }
    GradesIn.close();
    stringstream AllGrades;
    sort(GradeList.begin(), GradeList.end());
    for (int i = 0; GradeList.size()>i; i++) {
        AllGrades<<GradeList[i].toStringGrade();
    }
    AllGrades<<endl;
    return AllGrades.str();
} //3

void CalculateGPA(vector<Student>& StudentList,vector<string>& OrderToOutput, vector<Grade> &GradeList){
    for (int i = 0; OrderToOutput.size()>i; i++) {
        GPACalculator(GradeList, StudentList, OrderToOutput[i]);
    }
}  //2

string QueryBuilder(vector<string> &OrderToOutput, vector<Student> &StudentList){
    stringstream OutFile;
    
    for (int i=0; OrderToOutput.size()>i; i++) {
        bool AlreadyQueried = false;
        for (int g = 0; StudentList.size()>g; g++) {
            if (OrderToOutput[i]==StudentList[g].getStudentID() && AlreadyQueried==false) {
                OutFile<<OrderToOutput[i]<<"    ";
                OutFile<<fixed<<setprecision(2)<<StudentList[g].getGPA()<<"    ";
                OutFile<<StudentList[g].getName()<<endl;
                AlreadyQueried=true;
            }
        }
    }
    return OutFile.str();
    
}  //4

string Query(vector<Student> &StudentList, string Queryfile, string OutputFile, vector<Grade> &GradeList){
    ifstream QueryIn;
    string IDToOutput;
    vector<string> OrderToOuput;
    QueryIn.open(Queryfile);
    while (getline(QueryIn, IDToOutput)) {
        OrderToOuput.push_back(IDToOutput);
    }
    QueryIn.close();
    stringstream FileToPrint;
    if (StudentList.size()>0) {
        CalculateGPA(StudentList, OrderToOuput, GradeList);
        FileToPrint<<QueryBuilder(OrderToOuput, StudentList);
    }
    return FileToPrint.str();
}  //3

int main(int argc, char *argv[]){
    string Name, StudentID, PhoneNumber, Address, ClassName, ClassGrade, GradeID;
    vector<Student> StudentList;
    vector<Grade> GradeList;
    ofstream Print;
    Print.open(argv[4]);
    Print<< ImportStudents(StudentList, argv[1]);
    Print<< ImportGrades(GradeList, argv[2]);
    Print<< Query(StudentList, argv[3], argv[4], GradeList);
    Print.close();
    return 0;
}
