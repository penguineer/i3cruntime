/*
** i3c Master-Implementation
**
** Author: Christof Schulze <christof.schulze@gmx.net>
*/

#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "i3c_master.h"

#include <unistd.h>


#include <string.h>
#include "slavelist.h"

#include <iostream>
#include "slave.h"
#include "i3c_commhandler.h"
/*

#include <wiringPi.h>
#include <wiringPiI2C.h>

#define MPU6050_GYRO_XOUT_H        0x43   // R
#define MPU6050_GYRO_YOUT_H        0x45   // R
#define MPU6050_GYRO_ZOUT_H        0x47   // R

#define MPU6050_PWR_MGMT_1         0x6B   // R/W
#define MPU6050_I2C_ADDRESS        0x68   // I2C*/


using namespace std;

int main()
{
    const char i2cbus[255]="/dev/i2c-1";
    uint8_t address;
   


    i3c_commhandler ch;
    ch.init ( i2cbus );


//     /* Spezifizieren der Slave-Adresse -> Kommunikation frei geben */
//     if ( ioctl ( fd, I2C_SLAVE, address ) < 0 ) {
//         perror ( "Failed to acquire bus access and/or talk to slave\n" );
//         exit ( 1 );
//     }


//     int fd = wiringPiI2CSetup ( MPU6050_I2C_ADDRESS );
//     if ( fd == -1 ) {
//         return 1;
//     }
// 
//     wiringPiI2CReadReg8 ( fd, MPU6050_PWR_MGMT_1 );
//     wiringPiI2CWriteReg16 ( fd, MPU6050_PWR_MGMT_1, 0 );
// 
//     float x,y,z;
// 
//     while ( true ) {
//         x = wiringPiI2CReadReg8 ( fd, MPU6050_GYRO_XOUT_H );
//         y = wiringPiI2CReadReg8 ( fd, MPU6050_GYRO_YOUT_H );
//         z = wiringPiI2CReadReg8 ( fd, MPU6050_GYRO_ZOUT_H );
// 
//         printf ( "x=%d   y=%d   z=%d", x,y,z );
//     }



    uint8_t wire[2];
//     assemble_packet ( create_packet ( 0xfe, 0x34, ODD, ST_START ), wire );
    printf ( "wire: %02x %02x \n", wire[0], wire[1] );

}

