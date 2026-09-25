#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct Node{
    string nim;
    string nama;
    double ipk;

    Node *next;
};

Node *head = nullptr;
Node* cariMahasiswa(string nim){
    Node *temp = head;

    while (temp != nullptr){
        if (temp->nim == nim)
        {
            return temp;
        }

        temp = temp->next;
    }

    return nullptr;
}

bool validasiData(string nim, string nama, string ipk){
    if (nim.empty()){
        cout << "NIM tidak boleh kosong" << endl;
        return false;
    }

    for (char c : nim){
        if (!isdigit(c)){
            cout << "NIM harus berupa angka" << endl;
            return false;
        }
    }

    if (nama.empty()){
        cout << "Nama tidak boleh kosong" << endl;
        return false;
    }

    for (char c : nama){
        if (!isalpha(c) && c != ' '){
            cout << "Nama harus berupa huruf" << endl;
            return false;
        }
    }

    try{
        size_t posisi;
        double nilaiIPK = stod(ipk, &posisi);

        if (posisi != ipk.length()){
            cout << "IPK harus berupa angka" << endl;
            return false;
        }

        if (nilaiIPK < 0.00 || nilaiIPK > 4.00){
            cout << "IPK harus berada di antara 0.00 sampai 4.00" << endl;
            return false;
        }
    }
    catch (...){
        cout << "IPK harus berupa angka" << endl;
        return false;
    }

    return true;
}

void tambahMahasiswa()
{
    Node *baru = new Node;

    string nim;
    string nama;
    string ipk;

    cout << "\nMasukkan NIM  : ";
    cin >> nim;

    if (cariMahasiswa(nim) != nullptr){
        cout << "NIM sudah terdaftar.\n";
        delete baru;
        return;
    }

    cin.ignore();

    cout << "Masukkan Nama : ";
    getline(cin, nama);

    cout << "Masukkan IPK (ex:3.6): ";
    cin >> ipk;

    if (!validasiData(nim, nama, ipk)){
        cout << "Data tidak valid.\n";
        delete baru;
        return;
    }

    baru->nim = nim;
    baru->nama = nama;
    baru->ipk = stod(ipk);
    baru->next = nullptr;

    if (head == nullptr){
        head = baru;
    }
    else{
        Node *temp = head;
        while (temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = baru;
    }
    cout << "Mahasiswa berhasil ditambahkan\n";
}

void tampilkanMahasiswa()
{
    if (head == nullptr){
        cout << "\nBelum ada data mahasiswa\n";
        return;
    }

    Node *temp = head;
    int nomor = 1;

    cout << "\n========== DATA MAHASISWA ==========\n";

    while (temp != nullptr){
        cout << "Data ke-" << nomor << endl;
        cout << "NIM  : " << temp->nim << endl;
        cout << "Nama : " << temp->nama << endl;
        cout << "IPK  : " << temp->ipk << endl;
        cout << "------------------------------------\n";

        temp = temp->next;
        nomor++;
    }
}

void cariData(){
    string nim;

    cout << "\nMasukkan NIM yang dicari: ";
    cin >> nim;

    Node *hasil = cariMahasiswa(nim);

    if (hasil == nullptr){
        cout << "Mahasiswa tidak ditemukan.\n";
    }
    else{
        cout << "\nMahasiswa ditemukan.\n";
        cout << "NIM  : " << hasil->nim << endl;
        cout << "Nama : " << hasil->nama << endl;
        cout << "IPK  : " << hasil->ipk << endl;
    }
}

void hapusMahasiswa(){
    string nim;

    cout << "\nMasukkan NIM yang ingin dihapus: ";
    cin >> nim;

    if (head == nullptr){
        cout << "List masih kosong.\n";
        return;
    }

    if (head->nim == nim){
        Node *hapus = head;
        head = head->next;

        delete hapus;

        cout << "Mahasiswa berhasil dihapus.\n";
        return;
    }

    Node *temp = head;

    while (temp->next != nullptr &&
           temp->next->nim != nim){
        temp = temp->next;
    }

    if (temp->next == nullptr){
        cout << "Mahasiswa tidak ditemukan.\n";
        return;
    }

    Node *hapus = temp->next;
    temp->next = hapus->next;
    delete hapus;
    cout << "Mahasiswa berhasil dihapus.\n";
}

int jumlahMahasiswa(){
    int jumlah = 0;
    Node *temp = head;

    while (temp != nullptr){
        jumlah++;
        temp = temp->next;
    }

    return jumlah;
}

void hapusSemua(){
    Node *temp;

    while (head != nullptr){
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main(){
    int pilihan;
    char ulang;

    do{
        system("cls");
        cout << "NAUFAL RAIS RYANUR\n";
        cout << "1232502228\n";

        cout << "\n====================================\n";
        cout << "   PROGRAM DATA MAHASISWA\n";
        cout << "   SINGLY LINKED LIST\n";
        cout << "====================================\n";
        cout << "1. Tambah mahasiswa\n";
        cout << "2. Tampilkan seluruh mahasiswa\n";
        cout << "3. Cari mahasiswa berdasarkan NIM\n";
        cout << "4. Hapus mahasiswa berdasarkan NIM\n";
        cout << "5. Tampilkan jumlah mahasiswa\n";
        cout << "6. Keluar\n";
        cout << "====================================\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan){
        case 1:
            tambahMahasiswa();
            break;

        case 2:
            tampilkanMahasiswa();
            break;

        case 3:
            cariData();
            break;

        case 4:
            hapusMahasiswa();
            break;

        case 5:
            cout << "\nJumlah mahasiswa: " << jumlahMahasiswa() << endl;
            break;

        case 6:
            cout << "\nProgram selesai.\n";
            break;

        default:
            cout << "\nPilihan menu tidak valid.\n";
        }
        if (pilihan != 6)
        {
            cout << "\nApakah anda ingin mengulang? (y/n): ";
            cin >> ulang;
        }
    } while (pilihan != 6 && ulang != 'n');
    hapusSemua();
    return 0;
}