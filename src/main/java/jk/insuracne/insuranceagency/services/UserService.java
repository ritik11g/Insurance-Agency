package jk.insuracne.insuranceagency.services;

import jk.insuracne.insuranceagency.models.User;
import jk.insuracne.insuranceagency.models.VerificationToken;

public interface UserService {
    public void save(User user);
    public User findByUsername(String email);
    public boolean userExists(String email);
    public void createVerificationToken(User user, String token);
    public void enableRegisteredUser(User user);
    public VerificationToken getVerificationToken(String token);
    public User findByUserId(int id);
    public void assignRoleEmployee(String email);

    void deadUser(int userId);
}
