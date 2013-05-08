/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

#define  MOTOR_PORT                 GPIOB
#define  MOTOR_LEFT_EN_PIN          GPIO_PIN_1
#define  MOTOR_RIGHT_EN_PIN         GPIO_PIN_3
#define  MOTOR_LEFT_ON              MOTOR_PORT->ODR |= MOTOR_LEFT_EN_PIN
#define  MOTOR_RIGHT_ON             MOTOR_PORT->ODR |= MOTOR_RIGHT_EN_PIN
#define  MOTOR_LEFT_OFF             MOTOR_PORT->ODR &=~MOTOR_LEFT_EN_PIN
#define  MOTOR_RIGHT_OFF            MOTOR_PORT->ODR &=~MOTOR_RIGHT_EN_PIN
#define  LED_PORT                   GPIOA
#define  LED_RED                    GPIO_PIN_6
#define  LED_YELLOW                 GPIO_PIN_5
#define  LED_GREEN                  GPIO_PIN_4
#define  LED_RED_ON                 LED_PORT->ODR |= LED_RED
#define  LED_RED_OFF                LED_PORT->ODR &=~LED_RED
#define  LED_YELLOW_ON              LED_PORT->ODR |= LED_YELLOW
#define  LED_YELLOW_OFF             LED_PORT->ODR &=~LED_YELLOW
#define  LED_GREEN_ON               LED_PORT->ODR |= LED_GREEN
#define  LED_GREEN_OFF              LED_PORT->ODR &=~LED_GREEN
#define  US_PORT                    GPIOD
#define  US_LEFT                    GPIO_PIN_0
#define  US_CENTER                  GPIO_PIN_2
#define  US_RIGHT                   GPIO_PIN_6
#define  DETZ_PORT                  GPIOD
#define  DETZ_PIN                   GPIO_PIN_4
typedef enum
{
    Left    = US_LEFT,
    Center  = US_CENTER,
    Right   = US_RIGHT,
}US_Channel_def;

u8 SPI_Rev=0;