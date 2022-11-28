package com.example.demo.models;

public class TaskModel extends Model{
    private static int lastID = 0;
    String name;
    int time;

    public TaskModel(String name, int time) {
        this.name = name;
        this.time = time;
        this.ID = lastID;
        lastID++;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getTime() {
        return time;
    }

    public void setTime(int time) {
        this.time = time;
    }
}
