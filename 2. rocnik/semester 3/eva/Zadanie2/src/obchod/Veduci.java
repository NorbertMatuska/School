package obchod;

import java.util.List;

public class Veduci extends Predavac {									
	
	private List<Integer> objednavka;
	public Veduci(String meno, String email) {								//Kon�truktor		
		super(meno, email);
	}
	
	public void objednajZFirmy(List<Integer> kosik) {						//Tu sa objednaju vyrobky
		System.out.print("Zaslana objednavka pre vyrobky s ID: [");
		
		for(int i=0; i<kosik.size(); i++) {									//Pomocou cyklu vypi�eme v�etky vyrobky, ktore sa maju objedna�
		System.out.print(kosik.get(i).toString() + " ");
		}
		
		System.out.println("]");
		this.objednavka=kosik;
	}
	
	public List<Integer> vratObjednavku(){									//Funkcia, aby sme mohli objednane vyrobky odosla� �alej
		return this.objednavka;												//Firme
	}
	
	public void predaj() {													//Viacnssobne dedenie
		System.out.println("Predane veducim");
	}
	
	
}
