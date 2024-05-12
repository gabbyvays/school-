#include "school.h"
#include <iostream>
#include <string.h>
using namespace std;
//===============================-- Students --===================
ostream& operator<<(ostream& o, const Students& s)
{
    o << s.name <<endl;
    o << s.id << endl;
    o << s.classification <<endl;
    return o;
}

Students::Students()
{
    name = "";
    id = "";
    classification = '\n';
}

Students::Students(string n,string i, char c )
{
    name = n;
    id = i;
    classification = c;
}
string Students::GetID()
{
    return id;
}

//===============================-- Roster --====================

ostream& operator<<(ostream& o, const Roster& ros)
{
    for(int i = 0; i < ros.GetSize(); i++) {
        o << i + 1 << ". " << ros.Get(i) << endl;
    }
    return o;
}
Roster::Roster()
{
    capacity = 5;
    size = 0;
    contents = new Students[capacity];
}

Roster::~Roster() {
    delete [] contents;

}

Roster::Roster(const Roster& r)
{
    capacity = r.capacity;
    size = r.size;
    contents = new Students[capacity];
    for(int j = 0; j < size; j++) {
        contents[j] = r.contents[j];
    }
}

Roster& Roster::operator=(const Roster& r)
{
    capacity = r.capacity;
    size = r.size;
    delete [] contents;
    contents = new Students[capacity];
    for(int j = 0; j < size; j++) {
        contents[j] = r.contents[j];
    }
    return *this;
}

void Roster::Add(const Students& s)
{
    if(size == capacity)
    {
        capacity += 5;
        Students* temp = new Students[capacity];
        for(int i = 0; i < size; i++) {
            temp[i] = contents[i];
        }
        delete [] contents;
        contents = temp;
    }
    contents[size] = s;
    size++;
}

Students Roster::Remove(string i)
{
    int removed;
    for (int j = 0; j < size; j++) {
        if (contents[j].GetID() == i) {
            removed = j;
            break; // Found the student to remove
        }
    }
    Students removed_Student = contents[removed];

    for (int j = removed; j < size - 1; j++) {
        contents[j] = contents[j + 1];
    }

    size--;
    return removed_Student;
}

Students& Roster::Get(int i) const {
    return contents[i];
}
int Roster::GetSize() const
{
    return size;
}

//===============================-- Course --====================

ostream& operator<<(ostream& o, const Course& c)
{
    o << "Course Details:" << endl;
    o << "Name: " << c.name << endl;
    o << "Code: " << c.code << endl;
    o << c.roster;

    return o;
}

Course::Course(string n, string c)
{
    name = n;
    code = c;
}

Course::Course()
{
    name = "";
    code = "";
}

Course::Course(const Course& other)
{
    roster = other.roster;
    name = other.name;
    code = other.code;
}

Course& Course::operator=(const Course& other)
{
    roster = other.roster;
    name = other.name;
    code = other.code;

    return *this;
}

string Course::GetName()
{
    return name;
}

Roster& Course::GetRoster()
{
    return roster;
}

