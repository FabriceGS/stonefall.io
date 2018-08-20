//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#ifndef STONEFALL_PLAYER_H
#define STONEFALL_PLAYER_H


#include <string>
#include <atomic>

using namespace std;

class Player {
    private:
        string name;
        string id;
        atomic_int resourceCount;
        atomic_int score;

    public:
        Player(string name, string id);
        string getId();
        void setId(string id);
        int getResourceCount();
        void setResourceCount(int newCount);
        void incrementResourceCount(int amount);
        void decrementResourceCount(int amount);
        int getScore();
};


#endif //STONEFALL_PLAYER_H
