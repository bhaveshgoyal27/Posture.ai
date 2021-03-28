#include <Wire.h>
#include <math.h>
#include <Arduino_JSON.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>                                                    // esp8266 library                                              // firebase library

#define FIREBASE_HOST "https://posture-9f0bf-default-rtdb.firebaseio.com/"                          // the project name address from firebase id
#define FIREBASE_AUTH "****************************"            // the secret key generated from firebase

#define WIFI_SSID "********************"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "*****************"                                    //password of wifi ssid

FirebaseData firebaseData;
FirebaseJson json;

// MPU6050 Slave Device Address
const uint8_t MPU6050SlaveAddress = 0x68;

// Select SDA and SCL pins for I2C communication 
const uint8_t scl = D6;
const uint8_t sda = D7;

// sensitivity scale factor respective to full scale setting provided in datasheet 
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131;

// MPU6050 few configuration register addresses
const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;

int16_t AccelX, AccelY, AccelZ, Temperature, GyroX, GyroY, GyroZ;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
  Firebase.reconnectWiFi(true);
  Wire.begin(sda, scl);
  MPU6050_Init();
}

void loop() {
  double Ax, Ay, Az, T, Gx, Gy, Gz;
  double pitch, roll, yaw;

  JSONVar pos;
  
  Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
  
  //divide each with their sensitivity scale factor
  Ax = (double)AccelX/AccelScaleFactor;
  Ay = (double)AccelY/AccelScaleFactor;
  Az = (double)AccelZ/AccelScaleFactor;
//  T = (double)Temperature/340+36.53; //temperature formula
//  Gx = (double)GyroX/GyroScaleFactor;
//  Gy = (double)GyroY/GyroScaleFactor;
//  Gz = (double)GyroZ/GyroScaleFactor;

  //Calculate Roll, Yaw, Pitch
  pitch = 180 * atan (Ax/sqrt(Ay*Ay + Az*Az))/M_PI;
  roll = 180 * atan (Ay/sqrt(Ax*Ax + Az*Az))/M_PI;
  yaw = 180 * atan (Az/sqrt(Ax*Ax + Ay*Ay))/M_PI;

//  Serial.print("Ax: "); Serial.print(pitch);
//  Serial.print(" Ay: "); Serial.print(roll);
//  Serial.print(" Az: "); Serial.println(yaw);
//  Serial.print(" T: "); Serial.print(T);
//  Serial.print(" Gx: "); Serial.print(Gx);
//  Serial.print(" Gy: "); Serial.print(Gy);
//  Serial.print(" Gz: "); Serial.println(Gz);

  pos[0] = pitch;
  pos[1] = roll;
  pos[2] = yaw;
  Serial.println(pos);
  
  Firebase.setFloat(firebaseData, "/MPU/pitch_roll_yaw", pitch); //setup path and send readings

  delay(100);
}

void I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t data){
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.write(data);
  Wire.endTransmission();
}

// read all 14 register
void Read_RawValue(uint8_t deviceAddress, uint8_t regAddress){
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, (uint8_t)14);
  AccelX = (((int16_t)Wire.read()<<8) | Wire.read());
  AccelY = (((int16_t)Wire.read()<<8) | Wire.read());
  AccelZ = (((int16_t)Wire.read()<<8) | Wire.read());
//  Temperature = (((int16_t)Wire.read()<<8) | Wire.read());
//  GyroX = (((int16_t)Wire.read()<<8) | Wire.read());
//  GyroY = (((int16_t)Wire.read()<<8) | Wire.read());
//  GyroZ = (((int16_t)Wire.read()<<8) | Wire.read());
}

//configure MPU6050
void MPU6050_Init(){
  delay(150);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SMPLRT_DIV, 0x07);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_1, 0x01);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_2, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_CONFIG, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_GYRO_CONFIG, 0x00);//set +/-250 degree/second full scale
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_CONFIG, 0x00);// set +/- 2g full scale
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_FIFO_EN, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_INT_ENABLE, 0x01);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SIGNAL_PATH_RESET, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_USER_CTRL, 0x00);
}
