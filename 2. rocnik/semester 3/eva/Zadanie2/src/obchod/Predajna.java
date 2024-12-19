package obchod;
import java.util.List;

public class Predajna {
	
		private String nazov;
		private String adresa;
		
		private List<Integer> dorucene_vyrobky;							
		
		public Predajna (String nazov, String adresa) {					//Konötruktor
			this.nazov = nazov;
			this.adresa = adresa;
			
		}
		
		public void dorucovaciProces(List<Integer> prijateVyrobky) {	//Tu sa prijmu vyrobky
			System.out.print("Prijate vyrobky: ");
			
			for(int i=0; i<prijateVyrobky.size(); i++) {				//Funkcia na vypisanie prijatych vyrobkov
			System.out.print(prijateVyrobky.get(i).toString() + " ");	
			}
			
			this.dorucene_vyrobky=prijateVyrobky;
		}
		
		public List<Integer> vratDoruceneVyrobky(){						//Funkcia, aby sme mohli zoznam overenych vyrobkov odoslaù 
			return this.dorucene_vyrobky;								//Ôalej Predavacovi
		}

}
