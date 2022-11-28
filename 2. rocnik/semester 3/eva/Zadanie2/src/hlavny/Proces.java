package hlavny;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import obchod.Predajna;
import obchod.Predavac;
import obchod.Veduci;
import obchod.Zakaznik;
import produkty.Kefky;
import produkty.Nite;
import produkty.Ostatne;
import produkty.Ponuka;
import produkty.Pasty;
import produkty.Tovar;
import firma.Vyrobca;
import firma.Kontrolor_kvality;

public class Proces {
	public static void main(String[] args) {
		
		//Toto je mimo while, pretoze nepotrebujeme aby sa to inicializovalo po kazdom spusteni
		Ponuka ponuka = new Ponuka();
		ponuka.vytvorProdukty();													//Zadefinovanie a vytvorenie produktov v triede Ponuka
		
		String menoZ ;
		String emailZ;
		
		Veduci veduci = new Veduci("Servác", "veduci@gmail.com");					//Vytvorenie konkretneho vedúceho
		
		Vyrobca vyrobca = new Vyrobca("Agata", "vyrobca@gmal.com");					//Vytvorenie konkretneho vyrobcu
		
		Kontrolor_kvality kontrolor = new Kontrolor_kvality("Kontrolor", "a@b.com");//Vytvorenie konkretneho kontrolora kvality
		
		Predajna predajna = new Predajna("Predajna", "a@b.com");					//Vytvorenie konkretnej predajne
		
		Predavac predavac = new Predavac("Predavac", "x@v.com");					//Vytvorenie konkretneho predavaca
		
		//Toto je vo while, pretoze potrebujeme aby sa to inicializovalo po kazdom spusteni
		while(true) {
			System.out.println("Vitajte");
			System.out.println("----1. Vypis ponuky:----");		
			ponuka.zobrazProdukty();												//Funkcia, ktoru volame z Ponuky aby sa nam vypisali vsetky produkty
			
			
			System.out.println("\n----2a. Prihlasenie zakaznika----");				
			System.out.print("Zadaj meno: ");
			Scanner vstup = new Scanner(System.in);									//Pozadujeme vstup od pouzivatela
			menoZ= vstup.nextLine();												//Funkcia aby nas to hodilo na novy riadok
			
			System.out.print("Zadaj email: ");
			Scanner vstup1 = new Scanner(System.in);								
			emailZ= vstup1.nextLine();
			
			Zakaznik zakaznik = new Zakaznik(menoZ, emailZ);						//Vytvorenie konkretneho zakaznika, toho potrebujeme
																					//vytvorit po kazdom sputeni
			
			System.out.println("----2b. Vyber z ponuky----");		
			zakaznik.objednaj();													//Funkcia, ktoru volame od Zakaznika
			
			System.out.println("\n----3. Objednavka od veduceho----");		
			veduci.objednajZFirmy(zakaznik.vratKosik());
			
			System.out.println("\n----4. Firma vyrobí----");
			vyrobca.vyrobnyProces(veduci.vratObjednavku());
			
			System.out.println("\n----5. Kontrola vyrobkov----");
			kontrolor.kontrolnyProces(vyrobca.vratVyrobky());
			
			System.out.println("\n----5. Dorucene vyrobky do predajne----");
			predajna.dorucovaciProces(kontrolor.vratOvereneVyrobky());
			
			System.out.println("\n----6. Priprava a predaj vyrobkov----");
			predavac.vylozenieVyrobkov(predajna.vratDoruceneVyrobky(), zakaznik);		
			predavac.notifikujZakaznika();
			
			System.out.println("\n----7/8. Predaj/Nakup----");		
			predavac.predaj();
			
			System.out.println("\n----Ukoncenie objednavky----\n");
			System.out.println("Ak chcete ukoncit aplikaciu, tak stlacte \"q\", ak chcete pokracovat, stlacte enter.");
			Scanner vstup2 = new Scanner(System.in);
			String volba = vstup2.nextLine();
			
			zakaznik = null;
			
			if(volba.contentEquals("q")) {
				System.out.println("Koniec aplikacie");
				break;
			}
			System.out.println("----------------------------------------------------\n");
			
		
		}
	}	
	
}

