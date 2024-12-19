package com.example.demo.views;

import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public abstract class View {
    protected Stage window;
    protected Scene scene;
    protected GridPane gp;
    public abstract void render();
}
