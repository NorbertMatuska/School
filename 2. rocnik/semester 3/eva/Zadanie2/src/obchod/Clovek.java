package obchod;

public class Clovek {
	private String meno;
	private String email;
	
	public Clovek(String menoc, String emailc) {		//Konštruktor
		this.meno = menoc;
		this.email = emailc;
	}
	
	public String vratMeno() {
		return this.meno;
	}
	
	public String vratEmail() {
		return this.email;
	}
	
	public void zmenEmail(String novyEmail) {
		this.email = novyEmail;
	}
}
