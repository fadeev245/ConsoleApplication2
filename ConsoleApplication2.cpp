
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <clocale>
#include <limits>

using namespace std;

struct Student {
    string name;
    string group;
    vector<int> grades;
};

vector<Student> students = {
    {"Ivanov Ivan Ivanovich", "BD-1-25", {5, 5, 5, 5}},
    {"Petrov Petr Sergeevich", "BD-1-25", {4, 4, 5, 4}},
    {"Sidorova Anna Olegovna", "BD-1-25", {5, 5, 5, 5}},
    {"Smirnov Alexey Igorevich", "BD-1-25", {3, 4, 3, 4}},
    {"Kuznetsova Maria Dmitrievna", "GMU-2-24", {5, 4, 5, 5}}
};

vector<string> groups = { "BD-1-25", "GMU-2-24" };

double average(const Student& student) {
    if (student.grades.empty()) {
        return 0.0;
    }

    int sum = 0;

    for (int grade : student.grades) {
        sum += grade;
    }

    return static_cast<double>(sum) / student.grades.size();
}

int readNumber(const string& message, int minimum, int maximum) {
    int number;

    while (true) {
        cout << message;

        if (cin >> number && number >= minimum && number <= maximum) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }

        cout << "Invalid input. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readText(const string& message) {
    string text;

    cout << message;
    getline(cin >> ws, text);

    return text;
}

void showGroups() {
    cout << "\n=== GROUPS ===\n";

    if (groups.empty()) {
        cout << "No groups.\n";
        return;
    }

    for (const string& group : groups) {
        cout << group << '\n';
    }
}

void showStudents() {
    cout << "\n=== STUDENTS ===\n";

    if (students.empty()) {
        cout << "No students.\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(students.size()); i++) {
        cout << i + 1 << ". "
            << students[i].name
            << " | Group: " << students[i].group
            << " | Average: " << fixed << setprecision(2)
            << average(students[i]) << '\n';
    }
}

void addStudent() {
    string name = readText("Enter full name: ");

    showGroups();
    string group = readText("Enter group name: ");

    for (const string& existingGroup : groups) {
        if (existingGroup == group) {
            students.push_back({ name, group, {} });
            cout << "Student added.\n";
            return;
        }
    }

    cout << "Group not found. Student was not added.\n";
}

void editStudent() {
    showStudents();

    if (students.empty()) {
        return;
    }

    int number = readNumber(
        "Student number to edit: ", 1,
        static_cast<int>(students.size())
    );

    students[number - 1].name = readText("Enter new full name: ");

    showGroups();
    string group = readText("Enter new group: ");

    for (const string& existingGroup : groups) {
        if (existingGroup == group) {
            students[number - 1].group = group;
            cout << "Student updated.\n";
            return;
        }
    }

    cout << "Group not found. Name was updated, group unchanged.\n";
}

void deleteStudent() {
    showStudents();

    if (students.empty()) {
        return;
    }

    int number = readNumber(
        "Student number to delete: ", 1,
        static_cast<int>(students.size())
    );

    students.erase(students.begin() + number - 1);
    cout << "Student deleted.\n";
}

void addGroup() {
    string name = readText("Enter new group name: ");

    for (const string& group : groups) {
        if (group == name) {
            cout << "This group already exists.\n";
            return;
        }
    }

    groups.push_back(name);
    cout << "Group added.\n";
}

void editGroup() {
    showGroups();

    if (groups.empty()) {
        return;
    }

    string oldName = readText("Enter group name to change: ");
    bool found = false;

    for (string& group : groups) {
        if (group == oldName) {
            string newName = readText("Enter new group name: ");

            for (const string& other : groups) {
                if (other == newName) {
                    cout << "This group name already exists.\n";
                    return;
                }
            }

            group = newName;

            for (Student& student : students) {
                if (student.group == oldName) {
                    student.group = newName;
                }
            }

            found = true;
            break;
        }
    }

    if (found) {
        cout << "Group updated.\n";
    }
    else {
        cout << "Group not found.\n";
    }
}

void deleteGroup() {
    showGroups();

    string name = readText("Enter group name to delete: ");

    for (const Student& student : students) {
        if (student.group == name) {
            cout << "Cannot delete: this group has students.\n";
            return;
        }
    }

    for (int i = 0; i < static_cast<int>(groups.size()); i++) {
        if (groups[i] == name) {
            groups.erase(groups.begin() + i);
            cout << "Group deleted.\n";
            return;
        }
    }

    cout << "Group not found.\n";
}

void addGrade() {
    showStudents();

    if (students.empty()) {
        return;
    }

    int number = readNumber(
        "Student number: ", 1,
        static_cast<int>(students.size())
    );

    int grade = readNumber("Grade (1-5): ", 1, 5);

    students[number - 1].grades.push_back(grade);
    cout << "Grade added.\n";
}

void editGrade() {
    showStudents();

    if (students.empty()) {
        return;
    }

    int number = readNumber(
        "Student number: ", 1,
        static_cast<int>(students.size())
    );

    Student& student = students[number - 1];

    if (student.grades.empty()) {
        cout << "This student has no grades.\n";
        return;
    }

    cout << "Grades: ";
    for (int i = 0; i < static_cast<int>(student.grades.size()); i++) {
        cout << i + 1 << ")" << student.grades[i] << " ";
    }
    cout << '\n';

    int index = readNumber(
        "Grade number to edit: ", 1,
        static_cast<int>(student.grades.size())
    );

    student.grades[index - 1] = readNumber("New grade (1-5): ", 1, 5);

    cout << "Grade updated.\n";
}

void deleteGrade() {
    showStudents();

    if (students.empty()) {
        return;
    }

    int number = readNumber(
        "Student number: ", 1,
        static_cast<int>(students.size())
    );

    Student& student = students[number - 1];

    if (student.grades.empty()) {
        cout << "This student has no grades.\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(student.grades.size()); i++) {
        cout << i + 1 << ")" << student.grades[i] << " ";
    }
    cout << '\n';

    int index = readNumber(
        "Grade number to delete: ", 1,
        static_cast<int>(student.grades.size())
    );

    student.grades.erase(student.grades.begin() + index - 1);
    cout << "Grade deleted.\n";
}

void studentAverage() {
    showStudents();

    if (students.empty()) {
        return;
    }

    int number = readNumber(
        "Student number: ", 1,
        static_cast<int>(students.size())
    );

    cout << "Average: " << fixed << setprecision(2)
        << average(students[number - 1]) << '\n';
}

void groupAverage() {
    string group = readText("Enter group name: ");

    double sum = 0.0;
    int count = 0;

    for (const Student& student : students) {
        if (student.group == group && !student.grades.empty()) {
            sum += average(student);
            count++;
        }
    }

    if (count == 0) {
        cout << "No graded students in this group.\n";
        return;
    }

    cout << "Group average: " << fixed << setprecision(2)
        << sum / count << '\n';
}

void statistics() {
    string group = readText("Enter group name: ");

    int excellent = 0;
    int good = 0;
    int other = 0;
    int noGrades = 0;

    for (const Student& student : students) {
        if (student.group != group) {
            continue;
        }

        if (student.grades.empty()) {
            noGrades++;
            continue;
        }

        double avg = average(student);

        if (avg >= 4.5) {
            excellent++;
        }
        else if (avg >= 3.5) {
            good++;
        }
        else {
            other++;
        }
    }

    cout << "\nStatistics for " << group << ":\n";
    cout << "Excellent students: " << excellent << '\n';
    cout << "Good students: " << good << '\n';
    cout << "Average below 3.5: " << other << '\n';
    cout << "Without grades: " << noGrades << '\n';
}

int main() {
    setlocale(LC_ALL, "");

    int choice = -1;

    do {
        cout << "\n===== STUDENT GROUP MANAGER =====\n";
        cout << "1. Show students\n";
        cout << "2. Add student\n";
        cout << "3. Edit student\n";
        cout << "4. Delete student\n";
        cout << "5. Show groups\n";
        cout << "6. Add group\n";
        cout << "7. Edit group\n";
        cout << "8. Delete group\n";
        cout << "9. Add grade\n";
        cout << "10. Edit grade\n";
        cout << "11. Delete grade\n";
        cout << "12. Student average\n";
        cout << "13. Group average\n";
        cout << "14. Group statistics\n";
        cout << "0. Exit\n";

        choice = readNumber("Choose menu item: ", 0, 14);

        switch (choice) {
        case 1: showStudents(); break;
        case 2: addStudent(); break;
        case 3: editStudent(); break;
        case 4: deleteStudent(); break;
        case 5: showGroups(); break;
        case 6: addGroup(); break;
        case 7: editGroup(); break;
        case 8: deleteGroup(); break;
        case 9: addGrade(); break;
        case 10: editGrade(); break;
        case 11: deleteGrade(); break;
        case 12: studentAverage(); break;
        case 13: groupAverage(); break;
        case 14: statistics(); break;
        case 0: cout << "Program finished.\n"; break;
        }
    } while (choice != 0);

    return 0;
}
