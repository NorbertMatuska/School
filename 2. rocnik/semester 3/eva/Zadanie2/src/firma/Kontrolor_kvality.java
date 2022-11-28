package firma;
import java.util.List;
import obchod.Clovek;

public class Kontrolor_kvality extends Clovek{
	
	private List<Integer> overene_vyrobky;
		
		public Kontrolor_kvality (String meno, String email) {										//Konötruktor
			super(meno, email);
		}
		
		public void kontrolnyProces(List<Integer> vyrobkyNaKontrolu) {								//Tu sa overia vyrobky
			System.out.println("Kontrola vyrobkov: ");
			
			for(int i=0; i<vyrobkyNaKontrolu.size(); i++) {											//Prejde to cez cely cyklus a vypise
			System.out.println("Vyrobok s ID: " + vyrobkyNaKontrolu.get(i).toString() + " OK");		//ci su v poriadku(uplne overenie aû
			}																						//v 3 zadani
			
			this.overene_vyrobky=vyrobkyNaKontrolu;
		}
		
		public List<Integer> vratOvereneVyrobky(){							//Funkcia, aby sme mohli zoznam overenych vyrobkov odoslaù 
			return this.overene_vyrobky;									//Ôalej do predajne
		}
}
