/*******************************************************************************
* File Name: CapSense1_PM.c
* Version 2.60
*
* Description:
*  This file provides Sleep APIs for CapSense CSD Component.
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

static CapSense1_BACKUP_STRUCT CapSense1_backup =
{
    0x00u, /* enableState; */
};


/*******************************************************************************
* Function Name: CapSense1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the customer configuration of CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense1_backup - used to save the component state before entering the  sleep
*  mode and none-retention registers.
*
* Side Effects:
*  None
*
*******************************************************************************/
void CapSense1_SaveConfig(void)
{
    if ((CapSense1_CSD_CFG_REG & CapSense1_CSD_CFG_ENABLE) != 0u)
    {
        CapSense1_backup.enableState = 1u;
    }
}


/*******************************************************************************
* Function Name: CapSense1_Sleep
********************************************************************************
*
* Summary:
*  Disables the Active mode power.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense1_backup - used to save the component state before entering the sleep
*  mode.
*
*******************************************************************************/
void CapSense1_Sleep(void)
{
    CapSense1_SaveConfig();

    /* Disable interrupt */
    CyIntDisable(CapSense1_ISR_NUMBER);

    CapSense1_CSD_CFG_REG &= ~(CapSense1_CSD_CFG_SENSE_COMP_EN | CapSense1_CSD_CFG_SENSE_EN);

    #if(CapSense1_IDAC_CNT == 2u)
        CapSense1_CSD_CFG_REG &= ~(CapSense1_CSD_CFG_ENABLE);
    #endif /* (CapSense1_IDAC_CNT == 2u) */

    /* Disable Clocks */
    CapSense1_SenseClk_Stop();
    CapSense1_SampleClk_Stop();
}


/*******************************************************************************
* Function Name: CapSense1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the CapSense configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Must be called only after CapSense1_SaveConfig() routine. Otherwise
*  the component configuration will be overwritten with its initial setting.
*
* Global Variables:
*  CapSense1_backup - used to save the component state before entering the sleep
*  mode and none-retention registers.
*
*******************************************************************************/
void CapSense1_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: CapSense1_Wakeup
********************************************************************************
*
* Summary:
*  Restores the CapSense configuration and non-retention register values.
*  Restores the enabled state of the component by setting the Active mode power template
*  bits for a number of components used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense1_backup - used to save the component state before entering the sleep
*  mode and none-retention registers.
*
*******************************************************************************/
void CapSense1_Wakeup(void)
{
    /* Enable the Clocks */
    CapSense1_SenseClk_Start();
    CapSense1_SampleClk_Start();

    /* Restore CapSense Enable state */
    if (CapSense1_backup.enableState != 0u)
    {
        CapSense1_Enable();
    }
}


/* [] END OF FILE */
