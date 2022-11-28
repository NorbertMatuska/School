package vino;
import java.util.ArrayList;
import osoby.Zamestnanec;

public class Vinaren {
	private Frankovka fr;
	private Konkordia ko;
	private Ribezle ri;
	public static Vinaren vin;
	private final double cenaFr = 9.99;
	private final double cenaKo = 11.99;
	private final double cenaRi = 7.39;
	private ArrayList <IVyroba> vyroba;
	
	private Vinaren () {
		fr = new Frankovka();				//kompozicia
		ko = new Konkordia();
		ri = new Ribezle();
		vyroba = new ArrayList<IVyroba>();
		vyroba.add(fr);
		vyroba.add(ko);
		vyroba.add(ri);
	}
	
	public void pridajZCKo(Zamestnanec z) {
		ko.pridatZamestnanca(z);
	}
	public void pridajZCFr(Zamestnanec z) {
		fr.pridatZamestnanca(z);
	}
	public void pridajZCRi(Zamestnanec z) {
		ri.pridatZamestnanca(z);
	}
	public static Vinaren getVinaren() {
		if (vin == null) {
			vin = new Vinaren();			//singleton
		}
		return vin; 
	}
	public void pridajHmotnostfr(int m) {
		fr.sethmotnost(m+fr.gethmotnost());
	}
	public int getHmotnostfr() {
		return fr.gethmotnost();
	}
	public void pridajHmotnostko(int m) {
		ko.sethmotnost(m+ko.gethmotnost());
	}
	public int getHmotnostko() {
		return ko.gethmotnost();
	}
	public void pridajHmotnostri(int m) {
		ri.sethmotnost(m+ri.gethmotnost());
	}
	public int getHmotnostri() {
		return ri.gethmotnost();
	}
	public final double celkovaCena() {
		double cena = 0;
		cena = fr.getspracovane() * cenaFr;
		cena += ko.getspracovane() * cenaKo;
		cena += ri.getspracovane() * cenaRi;
		return cena;
	}
	
	public void spracuj() {
		for (IVyroba pom:vyroba) {
			pom.zber();
			pom.mletie();
		}
	} 
	public double predajHrozno(double mnozstvo, int typ) {
		double predajnaCena = 0;
		switch(typ) {
		case 1:
			if (fr.getspracovane() - mnozstvo >= 0) {
				fr.setspracovane(fr.getspracovane() - mnozstvo);
				predajnaCena = mnozstvo * cenaFr;
			}
			else {
				predajnaCena = -1;
			}
			break;
		case 2:
			if (ko.getspracovane() - mnozstvo >= 0) {
				ko.setspracovane(ko.getspracovane() - mnozstvo);
				predajnaCena = mnozstvo * cenaKo;
			}
			else {
				predajnaCena = -1;
			}
			break;
		case 3:
			if (ri.getspracovane() - mnozstvo >= 0) {
				ri.setspracovane(ri.getspracovane() - mnozstvo);
				predajnaCena = mnozstvo * cenaRi;
			}
			else {
				predajnaCena = -1;
			}
			break;
			
		}
		return predajnaCena;
	}
	public double cenaLiterFr() {
		return cenaFr;
	} 
	public double cenaLiterKo() {
		return cenaKo;
	} 
	public double cenaLiterRi() {
		return cenaRi;
	} 
	public double getSpracovaneFr() {
		return fr.getspracovane();
	}
	public double getSpracovaneKo() {
		return ko.getspracovane();
	}
	public double getSpracovaneRi() {
		return ri.getspracovane();
	}
}
