/*
 * File:   usart16f628a.c
 * Author: roner
 *
 * Created on 21 de Abril de 2017, 14:22
 */



#define __XTAL_FREQ 4000000;
#include <xc.h>
#include <stdio.h>
#include "uart16f628a.h"


/*******functions*/

void ConfigGeneralInit();
void UsartBuff();
void UsartRead();
void ExternalInterrupt();


/******hardware map*******/

// this button needed to be pulse button 
//#define startcourse     PORTAbits.RA4  //  micro off start course    

/*****variable ****/
unsigned int pointzero;
unsigned int counter = 0x00;

char readvalue;

void main() {


    CMCON = 0x07; // desable comparator internal 
    OPTION_REG = 0x87; //disable pull ups and select pre scale as 1/256  


    /*****config I0s*/

    TRISA = 0x1f; //pins 0 util 4 as input   here is my button and pin RA7 as output 

    TRISBbits.TRISB1 = 0x01; // RB1 AS input 
    TRISBbits.TRISB7 = 0x00; // RB1 AS  output
    TRISBbits.TRISB0 = 0x01; // interrupt button TR




    PORTBbits.RB7 = 0x00; //start in value low
    PORTBbits.RB1 = 0x00;

    PORTBbits.RB0 = 0x00; // //input button 
    PORTAbits.RA0 = 0x00; // start RA0 in zero volts








    ConfigGeneralInit(); //start process usart init




    while (1) {






    }

}

/***auxiliar function ***/

void ConfigGeneralInit() {


    TXSTAbits.TXEN = 0x01; // enable transmit
    TXSTAbits.BRGH = 0x01; // select baud rate in high speed   
    TXSTAbits.SYNC = 0X00; // Confi as mode asynchronous 

    SPBRG = 0x19; // baudrate = (fosc/16*(x + 1)   9600 off baudrate

    RCSTAbits.SPEN = 0x01; // enable serial door
    RCSTAbits.CREN = 0x01; //enable continuous reception 


    PIE1bits.RCIE = 0x01; //enable reciver interrupt  
    PIR1bits.RCIF = 0x00; //clear flag  usart interruption 



    /*****external interruption*/

    INTCONbits.GIE = 0x01; // enable global interruption
    INTCONbits.PEIE = 0x01; //enable peripherial interruption 
    INTCONbits.INTE = 0x01; // enable external interrupt
    INTCONbits.INTF = 0x00; // clear flag off external interruption 


    /*******timer 0 interruption*****/

    INTCONbits.T0IE = 0x01; // enable timer 0 
    INTCONbits.T0IF = 0x00; // clear flag timer 0 

    /******Calc to timer 0*/
    //  scale as 1/256 
    // machine cicle equal 1E-6  0VERFLOW = (1E-6*256*2^8)  0VERFLOW= 65micro segundo 
    // building one seconde 1000/65E-6  = 15

    ei(); //enable general 

}

void UsartRead() {


    if (RCREG == 'a') {


        //PORTBbits.RB7 = 0xff;
    }







}

void UsartBuff() {

    if (!TXSTAbits.TRMT) { //  is full equal 0 and there is something on buffer 
        //Whilw buffer empty


    }





}

void Condition() {

    switch (PORTA) { //here reciver value of port A and take a decision




    }


}

/**************interruptions**********/

void interrupt UsartInterrupt() {



    /******usart interruption ***********/


    if (PIR1bits.RCIF == 0x01) {

        PIR1bits.RCIF = 0x00; //clear flag  that was interrupted

        UsartRead();







    }




    /***external interruption**/

    if (INTCONbits.INTF == 0x01) {

        INTCONbits.INTF = 0x00; //clear flag 

        //  while (PORTAbits.RA4 == 0x00) {

        PORTBbits.RB7 = 0x01;

        //}


    }







    /*****TIMER ZERO INTERRUPTION*****/

    if (INTCONbits.T0IF == 0x01) {

        INTCONbits.T0IF = 0x00; //clear flag timer zero overflow

        counter++;

        if (counter == 0x0f) { //  counter equal 15 decimal there's 1 second



            PORTAbits.RA7 = ~PORTAbits.RA7; // It's just make a led blink
            counter = 0x00;
        }


    }













}











