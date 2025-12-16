#include "univ.h"

void insertFirstUniv(University*& head, const string& nama, int tahun, int jmlMhs) {
    University* u = new University{nama, tahun, jmlMhs, nullptr, head};
    head = u;
}

void insertLastUniv(University*& head, const string& nama, int tahun, int jmlMhs) {
    University* u = new University{nama, tahun, jmlMhs, nullptr, nullptr};
    if (!head) { head = u; return; }
    University* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = u;
}

void deleteFirstUniv(University*& head) {
    if (!head) return;
    University* temp = head;
    head = head->next;
    delete temp;
}

void deleteLastUniv(University*& head) {
    if (!head) return;
    if (!head->next) { delete head; head = nullptr; return; }
    University* temp = head;
    while (temp->next->next) temp = temp->next;
    delete temp->next;
    temp->next = nullptr;
}

void insertFirstFac(Faculty*& head, const string& nama, int jmlDosen, int jmlMhs) {
    Faculty* f = new Faculty{nama, jmlDosen, jmlMhs, nullptr, head};
    head = f;
}

void insertLastFac(Faculty*& head, const string& nama, int jmlDosen, int jmlMhs) {
    Faculty* f = new Faculty{nama, jmlDosen, jmlMhs, nullptr, nullptr};
    if (!head) { head = f; return; }
    Faculty* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = f;
}

void deleteFirstFac(Faculty*& head) {
    if (!head) return;
    Faculty* temp = head;
    head = head->next;
    delete temp;
}

void deleteLastFac(Faculty*& head) {
    if (!head) return;
    if (!head->next) { delete head; head = nullptr; return; }
    Faculty* temp = head;
    while (temp->next->next) temp = temp->next;
    delete temp->next;
    temp->next = nullptr;
}

bool addRelation(University* univ, Faculty* fac) {
    if (!univ || !fac) return false;
    Relation* r = new Relation{univ, fac, univ->relasiHead, fac->relasiHead};
    univ->relasiHead = r;
    fac->relasiHead = r;
    return true;
}

bool removeRelation(University* univ, Faculty* fac) {
    if (!univ || !fac) return false;
    Relation* prevU = nullptr, *currU = univ->relasiHead;
    while (currU) {
        if (currU->fac == fac) {
            if (prevU) prevU->nextUniv = currU->nextUniv;
            else univ->relasiHead = currU->nextUniv;
            break;
        }
        prevU = currU;
        currU = currU->nextUniv;
    }
    Relation* prevF = nullptr, *currF = fac->relasiHead;
    while (currF) {
        if (currF->univ == univ) {
            if (prevF) prevF->nextFac = currF->nextFac;
            else fac->relasiHead = currF->nextFac;
            delete currF;
            return true;
        }
        prevF = currF;
        currF = currF->nextFac;
    }
    return false;
}

void deleteUniv(University*& head, const string& nama) {
    University* prev = nullptr, *curr = head;
    while (curr) {
        if (curr->nama == nama) {
            Relation* r = curr->relasiHead;
            while (r) {
                removeRelation(curr, r->fac);
                r = r->nextUniv;
            }
            if (prev) prev->next = curr->next;
            else head = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void deleteFac(Faculty*& head, const string& nama) {
    Faculty* prev = nullptr, *curr = head;
    while (curr) {
        if (curr->nama == nama) {
            Relation* r = curr->relasiHead;
            while (r) {
                removeRelation(r->univ, curr);
                r = r->nextFac;
            }
            if (prev) prev->next = curr->next;
            else head = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

University* findUniversity(University* head, const string& name) {
    while (head) {
        if (head->nama == name) return head;
        head = head->next;
    }
    return nullptr;
}

Faculty* findFaculty(Faculty* head, const string& name) {
    while (head) {
        if (head->nama == name) return head;
        head = head->next;
    }
    return nullptr;
}

void showAllUniversities(University* head) {
    while (head) {
        cout << "Universitas: " << head->nama
            << " | Tahun: " << head->tahunBerdiri
            << " | Mahasiswa: " << head->jumlahMahasiswa << endl;
        showFacultiesOfUniversity(head);
        head = head->next;
    }
}

void showFacultiesOfUniversity(University* univ) {
    cout << "  Fakultas: ";
    Relation* r = univ->relasiHead;
    while (r) {
        cout << r->fac->nama << " ";
        r = r->nextUniv;
    }
    cout << endl;
}

void showUniversitiesWithFaculty(Faculty* fac) {
    cout << "Fakultas " << fac->nama << " dimiliki oleh: ";
    Relation* r = fac->relasiHead;
    while (r) {
        cout << r->univ->nama << " ";
        r = r->nextFac;
    }
    cout << endl;
}

void showFacultyList(Faculty* head) {
    while (head) {
        cout << "Fakultas: " << head->nama
            << " | Dosen: " << head->jumlahDosen
            << " | Mahasiswa: " << head->jumlahMahasiswa << endl;
        showUniversitiesWithFaculty(head);
        head = head->next;
    }
}

void showUniversityWithMostAndLeastFaculties(University* head) {
    if (!head) return;
    University* maxU = head, *minU = head;
    int maxCount = 0, minCount = INT_MAX;
    University* curr = head;
    while (curr) {
        int count = countChildOfParent(curr);
        if (count > maxCount) { maxCount = count; maxU = curr; }
        if (count < minCount) { minCount = count; minU = curr; }
        curr = curr->next;
    }
    cout << "Universitas dengan fakultas terbanyak: " << maxU->nama << " (" << maxCount << ")" << endl;
    cout << "Universitas dengan fakultas tersedikit: " << minU->nama << " (" << minCount << ")" << endl;
}

void showChildOfParent(University* univ, const string& facName) {
    Relation* r = univ->relasiHead;
    while (r) {
        if (r->fac->nama == facName) {
            cout << "Fakultas " << facName << " ditemukan di Universitas " << univ->nama << endl;
            return;
        }
        r = r->nextUniv;
    }
    cout << "Fakultas " << facName << " tidak ada di Universitas " << univ->nama << endl;
}

void deleteChildOfParent(University* univ, const string& facName) {
    Relation* r = univ->relasiHead;
    while (r) {
        if (r->fac->nama == facName) {
            removeRelation(univ, r->fac);
            cout << "Fakultas " << facName << " dihapus dari Universitas " << univ->nama << endl;
            return;
        }
        r = r->nextUniv;
    }
    cout << "Fakultas " << facName << " tidak ditemukan di Universitas " << univ->nama << endl;
}

int countChildOfParent(University* univ) {
    if (!univ) return 0;
    int count = 0;
    Relation* r = univ->relasiHead;
    while (r) {
        count++;
        r = r->nextUniv;
    }
    return count;
}
