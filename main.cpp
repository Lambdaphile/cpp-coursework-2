/**
 * За група студенти са зададени име, ЕГН, фак. №, оценките
 * по 10 дисциплини и среден успех.
 * Да се създаде програма, която избира от меню и използва функций за:
 *
 *  1. Създаване на файл с информация за група студенти, без да се въвежда
 *     средният успех.
 *  2. Изчисляване на средния успех на всеки един от студентите.
 *  3. Определяне броя на студентите с по три двойки.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

const int GRADE_COUNT = 10;
const string SUBJECTS[] = {
    "Programming",
    "Mathematics",
    "Physics",
    "Chemistry",
    "Biology",
    "History",
    "Geography",
    "English",
    "Literature",
    "Physchology"
};
const struct Questions {
    string ENTER_ANOTHER_STUDENT = "Enter another Student?";
    string GO_BACK_TO_MENU = "Go back to menu?";
} QUESTIONS;
const struct Answers {
    string YES = "y";
    string NO = "n";
    string NO_ANS = "no ans";
} ANSWERS;

struct Student {
    string name;
    string egn;
    int facultyNumber;
    float avgGrade;
    float grades[GRADE_COUNT];
};

void printMenu();
int getOption();
string getAnswer(string question);
void printNoStudentsMsg();
void handleCinFail();

Student getStudent();
float getAvgGrade(float grades[]);
void printStudentsAvgGrade(vector<Student> students);
void printStudentsWithThree2s(vector<Student> students);
bool hasThree2s(float grades[]);
void printStudents(vector<Student> students);

int main() {
    int option = -1, studentsSize;
    string answer = ANSWERS.NO_ANS,
        enterAnother = ANSWERS.YES, goBack = ANSWERS.YES;
    vector<Student> students;

    do {
        system("clear");
        printMenu();
        option = getOption();
        studentsSize = students.size();

        switch (option) {
            case 0:
                break;
            case 1:
                do {
                    Student student = getStudent();
                    students.push_back(student);

                    enterAnother = getAnswer(QUESTIONS.ENTER_ANOTHER_STUDENT);
                } while (enterAnother == ANSWERS.YES);
                break;
            case 2:
                if (studentsSize == 0) {
                    printNoStudentsMsg();
                } else {
                    for (int i = 0; i < studentsSize; i++) {
                        students[i].avgGrade = getAvgGrade(students[i].grades);
                    }
                    printStudentsAvgGrade(students);
                }
                goBack = getAnswer(QUESTIONS.GO_BACK_TO_MENU);
                break;
            case 3:
                if (studentsSize == 0) {
                    printNoStudentsMsg();
                } else {
                    printStudentsWithThree2s(students);
                }
                goBack = getAnswer(QUESTIONS.GO_BACK_TO_MENU);
                break;
            case 4:
                if (studentsSize == 0) {
                    printNoStudentsMsg();
                } else {
                    printStudents(students);
                }
                goBack = getAnswer(QUESTIONS.GO_BACK_TO_MENU);
                break;
            default:
                getOption();
                break;
        }
    } while (option != 0 && goBack == ANSWERS.YES);
    cout << "\nBye! <3\n";
    sleep(3);

    return 0;
}

void printMenu() {
    cout << "1 - Enter student information (name, EGN, faculty number, grades)\n";
    cout << "2 - Print the average grade for each student\n";
    cout << "3 - Print the number of students with three 2's\n";
    cout << "4 - Print students\n";
}

int getOption() {
    int option;

    while (true) {
        cout << "\nEnter an option from the menu or 0 to exit: ";
        cin >> option;
        if (cin.fail()) {
            handleCinFail();
        } else {
            break;
        }
    }

    return option;
}

string getAnswer(string question) {
    string answer = ANSWERS.NO_ANS;

    do {
        cout << "\n" << question << " (y/n): ";
        cin >> answer;
    } while (answer != ANSWERS.YES && answer != ANSWERS.NO);

    return answer;
}

void printNoStudentsMsg() {
    system("clear");
    cout << "No students!\n";
}

void handleCinFail() {
    cin.clear();
    cin.ignore();
}

Student getStudent() {
    Student student;
    string subject;

    system("clear");
    cout << "\nPlease enter student's information.\n\n";
    cout << "Name: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "EGN: ";
    cin >> student.egn;
    cout << "Faculty number: ";
    cin >> student.facultyNumber;
    cout << "Grades\n";
    for (int i = 0; i < GRADE_COUNT; i++) {
        subject = SUBJECTS[i];
        cout << "  " << subject << ": ";
        cin >> student.grades[i];
    }

    return student;
}

float getAvgGrade(float grades[]) {
    float sum = 0, count = 0, avgGrade;

    for (int i = 0; i < GRADE_COUNT; i++) {
        sum += grades[i];
        count++;
    }
    avgGrade = sum / count;

    return avgGrade;
}

void printStudentsAvgGrade(vector<Student> students) {
    system("clear");
    Student student;

    cout << "Student's average grades:\n\n";
    for (int i = 0; i < students.size(); i++) {
        student = students[i];

        cout << student.name << ", average grade: " << student.avgGrade << endl;
    }
}

void printStudentsWithThree2s(vector<Student> students) {
    system("clear");
    Student student;
    int total = 0;

    cout << "Students with three or more 2's:\n\n";
    for (int i = 0; i < students.size(); i++) {
        student = students[i];

        if (hasThree2s(student.grades)) {
            cout << student.name << endl;
            total++;
        }
    }
    if (total == 0) {
        cout << "No students with three 2's!\n";
    }
    cout << "\nNumber of students with three or more 2's: " << total << endl;
}

bool hasThree2s(float grades[]) {
    int lowGradesCount = 0;
    bool hasThree2s = false;
    float grade;

    for (int i = 0; i < GRADE_COUNT; i++) {
        grade = grades[i];

        if (grade == 2) {
            lowGradesCount++;
        }
    }

    if (lowGradesCount >= 3) {
        hasThree2s = true;
    }

    return hasThree2s;
}

void printStudents(vector<Student> students) {
    system("clear");
    Student student;

    int studentsSize = students.size();
    for (int i = 0; i < studentsSize; i++) {
        student = students[i];
        cout << "Student " << "(" << i + 1 << ")" << ":\n\n";
        cout << "Name: " << student.name << endl;
        cout << "EGN: " << student.egn << endl;
        cout << "Faculty number: " << student.facultyNumber << endl;
        cout << "Grades\n";
        for (int j = 0; j < GRADE_COUNT; j++) {
            string subject = SUBJECTS[j];

            cout << "  " << subject << ": " << student.grades[j] << endl;
        }
        if (i < studentsSize - 1) {
            cout << "\n-----------------\n\n";
        }
    }
}
