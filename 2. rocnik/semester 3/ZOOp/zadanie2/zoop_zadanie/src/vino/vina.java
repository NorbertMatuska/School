package vino;

public class vina {
	private String nazov;
	private int ID;
	private String typ;
	private int cukornatost;
	
	public vina (String nazov, int ID, String typ, int cukornatost) {
		this.nazov = nazov;
		this.ID = ID;
		this.typ = typ;
		this.cukornatost = cukornatost;
	}
	
	public String returnNazov() {
		return this.nazov;
	}
	
	public int returnID() {
		return this.ID;
	}
	
	public String returnTyp() {
		return this.typ;
	}
	
	public int returnCukornatost() {
		return this.cukornatost;
	}
}
