package sample.Location;

public class ForestStock implements Stock {
    private static int oak;
    private static int birch;
    private static int spruce;
    public static int getOak() { return ForestStock.oak; }
    public static void setOak(int count) { ForestStock.oak = ForestStock.oak + count; }
    public static int getBirch() { return ForestStock.birch ; }
    public static void setBirch(int count) { ForestStock.birch = ForestStock.birch + count; }
    public static int getSpruce() { return ForestStock.spruce ; }
    public static void setSpruce(int count) { ForestStock.spruce = ForestStock.spruce + count; }


    /***
     *
     * @return
     */
    public static String skladVypis(){

        return  (("Material na Sklade v Lese: \n Oak: " + oak    + "/2000 \n Birch:  " + birch  + "/2000 \n Spruce: " + spruce + "/2000 \n \n"));

    }




}
