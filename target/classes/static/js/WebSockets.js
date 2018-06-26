const WebSockets = function() {
  const MESSAGE_TYPE = {
    CONNECT: 0,
    UPDATE: 1,
    ATTACK: 2,
    CREATE: 3,
    INITIALIZE: 4,
    SELL: 5,
    ERROR: 6,
    GAMEOVER: 7,
    TEST: 8
  };

  const OBJECT_TYPE = {
    WALL: 0,
    TURRET: 1,
    ATTACKER: 2,
    MINE: 3
  };

  // const ip = "104.196.202.184";
  const ip = "localhost:4567";
  let conn = new WebSocket("ws://" + ip + "/sockets");
  let id = -1;

  // Setup the WebSocket connection.
  const setupConnection = initialize => {
    let initialized = false;
    conn.onerror = err => {
      console.log("Connection error:", err);
    };

    conn.onmessage = msg => {
      const data = JSON.parse(msg.data);
      switch (data.type) {
        default:
          console.log("Unknown message type!", data.type);
          break;
        case MESSAGE_TYPE.CONNECT:
          id = data.payload.id;
          sendInitialize();
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
  };

  const sendInitialize = () => {
    // there's a little bit of hackiness, we get the name from a hidden <h3> tag
    conn.send(
      JSON.stringify({
        type: MESSAGE_TYPE.INITIALIZE,
        payload: {
          id: id,
          name: $("#name").text()
        }
      })
    );
  };

  const sendAttack = (attackers, toAttackCoordinates) => {
    conn.send(
      JSON.stringify({
        type: MESSAGE_TYPE.ATTACK,
        payload: {
          id: id,
          attackers: attackers.map(attacker => attacker.id),
          x1: toAttackCoordinates.x,
          y1: toAttackCoordinates.y
        }
      })
    );
  };

  const sendSpawn = (x, y, type) => {
    conn.send(
      JSON.stringify({
        type: MESSAGE_TYPE.CREATE,
        payload: {
          id: id,
          x1: x,
          y1: y,
          objectType: type
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

  return {
    setupConnection,
    sendAttack,
    sendWallSpawn,
    sendTurretSpawn,
    sendAttackerSpawn,
    sendMineSpawn,
    sendWallsSell,
    sendTurretsSell,
    sendMinesSell
  };
};
