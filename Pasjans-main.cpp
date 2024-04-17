
#include <iostream>
#include <vector>
#include <random>   
#include <algorithm>

using namespace std;

struct card {
    string color;
    int number;
    int red_black;    ///red - 0 black-1

    card() {
        color = "N";
        number = 0;
        red_black = -1;
    }
};


vector<card> generateDeck();

void distribution(vector<vector<card>>& stos_main, vector<card>& deck);

void print_cards(vector<card>& stos_pik, vector<card>& stos_trefl, vector<card>& stos_kier, vector<card>& stos_hearth, card side[], vector<vector<card>>& stos_main);

void move(vector<card>& stos_pik, vector<card>& stos_trefl, vector<card>& stos_kier, vector<card>& stos_hearth, card side[], vector<vector<card>>& stos_main);

void data_correction(string& name_take, string& name_destination, int& number_take, int& number_destination);

void IsitWin(vector<card>& stos_pik, vector<card>& stos_trefl, vector<card>& stos_kier, vector<card>& stos_hearth, bool& win);

int main()
{
    vector<card> deck = generateDeck();
    vector<vector<card>> stos_main;                              /// kontener wylosowanych kart które chcemy ułożyć
    vector<card> stos_pik, stos_trefl, stos_kier, stos_hearth;   ///docelowe kontenery w które układamy karty 0d A-K
    card side[4];

    bool win = false;

    card zeroCard;
    zeroCard.number = 0;
    zeroCard.color = "P";
    stos_pik.push_back(zeroCard);
    zeroCard.color = "T";                                       ///wpisanie 0 do docelowych stosow
    stos_trefl.push_back(zeroCard);
    zeroCard.color = "K";
    stos_kier.push_back(zeroCard);
    zeroCard.color = "S";
    stos_hearth.push_back(zeroCard);

    distribution(stos_main, deck);                                   ///tasowanie kart

    print_cards(stos_pik, stos_trefl, stos_kier, stos_hearth, side, stos_main);   /// 1 wypisanie kart

    while (true)
    {
        char key;
        cin >> key;

        switch (key)
        {

        case('m'):
        {

            move(stos_pik, stos_trefl, stos_kier, stos_hearth, side, stos_main); ///funckja wykonujaca przesuniecie karty

            print_cards(stos_pik, stos_trefl, stos_kier, stos_hearth, side, stos_main); //funckja wypisujaca karty

            IsitWin(stos_pik, stos_trefl, stos_kier, stos_hearth, win);

            if (win == true)
            {
                return 0;
            }

            break;
        }

        case('e'):
        {
            return 0;
        }

        default:
        {
            cout << "WRONG BUTTON" << endl;
            break;
        }

        }
    }


}

// KONIEC MAIN

vector<card> generateDeck() {
    vector<string> suits = { "S", "K", "P", "T" };
    vector<int> ranks = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };    /// A-K

    vector<card> deck;

    // Generowanie talii kart
    for (int i = 0; i < suits.size(); i++) {
        for (int j = 0; j < ranks.size(); j++) {
            card new_card;
            new_card.color = suits[i];
            new_card.number = ranks[j];
            if (suits[i] == "K" || suits[i] == "S")
            {
                new_card.red_black = 0;
            }
            else
            {
                new_card.red_black = 1;
            }
            deck.push_back(new_card);
        }
    }

    //Tasowanie talii
    random_device rd;   ///mechanizm do generowania liczb pseudolosowych
    mt19937 g(rd());   ///algorytm generatora liczb pseudolosowych
    shuffle(deck.begin(), deck.end(), g);   ///tasowanie za pomocą liczba pseudolosowych

    return deck;
}

void distribution(vector<vector<card>>& stos_main, vector<card>& deck)
{
    int rows[] = { 7, 7, 7,7,6,6,6,6 }; // liczba kart w każdym wierszu
    int index = 0; // indeks karty w talii

    for (int i = 0; i < 8; i++) {
        stos_main.emplace_back(); // dodanie nowego wiersza do stos_main
        for (int j = 0; j < rows[i]; j++) {
            stos_main[i].push_back(deck[index++]); // dodanie karty do stos_main
        }
    }
}

void print_cards(vector<card>& stos_pik, vector<card>& stos_trefl, vector<card>& stos_kier, vector<card>& stos_hearth, card side[], vector<vector<card>>& stos_main)
{
    system("cls");
    cout << "ZAD 8 PASJANS: MARCEL KURJANCZYK, RADOSLAW PLICHTA: " << endl;
    cout << " PRESS 'm' TO START A MOVE" << endl;
    cout << "PRESS 'e' TO EXIT THE PROGRAM" << endl;
    cout << "NAME OF THE DECKS: 'main' , 'side' , 'pik' , 'trefl' , 'kier' , 'serce' " << endl;
    cout << endl;

    cout << "STOS PIK: ";
    for (int i = 1; i < stos_pik.size(); i++)
    {
        cout << stos_pik[i].number << "_" << stos_pik[i].color << " -> ";
    }
    cout << endl;

    cout << "STOS TREFL: ";
    for (int i = 1; i < stos_trefl.size(); i++)
    {
        cout << stos_trefl[i].number << "_" << stos_trefl[i].color << " -> ";
    }
    cout << endl;

    cout << "STOS KIER: ";
    for (int i = 1; i < stos_kier.size(); i++)
    {
        cout << stos_kier[i].number << "_" << stos_kier[i].color << " -> ";
    }
    cout << endl;

    cout << "STOS HEARTH: ";
    for (int i = 1; i < stos_hearth.size(); i++)
    {
        cout << stos_hearth[i].number << "_" << stos_hearth[i].color << " -> ";
    }
    cout << endl;

    cout << "SIDE STOS:";
    for (int i = 0; i < 4; i++)
    {
        cout << side[i].number << "_" << side[i].color << " ";
    }
    cout << endl;

    for (int i = 0; i < 8; i++) {
        cout << "STOS " << i << ": ";

        for (int j = 0; j < stos_main[i].size(); j++) {


            if (stos_main[i][j].number < 10)
            {
                cout << " " << stos_main[i][j].number << "_" << stos_main[i][j].color << " -> ";
            }
            else
            {
                cout << stos_main[i][j].number << "_" << stos_main[i][j].color << " -> ";
            }
        }

        cout << endl;
    }
}

void move(vector<card>& stos_pik, vector<card>& stos_trefl, vector<card>& stos_kier, vector<card>& stos_hearth, card side[], vector<vector<card>>& stos_main)
{

    string  name_take, name_destination;
    int number_take, number_destination;

    data_correction(name_take, name_destination, number_take, number_destination); /// sprawdzanie poprawnosci danych ^^

    card t1_card;   ///tymczasowe karty do przenoszenia
    card t2_card;

    if (name_take == "main")
    {
        t1_card = stos_main[number_take][stos_main[number_take].size() - 1];
        if (stos_main[number_take].size() > 0) ///sprawdzamy czy jest co przeniesc
        {
            ///main do main
            if (name_destination == "main")
            {
                if (stos_main[number_destination].size() == 0)   ///  sprawdzamy czy mozemy przeniesc bezwarunkowo
                {
                    stos_main[number_destination].push_back(t1_card);
                    stos_main[number_take].pop_back();
                }
                else
                {
                    t2_card = stos_main[number_destination][stos_main[number_destination].size() - 1];
                    if (t1_card.number + 1 == t2_card.number && t1_card.red_black != t2_card.red_black)
                    {
                        stos_main[number_destination].push_back(t1_card);
                        stos_main[number_take].pop_back();
                    }

                }
            }

            ///main do side
            if (name_destination == "side")
            {
                if (side[number_destination].number == 0)
                {
                    side[number_destination] = t1_card;
                    stos_main[number_take].pop_back();
                }
            }

            ///main do pik
            if (name_destination == "pik")
            {
                t2_card = stos_pik[stos_pik.size() - 1];

                if (t1_card.number == t2_card.number + 1 && t1_card.color == t2_card.color)
                {
                    stos_pik.push_back(t1_card);
                    stos_main[number_take].pop_back();
                }

            }
            //main do trefl
            if (name_destination == "trefl")
            {
                t2_card = stos_trefl[stos_trefl.size() - 1];

                if (t1_card.number == t2_card.number + 1 && t1_card.color == t2_card.color)
                {
                    stos_trefl.push_back(t1_card);
                    stos_main[number_take].pop_back();
                }

            }
            ///main do kier
            if (name_destination == "kier")
            {
                t2_card = stos_kier[stos_kier.size() - 1];

                if (t1_card.number == t2_card.number + 1 && t1_card.color == t2_card.color)
                {
                    stos_kier.push_back(t1_card);
                    stos_main[number_take].pop_back();
                }

            }
            //main do serce
            if (name_destination == "serce")
            {
                t2_card = stos_hearth[stos_hearth.size() - 1];

                if (t1_card.number == t2_card.number + 1 && t1_card.color == t2_card.color)
                {
                    stos_hearth.push_back(t1_card);
                    stos_main[number_take].pop_back();
                }

            }
        }
    }

    ///koniec z main

    if (name_take == "side")
    {
        t1_card = side[number_take];
        if (side[number_take].number > 0)
        {
            ///z side do main
            if (name_destination == "main")
            {
                if (stos_main[number_destination].size() == 0)      ///sprawdzamy czy mozemy przeniesc bezwarunkowo
                {
                    stos_main[number_destination].push_back(t1_card);
                    side[number_take].number = 0;
                    side[number_take].color = "N";             ///czyscimy miejsce w side
                    side[number_take].red_black = -1;
                }
                else
                {
                    t2_card = stos_main[number_destination][stos_main[number_destination].size() - 1];
                    if (t1_card.number + 1 == t2_card.number && t1_card.red_black != t2_card.red_black)
                    {
                        stos_main[number_destination].push_back(t1_card);
                        side[number_take].number = 0;
                        side[number_take].color = "N";
                        side[number_take].red_black = -1;
                    }

                }

            }
            ///side do docelowych

           ///side do pik
            if (name_destination == "pik")
            {
                t2_card = stos_pik[stos_pik.size() - 1];

                if (t1_card.number == t2_card.number + 1 && t1_card.color == t2_card.color)
                {
                    stos_pik.push_back(t1_card);
                    side[number_take].number = 0;
                    side[number_take].color = "N";
                    side[number_take].red_black = -1;
                }
                else
                {
                    cout << "WRONG CARD";
                }

            }
            ///side do trefl
            if (name_destination == "trefl")
            {
                t2_card = stos_trefl[stos_trefl.size() - 1];

                if (t1_card.number == t2_card.number + 1 && t1_card.color == t2_card.color)
                {
                    stos_trefl.push_back(t1_card);
                    side[number_take].number = 0;
                    side[number_take].color = "N";
                    side[number_take].red_black = -1;
                }
                else
                {
                    cout << "WRONG CARD";
                }

            }
            ///side do kier
            if (name_destination == "kier")
            {
                t2_card = stos_kier[stos_kier.size() - 1];

                if (t1_card.number == t2_card.number + 1 && t1_card.color == t2_card.color)
                {
                    stos_kier.push_back(t1_card);
                    side[number_take].number = 0;
                    side[number_take].color = "N";
                    side[number_take].red_black = -1;
                }
                else
                {
                    cout << "WRONG CARD";
                }

            }
            //side do serce
            if (name_destination == "serce")
            {
                t2_card = stos_hearth[stos_hearth.size() - 1];

                if (t1_card.number == t2_card.number + 1 && t1_card.color == t2_card.color)
                {
                    stos_hearth.push_back(t1_card);
                    side[number_take].number = 0;
                    side[number_take].color = "N";
                    side[number_take].red_black = -1;
                }
                else
                {
                    cout << "WRONG CARD";
                }

            }
        }

    }
}

void data_correction(string& name_take, string& name_destination, int& number_take, int& number_destination)
{
    int lim = 0;
    cout << "TYPE : NAME OF THE DECK YOU WANT TO TAKE A CARD FROM -> NUMBER -> NAME OF THE DESTINATION DECK -> NUMBER " << endl;
    cin >> name_take;
    while (name_take != "main" && name_take != "side")    ///tylko z main i side mozna cos wziac
    {
        cout << "WRONG NAME OF THE DECK. WRITE AGAIN:" << endl;
        cin >> name_take;
    }
    if (name_take == "main")    /// liczba main deck : 0-7
    {
        lim = 7;
    }
    else if (name_take == "side") ///liczba side deck: 0-3
    {
        lim = 3;
    }
    cin >> number_take;
    while (number_take > lim || number_take < 0)
    {
        cout << "WRONG NUMBER.WRITE AGAIN:" << endl;
        cin >> number_take;
    }
    cin >> name_destination;
    while (name_destination != "main" && name_destination != "side" && name_destination != "pik" && name_destination != "trefl" && name_destination != "kier" && name_destination != "serce")
    {
        cout << "WRONG DESTINATION.WRITE AGAIN:" << endl;
        cin >> name_destination;
    }

    if (name_destination == "main" || name_destination == "side")     ///tylko dla main i side potrzebny numer decku
    {
        if (name_destination == "main")
        {
            cin >> number_destination;
            while (number_destination > 7 || number_destination < 0)
            {
                cout << "WRONG NUMBER.WRITE AGAIN:" << endl;
                cin >> number_destination;
            }
        }
        else if (name_destination == "side")
        {
            cin >> number_destination;
            while (number_destination > 3 || number_destination < 0)
            {
                cout << "WRONG NUMBER.WRITE AGAIN:" << endl;
                cin >> number_destination;
            }
        }
    }
}

void IsitWin(vector<card>& stos_pik, vector<card>& stos_trefl, vector<card>& stos_kier, vector<card>& stos_hearth, bool& win) {

    if (stos_pik[stos_pik.size() - 1].number == 13 && stos_trefl[stos_trefl.size() - 1].number == 13 && stos_kier[stos_kier.size() - 1].number == 13 && stos_hearth[stos_hearth.size() - 1].number == 13)
    {
        win = true;
        cout << "CONGRATULATIONS. YOU WON." << endl;

    }
}


