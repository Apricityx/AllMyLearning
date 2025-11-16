package oop.task.exp.e03.kg.core;

public class Node {
  private int id; // 唯一编号
  public Node(int id){
    setId(id);
  }
  public int getId() {
    return id;
  }
  public void setId(int id) {
    this.id = id;
  }
  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    Node node = (Node) o;
    return id == node.id;
  }
  @Override
  public int hashCode() {
    return Integer.hashCode(id);
  }
}
