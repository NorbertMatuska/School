package sample.Worker;

import sample.Location.DielnaStock;
import sample.Location.ForestStock;

public class WoodMonter extends Peasant{


    /***
     *
     * @param wood
     * @param nabytok
     */
    public void Pracuj(String wood, String nabytok){

        switch (nabytok) {
            case "Postel":
            {

                switch (wood){

                    case "Oak":
                        DielnaStock.setOak(-200);
                        //Postel++

                        break;


                    case "Birch":

                        DielnaStock.setBirch(-200);
                        break;


                    case "Spruce":

                        DielnaStock.setSpruce(-200);
                        break;


                    default:
                }
                break;
            }

            case "Stolicka":

            {

                switch (wood){

                    case "Oak":
                        DielnaStock.setOak(-50);
                        //Postel++

                        break;


                    case "Birch":

                        DielnaStock.setBirch(-50);
                        break;


                    case "Spruce":

                        DielnaStock.setSpruce(-50);
                        break;


                    default:
                }
                break;
            }

            case "Stol":

            {

                switch (wood){

                    case "Oak":
                        DielnaStock.setOak(-150);
                        //Postel++

                        break;


                    case "Birch":

                        DielnaStock.setBirch(-150);
                        break;


                    case "Spruce":

                        DielnaStock.setSpruce(-150);
                        break;


                    default:
                }
                break;
            }

            default:
        }


    }

}
