package osoby;

public class zberac extends zamestnanec {
	private int pozbieraneOvocie;
	
	public zberac (String meno, int IDzamestnanca, int pozbieraneOvocie) {
		super(meno, IDzamestnanca);
		this.pozbieraneOvocie = pozbieraneOvocie;
	}
	
	public int returnPozbieraneOvocie() {
		return this.pozbieraneOvocie;
	} 
}
