const WebSockets = function() {
  const MESSAGE_TYPE = {
    INITIALIZE: 0,
    UPDATE: 1,
    ATTACK: 2,
    SPAWN: 3,
    SELL: 4,
    ERROR: 5,
    GAMEOVER: 6,
    TEST: 7
  };

  const OBJECT_TYPE = {
    WALL: 0,
    TURRET: 1,
    ATTACKER: 2,
    MINE: 3,
    SCAFFOLD: 4
  };

  let id = -1;

  const loc = window.location;
  let socketsUri;
  if (loc.protocol === "https:") {
      socketsUri = "wss:";
  } else {
      socketsUri = "ws:";
  }
  socketsUri += "//" + loc.host;
  socketsUri += "/sockets";

  let conn = new WebSocket(socketsUri);
  const initialMessage = JSON.stringify({
    type: MESSAGE_TYPE.INITIALIZE,
    payload: {
      name: $("#name").text()
    }
  });
  conn.onopen = () => { 
    conn.send(initialMessage)
  };
  conn.onclose = () => {
    console.log('websocket closed!');
  }
  conn.onerror = err => {
    console.log("Connection error:", err);
  };
  conn.onmessage = msg => {
    const data = JSON.parse(msg.data);
    switch (data.type) {
      default:
        console.log("Unknown message type!", data.type);
        break;
      case MESSAGE_TYPE.UPDATE:
        if (!initialized) {
          initialized = true;
          initialize(data.payload.my.base);
        }
        game.setObjects(data.payload);
        game.update();
        break;
      case MESSAGE_TYPE.ERROR:
        console.log(data.payload.message);
        break;
      case MESSAGE_TYPE.GAMEOVER:
        window.location.replace(
          "/gameover?maxScore=" + data.payload.maxScore
        );
        break;
    }
  };

  const sendAttack = (attackers, toAttackCoordinates) => {
    conn.send(
      JSON.stringify({
        type: MESSAGE_TYPE.ATTACK,
        payload: {
          id: id,
          attackers: attackers.map(attacker => attacker.id),
          x: toAttackCoordinates.x,
          y: toAttackCoordinates.y
        }
      })
    );
  };

  const sendSpawn = (x, y, objectType) => {
    conn.send(
      JSON.stringify({
        type: MESSAGE_TYPE.SPAWN,
        payload: {
          id: id,
          x: x,
          y: y,
          objectType
        }
      })
    );
  };

  const sendWallSpawn = (x, y) => {
    sendSpawn(x, y, OBJECT_TYPE.WALL);
  };

  const sendTurretSpawn = (x, y) => {
    sendSpawn(x, y, OBJECT_TYPE.TURRET);
  };

  const sendAttackerSpawn = (x, y) => {
    sendSpawn(x, y, OBJECT_TYPE.ATTACKER);
  };

  const sendMineSpawn = (x, y) => {
    sendSpawn(x, y, OBJECT_TYPE.MINE);
  };

  const sendSell = (objects, objectType) => {
    conn.send(
      JSON.stringify({
        type: MESSAGE_TYPE.SELL,
        payload: {
          id: id,
          toSellIds: objects.map(object => object.id),
          objectType
        }
      })
    );
  };

  const sendWallsSell = walls => {
    sendSell(walls, OBJECT_TYPE.WALL);
  };

  const sendTurretsSell = turrets => {
    sendSell(turrets, OBJECT_TYPE.TURRET);
  };

  const sendMinesSell = mines => {
    sendSell(mines, OBJECT_TYPE.MINE);
  };

  // helper developer functions
  const sendError = message => {
    conn.send(
      JSON.stringify({
        type: MESSAGE_TYPE.ERROR,
        payload: {
          message: message
        }
      })
    );
  }

  const sendTest = message => {
    conn.send(
      JSON.stringify({
        type: MESSAGE_TYPE.TEST,
        payload: {
          message: message
        }
      })
    );
  }

  return {
    sendAttack,
    sendWallSpawn,
    sendTurretSpawn,
    sendAttackerSpawn,
    sendMineSpawn,
    sendWallsSell,
    sendTurretsSell,
    sendMinesSell,
    sendError
  };
};
