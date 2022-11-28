package osoby;

public class Zamestnanec extends Clovek {
	private int IDzamestnanca;
	
	public Zamestnanec(String meno, int IDzamestnanca) {
		super(meno);
		this.IDzamestnanca = IDzamestnanca;
	}
	
	public int returnIDzamestnanca() {
		return this.IDzamestnanca;
	}
	}
	