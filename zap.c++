#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

// Deklarasi fungsi
void menuUtama();
void kalkulatorIPK();
void kalkulatorWaktu();
void kalkulatorBiaya();
float konversiNilai(char nilai);
string formatRupiah(double nilai);

// Fungsi konversi nilai huruf ke angka
float konversiNilai(char nilai) {
    switch (toupper(nilai)) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        case 'E': return 0.0;
        default: return 0.0;
    }
}

// Fungsi format angka jadi Rupiah (misal 1500000 → 1.500.000)
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
    menuUtama();
    return 0;
}

// Fungsi menu utama
void menuUtama() {
    int pilihan;
    do {
        cout << "\n===========================================\n";
        cout << "     APLIKASI MAHASISWA SERBA GUNA\n";
        cout << "===========================================\n";
        cout << "1. Kalkulator IPK\n";
        cout << "2. Kalkulator Waktu Belajar & Produktivitas\n";
        cout << "3. Kalkulator Biaya Kuliah & Hidup\n";
        cout << "4. Keluar\n";
        cout << "-------------------------------------------\n";
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: kalkulatorIPK(); break;
            case 2: kalkulatorWaktu(); break;
            case 3: kalkulatorBiaya(); break;
            case 4: cout << "\nTerima kasih telah menggunakan aplikasi!\n"; break;
            default: cout << "\nPilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 4);
}

// Modul Kalkulator IPK
void kalkulatorIPK() {
    int jumlahMK;
    cout << "\n=== KALKULATOR IPK ===\n";
    cout << "Masukkan jumlah mata kuliah: ";
    cin >> jumlahMK;

    vector<int> sks(jumlahMK);
    vector<char> nilaiHuruf(jumlahMK);
    float totalBobot = 0, totalSKS = 0;

    for (int i = 0; i < jumlahMK; i++) {
        cout << "\nMata Kuliah ke-" << i + 1 << ":\n";
        cout << "SKS: ";
        cin >> sks[i];
        cout << "Nilai huruf (A/B/C/D/E): ";
        cin >> nilaiHuruf[i];

        totalBobot += konversiNilai(nilaiHuruf[i]) * sks[i];
        totalSKS += sks[i];
    }

    float ipk = totalBobot / totalSKS;
    cout << "\nTotal SKS: " << totalSKS;
    cout << "\nIPK Anda: " << fixed << setprecision(2) << ipk;

    if (ipk >= 3.5) cout << " (Cumlaude)";
    else if (ipk >= 3.0) cout << " (Baik)";
    else if (ipk >= 2.0) cout << " (Cukup)";
    else cout << " (Kurang)";

    cout << "\n=========================\n";

    char kembali;
    cout << "\nKembali ke menu utama? (y/n): ";
    cin >> kembali;
    if (tolower(kembali) == 'y') menuUtama();
    else cout << "\nTerima kasih!\n";
}

// Modul Kalkulator Waktu Belajar & Produktivitas
void kalkulatorWaktu() {
    cout << "\n=== KALKULATOR WAKTU BELAJAR & PRODUKTIVITAS ===\n";
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
        cout << "\nRekomendasi: Waktu produktif cukup, pertahankan!";
    else if (sisa < 0)
        cout << "\nRekomendasi: Kurangi kegiatan lain, waktu melebihi 24 jam!";
    else
        cout << "\nRekomendasi: Masih ada waktu luang, bisa digunakan untuk belajar atau istirahat.";

    cout << "\n=========================================\n";

    char kembali;
    cout << "\nKembali ke menu utama? (y/n): ";
    cin >> kembali;
    if (tolower(kembali) == 'y') menuUtama();
    else cout << "\nTerima kasih!\n";
}

// Modul Kalkulator Biaya Kuliah & Hidup
void kalkulatorBiaya() {
    cout << "\n=== KALKULATOR BIAYA KULIAH & HIDUP ===\n";
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
    cout << "Masukkan pengeluaran lain per bulan (0 jika tidak ada): Rp ";
    cin >> lain;

    double totalBulanan = kos + makan + transport + buku + lain;
    double totalSemester = kuliah + (totalBulanan * 6); // 6 bulan per semester
    double totalTahunan = totalSemester * 2; // 2 semester dalam setahun

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
            cout << "\n Dana mencukupi. Sisa uang: Rp " << formatRupiah(sisa);
        else
            cout << "\n Dana kurang sebesar: Rp " << formatRupiah(-sisa);
    }

    cout << "\n============================================\n";

    char kembali;
    cout << "\nKembali ke menu utama? (y/n): ";
    cin >> kembali;
    if (tolower(kembali) == 'y') menuUtama();
    else cout << "\nTerima kasih!\n";
}
