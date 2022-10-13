/// ADMINISTRATOR 

#include <windows.h>
#include <vector>
#include <fstream>
#include "produs.cpp"
#include "data.cpp"
#include "comanda.cpp"

#define BLUE 9
#define GREEN 10
#define RED 4
#define YELLOW 6
#define PURPLE 5
#define WHITE 15
#define GRAY 8
#define PINK 13

void set_color(int color_code)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code);
}

string get_str_between_two_str(const string &s, const string &start_delim, const string &stop_delim)
{
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find(stop_delim);

    return s.substr(end_pos_of_first_delim, last_delim_pos - end_pos_of_first_delim);
}

void inregistrare()
{
    set_color(YELLOW);
    cout << "\n-----";
    cout << " Inregistrare ";
    cout << "----- \n\n";
    set_color(WHITE);

    ifstream fin("C://Users//Irina//CLionProjects//inreg-log//utilizatori.txt");

    string nume, prenume, email, parola, parola2, functie;

    set_color(GRAY);
    cout << "NUME: ";
    set_color(WHITE);
    cin >> nume;

    set_color(GRAY);
    cout << "PRENUME: ";
    set_color(WHITE);
    cin >> prenume;

    string line;
    int ok = 0;
    while (ok == 0){
        int aux = 1;

        set_color(GRAY);
        printf("ADRESA DE EMAIL: ");
        set_color(WHITE);
        cin >> email;

        while (fin.eof() != 1 && getline(fin, line)){
            string email2 = get_str_between_two_str(line, "", ";");
            string restul = get_str_between_two_str(line, ";", "\n");

            if (email == email2)
                aux = 0;
        }
        if (aux == 0){
            set_color(RED);
            cout<<"Adresa de email introdusa exista deja!\n";
            set_color(WHITE);
            ok = 0;
        }
        else
            ok = 1;
    }

    while (parola.length() < 8) {
        set_color(GRAY);
        cout << "PAROLA";
        cout << " (cel putin 8 caractere)";
        cout << ": ";
        set_color(WHITE);
        cin >> parola;
    }

    functie = "client";

    fin.close();

    if (ok == 1){
        set_color(GREEN);
        cout << "V-ati inregistrat cu succes! \n\n";
        set_color(WHITE);

        ofstream fout("C://Users//Irina//CLionProjects//inreg-log//utilizatori.txt", ios_base::app);
        fout << "\n" << email << ";" << parola << ";" << functie << ";" << nume << ";" << prenume << ";";
        fout.close();
    }
}

int logat = 0;
string restul, email, email2;

int valid = 1;
void logare()
{
    ifstream fin("C://Users//Irina//CLionProjects//PP - proiect C++//utilizatori.txt");

    set_color(YELLOW);
    printf("\n-----");
    printf(" Logare ");
    printf("----- \n\n");
    set_color(WHITE);

    string parola;

    set_color(GRAY);
    cout << "ADRESA DE EMAIL: ";
    set_color(WHITE);
    cin >> email;

    set_color(GRAY);
    cout << "PAROLA: ";
    set_color(WHITE);
    cin >> parola;

    string line;
    while (logat == 0 && fin.eof() != 1 && getline(fin, line)){
        email2 = get_str_between_two_str(line, "", ";");
        restul = get_str_between_two_str(line, ";", "\n");
        string parola2 = get_str_between_two_str(restul, "", ";");
        restul = get_str_between_two_str(restul, ";", "\n");

        if(email == email2  && parola == parola2)
            logat = 1;
    }
    if (logat == 0){
        set_color(RED);
        cout << "\nAdresa de email sau parola invalida(e)!\n\n";
        set_color(WHITE);

        valid = 0;
    }

    fin.close();
}

vector<Produs> produse;

void citire_produse()
{
    ifstream fin("C://Users//Irina//CLionProjects//PP - proiect C++//stoc.txt");
    string cod, denumire;
    int cantitate;
    double pret;

    while(!fin.eof()){
        fin>>cod;
        fin>>denumire;
        fin>>cantitate;
        fin>>pret;

        produse.push_back(Produs(cod, denumire, cantitate, pret));
    }
    fin.close();
}

void adauga_produs(Produs p)
{
    ofstream fout("C://Users//Irina//CLionProjects//PP - proiect C++//stoc.txt", ios_base::app);
    fout << p.getCod() << " " << p.getDenumire() << " " << p.getCantitate() << " " << p.getPret() << endl;
    fout.close();
}

void sterge_produs()
{
    ofstream fout("C://Users//Irina//CLionProjects//PP - proiect C++//stoc.txt");
    cout<<"Introduceti codul: ";
    string cod;
    cin>>cod;
    for (auto & produs: produse) {
        if (cod != produs.getCod()) {
            fout << produs.getCod() << " " << produs.getDenumire() << " " << produs.getCantitate() << " " << produs.getPret() << endl;
        }
    }
    fout.close();
}

void modifica_cod()
{
    ofstream fout("C://Users//Irina//CLionProjects//PP - proiect C++//stoc.txt");
    cout<<"Introduceti codul: ";
    string cod;
    cin>>cod;
    for (auto & produs: produse) {
        if (cod == produs.getCod()) {
            cout<<"Introduceti noul codul: ";
            string cod_nou;
            cin>>cod_nou;

            produs = Produs(cod_nou, produs.getDenumire(), produs.getCantitate(), produs.getPret());
        }
        fout << produs.getCod() << " " << produs.getDenumire() << " " << produs.getCantitate() << " " << produs.getPret() << endl;

    }
    fout.close();
}

void modifica_denumire()
{
    ofstream fout("C://Users//Irina//CLionProjects//PP - proiect C++//stoc.txt");
    cout<<"Introduceti codul: ";
    string cod;
    cin>>cod;
    for (auto & produs: produse) {
        if (cod == produs.getCod()) {
            cout<<"Introduceti noua denumire: ";
            string denumire_noua;
            cin>>denumire_noua;

            produs = Produs(produs.getCod(), denumire_noua, produs.getCantitate(), produs.getPret());
        }
        fout << produs.getCod() << " " << produs.getDenumire() << " " << produs.getCantitate() << " " << produs.getPret() << endl;
    }
    fout.close();
}

void modifica_cantitate()
{
    ofstream fout("C://Users//Irina//CLionProjects//PP - proiect C++//stoc.txt");
    cout<<"Introduceti codul: ";
    string cod;
    cin>>cod;
    for (auto & produs: produse) {
        if (cod == produs.getCod()) {
            cout<<"Introduceti noua cantitate: ";
            int cantitate_noua;
            cin>> cantitate_noua;

            produs = Produs(produs.getCod(), produs.getDenumire(), cantitate_noua, produs.getPret());
        }
        fout << produs.getCod() << " " << produs.getDenumire() << " " << produs.getCantitate() << " " << produs.getPret() << endl;
    }
    fout.close();
}

void modifica_pret()
{
    ofstream fout("C://Users//Irina//CLionProjects//PP - proiect C++//stoc.txt");
    cout<<"Introduceti codul: ";
    string cod;
    cin>>cod;
    for (auto & produs: produse) {
        if (cod == produs.getCod()) {
            cout<<"Introduceti noul pret: ";
            double pret_nou;
            cin>> pret_nou;

            produs = Produs(produs.getCod(), produs.getDenumire(), produs.getCantitate(), pret_nou);
        }
        fout << produs.getCod() << " " << produs.getDenumire() << " " << produs.getCantitate() << " " << produs.getPret() << endl;
    }
    fout.close();
}

void afisare_produse()
{
    for (auto & produs: produse){
        set_color(PURPLE);
        cout <<produs.getCod() << " " << produs.getDenumire() << " " << produs.getCantitate() <<" " << produs.getPret() << "\n";
        set_color(WHITE);
    }
}

void vizualizare_cereri()
{
    string line;
    ifstream fin("C://Users//Irina//CLionProjects//PP - proiect C++//propuneri.txt");
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
}

void istoric_comenzi() {
    ifstream fin("C://Users//Irina//CLionProjects//PP - proiect C++//comenzi.txt");

    string data, produse2;
    while (!fin.eof()) {
        getline(fin, email2);
        getline(fin, data);
        getline(fin, produse2);

        int ok;

        if (email2 != ""){
            ok = 1;
            set_color(GRAY);
            cout << "Email: ";
            set_color(PURPLE);
            cout << email2 << endl;
            set_color(GRAY);
            cout << "Data: " ;
            set_color(PURPLE);
            cout << data << endl;
            set_color(GRAY);
            cout << "Produse: \n";
            set_color(PURPLE);
        }

        string produs = get_str_between_two_str(produse2, "", ";");
        restul = get_str_between_two_str(produse2, ";", "\n");

        while (ok) {
            string cod, denumire, cantitate, pret;
            while(produs != ""){
                cod = get_str_between_two_str(produs, "", " ");
                string restul4 = get_str_between_two_str(produs, " ", "\n");
                denumire = get_str_between_two_str(restul4, "", " ");
                restul4 = get_str_between_two_str(restul4, " ", "\n");
                cantitate = get_str_between_two_str(restul4, "", " ");
                restul4 = get_str_between_two_str(restul4, " ", "\n");
                pret = get_str_between_two_str(restul4, "", " ");
                restul4 = get_str_between_two_str(restul4, " ", "\n");
                produs = "";
            }
            cout << "    - " << cod << " " << denumire << endl;
            set_color(GRAY);
            cout << "      Cantitate: ";
            set_color(PURPLE);
            cout << cantitate << endl;
            set_color(GRAY);
            cout << "      Pret: ";
            set_color(PURPLE);
            cout << pret << endl;
            set_color(WHITE);

            if (restul == "")
                ok = 0;
            else{
                produs = get_str_between_two_str(restul, "", ";");
                restul = get_str_between_two_str(restul, ";", "\n");
            }
        }
        cout << endl;
    }
    set_color(WHITE);
    fin.close();
}

int main() {
    citire_produse();
    int administrator = 1;
    while (administrator) {
        set_color(BLUE);
        cout << "-----";
        cout << " MENIU ADMINISTRATOR ";
        cout << "-----\n\n";
        set_color(WHITE);

        set_color(YELLOW);
        cout << "1. Inregistrare\n";
        cout << "2. Logare\n";
        set_color(WHITE);

        set_color(RED);
        cout << "3. Iesire\n\n";
        set_color(WHITE);

        int alegere_administrator = 0;          //----------------------- MENIU ADMINISTRATOR --------------------------

        while (alegere_administrator < 1 || alegere_administrator > 3) {
            cout << "Selectati optiunea dorita: ";
            cin >> alegere_administrator;
        }

        if (alegere_administrator == 1){
            inregistrare();
        }

        if (alegere_administrator == 2){
            logare();
            string functie = get_str_between_two_str(restul, "", ";");

            if(functie == "admin") {
                set_color(GREEN);
                cout << "\nTe-ai logat cu succes!\n\n";
                set_color(WHITE);

                while (logat == 1) {
                    set_color(YELLOW);
                    cout << "\n1. Vizualizare stoc";
                    cout << "\n2. Modificare stoc";
                    cout << "\n3. Vizualizare istoric comenzi";
                    cout << "\n4. Vizualizare cereri actualizare stoc";

                    set_color(RED);
                    cout << "\n5. Iesire\n\n";
                    set_color(WHITE);

                    int alegere_logat = 0;
                    while (alegere_logat < 1 || alegere_logat > 5) {
                        cout << "Selectati optiunea dorita: ";
                        cin >> alegere_logat;
                    }

                    if (alegere_logat == 1) {
                        set_color(BLUE);
                        cout << "\n-----";
                        cout << "Stoc produse";
                        cout << "-----\n\n";
                        set_color(WHITE);
                        afisare_produse();

                        cout << "\n\n";
                    }
                    if (alegere_logat == 2) {
                        int stoc = 1;
                        while (stoc) {
                            set_color(YELLOW);
                            cout << "\n1. Adaugare";
                            cout << "\n2. Stergere";
                            cout << "\n3. Modificare";
                            set_color(RED);
                            cout << "\n4. Iesire";
                            set_color(WHITE);

                            int optiune = 0;
                            while (optiune < 1 || optiune > 4) {
                                cout << "\n\nSelectati optiunea dorita: ";
                                cin >> optiune;
                            }
                            if (optiune == 1) {
                                set_color(BLUE);
                                cout << "\n-----";
                                cout << "Adaugare produs";
                                cout << "-----\n\n";
                                set_color(WHITE);
                                set_color(GRAY);
                                string cod;
                                cout << " Cod: ";
                                cin >> cod;
                                string denumire;
                                cout << "Denumire: ";
                                cin >> denumire;
                                int cantitate;
                                cout << "Cantitate: ";
                                cin >> cantitate;
                                double pret;
                                cout << "Pret: ";
                                cin >> pret;
                                set_color(WHITE);
                                adauga_produs(Produs(cod, denumire, cantitate, pret));
                            }
                            if (optiune == 2) {
                                set_color(BLUE);
                                cout << "-----";
                                cout << "Stergere produs";
                                cout << "-----\n\n";

                                set_color(BLUE);
                                cout << "Produse disponibile: \n\n";
                                set_color(WHITE);
                                afisare_produse();
                                cout << "\n\n";

                                sterge_produs();
                            }
                            if (optiune == 3){
                                set_color(BLUE);
                                cout << "-----";
                                cout << "Modificare produs";
                                cout << "-----\n\n";

                                set_color(BLUE);
                                cout << "Produse disponibile: \n\n";
                                set_color(WHITE);
                                afisare_produse();
                                cout << "\n\n";

                                int modificare = 1;
                                while (modificare){
                                    set_color(YELLOW);
                                    cout << "\n1. Modificare cod";
                                    cout << "\n2. Modificare denumire ";
                                    cout << "\n3. Modificare cantitate";
                                    cout << "\n4. Modificare pret";
                                    set_color(RED);
                                    cout << "\n5. Iesire";
                                    set_color(WHITE);

                                    int opt_modificare = 0;
                                    while (opt_modificare < 1 || opt_modificare > 5) {
                                        cout << "\n\nSelectati optiunea dorita: ";
                                        cin >> opt_modificare;
                                    }

                                    if (opt_modificare == 1){
                                        modifica_cod();
                                    }
                                    if (opt_modificare == 2){
                                        modifica_denumire();
                                    }
                                    if (opt_modificare == 3){
                                        modifica_cantitate();
                                    }
                                    if (opt_modificare == 4){
                                        modifica_pret();
                                    }
                                    if (opt_modificare == 5) modificare = 0;
                                }
                            }

                            if (optiune == 4) stoc = 0;
                        }
                    }
                    if (alegere_logat == 3) {
                        set_color(BLUE);
                        cout << "\n-----";
                        cout << "Istoric comenzi";
                        cout << "-----\n\n";
                        set_color(WHITE);

                        istoric_comenzi();
                    }

                    if (alegere_logat == 4) {
                        set_color(BLUE);
                        cout << "\n-----";
                        cout << "Cereri actualizare stoc";
                        cout << "-----\n\n";
                        set_color(WHITE);

                        vizualizare_cereri();
                        cout << "\n";
                    }

                    if (alegere_logat == 5) {
                        logat = 0;
                        cout << "\n\n";
                    }
                }
            }
            else
                if (valid == 1){
                    set_color(RED);
                    cout << "\nTrebuie sa utilizati un cont de administrator!\n\n";
                    set_color(WHITE);
                }
        }
        if (alegere_administrator == 3){
            set_color(PINK);
            cout << "\nLa revedere!";
            set_color(WHITE);
            administrator = 0;
        }
    }
    return 0;
}
