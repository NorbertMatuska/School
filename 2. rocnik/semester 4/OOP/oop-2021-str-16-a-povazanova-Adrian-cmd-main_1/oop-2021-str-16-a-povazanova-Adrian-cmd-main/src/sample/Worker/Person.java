package sample.Worker;

public abstract class Person {

    //private static Person dalsi;
    private String Name;
    private  String Surname;
    private int ID;
    private String Povolanie;

    public String getPovolanie() {
        return Povolanie;
    }

    public void setPovolanie(String povolanie) {
        Povolanie = povolanie;
    }

    public void setName(String name) {
      this.Name = name;
   }
   public String getName(){return Name;}

   public void setSurname(String surname) {
      this.Surname = surname;
   }
   public String getSurname(){return Surname;}

   public void setID(int ID) {
      this.ID = ID;
   }
   public int getID(){return ID;}



   public void Vypis(){

         System.out.println("Name: "+Name);
         System.out.println("Surname: "+Surname);
         System.out.println("ID: "+ID);



         }


}
