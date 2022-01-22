#include "EmonLib.h" // Include Emon Library
EnergyMonitor emon1; // Create an instance


void setup()
{
Serial.begin(9600);

emon1.voltage(1, 550, -1.4); // 2 -Voltage: input pin, calibration, phase_shift
emon1.current(2, 10); // Current: input pin, calibration.

//For relay module
 pinMode(6, OUTPUT);// connected to In terminal of relay
}

void loop()
{
emon1.calcVI(20,2000); // Calculate all. No.of half wavelengths (crossings), time-out
emon1.serialprint(); // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)

float realPower = emon1.realPower; //extract Real Power into variable
float apparentPower = emon1.apparentPower; //extract Apparent Power into variable
float powerFActor = emon1.powerFactor; //extract Power Factor into Variable
float supplyVoltage = emon1.Vrms; //extract Vrms into Variable
float Irms = emon1.Irms; //extract Irms into Variable
float current1 = emon1.Irms;



if (Irms>15) {
  digitalWrite(6,LOW);// turn relay OFF
 delay(3000);// keep it ON for 3 seconds
}

else{
  digitalWrite(6, HIGH);// turn relay ON
  }

}
