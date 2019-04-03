#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <cstdio>
#include <stdlib.h> 
#include <time.h> 
#include <iomanip>
#include <cmath>

using namespace std;

void displayStudents(int num);
void openSettings();
void saveSettings();

//DECLARATION OF CLASSES
class Person {
public:
	int id;
	string fname;
	string lname;
	char gender;
	string phone;
	string address;
};

class Student : public Person {
public:
	int new_modules;
	int repeat_modules;
	double pay;
};

class Teacher : public Person {
public:
	int dept;
	int desig;
	double work_hrs;
};

//PASSWORD MASKING 
string getpass(const char *prompt, bool show_asterisk = true)
{
	const char BACKSPACE = 8;
	const char RETURN = 13;

	string password;
	unsigned char ch = 0;

	cout << prompt;

	DWORD con_mode;
	DWORD dwRead;

	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(hIn, &con_mode);
	SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

	while (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN)
	{
		if (ch == BACKSPACE)
		{
			if (password.length() != 0)
			{
				if (show_asterisk)
					cout << "\b \b";
				password.resize(password.length() - 1);
			}
		}
		else
		{
			password += ch;
			if (show_asterisk)
				cout << '*';
		}
	}
	cout << endl;
	return password;
}

static Student students[1000];
static Teacher teachers[1000];

static int module_price;
static int repeat_price;
static double base_sal;
static int id_no;

int main(int argc, char** argv) {
	openSettings();

	string username;
	string pass;
	const char *correct_password = "admin123";
	bool wrongUser = false;
	bool wrongPass = false;

loginpage:
	system("cls");
	cout << "\n\n\n\tABC COLLEGE ACCOUNTING SYSTEM";

	//ID ERROR MESSAGE
	if (wrongUser == true)
	{
		cout << "\n\n\t\t\a(Invalid Username, Please try loginpage)";
		wrongUser = false;
	}
	if (wrongPass == true)
	{
		cout << "\n\n\t\t\a(Invalid Password, Please try loginpage)";
		wrongPass = false;
	}

	//GET USERNAME
	cout << "\n\n\tEnter Username: ";
	cin >> username;
	//GET PASSWORD
	pass = getpass("\tEnter Password: ", true); // Shows asterisks

	bool LoggedIn = false;

	while (LoggedIn == false)
	{
		if (username == "student")
		{
			if (pass == correct_password)
			{
			studentpage:
				cin.clear();
				//LOGGED IN STUDENT ACCOUNT TYPE
				system("cls");
				cout << "\n\n\n\tSTUDENT ADMIN HOMEPAGE" << endl;

				cout << "\n\n\t1. Add New Student" << endl;
				cout << "\n\t2. Update Student" << endl;
				cout << "\n\t3. Delete Student" << endl;
				cout << "\n\t4. Show Remaining Balance" << endl;
				cout << "\n\t5. Fee Deposit" << endl;
				cout << "\n\t6. Display all students with zero balance" << endl;
				cout << "\n\t7. Display all students with non-zero balance" << endl;
				cout << "\n\t8. Settings" << endl;
				cout << "\n\t9. Logout" << endl;

				cout << "\n\n\t Enter choice: ";
				int choice;
				cin >> choice;

				//Calling derived class
				Student s;
				char confirm;
				string confirm2;
				int id;
				bool found;
				int index;
				bool allowOnce;
				bool checker;
				double money;
				int new_module_price;
				int new_repeat_price;

				switch (choice)
				{
				case 1:
					//ADD STUDENT
					system("cls");
					cout << "\n\n\n\tADD NEW STUDENT" << endl;
					//ADD STUDENT
					system("cls");
					cout << "\n\n\n\tADD NEW STUDENT" << endl;

					//addStudent();
					cin.clear();
					cin.ignore(100000, '\n');

					//New generated ID for the new student
					cout << "\n\t New Student ID: " << setfill('0') << setw(5) << id_no << endl;
					s.id = id_no;

					cout << "\n\t Enter First-name: ";
					getline(cin, s.fname);

					cout << "\n\t Enter Last-name: ";
					getline(cin, s.lname);

					do {
						cout << "\n\t Enter Gender(M/F): ";
						cin >> s.gender;
					} while (s.gender != 'M' && s.gender != 'F' && s.gender != 'm' && s.gender != 'f');

					cin.clear();
					cin.ignore(100000, '\n');

					cout << "\n\t Enter Phone no.: ";
					getline(cin, s.phone);
					cout << "\n\t Enter Address: ";
					getline(cin, s.address);

					checker = false;
					do {
						checker = false;
						cout << "\n\t Enter Number of Modules: ";
						cin >> s.new_modules;
						cout << "\n\t Enter Number of Repeated Modules: ";
						cin >> s.repeat_modules;

						if (s.repeat_modules > 2 && s.new_modules > 0) {
							cout << "\n\t INVALID: Can only take 2 or more repeat modules if no new module is taken, Please Try Again.\n";
							checker = true;
						}
						else if ((s.new_modules + s.repeat_modules) > 6) {
							cout << "\n\t INVALID: Can only take max of 6 (new module + repeat) and min of 0, Please Try Again.\n";
							checker = true;
						}
					} while (checker);

					cout << "\n\t Are you sure you want to add new student? (y/n): ";
					cin >> confirm2;

					if (confirm2 == "y" || confirm2 == "Y") {
						for (index = 0; index < 1000; index++) {
							if (students[index].id == 0)
								break;
						}
						students[index] = s;
						id_no++;
					}
					else
					{
						goto studentpage;
					}
					saveSettings();
					system("pause");
					cout << "\n";
					goto studentpage;
					break;

				case 2:
					//UPDATE STUDENT
					system("cls");
					cout << "\n\n\n\tUPDATE STUDENT" << endl;
					id = 0;
					cin.clear();
					cin.ignore(100000, '\n');
					cout << "\n\t Enter Student ID you want to edit: ";
					cin >> id;

					found = false;
					index = 0;
					for (; index < 1000; index++) {
						if (students[index].id == 0)
							break;

						else
							if (students[index].id == id) {
								found = true;
								break;
							}
					}

					if (found) {
						system("cls");
						cout << "\n\n\n\tUPDATE STUDENT" << endl;
						cout << "\n\t Current information:" << endl;
						cout << "\n\tStudent ID: \t " << setfill('0') << setw(5) << students[index].id << '\n'
							<< " \tFirst-name: \t " << students[index].fname << '\n'
							<< " \tLast-name: \t " << students[index].lname << '\n'
							<< " \tGender: \t " << students[index].gender << '\n'
							<< " \tPhone no.: \t " << students[index].phone << '\n'
							<< " \tAddress: \t " << students[index].address << '\n'
							<< " \tNum of modules:  " << students[index].new_modules << '\n'
							<< " \tNum of repeats:  " << students[index].repeat_modules << endl;
						cout << "\t------------------------------------------------------------------------" << endl;

						cin.clear();
						cin.ignore(100000, '\n');

						cout << "\n\t Enter First-name: ";
						getline(cin, s.fname);

						cout << "\n\t Enter Last-name: ";
						getline(cin, s.lname);

						do {
							cout << "\n\t Enter Gender(M/F): ";
							cin >> s.gender;
						} while (s.gender != 'M' && s.gender != 'F' && s.gender != 'm' && s.gender != 'f');

						cin.clear();
						cin.ignore(100000, '\n');

						cout << "\n\t Enter Phone no.: ";
						getline(cin, s.phone);
						cout << "\n\t Enter Address: ";
						getline(cin, s.address);

						checker = false;
						do {
							checker = false;
							cout << "\n\t Enter Number of Modules: ";
							cin >> s.new_modules;
							cout << "\n\t Enter Number of Repeated Modules: ";
							cin >> s.repeat_modules;

							if (s.repeat_modules > 2 && s.new_modules > 0) {
								cout << "\n\t INVALID: Can only take max of 2 and min of 0 Repeated Module, Please Try Again.\n";
								checker = true;
							}
							else if ((s.new_modules + s.repeat_modules) > 6) {
								cout << "\n\t INVALID: Can only take max of 6 (new module + repeat) and min of 0, Please Try Again.\n";
								checker = true;
							}
						} while (checker);

						cout << "\n\t Are you sure you want to save the changes? (y/n): ";
						cin >> confirm2;

						if (confirm2 == "y" || confirm2 == "Y") {
							students[index] = s;
						}
						else
						{
							goto studentpage;
						}
					}
					else {
						cout << "\n\tRecord not found, Please Try again.\n\n";
					}
					
					saveSettings();
					cout << "\n";
					system("pause");
					goto studentpage;
					break;

				case 3:
					//DELETE STUDENT
					system("cls");
					cout << "\n\n\n\tDELETE STUDENT" << endl;
					cin.clear();
					cin.ignore(100000, '\n');
					id = 0;
					cout << "\n\t Enter Student ID you want to delete: ";
					cin >> id;

					found = false;
					index = 0;
					for (; index < 1000; index++) {
						if (students[index].id == 0)
							break;
						else
							if (students[index].id == id) {
								found = true;
								break;
							}
					}
					if (found) {
						system("cls");
						cout << "\n\n\n\tDELETE STUDENT\n" << endl;
						cout << "\n\tStudent ID: \t " << setfill('0') << setw(5) << students[index].id << '\n'
							<< " \tFirst-name: \t " << students[index].fname << '\n'
							<< " \tLast-name: \t " << students[index].lname << '\n'
							<< " \tGender: \t " << students[index].gender << '\n'
							<< " \tPhone no.: \t " << students[index].phone << '\n'
							<< " \tAddress: \t " << students[index].address << '\n'
							<< " \tNum of modules:  " << students[index].new_modules << '\n'
							<< " \tNum of repeats:  " << students[index].repeat_modules << endl;
						cout << "\t------------------------------------------------------------------------" << endl;
						cout << "\n\t Are you sure want to delete this Student Information (y/n): ";
						cin >> confirm;

						allowOnce = true;

						switch (confirm) {
						case 'Y':
						case 'y':
							for (int i = index; i < 1000; i++) {
								if (students[i].id == 0) {
									allowOnce = false;
								}
								if (!allowOnce) {
									break;
								}
								else {
									students[i] = students[i + 1];
								}
							}
							
							cout << "\n";
							system("pause");
							goto studentpage;

						default:
							cout << "\n";
							system("pause");
							goto studentpage;
						}
					}
					else
					{
						cout << "\n\tRecord not found, Please Try again.\n\n";
					}
					saveSettings();
					cout << "\n";
					system("pause");
					goto studentpage;
					break;

				case 4:
					//BALANCE INQUIRY
					system("cls");
					cout << "\n\n\n\tBALANCE INQUIRY" << endl;
					id = 0;
					cin.clear();
					cin.ignore(100000, '\n');
					cout << "\n\t Enter Student ID you want to check Balance: ";
					cin >> id;

					found = false;
					index = 0;
					for (; index < 1000; index++) {
						if (students[index].id == 0)
							break;
						else
							if (students[index].id == id) {
								found = true;
								break;
							}
					}
					if (found) {
						cout << "\n\tStudent ID: \t " << setfill('0') << setw(5) << students[index].id << endl;
						cout << " \tFirst-name: \t " << students[index].fname << endl;
						cout << " \tLast-name: \t " << students[index].lname << endl;
						cout << " \tNum of modules:  " << students[index].new_modules << endl;
						cout << " \tNum of repeats:  " << students[index].repeat_modules << endl;
						if ((((students[index].new_modules * module_price) + (students[index].repeat_modules * repeat_price)) - students[index].pay) < 0) {
							cout << "\tRemaining Balance: " << fixed << setprecision(2) << "( " << abs(((students[index].new_modules * module_price) + (students[index].repeat_modules * repeat_price)) - students[index].pay) << " )";
						}
						else {
							cout << "\tRemaining Balance: " << fixed << setprecision(2) << (((students[index].new_modules * module_price) + (students[index].repeat_modules * repeat_price)) - students[index].pay);
						}
					}
					else {
						cout << "\n\tRecord not found, Please Try again.\n\n";
					}

					cout << "\n";
					system("pause");
					goto studentpage;
					break;

				case 5:
					//PAY STUDENT
					system("cls");
					cout << "\n\n\n\tFEE DEPOSIT" << endl;
					cin.clear();
					cin.ignore(100000, '\n');
					cout << "\n\t Enter Student ID you want to check Balance: ";
					cin >> id;

					found = false;
					index = 0;
					for (; index < 1000; index++) {
						if (students[index].id == 0)
							break;

						else
							if (students[index].id == id) {
								found = true;
								break;
							}
					}
					if (found) {
						cout << "\n\tStudent ID: \t " << setfill('0') << setw(5) << students[index].id << endl;
						cout << " \tFirst-name: \t " << students[index].fname << endl;
						cout << " \tLast-name: \t " << students[index].lname << endl;
						cout << " \tTotal: \t\t " << ((students[index].new_modules * module_price) + (students[index].repeat_modules * repeat_price)) << endl;
						cout << " \tRemaining Balance: " << (((students[index].new_modules * module_price) + (students[index].repeat_modules * repeat_price)) - students[index].pay);

					tryagain:
						cout << "\n\n\t Enter Amount to pay: ";
						cin >> money;

						if (money > 0) {
							double balance = (((students[index].new_modules * module_price) + (students[index].repeat_modules * repeat_price)) - money);

							if (balance < 0) {
								cout << "\n\t Your Current Balance is now 0";
								students[index].pay += money;
							}
							else
							{
								cout << "\n\t Your Current Balance is now: " << balance;
								students[index].pay += money;
							}
						}
						else
						{
							cout << "\n\t Invalid input ammount, Please Try again";
							goto tryagain;
						}
					}
					else {
						cout << "\n\tRecord not found, Please Try again.\n\n";
					}
					saveSettings();
					cout << "\n";
					system("pause");
					goto studentpage;
					break;

				case 6:
					//DISPLAY STUDENT ZERO BALANCE
					system("cls");

					displayStudents(0);

					cout << "\n";
					system("pause");
					goto studentpage;
					break;

				case 7:
					//DISPLAY STUDENT NON ZERO
					system("cls");

					displayStudents(1);

					cout << "\n";
					system("pause");
					goto studentpage;
					break;

				case 8:
					// STUDENT SETTINGS
					system("cls");
					cout << "\n\n\n\tSETTINGS" << endl;

					cout << "\n\t Enter New Module Price: ";
					cin >> new_module_price;

					cout << "\n\t Enter New Repeat Price: ";
					cin >> new_repeat_price;

					cout << "\n\t Are you sure want to save the changes? (y/n): ";
					cin >> confirm;

					switch (confirm) {
					case 'y':
					case 'Y':
						module_price = new_module_price;
						saveSettings();

						repeat_price = new_repeat_price;
						saveSettings();

						cout << "\n";
						system("pause");
						goto studentpage;
						break;
					default:
						cout << "\n";
						system("pause");
						goto studentpage;
						break;
					}

					cout << "\n";
					system("pause");
					goto studentpage;
					break;

				case 9:
					saveSettings();
					goto loginpage;
					break;

				default:
					break;
				}

				LoggedIn = true;
				wrongUser = false;
				wrongPass = false;
			}
			else
			{
				wrongUser = false;
				wrongPass = true;
				goto loginpage;
			}
		}
		else if (username == "teacher")
		{
			if (pass == correct_password)
			{
			teacherpage:
				//LOGGED IN TEACHER ACCOUNT TYPE
				system("cls");
				cout << "\n\n\n\tTEACHER ADMIN HOMEPAGE" << endl;

				cout << "\n\n\t1. Add New Teacher" << endl;
				cout << "\n\t2. Update Teacher" << endl;
				cout << "\n\t3. Delete Teacher" << endl;
				cout << "\n\t4. Calculate salary of a teacher" << endl;
				cout << "\n\t5. Show all teacher" << endl;
				cout << "\n\t6. Settings" << endl;
				cout << "\n\t7. Logout" << endl;

				cout << "\n\n\t Enter choice: ";
				int choice;
				cin >> choice;

				Teacher t;
				string confirm;
				int index;
				int id;
				bool found;
				bool allowOnce;
				double ot, total, ha, ma, ta, net, base;
				int new_base_sal;
				//char confirm;
				string confirm2;


				switch (choice)
				{
				case 1:
					//ADD TEACHER
					system("cls");
					cout << "\n\n\n\tADD NEW TEACHER" << endl;
					cin.clear();
					cin.ignore(100000, '\n');
					cout << "\n\t New Teacher ID: " << setfill('0') << setw(5) << id_no << endl;
					t.id = id_no;

					cout << "\n\t Enter First-name: ";
					getline(cin, t.fname);

					cout << "\n\t Enter Last-name: ";
					getline(cin, t.lname);

					do {
						cout << "\n\t Enter Gender(M/F): ";
						cin >> t.gender;
					} while (t.gender != 'M' && t.gender != 'F' && t.gender != 'm' && t.gender != 'f');

					cin.clear();
					cin.ignore(100000, '\n');

					cout << "\n\t Enter Phone no.: ";
					getline(cin, t.phone);
					cout << "\n\t Enter Address: ";
					getline(cin, t.address);

					do {
						cout << "\n\t (1) Business\n"
							<< "\t (2) Computing \n"
							<< "\t Department: ";
						cin >> t.dept;
					} while (t.dept != 1 && t.dept != 2);
					do {
						cout << "\n\t Designation: ([1] HOF/[2] CO/[3] L): ";
						cin >> t.desig;
					} while (t.desig != 1 && t.desig != 2 && t.desig != 3);

					cout << "\n\t Enter no. of Teaching Hours: ";
					cin >> t.work_hrs;

					cout << "\n\t Are you sure you want to add new teacher? (y/n): ";
					cin >> confirm;

					if (confirm == "y" || confirm == "Y") {
						index = 0;
						for (index = 0; index < 1000; index++) {
							if (teachers[index].id == 0)
								break;
						}
						teachers[index] = t;
						id_no++;
					}
					else
					{
						goto teacherpage;
					}
					saveSettings();
					system("pause");
					cout << "\n";
					goto teacherpage;
					break;

				case 2:
					//UPDATE TEACHER
					system("cls");
					cout << "\n\n\n\tUPDATE TEACHER" << endl;
					cin.clear();
					cin.ignore(100000, '\n');
					cout << "\n\t Enter Teacher ID you want to edit: ";
					cin >> id;

					found = false;
					index = 0;
					for (; index < 1000; index++) {
						if (teachers[index].id == 0)
							break;
						else
							if (teachers[index].id == id) {
								found = true;
								break;
							}
					}

					if (found) {
						system("cls");
						cout << "\n\n\n\tUPDATE TEACHER" << endl;
						cout << "\n\t Current information:" << endl;
						cout << "\n\tTeacher ID: \t " << setfill('0') << setw(5) << teachers[index].id << "\n"
							<< " \tFirst-name: \t " << teachers[index].fname << "\n"
							<< " \tLast-name: \t " << teachers[index].lname << "\n"
							<< " \tGender: \t " << teachers[index].gender << "\n"
							<< " \tPhone no.: \t " << teachers[index].phone << "\n"
							<< " \tAddress: \t " << teachers[index].address << "\n";
						cout << "\tDepartment: " << teachers[index].dept << endl;
						cout << "\tDesignation: " << teachers[index].desig << endl;
						cout << "\tNo. of Teaching Hours: " << teachers[index].work_hrs << endl;
						cout << "\t------------------------------------------------------------------------" << endl;
						cin.clear();
						cin.ignore(100000, '\n');
						t.id = teachers[index].id;

						cout << "\n\t Enter First-name: ";
						getline(cin, t.fname);

						cout << "\n\t Enter Last-name: ";
						getline(cin, t.lname);

						do {
							cout << "\n\t Enter Gender(M/F): ";
							cin >> t.gender;
						} while (t.gender != 'M' && t.gender != 'F' && t.gender != 'm' && t.gender != 'f');

						cin.clear();
						cin.ignore(100000, '\n');

						cout << "\n\t Enter Phone no.: ";
						getline(cin, t.phone);
						cout << "\n\t Enter Address: ";
						getline(cin, t.address);

						do {
							cout << "\n\t (1) Business\n"
								<< "\t (2) Computing \n"
								<< "\t Department: ";
							cin >> t.dept;
						} while (t.dept != 1 && t.dept != 2);
						do {
							cout << "\n\t Designation: ([1] HOF/[2] CO/[3] L): ";
							cin >> t.desig;
						} while (t.desig != 1 && t.desig != 2 && t.desig != 3);

						cout << "\n\t Enter no. of Teaching Hours: ";
						cin >> t.work_hrs;

						cout << "\n\t Are you sure you want to edit this Teacher? (y/n): ";
						cin >> confirm2;

						if (confirm2 == "y" || confirm2 == "Y") {
							teachers[index] = t;
						}
						else
						{
							goto teacherpage;
						}
					}
					else {
						cout << "\n\tRecord not found, Please Try again.\n\n";
					}
					saveSettings();
					cout << "\n";
					system("pause");
					goto teacherpage;
					break;

				case 3:
					// DELETE TEACHER
					system("cls");
					cout << "\n\n\n\tDELETE TEACHER" << endl;
					id = 0;
					cin.clear();
					cin.ignore(100000, '\n');
					cout << "\n\t Enter Teacher ID you want to delete: ";
					cin >> id;

					found = false;
					index = 0;
					for (; index < 1000; index++) {
						if (teachers[index].id == 0)
							break;

						else
							if (teachers[index].id == id) {
								found = true;
								break;
							}
					}

					if (found) {
						system("cls");
						cout << "\n\n\tTeacher ID: \t " << setfill('0') << setw(5) << teachers[index].id << '\n'
							<< " \tFirst-name: \t " << teachers[index].fname << '\n'
							<< " \tLast-name: \t " << teachers[index].lname << '\n'
							<< " \tGender: \t " << teachers[index].gender << '\n'
							<< " \tPhone no.: \t " << teachers[index].phone << '\n'
							<< " \tAddress: \t " << teachers[index].address << '\n';
						cout << "\tDepartment: " << teachers[index].dept << endl;
						cout << "\tDesignation: " << teachers[index].desig << endl;
						cout << "\tNo. of Teaching Hours: " << teachers[index].work_hrs << endl;
						cout << "\t------------------------------------------------------------------------" << endl;
						cout << "\n\t Are you sure want to delete this Teacher Information (y/n): ";
						cin >> confirm;

						allowOnce = true;
						if (confirm == "y" || confirm == "Y") {
							for (int i = index; i < 1000; i++) {
								if (teachers[i].id == 0) {
									allowOnce = false;
								}
								if (!allowOnce) {
									break;
								}
								else {
									teachers[i] = teachers[i + 1];
								}
							}
						}
					}
					else
					{
						cout << "\n\tRecord not found, Please Try again.\n\n";
					}
					saveSettings();
					cout << "\n";
					system("pause");
					goto teacherpage;
					break;

				case 4:
					//CALCULATE TEACHER SALARY
					system("cls");
					cout << "\n\n\n\tCALCULATE SALARY" << endl;
					cin.clear();
					cin.ignore(100000, '\n');
					cout << "\n\t Enter Teacher ID you want to calculate salary: ";
					cin >> id;

					found = false;
					index = 0;
					for (; index < 1000; index++) {
						if (teachers[index].id == 0)
							break;

						else
							if (teachers[index].id == id) {
								found = true;
								break;
							}
					}

					if (found) {
						double ot, total, ha, ma, ta, net;
						cout << "\n\n\tTeacher ID: " << setfill('0') << setw(5) << teachers[index].id << endl;
						cout << "\tDepartment: " << teachers[index].dept << endl;
						cout << "\tDesignation: " << teachers[index].desig << endl;
						cout << "\tNo. of Teaching Hours: " << teachers[index].work_hrs << endl;

						cout << "\n\tBase Salary: " << fixed << setprecision(2) << base_sal << endl;
						switch (teachers[index].desig) {
						case 1:
							if ((teachers[index].work_hrs - 8) >= 0) {
								ot = (teachers[index].work_hrs - 8) * 325;
							}
							else {
								ot = 0;
							}
							break;
						case 2:
							if ((teachers[index].work_hrs - 13) >= 0) {
								ot = (teachers[index].work_hrs - 13) * 325;
							}
							else {
								ot = 0;
							}
							break;
						case 3:
							if ((teachers[index].work_hrs - 18) >= 0) {
								ot = (teachers[index].work_hrs - 18) * 325;
							}
							else {
								ot = 0;
							}
							break;
						}
						total = base_sal + ot;
						ha = total * 0.10;
						ma = total * 0.03;
						ta = total * 0.05;
						net = total + ha + ma + ta;
						cout << "\n\tTotal Salary: " << fixed << setprecision(2) << total << endl;
						cout << "\n\tOvertime: " << fixed << setprecision(2) << ot << endl;
						cout << "\tHousing allowance: " << fixed << setprecision(2) << ha << endl;
						cout << "\tMedical allowance: " << fixed << setprecision(2) << ma << endl;
						cout << "\tTransport allowance: " << fixed << setprecision(2) << ta << endl;
						cout << "\n\n\tNet Salary: " << fixed << setprecision(2) << net << endl;;

					}
					else {
						cout << "\n\tRecord not found, Please Try again.\n\n";
					}

					cout << "\n";
					system("pause");
					goto teacherpage;
					break;

				case 5:
					//DISPLAY ALL TEACHERS
					system("cls");
					cout << "\n\n\n\tLIST OF ALL TEACHERS\n" << endl;

					for (int index = 0; index < 1000; index++) {
						if (teachers[index].id == 0)
							break;
						else {
							cout << "\n\tTeacher ID: " << setfill('0') << setw(5) << teachers[index].id << endl;
							cout << "\tFirst Name: " << teachers[index].fname << endl;
							cout << "\tLast Name: " << teachers[index].lname << endl;
							cout << "\tGender: " << teachers[index].gender << endl;
							cout << "\tPhone no.: " << teachers[index].phone << endl;
							cout << "\tAddress: " << teachers[index].address << endl;
							cout << "\tDepartment: " << teachers[index].dept << endl;
							cout << "\tDesignation: " << teachers[index].desig << endl;
							cout << "\tNo. of Teaching Hours: " << teachers[index].work_hrs << endl;
							cout << "\n\t------------------------------------------------------------------------" << endl;
						}
					}

					cout << "\n";
					system("pause");
					goto teacherpage;
					break;

				case 6:
					//TEACHERS SETTINGS
					system("cls");
					cout << "\n\n\n\tSETTINGS" << endl;

					cout << "\n\t Enter New Salary Price: ";
					cin >> new_base_sal;

					cout << "\n\t Are you sure want to save the changes? (y/n): ";
					cin >> confirm;

					if (confirm == "y" || confirm == "Y") {
						base_sal = new_base_sal;
						saveSettings();
					}
					else
					{
						cout << "\n\tNo Changes Made\n\n";
					}

					cout << "\n";
					system("pause");
					goto teacherpage;
					break;

				case 7:
					//LOGOUT
					saveSettings();
					goto loginpage;
					break;

				default:
					cout << "LOL";
					system("pause");
					break;
				}

				LoggedIn = true;
				wrongUser = false;
				wrongPass = false;
			}
			else {
				wrongUser = false;
				wrongPass = true;
				goto loginpage;
			}
		}
		else
		{
			wrongUser = true;
			wrongPass = false;
			goto loginpage;
		}
	}

	system("pause");
	return 0;
}

void openSettings() {
	ifstream infile;
	string getfile;
	int lines;
	infile.open("settings.config");
	if (!infile.is_open()) {
		infile.close();
		ofstream outfile;
		outfile.open("settings.config");
		outfile << "525\n110\n1200\n1\n1";
		outfile.close();
		module_price = 525;
		repeat_price = 110;
		base_sal = 1200;
		id_no = 1;
	}
	else {
		infile >> module_price;
		infile >> repeat_price;
		infile >> base_sal;
		infile >> id_no;
		infile.close();
	}
	infile.open("students.dat");
	if (!infile.is_open()) {
		infile.close();
		ofstream outfile;
		outfile.open("students.dat");
		outfile.close();
	}
	else {
		int i = 0;
		for (i = 0; i < 1000; i++) {
			if (infile.eof()) break;
			infile >> students[i].id;
			infile >> students[i].fname;
			infile >> students[i].lname;
			infile >> students[i].gender;
			infile >> students[i].phone;
			infile >> students[i].address;
			infile >> students[i].new_modules;
			infile >> students[i].repeat_modules;
			infile >> students[i].pay;
		}
		infile.close();
	}
	infile.open("teachers.dat");
	if (!infile.is_open()) {
		infile.close();
		ofstream outfile;
		outfile.open("teachers.dat");
		outfile.close();
	}
	else {
		int i = 0;
		for (i = 0; i < 1000; i++) {
			if (infile.eof()) break;
			infile >> teachers[i].id;
			infile >> teachers[i].fname;
			infile >> teachers[i].lname;
			infile >> teachers[i].gender;
			infile >> teachers[i].phone;
			infile >> teachers[i].address;
			infile >> teachers[i].dept;
			infile >> teachers[i].desig;
			infile >> teachers[i].work_hrs;
		}
		infile.close();
	}
}

void saveSettings() {
	ofstream outfile;
	outfile.open("settings.config");
	outfile << module_price << "\n" << repeat_price << "\n" << base_sal << "\n" << id_no;
	outfile.close();
	outfile.open("students.dat");
	for (int index = 0; index < 1000; index++) {
		if (students[index].id == 0)
			break;
		else {
			outfile << students[index].id << endl
				<< students[index].fname << endl
				<< students[index].lname << endl
				<< students[index].gender << endl
				<< students[index].phone << endl
				<< students[index].address << endl
				<< students[index].new_modules << endl
				<< students[index].repeat_modules << endl
				<< students[index].pay << endl;
		}
	}
	outfile.close();
	outfile.open("teachers.dat");
	for (int index = 0; index < 1000; index++) {
		if (teachers[index].id == 0)
			break;
		else {
			outfile << teachers[index].id << endl
				<< teachers[index].fname << endl
				<< teachers[index].lname << endl
				<< teachers[index].gender << endl
				<< teachers[index].phone << endl
				<< teachers[index].address << endl
				<< teachers[index].dept << endl
				<< teachers[index].desig << endl
				<< teachers[index].work_hrs << endl;
		}
	}
	outfile.close();
}

void displayStudents(int num) {
	if (num == 0) {
		cout << "\n\n\n\tLIST OF STUDENTS WITH ZERO BALANCE" << endl;
		cout << "\n\t--------------------------------------" << endl;
		for (int index = 0; index < 1000; index++) {
			if (students[index].id == 0)
				break;
			else {
				if ((((students[index].new_modules * module_price) + (students[index].repeat_modules * repeat_price)) - students[index].pay) <= 0) {

					cout << "\n\tStudent ID: \t " << setfill('0') << setw(5) << students[index].id << endl;
					cout << " \tFirst-name: \t " << students[index].fname << endl;
					cout << " \tLast-name: \t " << students[index].lname << endl;
					cout << "\tGender: " << students[index].gender << endl;
					cout << "\tPhone no.: " << students[index].phone << endl;
					cout << "\tAddress: " << students[index].address << endl;
					cout << "\tNumber of modules: " << students[index].new_modules << endl;
					cout << "\tNumber of repeated modules: " << students[index].repeat_modules << endl;
					cout << "\tBalance: 0";
					cout << "\n\t------------------------------------------------------------------------" << endl;
				}
			}
		}
	}
	else {
		cout << "\n\n\n\tLIST OF STUDENTS WITH NON-ZERO BALANCE" << endl;
		cout << "\n\t--------------------------------------" << endl;
		for (int index = 0; index < 1000; index++) {
			if (students[index].id == 0)
				break;
			else {
				if ((((students[index].new_modules * module_price) + (students[index].repeat_modules * repeat_price)) - students[index].pay) > 0) {
					cout << "\n\tStudent ID: \t " << setfill('0') << setw(5) << students[index].id << endl;
					cout << " \tFirst-name: \t " << students[index].fname << endl;
					cout << " \tLast-name: \t " << students[index].lname << endl;
					cout << "\tGender: " << students[index].gender << endl;
					cout << "\tPhone no.: " << students[index].phone << endl;
					cout << "\tAddress: " << students[index].address << endl;
					cout << "\tNumber of modules: " << students[index].new_modules << endl;
					cout << "\tNumber of repeated modules: " << students[index].repeat_modules << endl;
					cout << "\tBalance: " << (((students[index].new_modules * module_price) + (students[index].repeat_modules * repeat_price)) - students[index].pay) << endl;
					//cout << students[index].pay << ' ' << students[index].new_modules << ' ' << module_price << ' ' << students[index].repeat_modules << ' ' << repeat_price << endl;
					cout << "\n\t------------------------------------------------------------------------" << endl;
				}
			}
		}
	}
}
