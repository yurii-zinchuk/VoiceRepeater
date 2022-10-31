/*******************************************************************************
* File Name: Avoice.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Avoice_H) /* Pins Avoice_H */
#define CY_PINS_Avoice_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Avoice_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Avoice_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Avoice_Read(void);
void    Avoice_Write(uint8 value);
uint8   Avoice_ReadDataReg(void);
#if defined(Avoice__PC) || (CY_PSOC4_4200L) 
    void    Avoice_SetDriveMode(uint8 mode);
#endif
void    Avoice_SetInterruptMode(uint16 position, uint16 mode);
uint8   Avoice_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Avoice_Sleep(void); 
void Avoice_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Avoice__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Avoice_DRIVE_MODE_BITS        (3)
    #define Avoice_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Avoice_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Avoice_SetDriveMode() function.
         *  @{
         */
        #define Avoice_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Avoice_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Avoice_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Avoice_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Avoice_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Avoice_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Avoice_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Avoice_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Avoice_MASK               Avoice__MASK
#define Avoice_SHIFT              Avoice__SHIFT
#define Avoice_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Avoice_SetInterruptMode() function.
     *  @{
     */
        #define Avoice_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Avoice_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Avoice_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Avoice_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Avoice__SIO)
    #define Avoice_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Avoice__PC) && (CY_PSOC4_4200L)
    #define Avoice_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Avoice_USBIO_DISABLE              ((uint32)(~Avoice_USBIO_ENABLE))
    #define Avoice_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Avoice_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Avoice_USBIO_ENTER_SLEEP          ((uint32)((1u << Avoice_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Avoice_USBIO_SUSPEND_DEL_SHIFT)))
    #define Avoice_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Avoice_USBIO_SUSPEND_SHIFT)))
    #define Avoice_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Avoice_USBIO_SUSPEND_DEL_SHIFT)))
    #define Avoice_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Avoice__PC)
    /* Port Configuration */
    #define Avoice_PC                 (* (reg32 *) Avoice__PC)
#endif
/* Pin State */
#define Avoice_PS                     (* (reg32 *) Avoice__PS)
/* Data Register */
#define Avoice_DR                     (* (reg32 *) Avoice__DR)
/* Input Buffer Disable Override */
#define Avoice_INP_DIS                (* (reg32 *) Avoice__PC2)

/* Interrupt configuration Registers */
#define Avoice_INTCFG                 (* (reg32 *) Avoice__INTCFG)
#define Avoice_INTSTAT                (* (reg32 *) Avoice__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Avoice_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Avoice__SIO)
    #define Avoice_SIO_REG            (* (reg32 *) Avoice__SIO)
#endif /* (Avoice__SIO_CFG) */

/* USBIO registers */
#if !defined(Avoice__PC) && (CY_PSOC4_4200L)
    #define Avoice_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Avoice_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Avoice_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Avoice_DRIVE_MODE_SHIFT       (0x00u)
#define Avoice_DRIVE_MODE_MASK        (0x07u << Avoice_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Avoice_H */


/* [] END OF FILE */
