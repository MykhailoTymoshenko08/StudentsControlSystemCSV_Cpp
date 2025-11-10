#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> //setw(num); 15 or 20
#include <vector>
#include <sstream>
using namespace std;

enum class Faculty {
    IT,
    Mathematics,
    Physics,
    History,
    Unknown
};

struct Student {
    int id;
    string name;
    int age;
    Faculty faculty;
};

void commandList();
int getStudentId(const vector<Student>& students);
Faculty stringToFaculty(const string& str);
string facultyToString(Faculty f);
void addStudent(vector<Student>& students);
void loadFromFile(vector<Student>& students, const string& filename);
void saveToFile(const vector<Student>& students, const string& filename);
void saveStudent(const Student& s, const string& filename);
void checkStudentsList(const vector<Student>& students);
void delSrudent(vector<Student>& students, const string& filename);
void searchStudent(const vector<Student>& students);

int getStudentId(const vector<Student>& students) {
    int maxId = 0;
    for (const auto& s : students) {
        if (s.id > maxId) maxId = s.id;
    }
    return maxId + 1;
}

Faculty stringToFaculty(const string& str) {
    if (str == "IT") return Faculty::IT;
    if (str == "Mathematics") return Faculty::Mathematics;
    if (str == "Physics") return Faculty::Physics;
    if (str == "History") return Faculty::History;
    return Faculty::Unknown;
}

string facultyToString(Faculty f) {
    switch (f) {
    case Faculty::IT: return "IT";
    case Faculty::Mathematics: return "Mathematics";
    case Faculty::Physics: return "Physics";
    case Faculty::History: return "History";
    default: return "Unknown";
    }
}

void addStudent(vector<Student>& students, int& nextId) {
    Student s;
    s.id = nextId++;
    cout << "Enter name: ";
    cin >> s.name;
    cout << "Enter age: ";
    cin >> s.age;
    cout << "Enter faculty (IT, Mathematics, Physics, History): ";
    string fac;
    cin >> fac;
    s.faculty = stringToFaculty(fac);
    students.push_back(s);
    cout << "Student added!\n";
}

void loadFromFile(vector<Student>& students, const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error opening file!(try again)\n";
        return;
    }

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string idStr, name, ageStr, facStr;

        getline(ss, idStr, ';');
        getline(ss, name, ';');
        getline(ss, ageStr, ';');
        getline(ss, facStr, ';');

        Student s;
        s.id = stoi(idStr);
        s.name = name;
        s.age = stoi(ageStr);
        s.faculty = stringToFaculty(facStr);

        students.push_back(s);
    }

    fin.close();
}

void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream fout(filename, ios::app);
    if (!fout.is_open()) {
        cout << "Error opening file!\n";
        return;
    }

    for (const auto& s : students) {
        fout << s.id << ";" << s.name << ";" << s.age << ";" << facultyToString(s.faculty) << endl;
    }

    fout.close();
}

void saveStudent(const Student& s, const string& filename) {
    ofstream fout(filename, ios::app);
    if (!fout.is_open()) {
        cout << "Error opening file!\n";
        return;
    }

    fout << s.id << ";" << s.name << ";" << s.age << ";" << facultyToString(s.faculty) << endl;
    fout.close();
}

//void addStudent(vector<Student>& students) {
//    int a = 20;
//    ifstream fin("studentList.txt");
//
//    fin.close();
//
//    ofstream fout("studentList.txt", ios::app); //ios::app to add not to recall file
//    Student s;
//
//    cout << "Enter student's name: ";
//    cin >> s.name;
//    cout << endl << "Enter student's age: ";
//    cin >> s.age;
//    cout << endl << "Enter student's faculty (IT, Mathematics, Physics, History): ";
//    string facultyInput;
//    cin >> facultyInput;
//    facultyInput = facultyCheck(facultyInput);
//
//    vector<vector<int>> studentsDataList;
//
//    cout << endl << "Id: " << setw(a) << "Name: " << setw(a) << "Age: " << setw(a) << "Faculty: " << endl;
//    cout << s.id << setw(a) << s.name << setw(a) << s.age << setw(a) << facultyInput;
//    fout << "Id: " << setw(a) << "Name: " << setw(a) << "Age: " << setw(a) << "Faculty: " << endl;
//    fout << s.id << setw(a) << s.name << setw(a) << s.age << setw(a) << facultyInput;
//
//    fout.close();
//}

void checkStudentsList(const vector<Student>& students) {
    if (students.empty()) {
        cout << "List of students is empty\n";
        return;
    }

    cout << "\nID\tName\tAge\tFaculty\n";
    for (const auto& s : students) {
        cout << s.id << "\t" << s.name << "\t" << s.age << "\t" << facultyToString(s.faculty) << endl;
    }
}

void delStudent(vector<Student>& students, const string& filename) {
    cout << "Enter student's Id to delete: ";
    int id;
    cin >> id;

    auto it = remove_if(students.begin(), students.end(), [id](const Student& s) {
        return s.id == id;
        });

    if (it != students.end()) {
        students.erase(it, students.end());
        cout << "Student is deleted.\n";
        ofstream fout(filename);
        for (const auto& s : students) {
            fout << s.id << ";" << s.name << ";" << s.age << ";" << facultyToString(s.faculty) << endl;
        }
        fout.close();
    }
    else {
        cout << "There is no student with that Id\n";
    }
}

void searchStudent(const vector<Student>& students) {
    cout << "Enter student's Id to search: ";
    string input;
    cin >> input;

    bool found = false;
    for (const auto& s : students) {
        if (to_string(s.id) == input || s.name == input) {
            cout << "Founded: " << s.id << " " << s.name << " " << s.age << " " << facultyToString(s.faculty) << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Student not founded\n";
    }
}

void commandList() {
    cout << "1 - Show all students\n";
    cout << "2 - Add student\n";
    cout << "3 - Search student\n";
    cout << "4 - Delete student\n";
    cout << "0 - Exit\n";
}

//void commandInput() {
//
//    int tempCommand;
//    cin >> tempCommand;
//
//    switch (tempCommand) {
//        //case 1: checkStudentsList();
//            //break;
//        case 2: addStudent();
//            break;
//        //case 3: delSrudent();
//             //break;
//        //case 4: searchStudent();
//            //break;
//        case 5: commandList();
//            break;
//    }
//
//}

int main() {
    vector<Student> students;
    loadFromFile(students, "studentList.txt");
    int nextId = getStudentId(students);

    int cmd;
    commandList();

    while (true) {
        cout << "\nEnter command: ";
        cin >> cmd;

        switch (cmd) {
        case 1:
            checkStudentsList(students);
            break;
        case 2:
            addStudent(students, nextId);
            saveStudent(students.back(), "studentList.txt");
            break;
        case 3:
            searchStudent(students);
            break;
        case 4:
            delStudent(students, "studentList.txt");
            break;
        case 0:
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "Unknown command\n";
        }
    }
}


//ofstream("studentList.txt");
//ifstream("studentList.txt");

//fout.close();
//fin.close()