/*******************************************************************************
* File Name: CapSense1_INT.c
* Version 2.60
*
* Description:
*  This file provides the source code of the  Interrupt Service Routine (ISR)
*  for the CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense1.h"
#include "CapSense1_PVT.h"
#include "cyapicallbacks.h"


/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START CapSense1_ISR_INTC` */

/* `#END` */


/*******************************************************************************
* Function Name: CapSense1_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when the measure window is closed. The measure window
*  depends on the sensor scan resolution parameter.
*  The ISR has two modes:
*   1. Scans a single sensor and stores the measure result.
*   2. Stores the result of the current measure and starts the next scan till all
*      the enabled sensors are scanned.
*  This interrupt handler is only used in one channel designs.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense1_csv - used to provide the status and mode of the scanning process.
*   Mode - a single scan or scan of all the enabled sensors.
*   Status - scan is in progress or ready for new scan.
*  CapSense1_sensorIndex - used to store a sensor scanning sensor number.
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(CapSense1_ISR)
{
    static uint8 CapSense1_snsIndexTmp;

    #ifdef CapSense1_ISR_ENTRY_CALLBACK
        CapSense1_ISR_EntryCallback();
    #endif /* CapSense1_ISR_ENTRY_CALLBACK */

    /*  Place your Interrupt code here. */
    /* `#START CapSense1_ISR_ENTER` */

    /* `#END` */

    CyIntDisable(CapSense1_ISR_NUMBER);

    CapSense1_CSD_INTR_REG = 1u;

    CapSense1_PostScan((uint32)CapSense1_sensorIndex);

    if ((CapSense1_csdStatusVar & CapSense1_SW_CTRL_SINGLE_SCAN) != 0u)
    {
        CapSense1_csdStatusVar &= (uint8)~CapSense1_SW_STS_BUSY;
    }
    else
    {
        /* Proceed scanning */
        CapSense1_sensorIndex = CapSense1_FindNextSensor(CapSense1_sensorIndex);

        /* Check end of scan */
        if(CapSense1_sensorIndex < CapSense1_TOTAL_SENSOR_COUNT)
        {
            CapSense1_PreScan((uint32)CapSense1_sensorIndex);
        }
        else
        {
            CapSense1_csdStatusVar &= (uint8)~CapSense1_SW_STS_BUSY;

             /* Check if widget has been scanned */
            if((CapSense1_csdStatusVar & CapSense1_SW_CTRL_WIDGET_SCAN) != 0u)
            {
                /* Restore sensorEnableMask array */
                for(CapSense1_snsIndexTmp = 0u;
                    CapSense1_snsIndexTmp < CapSense1_TOTAL_SENSOR_MASK;
                    CapSense1_snsIndexTmp++)
                {
                    /* Backup sensorEnableMask array */
                    CapSense1_sensorEnableMask[CapSense1_snsIndexTmp] = CapSense1_sensorEnableMaskBackup[CapSense1_snsIndexTmp];
                }
            }
        }
    }
    CyIntEnable(CapSense1_ISR_NUMBER);

    /*  Place your Interrupt code here. */
    /* `#START CapSense1_ISR_EXIT` */

    /* `#END` */

    #ifdef CapSense1_ISR_EXIT_CALLBACK
        CapSense1_ISR_ExitCallback();
    #endif /* CapSense1_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */
