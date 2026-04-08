//74HC595_testprg

#include "StdAfx.h"
#include "testdef.h"
#include "data.h"


void PASCAL A74HC595_LI()
{
	 int i,r,TX,TW;
	  CLEAR_RELAY("1");
      Sleep(20);
   CLEAR_RELAY("1-3");
   CLEAR_RELAY("1-3");
      
////////////////////////////////////1.CON_TEST////////////////////////////////

  SET_DPS(1,0,V,50,MA);
  PMU_CONDITIONS(FIMV,-0.1,MA,2,V);
  if(!PMU_MEASURE("1-7,41-47",15,"CON_",V,-0.1,-1.9))
	BIN(2);

///////////////////////////////////2.fun_test////////////////////////////////

	SET_DPS(1,2,V,20,MA);//VCC供电2v，DPS1通道，钳位电流为20MA
	SET_INPUT_LEVEL(1.5,0.5);//设置输入，高电平输入1.5v以上的电压，低电平输入0.5v以下电压
	SET_OUTPUT_LEVEL(1.9,0.1);//设置输出，高于1.9判定为高电平，低于0.1判定为低电平

  SET_PERIOD(5000);//设置时钟周期为5000us
  SET_TIMING(300,4700,4000);//设置时序，前沿=300us，脉冲=4700us，选通=4000us

  FORMAT(NRZ0,"42,45,46");  
  FORMAT(RZ,"43,44");  

   if (!RUN_PATTERN("FUN_clear_min",5,1,0,0)) //fun_test_clear
   BIN(2);
   if (!RUN_PATTERN("FUN_shift_min",0,1,0,0)) //fun_test_shifting_register
   BIN(2);
  SET_DPS(1,4.5,V,20,MA);//VCC供电4.5v，DPS1通道，钳位电流为20MA
	SET_INPUT_LEVEL(3.15,1.35);//设置输入，高电平输入3.5v以上的电压，低电平输入1.35v以下电压
	SET_OUTPUT_LEVEL(4.4,0.1);//设置输出，高于4.4判定为高电平，低于0.1判定为低电平
   if (!RUN_PATTERN("FUN_clear_mid",5,1,0,0)) //fun_test_clear
   BIN(2);
   if (!RUN_PATTERN("FUN_shift_mid",0,1,0,0)) //fun_test_shifting_register
   BIN(2);

 SET_DPS(1,6,V,20,MA);//VCC供电6v，DPS1通道，钳位电流为20MA
	SET_INPUT_LEVEL(4.2,1.8);//设置输入，高电平输入4.2v以上的电压，低电平输入1.8v以下电压
	SET_OUTPUT_LEVEL(5.9,0.1);//设置输出，高于5.9判定为高电平，低于0.1判定为低电平
   if (!RUN_PATTERN("FUN_clear_max",5,1,0,0)) //fun_test_clear
   BIN(2);
   if (!RUN_PATTERN("FUN_shift_max",0,1,0,0)) //fun_test_shifting_register
   BIN(2);

//////////////DC_test


////////VOL_test

 ////2.0V条件下测试


	SET_DPS(1,2.0,V,20,MA);//电源电压为2.0v条件下测试

	SET_INPUT_LEVEL(1.8,0.5);//设置输入，高电平输入5.8v以上的电压，低电平输入0.5v以下电压
	RUN_PATTERN(1,0,0,0);//执行图形文件，使得输出逻辑为低

   //测试所有输出

  PMU_CONDITIONS(FIMV,-20,UA,5,V);//加流测压
  if(!PMU_MEASURE("1-7,47,41",10,"VOL_ALL_2.0_",V,0.1,No_LoLimit)) //测试QA-QH的VOL，0.33的上限制，无下限
		BIN(2);


  ////4.5V条件下测试


	SET_DPS(1,4.5,V,20,MA);//电源电压为4.5v条件下测试

	SET_INPUT_LEVEL(4.0,0.5);//设置输入，高电平输入4v以上的电压，低电平输入0.5v以下电压
	RUN_PATTERN(1,0,0,0);//执行图形文件，使得输出逻辑为低


   //测试所有输出

  PMU_CONDITIONS(FIMV,-20,UA,6,V);//加流测压
  if(!PMU_MEASURE("1-7,47,41",10,"VOL_ALL_4.5_",V,0.1,No_LoLimit)) //测试QA-QH的VOL，0.33的上限制，无下限
		BIN(2);
   //测试Qn总线驱动输出
  PMU_CONDITIONS(FIMV,-6.0,MA,5,V);//加流测压
	if(!PMU_MEASURE("1-7,47",10,"VOL_Qn_4.5_",V,0.33,No_LoLimit)) //测试QA-QH的VOL，0.33的上限制，无下限
		BIN(2);
    //测试QS的标准输出

  PMU_CONDITIONS(FIMV,-4.0 ,MA,5,V);//加流测压
   if(!PMU_MEASURE("41",10,"VOL_Qs_4.5_",V,0.33,No_LoLimit))//测试QS的VOL，0.33的上限制，无下限
		BIN(2);

  ////6.0V条件下测试

  SET_DPS(1,6.0,V,20,MA);//电源电压为6.0v条件下测试

  SET_INPUT_LEVEL(5.8,0.5);//设置输入，高电平输入5.8v以上的电压，低电平输入0.5v以下电压
  RUN_PATTERN(1,0,0,0);//执行图形文件，使得输出逻辑为低

     //测试所有输出

  PMU_CONDITIONS(FIMV,-20,UA,6,V);//加流测压
  if(!PMU_MEASURE("1-7,47,41",10,"VOL_ALL_6.0_",V,0.1,No_LoLimit)) //测试QA-QH的VOL，0.33的上限制，无下限
		BIN(2);
   //测试Qn总线驱动输出
  PMU_CONDITIONS(FIMV,-7.8,MA,6,V);//加流测压
	if(!PMU_MEASURE("1-7,47",10,"VOL_Qn_6.0_",V,0.33,No_LoLimit)) //测试QA-QH的VOL，0.33的上限制，无下限
		BIN(2);
    //测试QS的标准输出

  PMU_CONDITIONS(FIMV,-5.2,MA,5,V);//加流测压
   if(!PMU_MEASURE("41",10,"VOL_Qs_6.0_",V,0.33,No_LoLimit))//测试QS的VOL，0.33的上限制，无下限
		BIN(2);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////VOH_test

////2.0V条件下测试

  SET_DPS(1,2.0,V,20,MA);//电源电压为2.0v条件下测试

	SET_INPUT_LEVEL(1.8,0.5);//设置输入，高电平输入1.8v以上的电压，低电平输入0.5v以下电压
	RUN_PATTERN(2,0,0,0);//执行图形文件，使得输出逻辑为高

   //测试所有输出

  PMU_CONDITIONS(FIMV,-20,UA,5,V);//加流测压
  if(!PMU_MEASURE("1-7,47,41",10,"VOH_ALL_2.0_",V,No_UpLimit,1.9)) //测试QA-QH的VOL，0.33的上限制，无下限
		BIN(2);

  //////4.5V条件下测试

    SET_DPS(1,4.5,V,20,MA);//电源电压为4.5v条件下测试

    SET_INPUT_LEVEL(4.5,0.5);//设置输入，高电平输入5.8v以上的电压，低电平输入0.5v以下电压
    RUN_PATTERN(2,0,0,0);//执行图形文件，使得输出逻辑为低
       //测试所有输出

  PMU_CONDITIONS(FIMV,-20,UA,6,V);//加流测压
  if(!PMU_MEASURE("1-7,47,41",10,"VOH_ALL_4.5_",V,No_UpLimit,4.4)) //测试QA-QH的VOL，0.33的上限制，无下限
		BIN(2); 
      //测试Qs的标准输出

    PMU_CONDITIONS(FIMV,-4.0,MA,5,V);//加流测压
    if(!PMU_MEASURE("41",10,"VOH_Qs_4.5_",V,No_UpLimit,3.84))//测试QS的VOL，0.33的上限制，无下限
		BIN(2);
       //测试Qn总线驱动输出
    PMU_CONDITIONS(FIMV,-6.0,MA,5,V);//加流测压
	  if(!PMU_MEASURE("1-7,47",10,"VOH_Qn_4.5_",V,No_UpLimit,3.84)) //测试QA-QH的VOL，0.33的上限制，无下限
		BIN(2);
/////6.0V条件下测试

   SET_DPS(1,6.0,V,20,MA);//电源电压为6.0v条件下测试

   SET_INPUT_LEVEL(6,0.5);//设置输入，高电平输入5.8v以上的电压，低电平输入0.5v以下电压
 	 RUN_PATTERN(2,0,0,0);//执行图形文件，使得输出QS逻辑为低

     //测试所有输出

    PMU_CONDITIONS(FIMV,-20,UA,6,V);//加流测压
    if(!PMU_MEASURE("1-7,47,41",10,"VOH_ALL_6.0_",V,No_UpLimit,5.9)) //VOH,5.9的下限，无上限

		BIN(2); 
      //测试Qs的标准输出

    PMU_CONDITIONS(FIMV,-5.8,MA,6,V);//加流测压
    if(!PMU_MEASURE("41",10,"VOH_Qs_6.0_",V,No_UpLimit,5.34))//测试QS的VOH,5.34的下限，无上限

		BIN(2);
       //测试Qn总线驱动输出
    PMU_CONDITIONS(FIMV,-8,MA,6,V);//加流测压
	  if(!PMU_MEASURE("1-7,47",10,"VOH_Qn_6.0_",V,No_UpLimit,5.34)) //测试QA-QH的VOH,5.34的下限，无上限

		BIN(2);
///////////////////////////////IIN_test/////////////////
    SET_DPS(1,6.0,V,20,MA);
    SET_INPUT_LEVEL(5.5,0.4);
    //IIH_test
    RUN_PATTERN(3,1,0,0); 
    PMU_CONDITIONS(FVMI,6,V,0.2,MA);
    if(!PMU_MEASURE("42,43,45,46",15,"IIH_",UA,0,-1))   
        BIN(2);
    //IIL_test
    RUN_PATTERN(4,1,0,0);     
    PMU_CONDITIONS(FVMI,0,V,0.2,MA);
    if(!PMU_MEASURE("42,43,45,46",15,"IIL_",UA,1,0))   
        BIN(2);       
/////ICC_test
    SET_DPS(1,6.0,V,20,MA);
    SET_INPUT_LEVEL(5.9,0.4);
    RUN_PATTERN(6,1,0,0); 
    if(!DPS_MEASURE(1,R2MA,5,"ICC_",UA,80,No_LoLimit))
        BIN(2);

////IOZ_test
    SET_DPS(1,6.0,V,50,MA);
    SET_INPUT_LEVEL(5.9,0.4);
    RUN_PATTERN(6,1,0,0); 
    PMU_CONDITIONS(FVMI,6,V,0.1,MA);
    if(!PMU_MEASURE("1-7,47",15,"IOZH_",UA,5,-5))   
        BIN(2);   
    PMU_CONDITIONS(FVMI,0,V,0.1,MA);
    if(!PMU_MEASURE("1-7,47",15,"IOZL_",UA,5,-5))   
   	BIN(2);   
	////////////////////////////交流参数测试/////////////////////////////////
     CLOSE_RELAY("3");
     Sleep(10);
    SET_DPS(1,6,V,20,MA);//VCC供电6v，DPS1通道，钳位电流为20MA
	SET_INPUT_LEVEL(5.8,0.5);//设置输入
	SET_OUTPUT_LEVEL(2.5,3);//设置输出，高于5.9判定为高电平，低于0.1判定为低电平
///tPLH_SCLK_6v
     TX=10;
	for(i=1;i<300;i++)
	{
	    SET_TIMING(10,2000,TX);
	   	r  = RUN_PATTERN(7,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}
	if(!SHOW_RESULT("tPLH_SCLK_6v",TX-10,"ns",60,No_LoLimit))  
  BIN(3); 
	///tPHL_SCLK_6v
     TX=10;
	for(i=1;i<300;i++)
	{
	    SET_TIMING(10,2000,TX);
	   	r  = RUN_PATTERN(8,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}
	if(!SHOW_RESULT("tPHL_SCLK_6v",TX-10,"ns",60,No_LoLimit))  
  BIN(3);
	///tPHL_clear_6v
	TX=10;
	for(i=1;i<300;i++)
	{
	    SET_TIMING(10,2000,TX);
	   	r  = RUN_PATTERN(9,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}
	if(!SHOW_RESULT("tPLH_CLEAR_6v",TX-10,"ns",60,No_LoLimit))  
      BIN(3); 
///RCK
	     TX=10;
	for(i=1;i<300;i++)
	{
	    SET_TIMING(10,2000,TX);
	   	r  = RUN_PATTERN(10,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}
	if(!SHOW_RESULT("tPD_RCK_6v",TX-10,"ns",60,No_LoLimit))  
  BIN(3);
///脉冲宽度
	TW=10;
	for(i=1;i<300;i++)
	{
	    SET_TIMING(10,TW,500);
	   	r  = RUN_PATTERN(5,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}
	if(!SHOW_RESULT("TW",TW,"ns",20,No_LoLimit))  
      BIN(3); 

    Sleep(200);
 ///2v
    SET_DPS(1,2,V,20,MA);//VCC供电6v，DPS1通道，钳位电流为20MA
	SET_INPUT_LEVEL(1.5,0.5);//设置输入，高电平输入4.2v以上的电压，低电平输入1.8v以下电压
	SET_OUTPUT_LEVEL(1,1);//设置输出，高于5.9判定为高电平，低于0.1判定为低电平
	   TX=10;
	for(i=1;i<300;i++)
	{
	    SET_TIMING(10,2000,TX);
	   	r  = RUN_PATTERN(7,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}
	if(!SHOW_RESULT("tPLH_SCLK_2v",TX-10,"ns",200,No_LoLimit))  
  BIN(3); 

	 TX=10;
	for(i=1;i<300;i++)
	{
	    SET_TIMING(10,2000,TX);
	   	r  = RUN_PATTERN(8,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}
	if(!SHOW_RESULT("tPHL_SCLK_2v",TX-10,"ns",200,No_LoLimit))  
    BIN(3);
Sleep(100);
	//ten tPZ
    
    CLOSE_RELAY("2");

		Sleep(20);
	   
    SET_DPS(1,6,V,20,MA);//VCC供电6v，DPS1通道，钳位电流为20MA
	SET_INPUT_LEVEL(5.8,0.5);//设置输入，高电平输入4.2v以上的电压，低电平输入1.8v以下电压
    SET_OUTPUT_LEVEL(2.8,2.5);//
     TX=10;
	for(i=1;i<300;i++)
	{
	    SET_TIMING(10,2000,TX);
	   	r  = RUN_PATTERN(11,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}
	if(!SHOW_RESULT("tPZL",TX-10,"ns",60,No_LoLimit))  
        BIN(3); 
		Sleep(100);
	SET_DPS(1,6,V,20,MA);//VCC供电6v，DPS1通道，钳位电流为20MA
	SET_INPUT_LEVEL(5.8,0.5);//设置输入，高电平输入4.2v以上的电压，低电平输入1.8v以下电压
    SET_OUTPUT_LEVEL(5.2,0.5);//
  
    TX=10;

	for(i=1;i<300;i++)
	{
	    SET_TIMING(10,2000,TX);
	   	r  = RUN_PATTERN(12,1,0,0);
	    if(r==0)//fail
		{    
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}
	if(!SHOW_RESULT("tPLZ",TX-10,"ns",60,No_LoLimit))  
  BIN(3); 
     Sleep(100);
   //TPZH 
     CLOSE_RELAY("1");
		Sleep(20);
	    SET_DPS(1,6,V,30,MA);//VCC供电6v，DPS1通道，钳位电流为20MA
	SET_INPUT_LEVEL(6.0,0.5);//设置输入，高电平输入4.2v以上的电压，低电平输入1.8v以下电压
    SET_OUTPUT_LEVEL(1.8,0.2);//
     TX=10;
	for(i=1;i<300;i++)
	{
	    SET_TIMING(10,2000,TX);
	   	r  = RUN_PATTERN(13,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}
	if(!SHOW_RESULT("tPZH",TX-10,"ns",60,No_LoLimit))  
        BIN(3); 
	 Sleep(100);
	//tphz
	    SET_DPS(1,6,V,20,MA);//VCC供电6v，DPS1通道，钳位电流为20MA
	SET_INPUT_LEVEL(5.8,0.5);//设置输入，高电平输入4.2v以上的电压，低电平输入1.8v以下电压
    SET_OUTPUT_LEVEL(5.5,4.0);//
     TX=10;
	for(i=1;i<300;i++)
	{
	   SET_TIMING(10,2000,TX);
	   	r  = RUN_PATTERN(14,1,0,0);
	    if(r==0)//fail
		{
		TX=TX+10;
		}
		if(r==1)//pass
	{
			break;
		}
	}
	if(!SHOW_RESULT("tPHZ",TX-10,"ns",60,No_LoLimit))  
        BIN(3); 
	   CLEAR_RELAY("1");
      Sleep(500);
  } 


