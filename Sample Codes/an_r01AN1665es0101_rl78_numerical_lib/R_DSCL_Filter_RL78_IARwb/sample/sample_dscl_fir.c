/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer *
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
*******************************************************************************/
/*******************************************************************************
* File Name    : sample_dscl_fir.c
* Version      : 0.1
* Device(s)    : RL78/G14
* Tool-Chain   : IAR Embedded Workbench for Renesas RL78, IAR Compiler V1.40.X
* Description  : FIR filter sample program, i16i16 format
* Operation    :
* Limitations  :
******************************************************************************/

/******************************************************************************
* History      : YYYY.MM.DD  Version  Description
*              : 2012.05.16  0.10     First draft
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dscl_filters.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define NUM_SAMPLES   		(10)
#define NUM_TAPS      		(10)
#define FRACTION_BITS		(15)	
#define CONVERSION_CONST	((1<<FRACTION_BITS)-1)      


/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Exported global variables (to be accessed by other files)
******************************************************************************/
 
/******************************************************************************
Private global variables and functions
******************************************************************************/
/* coeffients stored in time-reversed order */
static int16_t myCoeffs[NUM_TAPS] = {
    (int16_t)( 0.0029024*0x7FFF), // h(9)
    (int16_t)( 0.0100975*0x7FFF), // h(8)
    (int16_t)( 0.0098667*0x7FFF), // h(7)
    (int16_t)( 0.0010075*0x7FFF), // h(6)
    (int16_t)(-0.0149086*0x7FFF), // h(5)
    (int16_t)(-0.0336059*0x7FFF), // h(4)
    (int16_t)(-0.0490032*0x7FFF), // h(3)
    (int16_t)(-0.0547532*0x7FFF), // h(2)
    (int16_t)(-0.0460262*0x7FFF), // h(1)
    (int16_t)(-0.0210426*0x7FFF)  // h(0)
};

/* state & two blocks of input,
   stored in time-sequential order */
static int16_t inputData[NUM_TAPS - 1 + NUM_SAMPLES*2] = { 
	0, // x(-9), start of delayline 
	0, // x(-8) 
	0, // x(-7) 
	0, // x(-6) 
	0, // x(-5) 
	0, // x(-4) 
	0, // x(-3) 
	0, // x(-2) 
	0, // x(-1) 
    (int16_t)( 1.0000*0x7FFF), // x(0),start of 1st block input
    (int16_t)( 0.0530*0x7FFF), // x(1)
    (int16_t)( 0.7877*0x7FFF), // x(2)
    (int16_t)( 0.4080*0x7FFF), // x(3)
    (int16_t)( 0.3210*0x7FFF), // x(4)
    (int16_t)( 0.8155*0x7FFF), // x(5)
    (int16_t)(-0.0300*0x7FFF), // x(6)
    (int16_t)( 0.9202*0x7FFF), // x(7)
    (int16_t)( 0.0000*0x7FFF), // x(8)
    (int16_t)( 0.6072*0x7FFF), // x(9)
    (int16_t)( 0.3536*0x7FFF), // x(10),start of 2nd block input
    (int16_t)( 0.0977*0x7FFF), // x(11)
    (int16_t)( 0.6984*0x7FFF), // x(12)
    (int16_t)(-0.2326*0x7FFF), // x(13)
    (int16_t)( 0.7025*0x7FFF), // x(14)
    (int16_t)(-0.1622*0x7FFF), // x(15)
    (int16_t)( 0.3090*0x7FFF), // x(16)
    (int16_t)( 0.1949*0x7FFF), // x(17)
    (int16_t)(-0.2157*0x7FFF), // x(18)
    (int16_t)( 0.4847*0x7FFF)  // x(19)   
};

/* To store two blocks of output */
static int16_t outputData[NUM_SAMPLES*2];

/* Scale should be set to the number of fraction bits of coefficients.
 It is defined by FIR_SCALE_A in "r_dscl_filter_asm.inc" which is built-in the library.
*/
//static int16_t myScale = FRACTION_BITS; 


/******************************************************************************
* Function Name: sample_dscl_fir
* Description  : Sample code to demonstrate generic FIR filter
* Arguments    : none
* Return Value : r_dsp_status_t   Function status code
******************************************************************************/
int16_t sample_dscl_fir (void) 
{

    r_dscl_firfilter_t myFilterHandle;
    vector_t           myInput;
    vector_t           myOutput;
    int16_t            myFIRFlags = R_DSCL_STATUS_OK;

    /*--------------  Set up the FIR filter ------------*/
    myFilterHandle.taps  = NUM_TAPS;
    myFilterHandle.options = R_DSCL_ROUNDING_NEAREST;

	/* No need to call StateSize API for FIR, as it always return 0. */
	/* The delayline & input share the same buffer.	*/
	myFilterHandle.state = (void *)&inputData[0]; 			// start of delay line

    /*----- Initialize the coefficients and internal state ------*/
    myFilterHandle.coefs = (void *)myCoeffs;
    myFIRFlags = R_DSCL_FIR_Init_i16i16(&myFilterHandle); 	// initialize delay line
    if(myFIRFlags != R_DSCL_STATUS_OK)
    {
        return myFIRFlags;
    }

    /*----------------  Set up the input/output  ----------------*/
    myInput.n = NUM_SAMPLES;
    myInput.data  = (void *)&inputData[NUM_TAPS - 1]; 		//start of 1st block input
    myOutput.data = (void *)outputData;
    /*------------------  Wait for input data  ------------------*/
	
    /*---------------  Main library function call  --------------*/
	/* process 1st input block */
    myFIRFlags = R_DSCL_FIR_i16i16 (&myFilterHandle, &myInput, &myOutput);
    if(myFIRFlags != R_DSCL_STATUS_OK)
    {
        return myFIRFlags;
    }

	/* process 2nd input block */
	myFilterHandle.state = (void *)&inputData[NUM_SAMPLES]; // start of delay line for 2nd block
	myInput.data  = (void *)&inputData[NUM_TAPS - 1 + NUM_SAMPLES]; //start of 2nd block input
    myOutput.data = (void *)&outputData[NUM_SAMPLES]; 		//start of 2nd block output

    myFIRFlags = R_DSCL_FIR_i16i16 (&myFilterHandle, &myInput, &myOutput);
    if(myFIRFlags != R_DSCL_STATUS_OK)
    {
        return myFIRFlags;
    }
	
    /*---------------  Output data are now ready  ---------------
    * Note: At this point myOutput.n holds the number of output samples generated by
    * the library, where the data are written to the array pointed to by myOutput.data.
    *------------------------------------------------------------*/
    return myFIRFlags;
	
} /* End of function */
