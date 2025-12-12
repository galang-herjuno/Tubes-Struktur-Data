#include "Univ.h"

// Fungsi untuk membuat node University baru
University* createUniv(const string& nama) {
    University* newUniv = new University;
    newUniv->nama = nama;      // Mengisi nama Universitas
    newUniv->head = nullptr;   // Inisialisasi head relasi ke nullptr
    newUniv->next = nullptr;   // Inisialisasi pointer next University ke nullptr
    return newUniv;
}

// Fungsi untuk membuat node Faculty baru
Faculty* createFac(const string& nama) {
    Faculty* newFac = new Faculty;
    newFac->nama = nama;       // Mengisi nama Fakultas
    newFac->head = nullptr;    // Inisialisasi head relasi ke nullptr
    newFac->next = nullptr;    // Inisialisasi pointer next Faculty ke nullptr
    return newFac;
}

// Fungsi untuk menambahkan relasi Many-to-Many antara University dan Faculty
bool addRelation(University* univ, Faculty* fac) {
    if (!univ || !fac) return false;

    Relation* r = new Relation;
    r->univ = univ;  // Pointer ke University
    r->fac = fac;    // Pointer ke Faculty

    // Tambahkan relasi ke list relasi University (Prepend)
    r->nextUniv = univ->head;
    univ->head = r;

    // Tambahkan relasi ke list relasi Faculty (Prepend)
    r->nextFac = fac->head;
    fac->head = r;
    
    return true;
}


// Fungsi untuk menghapus University berdasarkan nama dari list utama
// CATATAN: Fungsi ini belum menangani penghapusan semua relasi terkait, 
// yang dapat menyebabkan memory leak jika tidak ditangani sebelum pemanggilan.
void deleteUniv(University* head, const string& nama){
    University* prev = nullptr;
    University* curr = head;
    while (curr) {
        if (curr->nama == nama) {
            // University ditemukan, hapus dari list
            if (prev) {
                prev->next = curr->next;
            } else {
                // Kasus head
                // Perlu diatur ulang jika ini adalah head dari list University, 
                // tetapi fungsi ini menerima head sebagai parameter, bukan reference.
                // Asumsi bahwa pemanggil akan mengelola perubahan head jika diperlukan.
            }

            // Idealnya, di sini harus ada kode untuk menghapus semua Relation yang menunjuk ke curr
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// Fungsi untuk menghapus Faculty berdasarkan nama dari list utama
// CATATAN: Fungsi ini belum menangani penghapusan semua relasi terkait.
void deleteFac(Faculty* head, const string& nama){
    Faculty* prev = nullptr;
    Faculty* curr = head;
    while (curr) {
        if (curr->nama == nama) {
            // Faculty ditemukan, hapus dari list
            if (prev) {
                prev->next = curr->next;
            } else {
                // Kasus head
            }
            
            // Idealnya, di sini harus ada kode untuk menghapus semua Relation yang menunjuk ke curr
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// Fungsi untuk menghapus relasi spesifik antara University dan Faculty
bool removeRelation(University* univ, Faculty* fac) {
    if (!univ || !fac) return false;

    // 1. Cari Relasi pada list relasi University
    Relation* currR = univ->head;
    Relation* prevR = nullptr;
    while (currR) {
        if (currR->fac == fac) break; // Relasi ditemukan
        prevR = currR;
        currR = currR->nextUniv;
    }

    if (!currR) return false; // Relasi tidak ditemukan

    // 2. Hapus dari daftar relasi Univ
    if (prevR) {
        prevR->nextUniv = currR->nextUniv;
    } else {
        univ->head = currR->nextUniv; // Relasi ada di head Univ
    }

    // 3. Cari Relasi yang sama pada list relasi Faculty
    Relation* currF = fac->head;
    Relation* prevF = nullptr;
    while (currF) {
        // Karena Relasi yang kita cari sudah diidentifikasi sebagai currR, 
        // kita bisa mencari berdasarkan univ, atau langsung membandingkan pointer:
        if (currF->univ == univ) break;
        prevF = currF;
        currF = currF->nextFac;
    }
    
    // Asumsi relasi pasti ada jika ditemukan di list Univ, tapi tetap periksa untuk robustness
    if (!currF) return false; 

    // 4. Hapus dari daftar relasi Fac
    if (prevF) {
        prevF->nextFac = currF->nextFac;
    } else {
        fac->head = currF->nextFac; // Relasi ada di head Fac
    }

    // 5. Bebaskan memori relasi (currR dan currF menunjuk ke objek yang sama)
    delete currR;
    return true;
}

// Fungsi untuk mencari University berdasarkan nama
University* findUniversity(University* head, const string& name) {
    University* curr = head;
    while (curr) {
        if (curr->nama == name) return curr;
        curr = curr->next;
    }
    return nullptr; // Tidak ditemukan
}

// Fungsi untuk mencari Faculty berdasarkan nama
Faculty* findFaculty(Faculty* head, const string& name) {
    Faculty* curr = head;
    while (curr) {
        if (curr->nama == name) return curr;
        curr = curr->next;
    }
    return nullptr; // Tidak ditemukan
}

// Fungsi untuk menampilkan semua University dalam list utama
void showAllUniversities(University* head) {
    cout << "Daftar Universitas:" << endl;
    University* curr = head;
    if (!curr) {
        cout << "  (Kosong)" << endl;
        return;
    }
    int count = 1;
    while (curr) {
        cout << "  " << count++ << ". " << curr->nama << endl;
        curr = curr->next;
    }
}

// Fungsi untuk menampilkan semua Faculty yang dimiliki oleh University tertentu
void showFacultiesOfUniversity(University* univ) {
    if (!univ) {
        cout << "Universitas tidak ditemukan." << endl;
        return;
    }
    cout << "Fakultas di Universitas " << univ->nama << ":" << endl;
    
    // Traversi melalui list relasi University menggunakan nextUniv
    Relation* currR = univ->head;
    if (!currR) {
        cout << "  (Tidak ada Fakultas)" << endl;
        return;
    }
    int count = 1;
    while (currR) {
        cout << "  " << count++ << ". " << currR->fac->nama << endl;
        currR = currR->nextUniv;
    }
}

// Fungsi untuk menampilkan semua University yang memiliki Faculty tertentu
void showUniversitiesWithFaculty(Faculty* fac) {
    if (!fac) {
        cout << "Fakultas tidak ditemukan." << endl;
        return;
    }
    cout << "Universitas yang memiliki Fakultas " << fac->nama << ":" << endl;
    
    // Traversi melalui list relasi Faculty menggunakan nextFac
    Relation* currR = fac->head;
    if (!currR) {
        cout << "  (Tidak ada Universitas)" << endl;
        return;
    }
    int count = 1;
    while (currR) {
        cout << "  " << count++ << ". " << currR->univ->nama << endl;
        currR = currR->nextFac;
    }
}

// Fungsi untuk menampilkan semua Faculty dalam list utama
void showFacultyList(Faculty* head) {
    cout << "Daftar Fakultas:" << endl;
    Faculty* curr = head;
    if (!curr) {
        cout << "  (Kosong)" << endl;
        return;
    }
    int count = 1;
    while (curr) {
        cout << "  " << count++ << ". " << curr->nama << endl;
        curr = curr->next;
    }
}

// Fungsi untuk menampilkan University dengan Fakultas Terbanyak dan Tersedikit
void showUniversityWithMostAndLeastFaculties(University* head) {
    if (!head) {
        cout << "Daftar Universitas kosong." << endl;
        return;
    }

    University* curr = head;
    int maxFaculties = -1;
    int minFaculties = -1;
    University* univMax = nullptr;
    University* univMin = nullptr;

    while (curr) {
        // Hitung jumlah Fakultas untuk University saat ini
        int facCount = 0;
        Relation* r = curr->head;
        while (r) {
            facCount++;
            r = r->nextUniv; // Traversi relasi dari sisi University
        }

        // Update Terbanyak (Max)
        if (maxFaculties == -1 || facCount > maxFaculties) {
            maxFaculties = facCount;
            univMax = curr;
        }

        // Update Tersedikit (Min)
        if (minFaculties == -1 || facCount < minFaculties) {
            minFaculties = facCount;
            univMin = curr;
        }

        curr = curr->next;
    }

    // Tampilkan hasil
    cout << "Universitas dengan Fakultas Terbanyak:" << endl;
    if (univMax) {
        cout << "  " << univMax->nama << " (" << maxFaculties << " Fakultas)" << endl;
    } else {
        cout << "  (Tidak ada data)" << endl;
    }

    cout << "Universitas dengan Fakultas Tersedikit:" << endl;
    if (univMin) {
        cout << "  " << univMin->nama << " (" << minFaculties << " Fakultas)" << endl;
    } else {
        cout << "  (Tidak ada data)" << endl;
    }
}