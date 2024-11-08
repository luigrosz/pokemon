#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>

#include "Ataque.h"

using namespace std;

class Pokemon {
   private:
    string nome;
    string tipo1;
    string tipo2;
    int hp;
    int nivel;
    int ataque;
    int defesa;
    int velocidade;
    int ataque_esp;
    int defesa_esp;

    vector<Ataque> ataques;

   public:
    Pokemon(string nome, string tipo1, string tipo2, int hp, int nivel,
            int ataque, int defesa, int velocidade, int ataque_esp,
            int defesa_esp)
        : nome(nome),
          tipo1(tipo1),
          tipo2(tipo2),
          hp(hp),
          nivel(nivel),
          ataque(ataque),
          defesa(defesa),
          velocidade(velocidade),
          ataque_esp(ataque_esp),
          defesa_esp(defesa_esp) {}

    string getNome();

    int getNivel();

    string getTipo1();

    string getTipo2();

    vector<Ataque> getAtaques();

    int getAtaque();

    int getDefesa();

    int getAtaqueEsp();

    int getDefesaEsp();

    int getHp();

    void adicionaAtaque(Ataque ataque);

    int dano(int dano);
};

#endif
