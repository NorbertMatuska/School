package firma;

import obchod.Clovek;
import java.util.List;

public class Vyrobca extends Clovek {
	
	private List<Integer> vyrobky;
	
	public Vyrobca (String meno, String email) {					//Konötruktor
		super(meno, email);
	}
	
	public void vyrobnyProces(List<Integer> objednavka) {			//Funkcia na vyorbu vyrobkov
		System.out.print("Vyrobene vyrobky s ID: [");
		
		for(int i=0; i<objednavka.size(); i++) {
		System.out.print(objednavka.get(i).toString() + " ");		//Cyklus na vypisanie vyrobenych vyrobkov
		}
		
		System.out.println("]");
		this.vyrobky=objednavka;
	}
	
	public List<Integer> vratVyrobky(){								//Funkcia aby sme mohli zoznam vyrobenych vyrobkov odolsaù kontolerovi
		return this.vyrobky;
	}
	
	
}
