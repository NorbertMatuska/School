package sample.Servis;

import sample.models.Model;

public interface Manager {

    Model get(int ID);

    void save(Model model);


}
