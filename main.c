/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
float x = 0;

int main(void)
{
    uint16 sliderval;
    uint16 oldsliderval;
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    UART_Start();
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    CapSense_ScanEnabledWidgets();
    ADC_Start();
    
   
    

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        ADC_StartConvert(); 
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
        x = ADC_GetResult16(0);
        float32 y = ADC_CountsTo_mVolts(0, x);
        char8 text[20];
        sprintf(text, "%f", y);
        
        
        UART_UartPutString(text);
        UART_UartPutString("\033[1F");
        
        if(!CapSense_IsBusy()){
            sliderval = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
            if(sliderval != 0xFFFF && sliderval != oldsliderval) {
                if (sliderval < 50) {
                    Green_Write(0u);
                    Red_Write(1u);
                }
                else if (sliderval > 50) {
                    Red_Write(0u);
                    Green_Write(1u);
                }
                oldsliderval = sliderval;
            }
            
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
        }
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
