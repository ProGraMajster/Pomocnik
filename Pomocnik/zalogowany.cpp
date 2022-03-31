//Plik: zalogowany.hpp
#include "zalogowany.hpp"

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include <string>
#include <locale>
#include <conio.h>
#include <cmath>
#include <iomanip>
#include <process.h>
#include <vector>
#include <thread>
#include <chrono>
#include <psapi.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;

extern HANDLE kolor;

extern wchar_t napis[1024];

extern string odp;
extern string lnickname;
extern string nickname;
extern string haslo;
extern string schowek_programowy;

extern int zkolor;
extern int wczytywanie_koloru();
extern int log();
extern int kodowanie(char *napis);
extern int napisy_p();
extern int data_napisy_p();
extern int przypomnienie_odczyt();
extern int wczytywanie_koloru_dnia();
extern int zapas_zkolor;
extern int errorlitsa();
extern int zapytanie();

extern bool zalogowany;
extern bool datanap;
extern bool przyp;
extern bool wczyt_kolor_dnia;
extern bool snet;
extern bool ust_logi;
extern bool przedrostek_path;
extern bool nowy_sys_zap_ust;
extern bool debugowanie;
extern bool czy_znaleziono_fraze;

bool rejestracja()
{
    SetConsoleTitleA( "Pomocnik - Rejsestracja" );

            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
            SetConsoleTextAttribute( kolor, 14 );
            string user,sciezka_f, user_sciezka, rozsze, nickname_r; // -
            system("cls");
            rozsze = ".uesrp";

            cout << "Rejestracja" << endl;

            cout << "Nickname:";
            cin >> nickname_r;
            user = nickname_r + rozsze;
            sciezka_f = "c:\\PlikiPomocnik\\Users\\" + nickname_r;
            user_sciezka = "c:\\PlikiPomocnik\\Users\\" + user;

            cout << "Haslo:";

            char napisu[100];
            cin.get();
            cin.get(napisu, 255);

            mkdir("c:\\PlikiPomocnik\\Users\\");


        kodowanie(napisu);
        kodowanie(napisu);
        kodowanie(napisu);
        kodowanie(napisu);
        kodowanie(napisu);
        kodowanie(napisu);
        kodowanie(napisu);

        fstream plik;
        plik.open(user_sciezka.c_str(), ios::out);
        if(plik.good() == true)
        {
            plik << napisu;
            cout << "Zarejestrowano" << endl;
            nickname = nickname_r;
            mkdir(sciezka_f.c_str());
            napisy_p();
        }
        else
        {
            wcsncpy(napis, L"Nie udało się utworzyć profilu!", 1024);
                wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                wprintf(L"%s", napis);
            cout << endl;
            getch();
        }
        plik.close();
        plik.clear();

            system("pause");

                SetConsoleTitleA( "Pomocnik" );
}

bool logowanie()
{
    SetConsoleTitleA( "Pomocnik - Logowanie" );

    if(zalogowany == 1)
    {
       wcsncpy(napis, L"Jesteś już zalogowany!", 1024);
                wprintf(L"%s", napis);
            cout << endl;
    }
    else
    {
                kolor = GetStdHandle( STD_OUTPUT_HANDLE );
            SetConsoleTextAttribute( kolor, 14 );
            string user, user_sciezka, rozsze, nickname_r; // -
            system("cls");
            rozsze = ".uesrp";

            cout << "Logowanie:" << endl;

            cout << "Login:";
            cin >> nickname_r;
            user = nickname_r + rozsze;
            user_sciezka = "c:\\PlikiPomocnik\\Users\\" + user;
            cout << endl;
            wcsncpy(napis, L"Hasło:", 1024);
                wprintf(L"%s", napis);

            char napisu[100];
            cin.get();
            cin.get(napisu, 255);

            mkdir("c:\\PlikiPomocnik\\Users\\");


            kodowanie(napisu);
            kodowanie(napisu);
            kodowanie(napisu);
            kodowanie(napisu);
            kodowanie(napisu);
            kodowanie(napisu);
            kodowanie(napisu);

            fstream plik;
            plik.open(user_sciezka.c_str(), ios::in);
            if(plik.good() == true)
            {
                string hasl = napisu;
                string hasp;
                plik >> hasp;
                if(hasp == hasl)
                {
                    cout << "Zalogowano!" << endl;
                    nickname = nickname_r;
                    zalogowany = true;
                    nowy_sys_zap_ust = true;
                    zal_ladowanie_ust();
                    napisy_p();
                }
                else
                {
                    wcsncpy(napis, L"Nie udało się zalogować!", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                    wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                    getch();
                    napisy_p();
                }
            }
            else
            {
                wcsncpy(napis, L"Nie znaleziono użytkownika!", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                getch();
                napisy_p();
            }
            plik.close();

    }
            log();
                SetConsoleTitleA( "Pomocnik" );
}

bool zalogowany_napisy_p()
{
    system("cls");
    SetConsoleTitleA( "Pomocnik" );
        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 9 );
        cout << "Pomocnik"<< endl;
    if(datanap == true)
    {
        data_napisy_p();
    }

    cout<< endl;
    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
    cout << "---------------------------------------------------------/" << endl;
    cout << "Satus: Zalogowany {" + nickname + "}" << endl;
    wcsncpy(napis, L"Wpisz 'pomoc' lub 'help' aby zobaczyć spis komend", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            if(przyp == true)
            {
                cout << "---------------------------------------------------------/" << endl;
                przypomnienie_odczyt();
            }
    cout << "________________________________________________________/" << endl << endl;

    cout << "Witaj "<< nickname <<"! Z tej strony Pomocnik." << endl;
    wcsncpy(napis, L"W czym mogę pomóć?", 1024);
            wprintf(L"%s", napis);
    cout << endl;
    if(wczyt_kolor_dnia == true)
    {
        wczytywanie_koloru_dnia();
    }
        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
}

bool zalogowany_kommendy()
{

}

bool zal_help()
{

}

bool zal_ladowanie_ust()
{
    string path = "C:\\PlikiPomocnik\\Users\\" + nickname + "\\ustawienia.txt";
    if(access(path.c_str(), F_OK) == 0)
    {
        fstream plik_ust; // plik ustawień
    plik_ust.open(path, ios::in);
        if(plik_ust.good()==true)
        {
            plik_ust >> zkolor;
            plik_ust >> snet;
            plik_ust >> ust_logi;
            plik_ust >> przedrostek_path;
            plik_ust >> wczyt_kolor_dnia;
            plik_ust >> datanap;

            plik_ust.close();
                //
                    zapas_zkolor = zkolor;
                    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
                //
            if(debugowanie == true)
            {
                cout << "Plik Ustawien" << endl;
                cout << "Kolor czcionki:" << zkolor << endl;
                cout << "Sprawdzanie polaczenia z inetr. po wlaczeniu programu:" << snet << endl;
                cout << "zapisywanie zdarzen do pliku (Pomocniklog.txt):" << ust_logi << endl;
                cout << "Szybkie wywolywanie z sciezki:" << przedrostek_path << endl;
                cout << "Kolor dnia:" << wczyt_kolor_dnia << endl;
                cout << "zapas_zkolor: " << zapas_zkolor << endl;
            }
        }
        else
        {
            if(debugowanie == true)
            {
                errorlitsa();
            }
        }
    }
    else
    {
        zal_domyslne_ust();
    }
}

bool zal_domyslne_ust()
{
    snet = true; // zmianna od funkcji
        ust_logi = true; // logi zapisywane do Pomocniklog.txt
        przedrostek_path = true; //
        nowy_sys_zap_ust = false; // nowy system zapisywania ustawień
        czy_znaleziono_fraze = false;
        przyp = false; //
        wczyt_kolor_dnia = false; // wczytywanie koloru zależny od dnia
        datanap = true;
        zkolor = 7; // zmania koloru czcinoki
        zapas_zkolor=7;
    //system("cls");
    cout << "10%" << endl;
    fstream plik_ust;
    plik_ust.open("C:\\PlikiPomocnik\\Users\\" + nickname +"\\ustawienia.txt", ios::out);
        if(plik_ust.good()==true)
        {
            cout << "30%" << endl;
            if(wczyt_kolor_dnia == false)
            {
               plik_ust << zapas_zkolor;
            }
            else
            {
                plik_ust << zkolor;
            }
            cout << "40%" << endl;
            plik_ust << endl;
            plik_ust << snet;
            cout << "50%" << endl;
            plik_ust << endl;
            plik_ust << ust_logi;
            cout << "60%" << endl;
            plik_ust << endl;
            plik_ust << przedrostek_path;
            cout << "70%" << endl;
            plik_ust << endl;
            plik_ust << wczyt_kolor_dnia;
            cout << "80%" << endl;
            plik_ust << endl;
            plik_ust << datanap;
            cout << "90%" << endl;
            plik_ust.close();
        }
        else
        {
            errorlitsa();
        }

    cout << "100%" << endl;
}

bool zal_zapis_uat()
{
    zapas_zkolor = zkolor;
    fstream plik_ust;
    plik_ust.open("C:\\PlikiPomocnik\\Users\\" + nickname +"\\ustawienia.txt", ios::out);
        if(plik_ust.good()==true)
        {
            if(wczyt_kolor_dnia == false)
            {
               plik_ust << zapas_zkolor;
            }
            else
            {
                plik_ust << zkolor;
            }
            plik_ust << endl;
            plik_ust << snet;
            plik_ust << endl;
            plik_ust << ust_logi;
            plik_ust << endl;
            plik_ust << przedrostek_path;
            plik_ust << endl;
            plik_ust << wczyt_kolor_dnia;
            plik_ust << endl;
            plik_ust << datanap;
            plik_ust.close();
        }
        else
        {
            errorlitsa();
        }
}




