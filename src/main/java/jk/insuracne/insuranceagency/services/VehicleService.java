package jk.insuracne.insuranceagency.services;

import jk.insuracne.insuranceagency.models.PolicyRecord;
import jk.insuracne.insuranceagency.models.Vehicle;

import java.util.List;

public interface VehicleService {
    public List<Vehicle> getByUser(int userId);
    public Vehicle getById(int id);
    public PolicyRecord getRecordOnVehicle(int id);
    public Vehicle getByRecord(int recordId);
    public void addVehicle(Vehicle vehicle);
    public void changeRecord(int recordId,int id);
    public void delete(int id);
    void removeRecord(int id);
    void removeExpirationRecord();
    public List<Vehicle> getVehicleForBuyingPolicy(int userId);
}
