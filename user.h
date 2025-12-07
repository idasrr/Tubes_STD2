#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "lagu.h"
#include <iostream>

using namespace std;

// ========== PLAYLIST ITEM (Level 3: Relasi Playlist-Lagu) ==========
typedef struct elmPlaylistItem *adrItem;

struct elmPlaylistItem{
    address_lagu lagu;
    int play_count;
    string tanggal_ditambah;
    adrItem next;
};

// ========== PLAYLIST (Level 2: Child of User) ==========
typedef struct elmPlaylist *adrPlaylist;

struct infoPlaylist{
    int id;
    string nama;
    string deskripsi;
    string tanggal_dibuat;
};

struct elmPlaylist{
    infoPlaylist info;
    adrPlaylist next;
    adrItem firstItem;
};

// ========== USER (Level 1: Parent) ==========
typedef struct elmUser *adrUser;

struct infoUser{
    string username;
    string nama_lengkap;
    string email;
    string negara;
    string tipe_akun;
    int umur;
};

struct elmUser{
    infoUser info;
    adrUser next;
    adrPlaylist firstPlaylist;
};

struct ListUser{
    adrUser first;
};

// ========== USER FUNCTIONS ==========
void createListUser(ListUser &L);
adrUser alokasiUser(infoUser x);
void insertLastUser(ListUser &L, adrUser P);
adrUser findUser(ListUser L, string username);
void deleteUser(ListUser &L, adrUser &P);
void printAllUsers(ListUser L);
void showUser(adrUser P);
adrUser inputUser();
void editUser(adrUser &P);
int hitungUser(ListUser L);
void dataUser(ListUser &L);

// ========== PLAYLIST FUNCTIONS ==========
adrPlaylist alokasiPlaylist(infoPlaylist x);
void insertLastPlaylist(adrUser U, adrPlaylist P);
adrPlaylist findPlaylist(adrUser U, string nama);
void deletePlaylist(adrUser &U, adrPlaylist &P);
void printAllPlaylists(adrUser U);
void showPlaylist(adrPlaylist P);
adrPlaylist inputPlaylist(adrUser U);
void editPlaylist(adrPlaylist &P);
int hitungPlaylist(adrUser U);
int getTotalLaguInPlaylist(adrPlaylist P);
int getTotalDurasiPlaylist(adrPlaylist P);

// ========== PLAYLIST ITEM FUNCTIONS ==========
adrItem alokasiItem(address_lagu L);
void insertLastItem(adrPlaylist PL, adrItem P);
adrItem findItem(adrPlaylist PL, address_lagu L);
void deleteItem(adrPlaylist &PL, adrItem &P);
void printIsiPlaylist(adrPlaylist PL);
void playLagu(adrPlaylist PL, address_lagu L);
adrItem getCurrentItem(adrPlaylist PL, address_lagu L); // Helper untuk navigasi
int getTotalPlayCount(adrPlaylist PL);
address_lagu getLaguTerpopulerDiPlaylist(adrPlaylist PL);

// ========== HELPER FUNCTIONS ==========
void tambahLaguKePlaylist(adrUser U, adrPlaylist PL, address_lagu L);
void hapusLaguDariPlaylist(adrPlaylist PL, address_lagu L);

#endif // USER_H_INCLUDED
