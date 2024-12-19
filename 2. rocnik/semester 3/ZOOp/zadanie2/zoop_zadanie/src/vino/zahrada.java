package vino;

public class zahrada {
	private int konkordia;
	private int samorod;
	private int frankovka;
	private int alibernet;
	private int ribezla;
	private int visna;
	
	public zahrada (int konkordia, int samorod, int frankovka, int alibernet, int ribezla, int visna) {
		this.konkordia = 500;
		this.samorod = 500;
		this.frankovka = 500;
		this.alibernet = 500;
		this.ribezla = 250;
		this.visna = 250;
	}
	
	public int returnKonkordia() {
		return this.konkordia;
	}
	public int returnSamorod() {
		return this.samorod;
	}
	public int returnFrankovka() {
		return this.frankovka;
	}
	public int returnAlibernet() {
		return this.alibernet;
	}
	public int returnRibezla() {
		return this.ribezla;
	}
	public int returnVisna() {
		return this.visna;
	}
	public int celkovaUroda(int konkordia, int samorod, int frankovka, int alibernet, int ribezla, int visna) { 
		return (konkordia + samorod + frankovka + alibernet + ribezla + visna); //overloading
	} 
}
