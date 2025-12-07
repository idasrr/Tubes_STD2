#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "user.h"
#include "lagu.h"

// ========== AUTHENTICATION ==========
struct CurrentUser {
    string username;
    string role;
    bool isLoggedIn;
};

void tampilkanHeader();
bool login(CurrentUser &current, ListUser LU);
void logout(CurrentUser &current);

// ========== MAIN MENU ==========
void menuAdmin(ListUser &LU, List_lagu &LL);
void menuUser(ListUser &LU, List_lagu &LL, string username);
string toLowerString(string str);
bool containsString(string text, string keyword);

// ========== USER OPERATIONS ==========
void lihatSemuaPlaylist(adrUser U);
void buatPlaylistBaru(adrUser U);
void hapusPlaylistUser(adrUser U);
void editPlaylistUser(adrUser U);
void tambahLaguKePlaylistMenu(adrUser U, List_lagu LL);
void hapusLaguDariPlaylistMenu(adrUser U);
void playLaguMenu(adrUser U);
void lihatIsiPlaylistMenu(adrUser U);

// ========== MUSIC PLAYER (PREV/NEXT) ==========
void musicPlayer(adrPlaylist PL);
void sortPlaylistByID(adrPlaylist PL);

// ========== STATISTICS ==========
void statistikGlobal(ListUser LU, List_lagu LL);
void laguTerpopulerGlobal(ListUser LU);
void userTeraktif(ListUser LU);
void laguTerpopulerUser(adrUser U);
void playlistTerpopulerUser(adrUser U);

// ========== DATA DUMMY ==========
void dataDummy(ListUser &LU, List_lagu &LL);

#endif // MENU_H_INCLUDED
