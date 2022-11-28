package util;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;

public interface IFrame {
    public Pane pane = new Pane();
    public Scene scene = new Scene(pane,500,500);

    void SetAndInitialize();
    void InitializeController();
}
