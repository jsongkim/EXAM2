#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "courseType.h"
#include "professorType.h"
#include "studentType.h"
#include "selectionSort.h"

using namespace std;

// Function prototypes
void loadCourses(ifstream& infile, vector<courseType*>& courses);
void loadProfessors(ifstream& infile, vector<professorType*>& professors, 
                    vector<courseType*>& courses);
void loadStudents(ifstream& infile, vector<studentType*>& students, 
                  vector<courseType*>& courses);
void printAllData(const vector<courseType*>& courses,
                 const vector<professorType*>& professors,
                 const vector<studentType*>& students);
vector<studentType*> getTopStudents(const vector<studentType*>& students, size_t count);

// Helper functions for lookup
courseType* findCourse(const vector<courseType*>& courses, const string& sectionID);
professorType* findProfessor(const vector<professorType*>& professors, const string& professorID);
studentType* findStudent(const vector<studentType*>& students, const string& studentID);

// Safe conversion functions
double safeStod(const string& str, double defaultValue = 0.0);
int safeStoi(const string& str, int defaultValue = 0);

int main() {
    vector<courseType*> courses;
    vector<professorType*> professors;
    vector<studentType*> students;

    ifstream infile("data.txt");
    if (!infile) {
        cerr << "Error: Unable to open data.txt" << endl;
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        if (line == "COURSES_START") {
            loadCourses(infile, courses);
        } else if (line == "PROFESSORS_START") {
            loadProfessors(infile, professors, courses);
        } else if (line == "STUDENTS_START") {
            loadStudents(infile, students, courses);
        }
    }

    infile.close();

    // Sort all lists using selectionSort
    // Sort courses by course code using lambda
    SelectionSort(courses.data(), courses.size(),
        [](courseType* a, courseType* b) {
            return a->getSectionID() < b->getSectionID();
        });

    // Sort professors by last name then first name using operator<
    SelectionSort(professors.data(), professors.size(),
        [](professorType* a, professorType* b) {
            return *a < *b;
        });

    // Sort students by last name then first name using operator<
    SelectionSort(students.data(), students.size(),
        [](studentType* a, studentType* b) {
            return *a < *b;
        });

    // Print all data (now sorted)
    printAllData(courses, professors, students);

    // Get and print top 10 students by GPA
    vector<studentType*> topStudents = getTopStudents(students, 10);
    cout << "\nTOP 10 STUDENTS BY GPA:\n";
    cout << "-----------------------\n";
    for (size_t i = 0; i < topStudents.size(); i++) {
        cout << i + 1 << ". " << topStudents[i]->getFName() << " " << topStudents[i]->getLName() 
             << " (GPA: " << topStudents[i]->getGPA() << ")\n";
    }

    // Print census data
    cout << "\nCENSUS DATA:\n";
    cout << "------------\n";
    cout << "Total courses: " << courses.size() << endl;
    cout << "Total professors: " << professors.size() << endl;
    cout << "Total students: " << students.size() << endl;
    cout << "Total enrollment: " << courseType::getCensus() << endl;

    // Clean up memory
    for (auto course : courses) delete course;
    for (auto professor : professors) delete professor;
    for (auto student : students) delete student;

    return 0;
}

void loadCourses(ifstream& infile, vector<courseType*>& courses) {
    string line;
    while (getline(infile, line)) {
        if (line == "COURSES_END") break;

        istringstream iss(line);
        string sectionID, title, days, time, room, capStr;
        
        getline(iss, sectionID, '|');
        getline(iss, title, '|');
        getline(iss, title, '|'); // title is the third field
        getline(iss, days, '|');
        getline(iss, time, '|');
        getline(iss, room, '|');
        getline(iss, capStr);

        int cap = safeStoi(capStr);
        courses.push_back(new courseType(sectionID, title, days, time, room, cap));
    }
}

void loadProfessors(ifstream& infile, vector<professorType*>& professors, 
                    vector<courseType*>& courses) {
    string line;
    while (getline(infile, line)) {
        if (line == "PROFESSORS_END") break;

        istringstream iss(line);
        string professorID, fName, lName, gender, heightStr, address, dob, department, degree, courseList;
        
        getline(iss, professorID, '|');
        getline(iss, fName, '|');
        getline(iss, lName, '|');
        getline(iss, gender, '|');
        getline(iss, heightStr, '|');
        getline(iss, address, '|');
        getline(iss, dob, '|');
        getline(iss, department, '|');
        getline(iss, degree, '|');
        getline(iss, courseList);

        double height = safeStod(heightStr);
        professorType* prof = new professorType(fName, lName, professorID, department, degree);
        prof->setGender(gender.empty() ? 'U' : gender[0]);
        prof->setHeight(height);
        prof->setAddress(address);
        prof->setDOB(dob);

        professors.push_back(prof);

        // Assign courses
        istringstream courseStream(courseList);
        string courseID;
        while (getline(courseStream, courseID, ',')) {
            if (!courseID.empty()) {
                courseType* course = findCourse(courses, courseID);
                if (course) {
                    prof->assignCourse(course);
                }
            }
        }
    }
}

void loadStudents(ifstream& infile, vector<studentType*>& students, 
                  vector<courseType*>& courses) {
    string line;
    while (getline(infile, line)) {
        if (line == "STUDENTS_END") break;

        istringstream iss(line);
        string studentID, fName, lName, gender, heightStr, address, dob, gpaStr, classification, courseList;
        
        getline(iss, studentID, '|');
        getline(iss, fName, '|');
        getline(iss, lName, '|');
        getline(iss, gender, '|');
        getline(iss, heightStr, '|');
        getline(iss, address, '|');
        getline(iss, dob, '|');
        getline(iss, gpaStr, '|');
        getline(iss, classification, '|');
        getline(iss, courseList);

        double height = safeStod(heightStr);
        double gpa = safeStod(gpaStr);
        studentType* student = new studentType(fName, lName, studentID, gpa, classification);
        student->setGender(gender.empty() ? 'U' : gender[0]);
        student->setHeight(height);
        student->setAddress(address);
        student->setDOB(dob);

        students.push_back(student);

        // Enroll in courses
        istringstream courseStream(courseList);
        string courseID;
        while (getline(courseStream, courseID, ',')) {
            if (!courseID.empty()) {
                courseType* course = findCourse(courses, courseID);
                if (course) {
                    student->addCourse(course);
                }
            }
        }
    }
}

void printAllData(const vector<courseType*>& courses,
                 const vector<professorType*>& professors,
                 const vector<studentType*>& students) {
    cout << "COURSE DATA:\n";
    cout << "------------\n";
    for (const auto& course : courses) {
        course->print();
    }

    cout << "\nPROFESSOR DATA:\n";
    cout << "---------------\n";
    for (const auto& professor : professors) {
        professor->print();
    }

    cout << "\nSTUDENT DATA:\n";
    cout << "-------------\n";
    for (const auto& student : students) {
        student->print();
    }
}

vector<studentType*> getTopStudents(const vector<studentType*>& students, size_t count) {
    vector<studentType*> studentList = students;

    // Sort students by GPA in descending order
    SelectionSort(studentList.data(), studentList.size(), 
        [](studentType* a, studentType* b) { return a->getGPA() > b->getGPA(); });

    if (count > studentList.size()) {
        count = studentList.size();
    }

    return vector<studentType*>(studentList.begin(), studentList.begin() + count);
}

courseType* findCourse(const vector<courseType*>& courses, const string& sectionID) {
    for (auto course : courses) {
        if (course->getSectionID() == sectionID) {
            return course;
        }
    }
    return nullptr;
}

professorType* findProfessor(const vector<professorType*>& professors, const string& professorID) {
    for (auto professor : professors) {
        if (professor->getProfessorID() == professorID) {
            return professor;
        }
    }
    return nullptr;
}

studentType* findStudent(const vector<studentType*>& students, const string& studentID) {
    for (auto student : students) {
        if (student->getStudentID() == studentID) {
            return student;
        }
    }
    return nullptr;
}

double safeStod(const string& str, double defaultValue) {
    if (str.empty()) return defaultValue;
    try {
        return stod(str);
    } catch (const invalid_argument&) {
        cerr << "Warning: Could not convert '" << str << "' to double, using default value " << defaultValue << endl;
        return defaultValue;
    } catch (const out_of_range&) {
        cerr << "Warning: Value '" << str << "' out of range for double, using default value " << defaultValue << endl;
        return defaultValue;
    }
}

int safeStoi(const string& str, int defaultValue) {
    if (str.empty()) return defaultValue;
    try {
        return stoi(str);
    } catch (const invalid_argument&) {
        cerr << "Warning: Could not convert '" << str << "' to int, using default value " << defaultValue << endl;
        return defaultValue;
    } catch (const out_of_range&) {
        cerr << "Warning: Value '" << str << "' out of range for int, using default value " << defaultValue << endl;
        return defaultValue;
    }
}
