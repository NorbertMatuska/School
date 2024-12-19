package util;

import javafx.scene.Node;
import util.IFrame;

public class LayoutStyler {
    public static void SetLayout(IFrame application, Node node, int pozx, int pozy, boolean visible) {
        node.setLayoutX(pozx);
        node.setLayoutY(pozy);
        node.setVisible(visible);
        application.pane.getChildren().add(node);
    }
    //Overload alebo override idk
    public static void SetLayout(IFrame application, Node node, int pozx, int pozy, int width, int height, boolean visible) {
        node.minWidth(width);
        node.minHeight(height);
        node.setLayoutX(pozx);
        node.setLayoutY(pozy);
        node.setVisible(visible);
        application.pane.getChildren().add(node);
    }
}
