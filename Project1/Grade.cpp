#include "Grade.h"

Grade::Grade(string InClassName, string InClassGrade, string InGradeID){
    ClassName = InClassName;
    ClassGrade = InClassGrade;
    GradeID = InGradeID;
    
}

Grade::~Grade(void){
    
}

string Grade::getClassName(){
    return ClassName;
}

string Grade::getGrade(){
    return ClassGrade;
}

string Grade::getGradeID(){
    return GradeID;
}

double Grade::getTotalNumberOfClasses(string IDForClasses){
    double TotalNumberOfClasses=0;
    return TotalNumberOfClasses;
}

string Grade::toStringGrade(){
    stringstream ss;
    ss<<GradeID<<"    "<<ClassGrade<<"    "<<ClassName<<endl;
    return ss.str();
}

bool Grade::operator < (Grade g) const {
    return GradeID < g.GradeID ||
    (GradeID == g.GradeID && ClassName < g.ClassName) ||
    (GradeID == g.GradeID && ClassName == g.ClassName && ClassGrade < g.ClassGrade);
}