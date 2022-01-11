#include <iostream>
#include <string>
#include "hash_table.h"

using namespace std;

bool pr = false; // Need debugging printing 

int main()
{
//	setlocale(LC_ALL, "");
	char login[LOGINLENGTH] = {};
	char input_str[LOGINLENGTH] = {};
	char password[LOGINLENGTH] = {};
//	cout << endl << "Select action:  \n   1 - Registration\n   2 - Authorization\n   3 - Search \n   4 - Delete \n   0 - Exit " << endl << "";
	int pass_length = 0;

	int act = 5;

	HashTable ht;
	
	cout << "If you need debugging printing, enter 1, else enter 0: ";
	cin >> pr;
	
	while (act != 0) {
		while (act != 0 && act != 1 && act != 2 && act != 3 && act != 4 && strlen(input_str) != 1) {
			cout << "\nSelect action:  \n   1 - Registration\n   2 - Authorization\n   3 - Search \n   4 - Delete \n   0 - Exit " << endl << "";
			cin >> input_str;
			act = input_str[0] - 48;
		}		
		
		switch (act) {
		case 1:
			cout << "Registration: enter your login: ";
			cin >> login;
			if (ht.find(login)) { cout << "\n Login: " << login << " is already registered" << endl; break; }

			cout << "Registration: enter the password: ";
			cin >> password;
			pass_length = strlen(password);
			if (pr) cout << "Registration: introduced login: " << login << "   password: " << password << "   length: " << pass_length << endl;
			ht.reg(login, password, pass_length);
			ht.show();
			break;
		case 2:
			cout << "Authorization: enter your login: ";
			cin >> login;
			cout << "Authorization: enter the password: ";
			cin >> password;
			pass_length = strlen(password);
			if (ht.login(login, password, pass_length)) cout << "Authorization: introduced login: " << login << "   password: " << password << "   rezult: Yes " << endl;
			else 	cout << "Authorization: introduced login: " << login << "   rezult: No" << endl;
			break;
		case 3:
			cout << "Find login: ";
			cin >> login;
			if (ht.find(login))	cout << "Find: introduced login: " << login << "   rezult: Yes" << endl;
			else 	cout << "Find: introduced login: " << login << "   rezult: No" << endl;
			break;
		case 4:
			cout << "Delete login: ";
			cin >> login;
			if (ht.find(login)) {
				ht.del(login);
				cout << "Delete: introduced login: " << login << endl;
			}
			else cout << "Delete: introduced login: " << login << " - not found " << endl;
			ht.show();
			break;
		default: break;

		}
		if (act != 0) {
			act = 5;
			input_str[0] = 0;
		}
	}

	ht.show();

}
