package sample.models;

public class UserModel extends Model{
    private static int lastID =0;
    String username;
    String password;

    public UserModel(String username,String password)
    {
        this.username = username;
        this.password = password;
        this.ID = lastID;
        lastID++;

    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }


}
