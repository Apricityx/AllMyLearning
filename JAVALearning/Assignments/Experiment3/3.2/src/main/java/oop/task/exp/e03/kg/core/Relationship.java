package oop.task.exp.e03.kg.core;

public class Relationship extends Edge{
  private String name;
  private String attribute;
  public Relationship(Entity from, Entity to, String name, String attribute) {
    super(from, to);
    setName(name);
    setAttribute(attribute);
  }
  public Relationship(Entity from, Entity to) {
    this(from, to, "关系", "无");
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
