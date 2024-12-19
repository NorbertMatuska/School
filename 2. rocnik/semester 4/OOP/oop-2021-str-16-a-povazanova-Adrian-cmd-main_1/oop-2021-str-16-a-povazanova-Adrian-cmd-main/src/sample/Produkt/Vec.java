package sample.Produkt;

public  abstract class Vec {

    private int Oak;
    private int Birch;
    private int Spruce;

    public int getOak() {
        return Oak;
    }

    public void setOak() {
        Oak = Oak+1;
    }

    public int getBirch() {
        return Birch;
    }

    public void setBirch() {
        Birch = Birch+1;
    }

    public int getSpruce() {
        return Spruce;
    }

    public void setSpruce() {
        Spruce = Spruce+1;
    }
}
