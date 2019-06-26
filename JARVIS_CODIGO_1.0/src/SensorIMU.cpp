#include "SensorIMU.h"

SensorIMU::SensorIMU(){
  //  
}

void SensorIMU::start(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  
  Wire.write(0); 
  Wire.endTransmission(true);
}

//Função Nescessaria para chamar o IMU
void SensorIMU::solicitarIMU(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);  
}

//Atribuição de valores do IMU
void SensorIMU::setIMU(){
  solicitarIMU(); 
  acX = Wire.read() << 8 | Wire.read();
  acY = Wire.read() << 8 | Wire.read();
  acZ = Wire.read() << 8 | Wire.read();
  gyX = Wire.read() << 8 | Wire.read();
  gyY = Wire.read() << 8 | Wire.read();
  gyZ = Wire.read() << 8 | Wire.read();
}

//Função de Retorno de Valor Expecifico do IMU (AcX)
double SensorIMU::getValorAcX(){ 
  setIMU(); 
  return acX; 
}

//Função de Retorno de Valor Expecifico do IMU (AcY)
double SensorIMU::getValorAcY(){ 
  setIMU(); 
  return acY; 
}

//Função de Retorno de Valor Expecifico do IMU (AcZ)
double SensorIMU::getValorAcZ(){ 
  setIMU(); 
  return acZ; 
}

//Função de Retorno de Valor Expecifico do IMU (GyX)
double SensorIMU::getValorGyX(){
  setIMU(); 
  return gyX;
}

//Função de Retorno de Valor Expecifico do IMU (GyY)
double SensorIMU::getValorGyY(){
  setIMU(); 
  return gyY;
}

//Função de Retorno de Valor Expecifico do IMU (GyZ)
double SensorIMU::getValorGyZ(){
  setIMU(); 
  return gyZ;
}

//Imprimir dados do Acelerômetro (IMU)
void SensorIMU::printImuA(){
  Serial.print("AcX = "); 
  Serial.print(getValorAcX());
  Serial.print(" | AcY = "); 
  Serial.print(getValorAcY());
  Serial.print(" | AcZ = "); 
  Serial.println(getValorAcZ()); 
}

//Imprimir dados do Giroscópio (IMU)
void SensorIMU::printImuG(){
  Serial.print("GyX = "); 
  Serial.print(getValorGyX());
  Serial.print(" | GyY = "); 
  Serial.print(getValorGyY());
  Serial.print(" | GyZ = "); 
  Serial.println(getValorGyZ()); 
}

//Imprimir todos dados do Acelerômetro e Giroscópio (IMU)
void SensorIMU::printImuTudo(){
  Serial.print("AcX = "); 
  Serial.print(getValorAcX());
  Serial.print(" | AcY = "); 
  Serial.print(getValorAcY());
  Serial.print(" | AcZ = "); 
  Serial.print(getValorAcZ());
  Serial.print(" | GyX = "); 
  Serial.print(getValorGyX());
  Serial.print(" | GyY = "); 
  Serial.print(getValorGyY());
  Serial.print(" | GyZ = "); 
  Serial.println(getValorGyZ()); 
}
