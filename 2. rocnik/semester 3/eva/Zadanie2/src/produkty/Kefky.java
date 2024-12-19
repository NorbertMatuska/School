package produkty;

public class Kefky extends Tovar {
	private String typ;
	
	public Kefky(int ID, String meno, String typ){		//Konštruktor
		super(ID, meno);
		this.typ = typ;
	}
	
	public Kefky(int ID) {								//overriding(prekonavanie)
		super(ID);
		this.typ = "nespecifikovany";
	}
	public String vratTyp() {							
		return this.typ;
	}
}
