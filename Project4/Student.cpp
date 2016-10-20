#include <sstream>
#include "Student.h"

Student::Student(string StudentIDIn, string NameIn, string AddressIn, string PhoneNumberIn){
    StudentID=StudentIDIn;
    Name=NameIn;
    Address=AddressIn;
    PhoneNumber=PhoneNumberIn;
}

Student::~Student(void){}

string Student::toString(){
    stringstream ss;
    ss<<Name<<endl;
    ss<<StudentID<<endl;
    ss<<Address<<endl;
    ss<<PhoneNumber<<endl;
    return ss.str();
}

string Student::getStudentID(){
    return StudentID;
}

string Student::getName(){
    return Name;
}

string Student::getAddress(){
    return Address;
}

string Student::getPhoneNumber(){
    return PhoneNumber;
}

int Student::getCompareCount(){
    return CompareCount;
}

void Student::addToCount(){
    CompareCount++;
}

void Student::setCompareCount(int TotalCount){
    CompareCount = TotalCount;
}

void Student::ClearCount(){
    CompareCount = 0;
}

int Student::CompareCount = 0;