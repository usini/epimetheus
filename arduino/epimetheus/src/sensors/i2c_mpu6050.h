/*
  MPU6050 - 6-DoF Accelerometer and Gyro
  Informations : https://www.adafruit.com/product/3886
  Library  : Adafruit MPU6050
*/
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 sensors_mpu6050[2];

bool setup_mpu6050(int id) {
    byte address = 0x00;
    if(id == 0) {
        address = MPU6050_0_ADDR;
    } else {
        address = MPU6050_1_ADDR;
    }

    bool check = false;
    check = sensors_mpu6050[id].begin(address);
    sensors_mpu6050[id].setAccelerometerRange(MPU6050_RANGE_8_G);
    sensors_mpu6050[id].setGyroRange(MPU6050_RANGE_500_DEG);
    sensors_mpu6050[id].setFilterBandwidth(MPU6050_BAND_21_HZ);
    return check;
}

void update_mpu6050() {
    for(int id = 0; id < 2; id++) {
        sensors_event_t a, g, temp;
        sensors_mpu6050[id].getEvent(&a, &g, &temp);
        sensors_mpu6050_temp[id] = temp.temperature;
        sensors_mpu6050_acc_x[id] = a.acceleration.x;
        sensors_mpu6050_acc_y[id] = a.acceleration.y;
        sensors_mpu6050_acc_z[id] = a.acceleration.z;
        sensors_mpu6050_gyro_x[id] = g.gyro.x;
        sensors_mpu6050_gyro_y[id] = g.gyro.y;
        sensors_mpu6050_gyro_z[id] = g.gyro.z;
    }
}