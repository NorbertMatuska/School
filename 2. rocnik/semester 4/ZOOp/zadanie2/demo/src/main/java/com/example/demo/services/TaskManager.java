package com.example.demo.services;

import com.example.demo.models.Model;
import com.example.demo.models.TaskModel;

import java.util.ArrayList;

public class TaskManager implements Manager{
    private final ArrayList<TaskModel> models = new ArrayList<>();

    private TaskManager(){}

    private static TaskManager instance;

    public static TaskManager getInstance() {
        if(instance == null) {
            instance = new TaskManager();
        }
        return  instance;
    }

    @Override
    public TaskModel get(int ID) {
        for (TaskModel model: models) {
            if (model.getID() == ID) {
                return model;
            }
        }
        return null;
    }

    //overloading
    public TaskModel get(String name) {
        for (TaskModel model: models) {
            if(model.getName().equals(name)) {
                return model;
            }
        }
        return null;
    }

    @Override
    public void save(Model model) {
        if (!(model instanceof TaskModel)) return;
        TaskModel TaskModel = (TaskModel) model;
        models.add(TaskModel);
    }
}
