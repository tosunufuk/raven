#include <Wire.h>

const int MPU = 0x68; /* constant int which stores I2C address */
int16_t accelerometer_x, accelerometer_y, accelerometer_z, gyro_x, gyro_y, gyro_z, temperature; /* variables to store read values */

void setup() {

  Serial.begin(9600);

  Wire.begin();

  Serial.println("Starting MPU6050....");

  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  Serial.println("Setting DLPF on MPU6050.... (0x06)");
  Wire.beginTransmission(MPU);
  Wire.write(0x1A);
  Wire.write(0x06);
  Wire.endTransmission();

  Serial.println("Using full scale range of the gyroscope (1B register) on MPU6050 as default.... (0x00)");
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0x00);
  Wire.endTransmission();
  
  Serial.println("Using full scale range of the accelerometer (1C register) on MPU6050 as default.... (0x00)");
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0x00);
  Wire.endTransmission();

  delay(300);
  
}

void loop() {
  Wire.beginTransmission(MPU); /* begins the transmission to the I2C slave device with the given 7 -*/
  /*- bit address */
  Wire.write(0x3B); /* send start with register 0x3B ACCEL_XOUT_H */
  Wire.endTransmission(false); /* when used with false flag it means reset instead of stop*/
  Wire.requestFrom(MPU, 14, true); /* request from <MPU> addressed slave <14> amount of bytes and <true> -*/
  /*- parameter has the same effect with endTransmission which is to stop and release theI2C bus -*/
  /*- requested bytes above can be read. two registers are read and assigned to the same variable. since -*/
  /*- each register is 1 byte, 14 bytes requested will be enuoght for 7 variables */
  accelerometer_x = Wire.read() << 8 | Wire.read(); /* read registers ACCEL_XOUT_H 0x3B and ACCEL_XOUT_L 0x3C */
  accelerometer_y = Wire.read() << 8 | Wire.read(); /* read registers ACCEL_YOUT_H 0x3D and ACCEL_YOUT_L 0x3E */
  accelerometer_z = Wire.read() << 8 | Wire.read(); /* read registers ACCEL_ZOUT_H 0x3F and ACCEL_ZOUT_L 0x40 */
  temperature = Wire.read() << 8 | Wire.read(); /* read registers TEMP_OUT_H 0x41 and TEMP_OUT_L 0x42 */
  gyro_x = Wire.read() << 8 | Wire.read(); /* read registers GYRO_XOUT_H 0x43 and GYRO_XOUT_L 0x44 */
  gyro_y = Wire.read() << 8 | Wire.read(); /* read registers GYROXOUT_H 0x45 and  GYRO_XOUT_L 0x46 */
  gyro_z = Wire.read() << 8 | Wire.read(); /* read registers GYRO_XOUT_H 0x47 and  GYRO_XOUT_L 0x48 */

  Serial.print("Raw Accelerometer: ");
  Serial.print(" X = "); Serial.print(accelerometer_x);
  Serial.print(" | Y = "); Serial.print(accelerometer_y);
  Serial.print(" | Z = "); Serial.println(accelerometer_z);

  Serial.print("Raw Gyroscope: ");
  Serial.print(" X = "); Serial.print(gyro_x);
  Serial.print(" | Y = "); Serial.print(gyro_y);
  Serial.print(" | Z = "); Serial.println(gyro_z);

  Serial.print("Temperature: "); Serial.println(temperature / 340 + 36.53); /* MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2 page 30 of 46 */

  Serial.println(" ");

  delay(1000);
}
