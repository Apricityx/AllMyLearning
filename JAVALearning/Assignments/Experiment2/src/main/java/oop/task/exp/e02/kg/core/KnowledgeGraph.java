package oop.task.exp.e02.kg.core;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Optional;
import java.util.Set;

public class KnowledgeGraph {
  private Set<Entity> entities; // 实体集合
  private Set<Relationship> relations; // 关系集合
  private Map<Entity, Set<Relationship>> outMap; // 出发索引
  private Map<Entity, Set<Relationship>> inMap;  // 进入索引
  private int seqNumber; // 实体自动编号
  
  public KnowledgeGraph() {
    seqNumber = 1;
    entities = new HashSet<Entity>();
    relations = new HashSet<Relationship>();
    outMap = new HashMap<>();
    inMap = new HashMap<>();
  }
  
  // 创建和添加实体
  public Optional<Entity> addEntity(String type, String name, String attribute) {
    Entity e = new Entity(seqNumber++, type, name, attribute);
    if(addEntity(e)) {
      return Optional.ofNullable(e); // 添加成功
    }else {
      return Optional.empty(); // 添加失败，则返回空
    }
  }
  public boolean addEntity(Entity e) {
    return this.entities.add(e);
  }
  // 创建与添加关系
  public Optional<Relationship> addRelation(Entity from, Entity to) {
    Optional<Relationship> r = Optional.empty();
    if(entities.contains(from) && entities.contains(to)) {
      Relationship rel = new Relationship(from, to);
      if(relations.add(rel)) { // 添加成功
        outMap.computeIfAbsent(from, f -> new HashSet<>()).add(rel); // 更新索引
        inMap.computeIfAbsent(to, f -> new HashSet<>()).add(rel); // 更新索引
        r = Optional.ofNullable(rel);
      }
    }
    return r;
  }
  
  //删除实体
  public void removeEntity(Entity e) {
    this.entities.remove(e);
    removeAllRelsByFrom(e);
    removeAllRelsByTo(e);
  }
  // 根据作为起始节点的所有关系
  public void removeAllRelsByFrom(Entity from) {
    if (outMap.containsKey(from)) {
      Set<Relationship> rels = outMap.get(from);
      relations.removeAll(rels); // 删除关系
      outMap.remove(from); // 删除索引
    }
  }

  // 根据作为终止节点的所有关系
  public void removeAllRelsByTo(Entity to) {
    if (inMap.containsKey(to)) {
      Set<Relationship> rels = inMap.get(to);
      relations.removeAll(rels); // 删除关系
      inMap.remove(to); // 删除索引
    }
  }

  public Set<Entity> getEntities() {
    return entities;
  }
  public Set<Relationship> getRelations(){
    return relations;
  }
  
}
