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
* File Name    : sample_dsp_main.c
* Version      : 0.1
* Device(s)    : RL78/G14
* Tool-Chain   : IAR Embedded Workbench for Renesas RL78, IAR Compiler V1.40.X
* Description  : Main program to demonstrate RX DSCL library
* Operation	   : 1. Compile and download the sample code. Click 'Reset Go'
*                   to start the software.   
* Limitations  : 
******************************************************************************/
/******************************************************************************
* History      : YYYY.MM.DD  Version  Description
*              : 2012.05.16  0.10     First draft
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dscl_types.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define MY_MIN_DSCL_LIB_VERSION    0x01000000u      /* requires at least v1.0.0 (BCD format */


/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Exported global variables (to be accessed by other files)
******************************************************************************/
uint32_t 		   myCurrentVersion; 

/******************************************************************************
Private global variables and functions
******************************************************************************/
uint32_t R_DSCL_GetVersion(void);
extern int16_t sample_dscl_fir(void);
extern int16_t sample_dscl_iirbiquad(void);
extern int16_t sample_dscl_iirsinglepole(void);

/******************************************************************************
* Function Name: main
* Description  : The main function of RX DSCL sample program
* Arguments    : none
* Return Value : none
******************************************************************************/
void main(void)
{
	int16_t status;

    /*--------------  Get Library Version --------------*/
	myCurrentVersion = R_DSCL_GetVersion();
	if (MY_MIN_DSCL_LIB_VERSION > myCurrentVersion)            // correct version?
    {
        return;
    }

    /*--------------  FIR filter --------------*/	
	status = sample_dscl_fir();

	if (status < 0)
    {
        return;
    }

    /*--------------  IIR Biquad filter --------------*/	
	status = sample_dscl_iirbiquad();

	if (status < 0)
    {
        return;
    }

    /*--------------  IIR Single-pole filter --------------*/	
	status = sample_dscl_iirsinglepole();

	if (status < 0)
    {
        return;
    }

	while(1);

} /* End of function main() */
