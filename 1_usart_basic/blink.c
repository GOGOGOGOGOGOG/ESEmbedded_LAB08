#include <stdint.h>
#include "reg.h"

void led_init(unsigned int a)
{
//SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTD)); //set RCC Init 
// set 12 13  14 for output mode
//CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_MODER_OFFSET, MODERy_1_BIT(14)|MODERy_1_BIT(13));

SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTD));
CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_MODER_OFFSET, MODERy_1_BIT(a));
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_MODER_OFFSET, MODERy_0_BIT(a));
//OT led pin = 0 => Output push-pull
CLEAR_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OTYPER_OFFSET, OTy_BIT(a));
//OSPEEDR led pin = 11 => High speed
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(a));
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(a));
//PUPDR led pin = 01 => no pull-up,NO pull-down
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(a));
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(a));

}

int GPIO_init (unsigned int GPIO_PORTx , unsigned int GPIO_Pinx , GPIO_InitDef * GPIO_initstruct )
{

SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTx));

if(GPIO_initstruct){


  if(GPIO_initstruct->GPIO_Mode == GPIO_Mode_IN )
  {
  CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_MODER_OFFSET, MODERy_1_BIT(GPIO_Pinx));
  CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_MODER_OFFSET, MODERy_0_BIT(GPIO_Pinx));
  }
  else if(GPIO_initstruct->GPIO_Mode ==GPIO_Mode_OUT)
  {
  CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_MODER_OFFSET, MODERy_1_BIT(GPIO_Pinx));
  SET_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_MODER_OFFSET, MODERy_0_BIT(GPIO_Pinx));
  }
  else if(GPIO_initstruct->GPIO_Mode ==GPIO_Mode_AF)
  {
  SET_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_MODER_OFFSET, MODERy_1_BIT(GPIO_Pinx));
  CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_MODER_OFFSET, MODERy_0_BIT(GPIO_Pinx));
  }
  else if(GPIO_initstruct->GPIO_Mode ==GPIO_Mode_AN)
  {
  SET_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_MODER_OFFSET, MODERy_1_BIT(GPIO_Pinx));
  SET_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_MODER_OFFSET, MODERy_0_BIT(GPIO_Pinx));
  }
  else 
  {
	   return GPIO_SET_fail;
 }
/* GPIO_Type_def */

  if(GPIO_initstruct->GPIO_OType == GPIO_Type_pp ) 
  {
  CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_MODER_OFFSET, OTy_BIT(GPIO_Pinx));
  }
  else if(GPIO_initstruct->GPIO_OType==GPIO_Type_OD)
  {
  SET_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_MODER_OFFSET, OTy_BIT(GPIO_Pinx));
  }
 else 
  {
  return GPIO_SET_fail;
  }
 /* GPIO_SPEED_def */

 if(GPIO_initstruct->GPIO_Speed ==GPIO_High_speed)
 {
  SET_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(GPIO_Pinx));
  SET_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(GPIO_Pinx));
 }
 else if(GPIO_initstruct->GPIO_Speed ==GPIO_Fast_speed)
 { 
  SET_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(GPIO_Pinx));
  CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(GPIO_Pinx));
 }
 else if(GPIO_initstruct->GPIO_Speed ==GPIO_Medium_speed)
 {
  CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(GPIO_Pinx));
  SET_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(GPIO_Pinx));
 }
  else if(GPIO_initstruct->GPIO_Speed ==GPIO_Low_speed)
 {
  CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(GPIO_Pinx));
  CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(GPIO_Pinx));
 }
  else 
  {

   return GPIO_SET_fail;
}

/*GPIO_PUPD_def*/
if(GPIO_initstruct->GPIO_PuPd==GPIO_PuPd_nopull)
{
//PUPDR led pin = 01 => no pull-up,NO pull-down
CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(GPIO_Pinx));
CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(GPIO_Pinx));
}

else if(GPIO_initstruct->GPIO_PuPd ==GPIO_PuPd_up)
{
CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(GPIO_Pinx));
SET_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(GPIO_Pinx));

}
else if(GPIO_initstruct->GPIO_PuPd ==GPIO_PuPd_down)
{
SET_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(GPIO_Pinx));
CLEAR_BIT(GPIO_BASE(GPIO_PORTx) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(GPIO_Pinx));
}
else 
{
return GPIO_SET_fail;
}

}
return GPIO_SET_READY;
}

void user_button_init(void)
{
	//int a=0;
	//SET RCC parameter
SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTA));
  // set input mode
CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_MODER_OFFSET, MODERy_1_BIT(0));
CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_MODER_OFFSET, MODERy_0_BIT(0));
  // SET Output push pull
CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_OTYPER_OFFSET, OTy_BIT(0));
  //set high speed 
SET_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_1_BIT(0));
SET_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_OSPEEDR_OFFSET, OSPEEDRy_0_BIT(0));
  // set pull down 
SET_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_PUPDR_OFFSET, PUPDRy_1_BIT(0));
CLEAR_BIT(GPIO_BASE(GPIO_PORTA) + GPIOx_PUPDR_OFFSET, PUPDRy_0_BIT(0));

//return a;

}

void blink(unsigned int led)
{
    	/*  High speed 
		SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OSPEEDR_OFFSET, PUPDRy_0_BIT(15));
	SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_OSPEEDR_OFFSET, PUPDRy_0_BIT(15));
	     */

		led_init(led);
		
	unsigned int i;
    //unsigned int cnt=0;  //READ_BIT(GPIO_BASE(GPIO_PORTA)+ GPIOx_IDR_OFFSET ,IDR_BIT(0));
	while (1)
	{
		//set GPIOD15
	  SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BSy_BIT(led));
     
		for (i = 0; i < 100000; i++) 
			;

		//reset GPIOD15
	   SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BRy_BIT(led));
   
		for (i = 0; i < 100000; i++) 
			;
        
  
	}
}

void Delay(unsigned int nDelay)
{
	unsigned int i, j;
	int k = 0;

	for (i = 0; i < nDelay; i++)
		;

	for (j = 0; j < 6144; j++)
		;

	k++;
}

void blink_count (unsigned int led,int count)
{
    //unsigned int i;
    unsigned int cnt1=0;
	led_init(led);
	while (cnt1<count)
	{
		//set GPIOD15
	  SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BSy_BIT(led));
     
	    //for (i = 0; i < 50000; i++) 
			;
			Delay(50000)
             ;
		//reset GPIOD15
	   SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BRy_BIT(led));
     
	    //for (i = 0; i < 50000; i++) 
			;
			Delay(50000)
			 ;
         ++cnt1;
  
	}

	
}
void close_light(int led)
{
//unsigned int i;
	 SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BRy_BIT(led));
	Delay(50000);
}
void turn_light_all (void)
{
	unsigned int i;
	int32_t led = 0xCDEF;
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BSy_BIT((int) ((led>>12&0x0C))));
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BSy_BIT((int)((led>>8&0x0D))));
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BSy_BIT((int)((led>>4&0x0E))));
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BSy_BIT((int)((led&0x0F))));
   for (i = 0; i < 1000000; i++) 
			;
}
void close_light_all(void)
{
	unsigned int i;
	int32_t led = 0xCDEF;
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BRy_BIT((int) ((led>>12&0x0C))));
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BRy_BIT((int)((led>>8&0x0D))));
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BRy_BIT((int)((led>>4&0x0E))));
SET_BIT(GPIO_BASE(GPIO_PORTD) + GPIOx_BSRR_OFFSET, BRy_BIT((int)((led&0x0F))));
 for (i = 0; i < 1000000; i++) 
			;
}
void turn_light_multiple (int32_t * led_ptr){
unsigned int i;

if(led_ptr){

    if ((*led_ptr)==0x0C)
    {
    SET_BIT(GPIO_BASE(GPIO_PORTD)+GPIOx_BSRR_OFFSET,BSy_BIT(0x0C));
     led_ptr++;
    }
    else
    {
      led_ptr++;
    }
    
   
     if((*led_ptr)==0x0D)
     {
         
      SET_BIT(GPIO_BASE(GPIO_PORTD)+GPIOx_BSRR_OFFSET,BSy_BIT(0x0D));
     led_ptr++;
     }     
     else
     {
       led_ptr++;
     }
     

     if((*led_ptr)==0x0E)
     {

     SET_BIT(GPIO_BASE(GPIO_PORTD)+GPIOx_BSRR_OFFSET,BSy_BIT(0X0E));
     led_ptr++;

      }

      else
      {
        led_ptr++;
      }



     if((*led_ptr)==0x0F)
     {
       SET_BIT(GPIO_BASE(GPIO_PORTD)+GPIOx_BSRR_OFFSET,BSy_BIT(0x0F));
       led_ptr++;
     }
     else 
     {

       led_ptr++;
     }

   for (i = 0; i < 1000000; i++) 
			;
      
 
}

}