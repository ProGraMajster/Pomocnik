//Plik: plik.cpp
#include "plik2.hpp"


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
#include <stdexcept>


#define _GNU_SOURCE

#define M_PI       3.14159265358979323846

using namespace std;

extern HANDLE kolor;

extern string odp;
extern string arg0global;
extern string nickname;
extern string schowek_programowy;
extern string pole_corep[3];

extern wchar_t napis[1024];
extern wchar_t kolor_slowo[1024]; //------

extern int main( int argc, char * argv[] );

extern int zkolor;
extern int zapas_zkolor;
extern int endloading;

extern int log();
extern int zmianakoloru();
extern int errorlitsa();
extern int stalematematyczne();
extern int napisy_p();
extern int menu_opcje(string arg0);
extern int zapis_plik_ustawien();
extern int kodowanie(char *napis);
extern int dekodowanie(char *napis);
extern int zapytanie();

extern bool nowy_sys_zap_ust;
extern bool debugowanie;
extern bool snet;
extern bool wczyt_kolor_dnia;
extern bool datanap;
extern bool zalogowany;
extern bool zal_zapis_uat();
extern bool ist_corep;

extern int watek( void * dummy);


int play_sound_path(string & path)
{
    bool stan = PlaySound((path.c_str()), NULL, SND_FILENAME | SND_ASYNC);
    if(debugowanie == true)
    {
        cout << "PlaySound > stan: " << stan << endl;
    }
}

int dodajLiczby(long long a, long long b )
{
    return( a + b );
}

string & foo (string & tekstwczytany)
{

   return tekstwczytany;
}
//--------------------------------------------------------
int spr_polaczenia_inter()
{
 //-----------------Sprawdanie polaczenia------------\/
    int retcode = system ("ping www.google.com");
  printf("kod powrotu: %d\n", retcode);
    //wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
     //   wprintf(L"%s", napis);
    cout<< endl;
  getch();

//-----------------------
}

int wczytywanie_koloru()
{
    if(debugowanie == true)
    {
        wcsncpy(napis, L"Wczytywanie pliku: C://PlikiPomocnik//kolor.txt", 1024);
            wprintf(L"%s", napis);
            cout << endl;
    }
    // HANDLE kolor;
    fstream plikw;
    plikw.open ("C://PlikiPomocnik//kolor.txt", ios::in);
    if(plikw.good() == true)
    {
        plikw >> zkolor;

        plikw.close();


        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( kolor, zkolor );
        if(debugowanie == true)
        {
            cout << "Wczytano kolor :" << zkolor << endl;
        }
    }
    else
    {
        if(debugowanie == true)
        {
           errorlitsa();
           wcsncpy(napis, L"Nie znaleziono pliku. Ustawiam kolor scionki na domyślny.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
        }
            zkolor =7;
        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( kolor, 7 );
        plikw.open ("C://PlikiPomocnik//kolor.txt", ios::out);
        if(plikw.good() == true)
        {
           plikw << "7";

        }
        else
        {
            if(debugowanie == true)
            {
                errorlitsa();
            }
        }
        plikw.close();

    }
}


int wczytywanie_koloru_dnia()
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    int dzien_tygodnia;
    string path;
    if(zalogowany == true)
    {
        path = "C:\\PlikiPomocnik\\Users\\" + nickname + "\\kolor_dnia.txt";
    }
    else
    {
        path = "C://PlikiPomocnik//kolor_dnia.txt";
    }
     fstream plikw;
     plikw.open (path, ios::in);
    if(plikw.good() == true)
    {
        int pen =0;
        while(!plikw.eof())
        {

            plikw >> dzien_tygodnia >> zkolor;
            if(st.wDayOfWeek == pen)
            {
                break;
            }

            pen++;
        }

        plikw.close();
        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( kolor, zkolor );
        if(debugowanie == true)
        {
            cout << "dzien_tygodnia: " << dzien_tygodnia << endl;
            cout << "Wczytano kolor :" << zkolor << endl;
        }
    }
    else
    {
        if(debugowanie == true)
        {
            errorlitsa();
            wcsncpy(napis, L"Nie znaleziono pliku. Ustawiam kolor scionki na domyślny.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
        }
        kolor = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( kolor, 7 );
    }

}

int zapisywanie_koloru_dnia()
{
    wcsncpy(napis, L"Funkcja kolor dnia.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"-- Spis dostępnych kolorów:", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            int kon =0;
            int liczba = 0;
            while(kon != 1)
            {
                liczba++;
                kolor = GetStdHandle( STD_OUTPUT_HANDLE );
                SetConsoleTextAttribute( kolor, liczba );
                cout << liczba;
                wcsncpy(napis, L" - Przykładowy tekst", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                if(liczba == 15)
                {
                    kon=1;
                }
            }
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( kolor, zkolor );
        wcsncpy(napis, L"Do każdej liczby jest przypisany kolor!", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"Zaraz wyświetlą się dni tygodnia", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"Do każdego dnia tygodnia przypisz liczbę (np. Poniedziałek: 14 ).", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"Wpisz tylko liczbę!!!", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"Niedziela: ", 1024);
            wprintf(L"%s", napis);
            cin >> odp;
            cout << endl;
            fstream plikw;
            if(zalogowany == true)
            {
                string path = "C:\\PlikiPomocnik\\Users\\" + nickname + "\\kolor_dnia.txt";
                plikw.open (path, ios::out);
                if(plikw.good() == true)
                {
                    plikw << "0 " << odp;
                    plikw << endl;
                    wcsncpy(napis, L"Poniedziałek: ", 1024);
                    wprintf(L"%s", napis);
                    cin >> odp;
                    cout << endl;
                    plikw << "1 " << odp;
                    plikw << endl;
                    wcsncpy(napis, L"Wtorek: ", 1024);
                    wprintf(L"%s", napis);
                    cin >> odp;
                    cout << endl;
                    plikw << "2 " << odp;
                    plikw << endl;

                    wcsncpy(napis, L"Środa: ", 1024);
                    wprintf(L"%s", napis);
                    cin >> odp;
                    cout << endl;
                    plikw << "3 " << odp;
                    plikw << endl;

                    wcsncpy(napis, L"Czwartek: ", 1024);
                    wprintf(L"%s", napis);
                    cin >> odp;
                    cout << endl;
                    plikw << "4 " << odp;
                    plikw << endl;

                    wcsncpy(napis, L"Piątek: ", 1024);
                    wprintf(L"%s", napis);
                    cin >> odp;
                    cout << endl;
                    plikw << "5 " << odp;
                    plikw << endl;

                    wcsncpy(napis, L"Sobota: ", 1024);
                    wprintf(L"%s", napis);
                    cin >> odp;
                    cout << endl;
                    plikw << "6 " << odp;
                    plikw << endl;

                    plikw.close();
                }
                else
                {
                    errorlitsa();
                }
            }
            else
            {
                plikw.open ("C:/PlikiPomocnik/kolor_dnia.txt", ios::out);
                if(plikw.good() == true)
                {
                plikw << "0 " << odp;
                plikw << endl;
                wcsncpy(napis, L"Poniedziałek: ", 1024);
                wprintf(L"%s", napis);
                cin >> odp;
                cout << endl;
                plikw << "1 " << odp;
                plikw << endl;
                wcsncpy(napis, L"Wtorek: ", 1024);
                wprintf(L"%s", napis);
                cin >> odp;
                cout << endl;
                plikw << "2 " << odp;
                plikw << endl;

                wcsncpy(napis, L"Środa: ", 1024);
                wprintf(L"%s", napis);
                cin >> odp;
                    cout << endl;
                plikw << "3 " << odp;
                plikw << endl;

                wcsncpy(napis, L"Czwartek: ", 1024);
                wprintf(L"%s", napis);
                cin >> odp;
                cout << endl;
                plikw << "4 " << odp;
                plikw << endl;

                wcsncpy(napis, L"Piątek: ", 1024);
                wprintf(L"%s", napis);
                cin >> odp;
                cout << endl;
                plikw << "5 " << odp;
                plikw << endl;

                wcsncpy(napis, L"Sobota: ", 1024);
                wprintf(L"%s", napis);
                cin >> odp;
                cout << endl;
                plikw << "6 " << odp;
                plikw << endl;

                plikw.close();
                }
                else
                {
                    errorlitsa();
                }
            }
        wcsncpy(napis, L"Aby włączyć tą funkcję przejdź do opcji programu!", 1024);
            wprintf(L"%s", napis);
            cout << endl;

}


//--------------------------------------------------------
int wczytywanie_linia_stop(int numerstop)
{
        std::string tekstt; //zmienna przechowuj¹ca tekst.
    fstream plikustawien;
        int liniapliku=0;// zmienna okreœlaj¹ca po³o¿enie kursora na wierszu w pliku tekstowym
    plikustawien.open ("C:/PlikiPomocnik/Opcje/OpcjeProgramu.txt", std::ios::in | std::ios::out);
            if(plikustawien.good() == true )
            {
                while(!plikustawien.eof())
                {
                    std::getline(plikustawien, tekstt); //wczytywanie linijki tekstu
                        liniapliku ++;

                        if(numerstop == liniapliku)
                        {
                          foo(tekstt);
                            if(liniapliku > numerstop)
                            {
                                return numerstop;
                                break; // koniec pêtli

                            }

                        }
                }
        plikustawien.close();
            }
            else
            {
             cout << "error" << endl;
            }
}


int komendy_testy(string & odpo)
{
            if(odpo=="test_n" || odpo == "wyszukaj")
            {
                cout << "Wpisz fraze" << endl;
                cout << ">";
                string tekst;
                cin.clear();
                tekst;
               // cin.get();
                getline(cin, tekst);
                string nett;
                nett = "https://www.google.com/search?q=";
                nett += tekst;
                ShellExecute(NULL, "open", nett.c_str(),
                         NULL, NULL, SW_SHOWNORMAL);
            }

            if(odpo=="taskmgr")
            {
                ShellExecute(NULL, "open", "taskmgr.exe",
                         NULL, NULL, SW_SHOWNORMAL);
            }

            if(odpo== "test001")
            {
                PlaySound(TEXT("C:\\PlikiPomocnik\\sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }

            if(odp == "zrzut_ekranu")
            {
                 keybd_event(VK_MENU, 0, 0, 0); //Alt Press
                keybd_event(VK_SNAPSHOT, 0, 0, 0); //PrntScrn Press


                keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0); //PrntScrn Release
                keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); //Alt Release

            cout << "ok" << endl;
            }

        if(odpo== "enginep")
        {
            string tekst;
            char kome[255];
            fstream plik;
            mkdir("c:\\PlikiPomocnik\\Komendy\\");
            plik.open("c:\\PlikiPomocnik\\Komendy\\engine.txt" , ios::in | ios::out );
            if(plik.good()==true)
            {

                while(!plik.eof())
                    {
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

    int n = tekst.length();

    // declaring character array
    char char_array[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(char_array, tekst.c_str());
    strcpy(kome, char_array);

//=============================================================================================
                strcpy(zmienna, "");         //przypisanie do zmiennej "zmienna" wartoœci
                strcpy(polecenie, kome);   //przypisanie do zmiennej "polecenie" wartoœci

                strcat(polecenie,zmienna);      //po³¹czenie ci¹gu znaków (dopisanie do zmiennej "polecenie" wartoœci
                //ze zmiennej "zmienna"

                system(polecenie);
        }

        if(odpo =="test003")
        {
         system("set");
        }

        if(odpo=="test004")
        {
            cout << "\245\206\251\210\344\242\230\276\253\244\217\250\235\343\340\227\275\215¹æê³ñóœ¿Ÿ¥ÆÊ£ÑÓŒ¯" << endl;
        }

        if(odpo == "hostname")
        {
            system("hostname");
        }

        if(odpo == "ttest")
        {
            system("chcp");
        }
        if(odpo== "loadingtest")
        {
            std::cout << '-' << std::flush;

            for (;;)
            {
                if( kbhit() )
                        if( getch() == 'q' )
                            break;
                    Sleep(100);
                    std::cout << "\b\\" << std::flush;
                    Sleep(100);
                    std::cout << "\b|" << std::flush;
                    Sleep(100);
                    std::cout << "\b/" << std::flush;
                    Sleep(100);
                    std::cout << "\b-" << std::flush;

            }
        }

        if(odpo=="test_od")
        {

            int rozmiar=0;
            string tekst[10000];
            //cout << "Test odczytu pliku / Kazda linijka plku do innej zmiennej" << endl;

            fstream pliko;
            pliko.open("C:\\PlikiPomocnik\\Pomocniklog.txt", ios::in );
            if( pliko.good()== true )
            {
                 while(!pliko.eof())
                    {
                        rozmiar++;
                        if(rozmiar > 9999)
                        {
                            break;
                            pliko.close();
                        }
                        getline(pliko, tekst[rozmiar]);

                    }
                pliko.close();

                for(int ile=0; ile<rozmiar; ile++)
                {
                    cout << "tekst:" << tekst[ile] << endl;
                }
            }
            else
            {
                cout << "Nie mozna otworzyc pliku" << endl;
            }

        }

        if(odp == "test_szukanie")
        {

        }

        if(odpo=="test_zpkolor")
        {
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, zapas_zkolor );
        }

        if(odpo == "animacja")
        {
        }
}

int usun_plik(string & path)
{
     remove(path.c_str());
}

int odczytywanie_pliku(string & path)
{
    schowek_programowy = "path:" + path + " \n";
        string tekst;
            fstream plik;
            plik.open( path.c_str(), ios::in );
                if(plik.good() == true)
                {
                    cout << "Tresc pliku: " << endl;

                    while(!plik.eof())
                    {
                        getline(plik, tekst);
                        cout<< tekst << endl; //wyœwietlenie linii
                        schowek_programowy += tekst + " \n";
                    }
                plik.close();
                }
                else
                {
                    cout << "Nie udalo sie otworzyc" << endl;
                }
                getch();
}

int odczytywanie_duzego_pliku(string & path)
{
    bool stop = false; // co sto wczytanych lini stop
    bool buffspr = true;
    long bufforlinii =0;
    long linia = 0;
    int tabile = 0;
        string tekst[1024];
            fstream plik;
            plik.open( path.c_str(), ios::in );
                if(plik.good() == true)
                {
                    cout << "Tresc pliku: " << endl;

                    while(!plik.eof())
                    {

                        getline(plik, tekst[tabile]);
                        if(buffspr == true)
                        {
                          bufforlinii++;
                        }
                        linia++;
                        if(debugowanie == true)
                        {
                            cout<< "B:"<< bufforlinii<< "|" <<"L:" << linia <<"| ";
                        }
                        cout << tekst[tabile] << endl; //wyœwietlenie linii
                        Sleep(20);

                        if(tabile == 50)
                        {
                            Sleep(50);
                        }

                        if(tabile > 200 || linia > 200)
                            {
                                if(stop == true)
                                {
                                    cout << endl;
                                    cout << endl;
                                    wcsncpy(napis, L"Aby wówczas kontynuować wczytywanie kliknij dowolny przycisk!", 1024);
                                    wprintf(L"%s", napis);
                                        cout << endl;
                                        cout << endl;
                                        getch();
                                        getch();
                                        if(getch() == 'q')
                                        {
                                            break;
                                            napisy_p();
                                        }
                                }
                                else
                                {
                                    cout << endl << endl << "//{Wczytywanie pliku...}//" << endl << endl;
                                    Sleep(1000);
                                }
                                 tabile = 0;
                                 linia = 0;
                                  tekst[tabile] = "";
                            }
                        tekst[tabile] = "";
                        tabile++;
                        if(bufforlinii > 9750)
                        {
                            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
                            SetConsoleTextAttribute( kolor, 12 );
                            wcsncpy(napis, L"!!! Uwaga kończy się miejsce w bufforze !!!", 1024);
                            wprintf(L"%s", napis);
                            cout << endl;
                            wcsncpy(napis, L"Co to oznacza? Tekst z samej góry bedzię znikał aby mogły się wczytać kolejne linie pliku", 1024);
                            wprintf(L"%s", napis);
                            cout << endl;
                            wcsncpy(napis, L"Od teraz co 200 wczytanych linii tekstu wczytywanie będzię się zatrzymywało", 1024);
                            wprintf(L"%s", napis);
                            cout << endl;
                            wcsncpy(napis, L"Aby wówczas kontynuować wczytywanie będzie trzeba kliknąć dowolny przycisk", 1024);
                            wprintf(L"%s", napis);
                            cout << endl;
                            getch();
                            buffspr = false;
                            stop = true;
                            bufforlinii = 0;
                            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
                            SetConsoleTextAttribute( kolor, zkolor );
                        }
                    }
                plik.close();
                }
                else
                {
                    cout << "Nie udalo sie otworzyc" << endl;
                }
}

string & rozmiar_pliku(string & path)
{
    unsigned int length;

  fstream fs;
  fs.open( path.c_str(), ios::binary | ios::in );
  if ( fs.good()==true )
  {
    // przesun pozycje na koniec
    fs.seekg( 0, ios::end );
    // odczytaj pozycje w pliku -> rozmiar pliku
    length = fs.tellg();
    // wroc na poczatek pliku!
    fs.seekg( 0, ios::beg );

        cout << "Rozmiar pliku to: " << length;
     wcsncpy(napis, L"bajtów", 1024); //okome
            wprintf(L"%s", napis);
            cout << endl;
  }
  else
  {
      errorlitsa();
  }
}

int kalp()
{
    int kon = 0;
    bool okej;
     SetConsoleTitleA( "Pomocnik - Wbudowany kalkulator" );
        while(kon != 1)
            {
                system("cls");
                cout << "1 - Stale matematyczne"<<endl;
                cout << "2 - Dzialeanie trygonometryczne" << endl;
                cout << "3 - Zaokraglenie" << endl;
                cout << "4 - Potegowanie liczb" << endl;
                cout << "5 - Dodawanie liczb (Tylko dwie liczby)" << endl;
                cout << "" << endl;
                cin >> odp;
                if(odp=="1")
                {
                    kon = 1;
                    stalematematyczne();
                    getch();
                    system("cls");
                    napisy_p();
                }
                if(odp == "2")
                {
                    kon = 1;
                    float kat;
                    cout << "Podaj wartosc kata: ";
                    cin>>kat;
                    okej = cin.good();
                    cin.clear();
                    cin.sync();
                    if(okej == true)
                    {
                       cout<< "sinus: " <<sin(kat*M_PI/180.0)<<endl;
                        cout<< "cosinus: " <<cos(kat*M_PI/180.0)<<endl;


                        if (fabs(tan(kat*M_PI/180.0))>=999999999|| fabs(1/tan(kat*M_PI/180.0))<=-999999999)
                        {
                            cout<<"Tangens nie istnieje!"<<endl;
                        }
                        else
                        {
                            cout<< "tangens: " <<tan(kat*M_PI/180.0)<<endl;
                        }
                        if (fabs(1/tan(kat*M_PI/180.0))>=999999999 || fabs(1/tan(kat*M_PI/180.0))<=-999999999)
                        {
                            cout<<"Cotangens nie istnieje!"<<endl;
                        }
                        else
                        {
                            cout<< "Cotangens: " <<1/tan(kat*M_PI/180.0)<<endl;
                        }
                    }
                    else
                    {
                        cout << "Wpisz liczbe!" << endl;
                        cout << "już za późno!" << endl;
                        cout << "wpisz to > cls" << endl;
                        cout << ">";
                    }


                }
                if(odp == "3")
                {
                    kon = 1;
                    float liczba;
                    cout << "Podaj liczbe: ";
                    cin>>liczba;
                    okej = cin.good();
                    cin.clear();
                    cin.sync();
                    cout<<"Zaokraglenie: "<<round(liczba)<<endl;
                    cout<<"Sufit: "<<ceil(liczba)<<endl;
                    cout<<"Podloga: "<<floor(liczba)<<endl;
                    cout<<"Obciecie: "<<trunc(liczba)<<endl;
                }
                if(odp == "4")
                {
                    kon = 1;
                    double liczba, potega;
                    cout << "Podaj liczbe: ";
                    cin >> liczba;
                    cin.clear();
                    cin.sync();
                    cout << "Do ktorej potegi podniesc liczbe " << liczba << "? Wpisz wartosc: ";
                    cin >> potega;
                    cin.clear();
                    cin.sync();
                    cout << "pow(" << liczba << "," << potega << ")=" << pow( liczba, potega ) << endl;
                }

                if(odp == "5")
                {
                    kon = 1;
                    long liczba1;
                    long liczba2;

                    cout << "Podaj liczbe." << endl;
                    cin >> liczba1;
                    cin.clear();
                    cin.sync();
                    cout << "Podaj kolejna liczbe." << endl;
                    cin >> liczba2;
                    cin.clear();
                    cin.sync();
                    cout << "Wynik dodawania to: " << dodajLiczby( liczba1, liczba2) << endl;

                }

            }
    SetConsoleTitleA( "Pomocnik" );
}

int wczytywanie_op_snet_star_sys()
{
    if(debugowanie == true)
    {
        cout << endl << ">---" <<endl;
        cout << "Otwieranie pliku: C://PlikiPomocnik//opcja_spr_int.txt" << endl;
    }
            fstream plik_snet;
        plik_snet.open("C://PlikiPomocnik//opcja_spr_int.txt", ios::in);
        if(plik_snet.good() == true)
        {
            if(debugowanie == true)
            {
                cout << "Sukces! Otwarto plik" << endl;
            }
            string tekst = "tekst";
            plik_snet >> tekst;
            if(tekst == "0")
            {
                snet = false;
            }
            else if (tekst == "1")
            {
                snet = true;
            }
            else
            {
                if(debugowanie == true)
                {
                    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
                SetConsoleTextAttribute( kolor, 12 );
                wcsncpy(napis, L"Złą wartość w pliku: opcja_spr_int.txt", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
                    SetConsoleTextAttribute( kolor, zkolor );
                    getch();
                    getch();
                }
            }
            plik_snet.close();
        }
        else
        {
            if(debugowanie == true)
            {
                errorlitsa();
            }
            plik_snet.open("C://PlikiPomocnik//opcja_spr_int.txt", ios::out);
            if(plik_snet.good() == true)
            {
                plik_snet << "1";
            }
            else
            {
                if(debugowanie == true)
                {
                    errorlitsa();
                }
            }
        }
        plik_snet.close();
        if(debugowanie == true)
        {
            cout << "snet: " << snet << endl;
            getch();
        }
}

int plik_menu()
{
    int kon =0;
    while(kon != 1)
    {
        system("cls");
        wcsncpy(napis, L"Menedżer plików Pomocnik.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"0 - Wyjście z menu.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"1 - Otwórz plik z podanej ścieżki.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"2 - Usuń plik z podanej ścieżki.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"3 - Sprawdzanie rozmiaru pliku (w bajtach) z podanej ścieżki.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"4 - Otwórz plik z podanej ścieżki (wersja dla dużych plików tekstowych.)", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"5 - onotatka - Otwieranie notatki z folderu programu (Aby otworzyć plik wpisz jego nazwę).", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"6 - nnotatka - Tworzenie notatki w folderze programu.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"7 - nnotatka_s - Tworzenie zaszyfrowanej notatki notatki w folderze programu.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"8 - onotatka_s - Otwieranie zaszyfrowanej notatki z folderu programu (Aby otworzyć plik wpisz jego nazwę).", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"9 - Otwiera folder z plikami programu.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"10 - (menu) Porównywanie zawartości dwóch plików.", 1024);
            wprintf(L"%s", napis);
            cout << endl;

            cout << ">";
            cin >> odp;

            if(odp == "0")
            {
                kon = 1;
                napisy_p();
            }
            else if(odp == "1")
            {
                kon = 1;
                string path;
                system("cls");
                wcsncpy(napis, L"Wpisz scieżke do pliku. Np. C:\\PlikiPomocnik\\Pomocniklog.txt", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            cout << ">";
            cin >> path;
                //
                odczytywanie_pliku(path);
                napisy_p();
            }
            else if(odp == "2")
            {
                    kon = 1;
                string path;
                system("cls");
                wcsncpy(napis, L"Wpisz scieżke do pliku. Np. C:\\PlikiPomocnik\\Pomocniklog.txt", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                cout << ">";
                    cin >> path;
                usun_plik(path);
                napisy_p();

            }
            else if(odp == "3")
            {
                    kon = 1;
                string path;
                system("cls");
                wcsncpy(napis, L"Wpisz scieżke do pliku. Np. C:\\PlikiPomocnik\\Pomocniklog.txt", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                cout << ">";
                    cin >> path;
                rozmiar_pliku(path);
                wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                getch();
                napisy_p();
            }
            else if(odp == "4")
            {
                    kon = 1;
                string path;
                system("cls");
                wcsncpy(napis, L"Wpisz scieżke do pliku. Np. C:\\PlikiPomocnik\\Pomocniklog.txt", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                cout << ">";
                    cin >> path;
                odczytywanie_duzego_pliku(path);
                wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                getch();
                napisy_p();
            }
            else if(odp == "5")
            {
                kon = 1;
               onotatka();
            }
            else if(odp == "6")
            {
                kon = 1;
                nnotatka();
            }
            else if(odp == "7")
            {
                kon = 1;
                nnotatka_szyf();
            }
            else if(odp == "8")
            {
                kon = 1;
                onotatka_szyf();
            }
            else if(odp == "9")
            {
                kon = 1;
                ShellExecute(NULL, "open", "c:\PlikiPomocnik",
                         NULL, NULL, SW_SHOWNORMAL);
                log();
                zapytanie();
            }
            else if(odp == "10")
            {
                kon = 1;
                menu_porownywanie_plikow();
            }
            else
            {
                kon =1;
                cout <<  "Wpisz liczbe!" << endl;
                cin.clear();
                getch();
                plik_menu();
            }



    }
}

int przypomnienie_tworzenie()
{
    cin.clear();
    string path = "C:\\PlikiPomocnik\\Przypomnienia\\";
    if(debugowanie == true)
    {
        cout << "path:" << path << endl;
    }

    if(zalogowany == true)
    {
        path = "C:\\PlikiPomocnik\\Users\\" + nickname + "\\Przypomnienia\\";
        mkdir(path.c_str());
    }
    mkdir("c:\\PlikiPomocnik\\Przypomnienia");
    wcsncpy(napis, L"Wpisz datę przypomnienia w takim formacie (Przykładowa data): 18.01.2021", 1024);
            wprintf(L"%s", napis);
            cout << endl;

    string dzien;
    string miesiac;
    string rok;

            wcsncpy(napis, L"Dzień:", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            cout << ">";
            cin >> dzien;
            cin.clear();
            wcsncpy(napis, L"Miesiąc:", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            cin >> miesiac;
            cin.clear();
            wcsncpy(napis, L"Rok:", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            cin >> rok;
            cin.clear();
            path += dzien;
            path += ".";
            path += miesiac;
            path += ".";
            path += rok;
            path += ".txt";
            //------------------- Plik ------------------
            string tekst;
            int kon = 0;
            fstream plik;
            if(debugowanie == true)
            {
                cout << "path: " << path << endl;
            }

            plik.open( path.c_str(), ios::out );
                if(plik.good() == true)
                {
                    wcsncpy(napis, L"Aby zakończyć pisanie przypomnienia, wpisz w nowej linii to: //koniec", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;

                    wcsncpy(napis, L"Temat: ", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                    cin >> odp;
                    plik << "Temat: " <<odp;
                    plik << endl << endl;
                    plik << "text:";

                    wcsncpy(napis, L"Treść: ", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;

                    while(kon != 1)
                    {
                        cin >> tekst;
                        //getline(cin, tekst);
                        if(tekst == "//koniec" || tekst == "//end")
                        {
                            kon = 1;
                            plik << tekst;
                            wcsncpy(napis, L"Zakończono pisanie!", 1024);
                                wprintf(L"%s", napis);
                                cout << endl;
                            getch();
                            napisy_p();
                        }
                    }
                plik.close();
                }
                else
                {
                   errorlitsa();
                }
}

int przypomnienie_odczyt()
{
     setlocale(LC_ALL, "polish");
    string path = "C:\\PlikiPomocnik\\Przypomnienia\\";
    if(zalogowany == true)
    {
        path = "C:\\PlikiPomocnik\\Users\\" + nickname + "\\Przypomnienia\\";
    }

          SYSTEMTIME st, lt;

            GetSystemTime(&st);
            std::string strMessage;

            // Output a given SYSTEMTIME in the format "

            // 1. Using CString
            string cstrMessage;

            cstrMessage = ("%d.%02d.%02d",
                            st.wDay,
                            st.wMonth,
                            st.wYear );

            strMessage = cstrMessage;

            // 2. Formating using ostringstream
            std::ostringstream ossMessage;

            ossMessage << st.wYear   << "."
               << std::setw( 2 ) << std::setfill( '0' ) << st.wMonth  << "-"
               << std::setw( 2 ) << std::setfill( '0' ) << st.wDay    << " "
               << std::setw( 2 ) << std::setfill( '0' ) << st.wHour   << ":"
               << std::setw( 2 ) << std::setfill( '0' ) << st.wMinute << ":"
               << std::setw( 2 ) << std::setfill( '0' ) << st.wSecond << "."
               << std::setw( 3 ) << std::setfill( '0' ) << st.wMilliseconds;

            strMessage = ossMessage.str();

            // 3. sprintf
        char buffer[ 256 ];
        sprintf( buffer,
                "%d.%02d.%02d",
                st.wDay,
                st.wMonth,
                st.wYear );

        strMessage = buffer;
        if(debugowanie == true )
        {
            cout << "data: " << strMessage << endl;
        }

            path += strMessage;
            path += ".txt";
            string tekst;
            fstream plik;
            plik.open( path.c_str(), ios::in );
                if(plik.good() == true)
                {
                    cout << "Przypomnienie:" << strMessage << endl;
                    while(!plik.eof())
                    {
                        getline(plik, tekst);
                        cout<< tekst << endl; //wyœwietlenie linii
                    }
                plik.close();
                }
                else
                {
                    wcsncpy(napis, L"Nie ma na dziś żadnego przypomnienia.", 1024);
                    wprintf(L"%s", napis);
                    cout << endl;
                }
}

int data_napisy_p()
{
    SYSTEMTIME st, lt;

            GetSystemTime(&st);
            std::string strMessage;

            // Output a given SYSTEMTIME in the format "

            // 1. Using CString
            string cstrMessage;

            cstrMessage = ("%d-%02d-%02d",
                            st.wYear,
                            st.wMonth,
                            st.wDay );

            strMessage = cstrMessage;

            // 2. Formating using ostringstream
            std::ostringstream ossMessage;

            ossMessage << st.wYear   << "-"
               << std::setw( 2 ) << std::setfill( '0' ) << st.wMonth  << "-"
               << std::setw( 2 ) << std::setfill( '0' ) << st.wDay    << " "
               << std::setw( 2 ) << std::setfill( '0' ) << st.wHour   << ":"
               << std::setw( 2 ) << std::setfill( '0' ) << st.wMinute << ":"
               << std::setw( 2 ) << std::setfill( '0' ) << st.wSecond << "."
               << std::setw( 3 ) << std::setfill( '0' ) << st.wMilliseconds;

            strMessage = ossMessage.str();

            // 3. sprintf
        char buffer[ 256 ];
        sprintf( buffer,
                "%d-%02d-%02d",
                st.wYear,
                st.wMonth,
                st.wDay );

        strMessage = buffer;
            cout << "| " <<strMessage;

}

int wstep_zmiania_koloru()
{
    log();
            int kon =0;
            int liczba = 0;
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( kolor, zkolor );
            wcsncpy(napis, L"Podaj liczbę aby wybrać kolor.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"Obok każdej liczby zanjduje się przykładowy tekst.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"Kolor odpowiada danej liczbie.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            cout << "-------------------------" << endl;
            while(kon != 1)
            {
                liczba++;
                kolor = GetStdHandle( STD_OUTPUT_HANDLE );
                SetConsoleTextAttribute( kolor, liczba );
                cout << liczba;
                wcsncpy(napis, L" - Przykładowy tekst", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                if(liczba == 15)
                {
                    kon=1;
                }
            }
            kolor = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( kolor, zkolor );
        //============================================
        cout << "-------------------------" << endl;
        cout << ">";

            cin >> odp;
            if(odp=="1")
            {
                zkolor=1;
                zmianakoloru();
            }
            if(odp=="2")
            {
                zkolor=2;
                zmianakoloru();
            }
            if(odp=="3")
            {
                zkolor=3;
                zmianakoloru();
            }
            if(odp=="4")
            {
                zkolor=4;
                zmianakoloru();
            }
            if(odp=="5")
            {
                zkolor=5;
                zmianakoloru();
            }
            if(odp=="6")
            {
                zkolor=6;
                zmianakoloru();
            }
            if(odp=="7")
            {
                zkolor=7;
                zmianakoloru();
            }
            if(odp=="8")
            {
                zkolor=8;
                zmianakoloru();
            }
            if(odp=="9")
            {
                zkolor=9;
                zmianakoloru();
            }
            if(odp=="10")
            {
                zkolor=10;
                zmianakoloru();
            }
            if(odp=="11")
            {
                zkolor=11;
                zmianakoloru();
            }
            if(odp=="12")
            {
                zkolor=12;
                zmianakoloru();
            }
            if(odp=="13")
            {
                zkolor=13;
                zmianakoloru();
            }
            if(odp=="14")
            {
                zkolor=14;
                zmianakoloru();
            }
            if(odp=="15")
            {
                zkolor=15;
                zmianakoloru();
            }
}

bool onotatka()
{
     SetConsoleTitleA( "Pomocnik - Odczytywanie notatki" );
            log();
            system("cls");
            string nazwa;
            string linia;
            cout << ""<< endl;
            wcsncpy(napis, L"Wpisz nazwę notatki którą chcesz odczytać.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            cin >> nazwa;
            nazwa += ".txt";
            string dysk = "c:\\PlikiPomocnik\\Notatki\\";
            if(zalogowany == true)
                    {
                        dysk = "c:\\PlikiPomocnik\\Users\\" + nickname +"\\Notatki\\";
                    }
             dysk+=nazwa;
            fstream plik;
            schowek_programowy = "[onotatka] path:" + dysk + " \n";
            plik.open( dysk.c_str(), ios::in );
                if(plik.good() == true)
                {
                    wcsncpy(napis, L"Treść notatki: ", 1024);
            wprintf(L"%s", napis);
            cout << endl;

                    while(!plik.eof())
                    {
                        getline(plik, linia);
                        cout<< linia << endl; //wyœwietlenie linii
                        schowek_programowy += linia + " \n";
                    }
                        SetConsoleTitleA( "Pomocnik" );

                plik.close();
                }
                else
                {
                    errorlitsa();
                        SetConsoleTitleA( "Pomocnik" );
                }

        cout << endl;
                wcsncpy(napis, L"Kliknij dowolny przycisk, aby kontynuować!", 1024);
        wprintf(L"%s", napis);
    cout<< endl;
    getch();
    napisy_p();
}

bool onotatka_szyf()
{
    SetConsoleTitleA( "Pomocnik - Odczytywanie notatki" );
            log();
            system("cls");
            string nazwa;
            char napis_s[10000];
            cout << ""<< endl;
            wcsncpy(napis, L"Wpisz nazwę notatki którą chcesz odczytać.", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            cin >> nazwa;
            nazwa += ".txtp";
            string dysk = "c:\\PlikiPomocnik\\Notatki\\";
            if(zalogowany == true)
                    {
                        dysk = "c:\\PlikiPomocnik\\Users\\" + nickname +"\\Notatki\\";
                    }
             dysk+=nazwa;
            fstream plik;
            plik.open( dysk.c_str(), ios::in );
                if(plik.good() == true)
                {
                    wcsncpy(napis, L"Treść notatki: ", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            string tekst;

                    while(!plik.eof())
                    {
                        //plik >> napis_s;
                        getline(plik, tekst);
                        strcpy( napis_s, tekst.c_str());
                        dekodowanie(napis_s);
                        cout<< napis_s << endl; //wyœwietlenie linii
                    }
                        SetConsoleTitleA( "Pomocnik" );

                plik.close();
                }
                else
                {
                    errorlitsa();
                        SetConsoleTitleA( "Pomocnik" );
                }

        cout << endl;
                wcsncpy(napis, L"Kliknij dowolny przycisk, aby kontynuować!", 1024);
        wprintf(L"%s", napis);
    cout<< endl;
    getch();
}

bool nnotatka()
{
    SetConsoleTitleA( "Pomocnik - Tworzenie notatki" );
            log();
            system("cls");
            mkdir("c:\\PlikiPomocnik\\Notatki");
            if(zalogowany == true)
            {
                string pathh = "c:\\PlikiPomocnik\\Users\\" + nickname + "\\Notatki";
               mkdir(pathh.c_str());
            }
            //system("mkdir c:\\PlikiPomocnik\\Notatki");
            string nazwa;
            cin.clear();
            cout << "Nazwa Notatki:";
            cin >> nazwa;
            nazwa += ".txt";
                    string dysk = "c:\\PlikiPomocnik\\Notatki\\";
                    if(zalogowany == true)
                    {
                        dysk = "c:\\PlikiPomocnik\\Users\\" + nickname +"\\Notatki\\";
                    }
             dysk+=nazwa;
            wcsncpy(napis, L"Treść notatki: ", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            string notatka;
            cin.get();
            getline( cin, notatka);
            fstream plik;
            plik.open(dysk.c_str(), ios::out );
            plik << notatka;
            plik.close();
            log();
            schowek_programowy = "[nnotatka] path: " + dysk + " \n";
            schowek_programowy += notatka + " \n";

            //SetConsoleTitleA( "Pomocnik" );
            cout << endl;
                wcsncpy(napis, L"Kliknij dowolny przycisk, aby kontynuować!", 1024);
        wprintf(L"%s", napis);
    cout<< endl;
    getch();
    napisy_p();
}

bool nnotatka_szyf()
{
    SetConsoleTitleA( "Pomocnik - Tworzenie notatki" );
            log();
            system("cls");
            mkdir("c:\\PlikiPomocnik\\Notatki");
            if(zalogowany == true)
            {
                string pathh = "c:\\PlikiPomocnik\\Users\\" + nickname + "\\Notatki";
               mkdir(pathh.c_str());
            }
            //system("mkdir c:\\PlikiPomocnik\\Notatki");
            string nazwa;
            cin.clear();
            cout << "Nazwa Notatki:";
            cin >> nazwa;
            nazwa += ".txtp";
                    string dysk = "c:\\PlikiPomocnik\\Notatki\\";
                    if(zalogowany == true)
                    {
                        dysk = "c:\\PlikiPomocnik\\Users\\" + nickname +"\\Notatki\\";
                    }
             dysk+=nazwa;
            wcsncpy(napis, L"Treść notatki: ", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            char napis_s[10000];
            cin.get();
            cin.get(napis_s, 10000);
            kodowanie(napis_s);

            fstream plik;
            plik.open(dysk.c_str(), ios::out );
            plik << napis_s;
            plik.close();
            log();

            //SetConsoleTitleA( "Pomocnik" );
            cout << endl;
                wcsncpy(napis, L"Kliknij dowolny przycisk, aby kontynuować!", 1024);
        wprintf(L"%s", napis);
    cout<< endl;
    getch();
    napisy_p();
}


bool zm_kolor_dnia()
{
    int kon=0;
    while(kon != 1)
    {
     cout << "Kolor dnia" << endl;
            cout << "Stan funkcji:" << wczyt_kolor_dnia << endl;
            if(wczyt_kolor_dnia == 0)
            {
                wcsncpy(napis, L" Wyłączone", 1024);
                wprintf(L"%s", napis);
                cout << endl;
            }
            if(wczyt_kolor_dnia == 1)
            {
                wcsncpy(napis, L" Włączone", 1024);
                wprintf(L"%s", napis);
                cout << endl;
            }
                    cout << "-------------" << endl;
                    wcsncpy(napis, L"!! Wpisz liczbę !!", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
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
                    if(odp== "1") // ust_logi on /
                        {
                            wczyt_kolor_dnia = true;
                            if(zalogowany == true)
                            {
                                kon = 1;
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
                                plik.open ("C://PlikiPomocnik//kolor_dnia_ust.txt", ios::out);
                                plik << "1";
                                plik.close();
                                }
                                kon = 1;
                            }



                            //-----------------------------

                            cout << "Zapisano zmiane" << endl;
                            wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                            getch();
                            menu_opcje(arg0global);
                        }
                    if(odp=="2")// ust_logi off
                        {
                            wczyt_kolor_dnia = false;
                            if(zalogowany == true)
                            {
                                kon =1;
                                zal_zapis_uat(); // zapisywanie ustawień dla zalogowanych
                            }
                            else
                            {
                                kon = 1;
                                if(nowy_sys_zap_ust == true) // jeśli jest włączony nowy system zapisywania ustawien
                                {
                                    zapis_plik_ustawien(); //zapisywanie ustawień / nowy_sys_zap_ust
                                }
                                else
                                {
                                    fstream plik;mkdir("C:/PlikiPomocnik");
                                    plik.open ("C://PlikiPomocnik//kolor_dnia_ust.txt", ios::out);
                                    plik << "0";
                                    plik.close();
                                }
                            }

                            //-----------------------------

                            cout << "Zapisano zmiane" << endl;
                            wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                        wprintf(L"%s", napis);
                        cout << endl;
                            getch();
                            napisy_p();
                        }
    }
}

bool zm_data_napisy_p()
{
    int kon=0;
    while(kon != 1)
    {
     wcsncpy(napis, L"Wyświetlanie daty.", 1024);
        wprintf(L"%s", napis);

    cout<< endl;
            cout << "Stan funkcji:" << datanap << endl;
            if(datanap == 0)
            {
                wcsncpy(napis, L" Wyłączone", 1024);
                wprintf(L"%s", napis);
                cout << endl;
            }
            if(datanap == 1)
            {
                wcsncpy(napis, L" Włączone", 1024);
                wprintf(L"%s", napis);
                cout << endl;
            }
                    cout << "-------------" << endl;
                    wcsncpy(napis, L"!! Wpisz liczbę !!", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
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
                    if(odp== "1") // ust_logi on /
                        {
                            datanap= true;
                            if(nowy_sys_zap_ust == true)
                            {
                                zapis_plik_ustawien();
                            }
                            else
                            {
                               fstream plik;
                            mkdir("C:/PlikiPomocnik");
                            plik.open ("C://PlikiPomocnik//datanap.txt", ios::out);
                            plik << "1";
                            plik.close();
                            }
                            kon = 1;

                            //-----------------------------

                            cout << "Zapisano zmiane" << endl;
                            wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                            getch();
                            menu_opcje(arg0global);
                        }
                    if(odp=="2")// ust_logi off
                        {
                            datanap = false;
                            kon = 1;
                            if(nowy_sys_zap_ust == true)
                            {
                                zapis_plik_ustawien();
                            }
                            else
                            {
                              fstream plik;
                            mkdir("C:/PlikiPomocnik");
                            plik.open ("C://PlikiPomocnik//datanap.txt", ios::out);
                            plik << "0";
                            plik.close();
                            }

                            //-----------------------------

                            cout << "Zapisano zmiane" << endl;
                            wcsncpy(napis, L"Kliknij dowolny przycisk aby kontynuować!", 1024);
                wprintf(L"%s", napis);
                        cout << endl;
                            getch();
                            menu_opcje(arg0global);
                        }
    }
}

int porownywanie_zawartosci_plikow_full(string & path1, string & path2)
{
    clock_t start, stop;
    start = clock();
    wcsncpy(napis, L"Porównywanie każdej linii pliku z drugim plikiem", 1024);
                wprintf(L"%s", napis);
                cout << endl;
    string tekstt;
    int aktualna_pozycaj = 0; // aktualna pozycaj odczytu linii pliku
    int ilosc_w1 = 0; // zakres wierszy w pierwszym pliku
    int ilosc_w2 = 0; // zakres wierszy w drugim pliku
    fstream plikz1;
    wcsncpy(napis, L"[Etap 1/5] Obliczanie ilości linii wierszy pierwszego pliku", 1024);
                wprintf(L"%s", napis);
                cout << endl;
    //*===========================kom
    ilosc_w1 = ilosc_linii_w_pliku(path1);

    string tekst_pliku_1[ilosc_w1];
    wcsncpy(napis, L"[Etap 2/5] Ładowanie zawartosci pierwszego pliku", 1024);
                wprintf(L"%s", napis);
                cout << endl;
    plikz1.open(path1.c_str(), ios::in );
    if(plikz1.good() == true)
    {
        string zmpomoc;
        for(int i = 0; i < ilosc_w1&& plikz1>> zmpomoc; ++i)
            { // (1)
                tekst_pliku_1[i] = zmpomoc;
            }

        plikz1.close();
    }
    else
    {
        errorlitsa(); // informacje o błędzie
    }

    //======================================================================
    aktualna_pozycaj = 0;
    //======================================================================
    wcsncpy(napis, L"[[Etap 3/5] Obliczanie ilości linii wierszy drugiego pliku", 1024);
                wprintf(L"%s", napis);
                cout << endl;

    ilosc_w2 = ilosc_linii_w_pliku(path2);

    string tekst_pliku_2[ilosc_w2];
    fstream plikz4;
    wcsncpy(napis, L"[Etap 4/5] Ładowanie zawartosci deugiego pliku", 1024);
                wprintf(L"%s", napis);
                cout << endl;
    plikz4.open(path2.c_str(), ios::in );
    if(plikz4.good() == true)
    {
        string zmpomoc;
        for(int i = 0; i < ilosc_w2&& plikz4>> zmpomoc; ++i)
            { // (1)
                tekst_pliku_2[i] = zmpomoc;
            }
        plikz4.close();
    }
    else
    {
        errorlitsa(); // informacje o błędzie
    }
//==========================================================
/*
------------------------------------------------------------
    Etap porównywania
------------------------------------------------------------
*/
//==========================================================
    wcsncpy(napis, L"[Etap 5/5] porównywanie zawartości plików", 1024);
        wprintf(L"%s", napis);
    cout<< endl;
    bool taka_sama_dl;
    if(ilosc_w1 == ilosc_w2)
    {
        taka_sama_dl = true;
    }
    else
    {
        taka_sama_dl = false;
    }

    if(debugowanie == true)
    {
        cout << "taka_sama_dl: " << taka_sama_dl << endl;
    }
    aktualna_pozycaj = 0;
    int numer = 0;
    int pasuje = 0;
    int nie_pasuje = 0;
    int kon =0;
    int kon2 =0;
    /*
    while(kon != 1)
    {
        if(aktualna_pozycaj >= ilosc_w1)
        {
            kon =1;
        }

        while(kon2 != 1)
        {
            if(numer >= ilosc_w2)
            {
                kon2 =1;
            }

            if(debugowanie == true)
            {
                cout << "tekst_pliku_1 == tekst_pliku_2 |> \n" << tekst_pliku_1[aktualna_pozycaj] << "[=]"<< tekst_pliku_2[numer] << endl;
                cout << "\n Numer:" << numer << endl;
                cout << "\n aktualna_pozycaj:" << aktualna_pozycaj << endl;
            }

            if(tekst_pliku_1[aktualna_pozycaj] == tekst_pliku_2[numer])
            {
                if(debugowanie == true)
                {
                    cout << ">true" << endl;
                }
            }
            else
            {
                if(debugowanie == true)
                {
                    cout << ">false" << endl;
                }
            }
            numer++;
        }

        aktualna_pozycaj++;
        numer=0;
        kon2 = 0;
    }

    */
    for (int i = 0; i < ilosc_w1; i++)
    {
        for (int j = 0; j < ilosc_w2; j++)
        {
            if(debugowanie == true)
            {
                cout << "tekst_pliku_1 == tekst_pliku_2 |> \n" << tekst_pliku_1[i] << "[=]"<< tekst_pliku_2[j] << endl;
                cout << "\n i:" << i << endl;
                cout << "\n j:" << j << endl;
            }

            if (tekst_pliku_1[i] == tekst_pliku_2[j])
            {
                if(debugowanie == true)
                {
                    cout << ">true" << endl;
                }
                pasuje++;
            }
            else
            {
                if(debugowanie == true)
                {
                    cout << ">false" << endl;
                }
                nie_pasuje++;
            }
        }
    }

        cout << endl << endl << "Podsumowanie" << endl;
        cout << "------------------" << endl;
        stop = clock();

        long double czas = (long double)(stop-start)/ CLOCKS_PER_SEC;
            cout << "Czas: "<< czas << "sek."<<endl;
        cout << "==================================" << endl;
        wcsncpy(napis, L"Ilość linii pierwszego pliku: ", 1024);
        wprintf(L"%s", napis);
        cout << ilosc_w1 << endl;
        wcsncpy(napis, L"Ilość linii pierwszego pliku: ", 1024);
        wprintf(L"%s", napis);
        cout << ilosc_w2 << endl;
        cout << "==================================" << endl;

    wcsncpy(napis, L"Ilość zgodnych linii:", 1024);
        wprintf(L"%s", napis);
    cout << pasuje << endl;
    wcsncpy(napis, L"Ilość nie zgodnych linii:", 1024);
        wprintf(L"%s", napis);
    cout << nie_pasuje << endl;
    cout << "==================================" << endl;
    wcsncpy(napis, L"Kliknij dowolny przycisk, aby kontynuować!", 1024);
        wprintf(L"%s", napis);
    cout<< endl;
    getch();
    napisy_p();
}

//=================================================================================
int porownywanie_zawartosci_plikow_zwykle(string & path1, string & path2)
{
    clock_t start, stop;
    start = clock();
    cout << "Porównywanie każdej linii pliku z drugim plikiem" << endl;
    string tekstt;
    int aktualna_pozycaj = 0; // aktualna pozycaj odczytu linii pliku
    int ilosc_w1 = 0; // zakres wierszy w pierwszym pliku
    int ilosc_w2 = 0; // zakres wierszy w drugim pliku
    fstream plikz1;
    wcsncpy(napis, L"[Etap 1/5] Obliczanie ilości linii wierszy pierwszego pliku", 1024);
                wprintf(L"%s", napis);
                cout << endl;

    ilosc_w1 = ilosc_linii_w_pliku(path1);

    string tekst_pliku_1[ilosc_w1];
    wcsncpy(napis, L"[Etap 2/5] Ładowanie zawartosci pierwszego pliku", 1024);
                wprintf(L"%s", napis);
                cout << endl;
    plikz1.open(path1.c_str(), ios::in );
    if(plikz1.good() == true)
    {
        string zmpomoc;
        for(int i = 0; i < ilosc_w1&& plikz1>> zmpomoc; ++i)
            { // (1)
                tekst_pliku_1[i] = zmpomoc;
            }

        plikz1.close();
    }
    else
    {
        errorlitsa(); // informacje o błędzie
    }

    //======================================================================
    aktualna_pozycaj = 0;
    //======================================================================
    wcsncpy(napis, L"[[Etap 3/5] Obliczanie ilości linii wierszy drugiego pliku", 1024);
                wprintf(L"%s", napis);
                cout << endl;

    ilosc_w2 = ilosc_linii_w_pliku(path2);

    string tekst_pliku_2[ilosc_w2];
    fstream plikz4;
    wcsncpy(napis, L"[Etap 4/5] Ładowanie zawartosci deugiego pliku", 1024);
                wprintf(L"%s", napis);
                cout << endl;
    plikz4.open(path2.c_str(), ios::in );
    if(plikz4.good() == true)
    {
        string zmpomoc;
        for(int i = 0; i < ilosc_w2&& plikz4>> zmpomoc; ++i)
            { // (1)
                tekst_pliku_2[i] = zmpomoc;
            }
        plikz4.close();
    }
    else
    {
        errorlitsa(); // informacje o błędzie
    }
//==========================================================
/*
------------------------------------------------------------
    Etap porównywania
------------------------------------------------------------
*/
//==========================================================
    wcsncpy(napis, L"[Etap 5/5] porównywanie zawartości plików", 1024);
        wprintf(L"%s", napis);
    cout<< endl;
    bool taka_sama_dl;
    if(ilosc_w1 == ilosc_w2)
    {
        taka_sama_dl = true;
    }
    else
    {
        taka_sama_dl = false;
    }

    if(debugowanie == true)
    {
        cout << "taka_sama_dl: " << taka_sama_dl << endl;
    }
    aktualna_pozycaj = 0;
    int numer = 0;
    int pasuje = 0;
    int nie_pasuje = 0;
    int kon =0;
    int kon2 =0;
    /*
    while(kon != 1)
    {
        if(aktualna_pozycaj >= ilosc_w1)
        {
            kon =1;
        }

        while(kon2 != 1)
        {
            if(numer >= ilosc_w2)
            {
                kon2 =1;
            }

            if(debugowanie == true)
            {
                cout << "tekst_pliku_1 == tekst_pliku_2 |> \n" << tekst_pliku_1[aktualna_pozycaj] << "[=]"<< tekst_pliku_2[numer] << endl;
                cout << "\n Numer:" << numer << endl;
                cout << "\n aktualna_pozycaj:" << aktualna_pozycaj << endl;
            }

            if(tekst_pliku_1[aktualna_pozycaj] == tekst_pliku_2[numer])
            {
                if(debugowanie == true)
                {
                    cout << ">true" << endl;
                }
            }
            else
            {
                if(debugowanie == true)
                {
                    cout << ">false" << endl;
                }
            }
            numer++;
        }

        aktualna_pozycaj++;
        numer=0;
        kon2 = 0;
    }

    */
    for (int i = 0; i < ilosc_w1; i++)
    {

        if( i >= ilosc_w1 || i >= ilosc_w2)
        {
            break;
        }
            if(debugowanie == true)
            {
                cout << "tekst_pliku_1 == tekst_pliku_2 |> \n" << "{" << tekst_pliku_1[i] << "[=]"<< tekst_pliku_2[numer] << "}" << endl;
                cout << "\n i:" << i << endl;
                cout << "\n numer:" << numer << endl;
            }

            if (tekst_pliku_1[i] == tekst_pliku_2[numer])
            {
                if(debugowanie == true)
                {
                    cout << ">true" << endl;
                }
                pasuje++;
            }
            else
            {
                if(debugowanie == true)
                {
                    cout << ">false" << endl;
                }
                nie_pasuje++;
            }
        numer++;
    }
    cout << endl << endl << "Podsumowanie" << endl;
        cout << "------------------" << endl;

    stop = clock();

        long double czas = (long double)(stop-start)/ CLOCKS_PER_SEC;
            cout << "Czas: "<< czas << "sek."<<endl;

            cout << "==================================" << endl;
        wcsncpy(napis, L"Ilość linii pierwszego pliku: ", 1024);
        wprintf(L"%s", napis);
        cout << ilosc_w1 << endl;
        wcsncpy(napis, L"Ilość linii pierwszego pliku: ", 1024);
        wprintf(L"%s", napis);
        cout << ilosc_w2 << endl;
        cout << "==================================" << endl;

    wcsncpy(napis, L"Ilość zgodnych linii:", 1024);
        wprintf(L"%s", napis);
    cout << pasuje << endl;
    wcsncpy(napis, L"Ilość nie zgodnych linii:", 1024);
        wprintf(L"%s", napis);
    cout << nie_pasuje << endl;
    cout << "==================================" << endl;
    wcsncpy(napis, L"Kliknij dowolny przycisk, aby kontynuować!", 1024);
        wprintf(L"%s", napis);
    cout<< endl;
    getch();
    napisy_p();
}

int ilosc_linii_w_pliku(string & path)
{
    string line;
     unsigned int count = 0;
    ifstream f(path.c_str());
    while(getline(f, line))
        count++;
        return count;
}

//==========================
int menu_porownywanie_plikow()
{
    bool kon = false;
    while(kon != true)
    {
        system("cls");
        wcsncpy(napis, L"Porównywanie plików", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"Wybierz typ porównywqania", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"0 = Wyjście z menu", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"1 = Szczegółowe porównanie dwóch plików (Plika A linia x(+ każda następna) jest porównywana z każdą linią pliku B)", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"2 = Porównanie  liniowe tego samego indeksu (Plika A i Plik B linia x, następnie porównanie {np. drugiej} linii z pliku A i B) + następne linie)", 1024);
            wprintf(L"%s", napis);
            cout << endl;
            wcsncpy(napis, L"9 = Powrót ", 1024);
            wprintf(L"%s", napis);
            cout << endl;

        cout << ">";
            cin >> odp;

            if(odp == "0")
            {
                kon = true;
                napisy_p();
            }
            else if(odp == "1")
            {
                cin.clear();
                kon = true;
                system("cls");
                wcsncpy(napis, L"Wpisz scieżke do pierwszego pliku. Np. C:\\PlikiPomocnik\\Pomocniklog.txt", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                cout << ">";
                string path1;

                cin >> path1;
                wcsncpy(napis, L"Wpisz scieżke do drugiego pliku. Np. C:\\PlikiPomocnik\\Pomocniklog.txt", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                cout << ">";
                string path2;

                cin.clear();
                cin >> path2;
                path2;
                cin.sync();
                try
                {
                    porownywanie_zawartosci_plikow_full(path1, path2);
                }
                catch( runtime_error & e )
                {
                    cout << "Runtime error: " << e.what() << "  (ale nic nie szkodzi)\n";
                }
                catch( exception & e )
                {
                    cout << "Inny standardowy wyjatek: " << e.what() << '\n';
                    // Rzuć złapany wyjątek ponownie
                    throw;
                    // Nie:
                    //throw e;
                    // Patrz: czerwona ramka
                }
                catch( int )
                {
                    cout << "Mowilem, zebys nie rzucal int >:/\n";
                    // Rzuć nowy, inny wyjątek
                    throw std::logic_error( "Nieoczekiwany int" );
                }
                catch(...)
                {
                    cout << "Nieoczekiwany, nieznany wyjatek!\n";
                    throw logic_error( "Zlapano nieznany wyjatek" );
                }
            }
            else if(odp == "2")
            {
                cin.clear();
                kon = true;
                system("cls");
                wcsncpy(napis, L"Wpisz scieżke do pierwszego pliku. Np. C:\\PlikiPomocnik\\Pomocniklog.txt", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                cout << ">";
                string path1;

                cin >> path1;
                wcsncpy(napis, L"Wpisz scieżke do drugiego pliku. Np. C:\\PlikiPomocnik\\Pomocniklog.txt", 1024);
                wprintf(L"%s", napis);
                cout << endl;
                cout << ">";
                string path2;

                cin.clear();
                cin >> path2;
                path2;
                cin.sync();
                   porownywanie_zawartosci_plikow_zwykle(path1, path2);

            }
            else if(odp == "9")
            {
                kon = true;
                plik_menu();
            }
    }
}
//
