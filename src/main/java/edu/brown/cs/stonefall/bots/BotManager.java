package edu.brown.cs.stonefall.bots;

import edu.brown.cs.stonefall.game.Constants;
import edu.brown.cs.stonefall.game.DefenseBot;
import edu.brown.cs.stonefall.game.Game;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.stream.Collectors;

public class BotManager {
  private Game game;
  private ExecutorService threadPoolExecutor;
  private List<Future<?>> botFutures;

  private int botIdCounter;

  public BotManager(Game game) {
    this.game = game;
    botIdCounter = 0;
    botFutures = new ArrayList<>();
    threadPoolExecutor = Executors.newFixedThreadPool(Constants.MAX_BOTS);
    initializeBots();
  }

  public void updateBots() {
    int numBots = botFutures.size();
    if (numBots != 0) {
      botFutures = botFutures.stream().filter(Future::isDone).collect(Collectors.toList());
      int newNumBots = botFutures.size();
      for (int i = 0; i < numBots - newNumBots; i++) {
        DefenseBot defenseBot = new DefenseBot( "Mr. Roboto", "/b/" + botIdCounter);
        botIdCounter++;
        game.addPlayer(defenseBot);
        Future<?> defenseBotFuture = threadPoolExecutor.submit(defenseBot);
        botFutures.add(defenseBotFuture);
      }
    }
  }

  private void initializeBots() {
    List<DefenseBot> bots = new ArrayList<>();
    for (int i = 0; i < Constants.MAX_BOTS; i++) {
      bots.add(new DefenseBot("Mr. Roboto", "/b/" + botIdCounter));
      botIdCounter++;
    }

    for (DefenseBot bot : bots) {
      // Adding the bot to the game.
      game.addPlayer(bot);
      Future<?> defenseBotFuture = threadPoolExecutor.submit(bot);
      botFutures.add(defenseBotFuture);
    }
  }
}
