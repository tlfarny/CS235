#pragma once
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include "Grade.h"

using namespace std;

class Student{
    
private:
    string Name, PhoneNumber, StudentID, Address;
    double GPA=0, TotalClassNumber=0;
    vector<Grade> CourseHistory;
    
public:
    Student(string inStudentID, string inName, string inAddress, string inPhoneNumber);
    ~Student(void);
    string getName();
    string getStudentID();
    string getPhoneNumber();
    string getAddress();
    string getCourseGrade(int Iterator);
    double getTotalNumberCourses();
    void SortGrades();
    double getGPA();
    void AddACourse(string ClassName, string ClassGrade, string GradeID);
    string ShowCourseHistory(int Iterator);
    void SetGPA(double GPA);
    string toString();
    bool operator < (Student s) const;
};