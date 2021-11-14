package jk.insuracne.insuranceagency.repository;

import jk.insuracne.insuranceagency.models.FAQ;

import java.util.List;

public interface FAQRepository {
    public List<FAQ> findAll();
    public List<FAQ> findByTopic(String topic);
    public void save(FAQ faq);
}
