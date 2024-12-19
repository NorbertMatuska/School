package view;

import javafx.application.Application;
import javafx.stage.Stage;
import util.IFrame;

public class NewWindow extends Application implements IFrame {

    public Stage PageStage = null;

    @Override
    public void start(Stage primaryStage) throws Exception {
        try {
            PageStage = primaryStage;
            //scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
            PageStage.setScene(scene);
            SetAndInitialize();
            InitializeController();
            PageStage.show();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void SetAndInitialize() {

    }

    @Override
    public void InitializeController() {

    }
}
