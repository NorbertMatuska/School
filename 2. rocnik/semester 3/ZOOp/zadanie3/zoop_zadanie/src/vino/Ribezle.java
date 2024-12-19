package vino;

public class Ribezle extends Vino {
	public Ribezle() {
		super();
		/*Zamestnanec zam = new ObsluhaMlynceku("Adrian",1,2);
		pridatZamestnanca(zam);
		pridatZamestnanca(new Zberac("Lucia",2,3));*/
		nazov = "Ribezle";
	}

	@Override
	public void mletie() {
		double a;
		a = gethmotnost()*0.66;
		setobjem(a);
		super.mletie();
	}
	@Override
	public void zrenie() {
		System.out.println("Vino dozrieva 10 dni");
	}
}
