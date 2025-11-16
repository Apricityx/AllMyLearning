package oop.task.exp.e02.kg.view;

import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import oop.task.exp.e02.kg.core.Relationship;

public class RelationshipDialog extends Dialog<Relationship>{
  private Relationship relation;
  public RelationshipDialog(Relationship rel) {
    relation = rel;
    this.setTitle("编辑关系信息");
    // 添加确认和取消按钮
    ButtonType okButtonType = new ButtonType("确认", ButtonType.OK.getButtonData());
    getDialogPane().getButtonTypes().addAll(okButtonType, ButtonType.CANCEL);

    // 使用格网布局，展示实体的属性
    GridPane grid = new GridPane();
    grid.setHgap(10);
    grid.setVgap(10);

    // 创建文本输入框
    TextField nameField = new TextField(relation.getName());
    TextField attrField = new TextField(relation.getAttribute());

    // 将输入框放入格网中
    grid.add(new Label("名称:"), 0, 1);
    grid.add(nameField, 1, 1);
    grid.add(new Label("属性:"), 0, 2);
    grid.add(attrField, 1, 2);

    getDialogPane().setContent(grid);

    // 设置确认按钮的行为
    setResultConverter(dialogButton -> {
      if (dialogButton == okButtonType) {
        // 更新实体信息
        relation.setName(nameField.getText());
        relation.setAttribute(attrField.getText());
        return relation;
      }
      return null;
    });
  }
}
