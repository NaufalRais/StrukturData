#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Node{
    string judul;
    string penyanyi;
    Node *prev;
    Node *next;
};

Node *head = nullptr;
Node *tail = nullptr;


bool validasiInput(string input, string tipe){
    if (input.empty())
    {
        cout << "Error! Input tidak boleh kosong.\n";
        return false;
    }

    if (tipe == "huruf")
    {
        for (char c : input)
        {
            if (!isalpha(c) && c != ' ')
            {
                cout << "Error! Input hanya boleh berupa huruf dan spasi.\n";
                return false;
            }
        }
    }

    if (tipe == "angka"){
        for (char c : input){
            if (!isdigit(c)){
                cout << "Error! Pilihan harus berupa angka.\n";
                return false;
            }
        }
    }
    return true;
}

Node *cariLagu(string judul){
    Node *temp = head;

    while (temp != nullptr){
        if (temp->judul == judul){
            return temp;
        }

        temp = temp->next;
    }
    return nullptr;
}

void tambahLagu(){
    string judul;
    string penyanyi;

    cin.ignore();

    // Input judul
    while (true){
        cout << "Masukkan judul lagu: ";
        getline(cin, judul);

        if (validasiInput(judul, "huruf")){
            break;
        }
    }

    // Cek judul duplikat
    if (cariLagu(judul) != nullptr){
        cout << "Error! Judul lagu sudah tersedia.\n";
        return;
    }

    // Input penyanyi
    while (true){
        cout << "Masukkan nama penyanyi: ";
        getline(cin, penyanyi);

        if (validasiInput(penyanyi, "huruf")){
            break;
        }
    }

    Node *baru = new Node;

    baru->judul = judul;
    baru->penyanyi = penyanyi;
    baru->prev = nullptr;
    baru->next = nullptr;

    // Jika playlist masih kosong
    if (head == nullptr){
        head = baru;
        tail = baru;
    }
    else{
        baru->prev = tail;
        tail->next = baru;
        tail = baru;
    }

    cout << "Lagu berhasil ditambahkan.\n";
}

void tampilkanMaju(){
    if (head == nullptr){
        cout << "Playlist kosong.\n";
        return;
    }

    Node *temp = head;

    cout << "\n=== PLAYLIST MAJU ===\n";

    while (temp != nullptr){
        cout << "Judul    : " << temp->judul << endl;
        cout << "Penyanyi : " << temp->penyanyi << endl;
        cout << "--------------------------\n";

        temp = temp->next;
    }
}

void tampilkanMundur(){
    if (tail == nullptr){
        cout << "Playlist kosong.\n";
        return;
    }

    Node *temp = tail;

    cout << "\n=== PLAYLIST MUNDUR ===\n";

    while (temp != nullptr){
        cout << "Judul    : " << temp->judul << endl;
        cout << "Penyanyi : " << temp->penyanyi << endl;
        cout << "--------------------------\n";

        temp = temp->prev;
    }
}

void cariData(){
    string judul;

    cin.ignore();

    while (true){
        cout << "Masukkan judul lagu yang dicari: ";
        getline(cin, judul);

        if (validasiInput(judul, "huruf")){
            break;
        }
    }

    Node *hasil = cariLagu(judul);

    if (hasil == nullptr){
        cout << "Lagu tidak ditemukan.\n";
    }
    else
    {
        cout << "\nLagu ditemukan!\n";
        cout << "Judul    : " << hasil->judul << endl;
        cout << "Penyanyi : " << hasil->penyanyi << endl;
    }
}

void hapusLagu(){
    string judul;

    cin.ignore();

    while (true){
        cout << "Masukkan judul lagu yang ingin dihapus: ";
        getline(cin, judul);

        if (validasiInput(judul, "huruf"))
        {
            break;
        }
    }

    Node *temp = cariLagu(judul);

    if (temp == nullptr){
        cout << "Lagu tidak ditemukan.\n";
        return;
    }

    // Jika hanya ada satu node
    if (head == tail){
        head = nullptr;
        tail = nullptr;
    }

    // Jika node yang dihapus adalah head
    else if (temp == head){
        head = head->next;
        head->prev = nullptr;
    }

    // Jika node yang dihapus adalah tail
    else if (temp == tail){
        tail = tail->prev;
        tail->next = nullptr;
    }

    // Jika node berada di tengah
    else{
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    delete temp;

    cout << "Lagu berhasil dihapus.\n";
}

void jumlahLagu(){
    int jumlah = 0;
    Node *temp = head;

    while (temp != nullptr){
        jumlah++;
        temp = temp->next;
    }

    cout << "Jumlah lagu dalam playlist: " << jumlah << endl;
}

void hapusSemua(){
    Node *temp = head;

    while (temp != nullptr){
        Node *hapus = temp;
        temp = temp->next;
        delete hapus;
    }

    head = nullptr;
    tail = nullptr;
}

int main(){
    int pilihan;
    char ulang = 'y';

    do{
        system("cls");

        cout << "==============================\n";
        cout << "      PLAYLIST MUSIK\n";
        cout << "==============================\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Tampilkan Playlist Maju\n";
        cout << "3. Tampilkan Playlist Mundur\n";
        cout << "4. Cari Lagu\n";
        cout << "5. Hapus Lagu\n";
        cout << "6. Jumlah Lagu\n";
        cout << "7. Keluar\n";
        cout << "==============================\n";

        string inputPilihan;

        while (true){
            cout << "Pilih menu: ";
            cin >> inputPilihan;

            if (validasiInput(inputPilihan, "angka")){
                pilihan = stoi(inputPilihan);
                break;
            }
        }

        switch (pilihan){
        case 1:
            tambahLagu();
            break;

        case 2:
            tampilkanMaju();
            break;

        case 3:
            tampilkanMundur();
            break;

        case 4:
            cariData();
            break;

        case 5:
            hapusLagu();
            break;

        case 6:
            jumlahLagu();
            break;

        case 7:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Error! Pilihan menu tidak tersedia.\n";
            break;
        }

        if (pilihan != 7){
            cout << "\nApakah ingin mengulang? (y/n): ";
            cin >> ulang;
        }

    } while (pilihan != 7 && ulang != 'n');

    hapusSemua();
    return 0;
}