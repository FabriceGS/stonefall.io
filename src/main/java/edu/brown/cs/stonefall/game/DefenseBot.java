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
import java.util.HashSet;
import java.util.Collections;
import java.lang.Math;
import java.util.Iterator;

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
    protected PriorityQueue<Pair> pq_farthest;
    protected PriorityQueue<Pair> pq_closest;
    protected ArrayList<Pair> spawnableLocs;
    //whenever an accessible resource is found, it is added here
    protected HashSet<Pair> potentialResources;
    protected HashSet<Pair> alreadyMined;
    

    /**
    * Constructs a new instance of a Stonefall game.
    */
    public DefenseBot(String name, String id) {
        super(name, id);
        //lol change the base
        base = new Base(Grid.getGridBlock(10, 10).get());

        System.out.println("super player constructed");
        resourceCount=10000;
        pq_farthest = new NoDuplicates<Pair>((a, b) -> (int) (distanceToBase((Pair)b) - distanceToBase((Pair)a)));
        pq_closest = new NoDuplicates<Pair>((a, b) -> (int) (distanceToBase((Pair)a) - distanceToBase((Pair)b)));
        spawnableLocs = new ArrayList<Pair>();
        potentialResources = new HashSet<Pair>();
        alreadyMined = new HashSet<Pair>();
        System.out.println("bot getting constructed 1");

        //fill up playable locations
        int offset = 1;
        while (offset <= 3) {
            for (int i = -offset + base.getX(); i < 1 + offset + base.getX(); i++) {
                for (int j = -offset + base.getY(); j < 1 + offset + base.getY(); j++) {
                    System.out.println("iterating within constructor");
                    pq_farthest.add(new Pair(i, j));
                    pq_closest.add(new Pair(i, j));
                    spawnableLocs.add(new Pair(i, j));
                }
            }
            offset += 1;
        }
        System.out.println("bot done getting constructed");
    }

    public void run() {
        System.out.println("resources: " + resourceCount);
        if(pq_farthest.isEmpty() || pq_closest.isEmpty()){
            return;
        }
        boolean builtMine = false;
        Pair resourceLoc = new Pair(-1, -1);
        if(resourceCount > (multiplyByScoreLogistically(Constants.TURRET_COST) + 8 * multiplyByScoreLogistically(Constants.WALL_COST))){
		    // build turret + 8 walls
            Pair closest = pq_closest.poll();
            System.out.println("building defense");
            System.out.println(pq_closest);
            spawnScaffold(closest.x, closest.y, Constants.OBJECT_TYPE.TURRET.ordinal());
            //8 walls
            for (int i = -1 + closest.x; i < 1 + 1 + closest.x; i++) {
                for (int j = -1 + closest.y; j < 1 + 1 + closest.y; j++) {
                    spawnScaffold(i, j, Constants.OBJECT_TYPE.WALL.ordinal());
                }
            }
        } else {
            //if can build a useful mine
            System.out.println("potential resources: " + potentialResources);

            Iterator<Pair> resourceItr = potentialResources.iterator();
            while(resourceItr.hasNext() && !builtMine){
                Pair pair = resourceItr.next();
                System.out.println("checking resource :" + pair);
                //if there's a resource
                // System.out.println("checking: " + pair.x + ", " + pair.y + Grid.getGridBlock(pair.x, pair.y).get().getEntity());
                // if(Grid.getGridBlock(pair.x, pair.y).get().getEntity() instanceof Resource){
                //     System.out.println("found resource");
                    //if we aren't already gathering
                int toMineX = -1;
                int toMineY = -1;
                for (int i = -1 + pair.x; i < 1 + 1 + pair.x; i++) {
                    for (int j = -1 + pair.y; j < 1 + 1 + pair.y; j++) {
                        if (Grid.validateCoordinates(i, j) && validateSpawn(i, j)) {
                            toMineX = i;
                            toMineY = j;
                        }
                        //this code should be duplicate, but leaving just in case
                        // if(Grid.getGridBlock(i, j).get().getEntity() instanceof Mine){
                        //     System.out.println("we are already mining");
                        //     toMineX = -1;
                        //     toMineY = -1;
                        //     //remove the resource from our set, no need to keep trying to mine this
                        //     potentialResources.remove(new Pair(pair.x, pair.y));
                        // }
                    }
                }
                //build a mine near it, if enough resources
                //if not enough resources just keep hitting this loop until we have enough resources
                if(toMineY != -1 && toMineY != -1){
                    if(resourceCount > multiplyByScoreLogistically(Constants.MINE_COST)){
                        System.out.println("building mine");
                        spawnScaffold(toMineX, toMineY, Constants.OBJECT_TYPE.MINE.ordinal());
                        //note that we have mined this resource
                        alreadyMined.add(pair);
                        builtMine = true;
                        resourceLoc = pair;
                    } else {
                        return;
                    }
                } 
            }

            if(builtMine){
                //remove the resource from our set, no need to keep trying to mine this
                potentialResources.remove(new Pair(resourceLoc.x, resourceLoc.y));
            } else {
                //expand
                if(resourceCount > multiplyByScoreLogistically(Constants.WALL_COST)){
                    System.out.println("expanding");
                    System.out.println(pq_farthest);
                    //otherwise expand
                    Pair farthest = pq_farthest.poll();
                    spawnScaffold(farthest.x, farthest.y, Constants.OBJECT_TYPE.WALL.ordinal());
                }
            }
        }
    }

    // //override creation & removal objects to keep
    // //our pq of available spaces updated
    // @Override
    // public synchronized void spawnWall(int x, int y){
    //     // super.spawnWall(x, y);
    //     // resourceCount -= multiplyByScoreLogistically(Constants.WALL_COST);
    //     spawnScaffold(x, y, Constants.OBJECT_TYPE.WALL.ordinal());
    // }

    // @Override
    // public synchronized void spawnTurret(int x, int y){
    //     // super.spawnTurret(x, y);
    //     // resourceCount -= multiplyByScoreLogistically(Constants.TURRET_COST);
    //     spawnScaffold(x, y, Constants.OBJECT_TYPE.TURRET.ordinal());
    // }

    // @Override
    // public synchronized void spawnMine(int x, int y){
    //     // super.spawnMine(x, y);
    //     // resourceCount -= multiplyByScoreLogistically(Constants.MINE_COST);
    //     spawnScaffold(x, y, Constants.OBJECT_TYPE.MINE.ordinal());
    // }

    @Override
    public synchronized void spawnScaffold(int x, int y, int scaffoldType) {
        super.spawnScaffold(x, y, scaffoldType);
        pq_closest.remove(new Pair(x, y));
        pq_farthest.remove(new Pair(x, y));
        spawnableLocs.removeAll(Collections.singleton(new Pair(x, y)));
    }

    @Override
    public synchronized void upgradeScaffold(Scaffold scaffold) {
        super.upgradeScaffold(scaffold);
        addBuilding(scaffold.getX(), scaffold.getY());
    }

    private void addBuilding(int x, int y){        
        int offset = 1;
        while (offset <= 3) {
            for (int i = -offset + x; i < 1 + offset + x; i++) {
                for (int j = -offset + y; j < 1 + offset + y; j++) {
                    if (Grid.inBounds(i, j)
                        && (!Grid.getGridBlock(i, j).get().isFull())){
                        pq_farthest.add(new Pair(i, j));
                        pq_closest.add(new Pair(i, j));
                        spawnableLocs.add(new Pair(i, j));
                    } else if (Grid.getGridBlock(i, j).isPresent()) {
                        if (Grid.getGridBlock(i, j).get().getEntity() instanceof Resource) {
                            if(!alreadyMined.contains(new Pair(i, j))){
                                potentialResources.add(new Pair(i, j));
                            }
                        }
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
            //if we managed to remove something
            if(x!=-1 && y!=-1){
                //trying to solve the problem of keeping track of all spaces available to build in
                //without iterating over every single object again
                //remove all the locations added due to this object
                ArrayList<Pair> locsToRemove = offsetAway(x, y, 3);
                locsToRemove.forEach((pair) -> {
                    spawnableLocs.remove(pair);
                });
                pq_farthest = new NoDuplicates<Pair>((a, b) -> (int) (distanceToBase((Pair)b) - distanceToBase((Pair)a)));
                pq_closest = new NoDuplicates<Pair>((a, b) -> (int) (distanceToBase((Pair)b) - distanceToBase((Pair)a)));
                spawnableLocs.forEach((pair) -> {
                    pq_farthest.add(pair);
                    pq_closest.add(pair);
                });
            }
        } catch (NullPointerException n){
            System.out.println("Attempted to remove null object");
        }        
    }

    //return list of pairs of locs offset away from (x, y)
    private ArrayList<Pair> offsetAway(int x, int y, int offsetLimit){
        ArrayList<Pair> retList = new ArrayList<>();
        int offset = 1;
        while (offset <= offsetLimit) {
            for (int i = -offset + x; i < 1 + offset + x; i++) {
                for (int j = -offset + y; j < 1 + offset + y; j++) {
                    retList.add(new Pair(i, j));
                }
            }
            offset +=1 ;
        }
        return retList;
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