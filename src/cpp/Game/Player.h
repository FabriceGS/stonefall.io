//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#ifndef STONEFALL_PLAYER_H
#define STONEFALL_PLAYER_H


#include <string>

using namespace std;

class Player {
    private:
        string name;
        string id;
        int resourceCount;

    public:
        Player(string name, string id);
        void spawnAttacker();
        void spawnWall();
        void spawnMine();
        void spawnTurret();
        string getId();
        void setId(string id);
        int getResourceCount();
        void setResourceCount(int newCount);
};


#endif //STONEFALL_PLAYER_H
