#include "menu.h"

int main(){
    ListUser LU;
    List_lagu LL;
    CurrentUser currentUser;
    currentUser.isLoggedIn = false;

    // Inisialisasi
    createListUser(LU);
    createList_lagu(LL);

    // Load data dummy
    dataUser(LU);
    data_lagu(LL);
    dataDummy(LU, LL);

    // Main loop
    while(true){
        if(!login(currentUser, LU)){
            break;
        }

        if(currentUser.role == "admin"){
            menuAdmin(LU, LL);
        }
        else if(currentUser.role == "user"){
            menuUser(LU, LL, currentUser.username);
        }

        logout(currentUser);
    }

    system("cls");
    cout << "\n==========================================================" << endl;
    cout << "  Terima kasih telah menggunakan Cotify!" << endl;
    cout << "  Sampai jumpa lagi!" << endl;
    cout << "==========================================================" << endl;

    return 0;
}
