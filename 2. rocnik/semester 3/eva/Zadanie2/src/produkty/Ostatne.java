package produkty;

public class Ostatne extends Tovar {
	private String druh;
	
	public Ostatne(int ID, String meno, String druh){		//Kon�truktor
		super(ID, meno);
		this.druh = druh;
	}
	
	public String vratDruh() {
		return this.druh;
	}
}
