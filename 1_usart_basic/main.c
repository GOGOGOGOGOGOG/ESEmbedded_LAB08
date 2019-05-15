#include <stdint.h>
#include "reg.h"
#include "blink.h"
void init_usart1(void)
{

    SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTB));
    GPIO_InitDef GPIO_initstructure ;
    GPIO_initstructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_initstructure.GPIO_OType = GPIO_Type_pp;
	GPIO_initstructure.GPIO_PuPd = GPIO_PuPd_up;
	GPIO_initstructure.GPIO_Speed = GPIO_Medium_speed;
	GPIO_init(GPIO_PORTB,GPIO_Pin(6),&GPIO_initstructure);
	
    GPIO_InitDef GPIO_initstructure1 ;
    GPIO_initstructure1.GPIO_Mode = GPIO_Mode_AF;
    GPIO_initstructure1.GPIO_OType = GPIO_Type_pp;
	GPIO_initstructure1.GPIO_PuPd = GPIO_PuPd_up;
	GPIO_initstructure1.GPIO_Speed = GPIO_Medium_speed;
	GPIO_init(GPIO_PORTB,GPIO_Pin(7),&GPIO_initstructure1);
    SET_BIT(RCC_BASE + RCC_APB2ENR_OFFSET, USART1EN);
	//SET_BIT(RCC_BASE + RCC_APB2ENR_OFFSET, SYSCFGEN_BIT);
    WRITE_BITS( GPIO_BASE(GPIO_PORTB)+GPIOx_AFRL_OFFSET,AFRLy_3_BIT(7),AFRLy_0_BIT(7),0b000111);
	WRITE_BITS( GPIO_BASE(GPIO_PORTB)+GPIOx_AFRL_OFFSET,AFRLy_3_BIT(6),AFRLy_0_BIT(6),0b000111);

	/*
	//PB6 PB7

	//RCC EN GPIOB
	//??????

	//GPIO Configurations
	//??????

	//RCC EN USART1
	//?????? 

	//Baud
	*/
	const unsigned int BAUD = 115200;
	const unsigned int SYSCLK_MHZ = 168;
	const double USARTDIV = SYSCLK_MHZ * 1.0e6 / 16 / BAUD;

	const uint32_t DIV_MANTISSA =  (uint32_t)USARTDIV;
	const uint32_t DIV_FRACTION =  (uint32_t)((USARTDIV-DIV_MANTISSA)*16);
  
	//USART  Configurations
	WRITE_BITS(USART1_BASE+USART_BRR_OFFSET,DIV_MANTISSA_11_BIT,DIV_MANTISSA_0_BIT,DIV_MANTISSA);
	WRITE_BITS(USART1_BASE+USART_BRR_OFFSET,DIV_FRACTION_3_BIT,DIV_FRACTION_0_BIT,DIV_FRACTION);

	//SET_BIT(USART1_BASE+USART_SR_OFFSET,TXE_BIT);
	//SET_BIT(USART1_BASE+USART_SR_OFFSET,RXNE_BIT);
 
    SET_BIT(USART1_BASE+USART_CR1_OFFSET ,UE_BIT);
	SET_BIT(USART1_BASE+USART_CR1_OFFSET ,TE_BIT);
    SET_BIT(USART1_BASE+USART_CR1_OFFSET ,RE_BIT);
	SET_BIT(USART1_BASE+ USART_CR1_OFFSET,RXNE_BIT);
	//ORE 前一個尚未傳完 下一個就準備要進來 這樣會有漏字的情況 所以就需要所謂的overrun error 當出現此情況時 這個ORE bits就會出現  


	WRITE_BITS(SYSCFG_BASE + SYSCFG_EXTICR1_OFFSET, EXTI0_3_BIT, EXTI0_0_BIT,);
	 
    SET_BIT(EXTI_BASE + EXTI_IMR_OFFSET, 0); // Interrupt request fomr line 0 NOT masked
	CLEAR_BIT(EXTI_BASE + EXTI_RTSR_OFFSET, 0); // Disable Rising trigger
    SET_BIT(EXTI_BASE + EXTI_FTSR_OFFSET, 0); // Enable Falling trigger

    SET_BIT(NVIC_ISER_BASE + NVIC_ISERn_OFFSET(1), 5); // Enable IRQ37

}

void usart1_send_char(const char ch)
{
	while(!READ_BIT(USART1_BASE+USART_SR_OFFSET,TXE_BIT))
     ;
  REG(USART1_BASE+USART_DR_OFFSET)=ch;
     

	


}

char usart1_receive_char(void)
{
	while(!READ_BIT(USART1_BASE+USART_SR_OFFSET,RXNE_BIT))
     ;
	 return (char)REG(USART1_BASE+USART_DR_OFFSET);
}

int main(void)
{
	init_usart1();

	char *hello = "Hello world!\r\n";
  
	//send Hello world
	while (*hello != '\0'){
		usart1_send_char(*hello++);
}

   // turn_light_multiple(LED_turn_on);
    //blink(LED_GREEN);
    

	//receive char and resend it
	char ch;
	while (1)
	{
		ch = usart1_receive_char();

		if (ch == '\r')
			usart1_send_char('\n');

		usart1_send_char(ch);
	}
}
