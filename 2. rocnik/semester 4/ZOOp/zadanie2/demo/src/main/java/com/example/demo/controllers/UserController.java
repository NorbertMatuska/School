package com.example.demo.controllers;

import com.example.demo.models.TaskModel;
import com.example.demo.models.UserModel;
import com.example.demo.services.TaskManager;
import com.example.demo.services.UserManager;
import com.example.demo.services.UserAccount;

public class UserController {
    UserManager um;
    TaskManager tm;
    UserAccount ua;
    public UserController() {
        um = UserManager.getInstance();
        tm = TaskManager.getInstance();
    }

    public UserModel getFirstUser() {
        return um.get(0);
    }

    public UserModel getByName(String name) {
        return um.get(name);
    }

    public TaskModel createTask(String name, int time) {
        TaskModel task = new TaskModel(name, time);
        tm.save(task);
        return task;
    }

    public void saveUserAccount(String name, String password) {
        this.ua.SaveAccountToTextFile(name, password);
    }
}
