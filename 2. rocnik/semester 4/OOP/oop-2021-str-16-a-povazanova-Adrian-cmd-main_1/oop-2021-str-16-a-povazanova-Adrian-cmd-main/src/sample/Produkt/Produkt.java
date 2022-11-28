package sample.Produkt;

import java.awt.*;

public class Produkt extends Vec{
    private int Full;
    private String Druh;
    public int getFull() {
        return Full;
    }

    public void setFull() {

        Full = getOak()+getBirch()+getSpruce();
    }

    public String getDruh() {
        return Druh;
    }

    public void setDruh(String druh) {
        Druh = druh;
    }
}
