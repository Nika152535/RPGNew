#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"
#include <queue>

using namespace std;

int main() {
    Player *player = new Player("---Tarnished---", 50, 30, 25, 60);
    Enemy *enemy = new Enemy("---Radahn---", 65, 13, 30, 50);
    Enemy *enemy2 = new Enemy("---Malenia---", 80, 25, 40, 70);

//    vector<Character*> participants;
//    participants.push_back(player);
//    participants.push_back(enemy);
//    participants.push_back(enemy2);
//
//    Combat* combat = new Combat(participants);
//    combat->doCombat();

    char* buffer = player->serialize();

    Player* ooootroPlayer = Player::unserialize(buffer);

    delete player;
    delete enemy;
    delete enemy2;
//    delete combat;

    return 0;
}
