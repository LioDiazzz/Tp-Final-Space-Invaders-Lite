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

    while (true) {

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
