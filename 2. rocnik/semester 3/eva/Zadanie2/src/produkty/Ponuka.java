package produkty;

import java.util.ArrayList;
import java.util.List;


public class Ponuka {
	private List<Kefky> zoznamKefky = new ArrayList<>();					//Inicializovanie zoznamov, do ktor˝ch budeme pridavat produkty
	private List<Nite>zoznamNite = new ArrayList<>();
	private List<Pasty>zoznamPasty = new ArrayList<>();
	private List<Ostatne>zoznamOstatne = new ArrayList<>();
	
	public Ponuka() {
		
	}
	
	public void vytvorProdukty() {
		Kefky kefka1= new Kefky(1, "Kefka","Tvrda");						//Vytvorenie konkrÈtnej kefky
		Kefky kefka2=new Kefky(2, "Kefka","Stredna");
		Kefky kefka3=new Kefky(3, "Kefka", "Makka");
		Kefky kefka4=new Kefky(4);
		
		
		zoznamKefky.add(kefka1);											//pridanie do zoznamu,  aby sme to mohli n·sledne vypisaù
		zoznamKefky.add(kefka2);
		zoznamKefky.add(kefka3);
		zoznamKefky.add(kefka4);
		
		Nite nit1=new Nite(5, "Nit", "15m");								//Vytvorenie konkrÈtnej nite
		Nite nit2=new Nite(6, "Nit", "30m");
		Nite nit3=new Nite(7, "Nit", "50m");
		
		
		zoznamNite.add(nit1);												//pridanie do zoznamu,  aby sme to mohli n·sledne vypisaù
		zoznamNite.add(nit2);
		zoznamNite.add(nit3);
		
		Pasty pasta1=new Pasty(8, "Pasta", "Detska");						//Vytvorenie konkrÈtnej pasty
		Pasty pasta2=new Pasty(9, "Pasta", "Bieliaca");
		Pasty pasta3=new Pasty(10, "Pasta", "Na citlive zuby");
		
		zoznamPasty.add(pasta1);											//pridanie do zoznamu,  aby sme to mohli n·sledne vypisaù
		zoznamPasty.add(pasta2);
		zoznamPasty.add(pasta3);
		
		Ostatne ostatne1 = new Ostatne(11, "Pasiky", "Bieliace");			////Vytvorenie konkrÈtneho produktu
		Ostatne ostatne2 = new Ostatne(12, "Vosk", "Ortodonticky");
		Ostatne ostatne3 = new Ostatne(13, "Gel", "Bieliaci");
		
		zoznamOstatne.add(ostatne1);										//pridanie do zoznamu,  aby sme to mohli n·sledne vypisaù
		zoznamOstatne.add(ostatne2);
		zoznamOstatne.add(ostatne3);
	}
	
	
	public void zobrazProdukty() {											//funkcia na vypÌsanie produktov
		System.out.println("ID\tNazov\tTyp");
		for(int i = 0;i<this.zoznamKefky.size();i++) {
			System.out.println(this.zoznamKefky.get(i).vratID() + "\t" + this.zoznamKefky.get(i).vratMeno() + "\t" + this.zoznamKefky.get(i).vratTyp());
		}
		for(int i = 0;i<this.zoznamNite.size();i++) {
			System.out.println(this.zoznamNite.get(i).vratID() + "\t" + this.zoznamNite.get(i).vratMeno() + "\t" + this.zoznamNite.get(i).vratDlzku());
		}
		for(int i = 0;i<this.zoznamPasty.size();i++) {
			System.out.println(this.zoznamPasty.get(i).vratID() + "\t" + this.zoznamPasty.get(i).vratMeno() + "\t" + this.zoznamPasty.get(i).vratKategoriu());
		}
		for(int i = 0;i<this.zoznamOstatne.size();i++) {
			System.out.println(this.zoznamOstatne.get(i).vratID() + "\t" + this.zoznamOstatne.get(i).vratMeno() + "\t" + this.zoznamOstatne.get(i).vratDruh());
		}
	}
}
