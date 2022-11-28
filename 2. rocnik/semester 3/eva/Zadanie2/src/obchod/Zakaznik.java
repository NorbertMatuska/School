package obchod;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import produkty.Kefky;

public class Zakaznik extends Clovek {
	
	private List<Integer> kosik= new ArrayList<>();
	private List<Integer> kupeneVyrobky;
	private boolean notifikacia = false;
	
	public Zakaznik(String meno, String email) {
		super(meno,email);
	}
	
	public void objednaj() {
		
		while(true) {
			System.out.println("Zadajte ID tovaru alebo stlacte \"q\" pre ukoncenie vyberu :)\n");
			
			Scanner vstup = new Scanner(System.in);
			
			String volba= vstup.nextLine();
			
			if(volba.contentEquals("q")) {
				
				break;
			}else {
				int ID = Integer.parseInt(volba);
				this.kosik.add(ID);
			}
		}
		
	}
	
	public void kup(List<Integer> nakup) {
		this.kupeneVyrobky = nakup;

		System.out.println("Kupene vyrobky");
		
		for(int i=0; i<kupeneVyrobky.size(); i++) {
			System.out.println("Vyrobok s ID: " + kupeneVyrobky.get(i).toString());
			}
		
		kosik.clear();
	}
	
	
	/*public void zobrazKosik() {
		for(int i=0; i<this.kosik.size();i++) {
			System.out.println(this.kosik.get(i));
		}
	}*/
	
	public List<Integer> vratKosik() {
		return this.kosik;
	}
	
	public void notifikovat() {
		this.notifikacia = true;
	}
	
	public boolean jeNaPredajni(){
		return this.notifikacia;
	}
	
	
	
}
