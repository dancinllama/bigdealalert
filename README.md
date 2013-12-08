Big Deal Alert
============

An Internet of Things experiment with SFDC callout to an mbed microcontroller and its HTTP server.

Closing a "big deal" in SFDC spawns a flurry of activity on the mbed microcontroller.

Instructions:
1. Download the .bin file from the mbed directory.  
2. Hook your computer up to the mbed microcontroller via the USB cable.
3. Copy the bin file to the mbed application board.
3. Press the reset button.  You should see an IP address displayed on the LCD.
4. Log into your SFDC org (preferably developer org)
5. Create a custom hierarchy setting called "MySettings__c" with two fields:
5a.  Big_Deal_Threshold__c and Big_Deal_Url__c
6.  Manage the custom setting and set Big_Deal_Url__c = 'http://<mbed micro ip addr>/bigdeal?opptyName={0}&opptyAmount={1}"
7.  Set Big_Deal_Threshold__c to some arbitrary amount.
8.  Copy the Apex classes from sfdc/src/classes to your salesforce org.
9.  Copy the Opportunity trigger from sfdc/src/triggers to your salesforce org.
10.  Try creating or updating an existing opportunity to closed won (surpassing the threshold)
11.  Watch the magic happen.
