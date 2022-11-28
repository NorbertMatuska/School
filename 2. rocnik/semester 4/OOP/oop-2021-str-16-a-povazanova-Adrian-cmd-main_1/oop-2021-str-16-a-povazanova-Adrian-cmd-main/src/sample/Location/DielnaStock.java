package sample.Location;

public class DielnaStock  implements Stock{
    private static int oak;
    private static int birch;
    private static int spruce;
    public static int getOak() { return DielnaStock.oak; }
    public static void setOak(int count) {
        DielnaStock.oak = DielnaStock.oak + count;
    }
    public static int getBirch() { return DielnaStock.birch ; }
    public static void setBirch(int count) {
        DielnaStock.birch = DielnaStock.birch + count;
    }
    public static int getSpruce() { return DielnaStock.spruce; }
    public static void setSpruce(int count) { DielnaStock.spruce = DielnaStock.spruce + count; }


    /***
     *
     * @return
     */
    public static String skladVypis(){

        return  ("Material na sklade v Dielni : \n Oak: " + oak    + "/2000 \n Birch:  " + birch  + "/2000 \n Spruce: " + spruce + "/2000 \n \n");

    }

}


