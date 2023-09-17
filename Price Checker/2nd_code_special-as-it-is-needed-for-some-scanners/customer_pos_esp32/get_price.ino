void getPrice( String bar){

digitalWrite(15 , LOW);
scannerOffEnd = millis() + 400;
Serial.println( millis());
Serial.println(scannerOffEnd);
  



  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;


      
 
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      
      String httpRequestData = "barcode=" + bar;


      int httpResponseCode = http.POST(httpRequestData);
      
      if(httpResponseCode>0){
  
    String response = http.getString();  //Get the response to the request

    if(response == "Not Found!"){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(response);
      return;
    }
    int response_len = response.length() + 1; 
    char json[response_len];

    response.toCharArray(json, response_len);


    DeserializationError error = deserializeJson(doc, json);

    
  
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);   
    
 if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    lcd.print("Failed to parse the price");

    //return;
  } else{
      const char* price = doc["barcode"];
Serial.println(price);

lcd.print(price);
lcd.setCursor(17, 2);
lcd.print("LBP");
}    
  
}else{
  
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  
}
     
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("WiFi Disconnected");

    }


}