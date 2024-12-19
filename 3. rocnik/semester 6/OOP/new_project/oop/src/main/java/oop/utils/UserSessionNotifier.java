package oop.utils;

import java.util.ArrayList;
import java.util.List;

/**
 * The UserSessionNotifier class manages observers for changes in user sessions.
 */
public class UserSessionNotifier {
    private static List<UserSessionObserver> observers = new ArrayList<>();

    /**
     * Adds an observer to the list of observers.
     *
     * @param observer The observer to be added.
     */
    public static void addObserver(UserSessionObserver observer) {
        if (!observers.contains(observer)) {
            observers.add(observer);
        }
    }

    /**
     * Removes an observer from the list of observers.
     *
     * @param observer The observer to be removed.
     */
    public static void removeObserver(UserSessionObserver observer) {
        observers.remove(observer);
    }

    /**
     * Notifies all registered observers.
     */
    public static void notifyObservers() {
        for (UserSessionObserver observer : observers) {
            observer.update();
        }
    }
}


