#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

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


void pantallaBienvenida();

int main() {

    pantallaBienvenida();

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

