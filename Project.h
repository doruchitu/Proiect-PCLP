#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Adresa {
protected:
    string strada;
    int numar;
    string oras;
    string judet;
    string tara;
    string cod_postal;
public:
    // Constructor
    Adresa(string _strada, int _numar, string _oras, string _judet, string _tara, string _cod_postal)
        : strada(_strada), numar(_numar), oras(_oras), judet(_judet), tara(_tara), cod_postal(_cod_postal) {}

    // Metoda pentru afisare adresa
    void afiseazaAdresa() const {
        cout << "Adresa: " << strada << " numarul: " << numar << " , " << oras << " , " << judet << " , " << tara << " , " << cod_postal << endl;
    }
};

class Persoana : public Adresa {
protected:
    string nume;
    string numar_telefon;
    string email;
public:
    // Constructor
    Persoana(string _nume, string _numar_telefon, string _email, string _strada, int _numar, string _oras, string _judet, string _tara, string _cod_postal)
        : nume(_nume), numar_telefon(_numar_telefon), email(_email), Adresa(_strada, _numar, _oras, _judet, _tara, _cod_postal) {}

    // Metoda pentru afisarea datelor persoanei
    void afiseazaDetalii() const {
        cout << "Nume: " << nume << endl;
        cout << "Numar de telefon: " << numar_telefon << endl;
        cout << "Email: " << email << endl;
        afiseazaAdresa();
    }

    // Getter pentru nume
    string getNume() const {
        return nume;
    }
};

class Nota {
private:
    string materia;
    double nota;
    string profesor;
    string data;
public:
    // Constructor
    Nota(string _materia, double _nota, string _profesor, string _data)
        : materia(_materia), nota(_nota), profesor(_profesor), data(_data) {}

    // Getteri pentru a accesa membrii privați
    string getMateria() const {
        return materia;
    }
    double getNota() const {
        return nota;
    }
    string getProfesor() const {
        return profesor;
    }
    string getData() const {
        return data;
    }
};

class Elev : public Persoana {
private:
    int numar_ordine;
    vector<Nota> note;
    vector<string> absente;
    double medie_semestru;
    double medie_finala;
public:
    // Constructor
    Elev(string _nume, string _numar_telefon, string _email, string _strada, int _numar, string _oras, string _judet, string _tara, string _cod_postal, int _numar_ordine)
        : Persoana(_nume, _numar_telefon, _email, _strada, _numar, _oras, _judet, _tara, _cod_postal), numar_ordine(_numar_ordine), medie_semestru(0), medie_finala(0) {}

    // Metoda pentru adaugare note
    void adaugaNota(string materia, double nota, string profesor, string data) {
        note.push_back(Nota(materia, nota, profesor, data));
    }

    // Metoda pentru adaugare absente
    void adaugaAbsenta(string data) {
        absente.push_back(data);
    }

    // Metoda pentru calculare medie/semestru
    double calculeazaMediaSemestru() {
        double suma_note = 0.0;
        for (const auto& nota : note) {
            suma_note += nota.getNota();
        }
        return suma_note / note.size();
    }

    // Getteri pentru accesul la note si absente
    const vector<Nota>& getNote() const {
        return note;
    }
    const vector<string>& getAbsente() const {
        return absente;
    }

    // Metodă pentru a obține o referință non-const la absente
    vector<string>& getAbsenteNonConst() {
        return absente;
    }
};

class Profesor : public Persoana {
private:
    string materia_predata;
    double salariu;
public:
    // Constructor
    Profesor(string _nume, string _numar_telefon, string _email, string _strada, int _numar, string _oras, string _judet, string _tara, string _cod_postal, string _materia_predata, double _salariu)
        : Persoana(_nume, _numar_telefon, _email, _strada, _numar, _oras, _judet, _tara, _cod_postal), materia_predata(_materia_predata), salariu(_salariu) {}

    // Metoda pentru adaugare nota elevului
    void adaugaNota(Elev& elev, string materia, double nota, string data) {
        elev.adaugaNota(materia, nota, getNume(), data);
    }
};

class Catalog {
private:
    vector<Elev> elevi;
public:
    // Metoda pentru afisarea datelor elevilor din catalog
    void afiseazaElevi() const {
        cout << "Lista elevilor din catalog:" << endl;
        for (const auto& elev : elevi) {
            elev.afiseazaDetalii();
            cout << endl;
        }
    }

    // Metoda pentru adaugare elevi
    void adaugaElev(const Elev& elev) {
        elevi.push_back(elev);
    }

    // Metoda pentru adaugare nota
    void adaugaNota(string numeElev, string materia, double nota, string profesor, string data) {
        for (auto& elev : elevi) {
            if (elev.getNume() == numeElev) {
                elev.adaugaNota(materia, nota, profesor, data);
                return;
            }
        }
        cout << "Elevul cu numele " << numeElev << " nu a fost gasit." << endl;
    }

    // Metoda pentru adaugare absente
    void adaugaAbsenta(string numeElev, string data) {
        for (auto& elev : elevi) {
            if (elev.getNume() == numeElev) {
                elev.adaugaAbsenta(data);
                return;
            }
        }
        cout << "Elevul cu numele " << numeElev << " nu a fost gasit." << endl;
    }

    // Metoda pentru validare scrisoare motivare absente
    void valideazaScrisoareMotivare(string numeElev, string data) {
        for (auto& elev : elevi) {
            if (elev.getNume() == numeElev) {
                auto& absente = elev.getAbsenteNonConst();
                auto it = find(absente.begin(), absente.end(), data);
                if (it != absente.end()) {
                    absente.erase(it);
                    cout << "Absenta din data de " << data << " a fost motivata pentru elevul " << numeElev << "." << endl;
                    return;
                }
                cout << "Absenta din data de " << data << " nu a fost gasita pentru elevul " << numeElev << "." << endl;
                return;
            }
        }
        cout << "Elevul cu numele " << numeElev << " nu a fost gasit." << endl;
    }

    // Metoda pentru salvarea modificarilor intr-un fisier
    void salveazaModificari() {
        ofstream fout("Catalog.txt");
        if (fout.is_open()) {
            for (const auto& elev : elevi) {
                fout << "Nume elev: " << elev.getNume() << endl;
                fout << "Note: " << endl;
                for (const auto& nota : elev.getNote()) {
                    fout << "Materia: " << nota.getMateria() << ", Nota: " << nota.getNota() << ", Profesor: " << nota.getProfesor() << ", Data: " << nota.getData() << endl;
                }
                fout << "Absente: ";
                for (const auto& absenta : elev.getAbsente()) {
                    fout << absenta << " ";
                }
                fout << endl << endl;
            }
            fout.close();
            cout << "Modificarile au fost salvate in fisierul Catalog.txt." << endl;
        }
        else {
            cout << "Eroare la deschiderea fisierului Catalog.txt." << endl;
        }
    }

    // Metodă adăugată pentru a obține elevii (vector constant)
    const vector<Elev>& getElevi() const {
        return elevi;
    }
};
