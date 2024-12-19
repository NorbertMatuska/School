package vino;

public class Konkordia extends Vino {

	public Konkordia() {
		super();
		/*Zamestnanec zam = new ObsluhaMlynceku("Jozko",1,2);
		pridatZamestnanca(zam);
		pridatZamestnanca(new Zberac("Janko",2,3));*/
		nazov = "Konkordia";
	}

	@Override
	public void mletie() {
		double a;
		a = gethmotnost()*0.55;
		setobjem(a);
		super.mletie();
	}

	@Override
	public void zrenie() {
		System.out.println("Vino dozrieva 7 dni");
	}
	
	
}
