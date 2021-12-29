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
        if (array[index].status == enPairStatus::free) {
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }
    if (i >= mem_size) return; // все перебрали, нет места

    // кладем в свободную ячейку пару
    array[index] = Pair(ch_log, ch_pas);
    count++;
}
/*
void HashTable::find(ChatMember ch_log) {
    int i = 0;
    int index = -1;
    // берем пробы по всем i от 0 до размера массива
    for (i = 0; i < mem_size; i++) {
        index = hash_func(ch_log, i);
        cout << "add: index = " << index << endl;
        if (array[index].status == enPairStatus::free) {
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }
    if (i >= mem_size) return; // все перебрали, нет места

    // кладем в свободную ячейку пару
    array[index] = Pair(ch_log, ch_pas);
    count++;
}
*/
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

    for (int i = 0; i < count; i++) {
        cout << "array[" << i << "].chat_log = " << array[i].chat_log << "      ";
        for( int j = 0; j < 10; j++) cout << array[i].chat_pass[j];
        cout << endl;
        //"  status = " << array[i].status << endl;
    }
    return;
}
int HashTable::hash_func(ChatMember ch_log, int offset) {
    // calculating the index
    int prod = 1;
    for (int i = 0; i < LOGINLENGTH; i++) {
        prod *= ch_log[i];
    }
    // cout << " hash_func: sum = " << sum << endl;

    // линейные пробы
    return (prod % mem_size + offset) % mem_size;
}
