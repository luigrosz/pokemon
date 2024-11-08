#include "Batalha.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <utility>

#define invalido cout << "Opção Inválida." << endl;
#define newLine cout << endl;
#define critico cout << "Foi um golpe crítico!" << endl;
#define nefetivo cout << "O ataque não é efetivo!" << endl;
#define ataqueFalhou cout << "O ataque falhou!" << endl;
#define pokemonAtualPlayer pokemonsPlayer[indexOfCurrentPokemonPlayer]
#define pokemonAtualCpu pokemonsCpu[indexOfCurrentPokemonCpu]

enum PokemonType {
    Normal,
    Fogo,
    Agua,
    Eletrico,
    Planta,
    Gelo,
    Lutador,
    Venenoso,
    Terrestre,
    Voador,
    Psiquico,
    Inseto,
    Rocha,
    Fantasma,
    Dragao,
    Metal,
    Fada
};

vector<vector<double>> efetividades = {
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0,
     0.5, 1.0},
    {1.0, 0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5,
     2.0, 1.0},
    {1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5,
     1.0, 1.0},
    {1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5,
     1.0, 1.0},
    {1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5,
     0.5, 1.0},
    {1.0, 0.5, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0,
     0.5, 1.0},
    {2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0,
     2.0, 0.5},
    {1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0,
     0.0, 2.0},
    {1.0, 2.0, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0,
     2.0, 1.0},
    {1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0,
     0.5, 1.0},
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0,
     0.5, 1.0},
    {1.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0,
     0.5, 0.5},
    {1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0,
     0.5, 1.0},
    {0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0,
     1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0,
     0.5, 0.0},
    {1.0, 0.5, 0.5, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0,
     0.5, 2.0},
    {1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0,
     0.5, 1.0}};

int Batalha::iniciarBatalha() {
    cout << "Seu oponente escolheu " << pokemonsCpu[0].getNome() << "!" << endl;
    escolherPokemon();
    int vencedor;  // 0 a batalha continua, 1 jogador venceu, 2 cpu venceu
    while (1) {
        int resultadoBatalha = batalhaPokemon();
        if (resultadoBatalha == 0) vencedor = cpuVenceLuta();
        if (resultadoBatalha == 1) vencedor = jogadorVenceLuta();
        if (vencedor == 0) continue;
        if (vencedor == 1) return playerWins();
        if (vencedor == 2) return cpuWins();
    }
};

int Batalha::jogadorVenceLuta() {
    if (indexOfCurrentPokemonCpu == 2) return 1;
    indexOfCurrentPokemonCpu = indexOfCurrentPokemonCpu + 1;
    cout << "Seu oponente escolheu "
         << pokemonsCpu[indexOfCurrentPokemonCpu].getNome() << "!" << endl;
    escolherPokemon();
    return 0;
};

int Batalha::cpuVenceLuta() {
    int flag = 0;
    for (int i = 0; i < 3; i++) {
        if (pokemonsPlayer[i].getHp() != 0) flag += 1;
    }
    if (flag == 0) return 2;
    escolherPokemon();
    return 0;
};

int Batalha::playerWins() { return 0; };

int Batalha::cpuWins() { return 1; };

void Batalha::escolherPokemon() {
    newLine;
    cout << "Escolha seu pokemon: " << endl;
    newLine;
    int quantidadeVivos = 0;
    int index = 1;
    for (int i = 0; i < pokemonsPlayer.size(); i++) {
        if (pokemonsPlayer[i].getHp() > 0) {
            cout << index << ": " << pokemonsPlayer[i].getNome() << endl;
            quantidadeVivos++;
            index++;
        }
    }

    vector<int> opcoesValidas;
    for (int i = 0; i < pokemonsPlayer.size(); i++) {
        if (pokemonsPlayer[i].getHp() > 0) opcoesValidas.push_back(i);
    }

    int opcao;
    while (1) {
        cin >> opcao;
        if (opcao > 0 && opcao <= opcoesValidas.size()) {
            indexOfCurrentPokemonPlayer = opcoesValidas[opcao - 1];
            break;
        }
        invalido;
    }
}

void Batalha::imprimirHpPokemons() {
    cout << endl
         << "Hp de " << pokemonAtualPlayer.getNome() << ": "
         << pokemonAtualPlayer.getHp() << endl;
    cout << "Hp de " << pokemonAtualCpu.getNome() << ": "
         << pokemonAtualCpu.getHp() << endl;
    if (pokemonAtualPlayer.getHp() == 0)
        cout << endl
             << pokemonAtualPlayer.getNome() << " foi derrotado!" << endl;
    if (pokemonAtualCpu.getHp() == 0)
        cout << pokemonAtualCpu.getNome() << " foi derrotado!" << endl;
}

void Batalha::imprimirAtaques() {
    cout << "Escolha um ataque:" << endl;
    newLine;
    vector<Ataque> ataques = pokemonAtualPlayer.getAtaques();
    for (int i = 0; i < ataques.size(); i++)
        cout << i + 1 << ": " << ataques[i].getMove() << endl;
}

// 1 if cpu wins, 0 if player
int Batalha::batalhaPokemon() {
    imprimirHpPokemons();
    while (1) {
        turnoPlayer();
        imprimirHpPokemons();
        if (pokemonAtualCpu.getHp() == 0) return 1;
        // turno Cpu
        escolherAtaque(true);
        imprimirHpPokemons();
        if (pokemonAtualPlayer.getHp() == 0) return 0;
    }
}

int indexTipo(string tipo) {
    if (tipo == "Normal") return Normal;
    if (tipo == "Fogo") return Fogo;
    if (tipo == "Agua") return Agua;
    if (tipo == "Eletrico") return Eletrico;
    if (tipo == "Planta") return Planta;
    if (tipo == "Gelo") return Gelo;
    if (tipo == "Lutador") return Lutador;
    if (tipo == "Venenoso") return Venenoso;
    if (tipo == "Terrestre") return Terrestre;
    if (tipo == "Voador") return Voador;
    if (tipo == "Psiquico") return Psiquico;
    if (tipo == "Inseto") return Inseto;
    if (tipo == "Rocha") return Rocha;
    if (tipo == "Fantasma") return Fantasma;
    if (tipo == "Dragao") return Dragao;
    if (tipo == "Metal") return Metal;
    if (tipo == "Fada") return Fada;
    return -1;
}

int Batalha::playerAtaca(int indexAtaque) {
    random_device rd;
    mt19937 gen(rd());  // Mersenne Twister random number generator
    uniform_int_distribution<> dis(0, 15);

    int randomNumber = dis(gen);

    Ataque ataque = pokemonAtualPlayer.getAtaques()[indexAtaque];
    double dano;
    float ad;
    if (ataque.getCategoria() == "Fisico") {
        dano = 2 * pokemonAtualPlayer.getNivel() * ataque.getPower();
        ad = pokemonAtualPlayer.getAtaque() /
             double(pokemonAtualCpu.getDefesa());
        dano = dano * ad;
        dano = dano / 50 + 2;
    } else {
        dano = 2 * pokemonAtualPlayer.getNivel() * ataque.getPower();
        ad = pokemonAtualPlayer.getAtaqueEsp() /
             double(pokemonAtualCpu.getDefesaEsp());
        dano = dano * ad;
        dano = dano / 50 + 2;
    }

    if (randomNumber == 0) {
        newLine;
        critico;
        dano = dano * 2;
    }

    string tipoAtaque = ataque.getTipo();
    if (tipoAtaque == pokemonAtualPlayer.getTipo1()) dano = dano * 1.5;

    int indexTipoAtaque = indexTipo(tipoAtaque);
    int indexTipo1Defensor = indexTipo(pokemonAtualCpu.getTipo1());
    int indexTipo2Defensor = indexTipo(pokemonAtualCpu.getTipo2());

    if (efetividades[indexTipoAtaque][indexTipo1Defensor] == 0) {
        nefetivo;
        return 0;
    }

    dano = dano * efetividades[indexTipoAtaque][indexTipo1Defensor];

    // se tipo for "nenhum", nao faz nada, caso contrario entra aqui
    if (indexTipo2Defensor != -1) {
        if (efetividades[indexTipoAtaque][indexTipo2Defensor] == 0) {
            nefetivo;
            return 0;
        }
        dano = dano * efetividades[indexTipoAtaque][indexTipo2Defensor];
    }

    if (round(dano) == 1) return 1;

    // 217 + numero aleatorio entre 0 e 38;
    int randomInt = 217 + rand() % 39;
    dano = dano * randomInt / 255;

    randomInt = rand() % 101;
    double precisao = ataque.getPrecisao() * 100;
    if (precisao < randomInt) {
        ataqueFalhou;
        return 0;
    }

    return round(dano);
}

int Batalha::cpuAtaca() {
    // 1:16 for a critical
    srand((time(0)));
    int randomNumber = rand() % 16;

    vector<Ataque> ataques = pokemonAtualCpu.getAtaques();

    vector<int> danos(ataques.size());
    // first: dano, second: index of attack
    pair<int, int> menorDano;
    pair<int, int> maiorDano;

    for (int i = 0; i < ataques.size(); i++) {
        double dano;
        float ad;
        if (ataques[i].getCategoria() == "Fisico") {
            dano = 2 * pokemonAtualPlayer.getNivel() * ataques[i].getPower();
            ad = pokemonAtualPlayer.getAtaque() /
                 double(pokemonAtualCpu.getDefesa());
            dano = dano * ad;
            dano = dano / 50 + 2;
        } else {
            dano = 2 * pokemonAtualPlayer.getNivel() * ataques[i].getPower();
            ad = pokemonAtualPlayer.getAtaqueEsp() /
                 double(pokemonAtualCpu.getDefesaEsp());
            dano = dano * ad;
            dano = dano / 50 + 2;
        }

        if (randomNumber == 0) dano = dano * 2;

        string tipoAtaque = ataques[i].getTipo();
        if (tipoAtaque == pokemonAtualPlayer.getTipo1()) dano = dano * 1.5;

        int indexTipoAtaque = indexTipo(tipoAtaque);
        int indexTipo1Defensor = indexTipo(pokemonAtualCpu.getTipo1());
        int indexTipo2Defensor = indexTipo(pokemonAtualCpu.getTipo2());

        if (efetividades[indexTipoAtaque][indexTipo1Defensor] == 0) {
            danos[i] = 0;
            continue;
        }

        dano = dano * efetividades[indexTipoAtaque][indexTipo1Defensor];

        // se tipo for "nenhum", nao faz nada, caso contrario entra aqui
        if (indexTipo2Defensor != -1) {
            if (efetividades[indexTipoAtaque][indexTipo2Defensor] == 0) {
                danos[i] = 0;
            }
            dano = dano * efetividades[indexTipoAtaque][indexTipo2Defensor];
        }

        if (round(dano) == 1) danos[i] = 1;

        int randomInt = 217 + rand() % 39;
        dano = dano * randomInt / 255;

        int danoInt = round(dano);
        danos[i] = danoInt;
    }

    menorDano.first = danos[0];
    menorDano.second = 0;

    maiorDano.first = danos[0];
    maiorDano.second = 0;

    for (int i = 1; i < danos.size(); i++) {
        if (danos[i] < menorDano.first) {
            menorDano.first = danos[i];
            menorDano.second = i;
        }
        if (danos[i] > maiorDano.first) {
            maiorDano.first = danos[i];
            maiorDano.second = i;
        }
    }

    if (dificuldade == 1) {
        cout << endl
             << pokemonAtualCpu.getNome() << " usou "
             << ataques[menorDano.second].getMove() << endl;
        if (menorDano.first == 0) {
            nefetivo;
            return 0;
        }

        if (randomNumber == 0) critico;

        int randomInt = rand() % 101;
        double precisao = ataques[menorDano.second].getPrecisao() * 100;
        if (precisao < randomInt) {
            ataqueFalhou;
            return 0;
        }

        cout << ataques[menorDano.second].getMove() << " causou "
             << menorDano.first << " de dano!" << endl;

        return menorDano.first;
    } else if (dificuldade == 2) {
        int randomInt = rand() % 4;
        cout << endl
             << pokemonAtualCpu.getNome() << " usou "
             << ataques[randomInt].getMove() << endl;

        if (danos[randomInt] == 0) nefetivo;

        if (randomNumber == 0) critico;

        cout << ataques[randomInt].getMove() << " causou " << danos[randomInt]
             << " de dano!" << endl;

        return danos[randomInt];

    } else {
        cout << endl
             << pokemonAtualCpu.getNome() << " usou "
             << ataques[maiorDano.second].getMove() << endl;
        if (maiorDano.first == 0) {
            nefetivo;
            return 0;
        }

        int randomInt = rand() % 101;
        double precisao = ataques[maiorDano.second].getPrecisao() * 100;

        if (precisao < randomInt) {
            ataqueFalhou;
            return 0;
        }

        if (randomNumber == 0) critico;

        cout << ataques[maiorDano.second].getMove() << " causou "
             << maiorDano.first << " de dano!" << endl;

        return maiorDano.first;
    }
}

void Batalha::escolherAtaque(bool cpu) {
    int opcao;

    if (!cpu) {
        imprimirAtaques();
        while (1) {
            cin >> opcao;
            if (opcao > 0 && opcao < 5) {
                int dano = playerAtaca(opcao - 1);
                cout << "Causou " << dano << " de dano!" << endl;
                pokemonAtualCpu.dano(dano);
                return;
            }

            invalido;
        }
    } else {
        int dano = cpuAtaca();
        pokemonAtualPlayer.dano(dano);
        return;
    }
}

void Batalha::turnoPlayer() {
    newLine;
    cout << "1. Selecionar ataque" << endl;
    cout << "2. Trocar pokemon" << endl;
    int opcao;
    while (1) {
        cin >> opcao;
        if (opcao == 1) {
            escolherAtaque(false);
            break;
        }
        if (opcao == 2) {
            escolherPokemon();
            break;
        }
        invalido;
    }
};
