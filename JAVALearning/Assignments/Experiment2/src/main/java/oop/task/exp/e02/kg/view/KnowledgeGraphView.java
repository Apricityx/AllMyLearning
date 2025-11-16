package oop.task.exp.e02.kg.view;

import java.util.Optional;

import javafx.scene.Group;
import javafx.scene.control.Label;
import javafx.scene.input.MouseButton;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.scene.text.Text;
import oop.task.exp.e02.kg.core.Entity;
import oop.task.exp.e02.kg.core.KnowledgeGraph;
import oop.task.exp.e02.kg.core.Relationship;

public class KnowledgeGraphView extends Pane{
  private KnowledgeGraph graph; // 每个图谱视图对应一个图谱对象
  private static EntityLabel selectedStart, selectedEnd; // 当前选中的实体标签
  
  public KnowledgeGraphView() {
    graph = new KnowledgeGraph(); // 暂不考虑加载已有图谱的情况
    actionInitialize();
  }
  
  public void actionInitialize() {
    this.setOnMousePressed(event -> {
      if (event.getButton() == MouseButton.PRIMARY) {
        clear();
      }
      event.consume();
    });
    this.setOnMouseClicked(event -> this.requestFocus()); // 鼠标点击后获取焦点
    this.setOnKeyPressed(e -> {
      System.out.println(e.getCode());
      switch(e.getCode()) {
        case SPACE:{
          createRelationship().ifPresent(line -> {
            this.getChildren().add(0, line);
            clear();
          });
        }break;
        default: break;
      }
      e.consume();
    });
  }
  
  // 根据文本创建一个实体
  public void add(String text) {
    graph.addEntity("", text, "").ifPresent(e -> {
      getChildren().add(new EntityLabel(e));
    });
  }
  
  // 选择一个实体标签
  public void select(EntityLabel e) {
    if(selectedStart == null) {
      selectedStart = e;
      selectedStart.selectedStyle();
    }else if(selectedStart != null && selectedEnd == null){
      selectedEnd = e;
      selectedEnd.selectedStyle();
    }else {
      selectedStart.nonSelectedStyle();
      selectedStart = selectedEnd;
      selectedEnd = e;
      selectedEnd.selectedStyle();
    }
  }
  // 清除选择
  public void clear() {
    if(selectedStart != null) {
      selectedStart.nonSelectedStyle();
      selectedStart = null;
    }
    if(selectedEnd != null) {
      selectedEnd.nonSelectedStyle();
      selectedEnd = null;
    }
  }
  
  // 创建关系
  public Optional<RelationLine> createRelationship() {
    if(selectedStart != null && selectedEnd != null) {
      Entity from = selectedStart.getEntity(); // 起始点实体
      Entity to = selectedEnd.getEntity(); // 终止点实体
      Optional<RelationLine> line = Optional.empty();
      Optional<Relationship> relation = graph.addRelation(from, to);
      if(relation.isPresent()) {
        line = Optional.ofNullable(new RelationLine(selectedStart, selectedEnd, relation.get()));
      }
      return line;
    }else {
      return Optional.empty();
    }
  }
  
  // 展示实体的标签类
  public class EntityLabel extends Label{
    private Entity entity; // 实体
    private double offsetX, offsetY; // 移动参考坐标
    public EntityLabel(Entity entity){
      setEntity(entity);
      this.setText(entity.getName());
      nonSelectedStyle();
      // 移动事件
      this.setOnMousePressed(event -> {
        if (event.getButton() == MouseButton.PRIMARY) { // 左键拖动
          offsetX = event.getSceneX() - this.getLayoutX();
          offsetY = event.getSceneY() - this.getLayoutY();
        }   
      });
      this.setOnMouseDragged(event -> {
        if (event.getButton() == MouseButton.PRIMARY) { // 左键拖动
          this.setLayoutX(event.getSceneX() - offsetX);
          this.setLayoutY(event.getSceneY() - offsetY);
        }
      });
      // 处理双击事件，改变标签的背景颜色
      this.setOnMouseClicked(event -> {
        if (event.getClickCount() == 2) {
          new EntityDialog(entity).showAndWait().ifPresent(update -> {
            this.updateText(); // 更新标签文本
          });
        }else if(event.getButton() == MouseButton.SECONDARY){
          select(this);
        }
      });
    }
    
    public void nonSelectedStyle() {
      this.setStyle("-fx-background-color: lightblue; "
          + "-fx-padding: 10; "
          + "-fx-background-radius: 15; "
          + "-fx-border-color: blue; "
          + "-fx-border-radius: 15; "
          + "-fx-border-width: 2;");
    }
    public void selectedStyle() {
      this.setStyle("-fx-background-color: lightblue; "
          + "-fx-padding: 10; "
          + "-fx-background-radius: 15; "
          + "-fx-border-color: yellow; "
          + "-fx-border-radius: 15; "
          + "-fx-border-width: 2;");
    }
    // 更新标签文本
    public void updateText() {
      this.setText(entity.getName());
    }
    
    public Entity getEntity() {
      return entity;
    }

    public void setEntity(Entity entity) {
      this.entity = entity;
    }
  }
  
  // 展示关系的线段类
  public class RelationLine extends Group{
    private Relationship relation;
    private Line line = new Line();
    private Text label;
    public RelationLine(EntityLabel start, EntityLabel end, Relationship rel) {
      this.relation = rel;
      label = new Text(relation.getName());
      line.setStrokeWidth(2.0);
      label.setFill(Color.RED);
      line.startXProperty().bind(start.layoutXProperty().add(start.widthProperty().divide(2)));
      line.startYProperty().bind(start.layoutYProperty().add(start.heightProperty().divide(2)));
      line.endXProperty().bind(end.layoutXProperty().add(end.widthProperty().divide(2)));
      line.endYProperty().bind(end.layoutYProperty().add(end.heightProperty().divide(2)));
      label.xProperty().bind(line.startXProperty().add(line.endXProperty()).divide(2));
      label.yProperty().bind(line.startYProperty().add(line.endYProperty()).divide(2).subtract(5));
      this.getChildren().addAll(line, label);
      this.setOnMouseClicked(event -> {
        if (event.getClickCount() == 2) {
          new RelationshipDialog(relation).showAndWait().ifPresent(update -> {
            this.updateText(); // 更新线标签
          });
        }
      });
    }
    // 更新线标签
    public void updateText() {
      label.setText(relation.getName());
    }
  }
}
