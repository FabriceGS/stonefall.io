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
 * Backend player class. Responsible for maintaining relationship between player
 * and all of their owned objects.
 *
 * @author Theodoros
 */
public class HumanPlayer extends Player{
    //these represent the viewing window of the user on the frontend
  private int topLX;
  private int topLY;
  private int bottomRX;
  private int bottomRY;

  /**
   * Constructor for a player.
   *
   * Fields:
   *
   * name: player name
   *
   * id: player id
   *
   * color: player color
   *
   * mines: hashmap of all mines owned by player
   *
   * attackers: hashmap of all attackers owned by player
   *
   * turrets: hashmap of all turrets owned by player
   *
   * walls: hashmap of all walls owned by player
   *
   * scaffolds: hashmap of all scaffolds owned by player
   *
   * base: player base
   *
   * score: player score
   *
   * resourceCount: player resource count
   *
   * @param name
   *          name of player
   * @param id
   *          id of player
   */
  public HumanPlayer(String name, String id) {
    super(name, id);
    random = new Random();

    if (name.equals("breezy") || name.equals("jj") || name.equals("papper")
        || name.equals("dave") || name.equals("mac")) {
      resourceCount = 200000;
    } else {
      resourceCount = 2000;
    }

    mineIdNum = 0;
    attackerIdNum = 0;
    structureIdNum = 0;
    scaffoldIdNum = 0;
    
  }


    /**
   * Sets the player's viewing window.
   *
   * @param x1,y1,x1,y2
   *          new resource count
   */
  public void setViewingWindow(int x1, int y1, int x2, int y2) {
    topLX = x1;
    topLY = y1;
    bottomRX = x2;
    bottomRY = y2;
  }

  /**
   * Sets the player's viewing window.
   *
   * @param x1,y1,x1,y2
   *          new resource count
   */
  public boolean inViewingWindow(int x, int y) {
    // return (x >= topLX-1) && (x<= bottomRX+1) && (y >= topLY-1) && (y <= bottomRY+1);
    return (x >= topLX) && (x<= bottomRX) && (y >= topLY) && (y <= bottomRY);
  }


}
