/* FSR testing sketch. 
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */
#include <math.h>

// int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
double fsrVoltage;     // the analog reading converted to voltage
double fsrResistance;  // The voltage converted to resistance, can be very big so make "long"
double fsrConductance; 
double fsrForce;       // Finally, the resistance converted to force
 
void GetPressure(uint8_t fsrPin);

void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}

void loop(void)
{
  GetPressure(0);
  delay(1000);
  GetPressure(1);
  delay(1000);
  Serial.println("<><><><>");
}
 
void GetPressure(uint8_t fsrPin) {
  Serial.print("Sensor=");
  Serial.print(fsrPin);
  Serial.print(" | ");
  fsrReading = analogRead(fsrPin);
  Serial.print("Analog=");
  Serial.print(fsrReading);
  Serial.print(" | ");
 
  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
  // fsrValue = map(fsrReading, 0, 1023, 0, 5000);
  // fsrVoltage = (double)fsrValue / 1000;
  fsrVoltage = (double)fsrReading * 5 / 1023;
  Serial.print("Voltage[V]=");
  Serial.print(fsrVoltage);  
  Serial.print(" | ");
 
  if (fsrVoltage == 0) {
    Serial.println("Resistance[KOhm]=inf | Force[g]=0");  
  } else {
    // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
    // FSR = (Vcc * R / V) - R
    // so FSR = ((Vcc - V) * R) / V        yay math!
    fsrResistance = (5 - fsrVoltage) * 10 / fsrVoltage;
    Serial.print("Resistance[KOhm]=");
    Serial.print(fsrResistance);
    Serial.print(" | ");
 
    fsrConductance = 1 / (fsrResistance)/100;
    if (fsrConductance < 1.00){
      fsrForce = 1 * pow(10,7)* pow(fsrConductance,3) + 2 * pow(10,6) * pow(fsrConductance,2) + 123524 * (fsrConductance) + 75.684;
    }
    else{
      fsrForce = -1 * pow(10,9)* pow(fsrConductance,3) + 2 * pow(10,7) * pow(fsrConductance,2) + 37916 * (fsrConductance) + 4.4801;
    }
    
    Serial.print("Force[g]=");
    Serial.print(fsrForce);
    Serial.println(".");
  }
}
