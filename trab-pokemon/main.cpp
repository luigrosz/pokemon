#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "Ataque.h"
#include "Batalha.h"
#include "Cpu.h"
#include "Player.h"
#include "Pokemon.h"

#define numberOfPokemonsHeld 3
#define invalido cout << "Opção Inválida." << endl;
#define newLine cout << endl;

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

vector<Pokemon> pokemons;
vector<Ataque> ataques;
vector<Player> jogadoresCadastrados;
int dificuldade = 1;

void carregarPokemon() {
    ifstream file("pokemons.txt");

    if (!file) {
        cerr << "Não foi possível abrir o arquivo de pokemons.\n";
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string word;
        vector<string> words;

        while (getline(ss, word, ',')) {
            words.push_back(word);
        }

        string nome = words[0];
        string tipo1 = words[1];
        string tipo2 = words[2];
        int hp = stoi(words[3]);
        int nivel = stoi(words[4]);
        int ataque = stoi(words[5]);
        int defesa = stoi(words[6]);
        int velocidade = stoi(words[7]);
        int ataque_esp = stoi(words[8]);
        int defesa_esp = stoi(words[9]);

        Pokemon newPokemon =
            Pokemon(nome, tipo1, tipo2, hp, nivel, ataque, defesa, velocidade,
                    ataque_esp, defesa_esp);
        pokemons.push_back(newPokemon);
    }
    file.close();
}

void carregarAtaques() {
    ifstream file("ataques.txt");

    if (!file) {
        cerr << "Não foi possível abrir o arquivo de ataques.\n";
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string word;
        vector<string> words;

        while (getline(ss, word, ',')) {
            words.push_back(word);
        }

        string move = words[0];
        string categoria = words[1];
        int poder = stoi(words[2]);
        double precisao = stod(words[3]);
        string tipo = words[4];

        Ataque novoAtaque = Ataque(move, categoria, poder, precisao, tipo);
        ataques.push_back(novoAtaque);
    }
    file.close();
}

void carregarPlayers() {
    ifstream file("scores.csv");

    if (!file) {
        cerr << "Não foi possível abrir o arquivo de scores.\n";
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string word;
        vector<string> words;

        while (getline(ss, word, ',')) {
            words.push_back(word);
        }

        string nome = words[0];
        int vitorias = stoi(words[1]);
        int derrotas = stoi(words[2]);
        int pontuacao = stoi(words[3]);

        Player novoPlayer = Player(nome, vitorias, derrotas, pontuacao);
        jogadoresCadastrados.push_back(novoPlayer);
    }
    file.close();
}

void escolherPokemon(Player &player, bool cpu, int nivelPokemonMaisFraco,
                     int nivelPokemonMaisForte) {
    random_device rd;
    mt19937 gen(rd());  // Mersenne Twister random number generator
    vector<int> randomIndexes;

    if (!cpu) {
        uniform_int_distribution<> dis(0, pokemons.size() - 1);
        player.removePokemons();
        while (randomIndexes.size() < numberOfPokemonsHeld) {
            int randomIndex = dis(gen);  // get random index
            int flag = 0;
            for (int i = 0; i < randomIndexes.size(); i++) {
                if (randomIndex == randomIndexes[i]) flag = 1;
            }
            if (flag == 1) continue;

            randomIndexes.push_back(randomIndex);
        }

        for (int i = 0; i < randomIndexes.size(); i++)
            player.adicionaPokemon(pokemons[randomIndexes[i]]);

        return;
    }

    vector<Pokemon> cpuVectorOfPossiblePokemon;

    if (dificuldade == 1) {
        for (int i = 0; i < pokemons.size(); i++) {
            if (pokemons[i].getNivel() <= nivelPokemonMaisFraco)
                cpuVectorOfPossiblePokemon.push_back(pokemons[i]);
        }
    } else if (dificuldade == 2) {
        for (int i = 0; i < pokemons.size(); i++) {
            if (pokemons[i].getNivel() <= nivelPokemonMaisForte)
                cpuVectorOfPossiblePokemon.push_back(pokemons[i]);
        }
    } else {
        for (int i = 0; i < pokemons.size(); i++) {
            if (pokemons[i].getNivel() >= nivelPokemonMaisForte)
                cpuVectorOfPossiblePokemon.push_back(pokemons[i]);
        }
    }

    uniform_int_distribution<> dis(0, cpuVectorOfPossiblePokemon.size() - 1);
    while (randomIndexes.size() < numberOfPokemonsHeld) {
        int randomIndex = dis(gen);  // get random index
        int flag = 0;
        for (int i = 0; i < randomIndexes.size(); i++) {
            if (randomIndex == randomIndexes[i]) flag = 1;
        }
        if (flag == 1) continue;

        randomIndexes.push_back(randomIndex);
    }

    for (int i = 0; i < randomIndexes.size(); i++)
        player.adicionaPokemon(cpuVectorOfPossiblePokemon[randomIndexes[i]]);
}

void escolherAtaques(Player &player) {
    random_device rd;
    mt19937 gen(rd());  // Mersenne Twister random number generator
    vector<int> randomIndexes;
    vector<Ataque> possibleAttacks;
    vector<pair<string, string>> tiposPokemon = player.getTiposPokemons();

    for (int i = 0; i < numberOfPokemonsHeld; i++) {
        for (int j = 0; j < ataques.size(); j++) {
            if (ataques[j].getTipo() == tiposPokemon[i].first ||
                ataques[j].getTipo() == tiposPokemon[i].second ||
                ataques[j].getTipo() == "Normal")
                possibleAttacks.push_back(ataques[j]);
        }

        uniform_int_distribution<> dis(0, possibleAttacks.size() - 1);

        while (randomIndexes.size() < 4) {
            int randomIndex = dis(gen);  // get random index
            int flag = 0;
            for (int i = 0; i < randomIndexes.size(); i++) {
                if (randomIndex == randomIndexes[i]) flag = 1;
            }
            if (flag == 1) continue;

            randomIndexes.push_back(randomIndex);
        }

        for (int j = 0; j < randomIndexes.size(); j++)
            player.adicionaAtaque(i, possibleAttacks[randomIndexes[j]]);

        possibleAttacks.clear();
        randomIndexes.clear();
    }
}

void imprimirPokemonsMain(vector<Pokemon> pokemonArr) {
    for (int i = 0; i < pokemonArr.size(); i++) {
        cout << pokemonArr[i].getNome() << endl;
    }
}

void imprimirAtaquesMain(vector<Ataque> AtaquesArr) {
    for (int i = 0; i < AtaquesArr.size(); i++) {
        cout << AtaquesArr[i].getMove() << endl;
    }
}

void imprimirJogadores() {
    system("clear");
    cout << "Jogadores cadastrados:" << endl << endl;
    for (int i = 0; i < jogadoresCadastrados.size(); i++)
        cout << i + 1 << ": " << jogadoresCadastrados[i].getNome() << endl;
};

void cadastrarJogador() {
    string nomePlayer;
    newLine;
    cout << "Qual é o seu nome?" << endl;
    cin >> nomePlayer;
    newLine;

    Player novoJogador = Player(nomePlayer, 0, 0, 0);
    jogadoresCadastrados.push_back(novoJogador);
}

void iniciarBatalha(Player &player) {
    system("clear");
    cout << "Bem vindo a batalha " << player.getNome() << endl;
    cout << "Você está iniciando o jogo na dificuldade ";
    switch (dificuldade) {
        case 1:
            cout << "fácil." << endl;
            break;
        case 2:
            cout << "média." << endl;
            break;
        default:
            cout << "difícil." << endl;
            break;
    }
    escolherPokemon(player, false, 0, 0);
    escolherAtaques(player);

    Cpu cpu = Cpu("cpu", dificuldade);
    escolherPokemon(cpu, true, player.nivelPokemonMaisFraco(),
                    player.nivelPokemonMaisForte());
    escolherAtaques(cpu);

    newLine;
    cout << "Seus pokemons para essa batalha: " << endl;
    newLine;
    player.imprimirPokemons();
    newLine;

    Batalha batalha =
        Batalha(player.getPokemons(), cpu.getPokemons(), dificuldade);

    while (1) {
        int opcao;
        cout << "Digite 0 para iniciar a batalha: " << endl;
        cin >> opcao;
        if (opcao == 0) {
            system("clear");
            // 0 if player wins
            int ganhador = batalha.iniciarBatalha();
            if (ganhador != 0) player.adicionaDerrota();
            if (ganhador == 0) {
                player.adicionaVitoria();
                if (dificuldade == 1) {
                    player.adicionaPontuacao(10);
                } else if (dificuldade == 2) {
                    player.adicionaPontuacao(20);
                } else {
                    player.adicionaPontuacao(30);
                }
            }
            if (ganhador == 0) {
                cout << "Voce venceu! Parabens!" << endl;
            } else {
                cout << "Voce perdeu!" << endl;
            }
            newLine;
            cout << "Pressione 0 para voltar para o menu" << endl;
            int opcao;
            while (1) {
                cin >> opcao;
                if (opcao == 0) return;
                invalido;
            }
        }
    }
}

void selecionarOuCriarjogador() {
    system("clear");
    while (1) {
        int opcao;
        cout << "========= Menu =========" << endl;
        cout << "1. Selecionar jogador" << endl;
        cout << "2. Criar jogador" << endl;
        cout << "3. Voltar" << endl;
        cin >> opcao;

        switch (opcao) {
            case 1:
                if (jogadoresCadastrados.size() == 0) {
                    cout << "Nenhum jogador cadastrado." << endl;
                    newLine;
                    break;
                }

                imprimirJogadores();
                newLine;
                cout << "Escolha um jogador: " << endl;
                cin >> opcao;
                if (opcao < 1 || opcao > jogadoresCadastrados.size()) {
                    invalido break;
                }
                iniciarBatalha(jogadoresCadastrados[opcao - 1]);
                return;
            case 2:
                cadastrarJogador();
                break;
            case 3:
                return;
            default:
                invalido;
        }
    }
}

void selecionarDificuldade() {
    system("clear");
    int dificuldadeInput;

    while (1) {
        cout << "========= Menu =========" << endl;
        cout << "1. Fácil" << endl;
        cout << "2. Médio" << endl;
        cout << "3. Difícil" << endl;
        cout << "4. Voltar" << endl;
        cin >> dificuldadeInput;

        if (dificuldadeInput == 4) return;
        if (dificuldadeInput < 1 || dificuldadeInput > 3) {
            cout << "Dificuldade inválida. Escolha entre 1, 2, ou 3." << endl
                 << endl;
            continue;
        }
        dificuldade = dificuldadeInput;
        newLine;
    }
};

void ranking() {
    system("clear");
    int quantidadeJogadoresCadastrados = jogadoresCadastrados.size();

    if (quantidadeJogadoresCadastrados == 0) {
        cout << "Nenhum jogador cadastrado." << endl;
        newLine;
    }
    bool flag = false;

    for (int i = 0; i < quantidadeJogadoresCadastrados; i++) {
        flag = 0;

        for (int j = 0; j < quantidadeJogadoresCadastrados - i; j++) {
            if (jogadoresCadastrados[j].getPontuacao() >
                jogadoresCadastrados[j + 1].getPontuacao()) {
                swap(jogadoresCadastrados[j], jogadoresCadastrados[j + 1]);
                flag = true;
            }
        }

        if (!flag) break;
    }

    int posicao = 1;
    for (int i = quantidadeJogadoresCadastrados - 1; i >= 0; i--) {
        cout << posicao << ": " << jogadoresCadastrados[i].getNome() << endl
             << "   Pontuacao: " << jogadoresCadastrados[i].getPontuacao()
             << "  Vitorias: " << jogadoresCadastrados[i].getVitorias()
             << "  Derrotas: " << jogadoresCadastrados[i].getDerrotas() << endl;
        posicao++;
    }

    newLine;
    cout << "Digite 0 para voltar" << endl;
    while (1) {
        int input;
        cin >> input;
        if (input == 0) return;
    }
}

void salvarPlayers() {
    ofstream scoresFile("scores.csv");
    if (!scoresFile.is_open()) {
        cerr << "Não foi possível escrever o arquivo de players.\n";
        return;
    }

    scoresFile << "Nome,Vitorias,Derrotas,Pontuacao" << endl;

    for (int i = 0; i < jogadoresCadastrados.size(); i++) {
        scoresFile << jogadoresCadastrados[i].getNome() << ","
                   << jogadoresCadastrados[i].getVitorias() << ","
                   << jogadoresCadastrados[i].getDerrotas() << ","
                   << jogadoresCadastrados[i].getPontuacao() << endl;
    }

    scoresFile.close();
}

int main() {
    carregarPokemon();
    carregarAtaques();
    carregarPlayers();

    // imprimirPokemonsMain(pokemons);
    // imprimirAtaquesMain(ataques);

    while (1) {
        system("clear");
        cout << "========= Menu =========" << endl;
        cout << "1. Iniciar Batalha" << endl;
        cout << "2. Dificuldade" << endl;
        cout << "3. Ranking" << endl;
        cout << "4. Sair" << endl;
        cout << "========================" << endl << endl;
        cout << "Escolha uma opção: ";

        int opcao;
        cin >> opcao;
        switch (opcao) {
            case 1:
                selecionarOuCriarjogador();
                break;
            case 2:
                selecionarDificuldade();
                break;
            case 3:
                ranking();
                break;
            case 4:
                salvarPlayers();
                return 0;
            default:
                cout << "Opção Inválida." << endl;
        }
    }

    return 0;
}