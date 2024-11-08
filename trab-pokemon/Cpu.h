#ifndef CPU_H
#define CPU_H

#include <string>

#include "Player.h"

class Cpu : public Player {
   private:
    int dificuldade;  // 1 - FACIL   2 - MEDIO   3 - DIFICIL
   public:
    Cpu(string nome, int dificuldade)
        : Player(nome), dificuldade(dificuldade) {}
};

#endif