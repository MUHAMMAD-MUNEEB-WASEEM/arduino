
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "PTCL-BB-208"
#define WIFI_PASSWORD "356E3FB0"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDNTtKvrDkdC9uFY1Ipm0wp-NTpy4V3sco"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "relay-9e705-default-rtdb.firebaseio.com" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

#include "CComplex.h"

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;

float floatValueNew;
int intValueNew;

bool signupOK = false;

float vp1;
float vp2;
float vp3;
float va1;
float va2;
float va3;
float ip1;
float ip2;
float ip3;
float ia1;
float ia2;
float ia3;

float vo=0; 
float v1=0; 
float v2=0; 
    
float io=0;
float i1=0;
float i2=0;

float a=120;
float a2=240;

String fault;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

                                      // GET CODE:

    //Getting data from react app via firebase real time database
    //It gets data from api, every const has its own api

    //current1 api :  /test/current/current1
    //current2 api :  /test/current/current2
        
    if (Firebase.RTDB.getInt(&fbdo, "/test/current/vp1")) {
      if (fbdo.dataType() == "int") {
        vp1 = fbdo.floatData();
        Serial.println(vp1);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/test/current/vp2")) {
      if (fbdo.dataType() == "int") {
        vp2 = fbdo.floatData();
        Serial.println(vp2);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/test/current/vp3")) {
      if (fbdo.dataType() == "int") {
        vp3 = fbdo.floatData();
        Serial.println(vp3);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/test/current/va1")) {
      if (fbdo.dataType() == "int") {
        va1 = fbdo.floatData();
        Serial.println(va1);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/test/current/va2")) {
      if (fbdo.dataType() == "int") {
        va2 = fbdo.floatData();
        Serial.println(va2);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/test/current/va3")) {
      if (fbdo.dataType() == "int") {
        va3 = fbdo.floatData();
        Serial.println(va3);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/test/current/ip1")) {
      if (fbdo.dataType() == "int") {
        ip1 = fbdo.floatData();
        Serial.println(ip1);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/test/current/ip2")) {
      if (fbdo.dataType() == "int") {
        ip2 = fbdo.floatData();
        Serial.println(ip2);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/test/current/ip3")) {
      if (fbdo.dataType() == "int") {
        ip3 = fbdo.floatData();
        Serial.println(ip3);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/test/current/ia1")) {
      if (fbdo.dataType() == "int") {
        ia1 = fbdo.floatData();
        Serial.println(ia1);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }


    if (Firebase.RTDB.getInt(&fbdo, "/test/current/ia2")) {
      if (fbdo.dataType() == "int") {
        ia2 = fbdo.floatData();
        Serial.println(ia2);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/test/current/ia3")) {
      if (fbdo.dataType() == "int") {
        ia3 = fbdo.floatData();
        Serial.println(ia3);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    
    
    
    float rv1= vp1*cos(deg2rad(va1));
    float iv1= vp1*sin(deg2rad(va1));
    
    float rv2=vp2*cos(deg2rad(va2));
    float iv2=vp2*sin(deg2rad(va2));
    
    float rv3=vp3*cos(deg2rad(va3));
    float iv3=vp3*sin(deg2rad(va3));
    
    float ri1= ip1*cos(deg2rad(ia1));
    float ii1= ip1*sin(deg2rad(ia1));
    
    float ri2=ip2*cos(deg2rad(ia2));
    float ii2=ip2*sin(deg2rad(ia2));
    
    float ri3=ip3*cos(deg2rad(ia3));
    float ii3=ip3*sin(deg2rad(ia3));
    
    float ra= 1*cos(deg2rad(a));
    float ia=1*sin(deg2rad(a));
    
    
    float rio= ri1+ri2+ri3;
    float iio= ii1+ii2+ii3;
    
    Complex A(ra,ia);
    Complex A2(-0.5,-0.866);
    
    Complex Ia(ri1,ii1);
    Complex Ib(ri2,ii2);
    Complex Ic(ri3,ii3);
    
    Complex tempib(0,0);
    tempib=A*Ib;
    
    Complex tempic(0,0);
    tempic=Ic*A2;
    
    Complex tempib2(0,0);
    tempib2=A2*Ib;
    
    Complex tempic2(0,0);
    tempic2=A*Ic;
    
    
    
    Complex I1(0,0);
    Complex I2(0,0);
    
    
    
    Complex Io(rio,iio);    // zero seq of current
    Io = Io / 3;
    I1= (Ia + tempib + tempic) / 3;  // +ve seq of current
    I2= (Ia + tempib2 + tempic2) / 3;
    
    
    //NOW WORKING FOR VOLTAGE
    
    Complex Va(rv1,iv1);
    Complex Vb(rv2,iv2);
    Complex Vc(rv3,iv3);
    
    Complex tempvb(0,0);
    tempvb=A*Vb;
    
    Complex tempvc(0,0);
    tempvc=Vc*A2;
    
    Complex tempvb2(0,0);
    tempvb2=A2*Vb;
    
    Complex tempvc2(0,0);
    tempvc2=A*Vc;
    
    
    
    Complex V1(0,0);
    Complex V2(0,0);
    
    
    
    float rvo= rv1+rv2+rv3;
    float ivo= iv1+iv2+iv3;
    Complex Vo(rvo,ivo);    // zero seq of voltage
    Vo = Vo / 3;
    V1= (Va + tempvb + tempvc)/3;  // +ve seq of voltage
    V2= (Va + tempvb2 + tempvc2)/3;
    
    //polar form for sequence components
    
    int vmo=Vo.modulus();
    double vao=Vo.phase();
    
    int vm2=V1.modulus();  // previously, 1
    double v2a=V1.phase();
    
    int vm1=V2.modulus();
    double v1a=V2.phase();
    
    int imo=Io.modulus();
    double ioa=Io.phase();
    
    int im2=I1.modulus(); // previously, 1
    double i2a=I1.phase();
    
    int im1=I2.modulus();
    double i1a=I2.phase();
    
    //Serial.println(Io);
    //Serial.println(I1);
    //Serial.println(I2);
    //
    //
    //Serial.println(V2);
    //Serial.println(I2);
    Serial.println(imo);
    Serial.println(vmo);
    Serial.println(im2);
    Serial.println(vm2);
    
     
    
    if (imo==0 && (im1>0) && (im2>0) &&(((vp1==0)&&(vp2==0))||((vp1==0)&&(vp3==0))||((vp3==0)&&(vp2==0)))){
      fault = "DOUBLE LINE FAULT DETECTED";
      Serial.println("DOUBLE LINE FAULT DETECTED");
    }
    
    else if ((imo>0)&&(im2>0) && (im1>0) &&(((vp1==0)&&(vp2==0))||((vp1==0)&&(vp3==0))||((vp3==0)&&(vp2==0)))){
      fault = "DOUBLE LINE TO GROUND FAULT DETECTED";
      Serial.println("DOUBLE LINE TO GROUND FAULT DETECTED");
    }
    
    else if ((imo>0)&&(im2>0) && (im1>0) &&(((ip1==0)&&(ip2==0))||((ip1==0)&&(ip3==0))||((ip3==0)&&(ip2==0)))){

      fault = "SINGLE LINE TO GROUND FAULT DETECTED";
      Serial.println("SINGLE LINE TO GROUND FAULT DETECTED");
    }
    else if (imo == 0 && vmo == 0 && im2 == 0 && vm2 == 0 ){
      fault = "THREE PHASE FAULT DETECTED";
      Serial.println("THREE PHASE FAULT DETECTED");
    }


                                 // LOGIC
  //After getting data, it stores in some variables which in this case are intValue and floatValue

//  floatValueNew = floatValue + 5;
//  intValueNew = intValue + 5;


                                 // POST CODE

  //After apply particular conditions on variables which we got, now its time to post to react app via firebase

//  if (Firebase.RTDB.setInt(&fbdo, "test/current/int",)){
//      Serial.println("PASSED");
//      Serial.println("PATH: " + fbdo.dataPath());
//      Serial.println("TYPE: " + fbdo.dataType());
//    }
//    else {
//      Serial.println("FAILED");
//      Serial.println("REASON: " + fbdo.errorReason());
//    }
////    count++;
//    
//    // Write an Float number on the database path test/float
//    if (Firebase.RTDB.setFloat(&fbdo, "test/current/float",floatValue + 5)){
//      Serial.println("PASSED");
//      Serial.println("PATH: " + fbdo.dataPath());
//      Serial.println("TYPE: " + fbdo.dataType());
//    }
//    else {
//      Serial.println("FAILED");
//      Serial.println("REASON: " + fbdo.errorReason());
//    }

    if (Firebase.RTDB.setString(&fbdo, "test/current/str", fault)){
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
      }
      else {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
      }
  }
}

float deg2rad ( float ang)
{
  float rad=ang*0.0174533;
  return rad;
}
