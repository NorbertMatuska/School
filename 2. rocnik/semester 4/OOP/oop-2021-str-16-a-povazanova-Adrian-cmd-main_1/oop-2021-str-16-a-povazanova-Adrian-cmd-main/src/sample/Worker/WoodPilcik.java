package sample.Worker;

import sample.Location.DielnaStock;
import sample.Location.ForestStock;

import java.io.Serializable;

public class WoodPilcik extends Peasant  {


    /***
     *
     * @param count
     * @param wood
     */
   public void Pracuj(int count, String wood) {

        switch (wood) {
            case "Oak":

                ForestStock.setOak(-count) ;
                DielnaStock.setOak(count);
                break;

            case "Birch":

                ForestStock.setBirch(-count);
                DielnaStock.setBirch(count);
                break;

            case "Spruce":

                ForestStock.setSpruce(-count);
                DielnaStock.setSpruce(count);
                break;


            default:
        }
    }



}