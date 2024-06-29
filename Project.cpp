#include <iostream>
using namespace std;
#include "Proiect.h";
#include "Optiuni.cpp";
#include "Optiuni.h";


int main() {
    Catalog catalog;
    Profesor profesor1("Ion Popescu", "0712345678", "ion.popescu@school.com", "Strada Principala", 10, "Oras", "Judet", "Tara", "123456", "Matematica", 4000);
    Elev elev1("Ana Ionescu", "0722345678", "ana.ionescu@student.com", "Strada Secundara", 5, "Brasov", "Brasov", "Romania", "654321", 1);
    Elev elev2("Mara Ionescu", "0722345678", "ana.ionescu@student.com", "Strada Suceava", 5, "Galati", "Galati", "Romania", "654321", 2);

    catalog.adaugaElev(elev1);
    catalog.adaugaElev(elev2);

    int userType;
    do {
        cout << "----------Bine ati venit!----------" << endl;
        cout << "Selectati tipul de utilizator:" << endl;
        cout << "1. Profesor" << endl;
        cout << "2. Elev" << endl;
        cout << "3. Parinte" << endl;
        cout << "4. Iesire" << endl;
        cin >> userType;

        switch (userType) {
        case 1:
            ProfesorOptions(profesor1, catalog);
            break;
        case 2:
            ElevOption(elev1);
            break;
        case 3:
            ParinteOption(catalog);
            break;
        case 4:
            cout << "Iesire..." << endl;
            break;
        default:
            cout << "Optiune invalida. Incercati din nou." << endl;
            break;
        }
    } while (userType != 4);

    return 0;
}


