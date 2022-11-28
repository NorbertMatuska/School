package sample.Worker;

public abstract class Peasant extends Person implements Plat{


    int Peniaze;

    public int getPeniaze(){
        return Peniaze;
    }

    public void setPeniaze(int penaz)
    {
        Peniaze=Peniaze+penaz;
    }

    public void Pracuj() {
        System.out.println("pracujem");
    };
}
