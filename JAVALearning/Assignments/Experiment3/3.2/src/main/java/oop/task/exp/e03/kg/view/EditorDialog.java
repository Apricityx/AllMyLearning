package oop.task.exp.e03.kg.view;

import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import oop.task.exp.e03.kg.editor.Editor;


public class EditorDialog<T> extends Dialog<T> {
    private Editor<T> editor; // 编辑类

    /**
     * 编辑框
     * - 泛型编程，实现了Entity和Relationship的编辑框
     * - 传入一个编辑类，需要编辑类有以下方法：
     * 1. values() 返回实体数据
     * 2. fieldNames() 返回实体字段名称，用于显示原来的数据
     * 3. update(String[] values) 更新数据
     *
     * @param e 编辑类
     */
    public EditorDialog(Editor<T> e) {
        this.editor = e;
        this.setTitle("编辑信息");
        // 添加确认和取消按钮
        ButtonType okButtonType = new ButtonType("确认", ButtonType.OK.getButtonData());
        getDialogPane().getButtonTypes().addAll(okButtonType, ButtonType.CANCEL);

        // 使用格网布局，展示实体的属性
        GridPane grid = new GridPane();
        grid.setHgap(10);
        grid.setVgap(10);

        // 初始化编辑框的结构和信息
        String[] values = editor.values(); // 实体数据
        TextField[] textFields = new TextField[values.length];
        for (int i = 0; i < values.length; i++) {
            textFields[i] = new TextField(values[i]);
        }
        String[] fields = editor.fieldNames(); // 字段名称
        for (int i = 0; i < values.length; i++) {
            grid.add(new Label(fields[i]), 0, i); // 添加字段标签
            System.out.println(textFields[i].getText());
            // 此时换行符被删除
            grid.add(textFields[i], 1, i); // 添加文本框显示具体数据
//            grid.add(new TextField("123"), 2, i); // 添加文本框显示具体数据
        }
        getDialogPane().setContent(grid);

        // 设置确认按钮的行为
        setResultConverter(dialogButton -> {
            if (dialogButton == okButtonType) {
                // 获取编辑框的数据信息
                String[] newValues = new String[values.length];
                for (int i = 0; i < values.length; i++) {
                    newValues[i] = textFields[i].getText();
                }
                editor.update(newValues); // 更新实体信息
                return editor.getTarget(); // 返回实体对象
            }
            return null;
        });
    }
}
