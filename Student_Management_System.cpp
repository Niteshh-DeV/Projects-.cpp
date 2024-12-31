#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    float mathMarks, scienceMarks, englishMarks;

public:
    void inputData() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cin.ignore(); // To consume newline character left in the input buffer
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks (Maths, Science, English): ";
        cin >> mathMarks >> scienceMarks >> englishMarks;
    }

    void displayData() const {
        cout << setw(10) << rollNo << setw(20) << name
             << setw(10) << mathMarks << setw(10) << scienceMarks
             << setw(10) << englishMarks << endl;
    }

    int getRollNo() const {
        return rollNo;
    }
};

void addStudent() {
    ofstream outFile("students.dat", ios::binary | ios::app);
    Student student;
    student.inputData();
    outFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    outFile.close();
    cout << "Record added successfully!\n";
}

void displayAllStudents() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }

    Student student;
    cout << setw(10) << "Roll No" << setw(20) << "Name"
         << setw(10) << "Maths" << setw(10) << "Science"
         << setw(10) << "English" << endl;
    cout << "-------------------------------------------------------------\n";

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        student.displayData();
    }
    inFile.close();
}

void searchStudent() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }

    int rollNo;
    cout << "Enter Roll Number to search: ";
    cin >> rollNo;

    Student student;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.getRollNo() == rollNo) {
            cout << "Record found:\n";
            cout << setw(10) << "Roll No" << setw(20) << "Name"
                 << setw(10) << "Maths" << setw(10) << "Science"
                 << setw(10) << "English" << endl;
            student.displayData();
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found)
        cout << "No record found with Roll Number " << rollNo << ".\n";
}

void modifyStudent() {
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "No records found.\n";
        return;
    }

    int rollNo;
    cout << "Enter Roll Number to modify: ";
    cin >> rollNo;

    Student student;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.getRollNo() == rollNo) {
            cout << "Existing record:\n";
            student.displayData();
            cout << "Enter new details:\n";
            student.inputData();

            // Move the file pointer to the correct position
            file.seekp(-static_cast<int>(sizeof(Student)), ios::cur);
            file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
            cout << "Record updated successfully!\n";
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "No record found with Roll Number " << rollNo << ".\n";
}

void deleteStudent() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }

    ofstream outFile("temp.dat", ios::binary);
    int rollNo;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNo;

    Student student;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.getRollNo() == rollNo) {
            cout << "Record deleted successfully!\n";
            found = true;
        } else {
            outFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        }
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (!found)
        cout << "No record found with Roll Number " << rollNo << ".\n";
}

void menu() {
    int choice;
    do {
        cout << "\n--- Student Record Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Modify Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: modifyStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}