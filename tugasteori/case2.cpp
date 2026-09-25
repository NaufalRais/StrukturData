#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const int MAX_PARKIR = 5;

struct Kendaraan{
    string nomorPolisi;
    string namaPemilik;
    string jenisKendaraan;
    string jamMasuk;
    string status;
};

struct Node{
    Kendaraan data;
    Node *next;
};

Kendaraan parkir[MAX_PARKIR];
int jumlahParkir = 0;

Node *head = nullptr;
Node *tail = nullptr;


int inputAngka(string pesan){
    string input;

    while (true){
        cout << pesan;
        cin >> input;

        bool valid = true;

        for (char c : input){
            if (!isdigit(c))
            {
                valid = false;
                break;
            }
        }

        if (valid && !input.empty()){
            return stoi(input);
        }
        cout << "Error! Input harus berupa angka.\n";
    }
}

// Validasi Huruf
string inputHuruf(string pesan){
    string input;

    while (true){
        cout << pesan;
        cin.ignore();
        getline(cin, input);

        if (input.empty()){
            cout << "Error! Input tidak boleh kosong.\n";
            continue;
        }

        bool valid = true;

        for (char c : input){
            if (!isalpha(c) && c != ' ')
            {
                valid = false;
                break;
            }
        }

        if (valid){
            return input;
        }
        cout << "Error! Input hanya boleh berupa huruf dan spasi.\n";
    }
}


// Validasi nomor polisi
// Huruf dan angka diperbolehkan
string inputNomorPolisi(){
    string nomor;

    while (true){
        cout << "Nomor Polisi     : ";
        cin >> nomor;

        bool valid = true;

        for (char c : nomor){
            if (!isalnum(c)){
                valid = false;
                break;
            }
        }

        if (!valid || nomor.empty()){
            cout << "Error! Nomor polisi hanya boleh berisi huruf dan angka.\n";
            continue;
        }

        return nomor;
    }
}


// Validasi jam
string inputJam(){
    string jam;

    while (true){
        cout << "Jam Masuk        : ";
        cin >> jam;

        if (jam.length() != 5 || jam[2] != ':'){
            cout << "Error! Format jam harus HH:MM. Contoh: 08:30\n";
            continue;
        }

        if (!isdigit(jam[0]) ||
            !isdigit(jam[1]) ||
            !isdigit(jam[3]) ||
            !isdigit(jam[4]))
        {
            cout << "Error! Jam hanya boleh berisi angka.\n";
            continue;
        }

        int jamAngka = (jam[0] - '0') * 10 + (jam[1] - '0');
        int menitAngka = (jam[3] - '0') * 10 + (jam[4] - '0');

        if (jamAngka < 0 || jamAngka > 23){
            cout << "Error! Jam harus berada antara 00 sampai 23.\n";
            continue;
        }

        if (menitAngka < 0 || menitAngka > 59){
            cout << "Error! Menit harus berada antara 00 sampai 59.\n";
            continue;
        }
        return jam;
    }
}

void tambahDaftarTunggu(Kendaraan data){
    Node *baru = new Node;

    baru->data = data;
    baru->next = nullptr;

    if (head == nullptr){
        head = baru;
        tail = baru;
    }
    else{
        tail->next = baru;
        tail = baru;
    }

    cout << "\nParkiran penuh.\n";
    cout << "Kendaraan masuk ke daftar tunggu.\n";
}


void tambahKendaraan(){
    Kendaraan data;

    cout << "\n===== TAMBAH KENDARAAN =====\n";

    data.nomorPolisi = inputNomorPolisi();

    // Cek nomor polisi agar tidak duplikat
    for (int i = 0; i < jumlahParkir; i++){
        if (parkir[i].nomorPolisi == data.nomorPolisi){
            cout << "Error! Nomor polisi sudah terdaftar di area parkir.\n";
            return;
        }
    }

    Node *temp = head;

    while (temp != nullptr){
        if (temp->data.nomorPolisi == data.nomorPolisi){
            cout << "Error! Nomor polisi sudah terdaftar di daftar tunggu.\n";
            return;
        }

        temp = temp->next;
    }

    data.namaPemilik = inputHuruf("Nama Pemilik     : ");

    data.jenisKendaraan = inputHuruf("Jenis Kendaraan  : ");

    data.jamMasuk = inputJam();

    data.status = inputHuruf("Status Kendaraan : ");

    if (jumlahParkir < MAX_PARKIR){
        parkir[jumlahParkir] = data;
        jumlahParkir++;

        cout << "\nKendaraan berhasil masuk ke area parkir.\n";
    }
    else{
        tambahDaftarTunggu(data);
    }
}


void tampilkanParkir(){
    cout << "\n===== KENDARAAN DI AREA PARKIR =====\n";

    if (jumlahParkir == 0){
        cout << "Area parkir kosong.\n";
        return;
    }

    for (int i = 0; i < jumlahParkir; i++){
        cout << "\nTempat Parkir ke-" << i + 1 << endl;
        cout << "Nomor Polisi     : " << parkir[i].nomorPolisi << endl;
        cout << "Nama Pemilik     : " << parkir[i].namaPemilik << endl;
        cout << "Jenis Kendaraan  : " << parkir[i].jenisKendaraan << endl;
        cout << "Jam Masuk        : " << parkir[i].jamMasuk << endl;
        cout << "Status Kendaraan : " << parkir[i].status << endl;
    }
}


void tampilkanDaftarTunggu(){
    cout << "\n===== DAFTAR TUNGGU =====\n";

    if (head == nullptr){
        cout << "Daftar tunggu kosong.\n";
        return;
    }

    Node *temp = head;
    int nomor = 1;

    while (temp != nullptr){
        cout << "\nKendaraan Tunggu ke-" << nomor << endl;
        cout << "Nomor Polisi     : " << temp->data.nomorPolisi << endl;
        cout << "Nama Pemilik     : " << temp->data.namaPemilik << endl;
        cout << "Jenis Kendaraan  : " << temp->data.jenisKendaraan << endl;
        cout << "Jam Masuk        : " << temp->data.jamMasuk << endl;
        cout << "Status Kendaraan : " << temp->data.status << endl;

        temp = temp->next;
        nomor++;
    }
}

void cariKendaraan(){
    string nomorPolisi;

    cout << "\nMasukkan nomor polisi yang dicari: ";
    cin >> nomorPolisi;

    // Cari di area parkir
    for (int i = 0; i < jumlahParkir; i++){
        if (parkir[i].nomorPolisi == nomorPolisi){
            cout << "\nKendaraan ditemukan di area parkir.\n";
            cout << "Nomor Polisi     : " << parkir[i].nomorPolisi << endl;
            cout << "Nama Pemilik     : " << parkir[i].namaPemilik << endl;
            cout << "Jenis Kendaraan  : " << parkir[i].jenisKendaraan << endl;
            cout << "Jam Masuk        : " << parkir[i].jamMasuk << endl;
            cout << "Status Kendaraan : " << parkir[i].status << endl;

            return;
        }
    }

    // Cari di daftar tunggu
    Node *temp = head;

    while (temp != nullptr){
        if (temp->data.nomorPolisi == nomorPolisi){
            cout << "\nKendaraan ditemukan di daftar tunggu.\n";
            cout << "Nomor Polisi     : " << temp->data.nomorPolisi << endl;
            cout << "Nama Pemilik     : " << temp->data.namaPemilik << endl;
            cout << "Jenis Kendaraan  : " << temp->data.jenisKendaraan << endl;
            cout << "Jam Masuk        : " << temp->data.jamMasuk << endl;
            cout << "Status Kendaraan : " << temp->data.status << endl;

            return;
        }

        temp = temp->next;
    }
    cout << "\nKendaraan tidak ditemukan.\n";
}


void pindahkanDariTunggu(){
    if (jumlahParkir >= MAX_PARKIR){
        cout << "\nArea parkir masih penuh.\n";
        return;
    }

    if (head == nullptr){
        cout << "\nDaftar tunggu kosong.\n";
        return;
    }

    Node *hapus = head;

    parkir[jumlahParkir] = hapus->data;
    jumlahParkir++;

    head = head->next;

    if (head == nullptr){
        tail = nullptr;
    }

    delete hapus;
    cout << "\nKendaraan pertama dari daftar tunggu berhasil masuk ke area parkir.\n";
}


void keluarkanKendaraan(){
    string nomorPolisi;

    cout << "\nMasukkan nomor polisi kendaraan yang keluar: ";
    cin >> nomorPolisi;

    int posisi = -1;

    for (int i = 0; i < jumlahParkir; i++){
        if (parkir[i].nomorPolisi == nomorPolisi){
            posisi = i;
            break;
        }
    }

    if (posisi == -1){
        cout << "Kendaraan tidak ditemukan di area parkir.\n";
        return;
    }

    // Geser data kendaraan
    for (int i = posisi; i < jumlahParkir - 1; i++){
        parkir[i] = parkir[i + 1];
    }
    jumlahParkir--;

    cout << "Kendaraan berhasil keluar dari area parkir.\n";
    // Jika ada daftar tunggu
    if (head != nullptr){
        pindahkanDariTunggu();
    }
}


void hapusKendaraanTunggu(){
    string nomorPolisi;

    cout << "\nMasukkan nomor polisi yang ingin dihapus: ";
    cin >> nomorPolisi;

    Node *temp = head;
    Node *sebelumnya = nullptr;

    while (temp != nullptr){
        if (temp->data.nomorPolisi == nomorPolisi){
            if (sebelumnya == nullptr){
                head = temp->next;
            }
            else{
                sebelumnya->next = temp->next;
            }

            if (temp == tail){
                tail = sebelumnya;
            }

            delete temp;

            cout << "Kendaraan berhasil dihapus dari daftar tunggu.\n";
            return;
        }

        sebelumnya = temp;
        temp = temp->next;
    }

    cout << "Kendaraan tidak ditemukan di daftar tunggu.\n";
}


void tampilkanTempatTersedia(){
    cout << "\n===== INFORMASI TEMPAT PARKIR =====\n";
    cout << "Kapasitas parkir : " << MAX_PARKIR << endl;
    cout << "Terisi           : " << jumlahParkir << endl;
    cout << "Tersedia         : "
         << MAX_PARKIR - jumlahParkir << endl;
}


void hapusSemua(){
    Node *temp;

    while (head != nullptr){
        temp = head;
        head = head->next;

        delete temp;
    }

    tail = nullptr;
}


int main(){
    int pilihan;

    do{
        cout << "\n========================================\n";
        cout << "     SISTEM PARKIR KENDARAAN KAMPUS\n";
        cout << "========================================\n";
        cout << "1. Menambahkan kendaraan\n";
        cout << "2. Menampilkan kendaraan di area parkir\n";
        cout << "3. Menampilkan kendaraan dalam daftar tunggu\n";
        cout << "4. Mencari kendaraan berdasarkan nomor polisi\n";
        cout << "5. Mengeluarkan kendaraan dari area parkir\n";
        cout << "6. Memindahkan kendaraan pertama dari daftar tunggu\n";
        cout << "7. Menghapus kendaraan dari daftar tunggu\n";
        cout << "8. Menampilkan jumlah tempat parkir yang masih tersedia\n";
        cout << "9. Keluar\n";
        cout << "========================================\n";

        pilihan = inputAngka("Pilihan: ");

        switch (pilihan){
            case 1:
                tambahKendaraan();
                break;

            case 2:
                tampilkanParkir();
                break;

            case 3:
                tampilkanDaftarTunggu();
                break;

            case 4:
                cariKendaraan();
                break;

            case 5:
                keluarkanKendaraan();
                break;

            case 6:
                pindahkanDariTunggu();
                break;

            case 7:
                hapusKendaraanTunggu();
                break;

            case 8:
                tampilkanTempatTersedia();
                break;

            case 9:
                cout << "\nProgram selesai.\n";
                break;

            default:
                cout << "\nError! Pilihan hanya 1 sampai 9.\n";
        }
    } while (pilihan != 9);
    
    hapusSemua();
    return 0;
}