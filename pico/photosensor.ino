#define pRes                 A1
#define MAX_ADC_READING      1023
#define ADC_REF_VOLTAGE      3.26
#define REF_RESISTANCE       9950  // measure this for best results
#define LUX_CALC_SCALAR      12518931
#define LUX_CALC_EXPONENT    -1.405
#define ADJ_Value            0.865
#define ARRAY_SIZE           20

int dataCollection[ARRAY_SIZE];
int counter = 0;

float toLux(int value){
  if(value==MAX_ADC_READING){
    return 600000.0;
  }
  float adjustedVoltage = ADC_REF_VOLTAGE * ADJ_Value;
  float resistorVoltage = (float)value / MAX_ADC_READING * adjustedVoltage;
  float ldrVoltage = adjustedVoltage - resistorVoltage;
  float ldrResistance = ldrVoltage/resistorVoltage * REF_RESISTANCE;
  float ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);
  return ldrLux;
}

void setup(){

  Serial.begin(9600);

  //Photoresistor  
  pinMode(pRes, INPUT);

}

int arithmeticMedian() {
  int lux;
  for (int i = 0; i < ARRAY_SIZE; i++) {
    lux = lux + dataCollection[i];
  }
  lux = lux / ARRAY_SIZE;
  return lux;
}

void loop() {
  
  //Photoresistor
  int value = analogRead(pRes);
  int vlux = toLux(value);

  if (counter == ARRAY_SIZE){
    int meanValue = arithmeticMedian();
    Serial.println(meanValue);
    
    counter=0;
  }
  
  dataCollection[counter] = vlux;
  counter++;
  
  delay(80);
}