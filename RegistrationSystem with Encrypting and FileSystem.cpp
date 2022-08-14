/*

	Title			: Registration System with SHA-256 Encrypting and FileSystem
	Language		: C++
	Author			: Wojciech Jastrzebowski
	Date Created	: 13-08-2022

*/

#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>
#include <iomanip>
#include "sha256.h"
#include "sha256.cpp"

using namespace std;

bool IsCorrect(string username, string password) {
	int unlength = username.size();
	int pwlength = password.size();

	if (unlength < 8) {
		return false;
	}
	if (pwlength < 8) {
		return false;
	}
	return true;
}
bool IsAlreadyRegistered(string username, string password) {
	string un;

	ifstream myFile("users.txt", ios::in);
	if (!myFile) {
		cerr << setw(25) << "Cannot open file\n";
		exit(1);
	}
	else {
		while (myFile >> un)
		{
			if (un == username)
			{
				return false;
			}
		}
	}
	return true;
}
bool IsLoggedIn() {
	string username, password, un, pw, hashpw;
	int linecount = 0;

	SHA256 sha256;

	cout << setw(29) << "Enter your Username: ";
	cin >> username;
	cout << setw(29) << "Enter your Password: ";
	cin >> password;

	ifstream myFile("users.txt", ios::in);
	if (!myFile) {
		cerr << setw(25) << "Cannot open file\n";
		exit(1);
	}
	else {
		while (myFile >> un)
		{
			linecount++;
			if (un == username)
			{
				break;
			}
		}
	}

	myFile.seekg(0);

	for (int i = 0; getline(myFile, pw) && i < (linecount+1); i++) {
		if (i == (linecount)) {
			break;
		}
	}
	hashpw = sha256(password);
	if (un == username && pw == hashpw) {
		return true;
	}
	else {
		return false;
	}
}
int main() {

	int option = 0, line_no = 0, count = 0;
	string optioncheck;
loop:
	cout << "|" << setw(30) << "Registration System 1.0" << setw(9) << "|\n";
	cout << "|" << "-------------------------------------" << "|\n";
	cout << "|" << setw(18) << "1: REGISTER" << setw(21) << "|\n";
	cout << "|" << setw(15) << "2: LOGIN" << setw(24) << "|\n";
	cout << "|" << setw(23) << "0: CLOSE PROGRAM" << setw(16) << "|\n";
	cout << "|" << "_____________________________________" << "|\n";
	cout << setw(28) << "Choose Your Option: ";
	cin >> optioncheck;

	for (int i = 0; i < optioncheck.length(); i++)
	{
		if (isdigit(optioncheck[i]) == false)
		{
			count = 1;
			break;
		}
		else
			count = 0;
	}

	if (count == 0) {
		int option = stoi(optioncheck);
		switch (option) {
		case 1: {
			string username, password, hashpw;
			ofstream myFile("users.txt", ios::app);
			SHA256 sha256;

			cout << setw(24) << "Enter username: ";
			cin >> username;
			cout << setw(24) << "Enter password: ";
			cin >> password;

			bool status1 = IsCorrect(username, password);
			bool status2 = IsAlreadyRegistered(username, password);
			
			if (!status1) {
				cout << setw(51) << "Username or/and password are wrong specifed!\n";
				cout << setw(69) << "(The username and password must have at least 8 characters)\n\n";
				goto loop;
			}
			else if (!status2) {
				cout << setw(37) << "Username are already in use!\n";
				cout << setw(48) << "Please use another username or log in!\n\n";
				goto loop;
			}
			else {
				hashpw = sha256(password);
				
				myFile << username << endl << hashpw << endl;
				myFile.close();
				cout << setw(34) << "Registered successfully!\n\n";
				goto loop;
			}
		}
		case 2: {
			bool status = IsLoggedIn();
			if (!status) {
				cout << setw(41) << "Username or Password are false!\n\n";
				goto loop;
			}
			else {
				cout << setw(32) << "Succesfully logged in!\n\n";
				system("PAUSE");
				return 1;
			}
		}
		case 0: {
			system("PAUSE");
			return 0;
		}
		default: {
			cout << setw(49) << "The wrong parameter has been specified!\n\n";
			goto loop;
		}
		}
	}
	else {
		cout << setw(49) << "The wrong parameter has been specified!\n\n";
		goto loop;;
	}
	return 0;
}
