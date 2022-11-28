package com.example.demo.services;

import com.example.demo.models.Model;

public interface Manager {
    Model get(int ID);
    Model get(String name);
    void save(Model model);
}
