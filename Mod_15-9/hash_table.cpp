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
    if (i >= mem_size) return; // everything has been sorted out, there is no place

    // we put a pair in a free cell
    hps = hf2(ch_pas, pass_length);
    array[index] = Pair(ch_log, hps);
    count++;
    if (pr) cout << "reg: count = " << count << endl;
}

bool HashTable::find(ChatMember ch_log) {
 
    for (int i = 0; i < mem_size; i++) {
        bool OK = false;
        int index = hash_func(ch_log, i);
        if (pr) cout << "find: index = " << index << endl;
        if (array[index].status == enPairStatus::free) {
            // an empty cell was found, false
            if (pr) cout << "find: array[" << index << "].status = free" << endl;
            return false;
        }       
        if (array[index].status == enPairStatus::engaged) {
            if (pr) cout << "find: array[" << index << "].status = engaged" << endl;
            // an occupied cell is found, we check
            OK = true;
            for (int j = 0; j < strlen(ch_log); j++) {
                if (pr) cout << "find: array[" << index << "].chat_log[" << j <<"] = " << array[index].chat_log[j];
                if (pr) cout << "    ch_log[" << j << "] = " << ch_log[j] << endl;
                if (array[index].chat_log[j] != ch_log[j]) OK = false;
            }
        }
        if (array[index].status == enPairStatus::deleted) continue;
        if (i >= mem_size) return false; // we went through everything, we didn't find it
        return OK;
    }
}

void HashTable::show() {
    setlocale(LC_ALL, "");

    for (int i = 0; i < mem_size; i++) {
        if (array[i].status != 0) {
            cout << "show:   array[" << i << "].chat_log = " << setw(20) << array[i].chat_log << "      ";
            cout << setw(10) << array[i].pass_hf2_hash;
            cout << "  status = " << array[i].status << endl;
        }
    }
    return;
}

void HashTable::del(ChatMember ch_log) {
    int index;
    if (find(ch_log)) {
        for (int i = 0; i < mem_size; i++) {
            index = hash_func(ch_log, i);
            break;
        }
        array[index].status = enPairStatus::deleted;
        array[index].pass_hf2_hash = 0;
    }

    return;
}

int HashTable::hash_func(ChatMember ch_log, int offset) {
    // calculating the index
    int login_length = strlen(ch_log);
    int sum = 0;
    for (int i = 0; i < login_length; i++) {
        sum += ch_log[i];
        if (pr) cout << " hash_func: ch_log[" << i << "] = " << ch_log[i] << "     sum = " << sum << endl;
    }
    if (pr) cout << " hash_func: sum = " << sum << "   return " << (sum % mem_size + offset*offset) % mem_size << endl;

    // samples
    return (sum % mem_size + offset*offset) % mem_size;
}
bool HashTable::login(ChatMember ch_log, char ch_pas[], int pass_length) {
    int index = 0;
    if (ch_log && pass_length && find(ch_log))
        {
        for (int i = 0; i < mem_size; i++) {
            index = hash_func(ch_log, i); 
            break;
        }
        if (pr) cout << "Autho:    log=" << ch_log << "    pass=" << ch_pas << "     index = " << index << endl;
        if (array[index].pass_hf2_hash == hf2(ch_pas, pass_length))
            {
                return true;
            }
            else {
                return false;
            }
        }
    
    else return false;
}
