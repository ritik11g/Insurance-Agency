package jk.insuracne.insuranceagency.job;

import jk.insuracne.insuranceagency.services.MailService;
import jk.insuracne.insuranceagency.services.PolicyRecordService;
import jk.insuracne.insuranceagency.services.PropertyService;
import jk.insuracne.insuranceagency.services.VehicleService;
import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;
import org.springframework.beans.factory.annotation.Autowired;

public class ExpiryCheckingJob implements Job {

    @Autowired
    private PolicyRecordService policyRecordService;
    @Autowired
    private VehicleService vehicleService;
    @Autowired
    private PropertyService propertyService;
    @Autowired
    private MailService mailService;

    @Override
    public void execute(JobExecutionContext jobExecutionContext) throws JobExecutionException {
        policyRecordService.markExpiration();
        vehicleService.removeExpirationRecord();
        propertyService.removeExpirationRecord();
        mailService.sendExpirationMail();
        System.out.println("Job running!");
    }
}
