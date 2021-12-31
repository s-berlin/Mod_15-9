#include "hash_table.h"
#include <iostream>

using namespace std;

HashTable::HashTable() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}
HashTable::~HashTable() {
    delete[] array;
}
void HashTable::add(ChatMember ch_log, ChatMember ch_pas) {
    int i = 0;
    int index = -1;
    // берем пробы по всем i от 0 до размера массива
    for (i = 0; i < mem_size; i++) {
        index = hash_func(ch_log, i);
        cout << "add: index = " << index << endl;
        if (array[index].status == enPairStatus::free || array[index].status == enPairStatus::deleted) {
            // найдена пуста€ €чейка, занимаем ее
            break;
        }
    }
    if (i >= mem_size) return; // все перебрали, нет места

    // кладем в свободную €чейку пару
    array[index] = Pair(ch_log, ch_pas);
    count++;
    cout << "add: count = " << count << endl;
}

bool HashTable::find(ChatMember ch_log) {
 
    for (int i = 0; i < mem_size; i++) {
        bool OK = false;
        int index = hash_func(ch_log, i);
        cout << "find: index = " << index << endl;
        if (array[index].status == enPairStatus::free) {
            // найдена пуста€ €чейка, false
            cout << "find: array[" << index << "].status = free" << endl;
            return false;
        }       
        if (array[index].status == enPairStatus::engaged) {
            cout << "find: array[" << index << "].status = engaged" << endl;
            // найдена зан€та€ €чейка, провер€ем
            OK = true;
            for (int j = 0; j < LOGINLENGTH; j++) {
                cout << "find: array[" << index << "].chat_log[" << j <<"] = " << array[index].chat_log[j];
                cout << "    ch_log[" << j << "] = " << ch_log[j] << endl;
                if (array[index].chat_log[j] != ch_log[j]) OK = false;
            }
        }
        if (array[index].status == enPairStatus::deleted) continue;
        if (i >= mem_size) return false; // все перебрали, не нашли
        return OK;
    }
}

/*
void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {

    if (!login(_login, _pass, pass_length))
    {
        AuthData* new_user = new AuthData(_login, sha1(_pass, pass_length));
        data[data_count] = *new_user;
        data_count++;

    }
    else {
        std::cout << "user already registered";
    }

}
*/
/*
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    if (_login && pass_length)
    {
        std::cout << "    log=" << _login << "    pass=" << _pass << endl;
        AuthData verifyData(_login, sha1(_pass, pass_length));
        for (int i = 0; i < data_count; i++)
        {
            if (!strcmp(verifyData.login, data[i].login) &&
                !memcmp(data[i].pass_sha1_hash, verifyData.pass_sha1_hash, SHA1HASHLENGTHBYTES))
            {
                return true;
            }
            else {
                return false;
            }
        }
    }
    else {
        return false;
    }
}
*/
void HashTable::show() {
    setlocale(LC_ALL, "");

    for (int i = 0; i < mem_size; i++) {
        cout << "array[" << i << "].chat_log = " << array[i].chat_log << "      ";
        for( int j = 0; j < 10; j++) cout << array[i].chat_pass[j];
        cout << endl;
        //"  status = " << array[i].status << endl;
    }
    return;
}
int HashTable::hash_func(ChatMember ch_log, int offset) {
    // calculating the index
    int sum = 0;
    for (int i = 0; i < LOGINLENGTH; i++) {
        sum += ch_log[i];
        cout << " hash_func: ch_log[" << i << "] = " << ch_log[i] << "     sum = " << sum << endl;
    }
    cout << " hash_func: sum = " << sum << "   return " << (sum % mem_size + offset*offset) % mem_size << endl;

    // линейные пробы
    return (sum % mem_size + offset*offset) % mem_size;
}
