#include <iostream>
#include <string>

using namespace std;

const int MAX_PESERTA = 5;

struct Peserta{
    string nim;
    string nama;
    string prodi;
    int semester;
    double ipk;
};

struct Node{
    Peserta data;
    Node *next;
};

Peserta pesertaUtama[MAX_PESERTA];
int jumlahUtama = 0;

Node *head = nullptr;
Node *tail = nullptr;

void tambahDaftarTunggu(Peserta data){
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

    cout << "Peserta masuk ke daftar tunggu.\n";
}

string inputData(string pesan, string tipe)
{
    string input;

    while (true){
        cout << pesan;

        if (tipe == "angka"){
            cin >> input;
        }
        else{
            cin.ignore();
            getline(cin, input);
        }

        bool valid = true;

        // Input angka
        if (tipe == "angka" || tipe == "nim"){
            for (char c : input){
                if (!isdigit(c)){
                    valid = false;
                    break;
                }
            }
            if (input.empty()){
                valid = false;
            }
        }

        // Input huruf
        else if (tipe == "huruf"){
            if (input.empty()){
                valid = false;
            }
            for (char c : input){
                if (!isalpha(c) && c != ' '){
                    valid = false;
                    break;
                }
            }
        }

        // input desimal
        else if (tipe == "desimal"){
            int titik = 0;
            if (input.empty()){
                valid = false;
            }

            for (char c : input){
                if (c == '.'){
                    titik++;

                    if (titik > 1){
                        valid = false;
                        break;
                    }
                }
                else if (!isdigit(c)){
                    valid = false;
                    break;
                }
            }
        }

        if (valid){
            return input;
        }

        cout << "Error! Input tidak sesuai.\n";
    }
}

void tambahPeserta(){
    Peserta data;

    cout << "\n===== TAMBAH PESERTA =====\n";

    data.nim = inputData("NIM           : ", "nim");

    // Cek NIM peserta utama
    for (int i = 0; i < jumlahUtama; i++){
        if (pesertaUtama[i].nim == data.nim){
            cout << "Error! NIM sudah terdaftar.\n";
            return;
        }
    }

    // Cek NIM daftar tunggu
    Node *temp = head;

    while (temp != nullptr){
        if (temp->data.nim == data.nim){
            cout << "Error! NIM sudah terdaftar di daftar tunggu.\n";
            return;
        }

        temp = temp->next;
    }

    data.nama = inputData("Nama          : ", "huruf");

    data.prodi = inputData("Program Studi : ", "huruf");

    string semester = inputData("Semester      : ", "angka");
    data.semester = stoi(semester);

    while (data.semester < 1){
        cout << "Error! Semester harus lebih dari 0.\n";
        semester = inputData("Semester      : ", "angka");
        data.semester = stoi(semester);
    }

    string ipk = inputData("IPK           : ", "desimal");
    data.ipk = stod(ipk);

    while (data.ipk < 0.00 || data.ipk > 4.00){
        cout << "Error! IPK harus berada antara 0.00 sampai 4.00.\n";
        ipk = inputData("IPK           : ", "desimal");
        data.ipk = stod(ipk);
    }

    if (jumlahUtama < MAX_PESERTA){
        pesertaUtama[jumlahUtama] = data;
        jumlahUtama++;

        cout << "\nPeserta berhasil masuk ke peserta utama.\n";
    }
    else{
        tambahDaftarTunggu(data);
    }
}

void tampilkanPesertaUtama(){
    cout << "\n===== PESERTA UTAMA =====\n";

    if (jumlahUtama == 0){
        cout << "Belum ada peserta utama.\n";
        return;
    }

    for (int i = 0; i < jumlahUtama; i++){
        cout << "\nPeserta ke-" << i + 1 << endl;
        cout << "NIM           : " << pesertaUtama[i].nim << endl;
        cout << "Nama          : " << pesertaUtama[i].nama << endl;
        cout << "Program Studi : " << pesertaUtama[i].prodi << endl;
        cout << "Semester      : " << pesertaUtama[i].semester << endl;
        cout << "IPK           : " << pesertaUtama[i].ipk << endl;
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
        cout << "\nPeserta tunggu ke-" << nomor << endl;
        cout << "NIM           : " << temp->data.nim << endl;
        cout << "Nama          : " << temp->data.nama << endl;
        cout << "Program Studi : " << temp->data.prodi << endl;
        cout << "Semester      : " << temp->data.semester << endl;
        cout << "IPK           : " << temp->data.ipk << endl;

        temp = temp->next;
        nomor++;
    }
}

void cariPeserta(){
    string nim;

    cout << "\nMasukkan NIM yang dicari: ";
    cin >> nim;

    // Cari di peserta utama
    for (int i = 0; i < jumlahUtama; i++){
        if (pesertaUtama[i].nim == nim){
            cout << "\nPeserta ditemukan di peserta utama.\n";
            cout << "NIM           : " << pesertaUtama[i].nim << endl;
            cout << "Nama          : " << pesertaUtama[i].nama << endl;
            cout << "Program Studi : " << pesertaUtama[i].prodi << endl;
            cout << "Semester      : " << pesertaUtama[i].semester << endl;
            cout << "IPK           : " << pesertaUtama[i].ipk << endl;
            return;
        }
    }

    // Cari di daftar tunggu
    Node *temp = head;

    while (temp != nullptr){
        if (temp->data.nim == nim){
            cout << "\nPeserta ditemukan di daftar tunggu.\n";
            cout << "NIM           : " << temp->data.nim << endl;
            cout << "Nama          : " << temp->data.nama << endl;
            cout << "Program Studi : " << temp->data.prodi << endl;
            cout << "Semester      : " << temp->data.semester << endl;
            cout << "IPK           : " << temp->data.ipk << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "\nPeserta tidak ditemukan.\n";
}



void pindahkanDariTunggu(){
    if (jumlahUtama >= MAX_PESERTA){
        cout << "\nPeserta utama masih penuh.\n";
        return;
    }

    if (head == nullptr){
        cout << "\nDaftar tunggu kosong.\n";
        return;
    }

    Node *hapus = head;

    pesertaUtama[jumlahUtama] = hapus->data;
    jumlahUtama++;

    head = head->next;

    if (head == nullptr){
        tail = nullptr;
    }

    delete hapus;
    cout << "\nPeserta pertama dari daftar tunggu berhasil dipindahkan.\n";
}


void hapusPesertaUtama(){
    string nim;

    cout << "\nMasukkan NIM peserta yang dibatalkan: ";
    cin >> nim;

    int posisi = -1;

    for (int i = 0; i < jumlahUtama; i++){
        if (pesertaUtama[i].nim == nim){
            posisi = i;
            break;
        }
    }

    if (posisi == -1){
        cout << "Peserta utama tidak ditemukan.\n";
        return;
    }

    // Geser data setelah data yang dihapus
    for (int i = posisi; i < jumlahUtama - 1; i++){
        pesertaUtama[i] = pesertaUtama[i + 1];
    }

    jumlahUtama--;

    cout << "Peserta berhasil dibatalkan.\n";

    // Jika ada daftar tunggu, langsung pindahkan
    if (head != nullptr){
        pindahkanDariTunggu();
    }
}


void hapusPesertaTunggu(){
    string nim;

    cout << "\nMasukkan NIM peserta yang ingin dihapus dari daftar tunggu: ";
    cin >> nim;

    Node *temp = head;
    Node *sebelumnya = nullptr;

    while (temp != nullptr){
        if (temp->data.nim == nim){
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
            cout << "Peserta berhasil dihapus dari daftar tunggu.\n";
            return;
        }
        sebelumnya = temp;
        temp = temp->next;
    }
    cout << "Peserta tidak ditemukan di daftar tunggu.\n";
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
    string pilihanInput;
    int pilihan;

    do{
        cout << "\n========================================\n";
        cout << " SISTEM PENDAFTARAN PESERTA WORKSHOP\n";
        cout << "========================================\n";
        cout << "1. Menambahkan peserta\n";
        cout << "2. Menampilkan peserta utama\n";
        cout << "3. Menampilkan daftar tunggu\n";
        cout << "4. Mencari peserta berdasarkan NIM\n";
        cout << "5. Menghapus atau membatalkan peserta utama\n";
        cout << "6. Memindahkan peserta pertama dari daftar tunggu\n";
        cout << "7. Menghapus peserta dari daftar tunggu\n";
        cout << "8. Keluar\n";
        cout << "========================================\n";

        pilihanInput = inputData("Pilihan: ", "angka");
        pilihan = stoi(pilihanInput);



        switch (pilihan){
            case 1:
                tambahPeserta();
                break;

            case 2:
                tampilkanPesertaUtama();
                break;

            case 3:
                tampilkanDaftarTunggu();
                break;

            case 4:
                cariPeserta();
                break;

            case 5:
                hapusPesertaUtama();
                break;

            case 6:
                pindahkanDariTunggu();
                break;

            case 7:
                hapusPesertaTunggu();
                break;

            case 8:
                cout << "\nProgram selesai.\n";
                break;

            default:
                cout << "\nPilihan tidak tersedia.\n";
        }

    } while (pilihan != 8);
}