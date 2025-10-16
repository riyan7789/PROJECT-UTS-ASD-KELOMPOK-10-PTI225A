#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cctype>
using namespace std;

// Kode warna ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"

// Deklarasi fungsi
void menuUtama();
void kalkulatorIPK();
void kalkulatorWaktu();
void kalkulatorBiaya();
float konversiNilai(float angka);
char hurufMutu(float angka);
string formatRupiah(double nilai);

// Fungsi konversi nilai angka ke IPK
float konversiNilai(float angka) {
    if (angka >= 85) return 4.0;
    else if (angka >= 70) return 3.0;
    else if (angka >= 55) return 2.0;
    else if (angka >= 40) return 1.0;
    else return 0.0;
}

// Fungsi menentukan huruf mutu
char hurufMutu(float angka) {
    if (angka >= 85) return 'A';
    else if (angka >= 70) return 'B';
    else if (angka >= 55) return 'C';
    else if (angka >= 40) return 'D';
    else return 'E';
}

// Fungsi format Rupiah
string formatRupiah(double nilai) {
    stringstream ss;
    ss << fixed << setprecision(0) << nilai;
    string num = ss.str();
    string hasil = "";
    int hitung = 0;
    for (int i = num.length() - 1; i >= 0; i--) {
        hasil.insert(0, 1, num[i]);
        hitung++;
        if (hitung == 3 && i > 0) {
            hasil.insert(0, 1, '.');
            hitung = 0;
        }
    }
    return hasil;
}

// Fungsi utama
int main() {
    cout << CYAN << "\n=====================================================\n";
    cout << "   SELAMAT DATANG DI APLIKASI KALKULATOR MAHASISWA\n";
    cout << "=====================================================\n" << RESET;

    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore();
    cin.get();

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    menuUtama();
    return 0;
}

// Menu utama
void menuUtama() {
    int pilihan;
    do {
        cout << BLUE << "\n==================================================\n";
        cout << "     APLIKASI KALKULATOR MAHASISWA SERBA GUNA\n";
        cout << "==================================================\n" << RESET;
        cout << "1. Kalkulator IPK\n";
        cout << "2. Kalkulator Waktu Belajar & Produktivitas\n";
        cout << "3. Kalkulator Biaya Kuliah & Hidup\n";
        cout << "0. Keluar\n";
        cout << "-------------------------------------------\n";
        cout << "Pilih menu (0-3): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: kalkulatorIPK(); break;
            case 2: kalkulatorWaktu(); break;
            case 3: kalkulatorBiaya(); break;
            case 0: cout << GREEN << "\nTerima Kasih Telah Menggunakan aplikasi!\n" << RESET; break;
            default: cout << RED << "\nPilihan tidak valid. Coba lagi.\n" << RESET;
        }
    } while (pilihan != 0);
}

// Modul Kalkulator IPK
void kalkulatorIPK() {
    cout << MAGENTA << "\n=== KALKULATOR IPK ===\n" << RESET;

    vector<string> namaMK = {
        "Landasan Kependidikan",
        "Matematika Dasar",
        "Fisika Dasar",
        "Pengantar Teknologi Informasi",
        "Algoritma dan Struktur Data",
        "Multimedia Dasar",
        "Agama Islam",
        "Pancasila"
    };
    vector<int> sks = {2, 2, 2, 2, 3, 2, 3, 2};
    vector<float> nilaiAngka(namaMK.size());

    float totalBobot = 0, totalSKS = 0, totalNilai = 0;

    cout << "\nMasukkan nilai angka (0-100) untuk setiap mata kuliah:\n";
    cout << "----------------------------------------------------\n";
    for (size_t i = 0; i < namaMK.size(); i++) {
        cout << setw(2) << i + 1 << ". " << setw(35) << left << namaMK[i]
             << " (" << sks[i] << " SKS): ";
        cin >> nilaiAngka[i];
        totalBobot += konversiNilai(nilaiAngka[i]) * sks[i];
        totalSKS += sks[i];
        totalNilai += nilaiAngka[i];
    }

    float ipk = totalBobot / totalSKS;
    float rataNilai = totalNilai / namaMK.size();

    cout << YELLOW << "\n========================================\n";
    cout << setw(30) << left << "Nama Mata Kuliah"
         << setw(8) << "SKS"
         << setw(12) << "Nilai"
         << setw(12) << "Huruf Mutu\n";
    cout << "----------------------------------------\n";

    for (size_t i = 0; i < namaMK.size(); i++) {
        cout << setw(30) << left << namaMK[i]
             << setw(8) << sks[i]
             << setw(12) << nilaiAngka[i]
             << setw(12) << hurufMutu(nilaiAngka[i]) << endl;
    }

    cout << "----------------------------------------\n";
    cout << "Total SKS        : " << totalSKS << endl;
    cout << "Jumlah Nilai     : " << fixed << setprecision(2) << totalNilai << endl;
    cout << "Rata-rata Nilai  : " << fixed << setprecision(2) << rataNilai << endl;
    cout << "IPK Anda         : " << fixed << setprecision(2) << ipk;

    if (ipk >= 3.5) cout << GREEN << " (Cumlaude)\n" << RESET;
    else if (ipk >= 3.0) cout << CYAN << " (Baik)\n" << RESET;
    else if (ipk >= 2.0) cout << YELLOW << " (Cukup)\n" << RESET;
    else cout << RED << " (Kurang)\n" << RESET;

    cout << "========================================\n";

    cout << GREEN << "\nTerima Kasih Telah Menggunakan Kalkulator IPK!" << RESET << endl;

    char kembali;
    cout << "\nKlik 0 untuk kembali ke menu utama : ";
    cin >> kembali;
    if (kembali == '0') {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        menuUtama();
    }
}

// Modul Kalkulator Waktu
void kalkulatorWaktu() {
    cout << CYAN << "\n=== KALKULATOR WAKTU BELAJAR & PRODUKTIVITAS ===\n" << RESET;
    float jamKuliah, jamBelajar, jamTidur, jamLain;
    cout << "Masukkan jam kuliah per hari: ";
    cin >> jamKuliah;
    cout << "Masukkan jam belajar mandiri: ";
    cin >> jamBelajar;
    cout << "Masukkan jam tidur: ";
    cin >> jamTidur;
    cout << "Masukkan jam kegiatan lain: ";
    cin >> jamLain;

    float totalTerpakai = jamKuliah + jamBelajar + jamTidur + jamLain;
    float sisa = 24 - totalTerpakai;

    cout << "\nTotal waktu terpakai: " << totalTerpakai << " jam";
    cout << "\nSisa waktu: " << sisa << " jam";

    if (sisa >= 0 && sisa <= 3)
        cout << GREEN << "\nRekomendasi: Waktu produktif cukup, pertahankan!\n" << RESET;
    else if (sisa < 0)
        cout << RED << "\nRekomendasi: Kurangi kegiatan lain, waktu melebihi 24 jam!\n" << RESET;
    else
        cout << YELLOW << "\nRekomendasi: Masih ada waktu luang, bisa digunakan untuk belajar atau istirahat.\n" << RESET;

    cout << GREEN << "\nTerima Kasih Telah Menggunakan Kalkulator Waktu!" << RESET << endl;

    char kembali;
    cout << "\nKlik 0 untuk kembali ke menu utama: ";
    cin >> kembali;
    if (kembali == '0') {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        menuUtama();
    }
}

// Modul Kalkulator Biaya
void kalkulatorBiaya() {
    cout << MAGENTA << "\n=== KALKULATOR BIAYA KULIAH & HIDUP ===\n" << RESET;
    double kuliah, kos, makan, transport, buku, lain, dana;

    cout << "Masukkan biaya kuliah per semester: Rp ";
    cin >> kuliah;
    cout << "Masukkan biaya kos per bulan: Rp ";
    cin >> kos;
    cout << "Masukkan biaya makan per bulan: Rp ";
    cin >> makan;
    cout << "Masukkan biaya transport per bulan: Rp ";
    cin >> transport;
    cout << "Masukkan biaya buku per bulan: Rp ";
    cin >> buku;
    cout << "Masukkan pengeluaran lain per bulan: Rp ";
    cin >> lain;

    double totalBulanan = kos + makan + transport + buku + lain;
    double totalSemester = kuliah + (totalBulanan * 6);
    double totalTahunan = totalSemester * 2;

    cout << "\n---------------------------------------------";
    cout << "\nTotal biaya bulanan       : Rp " << formatRupiah(totalBulanan);
    cout << "\nTotal biaya per semester  : Rp " << formatRupiah(totalSemester);
    cout << "\nTotal biaya per tahun     : Rp " << formatRupiah(totalTahunan);
    cout << "\n---------------------------------------------";

    cout << "\nMasukkan total dana tersedia per semester: Rp ";
    cin >> dana;

    if (dana > 0) {
        double sisa = dana - totalSemester;
        if (sisa > 0)
            cout << GREEN << "\nDana mencukupi. Sisa uang: Rp " << formatRupiah(sisa) << endl << RESET;
        else
            cout << RED << "\nDana kurang sebesar: Rp " << formatRupiah(-sisa) << endl << RESET;
    }

    cout << GREEN << "\nTerima Kasih Telah Menggunakan Kalkulator Biaya!" << RESET << endl;

    char kembali;
    cout << "\nKlik 0 untuk kembali ke menu utama: ";
    cin >> kembali;
    if (kembali == '0') {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        menuUtama();
    }
}
