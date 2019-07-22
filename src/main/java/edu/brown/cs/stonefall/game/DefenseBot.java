package edu.brown.cs.stonefall.game;

import edu.brown.cs.stonefall.map.Grid;
import edu.brown.cs.stonefall.structure.Base;
import edu.brown.cs.stonefall.structure.Mine;
import edu.brown.cs.stonefall.structure.Resource;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public class DefenseBot extends Player implements Runnable, Future<DefenseBot> {
  private boolean alive;
  private boolean isReadyForCleanup;

  //keep a priority queue that measures distance from base
  //we will pick farthest from base when expanding and closest to base when building defense
  protected PriorityQueue<Pair<Integer, Integer>> pq_closest;
  protected PriorityQueue<Pair<Integer, Integer>> pq_farthest;
  protected ArrayList<Pair<Integer, Integer>> spawnableLocs;

  public DefenseBot(String name, String id) {
    super(name, id);
    alive = true;
    isReadyForCleanup = false;

    pq_closest = new NoDuplicates<Pair<Integer, Integer>>((a, b) -> (int) (distanceToBase((Pair<Integer, Integer>) b) - distanceToBase((Pair<Integer, Integer>) a)));
    pq_farthest = new NoDuplicates<>((a, b) -> (int) (distanceToBase((Pair<Integer, Integer>) a) - distanceToBase((Pair<Integer, Integer>) b)));
    spawnableLocs = new ArrayList<>();
    System.out.println("bot getting constructed 1");

    //fill up playable locations
    int offset = 1;
    while (offset <= 3) {
      for (int i = -offset + base.getX(); i < 1 + offset + base.getX(); i++) {
        for (int j = -offset + base.getY(); j < 1 + offset + base.getY(); j++) {
          System.out.println("iterating within constructor");
          pq_closest.add(new Pair<>(i, j));
          pq_farthest.add(new Pair<>(i, j));
          spawnableLocs.add(new Pair<>(i, j));
        }
      }
      offset += 1;
    }
    System.out.println("bot done getting constructed");
  }

  @Override
  public void run() {
    while (alive) {
      System.out.println("Hello World");
      if (pq_closest.isEmpty() || pq_farthest.isEmpty()) {
        return;
      }
      System.out.println("running");
      if (resourceCount > (multiplyByScoreLogistically(Constants.TURRET_COST) + 8 * multiplyByScoreLogistically(Constants.WALL_COST))) {
        // build turret + 8 walls
        Pair<Integer, Integer> closest = pq_closest.poll();
        System.out.println("closest");
        System.out.println(pq_closest);
        spawnTurret(closest.getKey(), closest.getValue());
        //8 walls
        for (int i = -1 + closest.getKey(); i < 1 + 1 + closest.getKey(); i++) {
          for (int j = -1 + closest.getValue(); j < 1 + 1 + closest.getValue(); j++) {
            spawnWall(i, j);
          }
        }
      } else {
        //if can build a useful mine
        pq_farthest.forEach((pair) -> {
          //if there's a resource
          if (Grid.getGridBlock(pair.getKey(), pair.getValue()).get().getEntity() instanceof Resource) {
            //if we aren't already gathering
            for (int i = -1 + pair.getKey(); i < 1 + 1 + pair.getKey(); i++) {
              for (int j = -1 + pair.getValue(); j < 1 + 1 + pair.getValue(); j++) {
                if (Grid.getGridBlock(i, j).get().getEntity() instanceof Mine) {
                  break;
                }
              }
            }
            //build a mine randomly near it
            int i = random.nextInt(1);
            int j = random.nextInt(1);
            spawnMine(pair.getKey() + i, pair.getValue() + j);
            return;
          }
        });
        //otherwise expand
        Pair<Integer, Integer> farthest = pq_farthest.poll();
        spawnWall(farthest.getKey(), farthest.getValue());
      }

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
        public void run() {
          alive = false;
        }
      }, 1000);
    }
    return base.isDead();
  }

  //override creation & removal objects to keep
  //our pq of available spaces updated
  @Override
  public synchronized void spawnWall(int x, int y) {
    super.spawnWall(x, y);
    addBuilding(x, y);
  }

  @Override
  public synchronized void spawnTurret(int x, int y) {
    super.spawnTurret(x, y);
    addBuilding(x, y);
  }

  @Override
  public synchronized void spawnMine(int x, int y) {
    super.spawnMine(x, y);
    addBuilding(x, y);
  }

  private void addBuilding(int x, int y) {
    if (Grid.validateCoordinates(x, y) && validateSpawn(x, y)) {
      int offset = 1;
      while (offset <= 3) {
        for (int i = -offset + x; i < 1 + offset + x; i++) {
          for (int j = -offset + y; j < 1 + offset + y; j++) {
            pq_closest.add(new Pair<>(x, y));
            pq_farthest.add(new Pair<>(x, y));
            spawnableLocs.add(new Pair<>(x, y));
          }
        }
        offset += 1;
      }
    }
  }

  @Override
  public synchronized void remove(int objectType, String objectId) {
    try {
      int x = -1;
      int y = -1;
      if (objectType == Constants.OBJECT_TYPE.MINE.ordinal()) {
        x = mines.get(objectId).getX();
        y = mines.get(objectId).getY();
        Grid.getGridBlock(x, y)
            .get().depopulate();
        mines.remove(objectId);
        score -= Constants.MINE_COST;
      } else if (objectType == Constants.OBJECT_TYPE.TURRET.ordinal()) {
        x = turrets.get(objectId).getX();
        y = turrets.get(objectId).getY();
        Grid.getGridBlock(turrets.get(objectId).getX(),
            turrets.get(objectId).getY()).get().depopulate();
        turrets.remove(objectId);
        score -= Constants.TURRET_COST;
      } else if (objectType == Constants.OBJECT_TYPE.WALL.ordinal()) {
        x = walls.get(objectId).getX();
        y = walls.get(objectId).getY();
        Grid.getGridBlock(walls.get(objectId).getX(), walls.get(objectId).getY())
            .get().depopulate();
        walls.remove(objectId);
        score -= Constants.WALL_COST;
      }
      if (x != -1 && y != -1) {
        spawnableLocs.remove(new Pair<>(x, y));
        pq_closest = new NoDuplicates<>((a, b) -> (int) (distanceToBase((Pair<Integer, Integer>) b) - distanceToBase((Pair<Integer, Integer>) a)));
        pq_farthest = new NoDuplicates<>((a, b) -> (int) (distanceToBase((Pair<Integer, Integer>) b) - distanceToBase((Pair<Integer, Integer>) a)));
        spawnableLocs.forEach((pair) -> {
          pq_closest.add(pair);
          pq_farthest.add(pair);
        });
      }
    } catch (NullPointerException n) {
      System.out.println("Attempted to remove null object");
    }
  }

  //euclidean distance of point to base
  private double distanceToBase(Pair<Integer, Integer> one) {
    return Math.pow((Math.pow((one.getKey() - base.getX()), 2) + Math.pow((one.getValue() - base.getY()), 2)), 0.5);
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

  class NoDuplicates<E> extends PriorityQueue<E> {

    public NoDuplicates(Comparator comp) {
      super(comp);
    }

    public boolean add(E e) {
      boolean isAdded = false;
      if (!super.contains(e)) {
        isAdded = super.add(e);
      }
      return isAdded;
    }
  }
}
