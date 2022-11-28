package com.example.demo.services;


import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class UserAccount {
    PrintWriter out;
    public String AccountName;
    public String AccountPassword;

    public UserAccount(String accountName, String accountPassword) {
        AccountName = accountName;
        AccountPassword = accountPassword;
    }

    public String getAccountName() {
        return AccountName;
    }

    public String getAccountPassword() {
        return AccountPassword;
    }

    public void SaveAccountToTextFile(String accountName, String accountPassword) {
        {
            try {
                out = new PrintWriter("Accounts.txt");
                out.println(accountName);
                out.println(accountPassword);
                out.println("-");
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }
    }
}
