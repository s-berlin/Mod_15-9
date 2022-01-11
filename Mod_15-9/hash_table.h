#pragma once
#include <string.h>
#include <iostream>

using namespace std;

#define LOGINLENGTH 20

typedef char ChatMember[LOGINLENGTH]; // type - login

class HashTable { // hash table
public:

    HashTable();
    ~HashTable();
 //   void add(ChatMember ch_log, ChatMember ch_pas);
    void reg(ChatMember ch_log, char ch_pas[], int pass_length);
    bool login(ChatMember ch_log, char ch_pas[], int pass_length);
    void show();
    void resize();

    void del(ChatMember ch_log);
    bool find(ChatMember ch_log);

    friend void test(HashTable& ht);

private:
    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair { // pair key-value

        Pair() :
            chat_log(""),
            pass_hf2_hash(0),
            status(free)
        {}
        Pair(ChatMember ch_log, double sh1) :
            status(enPairStatus::engaged) {
            memcpy(chat_log, ch_log, LOGINLENGTH);
            pass_hf2_hash = sh1;
        }
        Pair& operator = (const Pair& other) {
            memcpy(chat_log, other.chat_log, LOGINLENGTH);
            pass_hf2_hash = other.pass_hf2_hash;
            status = other.status;

            return *this;
        }

        bool operator == (const Pair& other) {
            return  status == other.status &&
                (status != enPairStatus::engaged || (pass_hf2_hash == other.pass_hf2_hash && !strcmp(chat_log, other.chat_log)));
        }

        ChatMember chat_log;
        double pass_hf2_hash;
        enPairStatus status;
    };

    int hash_func(ChatMember ch_log, int offset);

    Pair* array;
    int mem_size;
    int count;
}; 
