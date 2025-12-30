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

void limpiarPantalla() {
    for (int y = 1; y < ALTO; y++) {
        for (int x = 1; x < ANCHO; x++) {
            gotoxy(x, y);
            cout << ' ';
        }
    }
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

        int getX() { return x; }
        int getY() { return y; }

        void desactivar() {
            activa = false;
        }

};

class BalaEnemiga {

    int x;
    int y;
    bool activa;
    clock_t tempo;
    clock_t paso;
    char forma;

    public:

        BalaEnemiga(int velocidad = 20, char f = '|') {
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
                y = py + 1;
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
                y++;

                if (y >= ALTO - 1) {
                    activa = false;
                    return;
                }

                dibujar();
                tempo = clock();
            }
        }

        int getX() { return x; }
        int getY() { return y; }
};


class Enemy {

    protected:
        int x;
        int y;
        char forma;
        int color;
        bool vivo;

    public:

        Enemy(int px = 0, int py = 0, char f = 'X', int c = 12) {
            x = px;
            y = py;
            forma = f;
            color = c;
            vivo = true;
        }

        virtual void dibujar() {
            if (!vivo) return;
            textcolor(color);
            gotoxy(x, y);
            cout << forma;
        }

        void borrar() {
            gotoxy(x, y);
            cout << ' ';
        }

        virtual void moverHorizontal(int dx) {
            if (!vivo) return;
            borrar();
            x += dx;
            dibujar();
        }

        void bajar() {
            if (!vivo) return;
            borrar();
            y++;
            dibujar();
        }

        int getX() { return x; }
        int getY() { return y; }

        bool estaVivo() { return vivo; }

        virtual void destruir() {
            vivo = false;
            borrar();
        }

        virtual ~Enemy() {}
};

class EnemyTipoA : public Enemy {

    public:
        EnemyTipoA(int px, int py)
            : Enemy(px, py, 'W', 14) {
        }   
};

class EnemyTipoB : public Enemy {

    public:
        EnemyTipoB(int px, int py)
            : Enemy(px, py, 'M', 10) {
        }   
};

Enemy* enemigos[20];
int cantEnemigos = 0;

int dir = 1;
clock_t tempoEnemigos;
clock_t pasoEnemigos = CLOCKS_PER_SEC / 8;

int enemigosRestantes = 0;
int puntaje = 0;


void crearEnemigos() {

    cantEnemigos = 0;
    enemigosRestantes = 0;

    int inicioX = 10;
    int inicioY = 5;

    for (int fila = 0; fila < 2; fila++) {
        for (int col = 0; col < 10; col++) {

            int px = inicioX + col * 3;
            int py = inicioY + fila * 2;

            if (fila == 0)
                enemigos[cantEnemigos] = new EnemyTipoA(px, py);
            else
                enemigos[cantEnemigos] = new EnemyTipoB(px, py);

            enemigos[cantEnemigos]->dibujar();
            cantEnemigos++;
            enemigosRestantes++;
        }
    }

    tempoEnemigos = clock();
}

void moverEnemigos() {

    if (tempoEnemigos + pasoEnemigos > clock())
        return;

    bool tocaronBorde = false;

    for (int i = 0; i < cantEnemigos; i++) {

        if (!enemigos[i]->estaVivo())
            continue;

        int x = enemigos[i]->getX();

        if ((dir == 1 && x >= ANCHO - 3) ||
            (dir == -1 && x <= 2)) {

            tocaronBorde = true;
            break;
        }
    }

    if (tocaronBorde) {

        for (int i = 0; i < cantEnemigos; i++)
            enemigos[i]->bajar();

        dir *= -1;
    }
    else {

        for (int i = 0; i < cantEnemigos; i++)
            enemigos[i]->moverHorizontal(dir);
    }

    tempoEnemigos = clock();
}

void disparoEnemigoAleatorio(BalaEnemiga& balaE) {

    if (balaE.estaActiva())
        return;

    int indice = rand() % cantEnemigos;

    for (int i = 0; i < cantEnemigos; i++) {

        int idx = (indice + i) % cantEnemigos;

        if (enemigos[idx]->estaVivo()) {

            balaE.dispararDesde(
                enemigos[idx]->getX(),
                enemigos[idx]->getY()
            );

            break;
        }
    }
}


void detectarColisionBala(Bala& bala) {

    if (!bala.estaActiva())
        return;

    for (int i = 0; i < cantEnemigos; i++) {

        if (!enemigos[i]->estaVivo())
            continue;

        if (bala.getX() == enemigos[i]->getX() &&
            bala.getY() == enemigos[i]->getY()) {

            enemigos[i]->destruir();

            enemigosRestantes--;
            puntaje += 10;

            bala.desactivar();

            break;
        }
    }
}



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

	limpiarPantalla();
}

void loopJuego() {

    Player jugador(ANCHO / 2, ALTO - 2);
    Bala bala;
    BalaEnemiga balaEnemiga;

    jugador.dibujar();

    crearEnemigos();

    while (true) {

        bala.mover();

        detectarColisionBala(bala);

        moverEnemigos();

        balaEnemiga.mover();

        disparoEnemigoAleatorio(balaEnemiga);


        // Entrada de teclado
        if (_kbhit()) {

            char tecla = _getch();

            jugador.borrar();

            if (tecla == 'a' || tecla == 'A')
                jugador.moverIzquierda();

            if (tecla == 'd' || tecla == 'D')
                jugador.moverDerecha();

            if (tecla == ' ') {
                if (!bala.estaActiva()) {
                    bala.dispararDesde(jugador.getX(), jugador.getY());
                }
            }

            jugador.dibujar();
        }

        if (enemigosRestantes == 0) {

            limpiarPantalla();

            textcolor(10);
            gotoxy(30, 10);
            cout << "VICTORIA";

            gotoxy(28, 12);
            cout << "Puntaje: " << puntaje;

            _getch();
            exit(0);
        }
    }
}
