#created May 2018 for NYC Roundtable. Have a ?, find cannadw@

import boto3
import time

def lambda_handler(event, context):
    
    #search table
    dynamodb = boto3.resource('dynamodb')
    roundtableTable = dynamodb.Table('roundtable_number_list')
    result = roundtableTable.scan()
    items = result["Items"]
    
    #return values and serialize just phoneNumbers
    emergencyNumbers = []
    for key in items:
        emergencyNumbers.append((key["PhoneNumber"]))
    
    
    print(emergencyNumbers)
    
    #buffer outboundAPI requests    
    counter = 0
    for num in emergencyNumbers: 
        counter = counter + 1
        if counter <= 2:
            outboundDialer(num)
            print("Dialing {}".format(num))
            counter = counter + 1
        else:
            counter = 0
            time.sleep(1)
            outboundDialer(num)
            print("Dialing {}".format(num))
            
    return "Successful!" 
    
def outboundDialer(ph):
    
    client = boto3.client('connect')

    response = client.start_outbound_voice_contact(
        DestinationPhoneNumber = ph,
        ContactFlowId = "b0482adf-85ae-4151-990b-5bb74859c5da",
        InstanceId = "33de395b-9b5e-4ed2-b4d0-4b2d42fcdc1c",
        # ClientToken='string',
        SourcePhoneNumber = "+13478093036"
        # QueueId='string',
        # Attributes={
        #     'string': 'string'
        # }
    )
    
    dialedRun = "Success!"

    return dialedRun

