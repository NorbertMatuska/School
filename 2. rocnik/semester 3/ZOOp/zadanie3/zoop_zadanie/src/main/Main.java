package main;
import java.util.Scanner;
import vino.*;
import osoby.*;

public class Main {
	public static void main(String[] args) {
		boolean x = true;
		Scanner scn = new Scanner(System.in);

		do {
			System.out.println("Zadajte jednu z nasledovnych moznosti");
			System.out.println("-------------------------------------");
			System.out.println("1-Pridat mnozstvo hrozna");
			System.out.println("2-Pridat zamestnanca");
			System.out.println("3-Ukazat celkovu cenu spracovaneho vina");
			System.out.println("4-Spracovat hrozno");
			System.out.println("5-Cennik + odkupenie vina");
			System.out.println("0-Ukoncit program");
			System.out.println("-------------------------------------");
			
			String input = scn.nextLine();
			//System.out.println(input);
			switch(input) {
			case "1":
				System.out.println("Vyberte a zadajte mnozstvo vina v kg");
				System.out.println("k - konkordia");
				System.out.println("f - frankovka");
				System.out.println("r - ribezle");
				System.out.println("-------------------------------------");

				input = scn.nextLine();
				switch(input) {
				case "k":
					System.out.println("Ake mnozstvo v kg?");
					input = scn.next();
					int s = Integer.parseInt(input);
					Vinaren.getVinaren().pridajHmotnostko(s);
					System.out.println("Hmotnost: "+Vinaren.getVinaren().getHmotnostko()+" kg");
					scn.nextLine();
					break;
				case "f":
					System.out.println("Ake mnozstvo v kg?");
					input = scn.next();
					int ss = Integer.parseInt(input);
					Vinaren.getVinaren().pridajHmotnostfr(ss);
					System.out.println("Hmotnost: "+Vinaren.getVinaren().getHmotnostfr()+" kg");
					scn.nextLine();
					break;
				case "r":
					System.out.println("Ake mnozstvo v kg?");
					input = scn.next();
					int sss = Integer.parseInt(input);
					Vinaren.getVinaren().pridajHmotnostri(sss);
					System.out.println("Hmotnost: "+Vinaren.getVinaren().getHmotnostri()+" kg");
					scn.nextLine();
					break;
				default:
					System.out.println("Invalid input");
					break;
				}
				break;
			case "2":
				String meno;
				int ID;
				Zamestnanec zam = new Zamestnanec("meno",0);
				
				System.out.println("Zadajte meno zamestnanca");
				meno = scn.nextLine();
				
				System.out.println("Zadajte ID zamestnanca");
				ID = scn.nextInt();
				scn.nextLine();
				
				System.out.println("Vyberte aky typ zamestnanca");
				System.out.println("1 - Obsluha Mlynceku");
				System.out.println("2 - Zberac");
				input = scn.nextLine();
				
				switch(input) {
				case "1":
					System.out.println("Zadajte produktivitu prace l/h");
					double lh = scn.nextDouble();
					zam = new ObsluhaMlynceku(meno,ID,lh);
					scn.nextLine();
					break;
				case "2":
					System.out.println("Zadajte produktivitu prace kg/h");
					double kgh = scn.nextDouble();
					zam = new Zberac(meno,ID,kgh);
					scn.nextLine();
					break;
				default:
					System.out.println("Invalid input");
					break;
				}
				System.out.println("Kam chcete priradit zamestnanca?");
				System.out.println("k - konkordia");
				System.out.println("f - frankovka");
				System.out.println("r - ribezle");
				System.out.println("-------------------------------------");
				input = scn.nextLine();
				
				switch(input) {
				case "k":
					Vinaren.getVinaren().pridajZCKo(zam);
					System.out.println("Zamestnanec bol pridany uspesne.");
					break;
				case "f":
					Vinaren.getVinaren().pridajZCFr(zam);
					System.out.println("Zamestnanec bol pridany uspesne.");
					break;
				case "r":
					Vinaren.getVinaren().pridajZCRi(zam);
					System.out.println("Zamestnanec bol pridany uspesne.");
					break;
				default:
					System.out.println("Invalid input");
					break;
				}
				break;
			case "3":
				System.out.println("Celkova cena za vsetko spracovane hrozno: "+Vinaren.getVinaren().celkovaCena()+" €.");
			case "4":
				Vinaren.getVinaren().spracuj();
				break;
			case "5":
				System.out.println("Cennik:");
				System.out.println("-------------------------------------");
				System.out.println("Cena za liter Frankovky "+Vinaren.getVinaren().cenaLiterFr()+" €.");
				System.out.println("Cena za liter Konkordie "+Vinaren.getVinaren().cenaLiterKo()+" €.");
				System.out.println("Cena za liter Ribezlaku "+Vinaren.getVinaren().cenaLiterRi()+" €.");
				System.out.println("-------------------------------------");
				System.out.println("Ktore vino chcete kupit?");
				System.out.println("k - konkordia");
				System.out.println("f - frankovka");
				System.out.println("r - ribezle");
				System.out.println("-------------------------------------");
				input = scn.nextLine();
				
				double mnozstvo = 0;
				double cena = 0;
				
				switch(input) {
				case "f":
					System.out.println("Ake mnozstvo? Mame k dispozicii: "+Vinaren.getVinaren().getSpracovaneFr()+" litrov vina.");
					mnozstvo = scn.nextDouble();
					scn.nextLine();
					cena = Vinaren.getVinaren().predajHrozno(mnozstvo, 1);
					
					if (cena > 0) {
						System.out.println("Hrozno bolo predane za: "+cena+" €.");
					}
					else {
						System.out.println("Nepodarilo sa predat hrozno.");
					}
					
					break;
				case "k":
					System.out.println("Ake mnozstvo? Mame k dispozicii: "+Vinaren.getVinaren().getSpracovaneKo()+" litrov vina.");
					mnozstvo = scn.nextDouble();
					scn.nextLine();
					cena = Vinaren.getVinaren().predajHrozno(mnozstvo, 2);
					
					if (cena > 0) {
						System.out.println("Hrozno bolo predane za: "+cena+" €.");
					}
					else {
						System.out.println("Nepodarilo sa predat hrozno.");
					}
					
					break;
				case "r":
					System.out.println("Ake mnozstvo? Mame k dispozicii: "+Vinaren.getVinaren().getSpracovaneRi()+" litrov vina.");
					mnozstvo = scn.nextDouble();
					scn.nextLine();
					cena = Vinaren.getVinaren().predajHrozno(mnozstvo, 3);
					
					if (cena > 0) {
						System.out.println("Hrozno bolo predane za: "+cena+" €.");
					}
					else {
						System.out.println("Nepodarilo sa predat hrozno.");
					}
					
					break;
				default:
					System.out.println("Invalid input");
					break;
				}
				break;
			case "0":
				x = false;
				break;
				
				default:
					System.out.println("Invalid input");
					break;
			}
		}
		while(x == true);
	}
}
