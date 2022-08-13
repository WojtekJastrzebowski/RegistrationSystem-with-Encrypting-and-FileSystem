﻿#include <iostream>
#include <fstream>
#include <string>
#include <openssl/sha.h>

using namespace std;

bool IsLoggedIn() {
	string username, password, un, pw;
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
			if (un == username)
			{
				cout << "Username found here!" << endl;
				getline(myFile, un);
				getline(myFile, pw);
			}
		}
	}


	if (un == username && pw == password) {
		return true;
	}
	else {
		return false;
	}


}

int main() {
	int option = 0, line_no = 0, count;
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
			string username, password;

			cout << "Enter username: ";
			cin >> username;
			cout << "Enter password: ";
			cin >> password;

			ofstream myFile("users.txt", ios::app);
			myFile << username << endl << password << endl;
			myFile.close();

			cout << "Registered successfully!\n\n";
			goto loop;
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
