#include "hash_table.h"
#include <iostream>
#include <string.h>

using namespace std;

// методы поиска и удалени€ элемента из хеш-таблицы по ключу
/*
void HashTable::del(ChatMember fr_name) {
    ChatMember fr_null = "";
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(fr_name, i);
        if (array[index].status == enPairStatus::free) return;
        if (array[index].status == enPairStatus::engaged) {
            array[index].chat_log;
            array[index].status = enPairStatus::deleted;
            array[index].chat_pass = "";
            return;
        }
        //       if (array[index].fruit_name == enPairStatus::free) {
        //           // найдена пуста€ €чейка, занимаем ее
        //           break;
        //       }
    }
    //   if (i >= mem_size) return; // все перебрали, нет места
    return;
}
*/
/*
int HashTable::find(ChatMember fr_name) {
    // вернуть нужно значение, соответствующее ключу fr_name
    // если такого ключа нету в таблице, то верните -1
    // ¬аш код
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(fr_name, i);
        if (array[index].status == enPairStatus::free) return -1;
        if (array[index].status == enPairStatus::engaged) return array[index].chat_pass;
        //         
        //       if (array[index].fruit_name == enPairStatus::free) {
        //           // найдена пуста€ €чейка, занимаем ее
        //           break;
        //       }
    }
    //   if (i >= mem_size) return; // все перебрали, нет места

    return -1;
}
*/