/**
 * OpportunityTriggerHandler
 * This class handles trigger activities (namely afterInsert and afterUpdate
 * The class uses Kevin O'Hara's awesomely fantastic Trigger Handler pattern: 
 * https://github.com/kevinohara80/sfdc-trigger-framework
 * The afterInsert and afterUpdate logic check oppportunities (in bulk mind you)
 * to see if they have just changed to "closed won" status and to see
 * if their amounts exceed the big deal alert threshold.
 * If so, then the big deal alert URL is called triggering a fun sequence
 * on the mbed application board.
 * @author James Loghry (@dancinllama on twitter)
 * @date 12/8/2013
 */
public class OpportunityTriggerHandler extends TriggerHandler {

    private Decimal bigDealThreshold {get;set;}
    private String bigDealURL {get;set;}

    /**
     * @description Default constructor
     * Sets private member variables via a custom hierarchy setting called MySettings__c
     */
    public OpportunityTriggerHandler() {
        //Get Big Deal configurations from Custom Setting (Hierarchy)
        MySettings__c ms = MySettings__c.getInstance();
        bigDealThreshold= ms.Big_Deal_Threshold__c;
        bigDealURL = ms.Big_Deal_URL__c;
    }

    //Run this on after update trigger logic
    protected override void afterUpdate() {
        if(bigDealThreshold != null){
            for(Opportunity o : (List<Opportunity>)Trigger.new){
                Opportunity old = (Opportunity)Trigger.oldMap.get(o.Id);
                
                //Check to see if old record was not closed won, and the update is to closed won.
                //Also check to see if the big deal threshold was reached.
                if(!(old.isClosed && old.isWon) && o.IsClosed && o.IsWon && o.Amount >= bigDealThreshold){
                    requestBigDealAlert(o.Name,o.Amount,bigDealURL);
                }
            }
        }
    }
  
    //Run this on after insert trigger logic
    protected override void afterInsert() {
        if(bigDealThreshold != null){
            for(Opportunity o : (List<Opportunity>)Trigger.new){
                if(o.IsClosed && o.IsWon && o.Amount >= bigDealThreshold){
                    requestBigDealAlert(o.Name,o.Amount,bigDealURL);
                }
            }
        }
    }

    //Method for calling out to HTTP server on mbed microcontroller.
    @future(callout=true)
    public static void requestBigDealAlert(String oname, Decimal oamount, String url){
  
        String onameStr = (oname != null) ? oname : '';
        String oamountStr = (oamount != null) ? oamount.setScale(2).format() : '';
        
        //Customs setting URL  should be http://<mbed_ip_addr>/bigdeal?opptyName=<name>&opptyAmount=<amount>
        String formattedUrl = String.format(url,new String[]{onameStr,oamountStr});
  
        HttpRequest req = new HttpRequest();
        req.setMethod('GET');
        req.setEndpoint(formattedUrl);
        System.debug('formattedURL: ' + formattedUrl);

        try {
            //Execute web service call here      
            Http http = new Http();
            HTTPResponse res = http.send(req);   
        } catch(System.CalloutException e) {}   
  }
}