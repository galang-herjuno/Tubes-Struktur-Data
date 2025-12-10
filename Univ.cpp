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

}


void deleteUniv(University* head, const string& nama);
void deleteFac(Faculty* head, const string& nama);