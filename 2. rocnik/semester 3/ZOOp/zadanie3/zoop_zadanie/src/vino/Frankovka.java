package vino;

public class Frankovka extends Vino {
	public Frankovka() {
		super();
		//Zamestnanec zam = new ObsluhaMlynceku("Peto",1,2);	//agregacia
		//pridatZamestnanca(zam);
		//pridatZamestnanca(new Zberac("Bob",2,3));
		nazov = "Frankovka";
	}

	@Override
	public void mletie() {
		double a;
		a = gethmotnost()*0.45;
		setobjem(a);
		super.mletie();
	}
	@Override
	public void zrenie() {
		System.out.println("Vino dozrieva 8.5 dna");
	}
}
