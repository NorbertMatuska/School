package osoby;

public class nosic extends zamestnanec {
	private int ovocieNaRuke;
	
	public nosic (String meno, int IDzamestnanca, int ovocieNaRuke) {
		super(meno, IDzamestnanca);
		this.ovocieNaRuke = ovocieNaRuke;
	}
	
	public int returnOvocieNaRuke() {
		return this.ovocieNaRuke;
	}
}
