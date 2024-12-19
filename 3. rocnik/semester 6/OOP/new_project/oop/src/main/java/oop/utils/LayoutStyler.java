package oop.utils;

import javafx.scene.Node;

/**
 * The LayoutStyler class provides methods for setting layout properties of nodes in JavaFX applications.
 */
public class LayoutStyler {
    /**
     * Sets layout properties of a node within an application.
     *
     * @param application The application view.
     * @param node        The node to set layout for.
     * @param posx        The X-coordinate position.
     * @param posy        The Y-coordinate position.
     * @param visible     Whether the node is visible.
     */
    public static void SetLayout(IFrame application, Node node, int posx, int posy, boolean visible) {
        node.setLayoutX(posx);
        node.setLayoutY(posy);
        node.setVisible(visible);
        application.pane.getChildren().add(node);
    }

    /**
     * Overloaded method to set layout properties of a node within an application with width and height.
     *
     * @param application The application view.
     * @param node        The node to set layout for.
     * @param posx        The X-coordinate position.
     * @param posy        The Y-coordinate position.
     * @param width       The width of the node.
     * @param height      The height of the node.
     * @param visible     Whether the node is visible.
     */
    public static void SetLayout(IFrame application, Node node, int posx, int posy, int width, int height, boolean visible) {
        node.minWidth(width);
        node.minHeight(height);
        node.setLayoutX(posx);
        node.setLayoutY(posy);
        node.setVisible(visible);
        application.pane.getChildren().add(node);
    }
}
