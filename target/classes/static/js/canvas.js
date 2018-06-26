let singletonCanvas;
let penciller;

const drawGame = (
  boundingBox,
  objects,
  currentlySelectedObjects,
  animationFrame
) => {
  const boundingBoxCoordinates = boundingBox.getCoordinates();
  const canvas = singletonCanvas.getCanvas();
  const ctx = singletonCanvas.getCtx();
  penciller = Penciller();
  penciller.setCanvas(canvas);
  penciller.setCtx(ctx);
  penciller.setDpi(singletonCanvas.getDpi());
  penciller.setBoundingBoxCoordinates(boundingBoxCoordinates);

  /////// BACKGROUND ///////
  // draw the background
  penciller.pencilBackground();
  // draw the grid
  penciller.pencilGrid();
  //////////////////////////

  ////// GAME OBJECTS //////
  // draw my objects, then draw others objects
  // draw my base
  if (objects.my) {
    if (objects.my.walls) {
      // draw my walls
      objects.my.walls.forEach(wall => {
        if (boundingBox.contains(wall)) {
          penciller.pencilWall(wall);
        }
      });
    }
    if (objects.my.turrets) {
      // draw my turrets
      objects.my.turrets.forEach(turret => {
        if (boundingBox.contains(turret)) {
          penciller.pencilTurret(turret, true);
        }
      });
    }
    if (objects.my.attackers) {
      // draw my attackers
      objects.my.attackers.forEach(attacker => {
        if (boundingBox.contains(attacker)) {
          penciller.pencilAttacker(attacker, true, animationFrame);
        }
      });
    }
    if (objects.my.mines) {
      // draw my mines
      objects.my.mines.forEach(mine => {
        if (boundingBox.contains(mine)) {
          penciller.pencilMine(mine, true);
        }
      });
    }
    if (objects.my.scaffoldings) {
      // draw my scaffoldings
      objects.my.scaffoldings.forEach(scaffolding => {
        if (boundingBox.contains(scaffolding)) {
          penciller.pencilScaffolding(scaffolding, true);
        }
      });
    }
  }
  if (objects.others) {
    if (objects.others.walls) {
      // draw others walls
      objects.others.walls.forEach(wall => {
        if (boundingBox.contains(wall)) {
          penciller.pencilWall(wall);
        }
      });
    }
    if (objects.others.turrets) {
      // draw others turrets
      objects.others.turrets.forEach(turret => {
        if (boundingBox.contains(turret)) {
          penciller.pencilTurret(turret, false);
        }
      });
    }
    if (objects.others.attackers) {
      // draw others attackers
      objects.others.attackers.forEach(attacker => {
        if (boundingBox.contains(attacker)) {
          penciller.pencilAttacker(attacker, false, animationFrame);
        }
      });
    }
    if (objects.others.mines) {
      // draw others mines
      objects.others.mines.forEach(mine => {
        if (boundingBox.contains(mine)) {
          penciller.pencilMine(mine, false);
        }
      });
    }
    if (objects.others.scaffoldings) {
      // draw others scaffoldings
      objects.others.scaffoldings.forEach(scaffolding => {
        if (boundingBox.contains(scaffolding)) {
          penciller.pencilScaffolding(scaffolding, false);
        }
      });
    }
  }
  // draw resources
  let flag = false;
  objects.resources.forEach(resource => {
    if (boundingBox.contains(resource)) {
      penciller.pencilResource(resource);
    }
  });
  // draw others bases
  if (objects.others && objects.others.bases) {
    objects.others.bases.forEach(base => {
      if (boundingBox.contains(base)) {
        penciller.pencilBase(base, false);
      }
    });
  }
  //////////////////////////

  if (objects.my && objects.my.base) {
    if (boundingBox.contains(objects.my.base)) {
      penciller.pencilBase(objects.my.base, true);
    }
  }
  /////////// GUI //////////
  switch (game.getCurrentState()) {
    // if the game is selecting objects, draw the selected objects
    case "selectingWalls":
      objects.my.walls.forEach(wall => {
        if (
          currentlySelectedObjects.map(object => object.id).includes(wall.id)
        ) {
          penciller.pencilSelectedWall(wall);
        }
      });
      penciller.pencilBuildingContextMenu(objects.my.base.color);
      break;
    case "selectingTurrets":
      objects.my.turrets.forEach(turret => {
        if (
          currentlySelectedObjects.map(object => object.id).includes(turret.id)
        ) {
          penciller.pencilSelectedTurret(turret);
        }
      });
      penciller.pencilBuildingContextMenu(objects.my.base.color);
      break;
    case "selectingAttackers":
      objects.my.attackers.forEach(attacker => {
        if (
          currentlySelectedObjects
            .map(object => object.id)
            .includes(attacker.id)
        ) {
          penciller.pencilSelectedAttacker(attacker, animationFrame);
        }
      });
      break;
    case "selectingMines":
      objects.my.mines.forEach(mine => {
        if (
          currentlySelectedObjects.map(object => object.id).includes(mine.id)
        ) {
          penciller.pencilSelectedMine(mine);
        }
      });
      penciller.pencilBuildingContextMenu(objects.my.base.color);
      break;
    // if the game is selecting a square, draw the selection
    case "selectingWallSquare":
      const validSquares = highlightValidSquares(
        boundingBoxCoordinates,
        objects
      );
      const coordinates = penciller.coordinateOf(
        interface.lastMousePos.x,
        interface.lastMousePos.y
      );
      if (validSquares["i" + coordinates.x + "j" + coordinates.y]) {
        penciller.pencilWallSelection(interface.lastMousePos);
      }
      break;
    case "selectingTurretSquare":
      const validSquares2 = highlightValidSquares(
        boundingBoxCoordinates,
        objects
      );
      const coordinates2 = penciller.coordinateOf(
        interface.lastMousePos.x,
        interface.lastMousePos.y
      );
      if (validSquares2["i" + coordinates2.x + "j" + coordinates2.y]) {
        penciller.pencilTurretSelection(interface.lastMousePos);
      }
      break;
    case "selectingAttackerSquare":
      const validSquares3 = highlightValidSquares(
        boundingBoxCoordinates,
        objects
      );
      const coordinates3 = penciller.coordinateOf(
        interface.lastMousePos.x,
        interface.lastMousePos.y
      );
      if (validSquares3["i" + coordinates3.x + "j" + coordinates3.y]) {
        penciller.pencilAttackerSelection(interface.lastMousePos);
      }
      break;
    case "selectingMineSquare":
      const validSquares4 = highlightValidSquares(
        boundingBoxCoordinates,
        objects
      );
      const coordinates4 = penciller.coordinateOf(
        interface.lastMousePos.x,
        interface.lastMousePos.y
      );
      if (validSquares4["i" + coordinates4.x + "j" + coordinates4.y]) {
        penciller.pencilMineSelection(interface.lastMousePos);
      }
      break;
  }

  // draw the hud
  if (objects.my && objects.my.statistics) {
    penciller.pencilHud({
      ...objects.my.statistics,
      color: objects.my.base.color
    });
  }
  //////////////////////////
};

const highlightValidSquares = (boundingBoxCoordinates, objects) => {
  // penciller.highlightValidSquares(boundingBoxCoordinates, objects);
  let validSquares = {};
  let x;
  let y;
  validSquares = { ...validSquares, ...validSquaresFrom(objects.my.base) };
  objects.my.walls.forEach(wall => {
    const wallValidSquares = validSquaresFrom(wall);
    const wallValidSquaresEntries = Object.entries(wallValidSquares);
    wallValidSquaresEntries.forEach(entry => {
      validSquares[entry[0]] = entry[1];
    });
  });
  objects.my.turrets.forEach(turret => {
    const turretValidSquares = validSquaresFrom(turret);
    const turretValidSquaresEntries = Object.entries(turretValidSquares);
    turretValidSquaresEntries.forEach(entry => {
      validSquares[entry[0]] = entry[1];
    });
  });
  objects.my.mines.forEach(mine => {
    const mineValidSquares = validSquaresFrom(mine);
    const mineValidSquaresEntries = Object.entries(mineValidSquares);
    mineValidSquaresEntries.forEach(entry => {
      validSquares[entry[0]] = entry[1];
    });
  });
  singletonCanvas.getCtx().beginPath();
  for (
    let i = Math.floor(boundingBoxCoordinates.topLeft.x);
    i < boundingBoxCoordinates.bottomRight.x && i < game.BOARD_WIDTH;
    i++
  ) {
    if (i >= 0) {
      for (
        let j = Math.floor(boundingBoxCoordinates.topLeft.y);
        j < boundingBoxCoordinates.bottomRight.y && j < game.BOARD_HEIGHT;
        j++
      ) {
        if (j >= 0) {
          if (!validSquares["i" + i + "j" + j]) {
            penciller.pencilInvalidSquare(i, j);
          }
        }
      }
    }
  }
  singletonCanvas.getCtx().closePath();
  singletonCanvas.getCtx().fillStyle = "rgba(20, 20, 20, 0.2)";
  singletonCanvas.getCtx().fill();
  return validSquares;
}

const validSquaresFrom = object => {
  const newValidSquares = {};
  for (
    let i = object.x - game.MAX_BLOCK_DISTANCE;
    i <= object.x + game.MAX_BLOCK_DISTANCE;
    i++
  ) {
    for (
      let j = object.y - game.MAX_BLOCK_DISTANCE;
      j <= object.y + game.MAX_BLOCK_DISTANCE;
      j++
    ) {
      newValidSquares["i" + i + "j" + j] = true;
    }
  }
  return newValidSquares;
};

const initializeCanvas = () => {
  singletonCanvas = SingletonCanvas();
  singletonCanvas.setDpi(window.devicePixelRatio);
  singletonCanvas.setCanvas($("#game")[0]);
  return {
    width: singletonCanvas.getWidth(),
    height: singletonCanvas.getHeight()
  };
};
