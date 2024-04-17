

#include <iostream>
#include<ctime>
#include<Windows.h>

using namespace std;

void porownaj_plansze(char plansza[][12], char plansza_z_atomami[][12], int wielkosc_planszy, int ile_atomow_na_planszy);
void wykonanie_strzalu(char planasz[][12], char plansza_z_atomami[][12], int polozenie_i, int polozenie_j, int* nr_strzalu, int wielkosc_planszy);
void losowanie_atomow(char plansza_z_atomami[][12], int wielkosc_planszy, int etap_rozgrywki, int* ile_atomow_na_planszy);
void wyswietleniemenu(char plansza[][12], char plansza_z_atomami[][12], int polozenie_i, int polozenie_j, int* wielkosc_planszy, int* ile_atomow_na_planszy, int ile_zaznaczonych_atomow, char* klawisz);
void wyswietleniemenu_2(char plansza[][12], char plansza_z_atomami[][12], int polozenie_i, int polozenie_j, int* wielkosc_planszy, int* ile_atomow_na_planszy, int ile_zaznaczonych_atomow);
void ile_atomow(int wielkosc_planszy, int etap_rozgrywki, int* ile_atomow_na_planszy);
void czysc_tablice(char plansza[][12], char plansza_z_atomami[][12]);
void wypelnienieplanszy(char planasza[][12], int wielkosc_planszy);
void wypisz_tablice_koniec(char plansza[][12], int wielkosc_planszy);
void wypisz_tablice(int wielkosc_planszy, char plansza[][12], int polozenie_i, int polozenie_j, int ile_atomow_na_planszy, int ile_zaznaczonych_atomow);
void powitanie();

int main()
{

    char plansza[12][12];
    char plansza_z_atomami[12][12];
    int etap_rozgrywki = 1;
    int polozenie_i = 0, polozenie_j = 0;
    char klawisz;
    int wielkosc_planszy;
    int nr_strzału = 1;
    int ile_zaznaczonych_atomow = 0;
    int ile_atomow_na_planszy;


    int licznik_do_cofania = 0;
    char poprzedni_ruch[5] = {};
    int ile_mozna_cofnac = 0;
    int ile_mozna_odcofnac = 0;
    bool poprawny_ruch = false;
    bool czy_poprzednie_u = false;
    czysc_tablice(plansza, plansza_z_atomami);
    powitanie();
    cout << "PODAJ WIELKOSC PLANSZY ZE ZBIORU {5,8,10} : ";

    cin >> wielkosc_planszy;
    while (wielkosc_planszy != 5 && wielkosc_planszy != 8 && wielkosc_planszy != 10)
    {
        cout << "NIEPOPRAWNA WIELKOSC PLANSZY. PODAJ JESZCZE RAZ:" << endl;
        cin >> wielkosc_planszy;
    }

    system("cls");

    ile_atomow(wielkosc_planszy, etap_rozgrywki, &ile_atomow_na_planszy);
    wypelnienieplanszy(plansza, wielkosc_planszy);
    wypisz_tablice(wielkosc_planszy, plansza, polozenie_i, polozenie_j, ile_atomow_na_planszy, ile_zaznaczonych_atomow);
    losowanie_atomow(plansza_z_atomami, wielkosc_planszy, etap_rozgrywki, &ile_atomow_na_planszy);

    while (cin >> noskipws >> klawisz)
    {


        czy_poprzednie_u = false;

        if (klawisz == 'u' || klawisz == 'U')
        {
            czy_poprzednie_u = true;

            if (ile_mozna_cofnac > 0)
            {
                ile_mozna_odcofnac++;
                ile_mozna_cofnac--;

                licznik_do_cofania--;

                if (poprzedni_ruch[licznik_do_cofania % 5] == 'a')
                {
                    klawisz = 'd';
                }
                else if (poprzedni_ruch[licznik_do_cofania % 5] == 'd')
                {
                    klawisz = 'a';
                }
                else if (poprzedni_ruch[licznik_do_cofania % 5] == 'w')
                {
                    klawisz = 's';
                }
                else if (poprzedni_ruch[licznik_do_cofania % 5] == 's')
                {
                    klawisz = 'w';
                }
                else if (poprzedni_ruch[licznik_do_cofania % 5] == 'o')
                {
                    klawisz = 'o';
                }
                else if (poprzedni_ruch[licznik_do_cofania % 5] == ' ')
                {
                    if (plansza[polozenie_i][polozenie_j] != 'H' && plansza[polozenie_i][polozenie_j] != 'R')
                    {
                        plansza[polozenie_i][polozenie_j] = '#';
                        plansza_z_atomami[polozenie_i][polozenie_j] = '#';
                        nr_strzału--;
                        for (int i = 0; i < wielkosc_planszy + 2; i++)
                        {
                            if (plansza[0][i] == 48 + nr_strzału)
                            {
                                plansza[0][i] = '#';
                                plansza_z_atomami[0][i] = '#';

                            }
                            else if (plansza[wielkosc_planszy + 1][i] == 48 + nr_strzału)
                            {
                                plansza[wielkosc_planszy + 1][i] = '#';
                                plansza_z_atomami[wielkosc_planszy + 1][i] = '#';
                            }
                            else if (plansza[i][0] == 48 + nr_strzału)
                            {
                                plansza[i][0] = '#';
                                plansza_z_atomami[i][0] = '#';
                            }
                            else if (plansza[i][wielkosc_planszy + 1] == 48 + nr_strzału)
                            {
                                plansza[i][wielkosc_planszy + 1] = '#';
                                plansza_z_atomami[i][wielkosc_planszy + 1] = '#';
                            }

                        }

                    }
                    else
                    {
                        plansza[polozenie_i][polozenie_j] = '#';
                        plansza_z_atomami[polozenie_i][polozenie_j] = '#';
                    }

                    system("cls");
                    wypisz_tablice(wielkosc_planszy, plansza, polozenie_i, polozenie_j, ile_atomow_na_planszy, ile_zaznaczonych_atomow);
                }
            }
            else
            {
                cout << "NIE MOZESZ DALEJ COFAC." << endl;
            }
        }

        if (klawisz == 'r' || klawisz == 'R')
        {
            czy_poprzednie_u = true;
            if (ile_mozna_odcofnac > 0)
            {
                if (poprzedni_ruch[licznik_do_cofania % 5] == 'a')
                {
                    klawisz = 'a';
                }
                else if (poprzedni_ruch[licznik_do_cofania % 5] == 'd')
                {
                    klawisz = 'd';
                }
                else if (poprzedni_ruch[licznik_do_cofania % 5] == 'w')
                {
                    klawisz = 'w';
                }
                else if (poprzedni_ruch[licznik_do_cofania % 5] == 's')
                {
                    klawisz = 's';
                }
                else if (poprzedni_ruch[licznik_do_cofania % 5] == 'o')
                {
                    klawisz = 'o';
                }
                else if (poprzedni_ruch[licznik_do_cofania % 5] == ' ')
                {
                    klawisz = ' ';
                }

                licznik_do_cofania++;
                ile_mozna_odcofnac--;
                ile_mozna_cofnac++;
            }
            else
            {
                cout << "NIE MOZESZ REDU." << endl;
            }
        }



        if (klawisz == 'd' || klawisz == 'D')
        {
            if (polozenie_j == wielkosc_planszy + 1)
            {
                poprawny_ruch = false;
                cout << "NIE MO" << char(189) << "ESZ WYKONA" << char(143) << " TAKIEGO RUCHU" << endl;
            }
            else
            {
                poprawny_ruch = true;
                polozenie_j++;
                wypelnienieplanszy(plansza, wielkosc_planszy);
                wypelnienieplanszy(plansza_z_atomami, wielkosc_planszy);
                system("cls");
                wypisz_tablice(wielkosc_planszy, plansza, polozenie_i, polozenie_j, ile_atomow_na_planszy, ile_zaznaczonych_atomow);
            }

        }
        if (klawisz == 'a' || klawisz == 'A')
        {
            if (polozenie_j == 0)
            {
                poprawny_ruch = false;
                cout << "NIE MO" << char(189) << "ESZ WYKONA" << char(143) << " TAKIEGO RUCHU" << endl;
            }
            else
            {
                poprawny_ruch = true;
                polozenie_j--;
                wypelnienieplanszy(plansza, wielkosc_planszy);
                wypelnienieplanszy(plansza_z_atomami, wielkosc_planszy);
                system("cls");
                wypisz_tablice(wielkosc_planszy, plansza, polozenie_i, polozenie_j, ile_atomow_na_planszy, ile_zaznaczonych_atomow);
            }
        }
        if (klawisz == 'w' || klawisz == 'W')
        {
            if (polozenie_i == 0)
            {
                poprawny_ruch = false;
                cout << "NIE MO" << char(189) << "ESZ WYKONA" << char(143) << " TAKIEGO RUCHU" << endl;
            }
            else
            {
                poprawny_ruch = true;
                polozenie_i--;
                wypelnienieplanszy(plansza_z_atomami, wielkosc_planszy);
                wypelnienieplanszy(plansza, wielkosc_planszy);
                system("cls");
                wypisz_tablice(wielkosc_planszy, plansza, polozenie_i, polozenie_j, ile_atomow_na_planszy, ile_zaznaczonych_atomow);
            }
        }
        if (klawisz == 's' || klawisz == 'S')
        {
            if (polozenie_i == wielkosc_planszy + 1)
            {
                poprawny_ruch = false;
                cout << "NIE MO" << char(189) << "ESZ WYKONA" << char(143) << " TAKIEGO RUCHU" << endl;
            }
            else
            {
                poprawny_ruch = true;
                polozenie_i++;
                wypelnienieplanszy(plansza, wielkosc_planszy);
                wypelnienieplanszy(plansza_z_atomami, wielkosc_planszy);
                system("cls");
                wypisz_tablice(wielkosc_planszy, plansza, polozenie_i, polozenie_j, ile_atomow_na_planszy, ile_zaznaczonych_atomow);
            }
        }

        if (klawisz == 'q' || klawisz == 'Q')
        {
            wyswietleniemenu(plansza, plansza_z_atomami, polozenie_i, polozenie_j, &wielkosc_planszy, &ile_atomow_na_planszy, ile_zaznaczonych_atomow, &klawisz);

            if (klawisz != 'g')
            {
                polozenie_i = 0;
                polozenie_j = 0;
                nr_strzału = 1;
                ile_zaznaczonych_atomow = 0;

            }

        }

        if (klawisz == ' ')
        {
            if (plansza[polozenie_i][polozenie_j] != '#' && plansza[polozenie_i][polozenie_j] != char(254))
            {
                poprawny_ruch = false;
                cout << "ODDALES JUZ STAD STRZAL" << endl;
            }
            else if (polozenie_i == 0 || polozenie_j == 0 || polozenie_i == wielkosc_planszy + 1 || polozenie_j == wielkosc_planszy + 1)
            {
                if (polozenie_i == 0 && polozenie_j == 0 || polozenie_i == 0 && polozenie_j == wielkosc_planszy + 1 || polozenie_i == wielkosc_planszy + 1 && polozenie_j == 0 || polozenie_i == wielkosc_planszy + 1 && polozenie_j == wielkosc_planszy + 1)
                {
                    poprawny_ruch = false;
                    cout << "STOISZ W ROGU SCIANY" << endl;
                }
                else
                {
                    poprawny_ruch = true;
                    system("cls");
                    wykonanie_strzalu(plansza, plansza_z_atomami, polozenie_i, polozenie_j, &nr_strzału, wielkosc_planszy);
                    wypisz_tablice(wielkosc_planszy, plansza, polozenie_i, polozenie_j, ile_atomow_na_planszy, ile_zaznaczonych_atomow);

                }

            }
            else
            {
                poprawny_ruch = false;
                cout << "NIE MOZESZ STAD ODDAC STRZALU" << endl;
            }

        }

        if (klawisz == 'o')
        {
            if (polozenie_i > 0 && polozenie_i < wielkosc_planszy + 1 && polozenie_j>0 && polozenie_j < wielkosc_planszy + 1 && ile_zaznaczonych_atomow < ile_atomow_na_planszy)
            {
                poprawny_ruch = true;
                if (plansza[polozenie_i][polozenie_j] == 'o')
                {
                    plansza[polozenie_i][polozenie_j] = '*';
                    ile_zaznaczonych_atomow--;
                    system("cls");
                    wypisz_tablice(wielkosc_planszy, plansza, polozenie_i, polozenie_j, ile_atomow_na_planszy, ile_zaznaczonych_atomow);
                }
                else
                {
                    plansza[polozenie_i][polozenie_j] = 'o';
                    ile_zaznaczonych_atomow++;
                    system("cls");
                    wypisz_tablice(wielkosc_planszy, plansza, polozenie_i, polozenie_j, ile_atomow_na_planszy, ile_zaznaczonych_atomow);
                }

            }
            else if (ile_zaznaczonych_atomow == ile_atomow_na_planszy)
            {
                poprawny_ruch = false;
                cout << "ZAZNACZYLES JUZ MAX ATOMOW" << endl;
            }
            else
            {
                poprawny_ruch = false;
                cout << "NIE JESTES W SRODKU PLANSZY" << endl;
            }

        }

        if (klawisz == 'k')
        {
            system("cls");
            porownaj_plansze(plansza, plansza_z_atomami, wielkosc_planszy, ile_atomow_na_planszy);

            polozenie_i = 0;
            polozenie_j = 0;
            nr_strzału = 1;
            ile_zaznaczonych_atomow = 0;
            wyswietleniemenu_2(plansza, plansza_z_atomami, polozenie_i, polozenie_j, &wielkosc_planszy, &ile_atomow_na_planszy, ile_zaznaczonych_atomow);
        }

        if (klawisz == 'p')
        {
            system("cls");
            wypisz_tablice_koniec(plansza_z_atomami, wielkosc_planszy);
            cout << char(94) << " ROZWIAZANIE " << char(94) << endl;
            cout << "OBECNA ROZGRYWKA ZAKONCZYLA SIE." << endl;

            polozenie_i = 0;
            polozenie_j = 0;
            nr_strzału = 1;
            ile_zaznaczonych_atomow = 0;
            wyswietleniemenu_2(plansza, plansza_z_atomami, polozenie_i, polozenie_j, &wielkosc_planszy, &ile_atomow_na_planszy, ile_zaznaczonych_atomow);
        }
        if (klawisz == 'H')
        {
            system("cls");
            wypisz_tablice(wielkosc_planszy, plansza_z_atomami, polozenie_i, polozenie_j, ile_atomow_na_planszy, ile_zaznaczonych_atomow);
            Sleep(2000);
            system("cls");
            wypisz_tablice(wielkosc_planszy, plansza, polozenie_i, polozenie_j, ile_atomow_na_planszy, ile_zaznaczonych_atomow);
        }
        if (poprawny_ruch == true&&czy_poprzednie_u==false)
        {
            if (klawisz == 'a' || klawisz == 'A' || klawisz == 'w' || klawisz == 'W' || klawisz == 's' || klawisz == 'S' || klawisz == 'd' || klawisz == 'D' || klawisz == ' ' || klawisz == 'o')
            {

                poprzedni_ruch[licznik_do_cofania % 5] = klawisz;
                licznik_do_cofania++;
                ile_mozna_odcofnac = 0;
                if (ile_mozna_cofnac == 5)
                    ile_mozna_cofnac = 5;
                else
                    ile_mozna_cofnac++;

            }
        }
    }
    return 0;
}




void porownaj_plansze(char plansza[][12], char plansza_z_atomami[][12], int wielkosc_planszy, int ile_atomow_na_planszy)
{
    int score = 0;
    for (int i = 1; i < wielkosc_planszy + 1; i++)
    {
        for (int j = 1; j < wielkosc_planszy + 1; j++)
        {
            if (plansza[i][j] == 'o' && plansza_z_atomami[i][j] == 'o')
            {
                plansza[i][j] = 'O';
                score++;
            }
            else if (plansza[i][j] == 'o' && plansza_z_atomami[i][j] != 'o')
            {
                plansza[i][j] = 'X';
            }
            else if (plansza_z_atomami[i][j] == 'o' && plansza[i][j] != 'o')
            {
                plansza[i][j] = 'O';
            }

        }
    }

    wypisz_tablice_koniec(plansza, wielkosc_planszy);
    cout << "TWOJ WYNIK TO: " << score << "/" << ile_atomow_na_planszy << " PKT." << endl;
}

void wykonanie_strzalu(char plansza[][12], char plansza_z_atomami[][12], int polozenie_i, int polozenie_j, int* nr_strzalu, int wielkosc_planszy)
{
    int miejsce_strzalu_i = polozenie_i;
    int miejsce_strzalu_j = polozenie_j;
    int kierunek_j = 0;
    int kierunek_i = 0;
    int poczatek_i = 0;
    int poczatek_j = 0;
    if (polozenie_j == 0 && polozenie_i > 0 && polozenie_i < wielkosc_planszy + 1)
    {
        kierunek_j = 1;
        kierunek_i = 0;
        poczatek_i = polozenie_i + 0;
        poczatek_j = polozenie_j + 1;
    }
    else if (polozenie_j == wielkosc_planszy + 1 && polozenie_i > 0 && polozenie_i < wielkosc_planszy + 1)
    {
        kierunek_j = -1;
        kierunek_i = 0;
        poczatek_i = polozenie_i + 0;
        poczatek_j = polozenie_j - 1;
    }
    else if (polozenie_i == 0 && polozenie_j > 0 && polozenie_j < wielkosc_planszy + 1)
    {
        kierunek_j = 0;
        kierunek_i = 1;
        poczatek_i = polozenie_i + 1;
        poczatek_j = polozenie_j + 0;
    }
    else if (polozenie_i == wielkosc_planszy + 1 && polozenie_j > 0 && polozenie_j < wielkosc_planszy + 1)
    {
        kierunek_j = 0;
        kierunek_i = -1;
        poczatek_i = polozenie_i - 1;
        poczatek_j = polozenie_j + 0;
    }


    for (int j = poczatek_j, i = poczatek_i; j < wielkosc_planszy + 1 && j > 0 && i < wielkosc_planszy + 1 && i > 0; j += kierunek_j, i += kierunek_i)
    {
        if (plansza_z_atomami[i][j] == 'o')
        {
            plansza[miejsce_strzalu_i][miejsce_strzalu_j] = 'H';
            plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = 'H';
            break;
        }
        else if (plansza_z_atomami[i - kierunek_j][j - kierunek_i] == 'o' || plansza_z_atomami[i + kierunek_j][j + kierunek_i] == 'o')
        {
            plansza[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
            plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
            break;
        }
        else if (plansza_z_atomami[i + kierunek_i][j + kierunek_j] == 'o')
        {
            plansza[miejsce_strzalu_i][miejsce_strzalu_j] = 'H';
            plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = 'H';
            break;
        }
        else if (plansza_z_atomami[i - kierunek_j][j - kierunek_i] == 'o' || plansza_z_atomami[i + kierunek_j][j + kierunek_i] == 'o')
        {
            plansza[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
            plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
            break;
        }
        else if (plansza_z_atomami[i - 1][j + 1] == 'o' && kierunek_i == 0 && kierunek_j == 1)
        {
            kierunek_i = 1;
            kierunek_j = 0;

            if (i != 1 && i != wielkosc_planszy && j != 1 && j != wielkosc_planszy)
            {
                continue;
            }

        }
        else if (plansza_z_atomami[i - 1][j - 1] == 'o' && kierunek_i == 0 && kierunek_j == -1)
        {
            kierunek_i = 1;
            kierunek_j = 0;

            if (i != 1 && i != wielkosc_planszy && j != 1 && j != wielkosc_planszy)
            {
                continue;
            }

        }
        else if (plansza_z_atomami[i + 1][j + 1] == 'o' && kierunek_i == 0 && kierunek_j == 1)
        {
            kierunek_i = -1;
            kierunek_j = 0;

            if (i != 1 && i != wielkosc_planszy && j != 1 && j != wielkosc_planszy)
            {
                continue;
            }

        }
        else if (plansza_z_atomami[i + 1][j - 1] == 'o' && kierunek_i == 0 && kierunek_j == -1)
        {
            kierunek_i = -1;
            kierunek_j = 0;

            if (i != 1 && i != wielkosc_planszy && j != 1 && j != wielkosc_planszy)
            {
                continue;
            }

        }
        else if (plansza_z_atomami[i + 1][j - 1] == 'o' && kierunek_i == 1 && kierunek_j == 0)
        {
            kierunek_i = 0;
            kierunek_j = 1;

            if (i != 1 && i != wielkosc_planszy && j != 1 && j != wielkosc_planszy)
            {
                continue;
            }

        }
        else if (plansza_z_atomami[i - 1][j - 1] == 'o' && kierunek_i == -1 && kierunek_j == 0)
        {
            kierunek_i = 0;
            kierunek_j = 1;

            if (i != 1 && i != wielkosc_planszy && j != 1 && j != wielkosc_planszy)
            {
                continue;
            }
        }

        else if (plansza_z_atomami[i + 1][j + 1] == 'o' && kierunek_i == 1 && kierunek_j == 0)
        {
            kierunek_i = 0;
            kierunek_j = -1;

            if (i != 1 && i != wielkosc_planszy && j != 1 && j != wielkosc_planszy)
            {
                continue;
            }
        }
        else if (plansza_z_atomami[i - 1][j + 1] == 'o' && kierunek_i == -1 && kierunek_j == 0)
        {
            kierunek_i = 0;
            kierunek_j = -1;

            if (i != 1 && i != wielkosc_planszy && j != 1 && j != wielkosc_planszy)
            {
                continue;
            }
        }


        if (j == 1 && kierunek_j == -1)
        {
            if (i == miejsce_strzalu_i && j - 1 == miejsce_strzalu_j)
            {
                plansza[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
                plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
            }
            else
            {
                plansza[miejsce_strzalu_i][miejsce_strzalu_j] = char(48 + *nr_strzalu);
                plansza[i][j - 1] = char(48 + *nr_strzalu);
                plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = char(48 + *nr_strzalu);
                plansza_z_atomami[i][j - 1] = char(48 + *nr_strzalu);

                (*nr_strzalu)++;
            }
            break;
        }
        if (j == wielkosc_planszy && kierunek_j == 1)
        {
            if (i == miejsce_strzalu_i && j + 1 == miejsce_strzalu_j)
            {
                plansza[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
                plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
            }
            else
            {
                plansza[miejsce_strzalu_i][miejsce_strzalu_j] = char(48 + *nr_strzalu);
                plansza[i][j + 1] = char(48 + *nr_strzalu);
                plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = char(48 + *nr_strzalu);
                plansza_z_atomami[i][j + 1] = char(48 + *nr_strzalu);

                (*nr_strzalu)++;
            }
            break;
        }
        if (i == 1 && kierunek_i == -1)
        {
            if (i - 1 == miejsce_strzalu_i && j == miejsce_strzalu_j)
            {
                plansza[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
                plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
            }
            else
            {
                plansza[miejsce_strzalu_i][miejsce_strzalu_j] = char(48 + *nr_strzalu);
                plansza[i - 1][j] = char(48 + *nr_strzalu);
                plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = char(48 + *nr_strzalu);
                plansza_z_atomami[i - 1][j] = char(48 + *nr_strzalu);

                (*nr_strzalu)++;
            }
            break;
        }
        if (i == wielkosc_planszy && kierunek_i == 1)
        {
            if (i + 1 == miejsce_strzalu_i && j == miejsce_strzalu_j)
            {
                plansza[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
                plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = 'R';
            }
            else
            {
                plansza[miejsce_strzalu_i][miejsce_strzalu_j] = char(48 + *nr_strzalu);
                plansza[i + 1][j] = char(48 + *nr_strzalu);
                plansza_z_atomami[miejsce_strzalu_i][miejsce_strzalu_j] = char(48 + *nr_strzalu);
                plansza_z_atomami[i + 1][j] = char(48 + *nr_strzalu);
                (*nr_strzalu)++;
            }
            break;
        }

    }

}

void losowanie_atomow(char plansza_z_atomami[][12], int wielkosc_planszy, int etap_rozgrywki, int* ile_atomow_na_planszy)
{
    wypelnienieplanszy(plansza_z_atomami, wielkosc_planszy);
    int x, y;

    srand(time(NULL));

    if (wielkosc_planszy == 5)
    {
        for (int i = 0; i < etap_rozgrywki + 2; i++)
        {
            x = rand() % 5 + 1;
            y = rand() % 5 + 1;
            while (plansza_z_atomami[x][y] == 'o')
            {
                x = rand() % 5 + 1;
                y = rand() % 5 + 1;
            }
            plansza_z_atomami[x][y] = 'o';

        }
    }
    if (wielkosc_planszy == 8)
    {
        for (int i = 0; i < etap_rozgrywki + 3; i++)
        {
            x = rand() % 8 + 1;
            y = rand() % 8 + 1;
            while (plansza_z_atomami[x][y] == 'o')
            {
                x = rand() % 8 + 1;
                y = rand() % 8 + 1;
            }
            plansza_z_atomami[x][y] = 'o';
        }
    }

    if (wielkosc_planszy == 10)
    {
        for (int i = 0; i < etap_rozgrywki + 5; i++)
        {
            x = rand() % 10 + 1;
            y = rand() % 10 + 1;
            while (plansza_z_atomami[x][y] == 'o')
            {
                x = rand() % 10 + 1;
                y = rand() % 10 + 1;
            }
            plansza_z_atomami[x][y] = 'o';
        }
    }

}

void wyswietleniemenu(char plansza[][12], char plansza_z_atomami[][12], int polozenie_i, int polozenie_j, int* wielkosc_planszy, int* ile_atomow_na_planszy, int ile_zaznaczonych_atomow, char* klawisz)
{
    int etap_rozgrywki;

    cout << "JEZELI CHCESZ WYJSC Z GRY WCISNIJ KLAWISZ: 'c' lub 'C':" << endl;
    cout << "JEZELI CHCESZ ROZPOCZAC NOWA GRE WCISNIJ KLAWISZ: 'n' lub 'N':" << endl;
    cout << "JEZELI CHCESZ KONTYNUOWAC WSCISNIJ 'g':" << endl;

    cin >> skipws >> *klawisz;
    while (*klawisz != 'c' && *klawisz != 'C' && *klawisz != 'n' && *klawisz != 'N' && *klawisz != 'g')
    {
        cout << "NIEPOPRAWNY KLAWISZ. PODAJ JESZCZE RAZ:" << endl;
        cin >> skipws >> klawisz;
    }
    if (*klawisz == 'c' || *klawisz == 'C')
    {
        exit(0);
    }
    else if (*klawisz == 'n' || *klawisz == 'N')
    {
        polozenie_i = 0;
        polozenie_j = 0;

        system("cls");

        cout << "JAKA ROZGRYWKE CHCESZ ROZPOCZAC ? PODAJ DANE:" << endl;
        cout << "WIELKOSC PLANSZY:" << endl;
        cin >> *wielkosc_planszy;
        while (*wielkosc_planszy != 5 && *wielkosc_planszy != 8 && *wielkosc_planszy != 10)
        {
            cout << "NIEPOPRAWNA WIELKOSC PLANSZY. PODAJ JESZCZE RAZ:" << endl;
            cin >> *wielkosc_planszy;
        }

        cout << "ETAP:" << endl;
        cin >> etap_rozgrywki;

        while (etap_rozgrywki > 3 || etap_rozgrywki < 1)
        {
            cout << "ZLE PODANY ETAP. PODAJ JESZCZE RAZ:";
            cin >> etap_rozgrywki;
        }

        system("cls");

        cout << "ROZPOCZYNAM ROZGRYWKE NA PLANSZY O WIELKOSCI: " << *wielkosc_planszy << " OD ETAPU NR: " << etap_rozgrywki << endl;

        ile_atomow(*wielkosc_planszy, etap_rozgrywki, ile_atomow_na_planszy);
        czysc_tablice(plansza, plansza_z_atomami);
        wypelnienieplanszy(plansza, *wielkosc_planszy);
        losowanie_atomow(plansza_z_atomami, *wielkosc_planszy, etap_rozgrywki, ile_atomow_na_planszy);
        wypisz_tablice(*wielkosc_planszy, plansza, polozenie_i, polozenie_j, *ile_atomow_na_planszy, ile_zaznaczonych_atomow);
    }
    else if (*klawisz == 'g')
    {
        system("cls");
        wypisz_tablice(*wielkosc_planszy, plansza, polozenie_i, polozenie_j, *ile_atomow_na_planszy, ile_zaznaczonych_atomow);
    }

}

void wyswietleniemenu_2(char plansza[][12], char plansza_z_atomami[][12], int polozenie_i, int polozenie_j, int* wielkosc_planszy, int* ile_atomow_na_planszy, int ile_zaznaczonych_atomow)
{
    char klawisz;
    int etap_rozgrywki;

    cout << "JEZELI CHCESZ WYJSC Z GRY WCISNIJ KLAWISZ: 'c' lub 'C':" << endl;
    cout << "JEZELI CHCESZ ROZPOCZAC NOWA GRE WCISNIJ KLAWISZ: 'n' lub 'N':" << endl;

    cin >> skipws >> klawisz;
    while (klawisz != 'c' && klawisz != 'C' && klawisz != 'n' && klawisz != 'N')
    {
        cout << "NIEPOPRAWNY KLAWISZ. PODAJ JESZCZE RAZ." << endl;
        cin >> skipws >> klawisz;
    }
    if (klawisz == 'c' || klawisz == 'C')
    {
        exit(0);
    }
    else
    {
        polozenie_i = 0;
        polozenie_j = 0;

        system("cls");

        cout << "JAKA ROZGRYWKE CHCESZ ROZPOCZAC ? PODAJ DANE:" << endl;
        cout << "WIELKOSC PLANSZY:" << endl;
        cin >> *wielkosc_planszy;
        while (*wielkosc_planszy != 5 && *wielkosc_planszy != 8 && *wielkosc_planszy != 10)
        {
            cout << "NIEPOPRAWNA WIELKOSC PLANSZY. PODAJ JESZCZE RAZ:" << endl;
            cin >> *wielkosc_planszy;
        }
        cout << "ETAP:" << endl;
        cin >> etap_rozgrywki;
        while (etap_rozgrywki > 3 || etap_rozgrywki < 1)
        {
            cout << "ZLE PODANY ETAP.PODAJ JESZCZE RAZ:";
            cin >> etap_rozgrywki;
        }

        system("cls");

        cout << "ROZPOCZYNAM ROZGRYWKE NA PLANSZY O WIELKOSCI: " << *wielkosc_planszy << " OD ETAPU NR: " << etap_rozgrywki << endl;

        ile_atomow(*wielkosc_planszy, etap_rozgrywki, ile_atomow_na_planszy);
        czysc_tablice(plansza, plansza_z_atomami);
        wypelnienieplanszy(plansza, *wielkosc_planszy);
        losowanie_atomow(plansza_z_atomami, *wielkosc_planszy, etap_rozgrywki, ile_atomow_na_planszy);
        wypisz_tablice(*wielkosc_planszy, plansza, polozenie_i, polozenie_j, *ile_atomow_na_planszy, ile_zaznaczonych_atomow);

    }


}

void ile_atomow(int wielkosc_planszy, int etap_rozgrywki, int* ile_atomow_na_planszy)
{
    if (wielkosc_planszy == 5)
    {
        *ile_atomow_na_planszy = etap_rozgrywki + 2;
    }
    else if (wielkosc_planszy == 8)
    {
        *ile_atomow_na_planszy = etap_rozgrywki + 3;
    }
    else if (wielkosc_planszy == 10)
    {
        *ile_atomow_na_planszy = etap_rozgrywki + 5;
    }
}

void czysc_tablice(char plansza[][12], char plansza_z_atomami[][12])
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            plansza[i][j] = '0';
            plansza_z_atomami[i][j] = '0';
        }
    }
}


void wypelnienieplanszy(char plansza[][12], int wielkosc_planszy)
{
    for (int i = 0; i < wielkosc_planszy + 2; i++)
    {
        for (int j = 0; j < wielkosc_planszy + 2; j++)
        {
            if (i == 0 || j == 0 || i == wielkosc_planszy + 1 || j == wielkosc_planszy + 1)
            {
                if (plansza[i][j] == '0' || plansza[i][j] == char(254))
                    plansza[i][j] = '#';
            }
            else
            {
                if (plansza[i][j] == '0' || plansza[i][j] == char(254))
                    plansza[i][j] = '*';
            }

        }
    }
}
void wypisz_tablice_koniec(char plansza[][12], int wielkosc_planszy)
{
    powitanie();

    for (int i = 0; i < wielkosc_planszy + 4; i++)
    {
        for (int j = 0; j < wielkosc_planszy + 4; j++)
        {
            if (i == 0 && j == 0)
            {

                cout << char(201);
            }
            else if (i == 0 && j == wielkosc_planszy + 3)
            {
                cout << char(205) << char(187);
            }
            else if (i == wielkosc_planszy + 3 && j == 0)
            {
                cout << char(200);
            }
            else if (i == wielkosc_planszy + 3 && j == wielkosc_planszy + 3)
            {
                cout << char(205) << char(188);
            }

            else if ((i > 0 && i < wielkosc_planszy + 3 && j == 0) || (i > 0 && i < wielkosc_planszy + 3 && j == wielkosc_planszy + 3))
            {
                cout << char(186);
            }
            else if ((j > 0 && j < wielkosc_planszy + 3 && i == 0) || (j > 0 && j < wielkosc_planszy + 3 && i == wielkosc_planszy + 3))
            {
                cout << char(205) << char(205);

            }

            else if ((i > 0 && i < wielkosc_planszy + 3 && j == 1) || (i > 0 && i < wielkosc_planszy + 3 && j == wielkosc_planszy + 2) || (j > 0 && j < wielkosc_planszy + 3 && i == 1) || (j > 0 && j < wielkosc_planszy + 3 && i == wielkosc_planszy + 2))
            {
                cout << " " << plansza[i - 1][j - 1];
                if (j == wielkosc_planszy + 2)
                    cout << " ";
            }
            else
            {
                if (j == 2)
                {
                    cout << " " << plansza[i - 1][j - 1] << " ";
                }
                else if (j == wielkosc_planszy + 1)
                {
                    cout << plansza[i - 1][j - 1];
                }
                else
                    cout << plansza[i - 1][j - 1] << " ";
            }

        }
        cout << endl;
    }

}

void wypisz_tablice(int wielkosc_planszy, char plansza[][12], int polozenie_i, int polozenie_j, int ile_atomow_na_planszy, int ile_zaznaczonych_atomow)
{
    powitanie();

    if (plansza[polozenie_i][polozenie_j] == '#' || plansza[polozenie_i][polozenie_j] == '*')
    {
        plansza[polozenie_i][polozenie_j] = char(254);
    }

    for (int i = 0; i < wielkosc_planszy + 4; i++)
    {
        for (int j = 0; j < wielkosc_planszy + 4; j++)
        {
            if (i == 0 && j == 0)
            {
                cout << char(201);
            }
            else if (i == 0 && j == wielkosc_planszy + 3)
            {
                cout << char(205) << char(187);
            }
            else if (i == wielkosc_planszy + 3 && j == 0)
            {
                cout << char(200);
            }
            else if (i == wielkosc_planszy + 3 && j == wielkosc_planszy + 3)
            {
                cout << char(205) << char(188);
            }
            else if ((i > 0 && i < wielkosc_planszy + 3 && j == 0) || (i > 0 && i < wielkosc_planszy + 3 && j == wielkosc_planszy + 3))
            {
                cout << char(186);
            }
            else if ((j > 0 && j < wielkosc_planszy + 3 && i == 0) || (j > 0 && j < wielkosc_planszy + 3 && i == wielkosc_planszy + 3))
            {
                cout << char(205) << char(205);
            }
            else if ((i > 0 && i < wielkosc_planszy + 3 && j == 1) || (i > 0 && i < wielkosc_planszy + 3 && j == wielkosc_planszy + 2) || (j > 0 && j < wielkosc_planszy + 3 && i == 1) || (j > 0 && j < wielkosc_planszy + 3 && i == wielkosc_planszy + 2))
            {
                cout << " " << plansza[i - 1][j - 1];
                if (j == wielkosc_planszy + 2)
                    cout << " ";
            }
            else
            {
                if (j == 2)
                {
                    cout << " " << plansza[i - 1][j - 1] << " ";
                }
                else if (j == wielkosc_planszy + 1)
                {
                    cout << plansza[i - 1][j - 1];
                }
                else
                    cout << plansza[i - 1][j - 1] << " ";
            }

        }
        cout << endl;
    }
    cout << "ZAZNACZYLES: " << ile_zaznaczonych_atomow << " ATOMOW NA: " << ile_atomow_na_planszy << " UKRYTYCH" << endl;
}

void powitanie() {
    cout << char(201);
    for (int i = 0; i < 73; i++)
    {
        cout << char(205);
    }
    cout << char(187) << endl;

    cout << char(186) << " WITAJ W GRZE BLACKBOX ZAPROJEKTOWANEJ PRZEZ : MARCEL KURJA" << char(227) << "CZYK, 197837,ACIR " << char(186) << endl;

    cout << char(200);
    for (int i = 0; i < 73; i++)
    {
        cout << char(205);
    }
    cout << char(188);
    cout << endl;
}
