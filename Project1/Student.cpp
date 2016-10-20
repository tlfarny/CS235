#include "Student.h"
#include <algorithm>
#include <sstream>

Student::Student(string inStudentID, string inName, string inAddress, string inPhoneNumber){
    StudentID = inStudentID;
    Name = inName;
    Address = inAddress;
    PhoneNumber = inPhoneNumber;
}

Student::~Student(void){
}

string Student::getName(){
    return Name;
}

string Student::getStudentID(){
    return StudentID;
}

string Student::getPhoneNumber(){
    return PhoneNumber;
}

string Student::getAddress(){
    return Address;
}

string Student::getCourseGrade(int Iterator){
    string GradeToReturn = CourseHistory[Iterator].getGrade();
    return GradeToReturn;
}

double Student::getTotalNumberCourses(){
    TotalClassNumber = CourseHistory.size();
    return TotalClassNumber;
}

void Student::SortGrades(){
    sort(CourseHistory.begin(), CourseHistory.end());
}

double Student::getGPA(){
    return GPA;
}

void Student::AddACourse(string ClassName, string ClassGrade, string GradeID){
    CourseHistory.push_back(Grade(ClassName, ClassGrade, GradeID));
}

string Student::ShowCourseHistory(int Iterator){
    string StringToReturn = CourseHistory[Iterator].toStringGrade();
    return StringToReturn;
}

void Student::SetGPA(double inGPA){
    GPA = inGPA;
}

string Student::toString(){
    stringstream ss;
    ss<<Name<<endl;
    ss<<StudentID<<endl;
    ss<<PhoneNumber<<endl;
    ss<<Address<<endl;
    return ss.str();
}

bool Student::operator < (Student s) const {
    return StudentID < s.StudentID;
}