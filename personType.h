#ifndef PERSONTYPE_H
#define PERSONTYPE_H

#include <iostream>
#include <string>
#include <vector>

class personType {
protected:
    std::string fName;
    std::string lName;
    std::string address;
    double height;
    std::string dob;
    char gender;
    personType* mother;
    personType* father;
    static int peopleCount;

public:
    // Constructors
    personType();
    personType(std::string fName, std::string lName);
    personType(std::string fName, std::string lName, 
               std::string address, double height, 
               std::string dob, char gender);
    
    // Copy constructor
    personType(const personType& other);
    
    // Destructor
    virtual ~personType();

    // Static method
    static int getPeopleCount();

    // Setters
    void setFName(std::string fName);
    void setLName(std::string lName);
    void setAddress(std::string address);
    void setHeight(double height);
    void setDOB(std::string dob);
    void setGender(char gender);
    void setMother(personType* mother);
    void setFather(personType* father);

    // Getters
    std::string getFName() const;
    std::string getLName() const;
    std::string getAddress() const;
    double getHeight() const;
    std::string getDOB() const;
    char getGender() const;
    personType* getMother() const;
    personType* getFather() const;

    // Pure virtual function
    virtual void print() const = 0;

    // Utility methods
    bool equals(const personType& other) const;

    // Operator overloads
    personType& operator=(const personType& other);
    bool operator==(const personType& other) const;
    bool operator!=(const personType& other) const;
    bool operator>(const personType& other) const;
    bool operator<(const personType& other) const;

    // Friend functions
    friend std::ostream& operator<<(std::ostream& os, const personType& person);
    friend std::istream& operator>>(std::istream& is, personType& person);

protected:
    // Helper method for derived classes
    void printBasicInfo() const {
        std::cout << "Name: " << fName << " " << lName << "\n"
                  << "Address: " << address << "\n"
                  << "Height: " << height << " inches\n"
                  << "DOB: " << dob << "\n"
                  << "Gender: " << gender << "\n"
                  << "Mother: " << (mother ? mother->fName + " " + mother->lName : "unknown") << "\n"
                  << "Father: " << (father ? father->fName + " " + father->lName : "unknown") << "\n";
    }
};

// Initialize static member
int personType::peopleCount = 0;

// Constructors
personType::personType() : 
    fName(""), lName(""), address(""), height(0.0), 
    dob(""), gender('U'), mother(nullptr), father(nullptr) {
    peopleCount++;
}

personType::personType(std::string fName, std::string lName) : 
    fName(fName), lName(lName), address(""), height(0.0), 
    dob(""), gender('U'), mother(nullptr), father(nullptr) {
    peopleCount++;
}

personType::personType(std::string fName, std::string lName, 
                       std::string address, double height, 
                       std::string dob, char gender) :
    fName(fName), lName(lName), address(address), 
    height(height), dob(dob), gender(gender),
    mother(nullptr), father(nullptr) {
    peopleCount++;
}

// Copy constructor
personType::personType(const personType& other) :
    fName(other.fName), lName(other.lName), address(other.address),
    height(other.height), dob(other.dob), gender(other.gender),
    mother(other.mother), father(other.father) {
    peopleCount++;
}

// Destructor
personType::~personType() {
    peopleCount--;
}

// Static method
int personType::getPeopleCount() {
    return peopleCount;
}

// Setters
void personType::setFName(std::string fName) { this->fName = fName; }
void personType::setLName(std::string lName) { this->lName = lName; }
void personType::setAddress(std::string address) { this->address = address; }
void personType::setHeight(double height) { this->height = height; }
void personType::setDOB(std::string dob) { this->dob = dob; }
void personType::setGender(char gender) { this->gender = gender; }
void personType::setMother(personType* mother) { this->mother = mother; }
void personType::setFather(personType* father) { this->father = father; }

// Getters
std::string personType::getFName() const { return fName; }
std::string personType::getLName() const { return lName; }
std::string personType::getAddress() const { return address; }
double personType::getHeight() const { return height; }
std::string personType::getDOB() const { return dob; }
char personType::getGender() const { return gender; }
personType* personType::getMother() const { return mother; }
personType* personType::getFather() const { return father; }

// Utility methods
bool personType::equals(const personType& other) const {
    return (fName == other.fName &&
            lName == other.lName &&
            address == other.address &&
            height == other.height &&
            dob == other.dob &&
            gender == other.gender);
}

// Operator overloads
personType& personType::operator=(const personType& other) {
    if (this != &other) {
        fName = other.fName;
        lName = other.lName;
        address = other.address;
        height = other.height;
        dob = other.dob;
        gender = other.gender;
        mother = other.mother;
        father = other.father;
    }
    return *this;
}

bool personType::operator==(const personType& other) const {
    return equals(other);
}

bool personType::operator!=(const personType& other) const {
    return !(*this == other);
}

bool personType::operator>(const personType& other) const {
    return height > other.height;
}

bool personType::operator<(const personType& other) const {
    return height < other.height;
}

// Friend functions
std::ostream& operator<<(std::ostream& os, const personType& person) {
    os << "Name: " << person.fName << " " << person.lName << "\n"
       << "Address: " << person.address << "\n"
       << "Height: " << person.height << " inches\n"
       << "DOB: " << person.dob << "\n"
       << "Gender: " << person.gender << "\n"
       << "Mother: " << (person.mother ? person.mother->fName + " " + person.mother->lName : "unknown") << "\n"
       << "Father: " << (person.father ? person.father->fName + " " + person.father->lName : "unknown") << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, personType& person) {
    std::cout << "Enter first name: ";
    is >> person.fName;
    std::cout << "Enter last name: ";
    is >> person.lName;
    std::cout << "Enter address: ";
    is.ignore();
    getline(is, person.address);
    std::cout << "Enter height (inches): ";
    is >> person.height;
    std::cout << "Enter date of birth: ";
    is.ignore();
    getline(is, person.dob);
    std::cout << "Enter gender (M/F/U): ";
    is >> person.gender;
    person.mother = nullptr;
    person.father = nullptr;
    return is;
}

#endif // PERSONTYPE_H
