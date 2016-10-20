#pragma once
#include <iostream>
#include <string>

using namespace std;

class Student{
    
private:
    string StudentID, Name, Address, PhoneNumber;
    static int CompareCount;
    
public:
    Student(string StudentIDIn, string NameIn, string AddressIn, string PhoneNumberIn);
    ~Student(void);
    string toString();
    string getStudentID();
    string getName();
    string getAddress();
    string getPhoneNumber();
    int getCompareCount();
    void addToCount();
    void setCompareCount(int TotalCount);
    void ClearCount();
    bool operator < (Student s) const {
        CompareCount++;
        return StudentID < s.StudentID;
    }
    bool operator == (Student s) const {
        CompareCount++;
        if(StudentID==s.StudentID){
            return true;
        }
        return false;
    }
};