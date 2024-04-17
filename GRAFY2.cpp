#include <iostream>

using namespace std;

void menu();

struct knot {
    int first;
    int color;  // Dodane pole 'color'
    knot* next;

    knot(int val) {

        first = val;
        color = -1;             // Domyślnie brak przypisanego koloru
        next = nullptr;
       
    }
};

void add_vertex(knot**& list, int num_v);
void remove_vertex(knot**& list, int num_v, int vertex);
void add_edge(knot** list, int vertex, int neighbor);
void remove_edge(knot** list, int vertex, int neighbor);
void print(knot** list, int num_v);
void greedyColoring(knot**& list, int num_v);
void printColors(knot**& list, int num_v);




int main() {
    int num_v = 1;   ///ilość początkowych wierzchołków

    knot** Neighborlist = new knot * [num_v];   ///  tworzenie dynamicznej tablicy do wierzchołków
    Neighborlist[0] = nullptr;



    menu();
    
    while (true) {
        char key;
        cin >> key;

        switch (key) {
        case 'w': {
            num_v++;
            add_vertex(Neighborlist, num_v);
            break;
        }
        case 'd': {
            int vertex;
            cin >> vertex;
            while (vertex > num_v || vertex < 0)
            {
                cout << "WRONG VERTEX.";
                cin >> vertex;
            }
            remove_vertex(Neighborlist, num_v, vertex);
            break; }
        case 'k': {
            int vertex, neighbor;
            cin >> vertex >> neighbor;
           
                if (vertex < num_v && neighbor < num_v && vertex != neighbor)
                {
                    add_edge(Neighborlist, vertex, neighbor);
                    add_edge(Neighborlist, neighbor, vertex);
                    break;
                }
                else
                {
                    cout << "WRONG CONNECTION" << endl;
                    break;
                }
            break;
        }
        case 'u': {
            int vertex, neighbor;
            cin >> vertex >> neighbor;
            remove_edge(Neighborlist, vertex, neighbor);
            remove_edge(Neighborlist, neighbor, vertex);
            break;
        }
        case 'p': {
            print(Neighborlist, num_v);
            break;
        }
        case 'c': {
            greedyColoring(Neighborlist, num_v);
            cout << "END OF COLORING" << endl;
            printColors(Neighborlist, num_v);
            return 0;

        }
        case 'e': {
            return 0;
        }
        default: {
            cout << "WRONG BUTTON." << endl;
            break;
        }
        }
    }

    return 0;
}

void menu() {
    cout << "ZACHLANNE KOLOROWANIE GRAFU: MARCEL KURJANCZYK , RADOSLAW PLICHTA" << endl;
    cout << "MENU:" << endl;
    cout << "PRESS 'w' TO ADD GRAPH VERTEX" << endl;
    cout << "PRESS 'd' TO DELETE GRAPH VERTEX" << endl;
    cout << "PRESS 'k' TO ADD EDGE OF THE GRAPH" << endl;
    cout << "PRESS 'u' TO DELETE EDGE OF THE GRAPH" << endl;
    cout << "PRESS 'p' TO PRINT NEIGHBORLIST LIST" << endl;
    cout << "PRESS 'c' TO COLOR NEIGHBORLIST LIST" << endl;
    cout << "PRESS 'e' TO EXIT" << endl;
}

void add_vertex(knot**& list, int num_v) {
    knot** newlist = new knot * [num_v];        /// tworzy nowa tablice wieksza o 1 od poprzedniej
    
    for (int i = 0; i < num_v - 1; ++i) {
        
        newlist[i] = list[i];                   ///przepisuje ze starej 
       
    }
    newlist[num_v - 1] = nullptr;               /// Ustawienie wskaźnika na nullptr dla nowo dodanego wierzchołka
  
    delete[] list;                              /// kasujemy poprzednia tablice
    list = newlist;

}

void remove_vertex(knot**& list, int num_v, int vertex) {

    for (int i = 0; i < num_v; ++i) {
        remove_edge(list, i, vertex);               ///petla która usunie wszystkie polaczenia z nie istniejacym juz wierzcholkiem
    }
             
             list[vertex]=nullptr;                  /// wyczyszczenie połączeń usuniętego wierzchołka
             list[vertex]= new knot(-1);            ///ustawienie połączenia z wierzchołkiem -1 co wskazuje na jego wyczyszczenie
}

void add_edge(knot** list, int vertex, int neighbor) {
    int a = -1;
    knot* current = list[vertex];
    bool exist = false;

    while (current != nullptr) {
        if (current->first == neighbor) {
            exist = true;
        }                                       ///sprawdzanie czy istnieje juz takie polaczenie  
        current = current->next;  
    }

    delete current;

    if ((list[vertex] == nullptr || list[vertex]->first != a) && (list[neighbor] == nullptr || list[neighbor]->first != a) && (exist==false)) {   ///sprawdzenie czy: 1)nie istnieje juz takie polaczenie 2)czy żaden z wierzchołków nie jest usunięty
        knot* newknot = new knot(neighbor);   ///tworzymy nową tablice wskazników i dodajemy jej polaczenie z neighbor
        newknot->next = list[vertex];           ///dopisujemy do niej aktualne dalsze węzły
        list[vertex] = newknot;                 ///przepisujemy te węzły do węzła zpowrotem
    }
    
}



    void remove_edge(knot **list, int vertex, int neighbor) {
        knot* current = list[vertex];
        knot* prev = nullptr;
        
        while (current != nullptr) {
            if (current->first == neighbor) {
                if (prev != nullptr) {       ///przypadek kiedy sąsiada znajdujemy pozniej
                    current = current->next;
                    list[vertex]->next = current;
                    break;
                }
                else {                              ///przypadek kiedy sasiada znajdujemy odrazu
                    list[vertex] = current->next;
                    break;
                }
               
            }
            current = current->next;
            list[vertex]->next = current;
            prev = current;
           
              
        }
        delete prev;


    }
    
    
    


void print(knot** list, int num_v) {
    for (int i = 0; i < num_v; ++i) 
    {
        
        int a =-1;

        knot* current = list[i];
        
        if (current == nullptr||current->first != a ) {
                  cout << i << ": ";
           
            while (current != nullptr ) {
             
                    
                cout << current->first << " ";
                current = current->next;
            }
            delete current;
       
        
        cout << endl;
        }
            
    }
   
}

void greedyColoring(knot**& list, int num_v) {
    int* colors = new int[num_v];  // Inicjalizacja tablicy kolorów
    for (int i = 0; i < num_v; ++i) {
        colors[i] = -1;             // -1 oznacza, że kolor nie jest jeszcze przypisan
    }

    int maxColor = -1;

                                                                    // Przechodzimy przez wszystkie wierzchołki grafu
    for (int vertex = 0; vertex < num_v; ++vertex) {
                                                                            // Sprawdzamy czy wierzchołek ma sąsiadów
        if (list[vertex] != nullptr) {
                                                                                // Tablica kolorów, które są używane przez sąsiadów
            bool* usedColors = new bool[maxColor + 2] {false};

            int a = -1;
                                                                                    // Sprawdzamy kolory używane przez sąsiadów
            knot* current = list[vertex];
            while (current != nullptr) {
                if (current->first != a) {
                    if (colors[current->first] != -1) {

                        usedColors[colors[current->first]] = true;
                    }
                }
                    current = current->next;
                
            }

            // Szukamy najniższego dostępnego koloru
            int chosenColor = 0;
            while (usedColors[chosenColor]) {
                chosenColor++;
            }

            if (chosenColor > maxColor) {
                maxColor = chosenColor;
            }

            colors[vertex] = chosenColor;
            delete[] usedColors;
        }
    }

    for (int i = 0; i < num_v; ++i) {
        if (colors[i] == -1)             ///wszystkie samotne wierzchołki na ten sam kolor
            colors[i] = 0;
    }

    for (int vertex = 0; vertex < num_v; ++vertex) {
        if (list[vertex] != nullptr) {
            list[vertex]->color = colors[vertex];             ///przypisanie do struktury
        }
    }
    delete[] colors;
}

void printColors(knot**& list, int num_v) {
    
    cout << "Vertex colors:" << endl;
    int a = -1;
    for (int i = 0; i < num_v; ++i) {
        knot* current = list[i];
        
        if (current != nullptr && current->first == a)        /// warunek po lewej potrzebny dla poprawnego działania programu
        {
            continue;                                                       ///omijanie nieistniejacych wierzchołkow
        };

        if (list[i] != nullptr)
        {
            cout << "Vertex " << i << ": Color " << list[i]->color + 1 << endl;
        }
        else
        {
            cout << "Vertex " << i << ": Color " << 1 << endl;
        }

    }
}

