package oop.utils;

import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import oop.controller.LoginController;
import oop.controller.VotingController;

/**
 * The IFrame interface defines methods for initializing the view.
 */
public interface IFrame {
    /**
     * The default pane for the view.
     */
    Pane pane = new Pane();
    /**
     * The default scene for the view.
     */
    Scene scene = new Scene(pane, 400, 400);

    /**
     * Sets up and initializes the view.
     */
    void SetAndInitialize();
    /**
     * Initializes the controller for the view.
     */
    default void InitializeController() {
        LoginController controller = new LoginController(this);
    };
}
