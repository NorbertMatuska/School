package oop.utils;

import oop.model.User;

/**
 * The UserSession class manages the session of the current user.
 */
public class UserSession {
    private static UserSession instance;
    private User currentUser;

    private UserSession() {}

    /**
     * Retrieves the singleton instance of UserSession.
     *
     * @return The singleton instance of UserSession.
     */
    public static UserSession getInstance() {
        if (instance == null) {
            instance = new UserSession();
        }
        return instance;
    }

    /**
     * Sets the current user.
     *
     * @param user The user to set as the current user.
     */
    public void setCurrentUser(User user) {
        this.currentUser = user;
        // Notify observers (e.g., DashboardView) about the change
        UserSessionNotifier.notifyObservers();
    }

    /**
     * Retrieves the current user.
     *
     * @return The current user.
     */
    public User getCurrentUser() {
        return currentUser;
    }

    /**
     * Logs out the current user.
     */
    public void logout() {
        setCurrentUser(null);
    }
}