import java.awt.*;
import java.awt.event.*;

public class ThreeListener implements MouseMotionListener,
        MouseListener, WindowListener { //实现了三个接口
    private Frame f;
    private TextField tf;
    public static void main(String args[]) {
        ThreeListener two = new ThreeListener();
        two.go();
    }

    public void go() {
        f = new Frame("Three listeners example");
        f.add(new Label("Click and drag the mouse"), "North");
        tf = new TextField(30);
        f.add(tf, "South"); //使用缺省的布局管理器
        f.addMouseMotionListener(this); //注册监听器MouseMotionListener
        f.addMouseListener(this); //注册监听器MouseListener
        f.addWindowListener(this); //注册监听器WindowListener
        f.setSize(300, 200);
        f.setVisible(true);
    }

    public void mouseDragged(MouseEvent e) {
//实现mouseDragged方法
        String s = "Mouse dragging : X=" + e.getX() + "Y = " + e.getY();
        tf.setText(s);
    }

    public void mouseMoved(MouseEvent e) {}

//对其不感兴趣的方法可以方法体为空
    public void mouseClicked(MouseEvent e) {}

    public void mouseEntered(MouseEvent e) {
        String s = "The mouse entered";
        tf.setText(s);
    }

    public void mouseExited(MouseEvent e) {
        String s = "The mouse has left the building";
        tf.setText(s);
    }

    public void mousePressed(MouseEvent e) {}

    public void mouseReleased(MouseEvent e) {}

    public void windowClosing(WindowEvent e) {
//为了使窗口能正常关闭，程序正常退出，需要实现windowClosing方法

        System.exit(1);
    }

    public void windowOpened(WindowEvent e) {}

//对其不感兴趣的方法可以方法体为空
    public void windowIconified(WindowEvent e) {}

    public void windowDeiconified(WindowEvent e) {}

    public void windowClosed(WindowEvent e) {}

    public void windowActivated(WindowEvent e) {}

    public void windowDeactivated(WindowEvent e) {}
}