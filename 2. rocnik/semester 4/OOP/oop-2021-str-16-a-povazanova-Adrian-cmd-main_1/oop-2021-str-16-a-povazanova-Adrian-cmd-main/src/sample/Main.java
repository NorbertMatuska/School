package sample;

import sample.Location.DielnaStock;
import sample.Location.MonternaStock;
import sample.Produkt.Produkt;
import sample.Worker.*;
import javafx.application.Application;
import javafx.stage.Stage;
import sample.Location.ForestStock;
import sample.router.ROUTES;
import sample.router.Router;


import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.ArrayList;



public class Main extends Application {

    DataClass Data = new DataClass(null,null,null,null,null,null,null);





    public static  void ArrayPridaj (ArrayList<String> pointer , String data){

        pointer.add(data);

    }


    @Override
    public void start(Stage primaryStage) throws IOException, ClassNotFoundException {
    ArrayList<WoodCutter> wc = new ArrayList<>();

    ArrayList<WoodPilcik> wp = new ArrayList<>();

    ArrayList<BigBoss> Boss = new ArrayList<>();

    ArrayList<WoodMonter> wmo = new ArrayList<>();

    ArrayList<Produkt>  postelka = new ArrayList<>();

    ArrayList<Produkt> stolcek  = new ArrayList<>();

    ArrayList<Produkt> stolicka = new ArrayList<>();

        int i=0;


        Produkt jedna = new Produkt();

        Produkt dva = new Produkt();

        Produkt tri = new Produkt();


       jedna.setDruh("Postele");
       postelka.add(jedna);


        dva.setDruh("Stoly");
        stolcek.add(dva);


        tri.setDruh("Stolicky");
        stolicka.add(tri);



        WoodCutter w = new WoodCutter();

        w.setName("Jozko") ;
        w.setPovolanie("Drevorubač");
        w.setSurname("Hrasko");
        w.setID(i+2 );
        wc.add(w);
        i++;

        WoodCutter s = new WoodCutter();
        s.setName("Jozef") ;
        s.setPovolanie("Drevorubač");
        s.setSurname("Hrach");
        s.setID(i+2 );
        wc.add(s);

        i++;

            WoodCutter a = new WoodCutter();
        a.setName("Juraj") ;
        a.setPovolanie("Drevorubač");
        a.setSurname("Mak");
        a.setID(i+2 );
        wc.add(a);

        i++;

            WoodCutter b = new WoodCutter();
        b.setName("Jano") ;
        b.setPovolanie("Drevorubač");
        b.setSurname("zemiak");
        b.setID(i+2 );
        wc.add(b);

        i++;

            WoodCutter x = new WoodCutter();
        x.setName("Karol") ;
        x.setPovolanie("Drevorubač");
        x.setSurname("Hurka");
        x.setID(i+2 );
        wc.add(x);
    i++;


        int j=0;

        WoodPilcik wa = new WoodPilcik();

        wa.setName("Jozko") ;
        wa.setPovolanie("pilcik");
        wa.setSurname("Hrasko");
        wa.setID(j+2 );
        wp.add(wa);
        j++;

        WoodPilcik wb = new WoodPilcik();
        wb.setName("Jozef") ;
        wb.setPovolanie("pilcik");
        wb.setSurname("Hrach");
        wb.setID(j+2 );
        wp.add(wb);

        j++;

        WoodPilcik wcc = new WoodPilcik();
        wcc.setName("Juraj") ;
        wcc.setPovolanie("pilcik");
        wcc.setSurname("Mak");
        wcc.setID(j+2 );
        wp.add(wcc);

        j++;

        WoodPilcik wd = new WoodPilcik();
        wd.setName("Jano") ;
        wd.setPovolanie("pilcik");
        wd.setSurname("zemiak");
        wd.setID(j+2 );
        wp.add(wd);

        j++;

        WoodPilcik we = new WoodPilcik();
        we.setName("Karol") ;
        we.setPovolanie("pilcik");
        we.setSurname("Hurka");
        we.setID(j+2 );
        wp.add(we);
        j++;


        int k =0;

        WoodMonter pu = new WoodMonter();

        pu.setName("Jozko") ;
        pu.setPovolanie("Monter");
        pu.setSurname("Hrasko");
        pu.setID(k+2 );
        wmo.add(pu);
        k++;

        WoodMonter pi = new WoodMonter();
        pi.setName("Jozef") ;
        pi.setPovolanie("Monter");
        pi.setSurname("Hrach");
        pi.setID(k+2 );
        wmo.add(pi);

        k++;


        WoodMonter po = new WoodMonter();
        po.setName("Karol") ;
        po.setPovolanie("Monter");
        po.setSurname("Hurka");
        po.setID(k+2 );
        wmo.add(po);
        k++;
///////////////
        DielnaStock.setOak(500);
        DielnaStock.setSpruce(500);
        DielnaStock.setBirch(500);

        ForestStock.setSpruce(1800);

        ForestStock.setBirch(1800);
        ForestStock.setOak(1800);


        BigBoss boss = new BigBoss();
        FirmaMaster FiM = new FirmaMaster();
        ForestMaster FoM = new ForestMaster();


        boss.setName("Big");
        boss.setSurname("Boss");
        boss.setPovolanie("Šef");
        boss.setID(100);
        Boss.add(boss);



        FiM.setName("Firma");
        FiM.setSurname("Master");
        FiM.setID(2);

        FoM.setName("Forest");
        FoM.setSurname("Master");
        FoM.setID(3);









        FiM.Vypis();
        FoM.Vypis();




        Data.setStolicka(stolicka);
        Data.setStvol(stolcek);
        Data.setPostel(postelka);
        Data.setMonter(wmo);
        Data.setBosik(Boss);
        Data.setPilcici(wp);
        Data.setDrevorubaci(wc);


        Router.window = primaryStage;



        Router.goTo(ROUTES.WELCOME,Data);



    }




    public static void main(String[] args) throws ClassNotFoundException, IOException {







        launch(args);


    }




}
