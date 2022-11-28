package sample.Location;

import org.jetbrains.annotations.Contract;

public interface Stock {

    default double StockLimit(int a, int b){
        return (int ) a + b;
    }

    default double StockLimitVrat(int a, int b){
        return (int ) a - b;
    }



    public static String skladVypis(){

        return  "";
    }






}
