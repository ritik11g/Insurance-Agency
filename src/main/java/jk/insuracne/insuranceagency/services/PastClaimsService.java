package jk.insuracne.insuranceagency.services;

import jk.insuracne.insuranceagency.models.PastClaims;

import java.util.List;

public interface PastClaimsService {
    public List<PastClaims> getByUsername(String email);
    public List<PastClaims> getByName(String firstName,String lastName);
    public PastClaims getByRecord(int id);
    public void add(PastClaims pastClaims);
}
