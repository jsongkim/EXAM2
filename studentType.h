#ifndef STUDENTTYPE_H
#define STUDENTTYPE_H

#include "personType.h"
#include "courseType.h"
#include <vector>

class studentType : public personType {
private:
    std::string studentID;
    double GPA;
    std::string classification;
    std::vector<courseType*> courses;
    static int studentCount;

public:
    // Constructors
    studentType();
    studentType(std::string fName, std::string lName, 
                std::string studentID, double GPA, 
                std::string classification);
    
    // Destructor
    virtual ~studentType();

    // Static method
    static int getStudentCount();

    // Getters
    std::string getStudentID() const;
    double getGPA() const;
    std::string getClassification() const;
    const std::vector<courseType*>& getCourses() const;

    // Setters
    void setStudentID(std::string id);
    void setGPA(double gpa);
    void setClassification(std::string classification);

    // Course management
    bool addCourse(courseType* course);
    bool dropCourse(courseType* course);

    // Pure virtual implementation
    void print() const override;
};

// Initialize static member
int studentType::studentCount = 0;

// Constructors
studentType::studentType() : 
    personType(), studentID(""), GPA(0.0), classification("") {
    studentCount++;
}

studentType::studentType(std::string fName, std::string lName, 
                         std::string studentID, double GPA, 
                         std::string classification) :
    personType(fName, lName), studentID(studentID), GPA(GPA), 
    classification(classification) {
    studentCount++;
}

// Destructor
studentType::~studentType() {
    studentCount--;
}

// Static method
int studentType::getStudentCount() {
    return studentCount;
}

// Getters
std::string studentType::getStudentID() const { return studentID; }
double studentType::getGPA() const { return GPA; }
std::string studentType::getClassification() const { return classification; }
const std::vector<courseType*>& studentType::getCourses() const { return courses; }

// Setters
void studentType::setStudentID(std::string id) { studentID = id; }
void studentType::setGPA(double gpa) { GPA = gpa; }
void studentType::setClassification(std::string classification) { 
    this->classification = classification; 
}

// Course management
bool studentType::addCourse(courseType* course) {
    if (courses.size() < 3 && course != nullptr) {
        courses.push_back(course);
        return course->enrollStudent();
    }
    return false;
}

bool studentType::dropCourse(courseType* course) {
    if (course == nullptr) return false;
    
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        if (*it == course) {
            courses.erase(it);
            course->dropStudent();
            return true;
        }
    }
    return false;
}

// Print implementation
void studentType::print() const {
    std::cout << "STUDENT INFORMATION\n"
              << "-------------------\n";
    printBasicInfo();
    
    std::cout << "Student ID: " << studentID << "\n"
              << "GPA: " << GPA << "\n"
              << "Classification: " << classification << "\n"
              << "Enrolled Courses (" << courses.size() << "):\n";
    
    if (courses.empty()) {
        std::cout << "  None\n";
    } else {
        for (const auto& course : courses) {
            if (course) {
                std::cout << "  - " << course->getTitle() 
                          << " (Section: " << course->getSectionID() << ")\n";
            }
        }
    }
    std::cout << "-------------------\n";
}

#endif // STUDENTTYPE_H
