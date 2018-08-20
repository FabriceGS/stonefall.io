//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_CONSTANTS_H
#define STONEFALL_CONSTANTS_H

namespace Constants {
    // Logistical Constants
    int const MAX_PLAYERS = 50;
    int const MIN_THREADS = 2;
    int const TICK_PERIOD = 20;
    int const SCAFFOLD_GENERATION_RATE = TICK_PERIOD / 2;

    // Grid Constants
    int const BOARD_WIDTH = 200;
    int const BOARD_LENGTH = 100;

    int const MINE_COLLECT_RATE = 5;
    int const RESOURCE_COLLECT_TIME = 15;
    int const RESOURCE_SPAWN_TIME = 100;
    int const RESOURCE_MAX = 280;

    // Health Constants
    int const BASE_HP = 200000;
    int const MINE_HP = 2000;
    int const TURRET_HP = 500;
    int const WALL_HP = 4000;
    int const RESOURCE_HP = 5000;
    int const ATTACKER_HP = 3000;

    // Structure Costs
    int const WALL_COST = 90;
    int const MINE_COST = 950;
    int const TURRET_COST = 450;
    int const ATTACKER_COST = 250;
}

enum DIRECTION {
    NW = 0,
    N = 1,
    NE = 2,
    E = 3,
    W = 4,
    SE = 5,
    S = 6,
    SW = 7
};

enum STRUCTURE_TYPE {
    WALL = 0,
    TURRET = 1,
    ATTACKER = 2,
    MINE = 3,
    SCAFFOLD = 4
};

#endif // STONEFALL_CONSTANTS_H
