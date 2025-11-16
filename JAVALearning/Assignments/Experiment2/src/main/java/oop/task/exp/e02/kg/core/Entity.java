package oop.task.exp.e02.kg.core;

public class Entity extends Node {

    private String name;
    private String type;
    private String attribute;

    Entity(int seqNumber, String type, String name, String attribute) {
        super(seqNumber);
        this.type = type;
        this.name = name;
        this.attribute = attribute;
    }

    public String getType() {
        return this.type;
    }

    public String getAttribute() {
        return this.attribute;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setAttribute(String text) {
        this.attribute = text;
    }

    public void setType(String text) {
        this.type = text;
    }
}
