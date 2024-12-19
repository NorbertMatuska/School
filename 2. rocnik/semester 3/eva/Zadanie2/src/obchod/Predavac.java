package obchod;

import java.util.List;

public class Predavac extends Clovek {
	
	private List<Integer> vyrobkyNaPredaj;
	private Zakaznik zakaznik;
	public Predavac(String meno, String email) {											//Kon�truktor
		super(meno,email);
	}
	
	public void vylozenieVyrobkov(List<Integer> naskladneneVyrobky, Zakaznik zakaznik) {	//Ako keby vylo�enie vyrobkov na pult
		this.vyrobkyNaPredaj = naskladneneVyrobky;
		this.zakaznik = zakaznik;
	}
	
	public void notifikujZakaznika() {														//Funkcia na notifikovanie zakaznika
		zakaznik.notifikovat();
	}
	
	public void predaj() {											//Funkcia na predaj vyrobkov zakaznikovi
		
		if(zakaznik.jeNaPredajni()) {
			
			zakaznik.kup(this.vyrobkyNaPredaj);						//zavolana funkcia od zakaznika aby vyrobky kupil
			
		}else {
			zakaznik.notifikovat();
		}
	}
}
