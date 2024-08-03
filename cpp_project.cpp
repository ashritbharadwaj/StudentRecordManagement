#include <iostream>
#include<cstring>
#include <fstream>
#include <iomanip>
using namespace std;

// the class that stores data
class student{
    int rollno;
    char name[50];
    int eng_marks, math_marks, sci_marks, lang2_marks, cs_marks;
    double average;
    char grade;

public:
    student(){
        rollno=0;
        strcpy(name,"");
        eng_marks=math_marks=sci_marks=lang2_marks=cs_marks=0;
        average=-1;
        grade='-';
    }
    void getdata();
    friend istream &operator>>(istream &, student &);
    void showdata() const;
    friend ostream &operator<<(ostream &, const student &);
    void calculate();
    void calculate_performance(double &, int &);
    int retrollno() const;
}; // class ends here

void student::calculate(){
    average = (eng_marks + math_marks + sci_marks + lang2_marks + cs_marks) / 5.0;
    if (average >= 90)
        grade = 'A';
    else if (average >= 75)
        grade = 'B';
    else if (average >= 50)
        grade = 'C';
    else
        grade = 'F';
}

void student::calculate_performance(double &average, int &stud_ct){
    average = average*stud_ct;
    average = average + this->average;
    stud_ct++;
    average = average/stud_ct;
}

void student::getdata(){
    cout << "\nEnter student's roll number: ";
    cin >> rollno;
    cout << "\n\nEnter student name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nAll marks should be out of 100";
    cout << "\nEnter marks in English: ";
    cin >> eng_marks;
    cout << "\nEnter marks in Math:  ";
    cin >> math_marks;
    cout << "\nEnter marks in Science:  ";
    cin >> sci_marks;
    cout << "\nEnter marks in 2nd language:  ";
    cin >> lang2_marks;
    cout << "\nEnter marks in Computer science:  ";
    cin >> cs_marks;
    calculate();
}

istream &operator>>(istream &get,student &stud){
    cout << "\nEnter student's roll number: ";
    get >> stud.rollno;
    cout << "\n\nEnter student name: ";
    get.ignore();
    get.getline(stud.name, 50);
    cout << "\nAll marks should be out of 100";
    cout << "\nEnter marks in English: ";
    get >> stud.eng_marks;
    cout << "\nEnter marks in Math:  ";
    get >> stud.math_marks;
    cout << "\nEnter marks in Science:  ";
    get >> stud.sci_marks;
    cout << "\nEnter marks in 2nd language:  ";
    get >> stud.lang2_marks;
    cout << "\nEnter marks in Computer science:  ";
    get >> stud.cs_marks;
    stud.calculate();
    return get;
}

void student::showdata() const{
    cout << "\nRoll number of student: " << rollno;
    cout << "\nName of student: " << name;
    cout << "\nEnglish: " << eng_marks;
    cout << "\nMaths: " << math_marks;
    cout << "\nScience: " << sci_marks;
    cout << "\nLanguage2: " << lang2_marks;
    cout << "\nComputer Science: " << cs_marks;
    cout << "\nAverage Marks: " << average;
    cout << "\nGrade of student is: " << grade;
}

ostream &operator<<(ostream &show, const student &stud){
    show << "\nRoll number of student: " << stud.rollno;
    show << "\nName of student: " << stud.name;
    show << "\nEnglish: " << stud.eng_marks;
    show << "\nMaths: " << stud.math_marks;
    show << "\nScience: " << stud.sci_marks;
    show << "\nLanguage2: " << stud.lang2_marks;
    show << "\nComputer Science: " << stud.cs_marks;
    show << "\nAverage Marks: " << stud.average;
    show << "\nGrade of student is: " << stud.grade;
    return show;
}

int student::retrollno() const{
    return rollno;
}

// function declaration
void create_student();
void display_sp(int);      // display particular record
void display_all();        // display all records
void delete_student(int);  // delete particular record
void change_student(int);  // edit particular record
void performance();        // display overall performance of class

// MAIN
int main(){
    char ch;
    //cout << setprecision(2);
    do{
        int num;
        system("cls");
        cout << "\n\n\n\tMENU";
        cout << "\n\n\t1. Create student record";
        cout << "\n\n\t2. Search student record";
        cout << "\n\n\t3. Display all students records";
        cout << "\n\n\t4. Delete student record";
        cout << "\n\n\t5. Modify student record";
        cout << "\n\n\t6. Overall performance of the class";
        cout << "\n\n\t7. Exit";
        cout << "\n\n\tWhat is your Choice (1/2/3/4/5/6/7)? ";
        cin >> ch;
        system("cls");
        switch (ch){
        case '1':
            create_student();
            break;
        case '2':
            cout << "\n\n\tEnter The roll number: ";
            cin >> num;
            display_sp(num);
            break;
        case '3':
            display_all();
            break;
        case '4':
            cout << "\n\n\tEnter The roll number: ";
            cin >> num;
            delete_student(num);
            break;
        case '5':
            cout << "\n\n\tEnter The roll number: ";
            cin >> num;
            change_student(num);
            break;
        case '6':
            performance();
            break;
        case '7':
            cout << "Exiting, Thank you!";
            exit(0);
        }
    } while (ch != '7');
    return 0;
}

// write student details to file
void create_student(){
    student stud;
    ofstream oFile;
    oFile.open("student.txt", ios::app);
    stud.getdata();
    oFile.write(reinterpret_cast<char *>(&stud), sizeof(student));
    oFile.close();
    cout << "\n\nStudent record has been created";
    cout << "\n\n\n\n\t\tpress enter to continue\n";
    cin.ignore();
    cin.get();
}

// read file records
void display_all(){
    student stud;
    ifstream inFile;
    inFile.open("student.txt");
    if (!inFile){
        cout << "File could not be opened!! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
    while (inFile.read(reinterpret_cast<char *>(&stud), sizeof(student))){
        //stud.showdata();
        cout << stud;
        cout << "\n\n====================================\n";
    }
    inFile.close();
    cout << "\n\n\n\n\t\t press enter to continue\n";
    cin.ignore();
    cin.get();
}

// read specific record based on roll number
void display_sp(int n){
    student stud;
    ifstream iFile;
    iFile.open("student.txt");
    if (!iFile){
        cout << "File could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(student))){
        if (stud.retrollno() == n)
        {
            stud.showdata();
            flag = true;
        }
    }
    iFile.close();
    if (flag == false)
        cout << "\n\nRecord does not exist";
    cout << "\n\n\n\n\t\t press enter to continue\n";
    cin.ignore();
    cin.get();
}

// modify record for specified roll number
void change_student(int n){
    bool found = false;
    student stud;
    fstream fl;
    fl.open("student.txt", ios::in | ios::out);
    if (!fl){
        cout << "File could not be opened. Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    while (!fl.eof() && found == false){
        fl.read(reinterpret_cast<char *>(&stud), sizeof(student));
        if (stud.retrollno() == n){
            stud.showdata();
            cout << "\nEnter new student details:" << endl;
            stud.getdata();
            int pos = (-1) * static_cast<int>(sizeof(stud));
            fl.seekp(pos, ios::cur);
            fl.write(reinterpret_cast<char *>(&stud), sizeof(student));
            cout << "\n\n\tRecord Updated";
            found = true;
        }
    }
    fl.close();
    if (found == false)
        cout << "\n\nRecord Not Found";
    cout << "\n\n\n\n\t\t press enter to continue\n";
    cin.ignore();
    cin.get();
}

// delete record with particular roll number
void delete_student(int n){
    bool flag=false;
    student stud;
    ifstream iFile;
    iFile.open("student.txt");
    if (!iFile){
        cout << "File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat", ios::out);
    iFile.seekg(0, ios::beg);
    while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(student))){
        if (stud.retrollno() != n)
            oFile.write(reinterpret_cast<char *>(&stud), sizeof(student));
        else
            flag = true;
    }
    oFile.close();
    iFile.close();
    remove("student.txt");
    rename("Temp.dat", "student.txt");
    if (!flag)
        cout << "\n\n\tRecord not found";
    else
        cout << "\n\n\tRecord Deleted";
    cout << "\n\n\n\n\t\t press enter to continue\n";
    cin.ignore();
    cin.get();
}

// Overall Performance of the class
void performance(){
    student stud;
    ifstream inFile;
    int stud_count=0;
    double average=0;
    inFile.open("student.txt");
    if (!inFile){
        cout << "File could not be opened!! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    while (inFile.read(reinterpret_cast<char *>(&stud), sizeof(student))){
        stud.calculate_performance(average,stud_count);
    }
    inFile.close();
    if(average>=90) cout << "\n\n\nOverall Performance of the Students : A ~ EXCELLENT\n";
    else if(average>=75) cout << "\n\n\nOverall Performance of the Students : B ~ GOOD\n";
    else if(average>=50) cout << "\n\n\nOverall Performance of the Students : C ~ SATISFACTORY\n";
    else cout << "\n\n\nOverall Performance of the Students : F ~ BAD\n";
    cout << "\n\n\n\n\t\t press enter to continue\n";
    cin.ignore();
    cin.get();
}