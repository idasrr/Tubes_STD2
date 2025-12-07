#include "user.h"
#include <stdlib.h>

// ========== USER FUNCTIONS ==========
void createListUser(ListUser &L){
    L.first = NULL;
}

adrUser alokasiUser(infoUser x){
    adrUser P = new elmUser;
    P->info = x;
    P->next = NULL;
    P->firstPlaylist = NULL;
    return P;
}

void insertLastUser(ListUser &L, adrUser P){
    if(L.first == NULL){
        L.first = P;
    }else{
        adrUser Q = L.first;
        while(Q->next != NULL){
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrUser findUser(ListUser L, string username){
    adrUser P = L.first;
    while(P != NULL){
        if(P->info.username == username){
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void deleteUser(ListUser &L, adrUser &P){
    if(P == NULL) return;

    adrPlaylist PL = P->firstPlaylist;
    while(PL != NULL){
        adrPlaylist temp = PL;
        PL = PL->next;

        adrItem IT = temp->firstItem;
        while(IT != NULL){
            adrItem tempIT = IT;
            IT = IT->next;
            delete tempIT;
        }
        delete temp;
    }

    if(P == L.first){
        L.first = P->next;
    }else{
        adrUser Q = L.first;
        while(Q->next != P){
            Q = Q->next;
        }
        Q->next = P->next;
    }
    delete P;
}

void printAllUsers(ListUser L){
    adrUser P = L.first;
    if(P == NULL){
        cout << "\nBelum ada user\n" << endl;
        return;
    }

    cout << "============================================================================" << endl;
    cout << "                            DAFTAR USER" << endl;
    cout << "============================================================================" << endl;
    cout << "Username\t| Nama\t\t| Email\t\t\t| Playlist" << endl;
    cout << "============================================================================" << endl;

    while(P != NULL){
        cout << P->info.username << "\t| "
             << P->info.nama_lengkap << "\t| "
             << P->info.email << "\t| "
             << hitungPlaylist(P) << endl;
        P = P->next;
    }
    cout << endl;
}

void showUser(adrUser P){
    cout << "Username: " << P->info.username << endl;
    cout << "Nama: " << P->info.nama_lengkap << endl;
    cout << "Email: " << P->info.email << endl;
    cout << "Negara: " << P->info.negara << endl;
    cout << "Umur: " << P->info.umur << endl;
    cout << "Jumlah Playlist: " << hitungPlaylist(P) << endl;
}

adrUser inputUser(){
    infoUser x;
    cin.ignore();
    cout << "Username: ";
    getline(cin, x.username);
    cout << "Nama Lengkap: ";
    getline(cin, x.nama_lengkap);
    cout << "Email: ";
    getline(cin, x.email);
    cout << "Negara: ";
    getline(cin, x.negara);
    cout << "Umur: ";
    cin >> x.umur;
    return alokasiUser(x);
}

void editUser(adrUser &P){
    cout << "Username: " << P->info.username << " (tidak bisa diubah)" << endl;
    cout << "Nama Lengkap: ";
    cin.ignore();
    getline(cin, P->info.nama_lengkap);
    cout << "Email: ";
    getline(cin, P->info.email);
    cout << "Negara: ";
    getline(cin, P->info.negara);
    cout << "Umur: ";
    cin >> P->info.umur;
}

int hitungUser(ListUser L){
    int count = 0;
    adrUser P = L.first;
    while(P != NULL){
        count++;
        P = P->next;
    }
    return count;
}

void dataUser(ListUser &L){
    infoUser u;
    adrUser P;

    u.username = "john_doe";
    u.nama_lengkap = "John Doe";
    u.email = "john@email.com";
    u.negara = "USA";
    u.umur = 25;
    P = alokasiUser(u);
    insertLastUser(L, P);

    u.username = "jane_smith";
    u.nama_lengkap = "Jane Smith";
    u.email = "jane@email.com";
    u.negara = "UK";
    u.umur = 28;
    P = alokasiUser(u);
    insertLastUser(L, P);

    u.username = "mike_wilson";
    u.nama_lengkap = "Mike Wilson";
    u.email = "mike@email.com";
    u.negara = "Canada";
    u.umur = 22;
    P = alokasiUser(u);
    insertLastUser(L, P);

    u.username = "sarah_lee";
    u.nama_lengkap = "Sarah Lee";
    u.email = "sarah@email.com";
    u.negara = "Australia";
    u.umur = 30;
    P = alokasiUser(u);
    insertLastUser(L, P);

    u.username = "david_brown";
    u.nama_lengkap = "David Brown";
    u.email = "david@email.com";
    u.negara = "Indonesia";
    u.umur = 24;
    P = alokasiUser(u);
    insertLastUser(L, P);
}

// ========== PLAYLIST FUNCTIONS ==========
adrPlaylist alokasiPlaylist(infoPlaylist x){
    adrPlaylist P = new elmPlaylist;
    P->info = x;
    P->next = NULL;
    P->firstItem = NULL;
    return P;
}

void insertLastPlaylist(adrUser U, adrPlaylist P){
    if(U->firstPlaylist == NULL){
        U->firstPlaylist = P;
    }else{
        adrPlaylist Q = U->firstPlaylist;
        while(Q->next != NULL){
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrPlaylist findPlaylist(adrUser U, string nama){
    adrPlaylist P = U->firstPlaylist;
    while(P != NULL){
        if(P->info.nama == nama){
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void deletePlaylist(adrUser &U, adrPlaylist &P){
    if(P == NULL) return;

    adrItem IT = P->firstItem;
    while(IT != NULL){
        adrItem temp = IT;
        IT = IT->next;
        delete temp;
    }

    if(P == U->firstPlaylist){
        U->firstPlaylist = P->next;
    }else{
        adrPlaylist Q = U->firstPlaylist;
        while(Q->next != P){
            Q = Q->next;
        }
        Q->next = P->next;
    }
    delete P;
}

void printAllPlaylists(adrUser U){
    adrPlaylist P = U->firstPlaylist;
    if(P == NULL){
        cout << "\nBelum ada playlist\n" << endl;
        return;
    }

    cout << "\n========== Playlist: " << U->info.username << " ==========" << endl;
    int no = 1;
    while(P != NULL){
        cout << no++ << ". " << P->info.nama
             << " (" << getTotalLaguInPlaylist(P) << " lagu, "
             << getTotalPlayCount(P) << "x play)" << endl;
        cout << "   " << P->info.deskripsi << endl;
        P = P->next;
    }
    cout << endl;
}

void showPlaylist(adrPlaylist P){
    cout << "Nama: " << P->info.nama << endl;
    cout << "Deskripsi: " << P->info.deskripsi << endl;
    cout << "Dibuat: " << P->info.tanggal_dibuat << endl;
    cout << "Jumlah Lagu: " << getTotalLaguInPlaylist(P) << endl;
    cout << "Total Play: " << getTotalPlayCount(P) << "x" << endl;
    cout << "Durasi: " << formatDurasi(getTotalDurasiPlaylist(P)) << endl;
}

adrPlaylist inputPlaylist(adrUser U){
    infoPlaylist x;
    static int counter = 1;
    x.id = counter++;
    cin.ignore();
    cout << "Nama Playlist: ";
    getline(cin, x.nama);
    cout << "Deskripsi: ";
    getline(cin, x.deskripsi);
    cout << "Tanggal (DD/MM/YYYY): ";
    getline(cin, x.tanggal_dibuat);
    return alokasiPlaylist(x);
}

void editPlaylist(adrPlaylist &P){
    cout << "Nama Playlist: ";
    cin.ignore();
    getline(cin, P->info.nama);
    cout << "Deskripsi: ";
    getline(cin, P->info.deskripsi);
}

int hitungPlaylist(adrUser U){
    int count = 0;
    adrPlaylist P = U->firstPlaylist;
    while(P != NULL){
        count++;
        P = P->next;
    }
    return count;
}

int getTotalLaguInPlaylist(adrPlaylist P){
    int count = 0;
    adrItem IT = P->firstItem;
    while(IT != NULL){
        count++;
        IT = IT->next;
    }
    return count;
}

int getTotalDurasiPlaylist(adrPlaylist P){
    int total = 0;
    adrItem IT = P->firstItem;
    while(IT != NULL){
        total += IT->lagu->info.durasi;
        IT = IT->next;
    }
    return total;
}

// ========== PLAYLIST ITEM FUNCTIONS ==========
adrItem alokasiItem(address_lagu L){
    adrItem P = new elmPlaylistItem;
    P->lagu = L;
    P->play_count = 0;
    P->tanggal_ditambah = "29/11/2024";
    P->next = NULL;
    return P;
}

void insertLastItem(adrPlaylist PL, adrItem P){
    if(PL->firstItem == NULL){
        PL->firstItem = P;
    }else{
        adrItem Q = PL->firstItem;
        while(Q->next != NULL){
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrItem findItem(adrPlaylist PL, address_lagu L){
    adrItem P = PL->firstItem;
    while(P != NULL){
        if(P->lagu == L){
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void deleteItem(adrPlaylist &PL, adrItem &P){
    if(P == NULL) return;

    if(P == PL->firstItem){
        PL->firstItem = P->next;
    }else{
        adrItem Q = PL->firstItem;
        while(Q->next != P){
            Q = Q->next;
        }
        Q->next = P->next;
    }
    delete P;
}

void printIsiPlaylist(adrPlaylist PL){
    adrItem P = PL->firstItem;
    if(P == NULL){
        cout << "\nPlaylist kosong\n" << endl;
        return;
    }

    cout << "\n========== " << PL->info.nama << " ==========" << endl;
    cout << PL->info.deskripsi << endl;
    cout << "Total: " << getTotalLaguInPlaylist(PL) << " lagu | "
         << formatDurasi(getTotalDurasiPlaylist(PL)) << " | "
         << getTotalPlayCount(PL) << "x play" << endl;
    cout << "\n";

    int no = 1;
    while(P != NULL){
        cout << no++ << ". " << P->lagu->info.judul
             << " - " << P->lagu->info.artis
             << " [" << P->lagu->info.genre << "] "
             << "(" << formatDurasi(P->lagu->info.durasi) << ")"
             << " | " << P->play_count << "x play" << endl;
        P = P->next;
    }
    cout << endl;
}

void playLagu(adrPlaylist PL, address_lagu L){
    adrItem P = findItem(PL, L);
    if(P != NULL){
        P->play_count++;
        cout << "\n>>> NOW PLAYING: " << L->info.judul
             << " - " << L->info.artis << " <<<" << endl;
        cout << "Play count: " << P->play_count << "x" << endl;
    }
}

adrItem getCurrentItem(adrPlaylist PL, address_lagu L){
    return findItem(PL, L);
}

int getTotalPlayCount(adrPlaylist PL){
    int total = 0;
    adrItem P = PL->firstItem;
    while(P != NULL){
        total += P->play_count;
        P = P->next;
    }
    return total;
}

address_lagu getLaguTerpopulerDiPlaylist(adrPlaylist PL){
    if(PL->firstItem == NULL) return NULL;

    adrItem P = PL->firstItem;
    adrItem max = P;

    while(P != NULL){
        if(P->play_count > max->play_count){
            max = P;
        }
        P = P->next;
    }
    return max->lagu;
}

// ========== HELPER FUNCTIONS ==========
void tambahLaguKePlaylist(adrUser U, adrPlaylist PL, address_lagu L){
    adrItem cek = findItem(PL, L);
    if(cek != NULL){
        cout << "\nLagu sudah ada di playlist!" << endl;
        return;
    }

    adrItem P = alokasiItem(L);
    insertLastItem(PL, P);
    cout << "\nLagu berhasil ditambahkan ke playlist!" << endl;
}

void hapusLaguDariPlaylist(adrPlaylist PL, address_lagu L){
    adrItem P = findItem(PL, L);
    if(P == NULL){
        cout << "\nLagu tidak ada di playlist!" << endl;
        return;
    }

    deleteItem(PL, P);
    cout << "\nLagu berhasil dihapus dari playlist!" << endl;
}
