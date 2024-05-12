#include <iostream>
#include <string.h>
using namespace std;

class Students {
    friend ostream& operator<<(ostream& o, const Students& s);
private:
    string name;
    string id;
    char classification;
public:
Students();
explicit Students(string n,string i, char c );
string GetID();
//getters and setters for each private member
};
class Roster {
    friend ostream& operator<<(ostream& o, const Roster& ros);
private:
    Students* contents;
    int size;
    int capacity;
public:
Roster();
~Roster();
Roster(const Roster& r);
Roster& operator=(const Roster& r);
void Add(const Students& s);
Students Remove(string i);
Students& Get(int i) const;
int GetSize() const;
};
class Course {
    friend ostream& operator<<(ostream& o, const Course& c);
private:
    string name;
    string code;
    Roster roster;
public:
Course(string n, string c);
Course();
Course(const Course& other);
Course& operator=(const Course& other);
string GetName();
Roster& GetRoster();
};
