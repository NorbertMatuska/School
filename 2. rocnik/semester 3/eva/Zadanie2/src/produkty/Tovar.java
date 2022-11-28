package produkty;

public class Tovar {
	private String meno;
	private int ID;
	
	public Tovar(int ID, String meno){			//Konštruktor
		
		this.ID = ID;
		this.meno = meno;
	}
	
	public Tovar(int ID) {						//overriding
		this.ID = ID;
		this.meno = "vyrobok";
	}
	
	public String vratMeno() {
		return this.meno;
	}
	
	public int vratID() {
		return this.ID;
	}
}
