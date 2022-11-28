package sample.controllers;

import sample.Servis.TaskManager;
import sample.Servis.UserManager;
import sample.models.TaskModel;
import sample.models.UserModel;

public class UserController {
    UserManager um;
    TaskManager tm;
    public UserController() {

        um = UserManager.getInstance();
        tm = TaskManager.getInstance();
    }

    public UserModel getFirstUser(){

        return um.get(0);

    }

    public UserModel getByName(String danka)
    {
        return um.get(danka);
    }

    public TaskModel createTask(String name, int time){
        TaskModel task = new TaskModel(name,time);
        tm.save(task);
        return task;


    }


}
