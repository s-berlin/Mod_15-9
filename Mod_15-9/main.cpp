#include <iostream>
#include <string>
#include "hash_table.h"

using namespace std;
int main()
{
	setlocale(LC_ALL, "");
	char login[LOGINLENGTH];
	char password[20] = {};
	cout << endl << "Возможные действия:  \n   1 - Registration\n   2 - Authorization\n   0 - Exit " << endl << "";
	int pass_length = 0;
	char* ch_log; 
	char* ch_pass;
	int act = 1;

	HashTable ht;

	while (act != 0) {
		cout <<  "Select action: ";
		cin >> act;
		
		switch (act) {
		case 1:
			cout << endl << "Registration: enter your login: ";
			cin >> login;
			cout << "Registration: enter the password: ";
			cin >> password;
			pass_length = strlen(password);
			cout << "Registration: introduced login: " << login << "   password: " << password << "   length: " << pass_length << endl;
//			ht.reg(login, password, pass_length);
			ht.add(login, password);
			break;
		case 2:
			cout << endl << "Authorization: enter your login: ";
			cin >> login;
			cout << "Authorization: enter the password: ";
			cin >> password;
			pass_length = strlen(password);
			cout << "Authorization: introduced login: " << login << "   password: " << password << "   length: " << pass_length << endl;
			break;
		default: break;

		}

	}

	ht.show();

	// FruitName fr_name3 = "orange";

	//ht.find((char*)"orange");

//	cout << endl << "  ht.find orange" << "      count = " << ht.find((char*)"orange") << endl;

	//ht.del(fr_name3);
//	ht.del((char*)"orange");

//	ht.show();


//	cout << endl << "  ht.find orange"  << "      count = " << ht.find((char*)"orange") << endl;

}
