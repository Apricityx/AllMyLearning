package tech.mctown.javafx;

import javafx.application.Application;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.stage.Stage;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.util.Duration;
public class RectApp extends Application {
    double i = 0.1;
    @Override
    public void start(Stage primaryStage) {
// 创建画布并设置大小
        Canvas canvas = new Canvas(500, 400);
        GraphicsContext gc = canvas.getGraphicsContext2D();
// 创建动画，每隔16ms更新一次角度，相当于每秒约60帧
        Rectangle rect = new Rectangle(200, 200, 200, 5);
        Timeline animation = new Timeline(new KeyFrame(Duration.millis(16), e -> {
            draw(gc, rect);
            rect.rotate(2);
// 莱姆尼斯卡曲线的参数方程计算坐标
            double x = 200 + 100 * Math.cos(i);
            double y = 200 + 100 * Math.sin(i) * Math.cos(i);
            rect.moveTo(x, y);
            i += 0.01;
        }));
        animation.setCycleCount(Timeline.INDEFINITE); // 无限循环
        animation.play(); // 开始动画
// 设置场景和舞台
        Group root = new Group();
        root.getChildren().add(canvas);
        Scene scene = new Scene(root, 500, 400);
        primaryStage.setTitle("矩形旋转");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
    // 绘制旋转矩形
    private void draw(GraphicsContext gc, Rectangle rect) {
// 清空画布
        gc.clearRect(0, 0, 500, 400);
// 保存当前状态
        gc.save();
// 将画布的原点平移到矩形中心
        gc.translate(rect.getCenterX(), rect.getCenterY());
// 旋转坐标系
        gc.rotate(rect.getAngle());
// 设置矩形颜色
        gc.setFill(Color.BLUE);
// 绘制矩形，绘制的坐标是相对于translate后的(0,0)的
        gc.fillRect(-rect.getWidth() / 2, -rect.getHeight() / 2, rect.getWidth(), rect.getHeight());
// 恢复原始状态
        gc.restore();
    }
    public static void main(String[] args) {
        launch(args);
    }
}