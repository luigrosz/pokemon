#ifndef ATAQUE_H
#define ATAQUE_H

#include <string>
#include <vector>

using namespace std;

class Ataque {
   private:
    string move;
    string categoria;
    int poder;
    double precisao;
    string tipo;

   public:
    Ataque(string move, string categoria, int poder, double precisao,
           string tipo)
        : move(move),
          categoria(categoria),
          poder(poder),
          precisao(precisao),
          tipo(tipo) {}

    string getMove();
    string getTipo();
    int getPower();
    string getCategoria();
    double getPrecisao();
};

#endif
