//STM8S105
#include "route.h"
u8 Direction;                                 //Read-only
extern void delay(u32 ms);                    //delay in millsecond
extern void Motor_Left_Set(s8 power);              //Set motor power,from -100 to 100
extern void Motor_Right_Set(s8 power);
extern u16  Distance_Get(US_Channel_def channel);  //Get distance from ultrasonic detector in cm
extern void Detection_Enable();                    //Enable the zone detection
extern void LED_SET( u16 Data );                    //Set the status of LEDs
extern void LED_ON( u16 Data );
extern void LED_OFF( u16 Data );

void route(void)
{
    u16 a=0;
    while(1)
    {
        //a=Distance_Get(Left);
        //LED_SET(a++);
        LED_SET(Direction);
        delay(100);
    }
}

void final(void)
{
    disableInterrupts();
    MOTOR_LEFT_OFF;
    MOTOR_RIGHT_OFF;
    while(1)
    {

    }
}

void BUMP_Left(void)
{

}

void BUMP_Center(void)
{

}

void BUMP_Right(void)
{

}