package sample.router;
import sample.DataClass;
import sample.Worker.Person;
import sample.viewsworkers.*;
import sample.montujem.*;

import javafx.stage.Stage;
import sample.views.*;
import sample.woodvyber.*;
import java.io.IOException;
import java.util.ArrayList;

public class Router {

    public static Stage window;

    /***
     *
     * @param route
     * @param Data
     * @throws IOException
     * @throws ClassNotFoundException
     */
    public static void goTo(ROUTES route, DataClass Data) throws IOException, ClassNotFoundException {
        View view = null;
        if (route == ROUTES.SHOP){

            view = new SHOP(window,Data);


        }

        if (route == ROUTES.LOGIN){

            view = new LoginView(window,Data);
        }

        if (route == ROUTES.LESWORKEROAK){

            view = new LesWorkerOak(window,Data);

        }

        if (route == ROUTES.LESWORKERBIRCH){

            view = new LesWorkerBirch(window,Data);
        }

        if (route == ROUTES.LESWORKERSPRUCE){

            view = new LesWorkerSpruce(window,Data);
        }

        if (route == ROUTES.DIELNAWORKEROAK){

            view = new DielnaWorkerOak(window,Data);

        }

        if (route == ROUTES.DIELNAWORKERBIRCH){

            view = new DielnaWorkerBirch(window,Data);
        }

        if (route == ROUTES.DIELNAWORKERSPRUCE){

            view = new DielnaWorkerSpruce(window,Data);
        }
////
        if (route == ROUTES.MONTERNAWORKERSTVOL){

            view = new MonternaWorkerStvol(window,Data);

        }

        if (route == ROUTES.MONTERNAWORKERSTOLICKA){

            view = new MonternaWorkerStolicka(window,Data);
        }

        if (route == ROUTES.MONTERNAWORKERPOSTEL){

            view = new MonternaWorkerPostel(window,Data);
        }

    /*    if (route == ROUTES.LESWORKER){

            view = new LesWorkerOak(window);
        }

*/
        if(route == ROUTES.LES){

            view = new Les(window,Data);
        }
        if(route == ROUTES.MONTERNA){

            view = new Monterna(window,Data);
        }


        if(route == ROUTES.WELCOME){

            view = new Welcome(window,Data);
        }

        if(route == ROUTES.DIELNA){

            view = new Dielna(window,Data);
        }

        if(route == ROUTES.SKLAD){

            view = new Sklad(window,Data);

        }









       if (view !=null) view.render() ;


    }

    public static void goTo(ROUTES route, DataClass Data, String wood) throws IOException, ClassNotFoundException
    {
        View view = null;


        if (route == ROUTES.STOLICKAMONTER){

            view = new MontujemStolicku(window,Data,wood);
        }


        if (route == ROUTES.STVOLMONTER){

            view = new MontujemStvol(window,Data,wood);
        }

        if (route == ROUTES.POSTELMONTER){

            view = new MontujemPostel(window,Data,wood);
        }



        if (view !=null) view.render() ;
    }

    public static void goTo(ROUTES route,  String nabytok ,DataClass Data) throws IOException, ClassNotFoundException
    {
        View view = null;




        if(route == ROUTES.VYBERWOOD){

            view = new VyberWood(window, nabytok ,Data);

        }



        if (view !=null) view.render() ;
    }

    }
