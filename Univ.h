#ifndef UNIV_H
#define UNIV_H
#include <iostream>
#include <string>
using namespace std;

struct Relation{
    University* univ;
    Faculty* fac;
    Relation* nextUniv;
    Relation* nextFac;
};

struct University{
    string nama;
    Relation* head;
    University* next;
};

struct Faculty{
    string nama;
    Relation* head;
    Faculty* next;
};

//Buat nambah data
University* createUniv(const string& nama);
Faculty* createFac(const string& nama);

//Buat nambah relasi
bool addRelation(University* univ, Faculty* fac);

//Buat hapus data
void deleteUniv(University* head, const string& nama);
void deleteFac(Faculty* head, const string& nama);

//Buat hapus relasi
bool removeRelation(University* univ, Faculty* fac);

//Buta search
University* findUniversity(University* head, const string& name);
Faculty* findFaculty(Faculty* head, const string& name);

//Buat nampilin data
void showAllUniversities(University* head);
void showFacultiesOfUniversity(University* univ);
void showUniversitiesWithFaculty(Faculty* fac);
void showFacultyList(Faculty* head);
void showUniversityWithMostAndLeastFaculties(University* head);


#endif