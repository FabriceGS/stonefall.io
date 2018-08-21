//
// Created by David Oyeka on 8/12/18.
//

#ifndef STONEFALL_SCAFFOLD_H
#define STONEFALL_SCAFFOLD_H

#include "AbstractClasses/Killable.h"
#include <Config/ReleaseConstants.h>
#include <string>

class Scaffold : public Killable {
    private:
        int maxHp;
        std::string id;
        int type;

    public:
        Scaffold(std::shared_ptr<GridBlock> block, int type, std::string id);
        ~Scaffold();
        std::weak_ptr<GridBlock> getBlock() override;
        int getReward() override;
        int getType();
        void update();
        bool readyToUpgrade() const;
        bool isDead() const override;
};


#endif //STONEFALL_SCAFFOLD_H
