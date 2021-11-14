package jk.insuracne.insuranceagency.repository;

import jk.insuracne.insuranceagency.models.Transaction;

import java.util.List;

public interface TransactionRepository {
    public void save(Transaction transaction);
    public List<Transaction> finalAll();
    public List<Transaction> findByUser(int userId);
}
