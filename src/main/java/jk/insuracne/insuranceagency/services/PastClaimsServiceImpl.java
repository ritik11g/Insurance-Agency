package jk.insuracne.insuranceagency.services;

import jk.insuracne.insuranceagency.models.PastClaims;
import jk.insuracne.insuranceagency.repository.PastClaimsRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class PastClaimsServiceImpl implements PastClaimsService {
    PastClaimsRepository pastClaimsRepository;

    @Autowired
    public PastClaimsServiceImpl(PastClaimsRepository pastClaimsRepository) {
        this.pastClaimsRepository = pastClaimsRepository;
    }

    @Override
    public List<PastClaims> getByUsername(String email) {
        return pastClaimsRepository.findByUsername(email);
    }

    @Override
    public List<PastClaims> getByName(String firstName, String lastName) {
        return pastClaimsRepository.findByName(firstName,lastName);
    }

    @Override
    public PastClaims getByRecord(int id) {
        return pastClaimsRepository.findByRecord(id);
    }

    @Override
    public void add(PastClaims pastClaims) {
        pastClaimsRepository.save(pastClaims);
    }
}
