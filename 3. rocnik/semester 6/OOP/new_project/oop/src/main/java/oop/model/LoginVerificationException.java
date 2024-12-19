package oop.model;

/**
 * The {@code LoginVerificationException} class is a custom exception used to indicate
 * a failure during the login verification process. It extends {@link Exception}, allowing it
 * to be thrown and caught in contexts where a login verification operation can fail.
 */
public class LoginVerificationException extends Exception {
    /**
     * Constructs a new {@code LoginVerificationException} with the specified detail message.
     * The message is saved for later retrieval by the {@link Throwable#getMessage()} method.
     *
     * @param message the detail message. The detail message is saved for later retrieval
     *                by the {@link Throwable#getMessage()} method.
     */
    public LoginVerificationException(String message) {
        super(message);
    }

    /**
     * Constructs a new {@code LoginVerificationException} with the specified detail message
     * and cause.
     *
     * @param message the detail message. The detail message is saved for later retrieval
     *                by the {@link Throwable#getMessage()} method.
     * @param cause   the cause (which is saved for later retrieval by the {@link Throwable#getCause()} method).
     */
    public LoginVerificationException(String message, Throwable cause) {
        super(message, cause);
    }
}
