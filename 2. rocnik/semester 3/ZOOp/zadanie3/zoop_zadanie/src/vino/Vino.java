package vino;
import java.util.ArrayList;
import java.util.Random;
import osoby.Zamestnanec;
import osoby.Zberac;
import osoby.ObsluhaMlynceku;

public abstract class Vino implements IVyroba {
	private int hmotnost = 0;
	private double objem;
	private double spracovane;
	private ArrayList <Zamestnanec> zamestnanci;
	protected String nazov;
	
	public Vino () {
		zamestnanci = new ArrayList<Zamestnanec>();
	}
	
	public Vino (int m) {
		this();																		//Overload
		hmotnost = m;
	}
	
	public void pridatZamestnanca(Zamestnanec Z)  {
		zamestnanci.add(Z);
	}
	
	public void pridatZamestnanca()  {
		Random rng = new Random();
		zamestnanci.add(new Zberac("-",rng.nextInt(100),rng.nextDouble()+1));       //Overload
	}
	
	public abstract void zrenie();
	
	public void zber() {
		int vykonnost = 0;
		
		for (Zamestnanec pom:zamestnanci) {
			if (pom instanceof Zberac) {
				Zberac zb = (Zberac) pom;
				vykonnost += zb.returnPozbieraneOvocie();
			}
		}
		if (hmotnost > 0 ) { 
			
			if (vykonnost > 0) {
				double pocethodin = hmotnost / vykonnost;
				System.out.println("Doba zberu hrozna "+nazov+":"+pocethodin+".");
			}
			else {
				System.out.println("Nedostatok zamestnancov na zber vina"+nazov+".");
			}
		}
		
	}

	@Override
	public void mletie() {
		int vykonnost = 0;
		
		for (Zamestnanec pom:zamestnanci) {
			if (pom instanceof ObsluhaMlynceku) {
				ObsluhaMlynceku zb = (ObsluhaMlynceku) pom;
				vykonnost += zb.returnLitre();
			}
		}
		if (objem > 0) { 
			if (vykonnost > 0) {
				hmotnost = 0;
				double pocethodin = objem / vykonnost;
				System.out.println("Doba pomletia hrozna "+nazov+":"+pocethodin+".");
				zrenie();
				System.out.println("--------------------------------------");
				spracovane = objem;
				objem = 0;
			}
			else {
				System.out.println("Nedostatok zamestnancov na pomletie vina "+nazov+".");
			}
			
		}
		
		
	}
	public int gethmotnost() {
		return this.hmotnost;
	}
	public void sethmotnost(int n) {
		hmotnost = n;
	}
	public void setobjem(double l) {
		objem = l;
	}
	public void setobjem(int l) {    //overload
		objem = l;
	}
	public double getobjem() {
		return this.objem;
	}
	public void setspracovane(double l) {
		spracovane = l;
	}
	public double getspracovane() {
		return this.spracovane;
	}
}
