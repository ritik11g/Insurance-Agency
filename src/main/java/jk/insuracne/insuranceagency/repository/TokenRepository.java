package jk.insuracne.insuranceagency.repository;

import jk.insuracne.insuranceagency.models.VerificationToken;

public interface TokenRepository {
    public VerificationToken getVerificationToken(String token);
    public void save(VerificationToken verificationToken);
}
