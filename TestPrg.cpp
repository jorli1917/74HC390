#include "StdAfx.h"
#include "testdef.h"
#include "data.h"

//DPS的电浝箝佝值需考虑

void PASCAL aa74HC390()
{
	int i,r,TX;
    
    //Turn off the relay.
	CLOSE_RELAY("1");
	CLEAR_RELAY("1-5");
	CLEAR_RELAY("1-5");
	Sleep(20);
	//CLOSE_RELAY("1-5");
	//CLOSE_RELAY("1-5");

    /************************************************************************************/
    // --------------------------------------------------
    //Connectivity test
    // --------------------------------------------------
	SET_DPS(1, 0, V, 20, MA);                   
    PMU_CONDITIONS(FIMV, 100, UA, 3, V);
    if(!PMU_MEASURE("1-7,41-47", 5, "CON_", V, 1.5, 0.2))
    {
        BIN(1); 
    }
		
    // --------------------------------------------------
    //Leakage current test
    // --------------------------------------------------
    SET_DPS(1, 6.0, V, 20, MA);  
    SET_INPUT_LEVEL(6.0,0);
	SET_OUTPUT_LEVEL(4.5,0);
    SET_PERIOD(2000);
    SET_TIMING(100,1500,1000);
    FORMAT(NRZ0,"1-7,41-47");
    
    RUN_PATTERN(1,1,0,0);   //other pin Input high level

    PMU_CONDITIONS(FVMI, 0, V, 0.02, MA);   //
    if(!PMU_MEASURE("1,2,4,44,46,47", 5, "IIL_", UA, No_UpLimit, -0.1))
        BIN(2);

    RUN_PATTERN(2,1,0,0);   //other pin Input low level

    PMU_CONDITIONS(FVMI, 6, V, 0.002, MA);   //加压测浝，电浝箝佄1�72uA
    if(!PMU_MEASURE("1,2,4,44,46,47", 5, "IIH_", UA, 0.1, No_LoLimit))
        BIN(3);

    /************************************************************************************/

    // --------------------------------------------------
    // Power current test
    // --------------------------------------------------
    SET_DPS(1, 6, V, 20, MA);
    RUN_PATTERN(3, 1, 0, 0);    //enter static mode
    if (!DPS_MEASURE(1, R20UA, 10, "IDD_STATIC", UA, 8, No_LoLimit))
    {
        BIN(4);  
    }


    //dynamic testing
    SET_DPS(1, 6, V, 20, MA);
    RUN_PATTERN(4, 1, 0, 0); 
    if (!DPS_MEASURE(1, R20UA, 10, "IDD_DYNAMIC", UA, 8, No_LoLimit)) //
    {
        BIN(5);  // 
    }

    /************************************************************************************/

    // --------------------------------------------------
    // Input level test
    // --------------------------------------------------
    SET_PERIOD(2000);
    SET_TIMING(100,1500,1000);
    FORMAT(RZ, "1-7,41-47");

    //Vcc is 2V
    SET_DPS(1, 2, V, 20, MA);

    SET_INPUT_LEVEL(1.5, 0.5);
    SET_OUTPUT_LEVEL(1.9, 0.1);

    if (!RUN_PATTERN("Vin_2V", 5, 1, 0, 0))
    {
        BIN(6);  // input failure
    }
    
    //Vcc is 4.5V
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(3.15, 1.35);
    SET_OUTPUT_LEVEL(4.4, 0.1);

    if (!RUN_PATTERN("Vin_45V", 5, 1, 0, 0))
    {
        BIN(6);  // input failure
    }


    //Vcc is 6V
    SET_DPS(1, 6, V, 30, MA);
    SET_INPUT_LEVEL(4.2, 1.8);
    SET_OUTPUT_LEVEL(5.9, 0.1);

    if (!RUN_PATTERN("Vin_6V-1", 5, 1, 0, 0))
    {
        BIN(6);  // input failure
    }

    //Vcc is 6V
    SET_DPS(1, 6, V, 30, MA);
    SET_INPUT_LEVEL(4.2, 1.8);
    SET_OUTPUT_LEVEL(5.48, 0.1);
    if (!RUN_PATTERN("Vin_6V-2", 5, 1, 0, 0))
    {
        BIN(6);  // input failure
    }


    SET_DPS(1, 6, V, 30, MA);
    SET_INPUT_LEVEL(4.2, 1.8);
    SET_OUTPUT_LEVEL(5.9, 0.1);
    PMU_CONDITIONS(DMV, 0, V, 6, V);   //
    if(!PMU_MEASURE("1-7,41-47", 5, "Vin_6V-3_", V, No_UpLimit, No_LoLimit))
        BIN(2);
    /************************************************************************************/


    // --------------------------------------------------
    // Output level test
    // --------------------------------------------------
    //2V,-20uA
    SET_DPS(1, 2.0, V, 20, MA);
    SET_INPUT_LEVEL(1.5, 0.5);

    
    RUN_PATTERN(6,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,5,V);
	if(!PMU_MEASURE("3,45",10,"VOH_2V20UA_",V,No_UpLimit,1.9))
		BIN(7);

	RUN_PATTERN(7,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,5,V);
	if(!PMU_MEASURE("5,43",10,"VOH_2V20UA_",V,No_UpLimit,1.9))
		BIN(7);

	RUN_PATTERN(8,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,5,V);
	if(!PMU_MEASURE("6,42",10,"VOH_2V20UA_",V,No_UpLimit,1.9))
		BIN(7);

	RUN_PATTERN(9,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,5,V);
	if(!PMU_MEASURE("7,41",10,"VOH_2V20UA_",V,No_UpLimit,1.9))
		BIN(7);
    
    
    //4.5V,-20uA
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(3.15, 1.35);
    
    RUN_PATTERN(6,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,5,V);
	if(!PMU_MEASURE("3,45",10,"VOH_4.5V20UA_",V,No_UpLimit,4.4))
		BIN(7);

	RUN_PATTERN(7,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,5,V);
	if(!PMU_MEASURE("5,43",10,"VOH_4.5V20UA_",V,No_UpLimit,4.4))
		BIN(7);

	RUN_PATTERN(8,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,5,V);
	if(!PMU_MEASURE("6,42",10,"VOH_4.5V20UA_",V,No_UpLimit,4.4))
		BIN(7);

	RUN_PATTERN(9,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,5,V);
	if(!PMU_MEASURE("7,41",10,"VOH_4.5V20UA_",V,No_UpLimit,4.4))
		BIN(7);

    
    
    
    //4.5V,-4mA
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(3.15, 1.35);

    
    RUN_PATTERN(6,0,0,0);
	PMU_CONDITIONS(FIMV,-4,MA,6,V);
	if(!PMU_MEASURE("3,45",10,"VOH_4.5V4MA_",V,No_UpLimit,3.98))
		BIN(7);

	RUN_PATTERN(7,0,0,0);
	PMU_CONDITIONS(FIMV,-4,MA,6,V);
	if(!PMU_MEASURE("5,43",10,"VOH_4.5V|4MA_",V,No_UpLimit,3.98))
		BIN(7);

	RUN_PATTERN(8,0,0,0);
	PMU_CONDITIONS(FIMV,-4,MA,6,V);
	if(!PMU_MEASURE("6,42",10,"VOH_4.5V4MA_",V,No_UpLimit,3.98))
		BIN(7);

	RUN_PATTERN(9,0,0,0);
	PMU_CONDITIONS(FIMV,-4,MA,6,V);
	if(!PMU_MEASURE("7,41",10,"VOH_4.5V4MA_",V,No_UpLimit,3.98))
		BIN(7);
    
    
    //6V,-20uA
    SET_DPS(1, 6, V, 20, MA);
    SET_INPUT_LEVEL(4.2, 1.8);
    
    RUN_PATTERN(6,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,6,V);
	if(!PMU_MEASURE("3,45",10,"VOH_6V20UA_",V,No_UpLimit,5.9))
		BIN(7);

	RUN_PATTERN(7,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,6,V);
	if(!PMU_MEASURE("5,43",10,"VOH_6V20UA_",V,No_UpLimit,5.9))
		BIN(7);

	RUN_PATTERN(8,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,6,V);
	if(!PMU_MEASURE("6,42",10,"VOH_6V20UA",V,No_UpLimit,5.9))
		BIN(7);

	RUN_PATTERN(9,0,0,0);
	PMU_CONDITIONS(FIMV,-20,UA,6,V);
	if(!PMU_MEASURE("7,41",10,"VOH_6V20UA",V,No_UpLimit,5.9))
		BIN(7);

    //6V,-5.2mA
    SET_DPS(1, 6, V, 20, MA);
    SET_INPUT_LEVEL(4.2, 1.8);
    
    RUN_PATTERN(6,0,0,0);
	PMU_CONDITIONS(FIMV,-5.2,MA,6,V);
	if(!PMU_MEASURE("3,45",10,"VOH_6V5.2MA",V,No_UpLimit,5.48))
		BIN(7);

	RUN_PATTERN(7,0,0,0);
	PMU_CONDITIONS(FIMV,-5.2,MA,6,V);
	if(!PMU_MEASURE("5,43",10,"VOH_6V5.2MA",V,No_UpLimit,5.48))
		BIN(7);

	RUN_PATTERN(8,0,0,0);
	PMU_CONDITIONS(FIMV,-5.2,MA,6,V);
	if(!PMU_MEASURE("6,42",10,"VOH_6V5.2MA",V,No_UpLimit,5.48))
		BIN(7);

	RUN_PATTERN(9,0,0,0);
	PMU_CONDITIONS(FIMV,-5.2,MA,6,V);
	if(!PMU_MEASURE("7,41",10,"VOH_6V5.2MA",V,No_UpLimit,5.48))
		BIN(7);

    /************************************************************************************/
    
    //VOL-TEST 
    FORMAT(NRZ0, "1-7,41-47");

    //Vcc is 2V, 20uA
    SET_DPS(1, 2, V, 20, MA);
	PMU_CONDITIONS(FIMV,20,UA,0.8,V);
    RUN_PATTERN(10,0,0,0);
	if(!PMU_MEASURE("3,5-7,41-43,45",10,"VOL_2V20UA",V,0.1,No_LoLimit))
		BIN(8);
	SET_MASKJMP();

    //Vcc is 4.5V, 20uA
    SET_DPS(1, 4.5, V, 20, MA);
	PMU_CONDITIONS(FIMV,20,UA,0.8,V);
    RUN_PATTERN(10,0,0,0);
	if(!PMU_MEASURE("3,5-7,41-43,45",10,"VOL_4.5V2UA",V,0.1,No_LoLimit))
		BIN(8);
	SET_MASKJMP();

    //Vcc is 4.5V, 4mA
    SET_DPS(1, 4.5, V, 20, MA);
	PMU_CONDITIONS(FIMV,4,MA,0.8,V);
    RUN_PATTERN(10,0,0,0);
	if(!PMU_MEASURE("3,5-7,41-43,45",10,"VOL_4.5V4MA",V,0.26,No_LoLimit))
		BIN(8);
	SET_MASKJMP();

    //Vcc is 6V, 20UA
    SET_DPS(1, 6, V, 20, MA);
	PMU_CONDITIONS(FIMV,20,UA,0.8,V);
    RUN_PATTERN(10,0,0,0);
	if(!PMU_MEASURE("3,5-7,41-43,45",10,"VOL_6V20UA",V,0.1,No_LoLimit))
		BIN(8);
	SET_MASKJMP();

    //Vcc is 6V, 5.2mA
    SET_DPS(1, 6, V, 20, MA);
	PMU_CONDITIONS(FIMV,5.2,MA,0.8,V);
    RUN_PATTERN(10,0,0,0);
	if(!PMU_MEASURE("3,5-7,41-43,45",10,"VOL_6V5.2MA",V,0.26,No_LoLimit))
		BIN(8);
	SET_MASKJMP();


    
    /************************************************************************************/
    /************************************************************************************/
    //AC PARAMETER


    //tPHL
    //CLKA -> A
    //Vcc =2V
    SET_DPS(1, 2, V, 20, MA);
    SET_INPUT_LEVEL(2,0);
    SET_OUTPUT_LEVEL(1,0);
    TX=10;
    SET_TIMING(10,1000,TX);         //comparion 
    RUN_PATTERN(11,1,0,0);           //reset
    for(i=1;i<1000;i++)
	{
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
	if(!SHOW_RESULT("tPHL_CP0_A_2V",TX,"ns",175,No_LoLimit))   
		BIN(11);


    //4.5V
    SET_DPS(1, 4.5, V, 50, MA);
    SET_INPUT_LEVEL(4.5,0);
    SET_OUTPUT_LEVEL(2.25,0);
    TX=10;
    SET_TIMING(10,1000,TX);         //comparion 
    RUN_PATTERN(11,1,0,0);           //reset
    for(i=1;i<1000;i++)
	{
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
	if(!SHOW_RESULT("tPHL_CP0_A_4.5V",TX,"ns",35,No_LoLimit))   
		BIN(11);


    //6V
    SET_DPS(1, 6, V, 50, MA);
    SET_INPUT_LEVEL(6,0);
    SET_OUTPUT_LEVEL(3,0);
    TX=10;
    SET_TIMING(10,1000,TX);         //comparion 
    RUN_PATTERN(11,1,0,0);           //reset
    for(i=1;i<1000;i++)
	{
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
	if(!SHOW_RESULT("tPHL_CP0_A_6V",TX,"ns",30,No_LoLimit))   
		BIN(11);


    //CLKB -> B
    //tPHL
    //4.5V
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(4.5,0);
    SET_OUTPUT_LEVEL(2.25,0);
    TX=10;
    SET_TIMING(10,1000,TX);         //comparion 
    RUN_PATTERN(13,1,0,0);           //reset
    for(i=1;i<1000;i++)
	{
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
	if(!SHOW_RESULT("tPHL_CP1_B_4.5V",TX,"ns",37,No_LoLimit))   
		BIN(11);


    //CLKB -> C
    //tPHL
    //4.5V
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(4.5,0);
    SET_OUTPUT_LEVEL(2.25,0);
    TX=10;
    SET_TIMING(10,1000,TX);         //comparion 
    RUN_PATTERN(15,1,0,0);           //reset
    for(i=1;i<1000;i++)
	{
	   	r  = RUN_PATTERN(16,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}

	}
	if(!SHOW_RESULT("tPHL_CP1_C_4.5V",TX,"ns",49,No_LoLimit))   
		BIN(11);


    //CLKB -> D
    //tPHL
    //4.5V
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(4.5,0);
    SET_OUTPUT_LEVEL(2.25,0);
    TX=10;
    SET_TIMING(10,1000,TX);         //comparion 
    RUN_PATTERN(17,1,0,0);           //reset
    for(i=1;i<1000;i++)
	{
	   	r  = RUN_PATTERN(18,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}

	}
	if(!SHOW_RESULT("tPHL_CP1_D_4.5V",TX,"ns",36,No_LoLimit))   
		BIN(11);


    //CLKA -> D
    //tPHL
    //4.5V
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(4.5,0);
    SET_OUTPUT_LEVEL(2.25,0);
    TX=10;
    SET_TIMING(10,1000,TX);         //comparion 
    RUN_PATTERN(19,1,0,0);           //reset
    for(i=1;i<1000;i++)
	{
	   	r  = RUN_PATTERN(20,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}

	}
	if(!SHOW_RESULT("tPHL_CP0_D_4.5V",TX,"ns",73,No_LoLimit))   
		BIN(11);


    //MR -> A
    //tPHL
    //4.5V
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(4.5,0);
    SET_OUTPUT_LEVEL(2.25,0);
    TX=10;
    SET_TIMING(10,1000,TX);         //comparion 
    RUN_PATTERN(11,1,0,0);           //reset
    for(i=1;i<1000;i++)
	{
	   	r  = RUN_PATTERN(21,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}

	}
	if(!SHOW_RESULT("tPHL_MR_D_4.5V",TX,"ns",38,No_LoLimit))   
		BIN(11);
    
    ///////////////////////////////////////////////////////////

    //CP0 -> A
    //4.5
    //tPLH
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(4.5,0);
    SET_OUTPUT_LEVEL(2.25,0);
    TX=10;
    for(i=1;i<100;i++)
	{
	    SET_TIMING(10,1000,TX);      
        RUN_PATTERN(22,1,0,0);       //first reset
	   	r  = RUN_PATTERN(23,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}

	}
	if(!SHOW_RESULT("tPLH_CP0_A_4.5V",TX,"ns",35,No_LoLimit))   
		BIN(12);

	
    //CP1 -> B
    //4.5
    //tPLH
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(4.5,0);
    SET_OUTPUT_LEVEL(2.25,0);
    TX=10;
    for(i=1;i<100;i++)
	{
	    SET_TIMING(10,1000,TX);      
        RUN_PATTERN(24,1,0,0);       //first reset
	   	r  = RUN_PATTERN(25,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}

	}
	if(!SHOW_RESULT("tPLH_CP1_B_4.5V",TX,"ns",37,No_LoLimit))   
		BIN(12);
    
    

    //CP1 -> C
    //4.5
    //tPLH
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(4.5,0);
    SET_OUTPUT_LEVEL(2.25,0);
    TX=10;
    for(i=1;i<100;i++)
	{
	    SET_TIMING(10,1000,TX);      
        RUN_PATTERN(26,1,0,0);       //first reset
	   	r  = RUN_PATTERN(27,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}

	}
	if(!SHOW_RESULT("tPLH_CP1_C_4.5V",TX,"ns",49,No_LoLimit))   
		BIN(12);
    


    //CP1 -> D
    //4.5
    //tPLH
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(4.5,0);
    SET_OUTPUT_LEVEL(2.25,0);
    TX=10;
    for(i=1;i<100;i++)
	{
	    SET_TIMING(10,1000,TX);      
        RUN_PATTERN(28,1,0,0);       //first reset
	   	r  = RUN_PATTERN(29,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}

	}
	if(!SHOW_RESULT("tPLH_CP1_D_4.5V",TX,"ns",36,No_LoLimit))   
		BIN(12);


    //CP0 -> D
    //4.5
    //tPLH
    SET_DPS(1, 4.5, V, 20, MA);
    SET_INPUT_LEVEL(4.5,0);
    SET_OUTPUT_LEVEL(2.25,0);
    TX=10;
    for(i=1;i<100;i++)
	{
	    SET_TIMING(10,1000,TX);      
        RUN_PATTERN(30,1,0,0);       //first reset
	   	r  = RUN_PATTERN(31,1,0,0);
	    if(r==0)//fail
		{
			TX=TX+10;
		}
		if(r==1)//pass
		{
			break;
		}

	}
	if(!SHOW_RESULT("tPLH_CP0_D_4.5V",TX,"ns",73,No_LoLimit))   
		BIN(12);
    
    //ttplh
	int TX1,TX2;
    SET_INPUT_LEVEL(4.5,0);
	SET_OUTPUT_LEVEL(0.45,0);
	RUN_PATTERN(22,1,0,0);           //reset
	TX1=10;
	for(i=1;i<200;i++)
	{
	    SET_TIMING(10,1000,TX1);
	   	r  = RUN_PATTERN(23,1,0,0);
	    if(r==0)//fail
		{
			TX1=TX1+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}


	SET_INPUT_LEVEL(4.5,0);
	SET_OUTPUT_LEVEL(4.05,2.25);
	RUN_PATTERN(22,1,0,0);           //reset
	TX2=10;
	for(i=1;i<500;i++)
	{
	    SET_TIMING(10,1000,TX2);
	   	r  = RUN_PATTERN(23,1,0,0);
	    if(r==0)//fail
		{
			TX2=TX2+10;
		}
		if(r==1)//pass
		{
			break;
		}

	}

	if(!SHOW_RESULT("ttlh",TX2-TX1,"ns",15,No_LoLimit))
		BIN(13);


    //ttphl
    SET_INPUT_LEVEL(4.5,0);
	SET_OUTPUT_LEVEL(0.45,0);
	RUN_PATTERN(11,1,0,0);           //reset
	TX1=10;
	for(i=1;i<200;i++)
	{
	    SET_TIMING(10,1000,TX1);
	   	r  = RUN_PATTERN(12,1,0,0);
	    if(r==0)//fail
		{
			TX1=TX1+10;
		}
		if(r==1)//pass
		{
			break;
		}
	}


	SET_INPUT_LEVEL(4.5,0);
	SET_OUTPUT_LEVEL(4.05,2.25);
	RUN_PATTERN(11,1,0,0);           //reset
	TX2=10;
	for(i=1;i<500;i++)
	{
	    SET_TIMING(10,1000,TX2);
	   	r  = RUN_PATTERN(12,1,0,0);
	    if(r==0)//fail
		{
			TX2=TX2+10;
		}
		if(r==1)//pass
		{
			break;
		}

	}

	if(!SHOW_RESULT("tthl",TX2-TX1,"ns",15,No_LoLimit))
		BIN(14);
}