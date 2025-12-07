#include "lagu.h"
#include <stdlib.h>

string formatDurasi(int detik){
    int menit = detik / 60;
    int sisa = detik % 60;
    string hasil = to_string(menit) + ":";
    if(sisa < 10) hasil += "0";
    hasil += to_string(sisa);
    return hasil;
}

void createList_lagu(List_lagu &L){
    L.first = NULL;
    L.last = NULL;
}

address_lagu alokasi_lagu(lagu x){
    address_lagu P = new elmList_lagu;
    P->info = x;
    P->next = NULL;
    P->prev = NULL;
    return P;
}

void insertLast_lagu(List_lagu &L, address_lagu P){
    if(L.first == NULL){
        L.first = P;
        L.last = P;
    }
    else{
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
}

address_lagu findElm_lagu(List_lagu L, string judul){
    address_lagu P = L.first;
    while(P != NULL){
        if(P->info.judul == judul){
            return P;
        }
        P = P->next;
    }
    return NULL;
}

address_lagu findLaguByID(List_lagu L, int id){
    address_lagu P = L.first;
    while(P != NULL){
        if(P->info.id_lagu == id){
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void deleteSearch_lagu(List_lagu &L, address_lagu &P){
    if(P == NULL) return;

    if(P == L.first && P == L.last){
        L.first = NULL;
        L.last = NULL;
    }
    else if(P == L.first){
        L.first = P->next;
        L.first->prev = NULL;
    }
    else if(P == L.last){
        L.last = P->prev;
        L.last->next = NULL;
    }
    else{
        P->prev->next = P->next;
        P->next->prev = P->prev;
    }
}

void showLagu(address_lagu P){
    cout << "ID: " << P->info.id_lagu << endl;
    cout << "Judul: " << P->info.judul << endl;
    cout << "Artis: " << P->info.artis << endl;
    cout << "Album: " << P->info.album << endl;
    cout << "Genre: " << P->info.genre << endl;
    cout << "Durasi: " << formatDurasi(P->info.durasi) << endl;
    cout << "Tahun: " << P->info.tahun << endl;
}

void printInfo_lagu(List_lagu L){
    address_lagu P = L.first;
    if(P == NULL){
        cout << "\nBelum ada lagu\n" << endl;
        return;
    }

    system("cls");
    cout << "==================================================================================" << endl;
    cout << "                            DAFTAR LAGU TERSEDIA" << endl;
    cout << "==================================================================================" << endl;
    cout << "ID  | Judul\t\t\t| Artis\t\t| Genre\t\t| Durasi | Tahun" << endl;
    cout << "==================================================================================" << endl;

    while(P != NULL){
        cout << P->info.id_lagu << "   | "
             << P->info.judul << "\t| "
             << P->info.artis << "\t| "
             << P->info.genre << "\t| "
             << formatDurasi(P->info.durasi) << " | "
             << P->info.tahun << endl;
        P = P->next;
    }
    cout << endl;
}

void editInfo_lagu(address_lagu &P){
    cout << "ID Lagu: ";
    cin >> P->info.id_lagu;
    cout << "Judul: ";
    cin.ignore();
    getline(cin, P->info.judul);
    cout << "Artis: ";
    getline(cin, P->info.artis);
    cout << "Album: ";
    getline(cin, P->info.album);
    cout << "Genre: ";
    getline(cin, P->info.genre);
    cout << "Durasi (detik): ";
    cin >> P->info.durasi;
    cout << "Tahun: ";
    cin >> P->info.tahun;
}

address_lagu input_lagu(){
    lagu x;
    static int counter = 101;
    x.id_lagu = counter++;
    cin.ignore();
    cout << "ID: " << x.id_lagu << " (Auto)" << endl;
    cout << "Judul: ";
    getline(cin, x.judul);
    cout << "Artis: ";
    getline(cin, x.artis);
    cout << "Album: ";
    getline(cin, x.album);
    cout << "Genre: ";
    getline(cin, x.genre);
    cout << "Durasi (detik): ";
    cin >> x.durasi;
    cout << "Tahun: ";
    cin >> x.tahun;
    return alokasi_lagu(x);
}

int hitungLagu(List_lagu L){
    int count = 0;
    address_lagu P = L.first;
    while(P != NULL){
        count++;
        P = P->next;
    }
    return count;
}

void data_lagu(List_lagu &L){
    lagu lg;
    address_lagu P;

    lg.id_lagu = 1;
    lg.judul = "Bohemian Rhapsody";
    lg.artis = "Queen";
    lg.album = "A Night at Opera";
    lg.genre = "Rock";
    lg.durasi = 354;
    lg.tahun = 1975;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 2;
    lg.judul = "Shape of You";
    lg.artis = "Ed Sheeran";
    lg.album = "Divide";
    lg.genre = "Pop";
    lg.durasi = 233;
    lg.tahun = 2017;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 3;
    lg.judul = "Blinding Lights";
    lg.artis = "The Weeknd";
    lg.album = "After Hours";
    lg.genre = "Synthwave";
    lg.durasi = 200;
    lg.tahun = 2019;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 4;
    lg.judul = "Starboy";
    lg.artis = "The Weeknd";
    lg.album = "Starboy";
    lg.genre = "R&B";
    lg.durasi = 230;
    lg.tahun = 2016;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 5;
    lg.judul = "Someone Like You";
    lg.artis = "Adele";
    lg.album = "21";
    lg.genre = "Pop";
    lg.durasi = 285;
    lg.tahun = 2011;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 6;
    lg.judul = "Bad Guy";
    lg.artis = "Billie Eilish";
    lg.album = "When We All Fall";
    lg.genre = "Pop";
    lg.durasi = 194;
    lg.tahun = 2019;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 7;
    lg.judul = "Levitating";
    lg.artis = "Dua Lipa";
    lg.album = "Future Nostalgia";
    lg.genre = "Pop";
    lg.durasi = 203;
    lg.tahun = 2020;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 8;
    lg.judul = "Stay";
    lg.artis = "Justin Bieber";
    lg.album = "Justice";
    lg.genre = "Pop";
    lg.durasi = 141;
    lg.tahun = 2021;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 9;
    lg.judul = "As It Was";
    lg.artis = "Harry Styles";
    lg.album = "Harry's House";
    lg.genre = "Pop";
    lg.durasi = 167;
    lg.tahun = 2022;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 10;
    lg.judul = "Anti-Hero";
    lg.artis = "Taylor Swift";
    lg.album = "Midnights";
    lg.genre = "Pop";
    lg.durasi = 200;
    lg.tahun = 2022;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 11;
    lg.judul = "Hotel California";
    lg.artis = "Eagles";
    lg.album = "Hotel California";
    lg.genre = "Rock";
    lg.durasi = 391;
    lg.tahun = 1976;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 12;
    lg.judul = "Wonderwall";
    lg.artis = "Oasis";
    lg.album = "Morning Glory";
    lg.genre = "Rock";
    lg.durasi = 258;
    lg.tahun = 1995;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 13;
    lg.judul = "Rolling in Deep";
    lg.artis = "Adele";
    lg.album = "21";
    lg.genre = "Soul";
    lg.durasi = 228;
    lg.tahun = 2010;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 14;
    lg.judul = "Lose Yourself";
    lg.artis = "Eminem";
    lg.album = "8 Mile";
    lg.genre = "Hip-Hop";
    lg.durasi = 326;
    lg.tahun = 2002;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 15;
    lg.judul = "Smells Like Teen";
    lg.artis = "Nirvana";
    lg.album = "Nevermind";
    lg.genre = "Grunge";
    lg.durasi = 301;
    lg.tahun = 1991;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 16;
    lg.judul = "Perfect";
    lg.artis = "Ed Sheeran";
    lg.album = "Divide";
    lg.genre = "Pop";
    lg.durasi = 263;
    lg.tahun = 2017;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 17;
    lg.judul = "Peaches";
    lg.artis = "Justin Bieber";
    lg.album = "Justice";
    lg.genre = "Pop";
    lg.durasi = 198;
    lg.tahun = 2021;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 18;
    lg.judul = "Watermelon Sugar";
    lg.artis = "Harry Styles";
    lg.album = "Fine Line";
    lg.genre = "Pop";
    lg.durasi = 174;
    lg.tahun = 2019;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 19;
    lg.judul = "Save Your Tears";
    lg.artis = "The Weeknd";
    lg.album = "After Hours";
    lg.genre = "Synthwave";
    lg.durasi = 215;
    lg.tahun = 2020;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);

    lg.id_lagu = 20;
    lg.judul = "Happier Than Ever";
    lg.artis = "Billie Eilish";
    lg.album = "Happier Than Ever";
    lg.genre = "Pop";
    lg.durasi = 298;
    lg.tahun = 2021;
    P = alokasi_lagu(lg);
    insertLast_lagu(L, P);
}
