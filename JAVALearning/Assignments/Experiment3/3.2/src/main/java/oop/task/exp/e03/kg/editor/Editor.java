package oop.task.exp.e03.kg.editor;

public abstract class Editor<T> {
  private T target; // 待编辑的目标对象
  public abstract String[] values(); // 返回实体数据
  public abstract String[] fieldNames(); // 返回实体字段名称
  public abstract void update(String[] values); // 更新数据
  public T getTarget() {
    return target;
  }
  public void setTarget(T target) {
    this.target = target;
  }
}
