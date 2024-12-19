package osoby;

public class Zberac extends Zamestnanec {
	private double pozbieraneOvocie;
	
	public Zberac (String meno, int IDzamestnanca, double pozbieraneOvocie) {
		super(meno, IDzamestnanca);
		this.pozbieraneOvocie = pozbieraneOvocie;
	}
	
	public double returnPozbieraneOvocie() {
		return this.pozbieraneOvocie;
	} 
}
