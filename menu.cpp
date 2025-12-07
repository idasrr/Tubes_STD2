#include "menu.h"
#include <stdlib.h>

const string ADMIN_USER = "admin";
const string ADMIN_PASS = "admin123";

// ========== HELPER FUNCTIONS ==========
// Fungsi untuk mengubah string ke lowercase (ganti std::transform)
string toLowerString(string str){
    string result = str;
    for(int i = 0; i < result.length(); i++){
        if(result[i] >= 'A' && result[i] <= 'Z'){
            result[i] = result[i] + 32; // Convert uppercase to lowercase
        }
    }
    return result;
}

// Fungsi untuk mengecek apakah keyword ada di dalam text (ganti find)
bool containsString(string text, string keyword){
    if(keyword.length() > text.length()){
        return false;
    }

    for(int i = 0; i <= text.length() - keyword.length(); i++){
        bool match = true;
        for(int j = 0; j < keyword.length(); j++){
            if(text[i + j] != keyword[j]){
                match = false;
                break;
            }
        }
        if(match){
            return true;
        }
    }
    return false;
}

// ========== AUTHENTICATION ==========
void tampilkanHeader(){
    cout << "==========================================================" << endl;
    cout << "                           COTIFY                         " << endl;
    cout << "==========================================================" << endl;
}

bool login(CurrentUser &current, ListUser LU){
    string username, password;
    int pilihan;

    system("cls");
    tampilkanHeader();

    cout << "\n[1] Login sebagai Admin" << endl;
    cout << "[2] Login sebagai User" << endl;
    cout << "[3] Daftar Akun User Baru" << endl;
    cout << "[0] Keluar" << endl;
    cout << "\nPilihan: ";
    cin >> pilihan;

    if(pilihan == 0) return false;

    system("cls");
    tampilkanHeader();

    if(pilihan == 1){
        cout << "\n=== LOGIN ADMIN ===" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if(username == ADMIN_USER && password == ADMIN_PASS){
            current.username = username;
            current.role = "admin";
            current.isLoggedIn = true;
            cout << "\nLogin berhasil! Selamat datang Admin!\n";
            system("pause");
            return true;
        }
        cout << "\nUsername/password salah!\n";
        system("pause");
        return false;
    }
    else if(pilihan == 2){
        cout << "\n=== LOGIN USER ===" << endl;
        cout << "\n--- Daftar Username Tersedia: ---" << endl;
        printAllUsers(LU);
        cout << "Masukkan Username: ";
        cin >> username;

        adrUser U = findUser(LU, username);
        if(U != NULL){
            current.username = username;
            current.role = "user";
            current.isLoggedIn = true;
            cout << "\nLogin berhasil! Selamat datang " << U->info.nama_lengkap << "!\n";
            system("pause");
            return true;
        }
        cout << "\nUsername tidak ditemukan!\n";
        system("pause");
        return false;
    }
    else if(pilihan == 3){
        cout << "\n=== DAFTAR AKUN BARU ===" << endl;
        adrUser U = inputUser();
        insertLastUser(LU, U);
        cout << "\nAkun berhasil dibuat! Silakan login dengan username: " << U->info.username << "\n";
        system("pause");
        login(current,LU);
        return false;
    }

    cout << "\nPilihan tidak valid!\n";
    system("pause");
    return false;
}

void logout(CurrentUser &current){
    current.username = "";
    current.role = "";
    current.isLoggedIn = false;
}

// ========== MUSIC PLAYER ==========
void musicPlayer(adrPlaylist PL){
    if(PL->firstItem == NULL){
        cout << "\nPlaylist kosong!\n";
        system("pause");
        return;
    }

    adrItem current = PL->firstItem;
    char pilihan;
    bool isPaused = false;

    while(pilihan != 'Q' && pilihan != 'q'){
        system("cls");
        cout << "==========================================================" << endl;
        cout << "                    MUSIC PLAYER"                           << endl;
        cout << "==========================================================" << endl;
        cout << "Playlist: " << PL->info.nama << endl;
        cout << "==========================================================" << endl;

        // Tampilkan lagu yang sedang diputar
        cout << "\n>>> NOW PLAYING <<<" << endl;
        if(isPaused){
            cout << ">>> [PAUSED] <<<" << endl;
        }
        cout << "Judul  : " << current->lagu->info.judul << endl;
        cout << "Artis  : " << current->lagu->info.artis << endl;
        cout << "Album  : " << current->lagu->info.album << endl;
        cout << "Genre  : " << current->lagu->info.genre << endl;
        cout << "Durasi : " << formatDurasi(current->lagu->info.durasi) << endl;
        cout << "Play Count: " << current->play_count << "x" << endl;
        cout << "==========================================================" << endl;

        // Kontrol
        cout << "\n[P] PREV  [N] NEXT  [R] REPLAY  [S] PAUSE/RESUME  [Q] QUIT" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        if(pilihan == 'P' || pilihan == 'p'){
            // PREV - cari lagu sebelumnya
            if(current == PL->firstItem){
                cout << "\nSudah di lagu pertama!" << endl;
                system("pause");
            }else{
                adrItem temp = PL->firstItem;
                while(temp->next != current){
                    temp = temp->next;
                }
                current = temp;
                current->play_count++;
                isPaused = false;
            }
        }
        else if(pilihan == 'N' || pilihan == 'n'){
            // NEXT - lagu berikutnya
            if(current->next == NULL){
                cout << "\nSudah di lagu terakhir!" << endl;
                system("pause");
            }else{
                current = current->next;
                current->play_count++;
                isPaused = false;
            }
        }
        else if(pilihan == 'R' || pilihan == 'r'){
            // REPLAY - putar ulang
            current->play_count++;
            isPaused = false;
            cout << "\nReplay... Play count: " << current->play_count << "x" << endl;
            system("pause");
        }
        else if(pilihan == 'S' || pilihan == 's'){
            // PAUSE/RESUME
            isPaused = !isPaused;
            if(isPaused){
                cout << "\nLagu dijeda..." << endl;
            } else {
                cout << "\nMelanjutkan pemutaran..." << endl;
            }
            system("pause");
        }
        else if(pilihan == 'Q' || pilihan == 'q'){
            // QUIT
            cout << "\nKeluar dari music player..." << endl;
            system("pause");
        }
        else{
            cout << "\nPilihan tidak valid!" << endl;
            system("pause");
        }
    };
}

// ========== SORTING LAGU ==========
void sortPlaylistByID(adrPlaylist PL){
    if(PL->firstItem == NULL || PL->firstItem->next == NULL){
        return;
    }

    bool swapped;
    do {
        swapped = false;
        adrItem current = PL->firstItem;
        adrItem prev = NULL;

        while(current->next != NULL){
            if(current->lagu->info.id_lagu > current->next->lagu->info.id_lagu){
                adrItem temp = current->next;
                current->next = temp->next;
                temp->next = current;

                if(prev == NULL){
                    PL->firstItem = temp;
                } else {
                    prev->next = temp;
                }

                prev = temp;
                swapped = true;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while(swapped);
}

void sortPlaylistByAbjad(adrPlaylist PL){
    if(PL->firstItem == NULL || PL->firstItem->next == NULL){
        return;
    }

    bool swapped;
    do {
        swapped = false;
        adrItem current = PL->firstItem;
        adrItem prev = NULL;

        while(current->next != NULL){
            string judul1 = toLowerString(current->lagu->info.judul);
            string judul2 = toLowerString(current->next->lagu->info.judul);

            if(judul1 > judul2){
                adrItem temp = current->next;
                current->next = temp->next;
                temp->next = current;

                if(prev == NULL){
                    PL->firstItem = temp;
                } else {
                    prev->next = temp;
                }

                prev = temp;
                swapped = true;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while(swapped);
}

void sortingPlaylistMenu(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    string namaPlaylist;
    cout << "Nama playlist yang akan diurutkan: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL == NULL){
        cout << "\nPlaylist tidak ditemukan!\n";
        system("pause");
        return;
    }

    if(PL->firstItem == NULL){
        cout << "\nPlaylist kosong!\n";
        system("pause");
        return;
    }

    int pilihan;
    cout << "\n=== URUTKAN LAGU ===" << endl;
    cout << "1. Urutkan berdasarkan ID" << endl;
    cout << "2. Urutkan berdasarkan Abjad (Judul)" << endl;
    cout << "Pilihan: ";
    cin >> pilihan;

    if(pilihan == 1){
        sortPlaylistByID(PL);
        cout << "\nPlaylist berhasil diurutkan berdasarkan ID!\n";
    } else if(pilihan == 2){
        sortPlaylistByAbjad(PL);
        cout << "\nPlaylist berhasil diurutkan berdasarkan Abjad!\n";
    } else {
        cout << "\nPilihan tidak valid!\n";
    }

    system("pause");
}

// ========== SEARCHING LAGU ==========
void searchLaguByJudul(List_lagu LL){
    system("cls");
    cout << "=== CARI LAGU BERDASARKAN JUDUL ===" << endl;
    string keyword;
    cout << "Masukkan kata kunci judul: ";
    cin.ignore();
    getline(cin, keyword);

    keyword = toLowerString(keyword);

    cout << "\n=== HASIL PENCARIAN ===" << endl;
    address_lagu L = LL.first;
    int count = 0;

    while(L != NULL){
        string judul = toLowerString(L->info.judul);

        if(containsString(judul, keyword)){
            cout << "\n[" << L->info.id_lagu << "] " << L->info.judul << endl;
            cout << "    Artis  : " << L->info.artis << endl;
            cout << "    Album  : " << L->info.album << endl;
            cout << "    Genre  : " << L->info.genre << endl;
            cout << "    Durasi : " << formatDurasi(L->info.durasi) << endl;
            count++;
        }
        L = L->next;
    }

    if(count == 0){
        cout << "Tidak ada lagu yang ditemukan dengan kata kunci \"" << keyword << "\"" << endl;
    } else {
        cout << "\nTotal: " << count << " lagu ditemukan" << endl;
    }
}

void searchLaguByArtis(List_lagu LL){
    system("cls");
    cout << "=== CARI LAGU BERDASARKAN ARTIS ===" << endl;
    string keyword;
    cout << "Masukkan nama artis: ";
    cin.ignore();
    getline(cin, keyword);

    keyword = toLowerString(keyword);

    cout << "\n=== HASIL PENCARIAN ===" << endl;
    address_lagu L = LL.first;
    int count = 0;

    while(L != NULL){
        string artis = toLowerString(L->info.artis);

        if(containsString(artis, keyword)){
            cout << "\n[" << L->info.id_lagu << "] " << L->info.judul << endl;
            cout << "    Artis  : " << L->info.artis << endl;
            cout << "    Album  : " << L->info.album << endl;
            cout << "    Genre  : " << L->info.genre << endl;
            cout << "    Durasi : " << formatDurasi(L->info.durasi) << endl;
            count++;
        }
        L = L->next;
    }

    if(count == 0){
        cout << "Tidak ada lagu dari artis \"" << keyword << "\"" << endl;
    } else {
        cout << "\nTotal: " << count << " lagu ditemukan" << endl;
    }
}

void searchLaguByGenre(List_lagu LL){
    system("cls");
    cout << "=== CARI LAGU BERDASARKAN GENRE ===" << endl;
    string keyword;
    cout << "Masukkan genre: ";
    cin.ignore();
    getline(cin, keyword);

    keyword = toLowerString(keyword);

    cout << "\n=== HASIL PENCARIAN ===" << endl;
    address_lagu L = LL.first;
    int count = 0;

    while(L != NULL){
        string genre = toLowerString(L->info.genre);

        if(containsString(genre, keyword)){
            cout << "\n[" << L->info.id_lagu << "] " << L->info.judul << endl;
            cout << "    Artis  : " << L->info.artis << endl;
            cout << "    Album  : " << L->info.album << endl;
            cout << "    Genre  : " << L->info.genre << endl;
            cout << "    Durasi : " << formatDurasi(L->info.durasi) << endl;
            count++;
        }
        L = L->next;
    }

    if(count == 0){
        cout << "Tidak ada lagu dengan genre \"" << keyword << "\"" << endl;
    } else {
        cout << "\nTotal: " << count << " lagu ditemukan" << endl;
    }
}

void searchLaguByAlbum(List_lagu LL){
    system("cls");
    cout << "=== CARI LAGU BERDASARKAN ALBUM ===" << endl;
    string keyword;
    cout << "Masukkan nama album: ";
    cin.ignore();
    getline(cin, keyword);

    keyword = toLowerString(keyword);

    cout << "\n=== HASIL PENCARIAN ===" << endl;
    address_lagu L = LL.first;
    int count = 0;

    while(L != NULL){
        string album = toLowerString(L->info.album);

        if(containsString(album, keyword)){
            cout << "\n[" << L->info.id_lagu << "] " << L->info.judul << endl;
            cout << "    Artis  : " << L->info.artis << endl;
            cout << "    Album  : " << L->info.album << endl;
            cout << "    Genre  : " << L->info.genre << endl;
            cout << "    Durasi : " << formatDurasi(L->info.durasi) << endl;
            count++;
        }
        L = L->next;
    }

    if(count == 0){
        cout << "Tidak ada lagu dari album \"" << keyword << "\"" << endl;
    } else {
        cout << "\nTotal: " << count << " lagu ditemukan" << endl;
    }
}

void searchingMenu(List_lagu LL){
    int pilihan;

    do {
        system("cls");
        cout << "==========================================================" << endl;
        cout << "                    SEARCH LAGU                           " << endl;
        cout << "==========================================================" << endl;
        cout << "\n1. Cari berdasarkan Judul" << endl;
        cout << "2. Cari berdasarkan Artis" << endl;
        cout << "3. Cari berdasarkan Genre" << endl;
        cout << "4. Cari berdasarkan Album" << endl;
        cout << "0. Kembali" << endl;
        cout << "\nPilihan: ";
        cin >> pilihan;

        switch(pilihan){
            case 1:
                searchLaguByJudul(LL);
                system("pause");
                break;
            case 2:
                searchLaguByArtis(LL);
                system("pause");
                break;
            case 3:
                searchLaguByGenre(LL);
                system("pause");
                break;
            case 4:
                searchLaguByAlbum(LL);
                system("pause");
                break;
            case 0:
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
                system("pause");
                break;
        }
    } while(pilihan != 0);
}

void searchPlaylist(adrUser U){
    system("cls");
    cout << "=== CARI PLAYLIST ===" << endl;
    string keyword;
    cout << "Masukkan nama playlist: ";
    cin.ignore();
    getline(cin, keyword);

    keyword = toLowerString(keyword);

    cout << "\n=== HASIL PENCARIAN ===" << endl;
    adrPlaylist PL = U->firstPlaylist;
    int count = 0;

    while(PL != NULL){
        string nama = toLowerString(PL->info.nama);

        if(containsString(nama, keyword)){
            cout << "\n[" << PL->info.id << "] " << PL->info.nama << endl;
            cout << "    Deskripsi : " << PL->info.deskripsi << endl;
            cout << "    Dibuat    : " << PL->info.tanggal_dibuat << endl;
            cout << "    Jumlah    : " << getTotalLaguInPlaylist(PL) << " lagu" << endl;
            cout << "    Play Count: " << getTotalPlayCount(PL) << "x" << endl;
            count++;
        }
        PL = PL->next;
    }

    if(count == 0){
        cout << "Tidak ada playlist yang ditemukan dengan kata kunci \"" << keyword << "\"" << endl;
    } else {
        cout << "\nTotal: " << count << " playlist ditemukan" << endl;
    }
}

void searchLaguInPlaylist(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    string namaPlaylist;
    cout << "Nama playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL == NULL){
        cout << "\nPlaylist tidak ditemukan!\n";
        system("pause");
        return;
    }

    string keyword;
    cout << "Masukkan kata kunci judul lagu: ";
    getline(cin, keyword);

    keyword = toLowerString(keyword);

    cout << "\n=== HASIL PENCARIAN DI PLAYLIST: " << PL->info.nama << " ===" << endl;
    adrItem IT = PL->firstItem;
    int count = 0;

    while(IT != NULL){
        string judul = toLowerString(IT->lagu->info.judul);

        if(containsString(judul, keyword)){
            cout << "\n[" << IT->lagu->info.id_lagu << "] " << IT->lagu->info.judul << endl;
            cout << "    Artis  : " << IT->lagu->info.artis << endl;
            cout << "    Album  : " << IT->lagu->info.album << endl;
            cout << "    Genre  : " << IT->lagu->info.genre << endl;
            cout << "    Durasi : " << formatDurasi(IT->lagu->info.durasi) << endl;
            cout << "    Play Count: " << IT->play_count << "x" << endl;
            count++;
        }
        IT = IT->next;
    }

    if(count == 0){
        cout << "Tidak ada lagu yang ditemukan dengan kata kunci \"" << keyword << "\"" << endl;
    } else {
        cout << "\nTotal: " << count << " lagu ditemukan" << endl;
    }
}

// ========== USER OPERATIONS ==========
void lihatSemuaPlaylist(adrUser U){
    system("cls");
    cout << "=== PLAYLIST: " << U->info.username << " ===" << endl;
    printAllPlaylists(U);
}

void buatPlaylistBaru(adrUser U){
    system("cls");
    cout << "=== BUAT PLAYLIST BARU ===" << endl;
    adrPlaylist P = inputPlaylist(U);
    insertLastPlaylist(U, P);
    cout << "\nPlaylist berhasil dibuat!\n";
}

void hapusPlaylistUser(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    string nama;
    cout << "Nama playlist yang akan dihapus: ";
    cin.ignore();
    getline(cin, nama);

    adrPlaylist P = findPlaylist(U, nama);
    if(P != NULL){
        deletePlaylist(U, P);
        cout << "\nPlaylist berhasil dihapus!\n";
    }else{
        cout << "\nPlaylist tidak ditemukan!\n";
    }
}

void editPlaylistUser(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    string nama;
    cout << "Nama playlist yang akan diedit: ";
    cin.ignore();
    getline(cin, nama);

    adrPlaylist P = findPlaylist(U, nama);
    if(P != NULL){
        cout << "\n=== EDIT PLAYLIST ===" << endl;
        editPlaylist(P);
        cout << "\nPlaylist berhasil diedit!\n";
    }else{
        cout << "\nPlaylist tidak ditemukan!\n";
    }
}

void tambahLaguKePlaylistMenu(adrUser U, List_lagu LL){
    system("cls");
    lihatSemuaPlaylist(U);
    string namaPlaylist, judulLagu;
    cout << "Nama playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL == NULL){
        cout << "\nPlaylist tidak ditemukan!\n";
        return;
    }

    printInfo_lagu(LL);
    cout << "Judul lagu: ";
    getline(cin, judulLagu);

    address_lagu L = findElm_lagu(LL, judulLagu);
    if(L != NULL){
        tambahLaguKePlaylist(U, PL, L);
    }else{
        cout << "\nLagu tidak ditemukan!\n";
    }
}

void hapusLaguDariPlaylistMenu(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    string namaPlaylist, judulLagu;
    cout << "Nama playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL == NULL){
        cout << "\nPlaylist tidak ditemukan!\n";
        return;
    }

    printIsiPlaylist(PL);
    cout << "Judul lagu yang akan dihapus: ";
    getline(cin, judulLagu);

    adrItem IT = PL->firstItem;
    address_lagu L = NULL;
    while(IT != NULL){
        if(IT->lagu->info.judul == judulLagu){
            L = IT->lagu;
            break;
        }
        IT = IT->next;
    }

    if(L != NULL){
        hapusLaguDariPlaylist(PL, L);
    }else{
        cout << "\nLagu tidak ada di playlist!\n";
    }
}

void lihatIsiPlaylistMenu(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    string namaPlaylist;
    cout << "Nama playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL != NULL){
        system("cls");
        showPlaylist(PL);
        printIsiPlaylist(PL);

        // Opsi untuk langsung play
        if(PL->firstItem != NULL){
            char pilihan;
            cout << "\nPutar playlist ini sekarang? (Y/N): ";
            cin >> pilihan;

            if(pilihan == 'Y' || pilihan == 'y'){
                musicPlayer(PL);
            }
        }
    }else{
        cout << "\nPlaylist tidak ditemukan!\n";
    }
}

// ========== STATISTICS ==========
void statistikGlobal(ListUser LU, List_lagu LL){
    system("cls");
    cout << "========== STATISTIK GLOBAL ==========" << endl;

    int totalUser = hitungUser(LU);
    int totalLagu = hitungLagu(LL);
    int totalPlaylist = 0;
    int totalPlay = 0;

    adrUser U = LU.first;
    while(U != NULL){
        totalPlaylist += hitungPlaylist(U);
        adrPlaylist PL = U->firstPlaylist;
        while(PL != NULL){
            totalPlay += getTotalPlayCount(PL);
            PL = PL->next;
        }
        U = U->next;
    }

    cout << "\nTotal User: " << totalUser << endl;
    cout << "Total Lagu: " << totalLagu << endl;
    cout << "Total Playlist: " << totalPlaylist << endl;
    cout << "Total Play Count: " << totalPlay << "x" << endl;

    laguTerpopulerGlobal(LU);
    userTeraktif(LU);
    cout << "\n======================================" << endl;
}

void laguTerpopulerGlobal(ListUser LU){
    cout << "\n========== TOP 10 LAGU TERPOPULER ==========" << endl;

    address_lagu laguList[100];
    int playCount[100];
    int totalLagu = 0;

    adrUser U = LU.first;
    while(U != NULL){
        adrPlaylist PL = U->firstPlaylist;
        while(PL != NULL){
            adrItem IT = PL->firstItem;
            while(IT != NULL){
                bool found = false;
                for(int i = 0; i < totalLagu; i++){
                    if(laguList[i] == IT->lagu){
                        playCount[i] += IT->play_count;
                        found = true;
                        break;
                    }
                }

                if(!found){
                    laguList[totalLagu] = IT->lagu;
                    playCount[totalLagu] = IT->play_count;
                    totalLagu++;
                }
                IT = IT->next;
            }
            PL = PL->next;
        }
        U = U->next;
    }

    for(int i = 0; i < totalLagu - 1; i++){
        for(int j = 0; j < totalLagu - i - 1; j++){
            if(playCount[j] < playCount[j+1]){
                int tempCount = playCount[j];
                playCount[j] = playCount[j+1];
                playCount[j+1] = tempCount;

                address_lagu tempLagu = laguList[j];
                laguList[j] = laguList[j+1];
                laguList[j+1] = tempLagu;
            }
        }
    }

    int limit;
    if (totalLagu < 10) {
        limit = totalLagu;
    } else {
        limit = 10;
    }

    for(int i = 0; i < limit; i++){
        if(playCount[i] > 0){
            cout << (i+1) << ". " << laguList[i]->info.judul
                 << " - " << laguList[i]->info.artis
                 << " (" << playCount[i] << "x play)" << endl;
        }
    }
}

void userTeraktif(ListUser LU){
    cout << "\n========== TOP 5 USER TERAKTIF ==========" << endl;

    adrUser userList[50];
    int playCount[50];
    int totalUser = 0;

    adrUser U = LU.first;
    while(U != NULL){
        userList[totalUser] = U;
        playCount[totalUser] = 0;

        adrPlaylist PL = U->firstPlaylist;
        while(PL != NULL){
            playCount[totalUser] += getTotalPlayCount(PL);
            PL = PL->next;
        }

        totalUser++;
        U = U->next;
    }

    for(int i = 0; i < totalUser - 1; i++){
        for(int j = 0; j < totalUser - i - 1; j++){
            if(playCount[j] < playCount[j+1]){
                int tempCount = playCount[j];
                playCount[j] = playCount[j+1];
                playCount[j+1] = tempCount;

                adrUser tempUser = userList[j];
                userList[j] = userList[j+1];
                userList[j+1] = tempUser;
            }
        }
    }
    int limit;
    if (totalUser < 5) {
        limit = totalUser;
    } else {
        limit = 5;
    }

    for(int i = 0; i < limit; i++){
        if(playCount[i] > 0){
            cout << (i+1) << ". " << userList[i]->info.username
                 << " (" << userList[i]->info.nama_lengkap << ") - "
                 << playCount[i] << "x play" << endl;
        }
    }
}

void laguTerpopulerUser(adrUser U){
    system("cls");
    cout << "========== LAGU FAVORIT SAYA ==========" << endl;

    address_lagu laguList[100];
    int playCount[100];
    int totalLagu = 0;

    adrPlaylist PL = U->firstPlaylist;
    while(PL != NULL){
        adrItem IT = PL->firstItem;
        while(IT != NULL){
            bool found = false;
            for(int i = 0; i < totalLagu; i++){
                if(laguList[i] == IT->lagu){
                    playCount[i] += IT->play_count;
                    found = true;
                    break;
                }
            }

            if(!found){
                laguList[totalLagu] = IT->lagu;
                playCount[totalLagu] = IT->play_count;
                totalLagu++;
            }

            IT = IT->next;
        }
        PL = PL->next;
    }

    for(int i = 0; i < totalLagu - 1; i++){
        for(int j = 0; j < totalLagu - i - 1; j++){
            if(playCount[j] < playCount[j+1]){
                int tempCount = playCount[j];
                playCount[j] = playCount[j+1];
                playCount[j+1] = tempCount;

                address_lagu tempLagu = laguList[j];
                laguList[j] = laguList[j+1];
                laguList[j+1] = tempLagu;
            }
        }
    }

    int limit;
    if (totalLagu < 10) {
        limit = totalLagu;
    } else {
        limit = 10;
    }

    for(int i = 0; i < limit; i++){
        if(playCount[i] > 0){
            cout << (i+1) << ". " << laguList[i]->info.judul
                 << " - " << laguList[i]->info.artis
                 << " (" << playCount[i] << "x play)" << endl;
        }
    }
    cout << endl;
}

void playlistTerpopulerUser(adrUser U){
    system("cls");
    cout << "========== PLAYLIST FAVORIT SAYA ==========" << endl;

    adrPlaylist PL = U->firstPlaylist;
    adrPlaylist plList[50];
    int playCount[50];
    int total = 0;

    while(PL != NULL){
        plList[total] = PL;
        playCount[total] = getTotalPlayCount(PL);
        total++;
        PL = PL->next;
    }

    for(int i = 0; i < total - 1; i++){
        for(int j = 0; j < total - i - 1; j++){
            if(playCount[j] < playCount[j+1]){
                int tempCount = playCount[j];
                playCount[j] = playCount[j+1];
                playCount[j+1] = tempCount;

                adrPlaylist tempPL = plList[j];
                plList[j] = plList[j+1];
                plList[j+1] = tempPL;
            }
        }
    }

    for(int i = 0; i < total; i++){
        cout << (i+1) << ". " << plList[i]->info.nama
             << " (" << getTotalLaguInPlaylist(plList[i]) << " lagu, "
             << playCount[i] << "x play)" << endl;
    }
    cout << endl;
}

// ========== MENU ADMIN ==========
void menuAdmin(ListUser &LU, List_lagu &LL){
    int pil;
    string username, judul;
    adrUser U;
    address_lagu L;

    do{
        system("cls");
        tampilkanHeader();
        cout << "\n=== ADMIN DASHBOARD ===" << endl;
        cout << "\n--- USER MANAGEMENT ---" << endl;
        cout << "1. Lihat Semua User" << endl;
        cout << "2. Lihat Detail User & Playlistnya" << endl;
        cout << "3. Hapus User" << endl;
        cout << "\n--- MUSIC DATABASE ---" << endl;
        cout << "4. Lihat Semua Lagu" << endl;
        cout << "5. Tambah Lagu Baru" << endl;
        cout << "6. Edit Info Lagu" << endl;
        cout << "7. Hapus Lagu" << endl;
        cout << "\n--- ANALYTICS ---" << endl;
        cout << "8. Statistik Global" << endl;
        cout << "\n0. Logout" << endl;
        cout << "\nPilihan: ";
        cin >> pil;

        switch(pil){
        case 1:
            system("cls");
            printAllUsers(LU);
            system("pause");
            break;

        case 2:
            system("cls");
            printAllUsers(LU);
            cout << "Username: ";
            cin >> username;
            U = findUser(LU, username);
            if(U != NULL){
                cout << "\n";
                showUser(U);
                printAllPlaylists(U);
            }else{
                cout << "\nUser tidak ditemukan!\n";
            }
            system("pause");
            break;

        case 3:
            system("cls");
            printAllUsers(LU);
            cout << "Username yang akan dihapus: ";
            cin >> username;
            U = findUser(LU, username);
            if(U != NULL){
                deleteUser(LU, U);
                cout << "\nUser berhasil dihapus!\n";
            }else{
                cout << "\nUser tidak ditemukan!\n";
            }
            system("pause");
            break;

        case 4:
            printInfo_lagu(LL);
            cout << "Total: " << hitungLagu(LL) << " lagu\n";
            system("pause");
            break;

        case 5:
            system("cls");
            cout << "=== TAMBAH LAGU BARU ===" << endl;
            L = input_lagu();
            insertLast_lagu(LL, L);
            cout << "\nLagu berhasil ditambahkan!\n";
            system("pause");
            break;

        case 6:
            printInfo_lagu(LL);
            cout << "Judul lagu yang akan diedit: ";
            cin.ignore();
            getline(cin, judul);
            L = findElm_lagu(LL, judul);
            if(L != NULL){
                cout << "\n=== EDIT LAGU ===" << endl;
                editInfo_lagu(L);
                cout << "\nLagu berhasil diedit!\n";
            }else{
                cout << "\nLagu tidak ditemukan!\n";
            }
            system("pause");
            break;

        case 7:
            printInfo_lagu(LL);
            cout << "Judul lagu yang akan dihapus: ";
            cin.ignore();
            getline(cin, judul);
            L = findElm_lagu(LL, judul);
            if(L != NULL){
                deleteSearch_lagu(LL, L);
                cout << "\nLagu berhasil dihapus!\n";
            }else{
                cout << "\nLagu tidak ditemukan!\n";
            }
            system("pause");
            break;

        case 8:
            statistikGlobal(LU, LL);
            system("pause");
            break;

        case 0:
            cout << "\nLogout berhasil!\n";
            system("pause");
            break;

        default:
            cout << "\nPilihan tidak valid!\n";
            system("pause");
            break;
        }
    }while(pil != 0);
}

// ========== MENU USER ==========
void menuUser(ListUser &LU, List_lagu &LL, string username){
    adrUser U = findUser(LU, username);
    if(U == NULL) return;

    int pil;

    do{
        system("cls");
        tampilkanHeader();
        cout << "\n=== USER: " << U->info.username << " (" << U->info.tipe_akun << ") ===" << endl;
        cout << "Playlist: " << hitungPlaylist(U) << " | ";

        int totalPlay = 0;
        adrPlaylist PL = U->firstPlaylist;
        while(PL != NULL){
            totalPlay += getTotalPlayCount(PL);
            PL = PL->next;
        }
        cout << "Total Play: " << totalPlay << "x" << endl;

        cout << "\n--- MY LIBRARY ---" << endl;
        cout << "1. Lihat Semua Playlist" << endl;
        cout << "2. Buat Playlist Baru" << endl;
        cout << "3. Hapus Playlist" << endl;
        cout << "4. Edit Playlist" << endl;
        cout << "\n--- PLAYLIST MANAGEMENT ---" << endl;
        cout << "5. Lihat Detail Playlist (dengan opsi play)" << endl;
        cout << "6. Tambah Lagu ke Playlist" << endl;
        cout << "7. Hapus Lagu dari Playlist" << endl;
        cout << "8. Urutkan Lagu di Playlist" << endl;
        cout << "\n--- SEARCH & DISCOVERY ---" << endl;
        cout << "9. Cari Lagu (Database)" << endl;
        cout << "10. Cari Playlist Saya" << endl;
        cout << "11. Cari Lagu di Playlist" << endl;
        cout << "12. Browse Semua Lagu" << endl;
        cout << "13. Lagu Terpopuler Global" << endl;
        cout << "\n--- MY FAVORITES ---" << endl;
        cout << "14. Lagu Favorit Saya" << endl;
        cout << "15. Playlist Favorit Saya" << endl;
        cout << "\n--- ACCOUNT ---" << endl;
        cout << "16. Edit Profil" << endl;
        cout << "\n0. Logout" << endl;
        cout << "\nPilihan: ";
        cin >> pil;

        switch(pil){
        case 1:
            system("cls");
            lihatSemuaPlaylist(U);
            system("pause");
            break;
        case 2:
            buatPlaylistBaru(U);
            system("pause");
            break;
        case 3:
            hapusPlaylistUser(U);
            system("pause");
            break;
        case 4:
            editPlaylistUser(U);
            system("pause");
            break;
        case 5:
            lihatIsiPlaylistMenu(U);
            system("pause");
            break;
        case 6:
            tambahLaguKePlaylistMenu(U, LL);
            system("pause");
            break;
        case 7:
            hapusLaguDariPlaylistMenu(U);
            system("pause");
            break;
        case 8:
            sortingPlaylistMenu(U);
            break;
        case 9:
            searchingMenu(LL);
            break;
        case 10:
            searchPlaylist(U);
            system("pause");
            break;
        case 11:
            searchLaguInPlaylist(U);
            system("pause");
            break;
        case 12:
            printInfo_lagu(LL);
            system("pause");
            break;
        case 13:
            system("cls");
            laguTerpopulerGlobal(LU);
            system("pause");
            break;
        case 14:
            laguTerpopulerUser(U);
            system("pause");
            break;
        case 15:
            playlistTerpopulerUser(U);
            system("pause");
            break;
        case 16:
            system("cls");
            cout << "=== EDIT PROFIL ===" << endl;
            editUser(U);
            cout << "\nProfil berhasil diupdate!\n";
            system("pause");
            break;
        case 0:
            cout << "\nLogout berhasil!\n";
            system("pause");
            break;
        default:
            cout << "\nPilihan tidak valid!\n";
            system("pause");
            break;
        }
    }while(pil != 0);
}

// ========== DATA DUMMY ==========
void dataDummy(ListUser &LU, List_lagu &LL){
    adrUser U;
    adrPlaylist PL;
    address_lagu L;
    adrItem IT;
    infoPlaylist plInfo;

    // === JOHN DOE ===
    U = findUser(LU, "john_doe");
    if(U != NULL){
        plInfo.id = 1;
        plInfo.nama = "My Favorites";
        plInfo.deskripsi = "Lagu-lagu favorit saya";
        plInfo.tanggal_dibuat = "01/01/2024";
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 2);
        IT = alokasiItem(L);
        IT->play_count = 25;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 3);
        IT = alokasiItem(L);
        IT->play_count = 18;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 6);
        IT = alokasiItem(L);
        IT->play_count = 12;
        insertLastItem(PL, IT);

        plInfo.id = 2;
        plInfo.nama = "Workout Mix";
        plInfo.deskripsi = "Energi untuk olahraga";
        plInfo.tanggal_dibuat = "15/01/2024";
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 14);
        IT = alokasiItem(L);
        IT->play_count = 30;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 4);
        IT = alokasiItem(L);
        IT->play_count = 15;
        insertLastItem(PL, IT);
    }

    // === JANE SMITH ===
    U = findUser(LU, "jane_smith");
    if(U != NULL){
        plInfo.id = 3;
        plInfo.nama = "Lagu Santai";
        plInfo.deskripsi = "Untuk relaksasi";
        plInfo.tanggal_dibuat = "10/02/2024";
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 5);
        IT = alokasiItem(L);
        IT->play_count = 20;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 10);
        IT = alokasiItem(L);
        IT->play_count = 15;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 16);
        IT = alokasiItem(L);
        IT->play_count = 10;
        insertLastItem(PL, IT);
    }

    // === MIKE WILSON ===
    U = findUser(LU, "mike_wilson");
    if(U != NULL){
        plInfo.id = 4;
        plInfo.nama = "Rock Legends";
        plInfo.deskripsi = "Classic rock hits";
        plInfo.tanggal_dibuat = "20/02/2024";
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 1);
        IT = alokasiItem(L);
        IT->play_count = 35;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 11);
        IT = alokasiItem(L);
        IT->play_count = 28;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 12);
        IT = alokasiItem(L);
        IT->play_count = 22;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 15);
        IT = alokasiItem(L);
        IT->play_count = 18;
        insertLastItem(PL, IT);
    }

    // === SARAH LEE ===
    U = findUser(LU, "sarah_lee");
    if(U != NULL){
        plInfo.id = 5;
        plInfo.nama = "Pop Hits 2020s";
        plInfo.deskripsi = "Best pop songs";
        plInfo.tanggal_dibuat = "01/03/2024";
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 7);
        IT = alokasiItem(L);
        IT->play_count = 40;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 8);
        IT = alokasiItem(L);
        IT->play_count = 32;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 9);
        IT = alokasiItem(L);
        IT->play_count = 27;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 17);
        IT = alokasiItem(L);
        IT->play_count = 19;
        insertLastItem(PL, IT);

        plInfo.id = 6;
        plInfo.nama = "Study Music";
        plInfo.deskripsi = "Fokus belajar";
        plInfo.tanggal_dibuat = "15/03/2024";
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 18);
        IT = alokasiItem(L);
        IT->play_count = 12;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 19);
        IT = alokasiItem(L);
        IT->play_count = 8;
        insertLastItem(PL, IT);
    }

    // === DAVID BROWN ===
    U = findUser(LU, "david_brown");
    if(U != NULL){
        plInfo.id = 7;
        plInfo.nama = "Hip-Hop Vibes";
        plInfo.deskripsi = "Best rap songs";
        plInfo.tanggal_dibuat = "10/03/2024";
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 14);
        IT = alokasiItem(L);
        IT->play_count = 45;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 4);
        IT = alokasiItem(L);
        IT->play_count = 22;
        insertLastItem(PL, IT);
    }
}
