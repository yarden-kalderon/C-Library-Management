
#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include<stdlib.h>
#include<cstdio>
using namespace std;


#include < conio.h >



#define _CRT_SECURE_NO_WARNINGS_

//*********************************************************
//                   CLASS USED IN PROJECT
//*********************************************************

char emptych;
int emptyint;

class book
{
    char bno[6];
    char bname[50];
    char aname[20];
    float rate;
    int btake;
    int loc_in_lib;

public:
    void create_book()
    {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nEnter The book no.";
        cin >> bno;
        emptych = getchar();
        cout << "\n\nEnter The Name of The Book ";
        gets_s(bname);
        cout << "\n\nEnter The Author's Name ";
        gets_s(aname);
        whereIsTheBook();
        cout << "\n\n\nBook Created..";

    }

    void show_book()
    {
        cout << "\nBook no. : " << bno;
        cout << "\nBook Name : ";
        puts(bname);
        cout << "Author Name : ";
        puts(aname);
        cout << "Place In Library is column #" << loc_in_lib ;
    }

    void modify_book()
    {
        cout << "\nBook no. : " << bno;
        cout << "\nModify Book Name : ";
        gets_s(bname);
        cout << "\nModify Author's Name of Book : ";
        gets_s(aname);
        cout << "\nModify Book Designated Column : ";
        whereIsTheBook();
    }

    char* retbno()
    {
        return bno;
    }

    void report()
    {
        cout << bno << setw(30) << bname << setw(30) << aname << setw(10) << rate << endl;
    }

    void set_take()
    {
        btake += 1;
    }
    void set_rate()
    {
        int x;
        cout << "\nHow much did you like the book from 1 - 10 ?" ;
        cin >> x;
        this->rate = (rate * (btake - 1) + x) / btake;
        
    }
    void whereIsTheBook()
    {
        cout << "\nWhat is the designated column for the book? ";
        cin >> this->loc_in_lib;
    }
};         //class ends here




class student
{
    char admno[6];
    char name[20];
    char stbno[6];
    int token;
public:
    void create_student()
    {
        system("CLS");
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The admission no. ";
        cin >> admno;
        emptych = getchar();
        cout << "\n\nEnter The Name of The Student ";

        gets_s(name);
        token = 0;
        stbno[0] = NULL;
        cout << "\n\nStudent Record Created..";
    }

    void show_student()
    {
        cout << "\nAdmission no. : " << admno;
        cout << "\nStudent Name : " << name;
        puts(name);
        cout << "\nNo of Book issued : " << token;
        if (token == 1)
            cout << "\nBook No " << stbno;
    }

    void modify_student()
    {
        cout << "\nAdmission no. : " << admno;
        cout << "\nModify Student Name : ";
        gets_s(name);
    }

    char* retadmno()
    {
        return admno;
    }

    char* retstbno()
    {
        return stbno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {
        token = 1;
    }

    void resettoken()
    {
        token = 0;
    }

    void getstbno(char t[])
    {
        strcpy_s(stbno, t);
    }

    void report()
    {
        cout << "\t" << admno << setw(20) << name << setw(10) << token <<
            endl;
    }

};         //class ends here




//**********************************************************
//        global declaration for stream object, object
//*********************************************************

fstream fp, fp1;
book bk;
student st;


//**********************************************************
//        function to write in file
//**********************************************************

void write_book()
{
    char ch;
    fp.open("book.dat", ios::out | ios::app);
    do
    {
        system("CLS");
        bk.create_book();
        fp.write((char*)&bk, sizeof(book));
        cout << "\n\nDo you want to add more record..(y/n?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void write_student()
{
    char ch;
    fp.open("student.dat", ios::out | ios::app);
    do
    {
        st.create_student();
        fp.write((char*)&st, sizeof(student));
        cout << "\n\ndo you want to add more record..(y/n?)";
        cin >> ch;
        emptych = getchar();
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}


//**********************************************************
//        function to read specific record from file
//**********************************************************


void display_spb(char n[])
{
    cout << "\nBOOK DETAILS\n";
    int flag = 0;
    fp.open("book.dat", ios::in);
    while (fp.read((char*)&bk, sizeof(book)))
    {
        if (strcmp(bk.retbno(), n) == 0)
        {
            bk.show_book();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nBook does not exist";
}

void display_sps(char n[])
{
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    fp.open("student.dat", ios::in);
    while (fp.read((char*)&st, sizeof(student)))
    {
        if ((strcmp(st.retadmno(), n) == 0))
        {
            st.show_student();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nStudent does not exist";
    emptych = getchar();
}


//**********************************************************
//        function to modify record of file
//**********************************************************


void modify_book()
{
    char n[6];
    int found = 0;
    system("CLS");
    cout << "\n\n\tMODIFY BOOK REOCORD.... ";
    cout << "\n\n\tEnter The book no. of The book";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&bk, sizeof(book)) && found == 0)
    {
        if (strcmp(bk.retbno(), n) == 0)
        {
            int pos;
            bk.show_book();
            cout << "\nEnter The New Details ofbook" << endl;
            bk.modify_book();
            pos = -1 * int(sizeof(bk));
            fp.seekp(pos, ios::cur);
            fp.write((char*)&bk, sizeof(book));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }

    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    emptych = getchar();
}


void modify_student()
{
    char n[6];
    int found = 0;
    system("CLS");
    cout << "\n\n\tMODIFY STUDENT RECORD... ";
    cout << "\n\n\tEnter The admission no. of The student";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(student)) && found == 0)
    {
        if (strcmp(st.retadmno(), n) == 0)
        {
            int pos;
            st.show_student();
            cout << "\nEnter The New Details of                      x                            student" << endl;
            st.modify_student();
            pos = -1 * int(sizeof(st));
            fp.seekp(pos, ios::cur);
            fp.write((char*)&st, sizeof(student));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }

    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    emptych = getchar();
}

//*********************************************************
//        function to delete record of file
//**********************************************************


void delete_student()
{
    char n[6];
    int flag = 0;
    system("CLS");
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter The admission no. of the Student You Want To Delete : ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*)&st, sizeof(student)))
    {
        if (strcmp(st.retadmno(), n) != 0)
            fp2.write((char*)&st, sizeof(student));
        else
            flag = 1;
    }

    fp2.close();
    fp.close();
    remove("student.dat");
    emptych = rename("Temp.dat", "student.dat");
    if (flag == 1)
        cout << "\n\n\tRecord Deleted ..";
    else
        cout << "\n\nRecord not found";
    emptych = getchar();
}


void delete_book()
{
    char n[6];
    system("CLS");
    cout << "\n\n\n\tDELETE BOOK ...";
    cout << "\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*)&bk, sizeof(book)))
    {
        if (strcmp(bk.retbno(), n) != 0)
        {
            fp2.write((char*)&bk, sizeof(book));
        }
    }

    fp2.close();
    fp.close();
    remove("book.dat");
    emptych = rename("Temp.dat", "book.dat");
    cout << "\n\n\tRecord Deleted ..";
    emptych = getchar();
}



//*********************************************************
//        function to display all students list
//**********************************************************

void display_alls()
{
    system("CLS");
    fp.open("student.dat", ios::in);
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        emptych = getchar();
        return;
    }

    cout << "\n\n\t\tSTUDENT LIST\n\n";
    cout << "============================================\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20)
        << "Book Issued\n";

    cout << "============================================\n";

    while (fp.read((char*)&st, sizeof(student)))
    {
        st.report();
    }

    fp.close();
    emptych = getchar();
}


//**********************************************************
//        function to display Books list
//**********************************************************

void display_allb()
{
    system("CLS");
    fp.open("book.dat", ios::in);
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        emptych = getchar();
        return;
    }

    cout << "\n\n\t\tBook LIST\n\n";
    cout << "===========================================================================================\n";
    cout << "Book Number" << setw(28) << "Book Name" << setw(25)
        << "Author"<<"      Rate\n";
    cout << "===========================================================================================\n";

    while (fp.read((char*)&bk, sizeof(book)))
    {
        bk.report();
    }
    fp.close();
    emptych = getchar();
}



//********************************************************
//        function to issue book
//**********************************************************

void book_issue()
{
    char sn[6], bn[6];
    int found = 0, flag = 0;
    system("CLS");
    cout << "\n\nBOOK ISSUE ...";
    cout << "\n\n\tEnter The student's admission no.";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(student)) && found == 0)
    {
        if (strcmp(st.retadmno(), sn) == 0)
        {
            found = 1;
            if (st.rettoken() == 0)
            {
                cout << "\n\n\tEnter the book no. ";
                cin >> bn;
                while (fp1.read((char*)&bk, sizeof(book)) && flag == 0)
                {
                    if (strcmp(bk.retbno(), bn) == 0)
                    {
                        bk.show_book();
                        flag = 1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                        int pos = -1 * int(sizeof(st));
                        fp.seekp(pos, ios::cur);
                        fp.write((char*)&st, sizeof
                        (student));
                        cout << "\n\n\t Book issued successfully\n\nPlease Note: Write current date in back side of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
                        
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";
            }
            else
                cout << "You have not returned the last book ";


        }
    }
    if (found == 0)
        cout << "Student record not exist...";
    emptych = getchar();
    fp.close();
    fp1.close();
}

//*********************************************************
//        function to deposit book
//**********************************************************

void book_deposit()
{
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;
    system("CLS");
    cout << "\n\nBOOK DEPOSIT ...";
    cout << "\n\n\tEnter The students admission no.";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(student)) && found == 0)
    {
        if (strcmp(st.retadmno(), sn) == 0)
        {
            found = 1;
            if (st.rettoken() == 1)
            {
                while (fp1.read((char*)&bk, sizeof(book)) &&
                    flag == 0)
                {
                    if (strcmp(bk.retbno(), st.retstbno()) == 0)
                    {
                        bk.show_book();
                        flag = 1;
                        cout << "\n\nBook deposited in no.of days";

                        cin >> day;
                        if (day > 15)
                        {
                            fine = (day - 15) * 1;
                            cout << "\n\nFine has to deposited Rs " << fine;
                        }
                        st.resettoken();
                        int pos = -1 * int(sizeof(st));
                        fp.seekp(pos, ios::cur);
                        fp.write((char*)&st,
                            sizeof(student));
                        cout << "\n\n\t Book deposited successfully";
                        bk.set_take();
                        pos = -1 * int(sizeof(bk));
                        fp1.seekp(pos, ios::cur);
                        fp1.write((char*)&bk, sizeof(book));
                        bk.set_rate();
                        pos = -1 * int(sizeof(bk));
                        fp1.seekp(pos, ios::cur);
                        fp1.write((char*)&bk, sizeof(book));
                        cout << "\n\n\t Rate Book Updated";
                        
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";
            }
            else
                cout << "No book is issued..please check!!";
        }
    }
    if (found == 0)
        cout << "Student record not exist...";
    emptych = getchar();
    fp.close();
    fp1.close();
}




//***************************************************************
//        INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
    system("CLS");
    cout << "\n\n\n\n\n\n\n\n\t                    LIBRARY MANAGEMENT SYSTEM";
    emptych = getchar();
}




//********************************************************
//        ADMINISTRATOR MENU FUNCTION
//*********************************************************

void admin_menu()
{

    int ch2;
    cout << "\n\n\n     ADMINISTRATOR MENU";
    cout << "\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout << "\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout << "\n\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\n\t5.DELETE STUDENT RECORD";
    cout << "\n\n\t6.CREATE BOOK ";
    cout << "\n\n\t7.DISPLAY ALL BOOKS ";
    cout << "\n\n\t8.DISPLAY SPECIFIC BOOK ";
    cout << "\n\n\t9.MODIFY BOOK ";
    cout << "\n\n\t10.DELETE BOOK ";
    cout << "\n\n\t11.BACK TO MAIN MENU";
    cout << "\n\n     Please Enter Your Choice (1-11) ";
    cin >> ch2;
    switch (ch2)
    {
    case 1: system("CLS");
        write_student(); break;
    case 2: display_alls(); break;
    case 3:
        char num[6];
        system("CLS");
        cout << "\n\n\tPlease Enter The Admission No.";
        cin >> num;
        display_sps(num);
        break;
    case 4: modify_student(); break;
    case 5: delete_student(); break;
    case 6: system("CLS");
        write_book(); break;
    case 7: display_allb(); break;
    case 8: {
        char num[6];
        system("CLS");
        cout << "\n\n\tPlease Enter The book No. ";
        cin >> num;
        emptych = getchar();
        display_spb(num);

        break;
    }
    case 9: modify_book(); break;
    case 10: delete_book(); break;
    case 11: return;
    default:cout << "\a";
    }
    admin_menu();
}

//********************************************************
//        GAMES MENU FUNCTION
//*********************************************************

class Game
{
private:
    int code;
    int guesses;
    int* history;
    int* grades;
    bool Check(int guess) {
        {
            int A = 0, B = 0, temp = code;
            int c[4];
            int g[4];
            for (int i = 3; i >= 0; i--)
            {
                g[i] = guess % 10;
                c[i] = temp % 10;
                temp /= 10;
                guess /= 10;
            }
            for (int i = 0; i < 4; ++i)
            {
                if (g[i] == c[i])
                {
                    A++;
                    c[i] = -1;
                    g[i] = -2;
                }
            }
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (g[i] == c[j])
                    {
                        B++;
                        c[j] = -1;
                        break;
                    }
                }
            }
            cout << A << " A And " << B << " B" << endl;
            //cout << code;
            int* tempgrades = new int[2 * guesses];
            if (guesses > 1)
            {
                for (int i = 0; i < 2 * guesses - 2; ++i)
                    tempgrades[i] = grades[i];
            }
            tempgrades[2 * guesses - 2] = A;
            tempgrades[2 * guesses - 1] = B;
            delete[] grades;
            grades = tempgrades;
            if (A == 4)
            {
                return true;
            }
            return false;
        }
    };
public:
    Game() {
        srand(time(0));
        code = rand() % 9000 + 1000;
        guesses = 0;
        history = NULL;
        grades = NULL;
    };
    Game(const Game& previous) {
        code = previous.code;
        guesses = previous.guesses;
        history = previous.history;
        grades = previous.grades;
    };
    bool update(int guess) {
        guesses++;
        int* temphistory = new int[guesses];
        int i = 0;
        if (guesses > 1)
        {
            for (; i < guesses - 1; ++i)
                temphistory[i] = history[i];
        }
        temphistory[i] = guess;
        delete[] history;
        history = temphistory;
        cout << guesses << endl;
        return this->Check(guess);
    };
    void print()const {
        for (int i = 0; i < guesses; i++)
            cout << i + 1 << "# Guess: " << history[i] << " " << grades[2 * i] << "A" << grades[2 * i + 1] << "B" << endl;
    };
    ~Game() {
        delete[] history;
        delete[] grades;
    };
};




void Buls_cows()
{

    Game NewGame;
    bool gameon = true;
    int turn = 1, new_guess;
    cout << "Welcome to the game!\n A=Bool , B = Hit " << endl;
    while (gameon)
    {
        cout << "Please enter your " << turn << " Guess!" << endl;
        cin >> new_guess;
        turn++;
        if (NewGame.update(new_guess))
        {
            break;
        }
    }
    cout << "Congratulations!" << endl;
    NewGame.print();
}





class MyDate {
public:
    MyDate(); //default constructor
    MyDate(int day, int month, int year, char* str); // constructor
    MyDate(const MyDate &x); // copy constructor
    bool isBefore(const MyDate &date) const;
    bool setDay(int d);
    bool setMonth(int m);
    bool setYear(int y);
    void setDate(int d, int m, int y);
    int getDay() const;
    int getMonth() const;
    int getYear() const;

private:
    int day, month, year;
};


MyDate::MyDate(int day, int month, int year) {
    this->day=day;
    this->month=month;
    this->year=year;
}

bool MyDate::setDay(int d) {
    if(d<0) {
        cout<<"invalid day"<<endl;
        return false;
    }

    if(getMonth()==2 && d>28) {
        cout<<"invalid day"<<endl;
        return false;
    }
    if((getMonth()==4 || getMonth()==6 || getMonth()==9 || getMonth()==11) && d>30){
        cout<<"invalid day"<<endl;
        return false;
    }
        if((getMonth()==1 || getMonth()==3 || getMonth()==5 || getMonth()==7 || getMonth()==10 || getMonth()==12)&& (d>31) ) {
            cout<<"invalid day"<<endl;
        return false;
    }
        else{
            day=d;
            return true;
        }
}

bool MyDate::setMonth(int m) {

    if(m<0 || m>12) {
        cout<<"invalid month";
        return false;
    }
    else{
        month=m;
        return true;
    }
}

bool MyDate::setYear(int y) {

    if(y<=0) {
        cout<<"invalid year";
        return false;
    }
    else{
        year=y;
        return true;
    }
}

void MyDate::setDate(int d, int m, int y) {

    int newDay=1, newMonth=1, newYear=1900;

    if(!setYear(y)){
        y=newYear;
        year=y;
    }
    if(!setMonth(m)){
        m=newMonth;
        month=m;
    }
    if(!setDay(d)){
        d=newDay;
        day=d;
    }
}

int MyDate::getDay() const {
    return day;
}

int MyDate::getMonth() const {
    return month;
}

int MyDate::getYear() const {
    return year;
}


bool MyDate::isBefore(const MyDate &date)  const{

    if(this->year < date.year){
        return true;
    }

    else if(date.year == this->year && this->month < date.month){
        return true;
    }

    else if (date.year == this->year && date.month == this->month  && this->day < date.day){
        return true;
    }

    else{
        return false;
    }





//***************************************************
//        THE MAIN FUNCTION OF PROGRAM
//***************************************************


int main()
{
        MyDate *d;
        MyDate d2;
        int day, month, year,day2, month2, year2,size;
        int count=0;
        char ch;
    
      cout<<"Enter the number of students who received an extension of time:";
      cin>>size;
      d=new MyDate[size];
    
      for(int i=0; i<size; i++){
        
          cout<<"Book return date after extension of time of student["<<i+1<<"]: ";
          cin>>day>>ch>>month>>ch>>year;
          d[i].setDate(day, month, year);
          cout<<endl<<"return date of student["<<i+1<<"]:";
          cin>>day2>>ch>>month2>>ch>>year2;
          d2.setDate(day2, month2, year2);
          if(d[i].isBefore(d2)){
               cout<<"student ["<<i+1<<"] returned the book on time"<<endl;
          }
          else{
              cout<<"student ["<<i+1<<"] was late in returning the book"<<endl;
              count++;
          }
      }
    
     cout<<"The number of students who were late after an extension of time:"<<count;
    
    intro();
    do
    {
        cout << "hi\n\n\n\n";
        system("CLS");
        cout << "\n\n\n     MAIN MENU";
        cout << "\n\n\t01. BOOK ISSUE";
        cout << "\n\n\t02. BOOK DEPOSIT";
        cout << "\n\n\t03. ADMINISTRATOR MENU";
        cout << "\n\n\t04. AVIRAM GAME - Bulls And cows";
        cout << "\n\n\t05. EXIT";
        cout << "\n\n     Please Select Your Option (1-5) ";
        ch = getchar();
        switch (ch)
        {
        case '1':system("CLS");
            book_issue();
            break;
        case '2':book_deposit();
            break;
        case '3':admin_menu();
            break;
        case '4':Buls_cows();
            break;
        case '5':exit(0);
        default:cout << "\a";
        }
        emptych = getchar();
    } while (ch != '5');
    

    return 0;
}

//****************END OF PROJECT**************************
