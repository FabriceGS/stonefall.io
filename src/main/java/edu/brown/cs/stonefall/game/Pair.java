package edu.brown.cs.stonefall.game;

import java.util.Objects;

public class Pair {

    public int x;
    public int y;

    public Pair(int x, int y){
        this.x = x;
        this.y = y;
    }

    @Override 
    public boolean equals(Object other) {
        return (other instanceof Pair) 
        && ((Pair) other).x == this.x
        && ((Pair) other).y == this.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }

    public String toString(){
        return "(" + x + ", " + y + ")";
    }

}