//STM8S105
#include "route.h"


#define diffright 99
#define diffleft 100
#define Maniabilite_IR 80
#define Maniabilite_US_Side -0.1
#define Distance_US_Side 17
#define Delay_US 10
#define Distance_US_Front 30
extern u8 detflg;
extern volatile s8 Direction;                                 //Read-only
extern void delay(u32 ms);                    //delay in millsecond
extern void Motor_Left_Set(s8 power);              //Set motor power,from -100 to 100
extern void Motor_Right_Set(s8 power);
extern u16  Distance_Get(US_Channel_def channel);  //Get distance from ultrasonic detector in cm
extern void Direction_Get();
extern void Detection_Enable();                    //Enable the zone detection
extern void LED_SET( u16 Data );                    //Set the status of LEDs
extern void LED_ON( u16 Data );
extern void LED_OFF( u16 Data );

void route(void)
{
    MOTOR_LEFT_ON;
    MOTOR_RIGHT_ON;
    LED_SET(0x0000);
    u16 dcenter, dleft, dright;
    u8 usdata=0;
    while(1)
    {
        //Receive info
        delay(Delay_US);
        dcenter = Distance_Get(Center);
        delay(Delay_US);
        dright = Distance_Get(Right);
        delay(Delay_US);
        dleft = Distance_Get(Left);
        //Process info
        usdata=0;
        detflg++;
        if(detflg>30)
        {
            detflg=0;
            Detection_Enable();
        }
        if(dcenter < Distance_US_Front)
        {
            SetBit(usdata,1);
        }
        if(dright < Distance_US_Side)
        {
            SetBit(usdata,0);
        }
        if(dleft < Distance_US_Side)
        {
            SetBit(usdata,2);
        }
        //Motor Action
        switch(usdata)
        {
        case 0x00:
            //clear
            if (Direction >= 0)
            {
                Motor_Right_Set(diffright - Maniabilite_IR*Direction);
                Motor_Left_Set(diffleft);
            }
            else
            {
                Motor_Left_Set(diffleft + Maniabilite_IR*Direction);
                Motor_Right_Set(diffright);
            }
            break;
        case 0x01:
            //right
            Motor_Left_Set(Maniabilite_US_Side*diffleft);                  //...on tourne ?gauche.
            Motor_Right_Set(diffright);
            break;
        case 0x02:
            //center
            if(Direction==0)
            {
                if(dright >= dleft)
                {
                    Motor_Left_Set(diffleft);           //...on tourne ?droite.
                    Motor_Right_Set(-60);
                }
                else
                {
                    Motor_Left_Set(-60);                  //...on tourne ?gauche.
                    Motor_Right_Set(diffright);
                }
            }
            else
            {
                if(Direction > 0)
                {
                    Motor_Left_Set(diffleft);           //...on tourne ?droite.
                    Motor_Right_Set(-60);
                }
                else
                {
                    Motor_Left_Set(-60);                  //...on tourne ?gauche.
                    Motor_Right_Set(diffright);
                }
            }
            break;
        case 0x03:
            //center right
            Motor_Left_Set(-20);                      //...on tourne ?gauche.
            Motor_Right_Set(diffright);
            break;
        case 0x04:
            //left
            Motor_Right_Set(Maniabilite_US_Side*diffright);                  //...on tourne ?droite.
            Motor_Left_Set(diffleft);
            break;
        case 0x05:
            //left right
            if((dleft>10) &&(dright>10))
            {
                Motor_Right_Set(diffright);
                Motor_Left_Set(diffleft);
            }
            else
            {
                Motor_Left_Set(-diffleft);                  //...on marche ?arriere.
                Motor_Right_Set(-diffright);
                delay(200);
                Motor_Left_Set(-diffleft);                  //...on tourne ?arriere.
                Motor_Right_Set(diffright);
                delay(200);
            }
            break;
        case 0x06:
            //left center
            Motor_Left_Set(diffleft);                  //...on tourne ?gauche.
            Motor_Right_Set(-20);
            break;
        case 0x07:
            //deblock all
            Motor_Left_Set(-diffleft);                  //...on marche ?arriere.
            Motor_Right_Set(-diffright);
            delay(200);
            Motor_Left_Set(-diffleft);                  //...on tourne ?arriere.
            Motor_Right_Set(diffright);
            delay(200);
            break;
        }
    }
}

void final(void)
{
    disableInterrupts();
    Motor_Left_Set(-diffleft);
    Motor_Right_Set(-diffright);
    delay(50);
    MOTOR_LEFT_OFF;
    MOTOR_RIGHT_OFF;
    LED_ON(0xffff);
    BALLON_START;
    delay(1000);
    BALLON_STOP;
    while(1)
    {

    }
}

void BUMP_Left(void)
{
    LED_ON(0xff00);
    Motor_Left_Set(-diffleft);
    Motor_Right_Set(-diffright);
    delay(100);
    Motor_Left_Set(diffleft);
    Motor_Right_Set(-diffright);
    delay(100);
    //Motor_Left_Set(diffleft);
    //Motor_Right_Set(diffright);
    //delay(100);
}

void BUMP_Center(void)
{

}

void BUMP_Right(void)
{
    LED_ON(0x00ff);
    Motor_Left_Set(-diffleft);
    Motor_Right_Set(-diffright);
    delay(100);
    Motor_Left_Set(-diffleft);
    Motor_Right_Set(diffright);
    delay(100);
    //Motor_Left_Set(diffleft);
    //Motor_Right_Set(diffright);
    //delay(100);
}