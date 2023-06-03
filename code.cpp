#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

// class to store the data
class Student
{
    int rollNo;
    std::string name;
    int eng_m, lang_m, maths_m, sci_m, soc_m, computer_m;
    double average;
    char grade;

public:
    void getdata();
    void showdata() const;
    void calculate();
    int getRollNo() const;
};

void Student::calculate()
{
    average = (eng_m + lang_m + sci_m + soc_m + computer_m) / 5.0;
    if (average >= 90)
        grade = 'O';
    else if (average >= 80)
        grade = 'A';
    else if (average >= 70)
        grade = 'B';
    else if (average >= 60)
        grade = 'C';
    else if (average >= 50)
        grade = 'D';
    else if (average >= 40)
        grade = 'E';
    else
        grade = 'F';
}

void Student::getdata()
{
    std::cout << "\nEnter student's roll number: ";
    std::cin >> rollNo;
    std::cin.ignore();
    std::cout << "\nEnter student name: ";
    std::getline(std::cin, name);
    std::cout << "\nAll marks should be out of 100";
    std::cout << "\nEnter marks in English: ";
    std::cin >> eng_m;
    std::cout << "\nEnter marks in 2nd language: ";
    std::cin >> lang_m;
    std::cout << "\nEnter marks in Math: ";
    std::cin >> maths_m;
    std::cout << "\nEnter marks in Science: ";
    std::cin >> sci_m;
    std::cout << "\nEnter marks in Social: ";
    std::cin >> soc_m;
    std::cout << "\nEnter marks in Computer: ";
    std::cin >> computer_m;
    calculate();
}

void Student::showdata() const
{
    std::cout << "\nRoll number of student: " << rollNo;
    std::cout << "\nName of student: " << name;
    std::cout << "\nEnglish: " << eng_m;
    std::cout << "\nSecond Language: " << lang_m;
    std::cout << "\nMaths: " << maths_m;
    std::cout << "\nScience: " << sci_m;
    std::cout << "\nSocial: " << soc_m;
    std::cout << "\nComputer Science: " << computer_m;
    std::cout << "\nAverage Marks: " << average;
    std::cout << "\nGrade of student is: " << grade;
}

int Student::getRollNo() const
{
    return rollNo;
}

// function declaration
void create_student();
void display_sp(int);
void display_all();
void delete_student(int);
void change_student(int);

int main()
{
    char ch;
    std::cout << std::setprecision(2);
    do
    {
        system("cls");
        std::cout << "\n\n\n\t-----------MENU----------";
        std::cout << "\n\n\t1. Create student record";
        std::cout << "\n\n\t2. Search student record";
        std::cout << "\n\n\t3. Display all student records";
        std::cout << "\n\n\t4. Delete student record";
        std::cout << "\n\n\t5. Modify student record";
        std::cout << "\n\n\t6. Exit";
        std::cout << "\n\n\tWhat is your choice (1/2/3/4/5/6)? ";
        std::cin >> ch;
        system("cls");
        switch (ch)
        {
            case '1':
                create_student();
                break;
            case '2':
                std::cout << "\n\n\tEnter the roll number: ";
                int num;
                std::cin >> num;
                display_sp(num);
                break;
            case '3':
                display_all();
                break;
            case '4':
                std::cout << "\n\n\tEnter the roll number: ";
                std::cin >> num;
                delete_student(num);
                break;
            case '5':
                std::cout << "\n\n\tEnter the roll number: ";
                std::cin >> num;
                change_student(num);
                break;
            case '6':
                std::cout << "Exiting, Thank you!";
                exit(0);
        }
    } while (ch != '6');
    return 0;
}

// write student details to file
void create_student()
{
    Student stud;
    stud.getdata();
    std::ofstream oFile("student.dat", std::ios::binary | std::ios::app);
    oFile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
    oFile.close();
    std::cout << "\n\nStudent record has been created";
    std::cin.ignore();
    std::cin.get();
}

// read file records
void display_all()
{
    Student stud;
    std::ifstream iFile("student.dat", std::ios::binary);
    if (!iFile)
    {
        std::cout << "File could not be opened! Press any key to exit";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    std::cout << "\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
    while (iFile.read(reinterpret_cast<char*>(&stud), sizeof(Student)))
    {
        stud.showdata();
        std::cout << "\n\n====================================\n";
    }
    iFile.close();
    std::cin.ignore();
    std::cin.get();
}

// read specific record based on roll number
void display_sp(int n)
{
    Student stud;
    std::ifstream iFile("student.dat", std::ios::binary);
    if (!iFile)
    {
        std::cout << "File could not be opened. Press any key to exit";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    bool found = false;
    while (iFile.read(reinterpret_cast<char*>(&stud), sizeof(Student)))
    {
        if (stud.getRollNo() == n)
        {
            stud.showdata();
            found = true;
        }
    }
    iFile.close();
    if (!found)
        std::cout << "\n\nRecord does not exist";
    std::cin.ignore();
    std::cin.get();
}

// modify record for specified roll number
void change_student(int n)
{
    bool found = false;
    Student stud;
    std::fstream fl("student.dat", std::ios::binary | std::ios::in | std::ios::out);
    if (!fl)
    {
        std::cout << "File could not be opened. Press any key to exit...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    while (fl.read(reinterpret_cast<char*>(&stud), sizeof(Student)))
    {
        if (stud.getRollNo() == n)
        {
            stud.showdata();
            std::cout << "\n\nEnter new student details:\n";
            stud.getdata();
            int pos = -1 * static_cast<int>(sizeof(stud));
            fl.seekp(pos, std::ios::cur);
            fl.write(reinterpret_cast<char*>(&stud), sizeof(Student));
            std::cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    fl.close();
    if (!found)
        std::cout << "\n\n Record Not Found ";
    std::cin.ignore();
    std::cin.get();
}

// delete record with specified roll number
void delete_student(int n)
{
    Student stud;
    std::ifstream iFile("student.dat", std::ios::binary);
    if (!iFile)
    {
        std::cout << "File could not be opened. Press any key to exit...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    std::ofstream oFile("temp.dat", std::ios::binary);
    iFile.seekg(0, std::ios::beg);
    while (iFile.read(reinterpret_cast<char*>(&stud), sizeof(Student)))
    {
        if (stud.getRollNo() != n)
        {
            oFile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
        }
    }
    oFile.close();
    iFile.close();
    std::remove("student.dat");
    std::rename("temp.dat", "student.dat");
    std::cout << "\n\n\tRecord Deleted ..";
    std::cin.ignore();
    std::cin.get();
}
