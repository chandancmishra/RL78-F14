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
#define 	INPUT_N		(10)


/******************************************************************************
Typedef definitions
******************************************************************************/
static int16_t	sp_buff_out16[INPUT_N];


/******************************************************************************
Exported global variables (to be accessed by other files)
******************************************************************************/
 
/******************************************************************************
Private global variables and functions
******************************************************************************/
static const int16_t sp_buff_in[INPUT_N] =
{(int16_t)(1.0000000000000000 *0x7FFF)  
,(int16_t)(0.0710197609601031 *0x7FFF)  
,(int16_t)(0.5590169943749470 *0x7FFF)  
,(int16_t)(0.4484011233337100 *0x7FFF)  
,(int16_t)(-0.2500000000000000*0x7FFF)  
,(int16_t)(0.5000000000000000 *0x7FFF)  
,(int16_t)(-0.5590169943749470*0x7FFF)  
,(int16_t)(-0.1393841289587630*0x7FFF)  
,(int16_t)(-0.2500000000000000*0x7FFF)  
,(int16_t)(-0.8800367553350520*0x7FFF)  
};


/******************************************************************************
* Function Name: sample_dscl_iirsinglepole
* Description  : Sample code to demonstrate single-pole IIR filter
* Arguments    : none
* Return Value : r_dsp_status_t   Function status code
******************************************************************************/
int16_t sample_dscl_iirsinglepole (void)
{
	
	int16_t    result;
	vector_t   input;
	vector_t * input_ptr;
	vector_t   output;
	vector_t * output_ptr;

 	int16_t state;
	int16_t coeff;
	
	/*---------------------------*/
	/* Single-pole IIR filter    */
	/*---------------------------*/
	r_dscl_iirsinglepole_t   sp_handle;
	r_dscl_iirsinglepole_t * sp_handle_ptr; 

	/*---------------------------*/
	/* Single-pole IIR filter    */
	/*---------------------------*/
	state 					= 0;
  	coeff 					= (int16_t) (-0.15 * 0x7FFF);
	sp_handle.options		= R_DSCL_ROUNDING_TRUNC;
	sp_handle.coefs			= &coeff;
	sp_handle.state			= &state;
	sp_handle_ptr			= &sp_handle;

	input.n		= INPUT_N;
	input.data	= (void*)(&sp_buff_in[0]);
	input_ptr	= &input;

	output_ptr	= &output;
  	output.data = (void *)sp_buff_out16;
	result 		= R_DSCL_IIRSinglePole_i16i16 (sp_handle_ptr,input_ptr,output_ptr);

	return (result);

} /* End of function */

