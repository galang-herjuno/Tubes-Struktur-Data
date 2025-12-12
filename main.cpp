#include "Univ.h"

using namespace std;

// Fungsi utama
int main() {
    // Inisialisasi head untuk list University dan Faculty
    University* univHead = nullptr;
    Faculty* facHead = nullptr;

    // --- 1. MEMBUAT ENTITAS BARU (University dan Faculty) ---

    cout << "--- 1. INISIALISASI UNIVERSITAS DAN FAKULTAS ---" << endl;

    // Membuat University
    University* u1 = createUniv("ITB");
    University* u2 = createUniv("UGM");
    University* u3 = createUniv("UI");
    
    // Menghubungkan University ke list utama (manual Prepend)
    u1->next = univHead; univHead = u1;
    u2->next = univHead; univHead = u2;
    u3->next = univHead; univHead = u3;
    
    // Membuat Faculty
    Faculty* f1 = createFac("Teknik");
    Faculty* f2 = createFac("Ekonomi");
    Faculty* f3 = createFac("Kedokteran");
    Faculty* f4 = createFac("Sains");

    // Menghubungkan Faculty ke list utama (manual Prepend)
    f1->next = facHead; facHead = f1;
    f2->next = facHead; facHead = f2;
    f3->next = facHead; facHead = f3;
    f4->next = facHead; facHead = f4;

    showAllUniversities(univHead);
    showFacultyList(facHead);
    cout << "------------------------------------------------" << endl << endl;

    // --- 2. MENAMBAH RELASI (ASSOCIATION) ---
    
    cout << "--- 2. MENAMBAH RELASI ANTAR ENTITAS ---" << endl;
    
    // ITB memiliki Teknik, Sains
    addRelation(u1, f1); 
    addRelation(u1, f4);

    // UGM memiliki Teknik, Ekonomi, Kedokteran
    addRelation(u2, f1);
    addRelation(u2, f2);
    addRelation(u2, f3);

    // UI memiliki Ekonomi, Kedokteran, Sains
    addRelation(u3, f2);
    addRelation(u3, f3);
    addRelation(u3, f4);
    
    cout << "Relasi berhasil dibuat." << endl;
    cout << "------------------------------------------------" << endl << endl;

    // --- 3. MENAMPILKAN RELASI DARI KEDUA SISI ---
    
    cout << "--- 3. MENAMPILKAN DATA BERELASI ---" << endl;
    
    // a. Tampilkan semua Fakultas di ITB
    showFacultiesOfUniversity(u1); 
    cout << endl;

    // b. Tampilkan semua University yang memiliki Fakultas Kedokteran
    showUniversitiesWithFaculty(f3); 
    cout << endl;
    
    // c. Tampilkan yang paling banyak dan sedikit Fakultas
    showUniversityWithMostAndLeastFaculties(univHead);
    cout << "------------------------------------------------" << endl << endl;

    // --- 4. MENGHAPUS RELASI ---
    
    cout << "--- 4. MENGHAPUS RELASI (ITB tidak lagi memiliki Sains) ---" << endl;
    
    if (removeRelation(u1, f4)) {
        cout << "Relasi (ITB - Sains) berhasil dihapus." << endl;
    } else {
        cout << "Gagal menghapus relasi." << endl;
    }
    cout << endl;

    // Verifikasi setelah penghapusan relasi
    showFacultiesOfUniversity(u1);
    cout << endl;
    
    // Verifikasi Fakultas Sains
    showUniversitiesWithFaculty(f4);
    cout << "------------------------------------------------" << endl << endl;
    
    // --- 5. PENCARIAN ENTITAS ---
    
    cout << "--- 5. PENCARIAN ENTITAS ---" << endl;
    
    University* foundUniv = findUniversity(univHead, "UGM");
    if (foundUniv) {
        cout << "Ditemukan University: " << foundUniv->nama << endl;
    }
    
    Faculty* foundFac = findFaculty(facHead, "Teknik");
    if (foundFac) {
        cout << "Ditemukan Faculty: " << foundFac->nama << endl;
    }
    cout << "------------------------------------------------" << endl << endl;
    
    // --- 6. MENGHAPUS ENTITAS (Contoh) ---
    
    cout << "--- 6. MENGHAPUS ENTITAS (UGM) ---" << endl;
    // PENTING: Sebelum memanggil deleteUniv untuk UGM, 
    // semua relasinya HARUS dihapus terlebih dahulu!
    
    // Hapus semua relasi UGM secara manual (simulasi)
    // Walaupun u2 (UGM) memiliki head, kita perlu traverse dan panggil removeRelation
    removeRelation(u2, f1); // UGM - Teknik
    removeRelation(u2, f2); // UGM - Ekonomi
    removeRelation(u2, f3); // UGM - Kedokteran
    
    // Sekarang aman untuk menghapus UGM dari list utama
    // CATATAN: Karena fungsi deleteUniv tidak mengembalikan head baru, 
    // kita harus pastikan UGM BUKAN head list saat dipanggil.
    deleteUniv(univHead, "UGM"); // UGM harusnya bukan head (UI dan ITB ada di depannya)

    cout << "University UGM dan relasinya telah dihapus." << endl;
    cout << endl;
    
    // Verifikasi University yang tersisa
    showAllUniversities(univHead);
    cout << endl;
    showUniversityWithMostAndLeastFaculties(univHead);
    
    cout << "--- PROGRAM SELESAI ---" << endl;

    // (Kode tambahan untuk cleanup memori yang lebih menyeluruh biasanya diperlukan di akhir,
    // tetapi ini di luar cakupan fungsi yang diminta.)

    return 0;
}