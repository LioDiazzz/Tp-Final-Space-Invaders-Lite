#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

const int ANCHO = 80;
const int ALTO = 25;

// venia usando estas funciones aparte simulando conio con windows.h pq nose porque no funcionaban.

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

class Player {

    int x;
    int y;
    char sprite;
    int color;

    public:

        Player(int posX, int posY, char forma = '^', int col = 10) {
            x = posX;
            y = posY;
            sprite = forma;
            color = col;
        }

        void dibujar() {
            textcolor(color);
            gotoxy(x, y);
            cout << sprite;
        }

        void borrar() {
            gotoxy(x, y);
            cout << ' ';
        }

        void moverIzquierda() {
            if (x > 2)
                x--;
        }

        void moverDerecha() {
            if (x < ANCHO - 2)
                x++;
        }

        int getX() { return x; }
        int getY() { return y; }
};

class Bala {

    int x;
    int y;
    bool activa;
    clock_t tempo;
    clock_t paso;
    char forma;

    public:

        Bala(int velocidad = 25, char f = '|') {
            activa = false;
            forma = f;
            paso = CLOCKS_PER_SEC / velocidad;
            tempo = clock();
        }

        bool estaActiva() {
            return activa;
        }

        void dispararDesde(int px, int py) {
            if (!activa) {
                x = px;
                y = py - 1;
                activa = true;
            }
        }

        void borrar() {
            gotoxy(x, y);
            cout << ' ';
        }

        void dibujar() {
            gotoxy(x, y);
            cout << forma;
        }

        void mover() {

            if (!activa)
                return;

            if (tempo + paso < clock()) {

                borrar();
                y--;

                if (y <= 1) {
                    activa = false;
                    return;
                }

                dibujar();
                tempo = clock();
            }
        }
};


void pantallaBienvenida();
void loopJuego();


int main() {

    pantallaBienvenida();
    loopJuego();

    return 0;
}

void pantallaBienvenida() {

    textcolor(10);

    cout << "========================================" << endl;
    cout << "          SPACE INVADERS LITE" << endl;
    cout << "========================================" << endl << endl;

    textcolor(15);
    cout << "Controles del jugador:" << endl;
    cout << "  A  -> Mover izquierda" << endl;
    cout << "  D  -> Mover derecha" << endl;
    cout << "  ESPACIO -> Disparar" << endl << endl;

    cout << "Objetivo del juego:" << endl;
    cout << "  Eliminar todas las naves enemigas" << endl;
    cout << "  evitando perder todas las vidas." << endl << endl;

    textcolor(14);
    cout << "Alumno: Lionel Diaz" << endl << endl;

    textcolor(11);
    cout << "Presione una tecla para comenzar..." << endl;

    _getch();
}

void loopJuego() {

    Player jugador(ANCHO / 2, ALTO - 2);
    Bala bala;

    jugador.dibujar();

    while (true) {

        bala.mover();

        // Entrada de teclado
        if (_kbhit()) {

            char tecla = _getch();

            jugador.borrar();

            if (tecla == 'a' || tecla == 'A')
                jugador.moverIzquierda();

            if (tecla == 'd' || tecla == 'D')
                jugador.moverDerecha();

            jugador.dibujar();
        }
    }
}
