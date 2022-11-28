package sample.models;

public class TaskModel extends Model{
    private static int lastID = 0;
    String name;
    int time;


    public TaskModel(String name,int time) {
        this.name = name;
        this.time = time;
        this.ID = lastID++;
    }

    public String getName() {
        return name;
    }

    public int getTime() {
        return time;
    }
}
