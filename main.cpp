#include "univ.h"
#include <iostream>
#include <climits>
using namespace std;

int main() {
    University* univHead = nullptr;
    Faculty* facHead = nullptr;

    int pilihan;
    do {
        cout << "\n=== MENU DATA PERGURUAN TINGGI ===\n";
        cout << "1. Insert Universitas (First)\n";
        cout << "2. Insert Universitas (Last)\n";
        cout << "3. Insert Fakultas (First)\n";
        cout << "4. Insert Fakultas (Last)\n";
        cout << "5. Hubungkan Universitas ke Fakultas\n";
        cout << "6. Tampilkan semua Universitas\n";
        cout << "7. Tampilkan semua Fakultas\n";
        cout << "8. Hapus Universitas tertentu\n";
        cout << "9. Hapus Fakultas tertentu\n";
        cout << "10. Cari Universitas\n";
        cout << "11. Cari Fakultas\n";
        cout << "12. Tampilkan Universitas dengan fakultas terbanyak/tersedikit\n";
        cout << "13. Cari Fakultas pada Universitas tertentu\n";
        cout << "14. Hapus Fakultas pada Universitas tertentu\n";
        cout << "15. Hitung jumlah Fakultas dari Universitas tertentu\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            string nama; int tahun, jml;
            cout << "Nama Universitas: "; cin >> nama;
            cout << "Tahun berdiri: "; cin >> tahun;
            cout << "Jumlah mahasiswa: "; cin >> jml;
            insertFirstUniv(univHead, nama, tahun, jml);
        }
        else if (pilihan == 2) {
            string nama; int tahun, jml;
            cout << "Nama Universitas: "; cin >> nama;
            cout << "Tahun berdiri: "; cin >> tahun;
            cout << "Jumlah mahasiswa: "; cin >> jml;
            insertLastUniv(univHead, nama, tahun, jml);
        }
        else if (pilihan == 3) {
            string nama; int dosen, mhs;
            cout << "Nama Fakultas: "; cin >> nama;
            cout << "Jumlah dosen: "; cin >> dosen;
            cout << "Jumlah mahasiswa: "; cin >> mhs;
            insertFirstFac(facHead, nama, dosen, mhs);
        }
        else if (pilihan == 4) {
            string nama; int dosen, mhs;
            cout << "Nama Fakultas: "; cin >> nama;
            cout << "Jumlah dosen: "; cin >> dosen;
            cout << "Jumlah mahasiswa: "; cin >> mhs;
            insertLastFac(facHead, nama, dosen, mhs);
        }
        else if (pilihan == 5) {
            string univName, facName;
            cout << "Nama Universitas: "; cin >> univName;
            cout << "Nama Fakultas: "; cin >> facName;
            University* u = findUniversity(univHead, univName);
            Faculty* f = findFaculty(facHead, facName);
            if (u && f) addRelation(u, f);
            else cout << "Universitas atau Fakultas tidak ditemukan!\n";
        }
        else if (pilihan == 6) {
            showAllUniversities(univHead);
        }
        else if (pilihan == 7) {
            showFacultyList(facHead);
        }
        else if (pilihan == 8) {
            string nama;
            cout << "Nama Universitas yang dihapus: "; cin >> nama;
            deleteUniv(univHead, nama);
        }
        else if (pilihan == 9) {
            string nama;
            cout << "Nama Fakultas yang dihapus: "; cin >> nama;
            deleteFac(facHead, nama);
        }
        else if (pilihan == 10) {
            string nama;
            cout << "Cari Universitas: "; cin >> nama;
            University* u = findUniversity(univHead, nama);
            if (u) cout << "Universitas ditemukan: " << u->nama << endl;
            else cout << "Universitas tidak ditemukan.\n";
        }
        else if (pilihan == 11) {
            string nama;
            cout << "Cari Fakultas: "; cin >> nama;
            Faculty* f = findFaculty(facHead, nama);
            if (f) cout << "Fakultas ditemukan: " << f->nama << endl;
            else cout << "Fakultas tidak ditemukan.\n";
        }
        else if (pilihan == 12) {
            showUniversityWithMostAndLeastFaculties(univHead);
        }
        else if (pilihan == 13) {
            string univName, facName;
            cout << "Nama Universitas: "; cin >> univName;
            cout << "Nama Fakultas: "; cin >> facName;
            University* u = findUniversity(univHead, univName);
            if (u) showChildOfParent(u, facName);
            else cout << "Universitas tidak ditemukan.\n";
        }
        else if (pilihan == 14) {
            string univName, facName;
            cout << "Nama Universitas: "; cin >> univName;
            cout << "Nama Fakultas: "; cin >> facName;
            University* u = findUniversity(univHead, univName);
            if (u) deleteChildOfParent(u, facName);
            else cout << "Universitas tidak ditemukan.\n";
        }
        else if (pilihan == 15) {
            string univName;
            cout << "Nama Universitas: "; cin >> univName;
            University* u = findUniversity(univHead, univName);
            if (u) cout << "Jumlah fakultas: " << countChildOfParent(u) << endl;
            else cout << "Universitas tidak ditemukan.\n";
        }

    } while (pilihan != 0);

    cout << "Program selesai.\n";
    return 0;
}