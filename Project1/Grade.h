#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Grade {
public:
    Grade(string InClassName, string InClassGrade, string InGradeID);
    ~Grade(void);
    string getClassName();
    string getGrade();
    string getGradeID();
    double getTotalNumberOfClasses(string IDForClasses);
    string toStringGrade();
    bool operator < (Grade g) const;
    
private:
    string ClassName, ClassGrade, GradeID;

};