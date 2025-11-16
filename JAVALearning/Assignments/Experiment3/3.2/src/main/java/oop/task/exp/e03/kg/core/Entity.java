package oop.task.exp.e03.kg.core;

public class Entity extends Node {
  private String type;
  private String name;
  private String attribute;
  
  public Entity(int id) {
    this(id, "", String.valueOf(id), "");
  }
  
  public Entity(int id, String type, String name, String attribute) {
    super(id);
    setType(type);
    setName(name);
    setAttribute(attribute);
  }
  
  public String getType() {
    return type;
  }
  public void setType(String type) {
    this.type = type;
  }
  public String getName() {
    return name;
  }
  public void setName(String name) {
    this.name = name;
  }
  public String getAttribute() {
    return attribute;
  }
  public void setAttribute(String attribute) {
    this.attribute = attribute;
  }
}
