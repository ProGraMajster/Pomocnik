#include "logo.h"
#include "plik2.hpp"
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

#define PRODUCT_VERSION "1.1"

#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401

using namespace std;

HANDLE hOut;
HANDLE kolor;

wchar_t napis[1024] = L"polskie litery";
wchar_t kolor_slowo[1024] = L"kolor";

string odp; // zmienna bo poleceń
string odpbot; // zmienna do odpowiadania botowi
string nickname; // nazwa użytkownika po zalogowaniu
string pom;
string nkome;
string nazwa;
string komenda;
string imiep;
string tlumaczenie;
string ver = PRODUCT_VERSION;
string arg0global;
string arg1global;
string polecenie;
string pole_corep[3];
string schowek_programowy;

extern int zkolor;
int zkolor = 7; // zmania koloru czcinoki
int zapas_zkolor=7;

int kkom;
int sekundy;
int ile;
int pomoc;
int autostart;
int endloading;
int pozycja_fraza=0; //pozycja szukane frazy

int testzm;//
int sprprogramu=0; //sprawdzanie czy prgram był już włanczany na komputerze.

//char data[80];

time_t czas;
            struct tm * data;
            char godzina[ 80 ];
//==============
bool zalogowany = false;
bool snet = true; /// zmianna od funkcji
bool debugowanie = false;
bool ust_logi = true; /// logi zapisywane do Pomocniklog.txt
bool przedrostek_path = true; //
bool czysty_rozruch = false;
bool nowy_sys_zap_ust = true; /// nowy system zapisywania ustawień
bool czy_znaleziono_fraze = false;
bool przyp = true; //
bool wczyt_kolor_dnia = false; /// wczytywanie koloru zależny od dnia
bool datanap = true;
bool ist_corep = false; /// czy istnieje Core-P
bool flaga_d = false;
bool flaga_na_domyslne = true; /// od stanu tej flagi zależy czy przy wywołaniu funkcji program się później wyłączy
//=============== F-U-N-K-C-J-E =======================

extern bool rejestracja();

extern bool logowanie();

extern bool zalogowany_napisy_p();

extern bool zalogowany_kommendy();
//==============

int sprawdzanie_corep();

int wyjscie_corep();

int menu_opcje(string arg0);

int menu_opcje_info(string arg0);

int wczytywanie_ustawien();

//int opcje_zalogowany();

int zapis_plik_ustawien();

int zm_opc_snet();

int zm_opc_logi(); // funkcja do ustawianie opcji od logów

int zm_opcji_programu();

int beta_opcje();

int na_domyslne();
//=-=-=-=-=-=-=-=-=-=-=-=
int kodowanie_max(char *napis);
int dekodowanie_max(char *napis);

string & rozmiar_pliku(string & path);

bool czy_spolgloska(char litera)
{
	//sprawdzamy czy samogłoska - jest ich mniej
	switch(litera)
	{
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
		case 'y':
			return 0;
	}
	return 1;
}

int kodowanie(char *napis)
{
	int dl = strlen(napis); //wyznaczenie liczby znaków

	//należy zapamiętać pozycję pierwszej spółgłoski
	bool f=1;	//czy dana spółgłoska jest pierwsza
	int nr; 	//pozycja pierwszej spółgłoski
	char first;	//przechowujemy spółgłoskę do podmiany

	for(int i=0;i<dl;i++)
		{
			if(czy_spolgloska(napis[i]))
			{
				if(f)	//jesli wczytana spółgłoska jest pierwsza
				{		//to ją spamiętujemy
					nr = i;
					first = napis[i];
					f = 0;
				}
				else //podmiana
				{
					char pom = napis[i];
					napis[i] = first;
					first = pom;
				}
			}

		}
		if(!f)
			napis[nr] = first;

            int zakres = strlen(napis);
    return napis[zakres];
}

int dekodowanie(char *napis)
{
	int dl = strlen(napis); //wyznaczenie liczby znaków

	//należy zapamiętać pozycję pierwszej spółgłoski
	bool f=1;	//czy dana spółgłoska jest pierwsza
	int nr; 	//pozycja pierwszej spółgłoski
	char first;	//przechowujemy spółgłoskę do podmiany

	for(int i=dl-1;i>=0;i--)
		{
			if(czy_spolgloska(napis[i]))
			{
				if(f)	//jesli wczytana spółgłoska jest ostatnia
				{		//to ją spamiętujemy
					nr = i;
					first = napis[i];
					f = 0;
				}
				else //podmiana
				{
					char pom = napis[i];
					napis[i] = first;
					first = pom;
				}
			}

		}
		if(!f)
			napis[nr] = first;


int zakres = strlen(napis);
    return napis[zakres];
}

int wstep_docore();

int docorep();

int zapytanie()
{
    setlocale(LC_ALL, "polish"); // mówimy, że chcemy, by wszystkie napisy były konwertowane do oem
    wchar_t napis[1024] = L"W czym mogę jeszcze pomóc?";
    wprintf(L"%s", napis);
    cout << endl;
}

string tlumaczenie_j( int stoplinia )
{
                int liniapliku=0;// zmienna okreœlaj¹ca po³o¿enie kursora na wierszu w pliku tekstowym
     string tekst;
     fstream plik_jezyk;

    plik_jezyk.open ("C:/PlikiPomocnik/jezyk_x.txt", std::ios::in | std::ios::out);
            if(plik_jezyk.good() == true )
            {
                while(!plik_jezyk.eof())
                {
                    std::getline(plik_jezyk, tekst); //wczytywanie linijki tekstu
                        liniapliku ++;

                        if(stoplinia == liniapliku)
                        {
                            tekst = tlumaczenie;
                            if(liniapliku > stoplinia)
                            {
                                break; // koniec pêtli

                            }

                        }
                }
        plik_jezyk.close();
            }
            else
            {
             cout << "error" << endl;
            }
}
//-------------------------------------------------------
int errorlitsa();

int loading()
{
    std::cout << '-' << std::flush;
    for (;;) {
        Sleep(100);
        std::cout << "\b\\" << std::flush;
        Sleep(100);
        std::cout << "\b|" << std::flush;
        Sleep(100);
        std::cout << "\b/" << std::flush;
        Sleep(100);
        std::cout << "\b-" << std::flush;
        if(endloading == 1)
        {
            cout << "loading completed" << endl;
            break;
        }
    }
}

int log()
{
    if( ust_logi == true )
    {
      string kom;
        kom = odp;
        fstream pliklog;
        time_t czas;
        time(&czas);

        mkdir("C:/PlikiPomocnik");
        pliklog.open("C:/PlikiPomocnik/Pomocniklog.txt", ios::out |  ios_base::app);
        if(pliklog.good() == true)
        {
            pliklog <<asctime(localtime(&czas))<< "|> Użyto komendy:"<< kom <<endl;
            pliklog << "|";
            pliklog.close();
        }
        else
        {
            errorlitsa();
        }
    }

}

int stalematematyczne()
{
    cout<<setprecision(20);
    wcsncpy(napis, L"[ M_E      ] Podstawa logarytmów naturalnych | Stała Eulera e: ", 1024);
    wprintf(L"%s", napis);
    cout << M_E <<endl;
    wcsncpy(napis, L"[ M_LOG10E ] Logarytm do podłoża 10z M_E: ", 1024);
    wprintf(L"%s", napis);
    cout << M_LOG10E << endl;
    cout << "[ M_LOG2E  ] Logarytm do podloza 2z M_E: " << M_LOG2E << endl;
    cout << "[ M_LN2    ] Logarytm naturalny 2: " << M_LN2 << endl;
    cout << "[ M_LN10   ] Logarytm naturalny 10: " << M_LN10 << endl;
    cout << "[ M_PI     ] Pi, stosunek obwodu kola do jego srednicy: " << M_PI << endl;
    cout << "[ M_PI_2   ] Pi podzielone przez dwa: " << M_PI_2 << endl;
    cout << "[ M_PI_4   ] Pi podzielone przez cztery: " << M_PI_4 << endl;
    cout << "[ M_1_PI   ] Odwrotnosc pi (1 / pi): " << M_1_PI << endl;
    cout << "[ M_2_PI   ] Dwa razy odwrotnosc pi: " << M_2_PI << endl;
    cout << "[ M_2_SQRTPI ] Dwukrotnie odwrotnosc pierwiastka kwadratowego z pi: " <<M_2_SQRTPI << endl;
    cout << "[ M_SQRT2  ] Pierwiastek kwadratowy z dwoch: " << M_SQRT2 << endl;
    cout << "[ M_SQRT1_2 ] Odwrotnosc pierwiastka kwadratowego z dwoch (takze pierwiastek kwadratowy z 1/2): " << M_SQRT1_2 << endl;
}

char *tr(char *str)
{
    static char buff[256];
    char cp[]="\245\206\251\210\344\242\230\276\253\244\217\250\235\343\340\227\275\215¹æê³ñóœ¿Ÿ¥ÆÊ£ÑÓŒ¯";
    if(strlen(str)>=sizeof(buff))
        return str;
    char *bf=buff;
    while(*str)
    {
        char *pos=strchr(cp+18,*str);
        *(bf++)=pos?*(pos-18):*str;
        ++str;
    }
    *bf=0;
    return buff;
}

bool zainstaluj( char * miejsce )
{
    /* DODAWANIE DO REJESTRU */
    HKEY klucz;
    LONG Wynik;
    DWORD Nowy;
    const BYTE * lpData =( const BYTE * ) "C:\\WINDOWS\\Pomocnik.exe";
    Wynik = RegCreateKeyEx( HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, & klucz, & Nowy );
    if( Wynik == ERROR_SUCCESS )
    {
        RegSetValueEx( klucz, "Pomocnik", 0, REG_SZ, lpData, 256 );
        RegCloseKey( klucz );

        autostart = 1;
        ofstream plik;
        mkdir("C:/PlikiPomocnik");
        plik.open ("C:/PlikiPomocnik/autostart.txt");
        plik << autostart;
        plik.close();
    }
    else
    {
        return false;
    }
    return true;
}

int zmianakoloru()
{
    if(zalogowany == true)
    {
        zal_zapis_uat();
    }
    else
    {
        if(nowy_sys_zap_ust == true )
        {
            zapis_plik_ustawien();
        }
        else
        {
        HANDLE kolor;
            fstream plik;

        mkdir("C://PlikiPomocnik");
        plik.open ("C://PlikiPomocnik//kolor.txt", ios::out);
        if(plik.good() == true)
            {
                plik << zkolor;
                plik.close();
            }
            else
            {
                errorlitsa();
            }
        }

    }
}

int Modulus(int iN, int iMod)
{
    int iQ = (iN/iMod);
    return iN - (iQ*iMod);
}

char GetChar(int iGenerator, char cBase, int iRange)
{
    return (cBase + Modulus(iGenerator, iRange));
}

int testy()
{
    if( AllocConsole() )
         MessageBoxA( NULL, "Utworzono konsolę", "Sukces", MB_ICONINFORMATION );
    else
         MessageBoxA( NULL, "Proces posiada już konsolę", "Błąd", MB_ICONEXCLAMATION );
}

int np_informacje()
{
    cout << "Pomocnik"<< endl;
        cout << "Wersja: " << ver << endl;
   cout << "Autor: ProGra Majster(Kiko)                  ";
}

int seperator()
{
    cout << "---------------------------------------------------------/" << endl;
}

int seperator_typ2()
{
    cout << "________________________________________________________/" << endl << endl;
}

int napisy_p() // napisy startowe |=| Przy pętli głównej
{
    if(zalogowany == true)
    {
        zalogowany_napisy_p();
    }
    else
    {
        system("cls");
    SetConsoleTitleA( "Pomocnik" );
        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 9 );
        np_informacje();
    if(datanap == true)
    {
        data_napisy_p();
    }

    cout<< endl;
    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
    seperator();
    cout << "Status: Niezalogowany" << endl;
    wcsncpy(napis, L"Wpisz 'pomoc' lub 'help' aby zobaczyć spis komend", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            if(przyp == true)
            {
                seperator();
                przypomnienie_odczyt();
            }
    seperator_typ2();
        cout << "Hej. Z tej strony Pomocnik" << endl;
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


}

//=========================-- wątek --=================================
void watek( void * dummy ) //wątek
 {
     mkdir("C:\\PlikiPomocnik\\Engine\\");
     int kon = 0;
        while(kon != 1)
        {
                fstream plik;
                plik.open ("c:\\PlikiPomocnik\\Engine\\plik_wymiany0.txt", ios::in | ios::out);
            if(plik.good() == true)
            {
                plik >> polecenie;
                plik.close();
            }
            else
            {
                kon=1;
            }
            Sleep(500);

            if(odp == "-end")
            {
                kon =1;
                cout << "koniec watku" << endl;
            }
        }
        _endthread();
 }


//======================================================================

void szukajWszystkichFraz( string & tekst, string szukanaFraza )
{
    int znalezionaPozycja = tekst.find( szukanaFraza );
    if( znalezionaPozycja == string::npos )
    {
        czy_znaleziono_fraze = false;
        return;
    }

    do
    {
        pozycja_fraza = znalezionaPozycja;
        znalezionaPozycja = tekst.find( szukanaFraza, znalezionaPozycja + szukanaFraza.size() );
        if(pozycja_fraza > 0)
        {
         czy_znaleziono_fraze = true;
        }
    } while( znalezionaPozycja != string::npos );


}

int aktualny_czas()
{
    time( & czas );
            data = localtime( & czas );
            int plik_data = strftime( godzina, 80, "%H:%M", data );
}


int main( int argc, char * argv[] )
{
    restart: // etykieta
        setlocale(LC_ALL, "polish"); // mówimy, że chcemy, by wszystkie napisy były konwertowane do oem

    WNDCLASSEX wincl;
    wincl.hIcon = LoadIcon( GetModuleHandle( NULL ), MAKEINTRESOURCE( 1234 ) );
    wincl.hIconSm = LoadIcon( GetModuleHandle( NULL ), MAKEINTRESOURCE( 1234 ) );
    LoadIcon( GetModuleHandle( NULL ), MAKEINTRESOURCE( 1234 ) );
    SetConsoleTitleA( "Pomocnik" );
    //--------------------------- v0.4
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // uchwyt standardowego wyjścia
            COORD c2; // struktura potrzebna do ustawienia rozmiarów bufora pamięci
            c2.X = 80; // szerokość na -- szerokości znaków
            c2.Y = 9999; // wysokość na -- wysokości znaków
            SetConsoleScreenBufferSize(handle, c2); // ustawia rozmiar bufora (wyświetlanego tekstu)
        SMALL_RECT sr; // struktura wykorzystywana do ustawienia rozmiaru okna
            sr.Left = 0; // na zero
            sr.Top = 0; // na zero
            sr.Right = c2.X-1; // szerokość o 1 mniejsza od bufora
            sr.Bottom = c2.Y-1; // wysokość o 1 mniejsza od bufora
        SetConsoleWindowInfo(handle,true,&sr); // ustawia rozmiar okna (jednostka to szerokość i wysokość pojedynczego znaku)
    //=========================================================
    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
    if(argc > 1)
    {
        string arg1(argv[1]);
            if(arg1 == "-debug")
            {
                debugowanie = true;
            }
    }

    wcsncpy(napis, L"Kliknij dowolny przycisk!", 1024);
        wprintf(L"%s", napis);

    cout<< endl;
    int qwerty = getch();
             if( qwerty == '+')
                {
                 cout << "~" << endl;
                 string tryb;
                 cout << "./>";
                 cin  >> tryb;
                if(tryb == "1337" || tryb == "debug-on")
                {
                     cout << "Tryb aktywowany" << endl;
                     debugowanie = true;
                     cout << "debudowanie = true" << endl;
                     getch();

                }
                else if( tryb == "debug-off")
                {
                    cout << "Tryb debugowania dezaktywowany" << endl;
                     debugowanie = false;
                     cout << "debudowanie = false" << endl;
                     getch();
                }
                else if (tryb == "-r")
                {
                     czysty_rozruch = true;
                    cout << "czysty_rozruch = true" << endl;
                     cout << ": " << czysty_rozruch << endl;
                     getch();
                }
                else if(tryb == "-nowysystem")
                {
                     nowy_sys_zap_ust = true;
                }
                else if( tryb == "-twardyreset")
                {
                    //
                }
                else if(tryb == "restart_ustawien" || tryb == "rs_ust")
                {

                }
//                else
//                 {
//                     goto dalej;
//                 }
                }
    zalogowany = false;
            if(qwerty == 'l')
            {
                logowanie();
                goto dalej;
            }
        dalej: //etykieta


    //==================== Wczytywanie plików ==============================
                    wcsncpy(napis, L"Wczytywanie plików... 0%", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
    //-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if(zalogowany == false)
    {
        char acUserName [100];
        DWORD nUserName = sizeof (acUserName);
            if (GetUserName (acUserName, & nUserName)) {
                    nickname = acUserName;
                    if(debugowanie == true)
                    {
                        cout << "User: " << nickname << endl;
                    }
                }
    }




        if (access("C:\\Core-P\\App", F_OK) == 0)
        {
            // jeżeli plik istnieje to funkcja access zwróci 0 i instrukcje w warunku sie wykonają
            fstream plik_corep;
            plik_corep.open("C://Core-P//App//Pomocnik.txt", ios::out ); // zapisywanie pliku
            if(plik_corep.good() == true )
            {
                plik_corep << argv[0];
                ist_corep = true;
            }
            else
            {
                if(debugowanie == true)
                {
                    errorlitsa();
                    getch();
                }
            }
        }
        else
        {
            if(debugowanie == true)
            {
                cout << " nie znaleziono folderu | path = C:\\Core-P\\App" << endl;
            }
        }

    // plik od którego zależy system zapisywania ustawień
        if(czysty_rozruch == false)
        {
            if(debugowanie == true)
            {
                cout << "Otwieranie pliku: C://PlikiPomocnik//plik_ust_z_p.txt" << endl;
            }
            fstream plik_sys_z; // plik od którego zależy system zapisywania ustawień
        plik_sys_z.open("C://PlikiPomocnik//plik_ust_z_p.txt", ios::in );
            if(plik_sys_z.good() == true )
            {
                if(debugowanie == true)
                {
                    cout << "Sukces! Otwarto plik!" << endl;
                }
                string poflaga;
                plik_sys_z >> poflaga;
                if(poflaga == "1")
                {
                    nowy_sys_zap_ust = true;
                }
                else if (poflaga == "0")
                {
                    nowy_sys_zap_ust = false;
                }
                else
                {
                    if(debugowanie == true)
                    {
                        SetConsoleTextAttribute( kolor, 12 );
                        wcsncpy(napis, L"Złe dane!", 1024);
                        wprintf(L"%s", napis);
                     cout<< endl;
                     SetConsoleTextAttribute( kolor, zkolor );
                     getch();
                    }
                }
                plik_sys_z.close();

                if(debugowanie == true)
                {
                    cout << "nowy_sys_zap_ust: " << nowy_sys_zap_ust << endl;
                    getch();
                }
            }
            else
            {
                if(debugowanie == true)
                {
                    errorlitsa();
                    cout << "Tworzenie pliku: plik_ust_z_p.txt" << endl;
                }

                        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( kolor, 7 );
                plik_sys_z.open("C:/PlikiPomocnik/plik_ust_z_p.txt", ios::out );
                if(plik_sys_z.good() == true )
                {
                    plik_sys_z << "0";
                    nowy_sys_zap_ust = false;// ustawienie flagi
                }
                else
                {
                    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
                    SetConsoleTextAttribute( kolor, 12 );
                    if(debugowanie == true)
                    {
                        errorlitsa();
                        wcsncpy(napis, L"Coś poszło nie tak... :(", 1024);
                        wprintf(L"%s", napis);
                        cout << endl;
                        SetConsoleTextAttribute( kolor, zkolor );
                        getch();
                    }
                    SetConsoleTextAttribute( kolor, zkolor );
                }
                plik_sys_z.close();
            }
        }


        wcsncpy(napis, L"Wczytywanie plików... 20%", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    if(nowy_sys_zap_ust == false)
    {
        if(debugowanie == true)
            {
                cout << endl << ">-----------------------------------------------" << endl;
                cout << "C://PlikiPomocnik//ust_p.txt" << endl;
            }
        fstream plik_ust_p;
        plik_ust_p.open("C://PlikiPomocnik//ust_p.txt", ios::in );
        if(plik_ust_p.good() == true )
        {
            if(debugowanie == true)
                {
                    cout << "Sukces! Otwarto plik!" << endl;
                }
            string stan; // zmienna do przechowywania zawartości z pierszej lini pliku ust_p.txt
            plik_ust_p >> stan;
            if(stan == "1")
            {
                ust_logi = true;
            }
            else if( stan == "0")
            {
                ust_logi = false;
            }
            else
            {
                SetConsoleTextAttribute( kolor, 12 );
                if(debugowanie == true)
                {
                    wcsncpy(napis, L"Nieprawidłowa wartość w pliku: ust_p.txt", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                    getch();
                }

                SetConsoleTextAttribute( kolor, zkolor );
            }
            plik_ust_p.close();
            system("cls");
        }
        else
        {
            if(debugowanie == true)
            {
                wcsncpy(napis, L"Ne udało się wczytać pliku", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                system("pause");
                system("cls");
                wcsncpy(napis, L"Tworzenie pliku: ust_p.txt", 1024);
                wprintf(L"%s", napis);
                cout << endl;
            }
            fstream plik_ust_p2;
            plik_ust_p2.open("C://PlikiPomocnik//ust_p.txt", ios::out ); // zapisywanie pliku
            if(plik_ust_p2.good() == true )
            {
                ust_logi = true;
                plik_ust_p2 << "1";
            }
            else
            {
                SetConsoleTextAttribute( kolor, 12 );
                if(debugowanie == true)
                {
                    wcsncpy(napis, L"Wystąpił bład! ;(", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                }
                SetConsoleTextAttribute( kolor, zkolor );
            }
            plik_ust_p2.close();
        }

        if(debugowanie == true)
        {
            cout << "ust_logi: " << ust_logi << endl;
            getch();
        }
    }

    wcsncpy(napis, L"Wczytywanie plików... 40%", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;

    if(nowy_sys_zap_ust == false)
    {
         //=========================- Wczytywanie pliku opcja_spr_int.txt -=====
        wczytywanie_op_snet_star_sys();
    }
//====================================================================================================

        wcsncpy(napis, L"Wczytywanie plików... 50%", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;

        odp="odp";
    clock_t start, stop;
    //-=-=
    //==============================================================================================================================
    //--------------------------------WCZYTYWANIE KOLORU----------------\/
    if(nowy_sys_zap_ust == false)
    {
        wczytywanie_koloru();
    }
    //===========================================================
    // ---- wczytywanie new
    if(nowy_sys_zap_ust == true)
    {
        wczytywanie_ustawien();
    }

    wcsncpy(napis, L"Wczytywanie plików... 60%", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;

    if(debugowanie == true)
    {
        getch();
    }

    wcsncpy(napis, L"Wczytywanie plików... 80%", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
    //==============================================================================================================================
    string linia;
    fstream pliklog;
    time_t czas;
    time(&czas);
    mkdir("C://PlikiPomocnik");
    if(ust_logi==true)
    {
        pliklog.open("C:/PlikiPomocnik/Pomocniklog.txt", ios::out |  ios_base::app);
        if(debugowanie==true)
            {
                cout << "Otwieranie pliku: C:/PlikiPomocnik/Pomocniklog.txt" << endl;
            }
        if(pliklog.good() == true)
        {
            if(debugowanie==true)
            {
                cout << ">Otwarto pomyslnie plik: C:/PlikiPomocnik/Pomocniklog.txt | Otwarto pomyslnie" << endl;
            }
        pliklog <<"-"<<asctime(localtime(&czas))<< " Aktywacja programu"<<endl;
        pliklog.close();
            if(debugowanie==true)
            {
                cout << "Zamekanie pliku: C:/PlikiPomocnik/Pomocniklog.txt" << endl;
                system("pause");
            }
        }
        else
        {
            cout << "Error" <<endl;
        }
    }

    //----------------------------
    if(nowy_sys_zap_ust == false)
    {
        fstream plik_kolordnia;
       plik_kolordnia.open("C:\\PlikiPomocnik\\kolor_dnia_ust.txt", ios::in );
        if(plik_kolordnia.good() == true )
        {
            string stan;
           plik_kolordnia >> stan;
            if(stan == "1")
            {
                wczyt_kolor_dnia = true;
            }
            else if( stan == "0")
            {
                wczyt_kolor_dnia = false;
            }
            else
            {
                if(debugowanie == true)
                {
                    SetConsoleTextAttribute( kolor, 12 );
                    wcsncpy(napis, L"Nieprawidłowa wartość w pliku: ust_p.txt", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                    SetConsoleTextAttribute( kolor, zkolor );
                    getch();
                }
            }
            plik_kolordnia.close();
            system("cls");
        }
    }
    wcsncpy(napis, L"Wczytywanie plików... 100%", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;

    if(snet == true)
    {
        system("cls");
        spr_polaczenia_inter();
    }
    else
    {
        system("cls");
    }
//=+===++++++++====+++++++++++++++++++=======================
    napisy_p();
//------------------------------------------------------
//------------- Obsługa argumentu argv 1 --- Otwórz za pomocą----------
    bool czy_jest_arg1 = false;
           if (argc > 1)
            {
                string rozsz;
                string arg1(argv[1]);
                arg1global = argv[1];
                string spra; //
                int dlugosc = arg1.size();

                spra.insert(0, arg1, 1, 2);

                if(debugowanie==true)
                    {
                        cout << "dl  > arg1 : " << dlugosc << endl;
                        cout << "Zmienna arg1: " << arg1 << endl;
                        cout << "Zmienna spar: " << spra << endl;
                    }

                if(spra == ":\\" || spra == ":\\")
                {
                    cout << "Otwieranie pliku z: " << arg1 << endl;
                    odczytywanie_pliku(arg1);
                }
                else
                {
                    czy_jest_arg1 = true;
                }

                if(arg1 == "-debug")
                {
                    debugowanie = true;
                }
            }
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    string sprodp="";
    string koncowka="";
    cin.clear();
    bool wp_kome = false;
    int rozmowa = 0;
    while(1)
    {

        //cin >> odp;
        odp;
        getline(cin, odp);
        sprodp.insert(0 , odp, 0, 3);
        komendy_testy(odp);
        if(zalogowany == true)
        {
            zalogowany_kommendy();
        }

        if(sprodp=="C:\\" || sprodp == "D:\\")
        {
            ShellExecute(NULL, "open", odp.c_str(),
                         NULL, NULL, SW_SHOWNORMAL);
        }
        sprodp="";
        /*
        szukajWszystkichFraz( odp, " " );

        if(czy_znaleziono_fraze == true)
        {
           koncowka.insert(0, odp, pozycja_fraza, 3);
            if(koncowka == " /?")
            {
                cout << "help /?" << endl;
            }
            koncowka = "";
        }
        */
        //===========
        if(wp_kome == true)
        {
            odp = arg1global;
            wp_kome = false;
        }
    //------------------------------------------------------------

        if(flaga_d == true && rozmowa == 5)
        {

        }

        if(odp == "Hej" || odp == "hej" )
        {
            cout <<"Witaj" <<endl;
        }

        if(odp == "jak jest dziś pogoda" || odp == "jak jest dziś pogoda?")
            {
                 wcsncpy(napis, L"już pokazuje :)", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                ShellExecute(NULL, "open", "https://www.google.com/search?biw=1366&bih=657&ei=53TEXLK8AYTPrgTL5rzACQ&q=pogoda&oq=po&gs_l=psy-ab.1.0.0i131i67i70i256j0i67l2j0i131i67j0i67l2j0i131i67j0i131l2j0i131i67.29323.30119..32528...0.0..0.89.162.2......0....1..gws-wiz.....0..0i71j0.DIWzSTeQql0",
                             NULL, NULL, SW_SHOWNORMAL);
                 zapytanie();
            }

        if(odp == "porozmawiamy?" || odp == "pogadamy?" || odp == "porozmawiamy" || odp == "pogadamy")
            {
                srand( (unsigned)time( NULL ) );
                int los, max=4;
                los=rand() % max;

                if(los==0)
                {
                    cout<< "Dobrze" << endl;
                    cout << "To na jaki temat pogadamy?"<< endl;
                }

                if(los==1)
                {
                    cout << "Pewnie. Na jaki temat?" << endl;
                }

                if(los==2)
                {
                    wcsncpy(napis, L"OK. O czym chcesz porozmawiać? Na jaki temat?", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                }

                if(los==3)
                {
                    wcsncpy(napis, L"Oczuwiście.", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                    cout << "Na jaki temat?" << endl;
                }


            }
        /*---/\---
        -----||---
        ---- rozmowa  ---------------------------------------------------------------------------------|
        */

        if (odp == "end"|| odp == "End" || odp == "Koniec" || odp == "koniec" || odp == "exit") // Odp koniec
        {

            //----------------------------------------
            system("cls");

            time_t czas;
            time(&czas);

        wcsncpy(napis, L"Dziekuję za wybranie mojego programu!", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
            cout << ".";
        //=========================
        if(ust_logi == true )
        {
             mkdir("C:/PlikiPomocnik");
            pliklog.open("C:/PlikiPomocnik/Pomocniklog.txt", ios::out |  ios_base::app);
            if(pliklog.good() == true)
            {
                cout << ".";
                pliklog <<asctime(localtime(&czas))<< "| Zamekanie programu"<< endl<< endl;
                pliklog.close();
            }
            else
            {
                errorlitsa();
            }
        }

            //----------------------------------------
            cout << ".";
            exit( 0 );
            return 0;
        }
        else if(odp=="PlikiPomcnik" || odp == "plikipomocnik")
        {
            ShellExecute(NULL, "open", "c:\PlikiPomocnik",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if(odp == "zkolor") // kolory
        {
            wstep_zmiania_koloru();
        }
        else if(odp == "zkolordnia")
        {
            log();
            zapisywanie_koloru_dnia();
        }
        else if(odp == "ztlo" )
        {
            cout << "Wpisz liczbe";
            cin >> zkolor;
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
            SetConsoleTextAttribute( kolor, zkolor );
        }
        else if(odp=="krkomendy")
        {
            cout<< endl <<"krotkie komendy co robia?"<< endl << "A ulatwia ci korzystanie z programu."<< endl;
            cout << "Czy chcesz wlaczyc krotkie komendy? Odpowiedz tak albo nie" << endl;

            cin >> odp;

            if(odp == "tak"|| odp =="Tak")
            {
                kkom =1;
                cout << "Krotkie komendy zostaly wlaczone." << endl;
            }
            if(odp == "nie" || odp == "Nie")
            {
                cout << "Krotkie komendy nie zostaly wlaczone." << endl;
            }

        }
        else if(kkom == 1)
        {
            if(odp == "MM" || odp == "mm")
            {
                ShellExecute(NULL, "open", "MovieMaker",
                             NULL, NULL, SW_SHOWNORMAL);
                cout << "w czym moge jeszcze pomoc ?" << endl;
                log();
            }

        }
        else if(odp =="MovMak")
        {
            ShellExecute(NULL, "open", "MovieMaker",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if(odp=="restart")
        {
            system("cls");
            log();
            main( argc, argv);
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
            SetConsoleTextAttribute( kolor, zkolor);

        }
        else if(odp=="clear" || odp == "cls")
        {
            system("cls");
            log();
            napisy_p();
        }
        else if(odp=="ff"||odp=="FF" ||odp=="firefox")
        {
            ShellExecute(NULL, "open", "firefox",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if(odp == "help" || odp == "pomoc") //==============-H-E-L-P-=============
        {
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
            SetConsoleTextAttribute( kolor, 10 );
            cout << "------------------------------------------------" << endl;
                wcsncpy(napis, L"cmd - Otwiera konsole cmd", 1024); // cmd
            wprintf(L"%s", napis);
            cout << endl;
                wcsncpy(napis, L"gmail - otwiera stronę gmail", 1024); // gmail
            wprintf(L"%s", napis);
            cout << endl;
            cout << "notatnik - otwiera notatnik" <<endl; // notatnik
            cout << "wordpad - otwiera wordpad'a" <<endl; // wordpad
            cout << "calc - otwiera kalkurator" << endl; // calc

            wcsncpy(napis, L"pogoda - otwiera stronę inter. z pogoda", 1024); // pogoda
            wprintf(L"%s", napis);
            cout << endl;

            cout << "paint - otwiera paint'a" << endl; // paint

            wcsncpy(napis, L"youtube - otwiera stronę youtube.com", 1024); //youtube
            wprintf(L"%s", napis);
            cout << endl;

            cout << "explorer - otwiera explorrer'a" << endl;//explorer


            wcsncpy(napis, L"zkolor - zmienia kolor którym piszemy", 1024); //zkolor
            wprintf(L"%s", napis);
            cout << endl;

            cout << "MovMak - otwiera MovieMaker'a" << endl;//movemak

            cout << "restart - restartuje program" << endl;
            cout << "lupa - otwiera program lupa"<< endl;
            cout << "winrar - otwiera program WinRAR" << endl;
            wcsncpy(napis, L"facebook - otwiera strone facebook'a", 1024); // facebook
            wprintf(L"%s", napis);
            cout << endl;

            cout << "clear - czysci ekran programu" << endl;

            wcsncpy(napis, L"firefox - otwiera przeglądarkę Firefox", 1024); //firefox
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"google -otwiera stronę google.com", 1024); //google
            wprintf(L"%s", napis);
            cout << endl;
            //------KOMENDY WERSJA 0.3 -----------------------------------------\/
            wcsncpy(napis, L"Netflix - otwiera stronę Neflix'a", 1024); //netflix
            wprintf(L"%s", napis);
            cout << endl;

            wcsncpy(napis, L"snet - sprawdza połączenie z internetem", 1024); //snet
            wprintf(L"%s", napis);
            cout << endl;

            wcsncpy(napis, L"data - wyświetla aktualną datę", 1024); //data
            wprintf(L"%s", napis);
            cout << endl;

            wcsncpy(napis, L"gry - otwiera spis gier Pomocnika", 1024); //gry
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"nnotatka - tworzenie nowej notatki", 1024); //nowanotatka
            wprintf(L"%s", napis);
            cout << endl;

            wcsncpy(napis, L"rejestracja - rejestracja w programie pomocnik", 1024); //rejsetracja
            wprintf(L"%s", napis);
            cout << endl;

            wcsncpy(napis, L"logowanie - logujesz się na zajerestrowane konto w Programie Pomocnik", 1024); //logowanie
            wprintf(L"%s", napis);
            cout << endl;

            //------------------------------------------------------------------/\
            //----------- Komendy Wersja 0.4 --------

            wcsncpy(napis, L"onotataka - odczytuję wybranę notatkę", 1024); //onotatka
            wprintf(L"%s", napis);
            cout << endl;

            wcsncpy(napis, L"ulog - usuwa plik rejestru zdarzeń", 1024); //ulog
            wprintf(L"%s", napis);
            cout << endl;

            cout << "matrix - animacja" << endl;

            wcsncpy(napis, L"godzina - wyświetla aktualną godzinę", 1024); //godzina
            wprintf(L"%s", napis);
            cout << endl;

            //-----------Komendy Wersja 0.5 ----------------------
            cout << "kalp - wbudowany kalkultor Pomocnik" << endl;
            cout << "plikipomocnik - otwiera folder z plikami programu" << endl;

            wcsncpy(napis, L"nowakom - tworzenie wlasnych komend", 1024); //nowakom
            wprintf(L"%s", napis);
            cout << endl;

            wcsncpy(napis, L"okome - uzycie wlasnej komendy", 1024); //okome
            wprintf(L"%s", napis);
            cout << endl;

            cout << "muzyka - wbudowany odtwarzacz do muzyki"<< endl;
            //----------- KOMENDYWERSJA 0.6
                        wcsncpy(napis, L"wyszukaj -  otwiera przegldąrkę i wyszukuje podaną frazę.", 1024); //wyszukaj
            wprintf(L"%s", napis);
            cout << endl;

            //------------- KOMENDY WERSJA 0.7 -----------------

            wcsncpy(napis, L"opcje - informacje o programie i możliwości zmiany ustawień programu", 1024); // facebook
            wprintf(L"%s", napis);
            cout << endl;

            //------------- KOMENDY WERSJA 0.8 ------------------
            cout << "stoper - wbudowany stoper Pomocnik" << endl;

            //------------ KOMENDY WERSJA 0.9 -------------------
            wcsncpy(napis, L"zkolordnia - zmienia kolor którym piszemy zależnie od dnia", 1024); //zkolor
            wprintf(L"%s", napis);
            cout << endl;
            //---------------------------------------------------
            wcsncpy(napis, L"end lub koniec - zameka program.", 1024); //end
            wprintf(L"%s", napis);
            cout << endl;
            //----------------------------------------------------------
            wcsncpy(napis, L"autor - otwiera stronę autora", 1024); //autor
            wprintf(L"%s", napis);
            cout << endl;
            //========================================================================
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
            SetConsoleTextAttribute( kolor, 12 );
            if(ist_corep == true)
            {
                wcsncpy(napis, L"cp_arg - wstęp do wysłania polecenia do Core-P", 1024); //zkolor
                wprintf(L"%s", napis);
                cout << endl;
            }
            wcsncpy(napis, L"- - - Nowość - - -", 1024);
            wprintf(L"%s", napis);
            cout << endl;

            //----------- KOMENDY WERSJA 1.0 -------------------------------
            wcsncpy(napis, L"plikm - wyświetla menu z opcjami dotyczące plików", 1024); //zkolor
            wprintf(L"%s", napis);
            cout << endl;

            wcsncpy(napis, L"przypo - tworzenie/odczytywanie przypomnień.", 1024); //zkolor
            wprintf(L"%s", napis);
            cout << endl;

            cout << "------------------------------------------------" << endl;
            log();
             kolor = GetStdHandle( STD_OUTPUT_HANDLE );
            SetConsoleTextAttribute( kolor, zkolor );
            zapytanie();

        }
        else if(odp == "Netflix")
        {
            ShellExecute(NULL, "open", "https://www.netflix.com/browse",
                         NULL, NULL, SW_SHOWNORMAL);

            log();
            zapytanie();
        }
        else if (odp=="FB"||odp=="Fb"||odp=="fb"||odp=="facebook"|| odp=="Facebook")
        {
            ShellExecute(NULL, "open", "https://pl-pl.facebook.com/",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if(odp=="winrar" || odp=="WinRAR")
        {
            ShellExecute(NULL, "open", "WinRAR",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if(odp=="Lupa"|| odp=="lupa")
        {
            ShellExecute(NULL, "open", "Magnify",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if (odp == "cmd" || odp == "Cmd" || odp == "CMD")
        {
            ShellExecute(NULL, "open", "cmd",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if(odp == "Gmail" || odp=="gmail")
        {
            ShellExecute(NULL, "open", "https://accounts.google.com/signin/v2/identifier?service=mail&passive=true&rm=false&continue=https%3A%2F%2Fmail.google.com%2Fmail%2F&ss=1&scc=1&ltmpl=default&ltmplcache=2&emr=1&osid=1&flowName=GlifWebSignIn&flowEntry=ServiceLogin",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if (odp == "notatnik" || odp == "notepad") // otwiera systemowy notatnik
        {
            ShellExecute(NULL, "open", "notepad",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if (odp == "wordpad"|| odp == "Wordpad") // otwiera wordpad
        {
            ShellExecute(NULL, "open", "Wordpad",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if (odp == "kalkulator" || odp == "calc") // otwiera systemowy kalkulator
        {
            ShellExecute(NULL, "open", "calc",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if(odp == "pogoda"|| odp == "Pogoda") // otwiera przeglądarke na zapytaniu pogoda
        {
            ShellExecute(NULL, "open", "https://www.google.com/search?biw=1366&bih=657&ei=53TEXLK8AYTPrgTL5rzACQ&q=pogoda&oq=po&gs_l=psy-ab.1.0.0i131i67i70i256j0i67l2j0i131i67j0i67l2j0i131i67j0i131l2j0i131i67.29323.30119..32528...0.0..0.89.162.2......0....1..gws-wiz.....0..0i71j0.DIWzSTeQql0",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if (odp == "paint") // otwiera paint
        {
            ShellExecute(NULL, "open", "mspaint",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();;
        }
        else if (odp == "YT"|| odp == "yt" || odp == "youtube") // otwiera stronę youtube.com
        {
            cout << "ok"<<endl;

            ShellExecute(NULL, "open", "https://www.youtube.com/",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if (odp == "explorer") // otwiera exploler
        {
            ShellExecute(NULL, "open", "explorer",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if (odp == "google")// otwiera witrynę google.com
        {
            ShellExecute(NULL, "open", "https://www.google.pl/",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if(odp == "autor" || odp == "Autor") // strona autora
        {
            ShellExecute(NULL, "open", "https://sites.google.com/view/progra-majster",
                         NULL, NULL, SW_SHOWNORMAL);
            log();
            zapytanie();
        }
        else if (odp =="gry")//--------Mini gry ---------->
        {
            log();
            cout << "Spis gier" << endl;
            cout << "- - - - - - - " << endl;
            wcsncpy(napis, L"1 - Gra polega na odgadnięciu liczby z wybranego zakresu", 1024);
            wprintf(L"%s", napis);
                cout << endl;
            cin >>odp;

            if (odp =="1")
            {
                system("cls");
                wcsncpy(napis, L"1 - Gra polega na odgadnięciu liczby z wybranego zakresu", 1024);
            wprintf(L"%s", napis);
                cout << endl;
                srand( (unsigned)time( NULL ) );
                int liczba, los, max,i=0;
                cout<<"Podaj zakres : 0-";
                cin>>max;
                if (max==0)
                {
                    wcsncpy(napis, L"Nie możma ustawić maksymalnego zakres na 0", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                    getch();
                    main( argc, argv);
                }
                los=rand() % max;
                do
                {
                    wcsncpy(napis, L"Podaj liczbę: ", 1024);
                    wprintf(L"%s", napis);
                    cin>>liczba;
                    if(liczba>los)
                    {
                        wcsncpy(napis, L"Twoja liczba jest za duża.", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                    }
                    if(liczba<los)
                    {
                        wcsncpy(napis, L"Twoja liczba jest za mała.", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                    }
                    if(liczba==los)
                    {
                        cout << endl;
                        wcsncpy(napis, L"!!! Brawo !! Udało ci się odnaleźć liczbę", 1024);
                        wprintf(L"%s", napis);
                    cout << endl;
                     cout<< "Twoja liczba to:" <<los<<endl;
                    }
                    ++i;
                }
                while(liczba!=los);
                cout<<"Udalo Ci sie za "<<i<<" razem."<<endl;
                getch();
                napisy_p();
            }
            if(odp == "2")
            {
                //
            }

        }

//-------------------------------------------------------------------<
        if(odp =="nowanotatka" || odp == "nowa notatka"
           || odp == "nnotatka") // tworzy plik teskstowy
        {
            nnotatka();
        }

        if(odp== "odczytnotatki" || odp== "onotatka") // otwiera plik tekstowy
        {
            onotatka();
        }
//==========================================
        if(odp == "onotatka_s")
        {
            onotatka_szyf();
        }

        if (odp == "nnotatka_s")
        {
            nnotatka_szyf();
        }

        if(odp == "data") // wyświetla aktualną date
        {
            log();
            time_t czas;
            time(&czas);
            std::cout<<asctime(localtime(&czas));
            log();
        }

        if(odp == "snet" ) // sprawdza ołączenie z internetem
        {
            spr_polaczenia_inter();
            log();
        }

        if(odp == "ulog") // usuwanie pliku Pomocnik_log.txt
        {
            cout << "Chcesz usunac rejestr wydarzen ?" << endl;
            cout << "Jesli wybierzesz tak," << endl;
            cout << "to zadne logi az do wylaczenia programu nie beda zapisywane" << endl;
           // cout << "Po ponownym uruchomieniu programu logi beda normalnie zapisywane tak jaka wczesniej" <<endl;
            cout << "Pomocniklog.txt :";
            string sciezka = "C:\\PlikiPomocnik\\Pomocniklog.txt";
            rozmiar_pliku(sciezka);
            cout << "Odpowiedz tak lub nie." << endl;
            cin >> odp;
            if(odp=="tak"|| odp=="Tak")
            {
                cout << "ok juz usuwam."<<endl;
                remove("C:/PlikiPomocnik/Pomocniklog.txt");
                ust_logi = false;
            }
            if(odp=="Nie" || odp=="nie")
            {
                cout << "okej" << endl;
            }
        }

        if(odp == "stoper")
        {
            log();
            int kon =0;
            clock_t start, stop;
            wcsncpy(napis, L"Kliknij dowolny przycisk aby rozpocząć.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            getch();
            start = clock();
            wcsncpy(napis, L"Kliknij dowolny przycisk aby zatrzymać stoper.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            getch();

            stop = clock();

            long double czas = (long double)(stop-start)/ CLOCKS_PER_SEC;
            cout << "czas:"<< czas << "sek."<<endl;

        }

        if (odp == "mojekom")
        {
            cout << "Stworzone komendy:" <<endl;
            cout << "Nazwa komendy -> N: | Program otwierany przez komende -> P:" << endl << endl;

            string linia;
            fstream plik;

            plik.open("C:/PlikiPomocnik/lista_komend.txt", ios::in);
            if(plik.good() == true)
            {
                while(!plik.eof())
                {
                    getline(plik, linia);
                    cout << linia << endl; //wyœwietlenie linii
                }
                plik.close();
            }
        }

        if(odp =="okomenda" || odp == "okome" )
        {
            log();
            string tekst;
            char kome[255];
            cout << "Wpisz nazwe komendy :";
            cin >> nazwa;
            nazwa += ".txt";
            string sciezka = "c:\\PlikiPomocnik\\Komendy\\";
            sciezka += nazwa;
            fstream plik;
            mkdir("c:\\PlikiPomocnik\\Komendy\\");
            plik.open( sciezka.c_str(), ios::in);
            if(plik.good()==true)
            {
                cin.clear();
                while(!plik.eof())
                    {
                        cin.clear();
                        getline(plik, tekst);
                        cout<< tekst << endl; //wyœwietlenie linii
                    }

                plik.close();
            }
            else
            {
                cout << "Nie mozna zapisac pliku" << endl;
            }
            //___________ Otwieranie_____________
            char polecenie[255];
                char zmienna[255];
                char zmienna2[255];

    int n = tekst.length();

    // declaring character array
    char char_array[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(char_array, tekst.c_str());
    strcpy(kome, char_array);

//=============================================================================================
                strcpy(zmienna, "cmd /S /C \"\"");         //przypisanie do zmiennej "zmienna" wartoœci
                strcpy(polecenie, kome);   //przypisanie do zmiennej "polecenie" wartoœci

                //strcat(polecenie,zmienna);      //po³¹czenie ci¹gu znaków (dopisanie do zmiennej "polecenie" wartoœci
                //ze zmiennej "zmienna"

                strcat(zmienna, polecenie);
                strcpy(zmienna2, "\"\"");
                strcat(zmienna, zmienna2);

                if(debugowanie == true)
                {
                    cout << "zmienna: " << zmienna << endl;
                    cout << "zmienna2: " << zmienna2 << endl;
                    cout << "polecenie: " << polecenie << endl;
                }
                system(zmienna);
                //system(polecenie);
                cin.clear();
                cin.sync();
        }

        if(odp == "stwórz nowa komende"|| odp == "nowakom" ||
            odp == "newkom" || odp == "nowa komenda" ) // tworzenie pliku z scieżką do programu, KOMENDA
        {
            log();
            cout << "Wpisz nazwe komendy :";
            cin >> nazwa;

            cout << "Wpisz sciezke do programu (Przykladowa sciezka C:\\windows\\system32\\notepad.exe) :" ;
            //cin >> komenda;
            cin.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );
            getline( cin, komenda );

            nazwa += ".txt";
            string sciezka = "c:\\PlikiPomocnik\\Komendy\\";
            sciezka += nazwa;
            fstream plik;
            mkdir("c:\\PlikiPomocnik\\Komendy\\");
            plik.open( sciezka.c_str(), ios::app );
            if(plik.good()==true)
            {
                plik << komenda;
                plik.close();
                cout << "Zapisano plik" << endl;
            }
            else
            {
                cout << "Nie mozna zapisac pliku" << endl;
            }
        }

        if(odp == "godzina" || odp == "?h") // wyswietla aktualną godzine
        {
            log();
            strftime( godzina, 80, "Teraz jest %H:%M.", data );
        }


        if(odp=="Kalkulator Pomocnik" || odp == "kalp") // własny kalkulator
        {
            log();
            kalp();
        }

//=========================- OPCJE PROGRAMU -===========================================================
        if(odp == "opcje" )
        {
            menu_opcje(argv[0]);
        }

//=======================-- Muzyka --==============================================================
        if(odp=="Muzyka" || odp == "muzyka" )
        {
            log();
                SetConsoleTitleA( "Pomocnik - Muzyka" );

            string path;
            system("cls");
            int wybor ; // zmienna do switch
            int potw; // potwierdzenie (koniec pętli)
            potw=0;
            while(potw!=1)
            {
                cout << "Muzyka" << endl;
                wcsncpy(napis, L"1 = Otwórz z podanej ścieżki do pliku (Tylko plik .wav)", 1024);
            wprintf(L"%s", napis);
                cout << endl;wcsncpy(napis, L"2 = Zatrzymaj odtwarzanie muzyki", 1024);
            wprintf(L"%s", napis);
                cout << endl;wcsncpy(napis, L"0 = Wyjście", 1024);
            wprintf(L"%s", napis);
                cout << endl;
                cin >> wybor;

                    if(wybor ==1)
                    {
                      system("cls");
                      cout << endl;
                      wcsncpy(napis, L"Podaj ścieżkę do pliku wav", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                    cout << "Np. C:\\PlikiPomocnik\\sound.wav" << endl;
                    cin >> path;
                    play_sound_path(path); // odwolanie do fynkicji
                    potw =1; // potwierdzenie zakonczenia pętli
                    getch();
                        SetConsoleTitleA( "Pomocnik" );
                        napisy_p();
                    }
                    if(wybor==2) // zatrzymywanie
                    {
                        cout << "Zatrzymuje odtwarzanie muzyki" << endl;
                         PlaySound(NULL, NULL, SND_ASYNC);
                         potw=1;
                             SetConsoleTitleA( "Pomocnik" );
                             getch();
                        odp=="clear";
                    }
                    if(wybor==0) // wyjscie
                    {
                        potw=1;
                        system("cls");
                            SetConsoleTitleA( "Pomocnik" );
                            napisy_p();
                    }

            }

                SetConsoleTitleA( "Pomocnik" );

        }

//================================================================================================

        //________________________________________________________

        if(odp =="cp_arg")
        {
            if (access("C:\\Core-P\\App", F_OK) == 0)
            {
                wstep_docore();
            }
            else
            {
                cout << endl;wcsncpy(napis, L"Nie wykryto rdzenia komunikacyjnego", 1024);
                wprintf(L"%s", napis);
                cout << endl;
            }

        }
    //=============================================================

        if(odp == "schowek_p")
        {
            cout << schowek_programowy << endl;
        }

        if(odp=="testw")
        {
            cout << "Test watek" <<endl;
            _beginthread( watek, 0, 0 );
                cout << "Wywolano watek" << endl;
        }

        if(odp == "test")
        {
           // MessageBox(NULL,"Test okna dialogowego","MessageBox",0x00000000L|0x00000040L|0x00000000L);

           cout << ">";
           cin >> odpbot;
           wp_kome = true;
           cout << endl;
        }

        if(odp == "plikm")
        {
            log();
            plik_menu();
        }

        if(odp == "test_t")
        {
                cout << ">";
            string tekst; //wprowadŸ dowolny tekst
            cin.get();
            getline(cin, tekst);
            for (int i = 0; i < tekst.length(); i++)  //pętla wykonuje sie od 0 do d³ugosci tekstu wprowadzonego w zmiennej tekst
            {
                cout << tekst[i]; //wyœwietlanie na ekranie po kolei ka¿dej litery
                Sleep(230); //tym regulujesz szybkoœæ pisania, wartoœæ w ms
            }
            cout << endl; //znak koñca linii
        }

        if(odp == "test4")
        {
            int liniapliku;
            liniapliku=0;
            fstream plik("plik.txt");
            string tekst;
            if(plik.good() == true)
            {
              while(!plik.eof())
                {
                liniapliku++;
                getline(plik, tekst);
                if(!(std::string::npos == tekst.find("Hej")))
                    std::cout << liniapliku<< ". " << "Znaleziono fraze"<< endl;
                else
                    std::cout << liniapliku<< ". " << "Nie znaleziono frazy"<< endl;
                }

            }
            else
            {
                cout << "nie znalezionp pliku" << endl;
            }

        }

        if(odp == "test5")
        {

        }

        if(odp == "nstdnote")
        {
            log();
            cout << "1 - tworzenie notatki , 2 - odzcztywanie notatki" << endl;
            cin >> odp;
            if(odp=="1")
            {
                        string rozsz ="";
                        string nazwa;
                        string notatka;
                        cin.clear();
                        cout << "Nazwa Notatki:";
                        cin >> nazwa;
                        cout << endl<< "Rozszezenie pliku: ";
                        cin >> rozsz;
                        cout << endl;
                        nazwa += rozsz;
                        cout << "Tresc notatki:" << endl;
                        cin >> notatka;


                        ofstream plikn;
                        plikn.open(nazwa.c_str(), ios::app );
                        cin.get();
                        plikn << notatka;
                        getline(cin, notatka);
                        plikn.close();
            }
            //------------
            if(odp=="2")
            {
                            string rozsz ="";
                            string notatka;
                            string nazwa;
                    cout << "Wpisz nazwe notatki ktora chcesz odczutac"<< endl;
                        cin >> nazwa;
                    cout << endl<< "Rozszezenie pliku: ";
                        cin >> rozsz;
                    cout << endl;
                        nazwa += rozsz;

                            string linia;
                        fstream plik;

                    plik.open( nazwa.c_str(), ios::in );
                    if(plik.good() == true)
                        {
                        cout << "Tresc notatki: " << endl;
                        while(!plik.eof())
                            {
                                getline(plik, linia);
                                cout<< linia << endl; //wyœwietlenie linii
                            }
                    plik.close();
                        }
                    else
                    {
                        errorlitsa();
                    }
            }
        }

        if(odp=="test_r")
        {
            if( rename( "C:\\PlikiPomocnik\\test.txtp", "C:\\PlikiPomocnik\\test.txt" ) == 0 )
            printf( "zmiana nazwy powiodla sie" );
            else
            printf( "zmiana nazwy nie powiodla sie" );
        }

        if(odp=="dodawanie_t")
        {
            long liczba1;
                long liczba2;

                cout << "Podaj liczbe." << endl;
                cin >> liczba1;
                cout << "Podaj kolejna liczbe." << endl;
                cin >> liczba2;
                long long wynik;
                wynik = dodajLiczby( liczba1, liczba2);
                cout << "Wynik dodawania to: " << wynik << endl;

        }

        if(odp=="test_okna")
        {
            testy();
        }

        if(odp=="testplik")
        {
            int numerstop;
            cout << "Lina stop:" << endl;
            cin >> numerstop;
                    string tekstt; //zmienna przechowuj¹ca tekst.
    fstream plikliniastop;
        int liniapliku=0;// zmienna okreœlaj¹ca po³o¿enie kursora na wierszu w pliku tekstowym
    plikliniastop.open ("C:\\PlikiPomocnik\\jezyk_x.txt", ios::in | ios::out);
            if(plikliniastop.good() == true )
            {
                while(!plikliniastop.eof())
                {
                    getline(plikliniastop, tekstt); //wczytywanie linijki tekstu
                        liniapliku ++;

                        if(numerstop == liniapliku)
                        {
                            cout << tekstt << endl;
                            if(liniapliku > numerstop)
                            {
                                break; // koniec pêtli
                            }

                        }
                }
                plikliniastop.close();
            }
            else
            {
                errorlitsa();
            }
        }

        if(odp=="startplik")
        {
            char kome[255];
            string cel;
            fstream plikstart;
            plikstart.open ("C:\\PlikiPomocnik\\Komendy\\mspaint.txt", ios::in | ios::out);
            if(plikstart.good() == true )
            {
                   plikstart >> kome;
                    plikstart.close();
            }
            else
            {
             cout << "error" << endl;
            }

            char polecenie[255];
                char zmienna[255];


                strcpy(zmienna, "");         //przypisanie do zmiennej "zmienna" wartoœci
                strcpy(polecenie, kome);   //przypisanie do zmiennej "polecenie" wartoœci

                strcat(polecenie,zmienna);      //po³¹czenie ci¹gu znaków (dopisanie do zmiennej "polecenie" wartoœci
                //ze zmiennej "zmienna"

                system(polecenie);
        }

        if(odp=="test_time")
        {
            SYSTEMTIME st;
            GetSystemTime(&st);
            cout << "Biezacy rok to " << st.wYear<< endl;
            cout << "Biezacy miesiac to " << st.wMonth<< endl;
            cout << "Biezacy dzien tygodnia to " << st.wDayOfWeek<< endl;
            cout << "Biezacy dzien  to " << st.wDay<< endl;
            cout << "Biezaca godzina  to " << st.wHour<< endl;
            cout << "Biezaca minuta  to " << st.wMinute<< endl;
            cout << "Biezaca sekunda  to " << st.wSecond<< endl;
        }

        if(odp=="test_wkdnia")
        {
          wczytywanie_koloru_dnia();
        }

        if(odp == "zrzut_zmiennyvh" || odp == "zrzut_zm")
        {
            cout << " Zrzut zmiennych globalnych." << endl;
            cout << "------------------------------" << endl;
            cout << "Zmienna odp >" <<  odp << endl; // zmienna bo poleceń
            cout << "Zmienna odpbot >" << odpbot << endl;  // zmienna do odpowiadania botowi
            cout << "hOut >" << hOut << endl;
            cout << "Zmienna zkolor >" << zkolor << endl;  // zmania koloru czcinoki
            cout << "Zmienna kkom >" << kkom << endl;
            cout << "Zmienna zalogowany >" << zalogowany << endl;
            cout << "Zmienna pom >" << pom << endl;
            cout << "Zmienna nkome >" << nkome <<endl;
            cout << "Zmienna nazwa >" << nazwa << endl;
            cout << "Zmienna komenda >" << komenda << endl;
            cout << "Zmienna imiep >" << imiep << endl;
            cout << "Zmienna tlumaczenie" << tlumaczenie << endl;
            cout << "Zmienna sekundy >" << sekundy << endl;
            cout << "Zmienna ile >" <<  ile << endl;
            cout << "Zmienna pomoc >" << pomoc << endl;
            cout << "Zmienna autostart >" << autostart << endl;
            cout << "Zmienna endloading >" << endloading << endl;
            cout << "Zmienna data >" << data << endl;
            cout << "Zmienna snet >" <<snet << endl; // zmianna od funkcji
            cout << "Zmienna testzm >" << testzm << endl;
            cout << "Zmienna sprprogramu >" << sprprogramu << endl; //sprawdzanie czy prgram był już włanczany na komputerze.
            cout << "Zmienna debugowanie >" << debugowanie << endl;
            cout << "Zmienna ust_log >" << ust_logi << endl;
            cout << "Zmienna arg0global >" << arg0global << endl;
            cout << "Zmienna nowy_sys_zap_ust >" << nowy_sys_zap_ust << endl;
        }
//===============================================================================================================


        if(odp == "przypo" || odp == "przypomnienie" || odp == "przypomnienia")
        {
            log();
            system("cls");
            wcsncpy(napis, L"Przypomnienia", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"0 - Wyjście", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"1 - Tworzenie przypomnienia", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"2 - Odczyt przypomnienia", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            cout << ">";
            cin >> odp;

            if(odp == "0")
            {
                napisy_p();
            }

            if(odp == "1")
            {
                przypomnienie_tworzenie();
            }

            if(odp == "2")
            {
                przypomnienie_odczyt();
            }
        }


        if(odp == "matrix") //motyw z matrix'a
        {
                log();
            cout << "INFO: ABY ZATRZYMAC MOTYW WCISNIJ 'q' !!!" << endl;
            Sleep(800);
            cout << "Zacznie siê za:"<< endl;
            Sleep(300);
            cout << "3"<<endl;
            Sleep(300);
            cout << "2"<<endl;
            Sleep(300);
            cout << "1"<<endl;
            int pkt = 0;

            // Color code
            HANDLE  hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);

            char caRow[80];
            int j = 7;
            int k = 2;
            int l = 5;
            int m = 1;
            while (true)
            {
                int i = 0;
                // Output a random row of characters
                while (i < 80)
                {

                    if( kbhit() )
                        if( getch() == 'q' )
                            goto restart;

                    if (caRow[i] != ' ')
                    {
                        caRow[i] = GetChar(j + i*i, 33, 30);
                        if (((i*i + k) % 71) == 0)
                        {
                            SetConsoleTextAttribute(hConsole,  7);
                        }
                        else
                        {
                            SetConsoleTextAttribute(hConsole,  2);
                        }
                    }
                    std::cout << caRow[i];
                    ++i;
                    SetConsoleTextAttribute(hConsole,  2);

                    //-=-=-==-===--=-=
                    ++pkt;
                    if(pkt == 100000)
                    {
                        cout << "  011001100110100101101110011001000010000001101101 01100101  ";
                        pkt = 0;
                    }
                    //-=-=-=-=

                }
                j = (j + 31);
                k = (k + 17);
                l = (l + 47);
                m = (m + 67);
                caRow[Modulus(j, 80)] = '-';
                caRow[Modulus(k, 80)] = ' ';
                caRow[Modulus(l, 80)] = '-';
                caRow[Modulus(m, 80)] = ' ';
                // Delay
                Sleep(10);
            }
        }


        if(odp =="benchmark")
        {
            cout << "1. CPU (jeden rdzen)" << endl;
            cin >> odp;
            if(odp == "1")
            {
                clock_t x,y;
                unsigned long long a = 0, b = 1;
                cout<<"CPU benchmark ..."<<endl;
                x=clock();
                for (int j=0; j<=9999999; j++)
                {
                    for(int i=0; i<90; i++)
                    {
                        b += a;
                        a = b-a;
                    }
                    a = 0, b = 1;
                }
                y=clock();
                cout<<"Czas "<<(long double)(y-x)/CLOCKS_PER_SEC<<" sekundy."<<endl;
            }

        }


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//--------------------------System rejestracji i logowania -----------------------------------------------------------------------
        if(odp == "rejestracja")
        {
            rejestracja();
        }

        if (odp == "logowanie")
        {
            logowanie();
        }

//--------------------------------------------
            if(odp == "polecenie systemowe" || odp == "cmdp")
            {
                log();
                char polecenie[255];
                char zmienna[255];
                char kome[255]= " ";

                cout << ">";
                cin >> kome;
                strcpy(zmienna, "/all");         //przypisanie do zmiennej "zmienna" wartoœci
                strcpy(polecenie, kome);   //przypisanie do zmiennej "polecenie" wartoœci

                strcat(polecenie,zmienna);      //po³¹czenie ci¹gu znaków (dopisanie do zmiennej "polecenie" wartoœci
                //ze zmiennej "zmienna"

                system(polecenie);

            }


        if(odp == "test_poru")
        {
            string sciezka1, sciezka2;
            cout << "1>";
            sciezka1;
            getline(cin, sciezka1);

            cout << endl;
            cout <<  "2>";

            sciezka2;
            getline(cin, sciezka2);
            if(debugowanie == true)
            {
                cout << "sciezka1: " << sciezka1 << "// sciezka2: " << sciezka2 << endl;
                getch();
            }

            porownywanie_zawartosci_plikow_full(sciezka1, sciezka2);
        }

        if(odp=="test_ustz")
        {
            cout << "Test nowego systemu zapisywania ustawien" << endl << endl;
            zapis_plik_ustawien();
        }

        if(odp == "test_ustw")
        {
            cout << "Test nowego systemu wczytywania ustawien" << endl << endl;
            wczytywanie_ustawien();
        }


        if(odp == "test_sz-on")
        {
            char napis[100];

        cout<<"Podaj napis do zaszyfrowania: ";
        cin.get(napis, 100);

        cout<<"Przed szyfrowaniem: ";
        cout<<napis<<endl;

        //szyfrujemy
        kodowanie(napis);

        cout<<"Szyfrogram: ";
        cout<<napis<<endl;
        //================================================================

        //szyfrujemy
        kodowanie(napis);

        cout<<"Szyfrogram: ";
        cout<<napis<<endl;
        //szyfrujemy
        kodowanie(napis);

        cout<<"Szyfrogram: ";
        cout<<napis<<endl;
        //szyfrujemy
        kodowanie(napis);

        cout<<"Szyfrogram: ";
        cout<<napis<<endl;
        //szyfrujemy
        kodowanie(napis);

        cout<<"Szyfrogram: ";
        cout<<napis<<endl;
        //szyfrujemy
        kodowanie(napis);

        cout<<"Szyfrogram: ";
        cout<<napis<<endl;
        //szyfrujemy
        kodowanie(napis);

        cout<<"Szyfrogram: ";
        cout<<napis<<endl;

        fstream plik;
        plik.open("C:\\PlikiPomocnik\\test.txt", ios::out);
        if(plik.good() == true)
        {
            plik << napis;
        }
        plik.close();
        plik.clear();

        /*//deszyfrujemy
        dekodowanie(napis);

        cout<<"Tekst jawny: ";
        cout<<napis<<endl;//deszyfrujemy
        dekodowanie(napis);

        cout<<"Tekst jawny: ";
        cout<<napis<<endl;//deszyfrujemy
        dekodowanie(napis);

        cout<<"Tekst jawny: ";
        cout<<napis<<endl;//deszyfrujemy
        dekodowanie(napis);

        cout<<"Tekst jawny: ";
        cout<<napis<<endl;
        //deszyfrujemy
        dekodowanie(napis);

        cout<<"Tekst jawny: ";
        cout<<napis<<endl;//deszyfrujemy
        dekodowanie(napis);

        cout<<"Tekst jawny: ";
        cout<<napis<<endl;
        //================================================================
        //deszyfrujemy
        dekodowanie(napis);

        cout<<"Tekst jawny: ";
        cout<<napis<<endl;*/

        cin.get();
        }
    }//petla while menu
    return 0;
} // int main

int zapis_plik_ustawien()
{
    wchar_t napis[1024] = L"Zapisywanie ustawień...";
    wprintf(L"%s", napis);
    cout << endl;
    if(debugowanie == true)
    {
        cout << "Kolor czcionki:" << zkolor << endl;
        cout << "Sprawdzanie polaczenia z inetr. po wlaczeniu programu:" << snet << endl;
        cout << "zapisywanie zdarzen do pliku (Pomocniklog.txt):" << ust_logi << endl;
        cout << "Szybkie wywolywanie z sciezki:" << przedrostek_path << endl;
        cout << "Kolor dnia:" << wczyt_kolor_dnia << endl;
        cout << "zapas_zkolor: " << zapas_zkolor << endl;
        system("pause");
    }

    fstream plik_ust; // plik ustawień
    plik_ust.open("C:\\PlikiPomocnik\\ustawienia.txt", ios::out);
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

int wczytywanie_ustawien()
{
    if(debugowanie == true)
    {
        cout << "Plik Ustawien || Przed wczytaniem" << endl;
        cout << "Kolor czcionki:" << zkolor << endl;
        cout << "Sprawdzanie polaczenia z inetr. po wlaczeniu programu:" << snet << endl;
        cout << "zapisywanie zdarzen do pliku (Pomocniklog.txt):" << ust_logi << endl;
        cout << "Szybkie wywolywanie z sciezki:" << przedrostek_path << endl;
        cout << "Kolor dnia:" << wczyt_kolor_dnia << endl;
        cout << "zapas_zkolor: " << zapas_zkolor << endl;
    }

    fstream plik_ust; // plik ustawień
    plik_ust.open("C:\\PlikiPomocnik\\ustawienia.txt", ios::in);
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
                getch();
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


int errorlitsa()
{
    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 12 );
    if(debugowanie==true)
    {
        cout << "Error:"<< strerror(errno)<< endl;
        getch();
    }
    if(debugowanie==false)
    {
        wchar_t napis[1024] = L"Ups.. Coś poszło nie tak!";
    wprintf(L"%s", napis);
    cout << endl;
    }

        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
}

int menu_opcje(string arg0)
{
    bool beta = false;
    int kon = 0;
                SetConsoleTitleA( "Pomocnik - Opcje" );
            while(kon!=1)
            {
                system("cls");
                SetConsoleTextAttribute( kolor, 9 );
                cout << "Opcje programu" << endl;
                SetConsoleTextAttribute( kolor, zkolor );
                cout << "Wpisz liczbe!"<< endl;

                wcsncpy(napis, L"0 - Wyjście z opcji programu.", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                cout << "1 - Informacje o programie i jego ustawieniach."<< endl;
                cout << "2 - Zmien opcje programu." << endl;
                //cout << "3 - Ustaw wszystko na domyslne" << endl;
                if(beta == true)
                {
                    cout << "9 - Ustawienia w wersji beta" << endl;
                }
                cout << ">";
                cin >> odp;
                if(beta == true )
                {
                    if(odp == "9")
                    {
                        kon = 1;
                        beta_opcje();
                    }
                }


                if(odp == "beta")
                {
                    beta = true;
                }

                if(odp == "0")
                {
                    kon=1;
                    napisy_p();
                }

                if(odp == "1")
                {
                    kon=1;
                    menu_opcje_info(arg0);
                }

                if(odp=="2") //Zmien opcje programu
                {
                    kon=1;
                    zm_opcji_programu();
                }

                if(odp == "3") // na domyślne
                {
                    kon =1;
                    na_domyslne();
                }
            }
            SetConsoleTitleA( "Pomocnik" );

}

// informacje o programie i ustawieniach | Opcje > 1
int menu_opcje_info(string arg0)
{
    SetConsoleTitleA( "Pomocnik - Opcje - Info" );
    arg0global = arg0;
    int kon=0;
    while(kon!=1)
    {
        system("cls");
        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );

    cout << "Informacje o programie i jego ustawieniach." << endl;
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );

            cout << "|==============================================================================|" << endl;
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
            cout << "Wersja programu: ";
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
            cout << ver << endl;
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7);
            cout << "Uruchomiono z: ";
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
            cout << arg0 << endl << endl;
    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
            cout << "Pomocniklog.txt \\/" << endl;
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
        string sciezka ="C:\\PlikiPomocnik\\Pomocniklog.txt";
        rozmiar_pliku(sciezka);
        cout << "------------------------------------------------{ " << endl;
        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
        wcsncpy(napis, L"Użytkownik: ", 1024);
            wprintf(L"%s", napis);
        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
    cout << nickname << endl;

        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
        cout << "Kolor ustawiony na: ";
        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
    cout << zkolor << endl;
    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
    //======================================
    wcsncpy(napis, L"Sprawdzanie połocznia z intrnetem przy właczaniu programu: ", 1024);
            wprintf(L"%s", napis);
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
            if(snet == true)
            {
                cout << snet;
                wcsncpy(napis, L" = Włączone.", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
            }
            else if(snet == false)
            {
                cout << snet;
                wcsncpy(napis, L" = Wyłączone.", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
            }
            else
            {
                cout << "Error" << endl;
            }

            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
    wcsncpy(napis, L"Zapisywanie zdarzeń do pliku: ", 1024);
            wprintf(L"%s", napis);
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
    // =============== LOGI =======================
            if(ust_logi == true)
            {
                cout << ust_logi;
                wcsncpy(napis, L" = Włączone.", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
            }
            else if(ust_logi == false)
            {
                cout << ust_logi;
                wcsncpy(napis, L" = Wyłączone.", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
            }
            else
            {
                cout << "Error" << endl;
            }
// =================================================
    if(debugowanie == true) // do zamiany w wersji 1.0
    {


            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
    wcsncpy(napis, L"System zapisywania ustawień: ", 1024);
            wprintf(L"%s", napis);
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
        if(nowy_sys_zap_ust == true)
        {
            cout << "1 = Nowy" << endl;
        }
        else if(nowy_sys_zap_ust == false)
        {
            cout << "0 = Stary" << endl;
        }
        else
        {
            cout << "Error" << endl;
        }
    }
//----------
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
            cout << "Stan funkcji kolor dnia: ";
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
            if(wczyt_kolor_dnia == true)
            {
                cout << wczyt_kolor_dnia;
                wcsncpy(napis, L" = Włączone.", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
            }
            else if(wczyt_kolor_dnia == false)
            {
                cout << wczyt_kolor_dnia;
                wcsncpy(napis, L" = Wyłączone.", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
            }

            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 7 );
            cout << endl << "Autor: ProGra Majster(Kiko)" << endl;
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zkolor );
        //---------------------
        cout << "|==============================================================================|" << endl;
        cout << "Wpisz liczbe" << endl;
        cout << "0 - Wyjscie z opcji programu" << endl;
        cout << "9 - Powrot do menu opcji" << endl;
        cin >> odp;
        if(odp == "0")
        {
            kon = 1;
            napisy_p();
        }

        if(odp == "9")
        {
            kon = 1;
            menu_opcje(arg0);
        }
    }
}

int zm_opcji_programu()
{
    int kon = 0;
        while(kon != 1)
            {
                system("cls");
                    cout << "Opcje:"<< endl;
                wcsncpy(napis, L"0 - Powrót", 1024);
                wprintf(L"%s", napis);
                            cout << endl;
            wcsncpy(napis, L"1 - Sprawdzanie połocznia z intrnetem przy włączaniu programu", 1024);
            wprintf(L"%s", napis);
                            cout << endl;
            wcsncpy(napis, L"2 - Zapisywanie zdarzeń do pliku", 1024);
            wprintf(L"%s", napis);
                            cout << endl;
                cout << "3 - Funkcja kolor dnia" << endl;
                wcsncpy(napis, L"4 - Reset wszystkich ustawień", 1024);
            wprintf(L"%s", napis);
                            cout << endl;
                wcsncpy(napis, L"5 - Przypomnienia / Sprawdzanie", 1024);
            wprintf(L"%s", napis);
                cout << endl;
                wcsncpy(napis, L"6 - Nowy system zapisywania ustawień", 1024);
            wprintf(L"%s", napis);
                cout << endl;
                            cout << ">";
                cin >> odp;
                if(odp == "0")
                {
                    kon =1;
                    menu_opcje(arg0global);
                }
                else if(odp == "1") //sprawdzanie polocznia z intrnetem przy wlaczeniu programu
                {
                    kon =1;
                  zm_opc_snet();
                }
                else if(odp == "2") // Zapisywanie zdarzeń do pliku
                {
                    kon = 1;
                    zm_opc_logi();
                }
                else if(odp == "3")
                {
                    kon =1;
                    zm_kolor_dnia();
                }
                else if(odp == "4")
                {
                    bool koniec = false;
                    while(koniec != true)
                    {
                        system("cls");
                        cout << "Czy na pewno?" << endl;
                        cout << "1 = Tak "<< endl;
                        cout << "2 = Nie" << endl;
                        cin >> odp;
                        if(odp == "1")
                        {
                            koniec = true; // koiec pętli
                            system("cls");
                            if(zalogowany == true)
                            {
                                zal_domyslne_ust();
                            }
                            else
                            {
                                na_domyslne();
                            }
                        }
                        else if(odp == "2")
                        {
                            koniec = true;
                            kon = 1;
                            zm_opcji_programu();
                        }
                    }
                }
                else if(odp == "5")
                {
                    cout << "Przypomnienia" << endl;
                    cout << "Stan funkcji:" << przyp << endl;
                    cout << "1 - on" << endl;
                    cout << "2 - off" << endl;
                    cout << ">";
                    cin >> odp;
                    if(odp == "1")
                    {
                    przyp = true;
                    napisy_p();
                    }
                    else if(odp == "2")
                    {
                    przyp = false;
                    napisy_p();
                    }
                    else
                    {
                    cout << "nie wybrano odpowiedzi" << endl;
                    napisy_p();
                    }
                }
                else if(odp == "6")
                {
                    cout << "System zapisywania ustawień" << endl;
                    cout << "Stan funkcji:" << nowy_sys_zap_ust << endl;
                    cout << "1 - on" << endl;
                    cout << "2 - off" << endl;
                    cout << ">";
                    cin >> odp;
                    if(odp == "1")
                    {
                    nowy_sys_zap_ust = true;
                    fstream pliks;
                    pliks.open("C://PlikiPomocnik//plik_ust_z_p.txt", ios::out);
                    if(pliks.good() == true )
                    {
                    pliks << nowy_sys_zap_ust;
                    }
                    pliks.close();
                    zapis_plik_ustawien();
                    napisy_p();
                    }
                    else if(odp == "2")
                    {
                    nowy_sys_zap_ust = false;
                    fstream pliks;
                    pliks.open("C://PlikiPomocnik//plik_ust_z_p.txt", ios::out );
                    if(pliks.good() == true )
                    {
                    pliks << nowy_sys_zap_ust;
                    }
                    pliks.close();
                    napisy_p();
                    }
                    else
                    {
                    cout << "nie wybrano odpowiedzi" << endl;
                    napisy_p();
                    }
                }
            }
}

int zm_opc_snet()
{
    int kon = 0;
                while(kon != 1)
                {
                 system("cls");
    cout << "Sprawdzanie polanczenia z internetem przy wlaczeniu programu" << endl;
                    cout << "Stan funkcji :" << snet;
                    if(snet == 0)
                    {
                        wcsncpy(napis, L" Wyłączone", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                    }
                    if(snet == 1)
                    {
                        wcsncpy(napis, L" Włączone", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                    }
                    cout << "-------------" << endl;
                wcsncpy(napis, L"0 - Powrót", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                    wcsncpy(napis, L"1 -Włąncz", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                    wcsncpy(napis, L"2 -Wyłącz", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                    cout << ">";
                    cin >> odp;

                    if(odp == "0")
                    {
                        kon = 1;
                        menu_opcje(arg0global);
                    }
                    if(odp== "1") // snet on /
                        {
                            snet = true;
                            kon = 1;
                            if(zalogowany == true)
                            {
                                zal_zapis_uat();
                            }
                            else
                            {
                                if(nowy_sys_zap_ust == true)
                                {
                                zapis_plik_ustawien();
                                }
                                else
                                {
                                    fstream plik;
                                    mkdir("C:/PlikiPomocnik");
                                    plik.open ("C:/PlikiPomocnik/opcja_spr_int.txt", ios::out);
                                    plik << "1";
                                    plik.close();
                                }
                            }
                            //----------------------

                            cout << "Zapisano zmiane" << endl;
                            wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                            getch();
                            menu_opcje(arg0global);
                        }
                    if(odp=="2")// snet off
                        {
                            kon = 1;
                            snet = false;
                            if(zalogowany == true)
                            {
                                zal_zapis_uat();
                            }
                            else
                            {
                                if(nowy_sys_zap_ust == true)
                                {
                                zapis_plik_ustawien();
                                }
                                else
                                {
                                fstream plik;
                                mkdir("C:/PlikiPomocnik");
                                plik.open ("C:/PlikiPomocnik/opcja_spr_int.txt", ios::out);
                                plik << "0";
                                plik.close();
                                }
                            }

                            cout << "Zapisano zmiane" << endl;
                            wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                            getch();
                            menu_opcje(arg0global);
                        }
                }
}

int zm_opc_logi()
{
        int kon = 0;
            while(kon != 1)
            {
                  system("cls");
     wcsncpy(napis, L"Zapisywanie zdarzeń do pliku Pomocniklog.txt", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                    cout << "Stan funkcji:" << ust_logi;
                    if(ust_logi == 0)
                    {
                        wcsncpy(napis, L" Wyłączone", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                    }
                    if(ust_logi == 1)
                    {
                        wcsncpy(napis, L" Włączone", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                    }
                    cout << "-------------" << endl;
                wcsncpy(napis, L"0 - Powrót", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                    wcsncpy(napis, L"1 -Włąncz", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                    wcsncpy(napis, L"2 -Wyłącz", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                    cout << ">";
                    cin >> odp;

                /*---------------------------------------
                ---------- \/ sprawdzanie odpowiedzi ----
                -----------------------------------------
                */
                 if(odp == "0")
                    {
                        kon = 1;
                        menu_opcje(arg0global);
                    }
                    if(odp== "1")
                        {
                            ust_logi = true;
                            kon = 1;
                            if(zalogowany == true)
                            {
                                zal_zapis_uat();
                            }
                            else
                            {
                                if(nowy_sys_zap_ust == true)
                                {
                                zapis_plik_ustawien();
                                }
                                else
                                {
                                fstream plik;
                                mkdir("C:/PlikiPomocnik");
                                plik.open ("C:/PlikiPomocnik/ust_p.txt", ios::out);
                                plik << "1";
                                plik.close();
                                }
                            }
                            //----------------------

                            cout << "Zapisano zmiane" << endl;
                            wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                            getch();
                            menu_opcje(arg0global);
                        }
                    if(odp=="2")
                        {
                            kon = 1;
                            ust_logi = false;
                            if(zalogowany == true)
                            {
                                zal_zapis_uat();
                            }
                            else
                            {
                                if(nowy_sys_zap_ust == true)
                                {
                                zapis_plik_ustawien();
                                }
                                else
                                {
                                fstream plik;
                                mkdir("C:/PlikiPomocnik");
                                plik.open ("C:/PlikiPomocnik/ust_p.txt", ios::out);
                                plik << "0";
                                plik.close();
                                }
                            }
                            cout << "Zapisano zmiane" << endl;
                            wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                            wprintf(L"%s", napis);
                            cout << endl;
                            getch();
                            menu_opcje(arg0global);
                        }

            }

}

int beta_opcje()
{
    int kon = 0;
    while(kon != 1 )
    {
        system("cls");
        cout << "Opcje wersji beta:" << endl;
        cout << "0 - Wyjście" << endl;
        cout << "9 - Powtót" << endl;
        cout << ">";
        cin >> odp;

        if(odp == "0")
        {
            kon = 1;
            napisy_p();
        }
        else if(odp == "9")
        {
            menu_opcje(arg0global);
        }
    }
}

int na_domyslne()
{
    if(zalogowany == true)
    {
        zal_domyslne_ust();
    }
    else
    {


    wcsncpy(napis, L"Rozpoczynam restartowanie ustawień programu.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            cout << "0%" << endl;
                            cout << endl;
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
        cout << "10%" << endl;



    if(nowy_sys_zap_ust == false)
    {
        fstream plik_ust_p2;
            plik_ust_p2.open("C://PlikiPomocnik//ust_p.txt", ios::out ); // zapisywanie pliku
            if(plik_ust_p2.good() == true )
            {
                cout << "20%" << endl;
                ust_logi = true;
                plik_ust_p2 << "1";
            }
            else
            {
                SetConsoleTextAttribute( kolor, 12 );
                if(debugowanie == true)
                {
                    wcsncpy(napis, L"Wystąpił bład! ;(", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                }
                SetConsoleTextAttribute( kolor, zkolor );
            }
            plik_ust_p2.close();
        cout << "30%" << endl;
    //==============================
    fstream plik_snet;
    plik_snet.open("C://PlikiPomocnik//opcja_spr_int.txt", ios::out);
            if(plik_snet.good() == true)
            {
                plik_snet << "1";
                cout << "40%" << endl;
            }
            else
            {
                if(debugowanie == true)
                {
                    errorlitsa();
                }
            }

            cout << "50%" << endl;
        plik_snet.close();
        //===============================
        cout << "60%" << endl;
        fstream plikw;
            plikw.open ("C://PlikiPomocnik//kolor.txt", ios::out);
        if(plikw.good() == true)
        {
            cout << "70%" << endl;
           plikw << "7";
            cout << "80%" << endl;
        }
        else
        {
            if(debugowanie == true)
            {
                errorlitsa();
            }
        }
        cout << "90%" << endl;
        plikw.close();
    }

    if(nowy_sys_zap_ust == true)
    {
        cout << "20%" << endl;
        fstream plik_ust; // plik ustawień
    plik_ust.open("C:\\PlikiPomocnik\\ustawienia.txt", ios::out);
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
            cout << "100%" << endl;
        }
        else
        {
            errorlitsa();
            cout << "Problem może zostać naprawiony przy kolejnym uruchomieniu programu" << endl;
        }
    }

    wcsncpy(napis, L"Za chwile nastąpi zamknięcie programu.", 1024);
    wprintf(L"%s", napis);
    cout << endl;
    Sleep(200);
    wcsncpy(napis, L"Po zamknięciu programu uruchom go ponownie!", 1024);
    wprintf(L"%s", napis);
    cout << endl;
    Sleep(200);
    wcsncpy(napis, L"Program zamknie się za:", 1024);
    wprintf(L"%s", napis);
    cout << endl;
    cout << "3" << endl;
    Sleep(1000);
    cout << "2" << endl;
    Sleep(1000);
    cout << "1" << endl;
    Sleep(1000);
    cout << "0" << endl;
    if(debugowanie == true)
    {
        getch();
        getch();
    }
    exit(0);
    }
}

int wstep_docore()
{
    cout << "1>";
    pole_corep[0];
    getline(cin, pole_corep[0]);

    cout << endl;
    cout <<  "2>";

    pole_corep[1];
    getline(cin, pole_corep[1]);
    cout << endl;
    cout << "3>";

    pole_corep[2];
    getline(cin, pole_corep[2]);
    cout << endl;

    pole_corep[2] = "\k " + pole_corep[2];

    cout << "1:" << pole_corep[0] << "| 2:" << pole_corep[1] << "| 3:" << pole_corep[2] << endl;
    docorep();
}

int docorep()
{
    bool nowe_p = true;
    bool praca_corep;

    ifstream plikstat;
    FILE_SHARE_READ;
    plikstat.open("c:\\Core-P\\status_pracy.txt", ios::in);
    if(plikstat.good() == true)
    {
        string tekst;
        plikstat >> tekst;
        if(tekst == "1")
        {
            praca_corep = true;
            napisy_p();
            wcsncpy(napis, L"Core-P jest zajęty teraz innym zadaniem!", 1024);
            wprintf(L"%s", napis);
            cout << endl;
        }
        else if(tekst == "0")
        {
            praca_corep = false; // ok
        }
        else if(tekst == "-1")
        {
            praca_corep = true;
            napisy_p();
            wcsncpy(napis, L"Core-P nie jest uruchomiony", 1024);
            wprintf(L"%s", napis);
            cout << endl;
        }
        else
        {
            wcsncpy(napis, L"Zła wartość w pliku!", 1024);
            wprintf(L"%s", napis);
            cout << endl;
        }
    }
    else
    {
        errorlitsa();
    }
    plikstat.close();
    plikstat.clear();



    ifstream plikstatp;
    FILE_SHARE_READ;
    plikstatp.open("c:\\Core-P\\nowe_p.txt", ios::in);
    if(plikstatp.good() == true)
    {
        string tekst;
        plikstatp >> tekst;
        if(tekst == "1")
        {
            nowe_p = false;
        }
        else if(tekst == "0")
        {
            nowe_p = true;
        }
        else
        {
            wcsncpy(napis, L"Zła wartość w pliku!", 1024);
            wprintf(L"%s", napis);
            cout << endl;
        }
        plikstatp.close();
    }
    else
    {
        errorlitsa();
    }
    plikstatp.close();
    plikstatp.clear();



    if(praca_corep == true)
    {
            wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            getch();
            napisy_p();
    }

    if(praca_corep == false && nowe_p == true)
    {

        ofstream plikcorep;
        FILE_SHARE_WRITE;
        plikcorep.open("c:\\Core-P\\nowe_p.txt", ios::out);
        if(plikcorep.good() == true)
        {
            plikcorep << "1";

            plikcorep.close();
        }
        else
        {
            errorlitsa();
        }
        plikcorep.close();
        plikcorep.clear();

        ofstream plikcore;
        FILE_SHARE_WRITE;
        plikcore.open("c:\\Core-P\\We\\dane_we.txt", ios::out);
        if(plikcore.good() == true)
        {
            plikcore << "Pomocnik";
            plikcore << endl;
            plikcore << pole_corep[0];
            plikcore << endl;
            plikcore << pole_corep[1];
            plikcore << endl;
            plikcore << pole_corep[2];
            plikcore.close();
            if(debugowanie == true)
            {
                cout << "wyslano dane do: dane_we.txt" << endl;
            }

            sprawdzanie_corep();

        }
        else
        {
            errorlitsa();
        }
        plikcore.close();
        plikcore.clear();
    }
}

int sprawdzanie_corep()
{
    //cout << "Przetwarzanie..." << endl;
    int kon =0;
    bool czesc1 = false;
    while(kon != 1)
    {
        if(czesc1 == false)
        {
            ifstream plikcore;
            FILE_SHARE_READ;
            plikcore.open("c:\\Core-P\\We\\status_we.txt", ios::in);
            if(plikcore.good() == true)
            {
                string tresc;
                plikcore >> tresc;
                if(tresc == "0")
                {
                    czesc1=true;
                    cout << "czesc1=true" << endl;
                }
                plikcore.close();
            }
        }

        if(czesc1 == true)
        {
             fstream plikcore2;
            plikcore2.open("c:\\Core-P\\Wy\\status_wy.txt", ios::in);
            if(plikcore2.good() == true)
            {
                string tresc;
                plikcore2 >> tresc;
                plikcore2.close();
                plikcore2.clear();
                if(tresc == "1")
                {
                    if(debugowanie == true)
                    {
                        cout <<"tresc == 1" << endl;
                    }
                    wyjscie_corep();
                    break;
                }
            }
        }
    }
    getch();
    napisy_p();
}

int kodowanie_max(char *napis)
{

}
int dekodowanie_max(char *napis)
{

}


int wyjscie_corep()
{
    //cout << "Czekanie na wiadomosc powrotna..." << endl;

        ifstream plikcore;
            FILE_SHARE_READ;
            plikcore.open("c:\\Core-P\\Wy\\dane_wy.txt", ios::in);
    if(plikcore.good() == true)
    {

        cout << "Komunikat powrotyny:" << endl;
        string tresc;
        while(!plikcore.eof())
        {
            getline(plikcore, tresc);
            cout << tresc << endl;
        }
        plikcore.close();

        getch();
        napisy_p();
    }
}

//koniec
