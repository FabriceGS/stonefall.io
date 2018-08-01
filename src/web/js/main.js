let game;
let sock;
const lt = /</g,
    gt = />/g,
    ap = /'/g,
    ic = /"/g;

const initialize = (baseCoordinates) => {
    const canvasDimensions = initializeCanvas();
    game = Game(canvasDimensions.width, canvasDimensions.height, baseCoordinates);
};

// on resize, we need to initialize the canvas and draw the game again
$(window).resize(() => { initialize(game.boundingBox.getCenter()) });

// initialize the game
$(document).ready(() => {
    const handlers = Handlers();
    $("#name").html(new URL(window.location.href).searchParams.get("name").replace(lt, "&lt;").replace(gt, "&gt;").replace(ap, "&#39;").replace(ic, "&#34;"));
    sock = WebSockets();
    $("#game").mousedown(handlers.mousedownHandler);
    $("#game").mousemove(handlers.mousemoveHandler);
    $("#game").mouseup(handlers.mouseupHandler);
    $("#game").contextmenu(handlers.rightClickHandler);
    $(document).keydown(handlers.keydownHandler);
    $("#game").keypress(handlers.keypressHandler);
    $(document).keyup(handlers.keyupHandler);
    $("#wallImage").click(handlers.wallImageClickHandler);
    $("#turretImage").click(handlers.turretImageClickHandler);
    $("#attacker1Image").click(handlers.attackerImageClickHandler);
    $("#mineImage").click(handlers.mineImageClickHandler);
    $("#sellImage").click(handlers.sellImageClickHandler);
});
