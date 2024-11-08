#include "Player.h"

#include <iostream>

void Player::adicionaPokemon(Pokemon pokemon) { pokemons.push_back(pokemon); }

void Player::removePokemons() { pokemons.clear(); }

void Player::imprimirPokemons() {
    for (int i = 0; i < pokemons.size(); i++) {
        cout << pokemons[i].getNome() << " de nível " << pokemons[i].getNivel()
             << " e ataques:" << endl;
        vector<Ataque> ataques = pokemons[i].getAtaques();
        for (int j = 0; j < ataques.size(); j++) {
            cout << ataques[j].getMove() << endl;
        }
        cout << endl;
    }
}

int Player::nivelPokemonMaisFraco() {
    int result = pokemons[0].getNivel();
    for (int i = 1; i < pokemons.size(); i++) {
        if (pokemons[i].getNivel() < result) result = pokemons[i].getNivel();
    }
    return result;
}

int Player::nivelPokemonMaisForte() {
    int result = pokemons[0].getNivel();
    for (int i = 1; i < pokemons.size(); i++) {
        if (pokemons[i].getNivel() > result) result = pokemons[i].getNivel();
    }
    return result;
}

string Player::getNome() { return nome; }

int Player::getPontuacao() { return pontuacao; }

int Player::getVitorias() { return vitorias; }

int Player::getDerrotas() { return derrotas; }

void Player::adicionaVitoria() { vitorias = vitorias + 1; };

void Player::adicionaDerrota() { derrotas = derrotas + 1; };

void Player::adicionaPontuacao(int pontos) { pontuacao += pontos; }

void Player::adicionaAtaque(int indexOfPokemon, Ataque ataque) {
    pokemons[indexOfPokemon].adicionaAtaque(ataque);
}

vector<pair<string, string>> Player::getTiposPokemons() {
    vector<pair<string, string>> result;
    for (int i = 0; i < pokemons.size(); i++) {
        result.push_back(
            make_pair(pokemons[i].getTipo1(), pokemons[i].getTipo2()));
    }
    return result;
};

vector<Pokemon> Player::getPokemons() { return pokemons; }