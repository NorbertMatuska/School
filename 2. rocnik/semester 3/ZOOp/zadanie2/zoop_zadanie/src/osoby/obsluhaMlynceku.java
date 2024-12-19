package osoby;

public class obsluhaMlynceku extends zamestnanec{
	private int litreVina;
	
	public obsluhaMlynceku(String meno, int IDzamestnanca, int litreVina) {
		super(meno,IDzamestnanca);
		this.litreVina = litreVina;
	}
	
	public int returnLitre() {
		return this.litreVina;
	}
}
