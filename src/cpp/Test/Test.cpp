#define CATCH_CONFIG_MAIN

#include "Catch.h"
#include <memory>
#include <Pathing/AStar.h>
#include <Map/Grid.h>
#include <Structure/Base.h>

// NOTE: To run tests faster, change grid length/width constants.
TEST_CASE("Necessary Navigation")
{
     // Test Setup
     unique_ptr<Grid> grid = std::make_unique<Grid>();
     grid->buildGrid();

     SECTION("getGridBlock retrieves valid GridBlock", "[grid]") {
          auto opt_block = grid->getGridBlock(10, 10);
          CHECK_FALSE(nullptr == opt_block);
     }

    SECTION("Simple Pathing Works", "[pathing]") {
        auto path = AStar::shortestPath(grid->getGridBlock(1, 1),
                                        grid->getGridBlock(5, 5));
        std::list<GridBlock*> correctPath = {
                grid->getGridBlock(1, 1),
                grid->getGridBlock(2, 2),
                grid->getGridBlock(3, 3),
                grid->getGridBlock(4, 4),
                grid->getGridBlock(5, 5)
        };
        CHECK(path == correctPath);
    }

    SECTION("Edge Pathing Works", "[pathing]") {
        auto path = AStar::shortestPath(grid->getGridBlock(18, 6),
                                        grid->getGridBlock(19, 9));
        std::list<GridBlock*> correctPath1 = {
                grid->getGridBlock(18, 6),
                grid->getGridBlock(18, 7),
                grid->getGridBlock(18, 8),
                grid->getGridBlock(19, 9)
        };

        std::list<GridBlock*> correctPath2 = {
                grid->getGridBlock(18, 6),
                grid->getGridBlock(19, 7),
                grid->getGridBlock(19, 8),
                grid->getGridBlock(19, 9)
        };

        CHECK(path == correctPath2);
    }
}

TEST_CASE("GridBlock Expected Behavior", "[grid]")
{
    Grid::buildGrid();
    auto block = Grid::getGridBlock(0, 0);
    CHECK_FALSE(block->isFull());

    weak_ptr<GridEntity> weakEntity;
    block->populate(weakEntity);
    CHECK_FALSE(block->isFull());
    block->depopulate();
    CHECK_FALSE(block->isFull());

    auto sharedEntity = make_shared<Base>(*(Grid::getGridBlock(0, 0)));
    weakEntity = sharedEntity;
    block->populate(weakEntity);
    CHECK(block->isFull());

    block->depopulate();
    CHECK_FALSE(block->isFull());
}