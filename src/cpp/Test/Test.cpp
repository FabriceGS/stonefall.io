#define CATCH_CONFIG_MAIN

#include "Catch.h"
#include "../Map/Grid.h"
#include <memory>
#include <Pathing/AStar.h>

TEST_CASE("Grid Necessary Actions")
{
     // Test Setup
     unique_ptr<Grid> grid = std::make_unique<Grid>();
     grid->buildGrid();

     SECTION("getGridBlock retrieves valid GridBlock", "[grid]") {
          auto opt_block = grid->getGridBlock(50, 50);
          CHECK_FALSE(nullptr == opt_block->get());

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
     }
}