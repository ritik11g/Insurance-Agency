package jk.insuracne.insuranceagency.controllers;

import jk.insuracne.insuranceagency.models.User;
import jk.insuracne.insuranceagency.services.SecurityService;
import jk.insuracne.insuranceagency.services.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import java.security.Principal;

@Controller
public class LoginController {
    UserService userService;
    SecurityService securityService;

    @Autowired
    public LoginController(UserService userService, SecurityService securityService) {
        this.userService = userService;
        this.securityService = securityService;
    }

    @GetMapping("/login")
    public String login(Model model){
        model.addAttribute("user",new User());
        return "login";
    }

    @RequestMapping("/welcome")
    public String welcome(Principal principal, Model model){
        User user = userService.findByUsername(principal.getName());
        if(user.getStatus().equals("not-verified")) {
            model.addAttribute("verification",false);
            securityService.notVerified();
            return "redirect:/homepage";
        }
        if(user.getStatus().equals("dead")){
            securityService.notVerified();
            return "redirect:/homepage";
        }
        String[] roles = user.getRole().split(" ");
        for(int i=0;i< roles.length;i++){
            if(roles[i].equals("admin"))return "redirect:/admin";
        }
        model.addAttribute("username",securityService.findLoggedInUsername());
        return "redirect:/self";
    }
}
