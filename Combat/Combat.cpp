//
// Created by Victor Navarro on 19/02/24.
//
#include "Combat.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant: participants) {
        if(participant->getIsPlayer()) {
            teamMembers.push_back((Player*)participant);
        }
        else {
            enemies.push_back((Enemy*)participant);
        }
    }
}

Combat::Combat(vector<Player*> _teamMembers, vector<Enemy*> _enemies) {
    teamMembers = std::move(_teamMembers);
    enemies = std::move(_enemies);
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()) {
        teamMembers.push_back((Player*)participant);
    }
    else {
        enemies.push_back((Enemy*)participant);
    }
}

void Combat::prepareCombat() {
    sort(participants.begin(), participants.end(), compareSpeed);
}

void Combat::doCombat() {
    prepareCombat();

    //Este while es 1 iteracion por ronda
    while(enemies.size() != 0 && teamMembers.size() != 0) {
        registerActions();
        executeActions();
    }

    //No se imprime el nombre del ganador
    if(enemies.size() == 0) {
        cout<<"---Stage clean---"<<endl;
    }
    else {
        cout<<"---Stage failed...You died---"<<endl;
    }
}

void Combat::checkParticipantStatus(Character* participant) {
	if (participant->getHealth() <= 0) {
		if (participant->getIsPlayer()) {
			teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), participant), teamMembers.end());
		}
		else {
			enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end());
            gainExpex(participant); //Si el enemigo se murio ganar la xp
		}
		participants.erase(remove(participants.begin(), participants.end(), participant), participants.end());
	}
}

void Combat::registerActions() {
    vector<Character*>::iterator participant = participants.begin();
    //Una iteracion por turno de cada participante (player y enemigo)
    while(participant != participants.end()) {
        Character* target = nullptr;
        Action currentAction;
        if((*participant)->getIsPlayer()) {
            currentAction = ((Player*)*participant)->takeAction(enemies);
        }
        else {
            currentAction = ((Enemy*)*participant)->takeAction(teamMembers);
        }
        actions.push(currentAction);
        participant++;
    }
}

void Combat::executeActions() {
    //Aqui se ejecutan las acciones
    while(!actions.empty()) {
        Action currentAction = actions.top();
        currentAction.action();
        checkParticipantStatus(currentAction.subscriber);
        checkParticipantStatus(currentAction.target);
        actions.pop();
    }
}

void Combat::gainExpex(Character* participant) {
    int exp = 0;
    exp = participant->getExpex();

	teamMembers[0]->gainExperience(exp);
    if (teamMembers[0]->SubirNivel()) {
        for (int i = 0; i < enemies.size(); ++i) {
            if (enemies[i] != participant) {
                enemies[i]->ActEstadisticas();
            }
        }
    }
}