module com.example.demo {
    requires javafx.controls;
    requires javafx.fxml;

    exports com.example.demo;
    opens com.example.demo to javafx.fxml;

    exports com.example.demo.views;
    opens com.example.demo.views to javafx.fxml;

    exports com.example.demo.models;
    opens com.example.demo.models to javafx.fxml;

    exports com.example.demo.controllers;
    opens com.example.demo.controllers to javafx.fxml;

    exports com.example.demo.router;
    opens com.example.demo.router to javafx.fxml;

    exports com.example.demo.services;
    opens com.example.demo.services to javafx.fxml;
}