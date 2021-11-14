package jk.insuracne.insuranceagency.repository;

import jk.insuracne.insuranceagency.models.LifeInsuranceClaim;

import java.util.List;


public interface LifeInsuranceClaimsRepository {
    public void save(LifeInsuranceClaim lifeInsuranceClaim);
    public void delete(int id);
    public void updateStatus(String status, int id);
    public LifeInsuranceClaim findById(int id);
    public String findDocuments(int id);

    List<LifeInsuranceClaim> findAllByStatus(String status);
}
