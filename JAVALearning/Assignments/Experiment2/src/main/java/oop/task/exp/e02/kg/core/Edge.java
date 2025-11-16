package oop.task.exp.e02.kg.core;

public class Edge {
  private Node from, to; // 起始节点和终止节点
  
  public Edge(Node from, Node to) {
    setFrom(from);
    setTo(to);
  }
  public Node getFrom() {
    return from;
  }

  public void setFrom(Node from) {
    this.from = from;
  }
  
  public Node getTo() {
    return to;
  }

  public void setTo(Node to) {
    this.to = to;
  }
  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    Edge edge = (Edge) o;
    return edge.getFrom().equals(this.getFrom()) && edge.getTo().equals(this.getTo());
  }
  @Override
  public int hashCode() {
    return Integer.hashCode(Math.addExact(getFrom().getId(), getTo().getId()));
  }
}
