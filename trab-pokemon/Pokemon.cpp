#include "Pokemon.h"

string Pokemon::getNome() { return nome; }

int Pokemon::getNivel() { return nivel; }

string Pokemon::getTipo1() { return tipo1; }

string Pokemon::getTipo2() { return tipo2; }

vector<Ataque> Pokemon::getAtaques() { return ataques; };

int Pokemon::getHp() { return hp; }

int Pokemon::getAtaque() { return ataque; };

int Pokemon::getDefesa() { return defesa; };

int Pokemon::getAtaqueEsp() { return ataque_esp; };

int Pokemon::getDefesaEsp() { return defesa_esp; };

void Pokemon::adicionaAtaque(Ataque ataque) { ataques.push_back(ataque); };

int Pokemon::dano(int dano) {
    hp -= dano;
    if (hp < 0) hp = 0;
    return hp;
}