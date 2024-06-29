#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Proiect.h"
#include "Optiuni.h"


// Funcție pentru afisarea opțiunilor profesorului
void ProfesorOptions(Profesor& profesor, Catalog& catalog) {
    int choice;
    do {
        cout << "----------Bun venit, " << profesor.getNume() << "!----------" << endl;
        cout << "Selectati una dintre urmatoarele optiuni:" << endl;
        cout << "1. Vizualizare elevi." << endl;
        cout << "2. Adaugare nota" << endl;
        cout << "3. Adaugare absenta" << endl;
        cout << "4. Validare cerere motivare absente" << endl;
        cout << "5. Salvati modificarile" << endl;
        cout << "6. Deconectare" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Elevii sunt:" << endl;
            catalog.afiseazaElevi();
            break;
        case 2: {
            string numeElev, materia, data;
            double nota;
            cout << "Introduceti numele elevului:";
            cin.ignore();
            getline(cin, numeElev);
            cout << "Introduceti materia:";
            getline(cin, materia);
            cout << "Introduceti nota:";
            cin >> nota;
            cout << "Introduceti data:";
            cin.ignore();
            getline(cin, data);
            catalog.adaugaNota(numeElev, materia, nota, profesor.getNume(), data);
            break;
        }
        case 3: {
            string numeElev, data;
            cout << "Introduceti numele elevului:";
            cin.ignore();
            getline(cin, numeElev);
            cout << "Introduceti data absentei:";
            getline(cin, data);
            catalog.adaugaAbsenta(numeElev, data);
            break;
        }
        case 4: {
            string numeElev, data;
            cout << "Introduceti numele elevului:";
            cin.ignore();
            getline(cin, numeElev);
            cout << "Introduceti data absentei de motivat:";
            getline(cin, data);
            catalog.valideazaScrisoareMotivare(numeElev, data);
            break;
        }
        case 5:
            catalog.salveazaModificari();
            break;
        case 6:
            cout << "Deconectare..." << endl;
            break;
        default:
            cout << "Optiune invalida. Incercati din nou." << endl;
            break;
        }
    } while (choice != 6);
}

// Funcție pentru afisarea opțiunilor elevului
void ElevOption(Elev& elev) {
    int choice;
    do {
        cout << "----------Bun venit, " << elev.getNume() << "!----------" << endl;
        cout << "Selectati una dintre urmatoarele optiuni:" << endl;
        cout << "1. Vizualizare note." << endl;
        cout << "2. Vizualizare absente." << endl;
        cout << "3. Calculeaza media semestriala." << endl;
        cout << "4. Deconectare." << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Notele sunt:" << endl;
            for (const auto& nota : elev.getNote()) {
                cout << "Materia:" << nota.getMateria() << ", Nota: " << nota.getNota() << ", Profesor: " << nota.getProfesor() << ", Data: " << nota.getData() << endl;
            }
            break;
        case 2:
            cout << "Absentele sunt:" << endl;
            for (const auto& absenta : elev.getAbsente()) {
                cout << "Data: " << absenta << endl;
            }
            break;
        case 3: {
            double media = elev.calculeazaMediaSemestru();
            cout << "Media semestriala este:" << media << endl;
            break;
        }
        case 4:
            cout << "Deconectare..." << endl;
            break;
        default:
            cout << "Optiune invalida. Incercati din nou." << endl;
            break;
        }
    } while (choice != 4);
}

// Funcție pentru afisare optiuni parinte
void ParinteOption(Catalog& catalog) {
    string numeElev;
    cout << "Introduceti numele elevului pentru care doriti sa aflati detalii:" << endl;
    cin.ignore();
    getline(cin, numeElev);

    int choice;
    do {
        cout << "----------Bun venit, Parinte!----------" << endl;
        cout << "Selectati una dintre urmatoarele optiuni:" << endl;
        cout << "1. Vizualizare note elev." << endl;
        cout << "2. Vizualizare absente." << endl;
        cout << "3. Deconectare." << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Notele elevului " << numeElev << " sunt:" << endl;
            for (const auto& elev : catalog.getElevi()) {
                if (elev.getNume() == numeElev) {
                    for (const auto& nota : elev.getNote()) {
                        cout << "Materia: " << nota.getMateria() << ", Nota: " << nota.getNota() << ", Profesor: " << nota.getProfesor() << ", Data: " << nota.getData() << endl;
                    }
                }
            }
            break;
        case 2:
            cout << "Absentele elevului " << numeElev << " sunt:" << endl;
            for (const auto& elev : catalog.getElevi()) {
                if (elev.getNume() == numeElev) {
                    for (const auto& absenta : elev.getAbsente()) {
                        cout << "Data: " << absenta << endl;
                    }
                }
            }
            break;
        case 3:
            cout << "Deconectare..." << endl;
            break;
        default:
            cout << "Optiune invalida. Incercati din nou." << endl;
            break;
        }
    } while (choice != 3);
}
