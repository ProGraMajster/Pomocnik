#ifndef plik2_hpp
#define plik2_hpp

#include <iostream>
#include <string>



using namespace std;

int dodajLiczby(long long a, long long b );

string & foo (string & tekstwczytany);
//--------------------------------------------------

int menu_porownywanie_plikow();

int spr_polaczenia_inter();

int wczytywanie_koloru();

int wczytywanie_koloru_dnia(); // wczytywanie koloru zale¿nie od dnia tydodnia

int zapisywanie_koloru_dnia();

//--------------------------------------------------
int porownywanie_zawartosci_plikow_full(string & path1, string & path2);

int porownywanie_zawartosci_plikow_zwykle(string & path1, string & path2);

int ilosc_linii_w_pliku(string & path);

int wczytywanie_linia_stop(int numerstop);

int komendy_testy(string & odpo);

int play_sound_path(string & path);

int usun_plik(string & path);

int odczytywanie_pliku(string & path);

int odczytywanie_duzego_pliku(string & path);

string & rozmiar_pliku(string & path);

int kalp();

int wczytywanie_op_snet_star_sys();

int plik_menu();

int przypomnienie_tworzenie();

int przypomnienie_odczyt();

int data_napisy_p();

int wstep_zmiania_koloru();

bool onotatka();

bool onotatka_szyf();

bool nnotatka();

bool nnotatka_szyf();

bool zm_kolor_dnia();

bool zm_data_napisy_p();


//=======================================================================

#endif
