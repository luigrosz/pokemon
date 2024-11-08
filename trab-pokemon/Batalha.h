#ifndef BATALHA_H
#define BATALHA_H

#include <string>
#include <vector>

#include "Pokemon.h"

using namespace std;

class Batalha {
   private:
    vector<Pokemon> pokemonsPlayer;
    vector<Pokemon> pokemonsCpu;
    int dificuldade;  // 1 - FACIL   2 - MEDIO   3 - DIFICIL
    int indexOfCurrentPokemonPlayer;
    int indexOfCurrentPokemonCpu = 0;

   public:
    Batalha(vector<Pokemon> pokemonsPlayer, vector<Pokemon> pokemonsCpu,
            int dificuldade)
        : pokemonsPlayer(pokemonsPlayer),
          pokemonsCpu(pokemonsCpu),
          dificuldade(dificuldade) {}

    int iniciarBatalha();

    void escolherPokemon();

    void imprimirHpPokemons();

    void imprimirAtaques();

    int playerAtaca(int index);

    int cpuAtaca();

    void escolherAtaque(bool cpu);

    int batalhaPokemon();  // returns 0 if cpu pokemon won, 1 if player

    int jogadorVenceLuta();

    int cpuVenceLuta();

    int playerWins();

    int cpuWins();

    void turnoPlayer();
};

#endif
