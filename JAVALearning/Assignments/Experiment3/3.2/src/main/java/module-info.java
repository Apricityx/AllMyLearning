module org.example.javafxdemo {
    requires javafx.controls;
    requires javafx.fxml;


    opens oop.task.exp.e03.kg to javafx.fxml;
    exports oop.task.exp.e03.kg;
}