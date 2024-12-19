module oop.oop {
    requires javafx.controls;
    requires javafx.fxml;


    opens oop.view to javafx.fxml;
    exports oop.view;
}