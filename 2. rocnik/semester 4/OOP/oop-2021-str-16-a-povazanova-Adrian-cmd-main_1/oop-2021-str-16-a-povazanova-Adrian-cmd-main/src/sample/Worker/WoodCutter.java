package sample.Worker;

import sample.Location.ForestStock;

import java.io.Serializable;


public class WoodCutter extends Peasant  {


    /***
     *
     * @param count
     * @param wood
     */
    public void Pracuj(int count, String wood) {

        switch (wood) {
            case "Oak":

                ForestStock.setOak(count) ;



                break;

            case "Birch":

             ForestStock.setBirch(count);

                break;

            case "Spruce":

                ForestStock.setSpruce(count);

                break;


            default:
        }
    }



}
