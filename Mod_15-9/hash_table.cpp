#include "hash_table.h"
#include "hf2.h"
#include <iostream>
#include <iomanip>

using namespace std;

extern bool pr;

HashTable::HashTable() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}
HashTable::~HashTable() {
    delete[] array;
}
void HashTable::reg(ChatMember ch_log, char ch_pas[], int pass_length) {
    double hps;
    int i = 0;
    int index = -1;
    // we take samples for all i from 0 to the size of the array
    for (i = 0; i < mem_size; i++) {
        index = hash_func(ch_log, i);
        if (pr) cout << "reg: index = " << index << endl;
        if (array[index].status == enPairStatus::free || array[index].status == enPairStatus::deleted) {
            // an empty cell is found, we occupy it
            break;
        }
    }
    if (i == mem_size) return; // everything has been sorted out, there is no place

    // we put a pair in a free cell
    hps = hf2(ch_pas, pass_length);
    array[index] = Pair(ch_log, hps);
    count++;
    if (pr) cout << "reg: count = " << count << endl;
}

bool HashTable::find(ChatMember ch_log) {
    int index = -1;
    bool OK = false;
    for (int i = 0; i < mem_size; i++) {
        index = hash_func(ch_log, i);
        if (pr) cout << "find: index = " << index << endl;
        if (array[index].status == enPairStatus::free) {
            // an empty cell was found, false
            if (pr) cout << "find: array[" << index << "].status = free" << endl;
            return false;
        }
        if (array[index].status == enPairStatus::deleted) continue;
        if (array[index].status == enPairStatus::engaged) {
            if (pr) cout << "find: array[" << index << "].status = engaged" << endl;
            // an occupied cell is found, we check
            OK = true;
            for (int j = 0; j < strlen(ch_log); j++) {
                if (pr) cout << "find: array[" << index << "].chat_log[" << j <<"] = " << array[index].chat_log[j];
                if (pr) cout << "    ch_log[" << j << "] = " << ch_log[j] << endl;
                if (array[index].chat_log[j] != ch_log[j]) OK = false;
            }
            if (OK) return true;
        }
        if (i >= mem_size) return false; // we went through everything, we didn't find it
    }
    return false;
}

void HashTable::show() {
    setlocale(LC_ALL, "");
    if (pr) cout << "show: mem_size = " << mem_size << endl;
    for (int i = 0; i < mem_size; i++) {
        if (array[i].status != 0) {
            cout << "show:   array[" << setw(2) << i << "].chat_log = " << setw(20) << array[i].chat_log << "      ";
            cout << setw(10) << array[i].pass_hf2_hash;
            cout << "  status = " << array[i].status << endl;
        }
    }
    if (3 * count > 2 * mem_size) {
        resize();
        if (pr) cout << "show: after resize mem_size = " << mem_size << endl;
        for (int i = 0; i < mem_size; i++) {
            if (array[i].status != 0) {
                cout << "show:   array[" << setw(2) << i << "].chat_log = " << setw(20) << array[i].chat_log << "      ";
                cout << setw(10) << array[i].pass_hf2_hash;
                cout << "  status = " << array[i].status << endl;
            }
        }
    }
    return;
}

void HashTable::del(ChatMember ch_log) {
    int index = -1;
    bool OK = false;
    for (int i = 0; i < mem_size; i++) {
        index = hash_func(ch_log, i);
        if (pr) cout << "del: index = " << index << endl;
        if (array[index].status == enPairStatus::free) {
            // an empty cell was found, false
            if (pr) cout << "del: array[" << index << "].status = free      login not found" << endl;
            return;
        }
        if (array[index].status == enPairStatus::deleted) continue;
        if (array[index].status == enPairStatus::engaged) {
            if (pr) cout << "del: array[" << index << "].status = engaged" << endl;
            // an occupied cell is found, we check
            OK = true;
            for (int j = 0; j < strlen(ch_log); j++) {
                if (pr) cout << "del: array[" << index << "].chat_log[" << j << "] = " << array[index].chat_log[j];
                if (pr) cout << "    ch_log[" << j << "] = " << ch_log[j] << endl;
                if (array[index].chat_log[j] != ch_log[j]) OK = false;
            }
            if (OK) {
                array[index].status = enPairStatus::deleted;
                array[index].pass_hf2_hash = 0;
                for (int j = 0; j < LOGINLENGTH; j++) array[index].chat_log[j] = ' ';
                cout << "login " << ch_log << " deleted " << endl;
                return;
            }
        }
    }
    cout << "login " << ch_log << " not found" << endl;
    return;
}

int HashTable::hash_func(ChatMember ch_log, int offset) {
    // calculating the index
    int login_length = strlen(ch_log);
    int sum = 0;
    if (pr) cout << " hash_func: mem_size = " << mem_size << endl;
    for (int i = 0; i < login_length; i++) {
        sum += ch_log[i];
        if (pr) cout << " hash_func: ch_log[" << i << "] = " << ch_log[i] << "     sum = " << sum << endl;
    }
    if (pr) cout << " hash_func: sum = " << sum << "   return " << (sum % mem_size + offset*offset) % mem_size << endl;

    // samples
    return (sum % mem_size + offset*offset) % mem_size;
}
bool HashTable::login(ChatMember ch_log, char ch_pas[], int pass_length) {
    int index = -1;
    bool OK = false;
    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(ch_log, i);
        if (pr) cout << "login: index = " << index << endl;
        if (array[index].status == enPairStatus::free) {
            // an empty cell was found, false
            if (pr) cout << "login: array[" << index << "].status = free" << endl;
            return false;
        }
        if (array[index].status == enPairStatus::deleted) continue;
        if (array[index].status == enPairStatus::engaged) {
            if (pr) cout << "login: array[" << index << "].status = engaged" << endl;
            // an occupied cell is found, we check
            OK = true;
            for (int j = 0; j < strlen(ch_log); j++) {
                if (pr) cout << "login: array[" << index << "].chat_log[" << j << "] = " << array[index].chat_log[j];
                if (pr) cout << "    ch_log[" << j << "] = " << ch_log[j] << endl;
                if (array[index].chat_log[j] != ch_log[j]) OK = false;
            }
            if (OK && array[index].pass_hf2_hash == hf2(ch_pas, pass_length)) return true;
        }
        if (i >= mem_size) return false; // we went through everything, we didn't find it
    }
    return false;
}
void HashTable::resize() {
    Pair* save_array = array; // remember old array
    int oldSize = mem_size;
    ChatMember ch_log;
    int index = -1;

    mem_size *= 2;  // we double the size  
    count = 0; // reset the number of elements
    array = new Pair[mem_size]; // allocating new memory
    for (int i = 0; i < mem_size; i++) {
        for (int j = 0; j < LOGINLENGTH; j++) array[i].chat_log[j] = ' ';
        array[i].status = enPairStatus::free;
        array[i].pass_hf2_hash = 0;
    }

    for (int i = 0; i < oldSize; i++) {
        // copy the old ones 
        if (save_array[i].status == enPairStatus::engaged) {
            memcpy(ch_log, save_array[i].chat_log, LOGINLENGTH);
            index = -1;
            for (int j = 0; j < mem_size; j++) {
                index = hash_func(ch_log, j);
                if (array[index].status == enPairStatus::free) break; // an empty cell is found, we occupy it                  
            }
            array[index] = Pair(ch_log, save_array[i].pass_hf2_hash);
            count++;
        }
    }
        // cleaning

    delete[] save_array;

}
