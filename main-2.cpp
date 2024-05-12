#include <iostream>
#include "school.h"
#include <string.h>
using namespace std;
void ShowMenu()
{
    cout << "\tWelcome to the School Directory!";
    cout << "\n\tA \tAdd a course";
    cout << "\n\tR \tRemove a course";
    cout << "\n\tL \tList all the courses ";
    cout << "\n\tE \tEnroll a Student";
    cout << "\n \tU \tUnenroll a Student";
    cout << "\n \tM \tSee the Menu";
    cout << "\n\tX \tExit ";
}

char GetAChar(const char* prompt)
// Prompt the user and get a single character,
// discarding the Return character.
// Used in GetCommand.
{
    char option;			// the char to be returned

    cout << prompt;		// Prompt the user
    cin >> option;			// Get a char,
    option = toupper(option);	// and convert it to uppercase
    cin.get();				// Discard newline char from input.
    return option;
}

bool Legal(char s)
// Determine if a particular character, c, corresponds
// to a legal menu command.  Returns true if legal, false if not.
// Used in GetCommand.
{
    return	((s == 'A') || (s == 'R') || (s == 'E') || (s == 'L') ||
               (s == 'U') || (s == 'M') || (s == 'X'));
}

char GetCommand()
{
    char cmd = GetAChar("\n\n>");

    while (!Legal(cmd))
    {
        cout << "\nIllegal command, please try again . . .";
        ShowMenu();
        cmd = GetAChar("\n\n>");
    }
    return cmd;
}
int main() {
    int maxcourses = 5;
    int numcourses = 0;
    Course* courses = new Course[maxcourses];
    Course newCourse;
    int itemIndex = -1;
    int studentIndex = -1;
    string class_name, student_name, code;
    string id;
    char classify;
    ShowMenu();				// Display the menu.
    char command;			// menu command entered by user
    do {
        command = GetCommand();        // Retrieve a command.
        switch (command) {
            case 'A':

                cout << "Enter the course name: ";
                getline(cin, class_name);
                cin.ignore();
                cout << "\nEnter the course code: ";
                cin >> code;

                if(numcourses == maxcourses)
                {
                    numcourses += 5;
                    Course* temp = new Course[maxcourses];
                    cout << "Array being resized to " << maxcourses << " allocated spots"<<endl;
                    for(int i = 0; i < numcourses; i++) {
                        temp[i] = courses[i];
                    }
                    delete [] courses;
                    courses = temp;
                }

                newCourse = Course(class_name, code);
                courses[numcourses] = newCourse;
                numcourses++;

                break;

            case 'R':
                cout << "\tType the course name you would like to be removed, followed by <Enter>: ";
                cin >> class_name;

                for (int i = 0; i < numcourses; i++) {    // Look at each entry.
                    if (courses[i].GetName() == class_name) {
                        itemIndex = i;        // If found, return position and exit.
                        //break;
                    }
                }
                if (itemIndex != -1){
                    courses[itemIndex] = courses[numcourses - 1];
                    numcourses--;
                    cout << "Course removed from inventory. " <<endl;
                }else{
                    cout << "Course not found in inventory. " <<endl;
                }
                break;
            case 'L':
                if (numcourses > 0 )
                {
                    for(int i = 0; i < numcourses; i++)
                    {
                        cout << courses[i] << endl;
                    }
                }else {
                    cout << "Inventory is empty."<<endl;
                }
                break;
            case 'E':
                cout << "Type the name of the student you would like to enroll, followed by <Enter>: ";
                getline(cin, student_name);
                cin.ignore();
                cout << "Type the id of the student you would like to enroll, followed by <Enter>: ";
                getline(cin, id);
                cin.ignore();
                cout << "Type the classification of the student you would like to enroll, followed by <Enter>";
                cin >> classify;
                cin.ignore();
                cout << "Pick which class you would like " << student_name << " to be enrolled in: ";
                getline(cin, class_name);
                for(int i = 0; i < numcourses; i++)
                {
                    if(courses[i].GetName() == class_name)
                    {
                        itemIndex = i;
                        break;
                    }
                }
                if (itemIndex != -1) {
                    // The course exists, enroll the student
                    Students student(student_name, id, classify);
                    courses[itemIndex].GetRoster().Add(student);
                    cout << student_name << " enrolled in " << class_name << " successfully." << endl;
                } else {
                    // The course doesn't exist
                    cout << "The course " << class_name << " doesn't exist. Cannot enroll the student." << endl;
                }
                break;
            case 'U':
                cout << "Type the id of the student you would like to unenroll, followed by <Enter>: ";
                getline(cin, id);
                cout << "Pick which class you would like the student to be unenrolled in, followed by <Enter>:  ";
                getline(cin, class_name);
                for(int i = 0; i < numcourses; i++)
                {
                    if(courses[i].GetName() == class_name)
                    {
                        itemIndex = i;
                        break;
                    }
                }
                if (itemIndex != -1) {
                    for(int j = 0; j < courses[itemIndex].GetRoster().GetSize(); j++)
                    {
                        if (courses[itemIndex].GetRoster().Get(j).GetID() == id) {
                            studentIndex = j;
                            break;
                    }
                }if (studentIndex != -1) {
                        // Unenroll the student from the course
                        Students unenrolledStudent = courses[itemIndex].GetRoster().Remove(id);
                        cout << unenrolledStudent << " unenrolled from " << class_name << " successfully." << endl;
                    } else {
                        cout << "Student with ID " << id << " not found in the roster of " << class_name << "." << endl;
                    }
                } else {
                    cout << "The course " << class_name << " doesn't exist. Cannot unenroll the student." << endl;
                }

                break;
            case 'M':
                ShowMenu();
                break;
            case 'X':
                break;
        }
    }
    while (command != 'X');
    return 0;

}
