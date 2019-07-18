package edu.brown.cs.stonefall.game;

import java.awt.Color;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;
import java.util.Random;
import java.util.concurrent.ConcurrentHashMap;

import edu.brown.cs.stonefall.entity.MeleeAttacker;
import edu.brown.cs.stonefall.entity.RangedAttacker;
import edu.brown.cs.stonefall.interfaces.Attacker;
import edu.brown.cs.stonefall.interfaces.Killable;
import edu.brown.cs.stonefall.map.Grid;
import edu.brown.cs.stonefall.structure.Base;
import edu.brown.cs.stonefall.structure.Mine;
import edu.brown.cs.stonefall.structure.Scaffold;
import edu.brown.cs.stonefall.structure.Turret;
import edu.brown.cs.stonefall.structure.Wall;

/**
 * Player interface to allow bot integration.
 *
 * @author David
 */
public interface Player {
  /**
   * Returns color of player in string format.
   *
   * @return string formatted color
   */
  public String getColorHex();

  /**
   * Validates the spawning of a new object. Checks its coordinates and if it's
   * within 3 units of other owned structures
   *
   * @param x
   *          x coordinate
   * @param y
   *          y coordinate
   * @return true if spawn is valid, false otherwise
   */
  public synchronized boolean validateSpawn(int x, int y);

  /**
   * Spawns a mine at the x, y coordinate.
   *
   * @param x
   *          x coordinate
   * @param y
   *          y coordinate
   */
  public synchronized void spawnMine(int x, int y);

  /**
   * Spawns a melee attacker at the x, y coordinate.
   *
   * @param x
   *          x coordinate
   * @param y
   *          y coordinate
   */
  public synchronized void spawnMeleeAttacker(int x, int y);

  /**
   * Spawns a ranged attacker at the x, y coordinate.
   *
   * @param x
   *          x coordinate
   * @param y
   *          y coordinate
   */
  public synchronized void spawnRangedAttacker(int x, int y);

  /**
   * Spawns a turret at the x, y coordinate.
   *
   * @param x
   *          x coordinate
   * @param y
   *          y coordinate
   */
  public synchronized void spawnTurret(int x, int y);

  /**
   * Spawns a wall at the x, y coordinate.
   *
   * @param x
   *          x coordinate
   * @param y
   *          y coordinate
   */
  public synchronized void spawnWall(int x, int y);
  /**
   * Spawns a scaffold of type scaffoldType at the x, y coordinate.
   *
   * @param x
   *          x coordinate
   * @param y
   *          y coordinate
   * @param scaffoldType
   *          scaffold type: could either be a mine or a turret or a wall
   */
  public synchronized void spawnScaffold(int x, int y, int scaffoldType);

  /**
   * Upgrades the passed in scaffold to its scaffoldType.
   *
   * @param scaffold
   *          scaffold to upgrade
   */
  public synchronized void upgradeScaffold(Scaffold scaffold);

  /**
   * Checks whether a player is dead by checking the base health.
   *
   * @return true if player is dead, false otherwise
   */
  public boolean isDead();
    /**
   * Sets the player's viewing window.
   *
   * @param x1,y1,x1,y2
   *          new resource count
   */
  public void setViewingWindow(int x1, int y1, int x2, int y2);

  /**
   * Sets the player's viewing window.
   *
   * @param x1,y1,x1,y2
   *          new resource count
   */
  public boolean inViewingWindow(int x, int y);
  /**
   * Sets the player's resource count.
   *
   * @param newCount
   *          new resource count
   */
  public void setResourceCount(int newCount);

  /**
   * Gets the resource count.
   *
   * @return resource count
   */
  public int getResourceCount();

  /**
   * Gets the player's name.
   *
   * @return name
   */
  public String getName();

  /**
   * Gets the player's id.
   *
   * @return id
   */
  public String getId();

  /**
   * Gets the player's attackers.
   *
   * @return map from attacker id to attacker object
   */
  public Map<String, Attacker> getAttackers();

  /**
   * Gets the player's turrets.
   *
   * @return map from turret id to turret object
   */
  public Map<String, Turret> getTurrets() {
    return turrets;
  }

  /**
   * Gets the player's walls.
   *
   * @return map from wall id to wall object
   */
  public Map<String, Wall> getWalls();

  /**
   * Gets the player's mines.
   *
   * @return map from mine id to mine object
   */
  public Map<String, Mine> getMines();
  /**
   * Gets the player's scaffolds.
   *
   * @return map from scaffold id to scaffold object
   */
  public Map<String, Scaffold> getScaffolds();

  /**
   * Gets the player's base.
   *
   * @return base
   */
  public Base getBase();

  /**
   * Validates a target.
   *
   * @param target
   *          target to validate
   * @param attacker
   *          attacker that wants to attack target
   * @return true if target is valid, false otherwise
   */
  public boolean validateTarget(Optional<Killable> target, Attacker attacker);

  @Override
  public boolean equals(Object other);

  @Override
  public int hashCode();

  /**
   * Removes an object, and updates map, score, and player hashmaps accordingly.
   *
   * @param objectType
   *          object type we wish to remove
   * @param objectId
   *          id of object we wish to remove
   */
  public synchronized void remove(int objectType, String objectId);

  /**
   * Sells an object. Increments the resource count of the player and then
   * removes it.
   *
   * @param objectType
   *          type of object we want to sell
   * @param objectId
   *          id of object we want to sell
   */
  public synchronized void sell(int objectType, String objectId);

  /**
   * Gets the player score.
   *
   * @return score
   */
  public int getScore();

  /**
   * Gets the players top score.
   *
   * @return top score
   */
  public int getTopScore();

  /**
   * Multiplies cost by a logistic growth model with a carrying capacity of a
   * ten multiplier.
   *
   * @param cost
   *          cost we wish to multiply logistically
   * @return multiplied cost
   */
  public int multiplyByScoreLogistically(int cost);
}
