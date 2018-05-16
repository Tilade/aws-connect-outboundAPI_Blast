#created May 2018 for NYC Roundtable. Have a ?, find cannadw@

import boto3


def lambda_handler(event, context):
    
    dynamodb = boto3.resource('dynamodb')
    roundtableTable = dynamodb.Table('roundtable_number_list')
    
    callerID = event["Details"]["ContactData"]["CustomerEndpoint"]["Address"]
    
    
    roundtableTable.put_item(
        Item = {
            'PhoneNumber' : callerID
        }
    )
    
    returnStatement = {"lambdaRun" : "True"}
    
    return returnStatement
