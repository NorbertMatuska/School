package sample.Servis;

import sample.models.Model;
import sample.models.UserModel;


import java.util.ArrayList;

public class UserManager implements Manager{

    private final ArrayList<UserModel> models = new ArrayList<>();









    private UserManager(){}

    private static UserManager instance;

    public static UserManager getInstance(){

        if(instance==null){
            instance= new UserManager();
        }
    return instance;
}

    @Override
    public UserModel get(int ID) {
        for (UserModel model: models){
            if (model.getID()==ID){
                return model;
            }
        }

        return null;
    }

    public UserModel get(String username){


        for (UserModel model: models){
            if (model.getUsername().equals(username)){
                return model;
            }
        }

        return null;

    }


    @Override
    public void save(Model model) {
            if (!(model instanceof UserModel)) return;
            UserModel userModel= (UserModel) model;
            models.add(userModel);
    }
}
