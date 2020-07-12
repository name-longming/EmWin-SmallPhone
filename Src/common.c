#include "common.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"


/*********************************************************************************
*************************MCU启明 STM32F407核心开发板******************************
**********************************************************************************
* 文件名称: common.c                                                             *
* 文件简述：各个工程所需调用的公共文件                                           *
* 创建日期：2015.03.03                                                           *
* 版    本：V1.0                                                                 *
* 作    者：Clever                                                               *
* 说    明：包涵数据类型定义、IO口位定义、位段定义与延时函数定义                 * 
**********************************************************************************
*********************************************************************************/	  

/****************************************************************************
* 名    称: void GPIO_group_OUT(_gpio_group *group,u16 outdata)
* 功    能：使用随意16个IO口组成一个16位并行输出口
* 入口参数：*group： 任意16个IO口为元素的结构体指针
            outdata: 16位输出数值
* 返回参数：无
* 说    明：outdata从高位开始赋值
****************************************************************************/
void GPIO_group_OUT(_gpio_group *group,u16 outdata)
{
  u8 t;
	for(t=0;t<16;t++)
    {               
        if((outdata&0x8000)>>15)  
				{
						switch(t)
						{
								case 0:	   group->data15=1; break;
								case 1:	   group->data14=1; break;
								case 2:	   group->data13=1; break;
								case 3:	   group->data12=1; break;
								case 4:	   group->data11=1; break;
								case 5:	   group->data10=1; break;
								case 6:	   group->data9=1;  break;
								case 7:	   group->data8=1;  break;
								case 8:	   group->data7=1;  break;
								case 9:	   group->data6=1;  break;
								case 10:	 group->data5=1;  break;
								case 11:	 group->data4=1;  break;
								case 12:	 group->data3=1;  break;
								case 13:	 group->data2=1;  break;
								case 14:	 group->data1=1;  break;
								case 15:	 group->data0=1;  break;
						}
				}
				else
				{
				  switch(t)
						{
								case 0:	   group->data15=0; break;
								case 1:	   group->data14=0; break;
								case 2:	   group->data13=0; break;
								case 3:	   group->data12=0; break;
								case 4:	   group->data11=0; break;
								case 5:	   group->data10=0; break;
								case 6:	   group->data9=0;  break;
								case 7:	   group->data8=0;  break;
								case 8:	   group->data7=0;  break;
								case 9:	   group->data6=0;  break;
								case 10:	 group->data5=0;  break;
								case 11:	 group->data4=0;  break;
								case 12:	 group->data3=0;  break;
								case 13:	 group->data2=0;  break;
								case 14:	 group->data1=0;  break;
								case 15:	 group->data0=0;  break;
						}
				}
     outdata<<=1; 	
	  }
}
/****************************************************************************
* 名    称: void GPIO_bits_OUT(GPIO_TypeDef* GPIOx, u8 start_bit, u8 bit_size,u16 outdata)
* 功    能：位段操作实现，同一IO口的几位并行输出操作
* 入口参数：* GPIOx：  对应的IO口
*           start_bit: 并行输出的起始位
*           bit_size:  要并行输出的位数
* 返回参数：无
* 说    明：start_bit: 0~14
            bit_size:  1~16 
            bit_size<=16-start_bit
****************************************************************************/
void GPIO_bits_OUT(GPIO_TypeDef* GPIOx, u8 start_bit, u8 bit_size,u16 outdata)
{
  u8 i=0;
	u16 bu1=0;u16 middata=1;

	if( bit_size>(16-start_bit) ) 
     bit_size=16-start_bit;
	
	i=start_bit;
	if(i>0)
		 {
			 while(i--)
         { bu1+=middata; middata*=2;}
		 }
	
   assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
   
	 GPIOx->ODR&=(  ( (0xffff<<bit_size) <<start_bit ) |bu1   ); 
	 GPIOx->ODR|=(outdata<<start_bit);		 
}
 void delay_us( u32 us)
{
		us = 20*us;
		while(us--);
}
///*****************************************************************************
//*****************************以下代码参考网上*********************************
//*****************************************************************************/
////THUMB指令不支持汇编内联
////采用如下方法实现执行汇编指令WFI  
//__asm void WFI_SET(void)
//{
//	WFI;		  
//}
////关闭所有中断(但是不包括fault和NMI中断)
//__asm void INTX_DISABLE(void)
//{
//	CPSID   I
//	BX      LR	  
//}
////开启所有中断
//__asm void INTX_ENABLE(void)
//{
//	CPSIE   I
//	BX      LR  
//}
////设置栈顶地址
////addr:栈顶地址
//__asm void MSR_MSP(u32 addr) 
//{
//	MSR MSP, r0 			//set Main Stack value
//	BX r14
//}

//利用系统滴答定时，编写的延时函数

//static u8  fac_us=0; //us延时倍乘数			   
//static u16 fac_ms=0; //ms延时倍乘数,在ucos下,代表每个节拍的ms数

/****************************************************************************
* 名    称: delay_init()
* 功    能：延时函数初始化
* 入口参数：无
* 返回参数：无
* 说    明：
****************************************************************************/
//void delay_init()
//{
// 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
//	fac_us=SYSCLK/8;	 
//	fac_ms=(u16)fac_us*1000; //每个ms需要的systick时钟数   
//}								    

/****************************************************************************
* 名    称: void delay_us(u32 nus)
* 功    能：延时nus
* 入口参数：要延时的微妙数
* 返回参数：无
* 说    明：nus的值,不要大于798915us
****************************************************************************/
//void delay_us(u32 nus)
//{		
//	u32 midtime;	    	 
//	SysTick->LOAD=nus*fac_us; //时间加载	  		 
//	SysTick->VAL=0x00;        //清空计数器
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数 
//	do
//	{
//		midtime=SysTick->CTRL;
//	}
//	while((midtime&0x01)&&!(midtime&(1<<16)));//等待时间到达   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
//	SysTick->VAL =0X00;       //清空计数器	 
//}
/****************************************************************************
* 名    称: void delay_xms(u16 nms)
* 功    能：延时nms
* 入口参数：要延时的毫妙数
* 返回参数：无
* 说    明：SysTick->LOAD为24位寄存器,所以,最大延时为: nms<=0xffffff*8*1000/SYSCLK
            对168M条件下,nms<=798ms 
****************************************************************************/
//void delay_xms(u16 nms)
//{	 		  	  
//	u32 midtime;		   
//	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
//	SysTick->VAL =0x00;           //清空计数器
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数  
//	do
//	{
//		midtime=SysTick->CTRL;
//	}
//	while((midtime&0x01)&&!(midtime&(1<<16)));//等待时间到达   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
//	SysTick->VAL =0X00;       //清空计数器	  	    
//} 
/****************************************************************************
* 名    称: void delay_ms(u16 nms)
* 功    能：延时nms
* 入口参数：要延时的毫妙数
* 返回参数：无
* 说    明：nms:0~65535
****************************************************************************/
//void delay_ms(u16 nms)
//{	 	 
//	u8 repeat=nms/540;	//这里用540,是考虑到某些客户可能超频使用,
//						          //比如超频到248M的时候,delay_xms最大只能延时541ms左右了
//	u16 remain=nms%540;
//	while(repeat)
//	{
//		delay_xms(540);
//		repeat--;
//	}
//	if(remain)delay_xms(remain);
//} 
//初始化延迟函数
//当使用OS的时候,此函数会初始化OS的时钟节拍
//SYSTICK的时钟固定为AHB时钟的1/8
//SYSCLK:系统时钟频率
//void delay_init(u8 SYSCLK_CLK)
//{
//#if SYSTEM_SUPPORT_OS 						//如果需要支持OS.
//	u32 reload;
//#endif
// 	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8); 
//	fac_us=SYSCLK/8;						//不论是否使用OS,fac_us都需要使用
//#if SYSTEM_SUPPORT_OS 						//如果需要支持OS.
//	reload=SYSCLK/8;						//每秒钟的计数次数 单位为M	   
//	reload*=1000000/delay_ostickspersec;	//根据delay_ostickspersec设定溢出时间
//											//reload为24位寄存器,最大值:16777216,在168M下,约合0.7989s左右	
//	fac_ms=1000/delay_ostickspersec;		//代表OS可以延时的最少单位	   
//	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//开启SYSTICK中断
//	SysTick->LOAD=reload; 					//每1/delay_ostickspersec秒中断一次	
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; 	//开启SYSTICK    
//#else
//	fac_ms=(u16)fac_us*1000;				//非OS下,代表每个ms需要的systick时钟数   
//#endif
//}			
//	
////延时nus
////nus为要延时的us数.	
////注意:nus的值,不要大于798915us(最大值即2^24/fac_us@fac_us=21)
////void delay_us(u32 nus)
////{		
////	u32 temp;	    	 
////	SysTick->LOAD=nus*fac_us; 				//时间加载	  		 
////	SysTick->VAL=0x00;        				//清空计数器
////	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //开始倒数 	 
////	do
////	{
////		temp=SysTick->CTRL;
////	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
////	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //关闭计数器
////	SysTick->VAL =0X00;       				//清空计数器 
////}

//void delay_us(u32 nus)
//{		
//	u32 ticks;
//	u32 told,tnow,tcnt=0;
//	u32 reload=SysTick->LOAD;				//LOAD的值	    	 
//	ticks=nus*fac_us; 						//需要的节拍数 
//	//delay_osschedlock();					//阻止OS调度，防止打断us延时
//	vTaskSuspendAll();     //开启调度锁
//	told=SysTick->VAL;        				//刚进入时的计数器值
//	while(1)
//	{
//		tnow=SysTick->VAL;	
//		if(tnow!=told)
//		{	    
//			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
//			else tcnt+=reload-tnow+told;	    
//			told=tnow;
//			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
//		}  
//	};
//	xTaskResumeAll ();
//	//delay_osschedunlock();					//恢复OS调度											    
//}  
