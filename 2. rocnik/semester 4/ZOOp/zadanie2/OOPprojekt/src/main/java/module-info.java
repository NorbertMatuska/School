module com.example.oopprojekt {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.controller to javafx.fxml;
    exports com.example.controller;

    exports view;
    opens view to javafx.fxml;
}