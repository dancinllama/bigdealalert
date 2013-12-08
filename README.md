Big Deal Alert
============

An Internet of Things experiment with SFDC callout to an mbed microcontroller and its HTTP server.

Closing a "big deal" in SFDC spawns a flurry of activity on the mbed microcontroller.

Instructions:
<ol>
<li>Download the .bin file from the mbed directory.</li>
<li>ook your computer up to the mbed microcontroller via the USB cable.</li>
<li>Copy the bin file to the mbed application board.</li>
<li>Press the reset button.  You should see an IP address displayed on the LCD.</li>
<li>Log into your SFDC org (preferably developer org)</li>
<li>Create a custom hierarchy setting called "MySettings__c" with two fields:<br />
Big_Deal_Threshold__c and Big_Deal_Url__c</li>
<li>Manage the custom setting and set Big_Deal_Url__c = 'http://<mbed micro ip addr>/bigdeal?opptyName={0}&opptyAmount={1}"</li>
<li>Set Big_Deal_Threshold__c to some arbitrary amount.</li>
<li>Copy the Apex classes from sfdc/src/classes to your salesforce org.</li>
<li>Copy the Opportunity trigger from sfdc/src/triggers to your salesforce org.</li>
<li>Try creating or updating an existing opportunity to closed won (surpassing the threshold)</li>
<li>Watch the magic happen.</li>
</ol>
