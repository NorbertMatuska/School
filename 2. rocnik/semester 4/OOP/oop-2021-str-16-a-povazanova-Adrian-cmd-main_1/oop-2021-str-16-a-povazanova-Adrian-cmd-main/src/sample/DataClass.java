package sample;

import sample.Produkt.Produkt;
import sample.Worker.BigBoss;
import sample.Worker.*;

import java.util.ArrayList;

public class DataClass {

    ArrayList<WoodCutter> drevorubaci = new ArrayList<>();
    ArrayList<BigBoss> bosik = new ArrayList<>();
    ArrayList<WoodPilcik> pilcici = new ArrayList<>();
    ArrayList<WoodMonter> monter = new ArrayList<>();
    ArrayList<Produkt>  stvol = new ArrayList<>();
    ArrayList<Produkt>  stolicka = new ArrayList<>();
    ArrayList<Produkt>  postel = new ArrayList<>();

    public DataClass(ArrayList<WoodCutter> drevorubaci,ArrayList<WoodPilcik> pilcici,ArrayList<BigBoss> bosik, ArrayList<WoodMonter> monter,ArrayList<Produkt>  stvol,ArrayList<Produkt>  stolicka,ArrayList<Produkt>  postel) {
        this.drevorubaci = drevorubaci;
        this.pilcici = pilcici;
        this.bosik = bosik;
        this.monter = monter;
        this.stvol = stvol;
        this.stolicka = stolicka;
        this.postel = postel;
    }


    public ArrayList<WoodCutter> getDrevorubaci() {
        return drevorubaci;
    }
    public void setDrevorubaci(ArrayList<WoodCutter> drevorubaci) {
        this.drevorubaci = drevorubaci;
    }



    public ArrayList<WoodPilcik> getPilcici() {
        return pilcici;
    }
    public void setPilcici(ArrayList<WoodPilcik> pilcici) {
        this.pilcici = pilcici;
    }



    public void setBosik(ArrayList<BigBoss> bosik) {
        this.bosik=bosik;
    }

    public ArrayList<BigBoss> getBosik() {
        return bosik;
    }


    public ArrayList<WoodMonter> getMonter() {
        return monter;
    }

    public void setMonter(ArrayList<WoodMonter> monter) {
        this.monter = monter;
    }



    public ArrayList<Produkt> getStvol() {
        return stvol;
    }

    public void setStvol(ArrayList<Produkt> stvol) {
        this.stvol = stvol;
    }

    public ArrayList<Produkt> getStolicka() {
        return stolicka;
    }

    public void setStolicka(ArrayList<Produkt> stolicka) {
        this.stolicka = stolicka;
    }

    public ArrayList<Produkt> getPostel() {
        return postel;
    }

    public void setPostel(ArrayList<Produkt> postel) {
        this.postel = postel;
    }
}
