package obchod;

import java.util.List;

public class Predavac extends Clovek {
	
	private List<Integer> vyrobkyNaPredaj;
	private Zakaznik zakaznik;
	public Predavac(String meno, String email) {											//Konštruktor
		super(meno,email);
	}
	
	public void vylozenieVyrobkov(List<Integer> naskladneneVyrobky, Zakaznik zakaznik) {	//Ako keby vyloženie vyrobkov na pult
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
