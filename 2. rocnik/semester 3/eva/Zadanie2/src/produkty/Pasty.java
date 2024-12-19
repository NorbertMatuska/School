package produkty;

public class Pasty extends Tovar {
	private String kategoria;
	
	public Pasty(int ID, String meno, String kategoria){		//Kon�truktor
		super(ID, meno);
		this.kategoria = kategoria;
	}
	
	public String vratKategoriu() {
		return this.kategoria;
	}
}
