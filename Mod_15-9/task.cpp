#include "hash_table.h"
#include <iostream>
#include <string.h>

using namespace std;

// ������ ������ � �������� �������� �� ���-������� �� �����
/*
void HashTable::del(ChatMember fr_name) {
    ChatMember fr_null = "";
    int index = -1, i = 0;
    // ����� ����� �� ���� i �� 0 �� ������� �������
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
        //           // ������� ������ ������, �������� ��
        //           break;
        //       }
    }
    //   if (i >= mem_size) return; // ��� ���������, ��� �����
    return;
}
*/
/*
int HashTable::find(ChatMember fr_name) {
    // ������� ����� ��������, ��������������� ����� fr_name
    // ���� ������ ����� ���� � �������, �� ������� -1
    // ��� ���
    int index = -1, i = 0;
    // ����� ����� �� ���� i �� 0 �� ������� �������
    for (; i < mem_size; i++) {
        index = hash_func(fr_name, i);
        if (array[index].status == enPairStatus::free) return -1;
        if (array[index].status == enPairStatus::engaged) return array[index].chat_pass;
        //         
        //       if (array[index].fruit_name == enPairStatus::free) {
        //           // ������� ������ ������, �������� ��
        //           break;
        //       }
    }
    //   if (i >= mem_size) return; // ��� ���������, ��� �����

    return -1;
}
*/