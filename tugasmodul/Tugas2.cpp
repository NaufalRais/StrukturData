#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

struct Mahasiswa{
    string nim;
    string nama;
    float ipk;
};

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

int cariMahasiswa(Mahasiswa *data, int jumlah, string nim){
    for (int i = 0; i < jumlah; i++){
        if (data[i].nim == nim){
            return i;
        }
    }

    return -1;
}

void tampilkanData(Mahasiswa *data, int jumlah){
    if (jumlah == 0){
        cout << "Data mahasiswa masih kosong" << endl;
        return;
    }

    cout << "\n===== DATA MAHASISWA =====" << endl;

    for (int i = 0; i < jumlah; i++){
        cout << "Mahasiswa ke-" << i + 1 << endl;
        cout << "NIM  : " << data[i].nim << endl;
        cout << "Nama : " << data[i].nama << endl;
        cout << "IPK  : " << fixed << setprecision(2) << data[i].ipk << endl;
        cout << "--------------------------" << endl;
    }
}

void tambahMahasiswa(Mahasiswa *data, int i){
    string nim;
    string nama;
    string ipk;

    cout << "NIM  : ";
    cin >> nim;

    cin.ignore();

    cout << "Nama : ";
    getline(cin, nama);

    cout << "IPK (ex:3.6) : ";
    cin >> ipk;

    if (!validasiData(nim, nama, ipk)){
        cout << "Data tidak valid." << endl;
        return;
    }

    data[i].nim = nim;
    data[i].nama = nama;
    data[i].ipk = stof(ipk);

    cout << "Data berhasil ditambahkan." << endl;
}

void cariData(Mahasiswa *data, int jumlah){
    string nim;

    cout << "\nMasukkan NIM yang dicari: ";
    cin >> nim;

    int index = cariMahasiswa(data, jumlah, nim);

    if (index == -1){
        cout << "Mahasiswa tidak ditemukan" << endl;
    }
    else{
        cout << "\nMahasiswa ditemukan pada indeks " << index << endl;

        cout << "NIM  : " << data[index].nim << endl;
        cout << "Nama : " << data[index].nama << endl;
        cout << "IPK  : " << fixed << setprecision(2) << data[index].ipk << endl;
    }
}

int main(){
    int jumlah;
    system("cls");
    cout << "NAUFAL RAIS RYANUR\n";
    cout << "1232502228\n\n";

    cout << "=================================" << endl;
    cout << "   ARRAY DINAMIS MAHASISWA" << endl;
    cout << "=================================" << endl;

    do{
        cout << "Masukkan jumlah mahasiswa: ";
        cin >> jumlah;

        if (jumlah <= 0){
            cout << "Jumlah mahasiswa harus lebih dari 0" << endl;
        }

    } while (jumlah <= 0);

    Mahasiswa *data = new Mahasiswa[jumlah];

    int pilihan;
    char ulang;

    do{
        system("cls");
        cout << "NAUFAL RAIS RYANUR\n";
        cout << "1232502228\n\n";

        cout << "========== MENU ==========" << endl;
        cout << "1. Tampilkan seluruh data" << endl;
        cout << "2. Cari mahasiswa berdasarkan NIM" << endl;
        cout << "3. Tampilkan jumlah mahasiswa" << endl;
        cout << "4. Keluar" << endl;
        cout << "==========================" << endl;

        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan){
        case 1:
            tampilkanData(data, jumlah);
            break;

        case 2:
            cariData(data, jumlah);
            break;

        case 3:
            cout << "Jumlah mahasiswa: " << jumlah << endl;
            break;

        case 4:
            cout << "Program selesai" << endl;
            break;

        default:
            cout << "Pilihan menu tidak valid" << endl;
        }
        if (pilihan != 4){
            cout << "\nApakah anda ingin mengulang? (y/n): ";
            cin >> ulang;
        }
    } while (pilihan != 4 && ulang != 'n');

    delete[] data;
    return 0;
}