package obchod;

import java.util.List;

public class Veduci extends Predavac {									
	
	private List<Integer> objednavka;
	public Veduci(String meno, String email) {								//Konötruktor		
		super(meno, email);
	}
	
	public void objednajZFirmy(List<Integer> kosik) {						//Tu sa objednaju vyrobky
		System.out.print("Zaslana objednavka pre vyrobky s ID: [");
		
		for(int i=0; i<kosik.size(); i++) {									//Pomocou cyklu vypiöeme vöetky vyrobky, ktore sa maju objednaù
		System.out.print(kosik.get(i).toString() + " ");
		}
		
		System.out.println("]");
		this.objednavka=kosik;
	}
	
	public List<Integer> vratObjednavku(){									//Funkcia, aby sme mohli objednane vyrobky odoslaù Ôalej
		return this.objednavka;												//Firme
	}
	
	public void predaj() {													//Viacnssobne dedenie
		System.out.println("Predane veducim");
	}
	
	
}
