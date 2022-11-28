package com.example.demo.router;

import com.example.demo.views.HomeView;
import com.example.demo.views.LoginView;
import com.example.demo.views.View;
import javafx.stage.Stage;

public class Router {
    public static Stage window;

    public static void goTo(ROUTES route) {
        View view = null;
        if(route == ROUTES.LOGIN) {
            view = new LoginView(window);
        }
        if(route == ROUTES.HOME) {
            view = new HomeView(window);
        }
        if(view != null){
            view.render();
        }
    }
}
