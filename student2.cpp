/// CLIENT

#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

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
    cout << "-----";
    cout << " Inregistrare ";
    cout << "----- \n\n";

    ifstream fin("C://Users//Irina//CLionProjects//PP - proiect C++//utilizatori.txt");

    string nume, prenume, email, parola, parola2, functie;

    set_color(GRAY);
    cout << "NUME: ";
    cin >> nume;

    cout << "PRENUME: ";
    cin >> prenume;
    set_color(WHITE);

    string line;
    int ok = 0;
    while (ok == 0){
        int aux = 1;

        set_color(GRAY);
        cout <<"ADRESA DE EMAIL: ";
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
            cout<<"\nAdresa de email introdusa exista deja!\n\n";
            set_color(WHITE);
            ok = 0;
        }
        else
            ok = 1;
    }

    set_color(GRAY);
    while (parola.length() < 8) {
        cout << "PAROLA";
        cout << " (cel putin 8 caractere)";
        cout << ": ";
        cin >> parola;
    }

    functie = "client";

    fin.close();

    if (ok == 1){
        set_color(GREEN);
        cout << "\nV-ati inregistrat cu succes!\n\n";
        set_color(WHITE);

        ofstream fout("C://Users//Irina//CLionProjects//PP - proiect C++//utilizatori.txt", ios_base::app);
        fout << "\n" << email << ";" << parola << ";" << functie << ";" << nume << ";" << prenume << ";";
        fout.close();
    }
    set_color(WHITE);
}

int logat = 0;
string restul, email, email2;

void logare()
{
    ifstream fin("C://Users//Irina//CLionProjects//PP - proiect C++//utilizatori.txt");

    set_color(YELLOW);
    cout <<"-----";
    cout << " Logare ";
    cout << "----- \n\n";
    set_color(WHITE);

    string parola;

    set_color(GRAY);
    cout << "ADRESA DE EMAIL: ";
    cin >> email;

    cout << "PAROLA: ";
    cin >> parola;
    set_color(WHITE);

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
    }
    else{
        set_color(GREEN);
        cout << "\nTe-ai logat cu succes!\n\n";
        set_color(WHITE);
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

void afisare_produse()
{
    for (auto & produs: produse){
        set_color(PURPLE);
        cout <<produs.getCod() << " " << produs.getDenumire() << " " << produs.getCantitate() <<" " << produs.getPret() << "\n";
    }
    set_color(WHITE);
}

vector <Produs> produse_comanda;

void adauga_produs()
{
    afisare_produse();

    cout << endl;

    string cod;
    cout << "Scrie codul produsului pe care doresti sa-l adaugi la comanda: ";
    cin >> cod;

    double cantitate;
    cout << "Introduceti cantitatea dorita: ";
    cin >> cantitate;

    cout << endl;

    for (auto & produs: produse)
        if (cod == produs.getCod()){
            string denumire = produs.getDenumire();
            double pret = cantitate * produs.getPret();
            Produs p(cod, denumire, cantitate, pret);
            produse_comanda.push_back(p);
        }
}

int egal (string c1, string c2)
{
    return c1 == c2;
}

void sterge_produs()
{
    for (auto & produs: produse_comanda){
        set_color(PURPLE);
        cout <<produs.getCod() << " " << produs.getDenumire() << " " << produs.getCantitate() <<" " << produs.getPret() << "\n";
        set_color(WHITE);
    }
    cout << endl;

    string cod;
    cout << "Scrie codul produsului pe care doresti sa-l stergi din comanda: ";
    cin >> cod;

    for (auto & produs: produse_comanda) {
        produse_comanda.clear();
        if (cod != produs.getCod())
            produse_comanda.push_back(produs);
    }
}

void plaseaza_comanda()
{
    ofstream fout("C://Users//Irina//CLionProjects//PP - proiect C++//comenzi.txt", ios_base::app);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Data d(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);

    if (produse_comanda.size() > 0) {
        fout << email2 << endl;
        fout << d << endl;

        for (auto &produs: produse_comanda)
            fout << produs << ";";

        fout << endl;

        set_color(GREEN);
        cout << "\n\nComanda a fost plasata cu succes!\n\n";
        set_color(WHITE);
    }

    fout.close();
}

void actualizare_stoc()
{
    ofstream fout("C://Users//Irina//CLionProjects//PP - proiect C++//propuneri.txt", ios_base::app);

    string propunere;

    cout << "Scrieti propunerea dorita: ";
    getline(cin>>ws, propunere);

    fout << email << ": " << propunere << endl;

    cout << "\n\n";

    fout.close();
}

void istoric_comenzi() {
    ifstream fin("C://Users//Irina//CLionProjects//PP - proiect C++//comenzi.txt");

    string data, produse2;
    while (!fin.eof()) {
        getline(fin, email2);
        getline(fin, data);
        getline(fin, produse2);

        if (email == email2) {
            set_color(GRAY);
            cout << "Data: ";
            set_color(PURPLE);
            cout << data << endl;
            set_color(WHITE);

            set_color(GRAY);
            cout << "Produse: \n";
            set_color(WHITE);

            int ok = 1;

            string produs = get_str_between_two_str(produse2, "", ";");
            restul = get_str_between_two_str(produse2, ";", "\n");

            while (ok) {
                set_color(PURPLE);

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
    }
    set_color(WHITE);

    cout << endl;

    fin.close();
}

int main() {
    citire_produse();

    int client = 1;
    while (client){
        set_color(BLUE);
        cout << "-----";
        cout << " MENIU CLIENT ";
        cout << "-----\n\n";
        set_color(YELLOW);
        cout << "1. Inregistrare\n";
        cout << "2. Logare\n";
        set_color(RED);
        cout << "3. Iesire\n\n";
        set_color(WHITE);

        int alegere_client = 0;
        while (alegere_client < 1 || alegere_client > 3){
            cout << "Selectati optiunea dorita: ";
            cin >> alegere_client;
        }
        cout << "\n";

        if (alegere_client == 1){
            inregistrare();
        }

        if (alegere_client == 2) {
            logare();
            while (logat == 1) {
                set_color(YELLOW);
                cout << "1. Vizualizare produse";
                cout << "\n2. Vizualizare cos cumparaturi";
                cout << "\n3. Vizualizare istoric comenzi";
                cout << "\n4. Propunere actualizare stoc";
                set_color(RED);
                cout << "\n5. Iesire\n\n";
                set_color(WHITE);

                int alegere_logat = 0;
                while (alegere_logat < 1 || alegere_logat > 5) {
                    cout << "Selectati optiunea dorita: ";
                    cin >> alegere_logat;
                }

                cout << "\n";

                if (alegere_logat == 1) {
                    set_color(BLUE);
                    cout << "\n-----";
                    cout << "Produse";
                    cout << "-----\n\n";
                    set_color(WHITE);
                    afisare_produse();
                }

                if (alegere_logat == 2) {
                    int cos = 1;
                    while (cos) {
                        set_color(BLUE);
                        cout << "\n-----";
                        cout << "Cos de cumparaturi";
                        cout << "-----\n";
                        set_color(WHITE);

                        if (produse_comanda.size() > 0) {
                            set_color(BLUE);
                            cout << "\nProduse: \n\n";
                            for (auto &produs: produse_comanda) {
                                set_color(PURPLE);
                                cout << produs.getCod() << " " << produs.getDenumire() << " " << produs.getCantitate() << " " << produs.getPret() << "\n";
                                set_color(WHITE);
                            }
                            cout << endl;
                        }
                        else {
                            set_color(RED);
                            cout << "\nCosul dumneavoastra este gol! \n\n";
                            set_color(WHITE);
                        }

                        set_color(YELLOW);
                        cout << "1. Modificare cos de cumparaturi";
                        cout << "\n2. Plasare comanda";
                        set_color(RED);
                        cout << "\n3. Iesire";
                        set_color(WHITE);

                        int optiune = 0;
                        while (optiune < 1 || optiune > 3) {
                            cout << "\n\nSelectati optiunea dorita: ";
                            cin >> optiune;
                        }

                        if (optiune == 1) {
                            set_color(BLUE);
                            cout << "\n-----";
                            cout << " Modificare cos de cumparaturi ";
                            cout << "-----\n\n";
                            set_color(WHITE);

                            int modificare = 1;
                            while (modificare) {
                                int opt = 0;

                                set_color(YELLOW);
                                cout << "1. Adauga un produs";
                                cout << "\n2. Sterge un produs";
                                set_color(RED);
                                cout << "\n3. Iesire\n\n";
                                set_color(WHITE);

                                while (opt < 1 || opt > 3) {
                                    cout << "\nSelectati optiunea dorita: ";
                                    cin >> opt;
                                }

                                if (opt == 1) {
                                    set_color(BLUE);
                                    cout << "\n-----";
                                    cout << "Adauga un produs";
                                    cout << "-----\n\n";
                                    set_color(WHITE);

                                    adauga_produs();
                                }

                                if (opt == 2) {
                                    set_color(BLUE);
                                    cout << "-----";
                                    cout << "Sterge un produs";
                                    cout << "-----\n\n";
                                    set_color(WHITE);

                                    sterge_produs();
                                }

                                if (opt == 3)
                                    modificare = 0;
                            }
                        }

                        if (optiune == 2) {
                            plaseaza_comanda();
                            cos = 0;
                        }

                        if (optiune == 3) {
                            cos = 0;
                        }
                    }
                }

                if (alegere_logat == 3) {
                    set_color(BLUE);
                    cout << "-----";
                    cout << "Istoric comenzi";
                    cout << "-----\n\n";
                    set_color(WHITE);

                    istoric_comenzi();
                }

                if (alegere_logat == 4) {
                    set_color(BLUE);
                    cout << "\n-----";
                    cout << "Propunere actualizare stoc";
                    cout << "-----\n\n";
                    set_color(WHITE);

                    actualizare_stoc();
                }

                if (alegere_logat == 5) {
                    logat = 0;
                    cout << "\n\n";
                }
            }
        }
        if (alegere_client == 3) {
            set_color(PINK);
            cout << "\nLa revedere!\n";
            set_color(WHITE);
            client = 0;
        }
    }
    return 0;
}
