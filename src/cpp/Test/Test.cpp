#define CATCH_CONFIG_MAIN

#include "Catch.h"
#include "../Map/Grid.h"
#include <memory>

TEST_CASE("This is a test!", "[grid]")
{
     unique_ptr<Grid> grid = std::make_unique<Grid>();
     grid->buildGrid();
}