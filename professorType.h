#ifndef PROFESSORTYPE_H
#define PROFESSORTYPE_H

#include "personType.h"
#include "courseType.h"
#include <vector>

class professorType : public personType {
private:
    std::string professorID;
    std::string department;
    std::string degree;
    std::vector<courseType*> courses;

public:
    // Constructors
    professorType();
    professorType(std::string fName, std::string lName, 
                  std::string professorID, std::string department, 
                  std::string degree);
    
    // Getters
    std::string getProfessorID() const;
    std::string getDepartment() const;
    std::string getDegree() const;
    const std::vector<courseType*>& getCourses() const;

    // Setters
    void setProfessorID(std::string id);
    void setDepartment(std::string department);
    void setDegree(std::string degree);

    // Course management
    bool assignCourse(courseType* course);
    bool removeCourse(courseType* course);

    // Pure virtual implementation
    void print() const override;
};

// Constructors
professorType::professorType() : 
    personType(), professorID(""), department(""), degree("") {}

professorType::professorType(std::string fName, std::string lName, 
                             std::string professorID, std::string department, 
                             std::string degree) :
    personType(fName, lName), professorID(professorID), 
    department(department), degree(degree) {}

// Getters
std::string professorType::getProfessorID() const { return professorID; }
std::string professorType::getDepartment() const { return department; }
std::string professorType::getDegree() const { return degree; }
const std::vector<courseType*>& professorType::getCourses() const { return courses; }

// Setters
void professorType::setProfessorID(std::string id) { professorID = id; }
void professorType::setDepartment(std::string dept) { department = dept; }
void professorType::setDegree(std::string deg) { degree = deg; }

// Course management
bool professorType::assignCourse(courseType* course) {
    if (courses.size() < 5 && course != nullptr) {
        courses.push_back(course);
        return course->addInstructor();
    }
    return false;
}

bool professorType::removeCourse(courseType* course) {
    if (course == nullptr) return false;
    
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        if (*it == course) {
            courses.erase(it);
            course->removeInstructor();
            return true;
        }
    }
    return false;
}

// Print implementation
void professorType::print() const {
    std::cout << "PROFESSOR INFORMATION\n"
              << "---------------------\n";
    printBasicInfo();
    
    std::cout << "Professor ID: " << professorID << "\n"
              << "Department: " << department << "\n"
              << "Degree: " << degree << "\n"
              << "Assigned Courses (" << courses.size() << "):\n";
    
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
    std::cout << "---------------------\n";
}

#endif // PROFESSORTYPE_H
