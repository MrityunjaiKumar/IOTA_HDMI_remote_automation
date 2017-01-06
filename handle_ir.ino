/*
 * IOTA platform developed (as a part of my BTP project) at www.cedtnsit.in
 * Few application developed at http://iot.net.in/
 * Based on https://github.com/markszabo/IRremoteESP8266 library
 * 
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 *By:- www.mrityunjai.in
 */

void handle_ir(int hdmi_x){
    
    
    if(hdmi_x==1){
        Serial.print("hdmi 1 is selected");
        hdmi_status=hdmi_x;
        irsend.sendNEC(0xFF18E7, 38);
        delay(2000);
      }
    else if(hdmi_x==2){
         Serial.print("hdmi 2 is selected");  
         hdmi_status=hdmi_x;
         irsend.sendNEC(0xFF10EF, 38);
         delay(2000); 
      }
    else if(hdmi_x==3){
         Serial.print("hdmi 3 is selected");
         hdmi_status=hdmi_x;
         irsend.sendNEC(0xFF9867, 38);
         delay(2000);
     }
     else if(hdmi_x==4){
         Serial.print("hdmi 4 is selected");
         circular_shift_hdmi();
         Serial.println();
         Serial.print("hdmi_status = "); 
         Serial.println(hdmi_status);
      }
    else {
    Serial.println("invalid hdmi");
     }
  }

  void circular_shift_hdmi(){
    Serial.println();
    Serial.println("hdmi shift is selected");
    

    handle_ir(hdmi_status);
    if(hdmi_status==3)
      hdmi_status=0;
    hdmi_status=hdmi_status+1;
    }
    

