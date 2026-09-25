#include <iostream>
#include <iomanip>
#include <string>
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

void tampilkanData(Mahasiswa data[], int jumlah){
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

int cariMahasiswa(Mahasiswa data[], int jumlah, string nim){
    for (int i = 0; i < jumlah; i++){
        if (data[i].nim == nim){
            return i;
        }
    }
    return -1;
}

void tambahMahasiswa(Mahasiswa data[], int &jumlah, int kapasitas){
    if (jumlah >= kapasitas){
        cout << "Array sudah penuh" << endl;
        return;
    }

    string nim;
    string nama;
    string ipk;

    cout << "\nMasukkan NIM  : ";
    cin >> nim;

    cin.ignore();

    cout << "Masukkan Nama : ";
    getline(cin, nama);

    cout << "\nex : 3.8\n";
    cout << "Masukkan IPK  : ";
    cin >> ipk;

    if (!validasiData(nim, nama, ipk)){
        cout << "Data tidak valid." << endl;
        return;
    }

    for (int i = 0; i < jumlah; i++){
        if (data[i].nim == nim){
            cout << "NIM sudah terdaftar" << endl;
            return;
        }
    }

    data[jumlah].nim = nim;
    data[jumlah].nama = nama;
    data[jumlah].ipk = stof(ipk);

    jumlah++;

    cout << "Mahasiswa berhasil ditambahkan" << endl;
}

void cariData(Mahasiswa data[], int jumlah){
    string nim;

    cout << "Masukkan NIM yang dicari: ";
    cin >> nim;

    int index = cariMahasiswa(data, jumlah, nim);

    if (index == -1){
        cout << "Mahasiswa tidak ditemukan" << endl;
    }
    else{
        cout << "\nMahasiswa ditemukan." << endl;
        cout << "NIM  : " << data[index].nim << endl;
        cout << "Nama : " << data[index].nama << endl;
        cout << "IPK  : " << fixed << setprecision(2) << data[index].ipk << endl;
        cout <<"Gunakan titik, ex: 3.7)" << endl;
    }
}

void ubahIPK(Mahasiswa data[], int jumlah){
    string nim;
    float ipkBaru;

    cout << "Masukkan NIM: ";
    cin >> nim;

    int index = cariMahasiswa(data, jumlah, nim);

    if (index == -1){
        cout << "Mahasiswa tidak ditemukan" << endl;
        return;
    }

    cout << "IPK lama: " << fixed << setprecision(2) << data[index].ipk << endl;

    cout << "Masukkan IPK baru (gunakan titik, ex: 3.7): ";
    cin >> ipkBaru;

    if (ipkBaru < 0.00 || ipkBaru > 4.00){
        cout << "IPK harus berada di antara 0.00 sampai 4.00" << endl;
        return;
    }

    data[index].ipk = ipkBaru;

    cout << "IPK berhasil diubah" << endl;
}

int main(){   

    int maxDATA;
    do{
    system("cls");
    cout << "NAUFAL RAIS RYANUR\n";
    cout << "1232502228\n\n";

    cout << "=================================" << endl;
    cout << "    PROGRAM DATA MAHASISWA" << endl;
    cout << "=================================" << endl;

        cout << "Masukkan jumlah data mahasiswa: ";
        cin >> maxDATA;

        if (maxDATA <= 0)
        {
            cout << "Jumlah data harus lebih dari 0" << endl;
        }

    } while (maxDATA <= 0);

    int maxData = 100;
    Mahasiswa data[maxData];

    int jumlah = 0;
    int pilihan;
    string ulang;

        do{
            system("cls");
            cout << "\nNAUFAL RAIS RYANUR\n";
            cout << "1232502228\n\n";

            cout << "\n========== MENU ==========" << endl;
            cout << "1. Tambah mahasiswa" << endl;
            cout << "2. Tampilkan seluruh data" << endl;
            cout << "3. Cari mahasiswa berdasarkan NIM" << endl;
            cout << "4. Ubah IPK" << endl;
            cout << "5. Tampilkan jumlah mahasiswa" << endl;
            cout << "6. Keluar" << endl;
            cout << "===========================" << endl;

            cout << "Pilihan: ";
            cin >> pilihan;

            switch (pilihan){
            case 1:
                tambahMahasiswa(data, jumlah, maxDATA);
                cout << "Apakah ingin mengulang program? (y/n): ";
                cin >> ulang;
                break;

            case 2:
                tampilkanData(data, jumlah);
                cout << "Apakah ingin mengulang program? (y/n): ";
                cin >> ulang;
                break;

            case 3:
                cariData(data, jumlah);
                cout << "Apakah ingin mengulang program? (y/n): ";
                cin >> ulang;
                break;

            case 4:
                ubahIPK(data, jumlah);
                cout << "Apakah ingin mengulang program? (y/n): ";
                cin >> ulang;
                break;

            case 5:
                cout << "Jumlah mahasiswa: "<< jumlah << endl;
                cout << "Apakah ingin mengulang program? (y/n): ";
                cin >> ulang;
                break;

            case 6:
                cout << "Program selesai" << endl;
                cout << "Terimakasih" << endl;
                break;
            default:
                cout << "Pilihan menu tidak valid" << endl;
                cout << "Apakah ingin mengulang program? (y/n): ";
                cin >> ulang;
            }
        } while (pilihan != 6 && ulang != "n");
    return 0;
}