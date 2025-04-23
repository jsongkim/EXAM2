#ifndef COURSETYPE_H
#define COURSETYPE_H

#include <iostream>
#include <string>

class courseType {
private:
    std::string sectionID;
    std::string title;
    std::string days;
    std::string time;
    std::string room;
    int cap;
    int enrolled;
    int num_instructors;
    static int census;

public:
    // Constructors
    courseType();
    courseType(std::string sectionID, std::string title, std::string days, 
               std::string time, std::string room, int cap);
    
    // Static method to get census
    static int getCensus();

    // Getters
    std::string getSectionID() const;
    std::string getTitle() const;
    std::string getDays() const;
    std::string getTime() const;
    std::string getRoom() const;
    int getCap() const;
    int getEnrolled() const;
    int getNumInstructors() const;
    
    // Setters
    void setSectionID(std::string id);
    void setTitle(std::string title);
    void setDays(std::string days);
    void setTime(std::string time);
    void setRoom(std::string room);
    void setCap(int cap);
    
    // Enrollment management
    bool enrollStudent();
    bool dropStudent();
    bool addInstructor();
    bool removeInstructor();

    // Print method
    void print() const;
};

// Initialize static member
int courseType::census = 0;

// Constructors
courseType::courseType() : 
    sectionID(""), title(""), days(""), time(""), room(""), cap(0), enrolled(0), num_instructors(0) {}

courseType::courseType(std::string sectionID, std::string title, std::string days, 
                       std::string time, std::string room, int cap) :
    sectionID(sectionID), title(title), days(days), time(time), room(room), 
    cap(cap), enrolled(0), num_instructors(0) {}

// Print implementation
void courseType::print() const {
    std::cout << "Course Information\n";
    std::cout << "------------------\n";
    std::cout << "Section ID: " << sectionID << "\n";
    std::cout << "Title: " << title << "\n";
    std::cout << "Days: " << days << "\n";
    std::cout << "Time: " << time << "\n";
    std::cout << "Room: " << room << "\n";
    std::cout << "Capacity: " << cap << "\n";
    std::cout << "Enrolled: " << enrolled << "\n";
    std::cout << "Instructors: " << num_instructors << "\n";
    std::cout << "------------------\n";
}

// Static method
int courseType::getCensus() {
    return census;
}

// Getters
std::string courseType::getSectionID() const { return sectionID; }
std::string courseType::getTitle() const { return title; }
std::string courseType::getDays() const { return days; }
std::string courseType::getTime() const { return time; }
std::string courseType::getRoom() const { return room; }
int courseType::getCap() const { return cap; }
int courseType::getEnrolled() const { return enrolled; }
int courseType::getNumInstructors() const { return num_instructors; }

// Setters
void courseType::setSectionID(std::string id) { sectionID = id; }
void courseType::setTitle(std::string title) { this->title = title; }
void courseType::setDays(std::string days) { this->days = days; }
void courseType::setTime(std::string time) { this->time = time; }
void courseType::setRoom(std::string room) { this->room = room; }
void courseType::setCap(int cap) { this->cap = cap; }

// Enrollment management
bool courseType::enrollStudent() {
    if (enrolled < cap) {
        enrolled++;
        census++;
        return true;
    }
    return false;
}

bool courseType::dropStudent() {
    if (enrolled > 0) {
        enrolled--;
        census--;
        return true;
    }
    return false;
}

bool courseType::addInstructor() {
    num_instructors++;
    return true;
}

bool courseType::removeInstructor() {
    if (num_instructors > 0) {
        num_instructors--;
        return true;
    }
    return false;
}

#endif // COURSETYPE_H

