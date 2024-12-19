package osoby;

public class ObsluhaMlynceku extends Zamestnanec{
	private double litreVina;
	
	public ObsluhaMlynceku(String meno, int IDzamestnanca, double litreVina) {
		super(meno,IDzamestnanca);
		this.litreVina = litreVina;
	}
	
	public double returnLitre() {
		return this.litreVina;
	}
}
