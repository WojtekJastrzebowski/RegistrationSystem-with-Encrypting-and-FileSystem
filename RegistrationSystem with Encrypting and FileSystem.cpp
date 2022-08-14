
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
		cerr << "Cannot open file\n";
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

	cout << "Enter your Username: ";
	cin >> username;
	cout << "Enter your Password: ";
	cin >> password;

	ifstream myFile("users.txt", ios::in);
	if (!myFile) {
		cerr << "Cannot open file\n";
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
	cout << "Registration System 1.0\n";
	cout << "1: Register\n";
	cout << "2: LogIn\n";
	cout << "0: Close Program\n\n";
	cout << "Choose Option: ";
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

			SHA256 sha256;

			cout << "Enter username: ";
			cin >> username;
			cout << "Enter password: ";
			cin >> password;

			bool status1 = IsCorrect(username, password);
			bool status2 = IsAlreadyRegistered(username, password);
			
			if (!status1) {
				cout << "Username or/and password are wrong specifed!\n";
				cout << "(The username and password must have at least 8 characters)\n\n";
				goto loop;
			}
			else if (!status2) {
				cout << "Username are already in use!\n";
				cout << "Please use another username or log in!\n\n";
				goto loop;
			}
			else {
				hashpw = sha256(password);
				ofstream myFile("users.txt", ios::app);
				myFile << username << endl << hashpw << endl;
				myFile.close();
				cout << "Registered successfully!\n\n";
				goto loop;
			}
		}
		case 2: {
			bool status = IsLoggedIn();
			if (!status) {
				cout << "Username or Password are false!\n\n";
				goto loop;
			}
			else {
				cout << "Succesfully logged in!\n\n";
				system("PAUSE");
				return 1;
			}
		}
		case 0: {
			system("PAUSE");
			return 0;
		}
		default: {
			cout << "The wrong parameter has been specified!\n\n";
			goto loop;
		}
		}
	}
	else {
		cout << "The wrong parameter has been specified!\n\n";
		goto loop;;
	}
	return 0;
}
