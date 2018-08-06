#define CATCH_CONFIG_MAIN

#include "Catch.h"
#include "../Map/Grid.h"
#include <memory>
#include <Pathing/AStar.h>

// NOTE: To run tests faster, change grid length/width constants.
TEST_CASE("Necessary Navigation")
{
     // Test Setup
     unique_ptr<Grid> grid = std::make_unique<Grid>();
     grid->buildGrid();

     SECTION("getGridBlock retrieves valid GridBlock", "[grid]") {
          auto opt_block = grid->getGridBlock(10, 10);
          CHECK_FALSE(nullptr == opt_block->get());
     }

    SECTION("Simple Pathing Works", "[pathing]") {
        auto path = AStar::shortestPath(grid->getGridBlock(1, 1)->get(),
                                        grid->getGridBlock(5, 5)->get());
        std::list<GridBlock*> correctPath = {
                grid->getGridBlock(1, 1)->get(),
                grid->getGridBlock(2, 2)->get(),
                grid->getGridBlock(3, 3)->get(),
                grid->getGridBlock(4, 4)->get(),
                grid->getGridBlock(5, 5)->get()
        };
        CHECK(path == correctPath);
    }

    SECTION("Edge Pathing Works", "[pathing]") {
        auto path = AStar::shortestPath(grid->getGridBlock(18, 6)->get(),
                                        grid->getGridBlock(19, 9)->get());
        std::list<GridBlock*> correctPath1 = {
                grid->getGridBlock(18, 6)->get(),
                grid->getGridBlock(18, 7)->get(),
                grid->getGridBlock(18, 8)->get(),
                grid->getGridBlock(19, 9)->get()
        };

        std::list<GridBlock*> correctPath2 = {
                grid->getGridBlock(18, 6)->get(),
                grid->getGridBlock(19, 7)->get(),
                grid->getGridBlock(19, 8)->get(),
                grid->getGridBlock(19, 9)->get()
        };

        CHECK(path == correctPath2);
    }
}