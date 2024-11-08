#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <utility>
#include <vector>

#include "Pokemon.h"

using namespace std;

class Player {
   private:
    string nome;
    int vitorias = 0;
    int derrotas = 0;
    int pontuacao = 0;
    vector<Pokemon> pokemons;

   public:
    Player(string nome) : nome(nome) {}

    Player(string nome, int vitorias, int derrotas, int pontuacao)
        : nome(nome),
          vitorias(vitorias),
          derrotas(derrotas),
          pontuacao(pontuacao) {}

    void adicionaPokemon(Pokemon pokemon);

    void removePokemons();

    void imprimirPokemons();

    int nivelPokemonMaisFraco();

    int nivelPokemonMaisForte();

    string getNome();

    int getPontuacao();

    int getVitorias();

    int getDerrotas();

    void adicionaPontuacao(int pontos);

    void adicionaVitoria();

    void adicionaDerrota();

    void adicionaAtaque(int indexOfPokemon, Ataque ataque);

    vector<pair<string, string>> getTiposPokemons();

    vector<Pokemon> getPokemons();
};

#endif
