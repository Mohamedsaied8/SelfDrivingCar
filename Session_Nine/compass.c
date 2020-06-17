#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
#define PI 3.14159265
#define COMPASS_REG_MODE   0x02
#define COMPASS_MODE_CONTINOUS  0x00
#define COMPASS_REG_LSB_X  0x03
#define COMPASS_REG_MSB_X   0x04
#define COMPASS_REG_LSB_Y  0x05
#define COMPASS_REG_MSB_Y 0x06
#define COMPASS_REG_LSB_Z 0x07
#define COMPASS_REG_MSB_Z	0x08
#define COMPASS_CNTL   0x0A
void checkRC(int rc, char *text) {
  if (rc < 0) {
    printf("Error: %s - %d\n", text, rc);
    exit(-1);
  }
}

int main(int argc, char *argv[]) {
  printf("IMU Compass  starting\n");
  // Setup Wiring Pi
 // Open an I2C connection
  int fd = wiringPiI2CSetup(0x0C);
  checkRC(fd, "wiringPiI2CSetup");

 wiringPiI2CWriteReg8(fd,0x37,0x02);
 wiringPiI2CWriteReg8(fd,COMPASS_CNTL,0x16);


int8_t adjx=wiringPiI2CReadReg8(fd,0x10);
int8_t adjy=wiringPiI2CReadReg8(fd,0x11);

while(1){
 uint8_t ST1;
 
 do{
   ST1=wiringPiI2CReadReg8(fd, 0x02);
 }while(!(ST1&0x01));
 
  puts("reading"); 
  int16_t x=-(int16_t)((wiringPiI2CReadReg8(fd, COMPASS_REG_MSB_X) << 8 )|(wiringPiI2CRead(fd)));
  
  int16_t y =-(int16_t) ((wiringPiI2CRead(fd)<<8) | (wiringPiI2CRead(fd)));
  int16_t  z =-(int16_t) (( wiringPiI2CRead(fd)<<8)|(wiringPiI2CRead(fd)));

   int16_t x_sens=x*((((adjx-128)*0.5)/128)+1); 
   int16_t y_sens=y*((((adjy-128)*0.5)/128)+1);
   
   double angle = atan2((double) y_sens, (double)x_sens) * (180 / PI) + 180;
 
   printf("yaw=%f,x=%d, y=%d, z=%d \n",angle,x_sens, y_sens, z);
   sleep(.1);

  }

  return 0;
}


