package edu.brown.cs.stonefall.game;

import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public class DefenseBot extends Player implements Runnable, Future<DefenseBot> {
  private boolean alive;
  private boolean isReadyForCleanup;

  public DefenseBot(String name, String id) {
    super(name, id);
    alive = true;
    isReadyForCleanup = false;
  }

  @Override
  public void run() {
    while (alive) {
      System.out.println("Hello World");
    }
    isReadyForCleanup = true;
  }

  @Override
  /**
   * Checks whether a player is dead by checking the base health.
   *
   * @return true if player is dead, false otherwise
   */
  public boolean isDead() {
    if (base.isDead()) {
      new Timer().schedule(new TimerTask() {
        @Override
        public void run() { alive = false; }}, 1000);
    }
    return base.isDead();
  }

  @Override
  public boolean cancel(boolean mayInterruptIfRunning) {
    return false;
  }

  @Override
  public boolean isCancelled() {
    return false;
  }

  @Override
  public boolean isDone() {
    return isReadyForCleanup;
  }

  @Override
  public DefenseBot get() throws InterruptedException, ExecutionException {
    return null;
  }

  @Override
  public DefenseBot get(long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
    return null;
  }
}
