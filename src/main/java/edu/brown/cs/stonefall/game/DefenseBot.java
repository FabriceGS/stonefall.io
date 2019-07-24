package edu.brown.cs.stonefall.game;

import java.awt.Color;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;
import java.util.Random;
import java.util.concurrent.ConcurrentHashMap;
import java.util.PriorityQueue;
import java.util.Comparator;
import java.util.ArrayList;
import java.lang.Math;

import edu.brown.cs.stonefall.entity.MeleeAttacker;
import edu.brown.cs.stonefall.entity.RangedAttacker;
import edu.brown.cs.stonefall.interfaces.Attacker;
import edu.brown.cs.stonefall.interfaces.Killable;
import edu.brown.cs.stonefall.map.Grid;
import edu.brown.cs.stonefall.structure.Base;
import edu.brown.cs.stonefall.structure.Mine;
import edu.brown.cs.stonefall.structure.Scaffold;
import edu.brown.cs.stonefall.structure.Resource;
import edu.brown.cs.stonefall.structure.Turret;
import edu.brown.cs.stonefall.structure.Wall;

/**
 * Class representing the game of Stonefall.
 */
public class DefenseBot extends Player {
    //keep a priority queue that measures distance from base
    //we will pick farthest from base when expanding and closest to base when building defense
    protected PriorityQueue<Pair> pq_closest;
    protected PriorityQueue<Pair> pq_farthest;
    protected ArrayList<Pair> spawnableLocs;

    /**
    * Constructs a new instance of a Stonefall game.
    */
    public DefenseBot(String name, String id) {
        super(name, id);
        //lol change the base
        base = new Base(Grid.getGridBlock(10, 10).get());

        System.out.println("super player constructed");
        resourceCount=100000;
        pq_closest = new NoDuplicates<Pair>((a, b) -> (int) (distanceToBase((Pair)b) - distanceToBase((Pair)a)));
        pq_farthest = new NoDuplicates<Pair>((a, b) -> (int) (distanceToBase((Pair)a) - distanceToBase((Pair)b)));
        spawnableLocs = new ArrayList<Pair>();
        System.out.println("bot getting constructed 1");

        //fill up playable locations
        int offset = 1;
        while (offset <= 3) {
            for (int i = -offset + base.getX(); i < 1 + offset + base.getX(); i++) {
                for (int j = -offset + base.getY(); j < 1 + offset + base.getY(); j++) {
                    System.out.println("iterating within constructor");
                    pq_closest.add(new Pair(i, j));
                    pq_farthest.add(new Pair(i, j));
                    spawnableLocs.add(new Pair(i, j));
                }
            }
            offset += 1;
        }
        System.out.println("bot done getting constructed");
    }

    public void run() {
        if(pq_closest.isEmpty() || pq_farthest.isEmpty()){
            return;
        }
        if(resourceCount > (multiplyByScoreLogistically(Constants.TURRET_COST) + 8 * multiplyByScoreLogistically(Constants.WALL_COST))){
		    // build turret + 8 walls
            Pair closest = pq_closest.poll();
            System.out.println("closest");
            System.out.println(pq_closest);
            spawnTurret(closest.x, closest.y);
            //8 walls
            for (int i = -1 + closest.x; i < 1 + 1 + closest.x; i++) {
                for (int j = -1 + closest.y; j < 1 + 1 + closest.y; j++) {
                    spawnWall(i, j);
                }
            }
        } else {
            //if can build a useful mine
            pq_farthest.forEach((pair) -> {
                //if there's a resource
                if(Grid.getGridBlock(pair.x, pair.y).get().getEntity() instanceof Resource){
                    //if we aren't already gathering
                    for (int i = -1 + pair.x; i < 1 + 1 + pair.x; i++) {
                        for (int j = -1 + pair.y; j < 1 + 1 + pair.y; j++) {
                            if(Grid.getGridBlock(i, j).get().getEntity() instanceof Mine){
                                break;
                            }
                        }
                    }
                    //build a mine randomly near it
                    int i = random.nextInt(1);
                    int j = random.nextInt(1);
                    spawnMine(pair.x + i, pair.y + j);
                    return;
                }
            });
            //otherwise expand
            Pair farthest = pq_farthest.poll();
            spawnWall(farthest.x, farthest.y);
        }
    }

    //override creation & removal objects to keep
    //our pq of available spaces updated
    @Override
    public synchronized void spawnWall(int x, int y){
        super.spawnWall(x, y);
        addBuilding(x, y);
    }

    @Override
    public synchronized void spawnTurret(int x, int y){
        super.spawnTurret(x, y);
        addBuilding(x, y);
    }

    @Override
    public synchronized void spawnMine(int x, int y){
        super.spawnMine(x, y);
        addBuilding(x, y);
    }

    private void addBuilding(int x, int y){
        System.out.println("bot is building at: " + x + ", " + y);
        
        int offset = 1;
        while (offset <= 3) {
            for (int i = -offset + x; i < 1 + offset + x; i++) {
                for (int j = -offset + y; j < 1 + offset + y; j++) {
                    System.out.println("adding location: " + i + ", " + j);
                    if (Grid.validateCoordinates(i, j) && validateSpawn(i, j)) {
                        pq_closest.add(new Pair(i, j));
                        pq_farthest.add(new Pair(i, j));
                        spawnableLocs.add(new Pair(i, j));
                    }
                }
            }
            offset +=1 ;
        }
    }

    @Override 
    public synchronized void remove(int objectType, String objectId) {
        try{
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
            if(x!=-1 && y!=-1){
                spawnableLocs.remove(new Pair(x, y));
                pq_closest = new NoDuplicates<Pair>((a, b) -> (int) (distanceToBase((Pair)b) - distanceToBase((Pair)a)));
                pq_farthest = new NoDuplicates<Pair>((a, b) -> (int) (distanceToBase((Pair)b) - distanceToBase((Pair)a)));
                spawnableLocs.forEach((pair) -> {
                    pq_closest.add(pair);
                    pq_farthest.add(pair);
                });
            }
        } catch (NullPointerException n){
            System.out.println("Attempted to remove null object");
        }        
    }


    //euclidean distance of point to base
    private double distanceToBase(Pair one){
        return  Math.pow((Math.pow((one.x - base.getX()), 2) + Math.pow((one.y - base.getY()), 2)), 0.5);
    }

}

class NoDuplicates<E> extends PriorityQueue<E> {

    public NoDuplicates(Comparator comp){
        super(comp);
    }

    public boolean add(E e){
        boolean isAdded = false;
        if(!super.contains(e)){
            isAdded = super.add(e);
        }
        return isAdded;
    }
}