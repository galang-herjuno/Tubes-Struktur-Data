#include "Univ.h"

University* createUniv(const string& nama) {
    University* newUniv = new University;
    newUniv->nama = nama;
    newUniv->head = nullptr;
    newUniv->next = nullptr;
    return newUniv;
}

Faculty* createFac(const string& nama) {
    Faculty* newFac = new Faculty;
    newFac->nama = nama;
    newFac->head = nullptr;
    newFac->next = nullptr;
    return newFac;
}

bool addRelation(University* univ, Faculty* fac) {
    if (!univ || !fac) return false;

    Relation* r = new Relation;
    r->univ = univ;
    r->fac = fac;
    r->nextUniv = univ->head;
    r->nextFac = fac->head;

    univ->head = r;
    fac->head = r;
    return true;

}


void deleteUniv(University* head, const string& nama){
    University* prev = nullptr;
    University* curr = head;
    while (curr) {
        if (curr->nama == nama) {
            if (prev) prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void deleteFac(Faculty* head, const string& nama){
    Faculty* prev = nullptr;
    Faculty* curr = head;
    while (curr) {
        if (curr->nama == nama) {
            if (prev) prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

}