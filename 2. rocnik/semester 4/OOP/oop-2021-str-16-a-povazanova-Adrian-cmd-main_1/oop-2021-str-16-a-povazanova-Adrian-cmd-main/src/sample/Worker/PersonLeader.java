package sample.Worker;

public abstract class PersonLeader extends Peasant {

    public int NumberPeasant;
    private double Bonus;


    public double getBonus() {

        if (NumberPeasant<6 && NumberPeasant>0)
        {Bonus=(30-NumberPeasant*5)/100;

            return Bonus;
        }
        else
            Bonus=0;

        return Bonus;

    }
}
