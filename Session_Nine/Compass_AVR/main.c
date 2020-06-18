/*
 * mpu9250_compass.cpp
 *
 * Created: 6/17/2020 12:25:46 PM
 * Author : Mohamed
 */ 
#define F_CPU	16000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <math.h>
#define PI 3.14
#include "lcd.h"
#include "i2c.h"

char buffer[15];

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

void compassInit(){
	
	_delay_ms(150);										/* Power up time >100ms */
	I2C_Start_Wait(0x18);//0b1101000 ,0001 1000


	// Set by pass mode for the magnetometers
	I2C_Write(0x37);
	I2C_Write(0x02);
	I2C_Stop();
	I2C_Start_Wait(0x18);
	// Request continuous magnetometer measurements in 16 bits
	I2C_Write(0x0A);
	I2C_Write(0x16);
	I2C_Stop();
    //  LCD_String("after init");

}
void Compass_Start_Loc()
{
	I2C_Start(0x18);								/* I2C start with device write address */
	I2C_Write(0x04);							/* Write start location address from where to read */
	I2C_Repeated_Start(0x19);							/* I2C start with device read address */

}
int main(void)
{
	LCD_Init();
	LCD_Command(0xC0);
	

    I2C_Init();	
										/* Initialize I2C */
    compassInit();
	_delay_ms(500);
    while (1) 
    {
		static uint16_t count=0;
		//LCD_Command(0x01);	  
		  uint8_t ST1;
		

		  do
		  {

			  	I2C_Start(0x18);	
			    I2C_Write(0x02);							/* I2C start with device read address */							/* I2C start with device read address */

				I2C_Repeated_Start(0x19);							/* I2C start with device read address */
		 	    ST1=I2C_Read_Nack();

			    I2C_Stop();


		  }
		  while (!(ST1&0x01));
		  		LCD_Command(0x80);
		sprintf(buffer,"count=%d",count++);
		LCD_String(buffer);
			     //LCD_String("after while");

			Compass_Start_Loc();
							/* I2C start with device read address */
							
	    	int16_t  mx =-(int16_t)((I2C_Read_Ack()<<8)|I2C_Read_Ack());
    					 
		 	int16_t  my =-(int16_t)(I2C_Read_Ack()<<8)|I2C_Read_Ack();
			
			
			int16_t  mz =-(I2C_Read_Ack()<<8) | I2C_Read_Nack();
			
			 
		//LCD_String("after 2nd read");

		 I2C_Stop();
        double angle = atan2((double) my, (double)mx) * (180 / PI) + 180;
		LCD_Command(0xC0);
	  // double angle =(double) atan2(my, mx);
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"H=%d,x=%d y=%d z=%d",(int)angle,mx,my,mz);
		LCD_String(buffer);
		 
		_delay_ms(1000);
    }
}

