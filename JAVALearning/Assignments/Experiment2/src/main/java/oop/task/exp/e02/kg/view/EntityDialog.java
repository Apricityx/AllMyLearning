package oop.task.exp.e02.kg.view;

import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import oop.task.exp.e02.kg.core.Entity;


public class EntityDialog extends Dialog<Entity>{
  private Entity entity;
  
  public EntityDialog(Entity e) {
    entity = e;
    this.setTitle("编辑实体信息");
    // 添加确认和取消按钮
    ButtonType okButtonType = new ButtonType("确认", ButtonType.OK.getButtonData());
    getDialogPane().getButtonTypes().addAll(okButtonType, ButtonType.CANCEL);

    // 使用格网布局，展示实体的属性
    GridPane grid = new GridPane();
    grid.setHgap(10);
    grid.setVgap(10);

    // 创建文本输入框
    TextField typeField = new TextField(entity.getType());
    TextField nameField = new TextField(entity.getName());
    TextField attrField = new TextField(entity.getAttribute());

    // 将输入框放入格网中
    grid.add(new Label("类型:"), 0, 0);
    grid.add(typeField, 1, 0);
    grid.add(new Label("名称:"), 0, 1);
    grid.add(nameField, 1, 1);
    grid.add(new Label("属性:"), 0, 2);
    grid.add(attrField, 1, 2);

    getDialogPane().setContent(grid);

    // 设置确认按钮的行为
    setResultConverter(dialogButton -> {
      if (dialogButton == okButtonType) {
        // 更新实体信息
        entity.setType(typeField.getText());
        entity.setName(nameField.getText());
        entity.setAttribute(attrField.getText());
        return entity;
      }
      return null;
    });
  }
  
}
