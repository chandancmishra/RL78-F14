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
* File Name    : sample_dscl_iirbiquad.c
* Version      : 0.1
* Device(s)    : RL78/G14
* Tool-Chain   : CubeSuite+, CA78K0R V1.30
* Description  : IIR biquad filter sample program, i16i16 format
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
#include <stdlib.h>
#include "r_dscl_filters.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define NUM_SAMPLES                 (10)
#define NUM_TAPS_PER_BIQUAD         (5) 
#define NUM_BIQUAD_STAGES           (2) 
#define FRACTION_BITS               (14)  
#define CONVERSION_CONST            ((1<<FRACTION_BITS)-1)  


/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Exported global variables (to be accessed by other files)
******************************************************************************/
 
/******************************************************************************
Private global variables and functions
******************************************************************************/
static const int16_t myCoeffs[NUM_TAPS_PER_BIQUAD * NUM_BIQUAD_STAGES] = 
{
    (int16_t)( 0.0412535372417203*CONVERSION_CONST),
    (int16_t)( 0.0484964426642926*CONVERSION_CONST),
    (int16_t)( -0.0127480428242319*CONVERSION_CONST),
    (int16_t)( -0.792903364023193*CONVERSION_CONST),
    (int16_t)( -0.158829124397261*CONVERSION_CONST),
    (int16_t)( 0.855930601814815*CONVERSION_CONST),
    (int16_t)( -1.00620679173049*CONVERSION_CONST),
    (int16_t)( -0.264497075791865*CONVERSION_CONST),
    (int16_t)( -0.993942754008415*CONVERSION_CONST),
    (int16_t)( -0.226424773198911*CONVERSION_CONST)
};

/* state to be stored in section-reversed order */
static int16_t myDLine[NUM_TAPS_PER_BIQUAD * NUM_BIQUAD_STAGES]; 

/* input stored in time-sequential order */
static const int16_t inputData[NUM_SAMPLES] = 
{
    (int16_t)( 0.0625*CONVERSION_CONST), 				// x(0)
    (int16_t)( 0.0440845988319186*CONVERSION_CONST), 	// x(1)
    (int16_t)( 0.010252390566028*CONVERSION_CONST), 	// x(2)
    (int16_t)( -0.002828057179952*CONVERSION_CONST),   	// x(3)
    (int16_t)( 0.00976214803848264*CONVERSION_CONST),	// x(4)
    (int16_t)( 0.0198136774573159*CONVERSION_CONST),	// x(5)
    (int16_t)( 0.00895367859952169*CONVERSION_CONST),	// x(6)
    (int16_t)( -0.00444181075510635*CONVERSION_CONST),	// x(7)
    (int16_t)( 0.0078397187881209*CONVERSION_CONST),	// x(8)
    (int16_t)( 0.0408825349841861*CONVERSION_CONST),	// x(9)
};

/* To store 1 block of output */
static int16_t outputData[NUM_SAMPLES];

/* Scale should be set to the number of fraction bits of coefficients */
static int16_t myScale = FRACTION_BITS; 

/******************************************************************************
* Function Name: sample_dscl_iirbiquad
* Description  : Sample code to demonstrate generic biquad IIR filter
* Arguments    : none
* Return Value : r_dsp_status_t   Function status code
******************************************************************************/
int16_t sample_dscl_iirbiquad(void)
{
    r_dscl_iirbiquad_t  myFilterHandle;
    vector_t            myInput;  				// See introduction section describing the API document  
    vector_t            myOutput; 				// for a definition of the “vector_t” data type.  
    int16_t             myIIRFlags = R_DSCL_STATUS_OK; 
    int16_t             dynMemSize, staMemSize; 
    
    /*--------------  Set up the IIR filter biquads  ------------*/ 
    myFilterHandle.stages = NUM_BIQUAD_STAGES;
 
    /* Setup data format and options */ 
    myFilterHandle.options  = R_DSCL_ROUNDING_NEAREST;
 
    /* !!! It is important to setup the stages and the form before */ 
    /* !!! calling function R_DSCL_IIRBiquad_StSize_xyyxyy() */ 
    staMemSize = NUM_TAPS_PER_BIQUAD * NUM_BIQUAD_STAGES * sizeof(int16_t); 
    dynMemSize = R_DSCL_IIRBiquad_StateSize_i16i16(&myFilterHandle); 
    if (staMemSize >= dynMemSize)  
    { 
      myFilterHandle.state = (void *)myDLine;  				// probably more common 
    } 
    else 
    {
      myFilterHandle.state = malloc((size_t) dynMemSize);  	//malloc expects size_t 
    } 
 
    /* Initialize the coefficients and internal state */ 
    myFilterHandle.coefs = (void *)myCoeffs;
    myIIRFlags = R_DSCL_IIRBiquad_Init_i16i16(&myFilterHandle); 
    if(myIIRFlags != R_DSCL_STATUS_OK)
    {
        return myIIRFlags;
    }   
 
    /*----------------  Set up the input/output  ----------------*/
    myInput.n = NUM_SAMPLES; 
    myInput.data  = (void *)inputData; 
    myOutput.data = (void *)outputData; 
 
    /*------------------  Wait for input data  ------------------*/
 
    /*---------------  Main library function call  --------------*/
    myIIRFlags = R_DSCL_IIRBiquad_i16i16(&myFilterHandle, &myInput, &myOutput); 
 
    if(myIIRFlags != R_DSCL_STATUS_OK)
    {
        return myIIRFlags;
    }
    
    /*---------------  Output data are now ready  ---------------
    * Note: At this point myOutput.n holds the number of output samples generated by
    * the library, where the data are written to the array pointed to by
    myOutput.data.
    *------------------------------------------------------------*/

    return myIIRFlags;
    
} /* End of function */

