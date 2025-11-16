package oop.task.exp.e02.kg.core;

public class Relationship extends Edge {
    //todo
    public String name;
    public String attribute;

    public Relationship(Entity from, Entity to) {
        super(from, to);
    }

    public String getName() {
        return this.name;
    }

    public String getAttribute() {
        return this.attribute;
    }

    public void setName(String text) {
        this.name = text;
    }

    public void setAttribute(String text) {
        this.attribute = text;
    }
}

