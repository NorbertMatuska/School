package produkty;

public class Nite extends Tovar {
	private String dlzka;
	
	public Nite(int ID, String meno, String dlzka){			//Kon�truktor
		super(ID, meno);
		this.dlzka = dlzka;
	}
	
	public String vratDlzku() {
		return this.dlzka;
	}
}
