#ifndef LAGU_H_INCLUDED
#define LAGU_H_INCLUDED

#include <iostream>

using namespace std;

struct lagu{
    int id_lagu;
    string judul;
    string artis;
    string album;
    string genre;
    int durasi;
    int tahun;
};

typedef struct elmList_lagu *address_lagu;

struct elmList_lagu{
    lagu info;
    address_lagu next;
    address_lagu prev;
};

struct List_lagu{
    address_lagu first;
    address_lagu last;
};

void createList_lagu(List_lagu &L);
address_lagu alokasi_lagu(lagu x);
void insertLast_lagu(List_lagu &L, address_lagu P);
address_lagu findElm_lagu(List_lagu L, string judul);
address_lagu findLaguByID(List_lagu L, int id);
void deleteSearch_lagu(List_lagu &L, address_lagu &P);
void printInfo_lagu(List_lagu L);
void showLagu(address_lagu P);
address_lagu input_lagu();
void editInfo_lagu(address_lagu &P);
void data_lagu(List_lagu &L);
string formatDurasi(int detik);
int hitungLagu(List_lagu L);

#endif // LAGU_H_INCLUDED
