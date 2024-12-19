package osoby;

public class zamestnanec extends clovek {
	private int IDzamestnanca;
	
	public zamestnanec(String meno, int IDzamestnanca) {
		super(meno);
		this.IDzamestnanca = IDzamestnanca;
	}
	
	public int returnIDzamestnanca() {
		return this.IDzamestnanca;
	}
	}
	