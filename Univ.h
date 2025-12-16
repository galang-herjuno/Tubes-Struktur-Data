#ifndef UNIV_H
#define UNIV_H
#include <iostream>
#include <string>
using namespace std;

struct University;
struct Faculty;

struct Relation {
    University* univ;
    Faculty* fac;
    Relation* nextUniv;
    Relation* nextFac;
};

struct University {
    string nama;
    int tahunBerdiri;
    int jumlahMahasiswa;
    Relation* relasiHead;
    University* next;
};

struct Faculty {
    string nama;
    int jumlahDosen;
    int jumlahMahasiswa;
    Relation* relasiHead;
    Faculty* next;
};

void insertFirstUniv(University*& head, const string& nama, int tahun, int jmlMhs);
void insertLastUniv(University*& head, const string& nama, int tahun, int jmlMhs);
void deleteFirstUniv(University*& head);
void deleteLastUniv(University*& head);
void insertFirstFac(Faculty*& head, const string& nama, int jmlDosen, int jmlMhs);
void insertLastFac(Faculty*& head, const string& nama, int jmlDosen, int jmlMhs);
void deleteFirstFac(Faculty*& head);
void deleteLastFac(Faculty*& head);
bool addRelation(University* univ, Faculty* fac);
bool removeRelation(University* univ, Faculty* fac);
void deleteUniv(University*& head, const string& nama);
void deleteFac(Faculty*& head, const string& nama);
University* findUniversity(University* head, const string& name);
Faculty* findFaculty(Faculty* head, const string& name);
void showAllUniversities(University* head);
void showFacultiesOfUniversity(University* univ);
void showUniversitiesWithFaculty(Faculty* fac);
void showFacultyList(Faculty* head);
void showUniversityWithMostAndLeastFaculties(University* head);
void showChildOfParent(University* univ, const string& facName);
void deleteChildOfParent(University* univ, const string& facName);
int countChildOfParent(University* univ);

#endif