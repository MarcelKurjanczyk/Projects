// Wykresy_gieldowe.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace  std;

struct Dane
{
    char data[11];
    float open;
    float high;
    float low;
    float close;
    char volume[30];
};
void zapisywaniedopliku(float wysokosc_wykresu, char** wykres, ofstream& plik_wyjsciowy, Dane dane[]);
void wybornazwyplikow(char nazwa_wejscia[], char nazwa_wyjscia[]);
void wyswitlaniewykresu(float wysokosc_wykresu, char** wykres, Dane dane[]);
void generowaniewykresu(Dane dane[], float& wysokosc_wykresu, char** wykres);
float minimum(Dane dane[]);
float maksimum(Dane dane[]);
void wczytywanie(Dane dane[], ifstream& plik_wejsciowy);
float konwersja(char toconvert[]);
void powitanie();
bool menu();

int main()
{
    powitanie();

    if (menu())
    {

        char nazwa_wejscia[50];
        char nazwa_wyjscia[50];

        wybornazwyplikow(nazwa_wejscia, nazwa_wyjscia);             ///ta funckja pozwala zmienic standardowa nazwe pliku na wybrana

        ifstream plik_wejsciowy(nazwa_wejscia);

        if (!plik_wejsciowy.is_open())
        {
            cout << "Nie udalo sie otworzyc pliku" << endl;         ///wczytanie pliku i sprawdzenia otwarcia
            return 1;
        }

        ofstream plik_wyjsciowy(nazwa_wyjscia);

        if (!plik_wejsciowy.is_open())
        {
            cout << "Nie udalo sie otworzyc pliku" << endl;         ///plik wyjsciowy 
            return 1;
        }

        Dane* dane = new Dane[200];                         //tu deklaracja tablicyz danymi, ilosci danych

        wczytywanie(dane, plik_wejsciowy);       ///tu wczytuje dane i przerabiam dane na inne zmienne

        char** wykres = new char* [1000];
        for (int i = 0; i < 1000; i++)                  ///deklaracja dynamicznej 2 wymiarowej tablicy do wykresow
        {
            wykres[i] = new char[200];
        }

        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < 200; j++)    ///wstawianie wszedzie spacji
            {
                wykres[i][j] = ' ';
            }
        }

        float wysokosc_wykresu;
        cout << "PODAJ WYSOKOSC WYKRESU Z ZAKRESU (0-999) " << endl;      ///mozliwosc wybrou wysokosci wykresu
        cin >> wysokosc_wykresu;

        generowaniewykresu(dane, wysokosc_wykresu, wykres);

        zapisywaniedopliku(wysokosc_wykresu, wykres, plik_wyjsciowy, dane);

        wyswitlaniewykresu(wysokosc_wykresu, wykres, dane);

        for (int i = 0; i < 1000; i++)
        {
            delete[] wykres[i];             ///czysczenie kazdego wiersza
        }

        delete[] wykres;
        delete[] dane;
        plik_wejsciowy.close();             ///czyszczenie danych i zamykanie plikow
        plik_wyjsciowy.close();
    }
    else
    {
        return 0;
    }

    return 0;
}

/// tu konczy sie main

void zapisywaniedopliku(float wysokosc_wykresu, char** wykres, ofstream& plik_wyjsciowy, Dane dane[])
{
    plik_wyjsciowy << "[WARTOSCI]" << endl;
    for (int i = 0; i < wysokosc_wykresu; i++)
    {
        if (i == 0)
        {
            plik_wyjsciowy << maksimum(dane);
        }
        else if (i == wysokosc_wykresu - 1)
        {
            plik_wyjsciowy << minimum(dane);
        }
        else
        {
            plik_wyjsciowy << "     ";
        }
        plik_wyjsciowy << "-" << " ";

        for (int j = 0; j < 200; j++)
        {
            plik_wyjsciowy << wykres[i][j] << " ";
        }
        plik_wyjsciowy << endl;
    }

    plik_wyjsciowy << "     + ";

    for (int i = 0; i < 200; i++)
    {
        plik_wyjsciowy << "^" << " ";
    }
    plik_wyjsciowy << "[DZIEN]" << endl;

    plik_wyjsciowy << "       ";
    for (int i = 1; i <= 200; i++)
    {
        if (i == 1 || i == 200)
        {
            plik_wyjsciowy << i << " ";
        }
        else
        {
            plik_wyjsciowy << "  ";
        }
    }

    plik_wyjsciowy << endl;


}

void wybornazwyplikow(char nazwa_wejscia[], char nazwa_wyjscia[])
{
    cout << "PODAJ NAZWE PLIKU WEJSCIOWEGO: " << endl;
    cin >> nazwa_wejscia;
    cout << endl;
    cout << "PODAJ NAZWE PLIKU WYJSCIOWEGO: " << endl;
    cin >> nazwa_wyjscia;
    cout << endl;



}
void wyswitlaniewykresu(float wysokosc_wykresu, char** wykres, Dane dane[])
{
    cout << "CZY CHCESZ WYSWIETLIC KAWALEK WYKRESU W KONSOLI, JEZELI TAK PODAJ LICZBE Z ZAKRESU (0-200), JEZELI NIE WPISZ '0'" << endl;

    int ilewyswietlic;
    cin >> ilewyswietlic;
    if (ilewyswietlic > 0)
    {
        cout << "[WARTOSCI]" << endl;
        for (int i = 0; i < wysokosc_wykresu; i++)
        {
            if (i == 0)
            {
                cout << maksimum(dane);
            }
            else if (i == wysokosc_wykresu - 1)
            {
                cout << minimum(dane);
            }
            else
            {
                cout << "     ";
            }
            cout << "-" << " ";

            for (int j = 0; j < ilewyswietlic; j++)
            {
                cout << wykres[i][j] << " ";
            }
            cout << endl;
        }

        cout << "     + ";

        for (int i = 0; i < ilewyswietlic; i++)
        {
            cout << "^" << " ";
        }
        cout << "[DZIEN]" << endl;

        cout << "       ";
        for (int i = 1; i <= ilewyswietlic; i++)
        {
            if (i == 1 || i == ilewyswietlic)
            {
                cout << i << " ";
            }
            else
            {
                cout << "  ";
            }
        }

        cout << endl;
    }
}
void generowaniewykresu(Dane dane[], float& wysokosc_wykresu, char** wykres)
{
    float mini = minimum(dane);
    float maks = maksimum(dane);

    float skala;
    skala = (maks - mini) / wysokosc_wykresu;

    char cialo;

    for (int i = 0; i < 200; i++)    ///operacje na wykresie
    {

        if (dane[i].open < dane[i].close)
        {
            cialo = 'O';
        }
        else
        {
            cialo = '#';
        }

        for (int j = (maks - dane[i].high) / skala; j < (maks - dane[i].low) / skala; j++)  ///petla w ktorej wykres
        {

            wykres[j][i] = '|';

        }
        if (cialo == '#')
        {
            for (int j = (maks - dane[i].open) / skala; j < (maks - dane[i].close) / skala; j++)  ///petla w ktorej wykres
            {

                wykres[j][i] = '#';

            }
        }
        if (cialo == 'O')
        {
            for (int j = (maks - dane[i].close) / skala; j < (maks - dane[i].open) / skala; j++)  ///petla w ktorej wykres
            {

                wykres[j][i] = 'O';

            }
        }

    }
}

float minimum(Dane dane[])
{
    float mini = 100;
    for (int i = 0; i < 200; i++)
    {
        if (mini > dane[i].low)
        {
            mini = dane[i].low;
        }
    }
    return mini;
}

float maksimum(Dane dane[])
{
    float maks = 0;
    for (int i = 0; i < 200; i++)
    {
        if (maks < dane[i].high)
        {
            maks = dane[i].high;
        }
    }
    return maks;
}

void wczytywanie(Dane dane[], ifstream& plik_wejsciowy)
{
    char nieuzywane[60] = {};
    char linia[60] = {};

    for (int i = 0; i < 5816; i++)
    {
        plik_wejsciowy >> nieuzywane;
    }

    for (int i = 0; i < 200; i++)
    {
        int indeks = 0;
        char toconvert[20] = {};
        for (int j = 0; j < 60; j++)
        {
            linia[j] = NULL;
        }

        plik_wejsciowy >> linia;
        int indeks_toconvert = 0;

        while (linia[indeks] != ',')
        {
            dane[i].data[indeks] = linia[indeks];
            indeks++;

        }
        indeks++;

        while (linia[indeks] != ',')
        {
            toconvert[indeks_toconvert] = linia[indeks];
            indeks++;
            indeks_toconvert++;
        }
        indeks++;
        dane[i].open = konwersja(toconvert);
        indeks_toconvert = 0;

        while (linia[indeks] != ',')
        {
            toconvert[indeks_toconvert] = linia[indeks];
            indeks++;
            indeks_toconvert++;
        }
        indeks++;
        dane[i].high = konwersja(toconvert);
        indeks_toconvert = 0;

        while (linia[indeks] != ',')
        {
            toconvert[indeks_toconvert] = linia[indeks];
            indeks++;
            indeks_toconvert++;
        }
        indeks++;
        dane[i].low = konwersja(toconvert);
        indeks_toconvert = 0;

        while (linia[indeks] != ',')
        {
            toconvert[indeks_toconvert] = linia[indeks];
            indeks++;
            indeks_toconvert++;
        }
        indeks++;
        dane[i].close = konwersja(toconvert);
        indeks_toconvert = 0;

    }

}

float konwersja(char toconvert[])
{
    float mnoznik = 10;
    float liczba = 0;

    for (int i = 0; i < 20; i++)
    {
        if (toconvert[i] == 0)
        {
            break;
        }
        if (toconvert[i] != '.')
        {
            liczba += (((float)toconvert[i]) - 48.0) * mnoznik;
            mnoznik /= 10;
        }

    }
    toconvert = {};
    return liczba;

}

void powitanie()
{
    cout << char(201);
    for (int i = 0; i < 33; i++)
    {
        cout << char(205);
    }
    cout << char(187) << endl;

    cout << char(186) << "MARCEL KURJA" << char(227) << "CZYK, 197837,ACIR I " << char(186) << endl;

    cout << char(200);
    for (int i = 0; i < 33; i++)
    {
        cout << char(205);
    }
    cout << char(188);
    cout << endl;
}

bool menu()
{
    char klawisz;
    cout << "JEZELI CHCESZ ZAKONCZYC PROGRAM WCISNIJ 'q' " << endl;
    cout << "JEZELI CHCESZ NARYSOWAC I ZAPISAC WYKRES WCISNIJ 'g'" << endl;

    cin >> klawisz;

    while (klawisz != 'q' && klawisz != 'g')
    {
        cin >> klawisz;
    }
    if (klawisz == 'q')
    {
        return false;
    }
    if (klawisz == 'g')
    {
        return true;
    }
    return false;
}
