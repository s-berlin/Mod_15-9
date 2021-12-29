#pragma once

#include <string.h>

#define LOGINLENGTH 10

typedef char ChatMember[LOGINLENGTH]; // type - login

class HashTable { // hash table
public:

    HashTable();
    ~HashTable();
    void add(ChatMember ch_log, char ch_pas[]);
    void show();

    void del(ChatMember ch_log);
    int find(ChatMember ch_log);

    friend void test(HashTable& ht);

    void dummy(char* ch_log);

private:
    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair { // pair key-value

        Pair() :
            chat_log(""),
            chat_pass(0),
            status(free)
        {}
        Pair(ChatMember ch_log, char* ch_pas) :
            chat_pass(ch_pas),
            status(enPairStatus::engaged) {
            memcpy(chat_log, ch_log, LOGINLENGTH);
        }
        Pair& operator = (const Pair& other) {
            chat_pass = other.chat_pass;
            memcpy(chat_log, other.chat_log, LOGINLENGTH);
            status = other.status;

            return *this;
        }

        bool operator == (const Pair& other) {
            return  status == other.status &&
                (status != enPairStatus::engaged || (chat_pass == other.chat_pass && !strcmp(chat_log, other.chat_log)));
        }

        ChatMember chat_log;
        char* chat_pass;

        enPairStatus status;
    };

    int hash_func(ChatMember ch_log, int offset);

    Pair* array;
    int mem_size;
    int count;
}; 
