/**
  ******************************************************************************
  * @file    stm32u5xx_ll_fdcan.c
  * @author  MCD Application Team
  * @brief   FDCAN LL module driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include "stm32u5xx_ll_fdcan.h"
#include "stm32u5xx_ll_bus.h"
#ifdef USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined(FDCAN1)

/** @addtogroup FDCAN_LL
  * @{
  */

/* Private constants ---------------------------------------------------------*/
/** @addtogroup FDCAN_LL_Private_Constants
  * @{
  */
#define LL_FDCAN_TIMEOUT_VALUE (10U)

#define FDCAN_ELEMENT_MASK_STDID (0x1FFC0000UL)
#define FDCAN_ELEMENT_MASK_EXTID (0x1FFFFFFFUL)
#define FDCAN_ELEMENT_MASK_RTR (0x20000000UL)
#define FDCAN_ELEMENT_MASK_XTD (0x40000000UL)
#define FDCAN_ELEMENT_MASK_ESI (0x80000000UL)
#define FDCAN_ELEMENT_MASK_TS (0x0000FFFFUL)
#define FDCAN_ELEMENT_MASK_DLC (0x000F0000UL)
#define FDCAN_ELEMENT_MASK_BRS (0x00100000UL)
#define FDCAN_ELEMENT_MASK_FDF (0x00200000UL)
#define FDCAN_ELEMENT_MASK_FIDX (0x7F000000UL)
#define FDCAN_ELEMENT_MASK_ANMF (0x80000000UL)

#define SRAMCAN_FLS_NBR LL_FDCAN_MAX_STD_FILTERS
#define SRAMCAN_FLE_NBR LL_FDCAN_MAX_EXT_FILTERS
#define SRAMCAN_RF0_NBR LL_FDCAN_MAX_RX_FIFO0_ELEMENTS
#define SRAMCAN_RF1_NBR LL_FDCAN_MAX_RX_FIFO1_ELEMENTS
#define SRAMCAN_TEF_NBR LL_FDCAN_MAX_TX_EVENT_FIFO_ELEMENTS
#define SRAMCAN_TFQ_NBR LL_FDCAN_MAX_TX_FIFO_QUEUE_ELEMENTS

#define SRAMCAN_FLS_SIZE (1U * 4U)
#define SRAMCAN_FLE_SIZE (2U * 4U)
#define SRAMCAN_RF0_SIZE (18U * 4U)
#define SRAMCAN_RF1_SIZE (18U * 4U)
#define SRAMCAN_TEF_SIZE (2U * 4U)
#define SRAMCAN_TFQ_SIZE (18U * 4U)

#define SRAMCAN_FLSSA (0U)
#define SRAMCAN_FLESA (SRAMCAN_FLSSA + (SRAMCAN_FLS_NBR * SRAMCAN_FLS_SIZE))
#define SRAMCAN_RF0SA (SRAMCAN_FLESA + (SRAMCAN_FLE_NBR * SRAMCAN_FLE_SIZE))
#define SRAMCAN_RF1SA (SRAMCAN_RF0SA + (SRAMCAN_RF0_NBR * SRAMCAN_RF0_SIZE))
#define SRAMCAN_TEFSA (SRAMCAN_RF1SA + (SRAMCAN_RF1_NBR * SRAMCAN_RF1_SIZE))
#define SRAMCAN_TFQSA (SRAMCAN_TEFSA + (SRAMCAN_TEF_NBR * SRAMCAN_TEF_SIZE))
#define SRAMCAN_SIZE LL_FDCAN_MESSAGE_RAM_SIZE
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @addtogroup FDCAN_LL_Private_Variables
  * @{
  */
static const uint8_t DLCtoBytes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup FDCAN_LL_Private_Macros
  * @{
  */
#define IS_LL_FDCAN_CKDIV(__VALUE__)                                                   \
    (((__VALUE__) == LL_FDCAN_CLOCK_DIV1) || ((__VALUE__) == LL_FDCAN_CLOCK_DIV2) ||   \
     ((__VALUE__) == LL_FDCAN_CLOCK_DIV4) || ((__VALUE__) == LL_FDCAN_CLOCK_DIV6) ||   \
     ((__VALUE__) == LL_FDCAN_CLOCK_DIV8) || ((__VALUE__) == LL_FDCAN_CLOCK_DIV10) ||  \
     ((__VALUE__) == LL_FDCAN_CLOCK_DIV12) || ((__VALUE__) == LL_FDCAN_CLOCK_DIV14) || \
     ((__VALUE__) == LL_FDCAN_CLOCK_DIV16) || ((__VALUE__) == LL_FDCAN_CLOCK_DIV18) || \
     ((__VALUE__) == LL_FDCAN_CLOCK_DIV20) || ((__VALUE__) == LL_FDCAN_CLOCK_DIV22) || \
     ((__VALUE__) == LL_FDCAN_CLOCK_DIV24) || ((__VALUE__) == LL_FDCAN_CLOCK_DIV26) || \
     ((__VALUE__) == LL_FDCAN_CLOCK_DIV28) || ((__VALUE__) == LL_FDCAN_CLOCK_DIV30))

#define IS_LL_FDCAN_FRAME_FORMAT(__VALUE__)                                                  \
    (((__VALUE__) == LL_FDCAN_FRAME_CLASSIC) || ((__VALUE__) == LL_FDCAN_FRAME_FD_NO_BRS) || \
     ((__VALUE__) == LL_FDCAN_FRAME_FD_BRS))

#define IS_LL_FDCAN_MODE(__VALUE__)                         \
    (((__VALUE__) == LL_FDCAN_MODE_NORMAL) ||               \
     ((__VALUE__) == LL_FDCAN_MODE_RESTRICTED_OPERATION) || \
     ((__VALUE__) == LL_FDCAN_MODE_BUS_MONITORING) ||       \
     ((__VALUE__) == LL_FDCAN_MODE_INTERNAL_LOOPBACK) ||    \
     ((__VALUE__) == LL_FDCAN_MODE_EXTERNAL_LOOPBACK))

#define IS_LL_FDCAN_STATE(__VALUE__)                          \
    (((__VALUE__) == LL_FDCAN_AUTO_RETRANSMISSION_ENABLE) ||  \
     ((__VALUE__) == LL_FDCAN_AUTO_RETRANSMISSION_DISABLE) || \
     ((__VALUE__) == LL_FDCAN_TRANSMIT_PAUSE_DISABLE) ||      \
     ((__VALUE__) == LL_FDCAN_TRANSMIT_PAUSE_ENABLE) ||       \
     ((__VALUE__) == LL_FDCAN_PROTOCOL_EXCEPTION_ENABLE) ||   \
     ((__VALUE__) == LL_FDCAN_PROTOCOL_EXCEPTION_DISABLE))

#define IS_LL_FDCAN_NOMINAL_PRESCALER(__VALUE__) (((__VALUE__) >= 1U) && ((__VALUE__) <= 512U))
#define IS_LL_FDCAN_NOMINAL_SJW(__VALUE__) (((__VALUE__) >= 1U) && ((__VALUE__) <= 128U))
#define IS_LL_FDCAN_NOMINAL_TSEG1(__VALUE__) (((__VALUE__) >= 1U) && ((__VALUE__) <= 256U))
#define IS_LL_FDCAN_NOMINAL_TSEG2(__VALUE__) (((__VALUE__) >= 1U) && ((__VALUE__) <= 128U))
#define IS_LL_FDCAN_DATA_PRESCALER(__VALUE__) (((__VALUE__) >= 1U) && ((__VALUE__) <= 32U))
#define IS_LL_FDCAN_DATA_SJW(__VALUE__) (((__VALUE__) >= 1U) && ((__VALUE__) <= 16U))
#define IS_LL_FDCAN_DATA_TSEG1(__VALUE__) (((__VALUE__) >= 1U) && ((__VALUE__) <= 32U))
#define IS_LL_FDCAN_DATA_TSEG2(__VALUE__) (((__VALUE__) >= 1U) && ((__VALUE__) <= 16U))
#define IS_LL_FDCAN_MAX_VALUE(__VALUE__, __MAX__) ((__VALUE__) <= (__MAX__))

#define IS_LL_FDCAN_TX_FIFO_QUEUE_MODE(__VALUE__) \
    (((__VALUE__) == LL_FDCAN_TX_FIFO_OPERATION) || ((__VALUE__) == LL_FDCAN_TX_QUEUE_OPERATION))

#define IS_LL_FDCAN_ID_TYPE(__VALUE__) \
    (((__VALUE__) == LL_FDCAN_STANDARD_ID) || ((__VALUE__) == LL_FDCAN_EXTENDED_ID))

#define IS_LL_FDCAN_FILTER_CFG(__VALUE__)                                                       \
    (((__VALUE__) == LL_FDCAN_FILTER_DISABLE) || ((__VALUE__) == LL_FDCAN_FILTER_TO_RXFIFO0) || \
     ((__VALUE__) == LL_FDCAN_FILTER_TO_RXFIFO1) || ((__VALUE__) == LL_FDCAN_FILTER_REJECT) ||  \
     ((__VALUE__) == LL_FDCAN_FILTER_HP) || ((__VALUE__) == LL_FDCAN_FILTER_TO_RXFIFO0_HP) ||   \
     ((__VALUE__) == LL_FDCAN_FILTER_TO_RXFIFO1_HP))

#define IS_LL_FDCAN_STD_FILTER_TYPE(__VALUE__)                                          \
    (((__VALUE__) == LL_FDCAN_FILTER_RANGE) || ((__VALUE__) == LL_FDCAN_FILTER_DUAL) || \
     ((__VALUE__) == LL_FDCAN_FILTER_MASK))

#define IS_LL_FDCAN_EXT_FILTER_TYPE(__VALUE__)                                          \
    (((__VALUE__) == LL_FDCAN_FILTER_RANGE) || ((__VALUE__) == LL_FDCAN_FILTER_DUAL) || \
     ((__VALUE__) == LL_FDCAN_FILTER_MASK) || ((__VALUE__) == LL_FDCAN_FILTER_RANGE_NO_EIDM))

#define IS_LL_FDCAN_FRAME_TYPE(__VALUE__) \
    (((__VALUE__) == LL_FDCAN_DATA_FRAME) || ((__VALUE__) == LL_FDCAN_REMOTE_FRAME))

#define IS_LL_FDCAN_DLC(__VALUE__)                                                       \
    (((__VALUE__) == LL_FDCAN_DLC_BYTES_0) || ((__VALUE__) == LL_FDCAN_DLC_BYTES_1) ||   \
     ((__VALUE__) == LL_FDCAN_DLC_BYTES_2) || ((__VALUE__) == LL_FDCAN_DLC_BYTES_3) ||   \
     ((__VALUE__) == LL_FDCAN_DLC_BYTES_4) || ((__VALUE__) == LL_FDCAN_DLC_BYTES_5) ||   \
     ((__VALUE__) == LL_FDCAN_DLC_BYTES_6) || ((__VALUE__) == LL_FDCAN_DLC_BYTES_7) ||   \
     ((__VALUE__) == LL_FDCAN_DLC_BYTES_8) || ((__VALUE__) == LL_FDCAN_DLC_BYTES_12) ||  \
     ((__VALUE__) == LL_FDCAN_DLC_BYTES_16) || ((__VALUE__) == LL_FDCAN_DLC_BYTES_20) || \
     ((__VALUE__) == LL_FDCAN_DLC_BYTES_24) || ((__VALUE__) == LL_FDCAN_DLC_BYTES_32) || \
     ((__VALUE__) == LL_FDCAN_DLC_BYTES_48) || ((__VALUE__) == LL_FDCAN_DLC_BYTES_64))

#define IS_LL_FDCAN_ESI(__VALUE__) \
    (((__VALUE__) == LL_FDCAN_ESI_ACTIVE) || ((__VALUE__) == LL_FDCAN_ESI_PASSIVE))

#define IS_LL_FDCAN_BRS(__VALUE__) \
    (((__VALUE__) == LL_FDCAN_BRS_OFF) || ((__VALUE__) == LL_FDCAN_BRS_ON))

#define IS_LL_FDCAN_FDF(__VALUE__) \
    (((__VALUE__) == LL_FDCAN_CLASSIC_CAN) || ((__VALUE__) == LL_FDCAN_FD_CAN))

#define IS_LL_FDCAN_EFC(__VALUE__) \
    (((__VALUE__) == LL_FDCAN_NO_TX_EVENTS) || ((__VALUE__) == LL_FDCAN_STORE_TX_EVENTS))

#define IS_LL_FDCAN_RX_FIFO(__VALUE__) \
    (((__VALUE__) == LL_FDCAN_RX_FIFO0) || ((__VALUE__) == LL_FDCAN_RX_FIFO1))
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
static void FDCAN_CopyMessageToRAM(
    const LL_FDCAN_MessageRAMTypeDef* MessageRAM,
    const LL_FDCAN_TxHeaderTypeDef* TxHeader,
    const uint8_t* TxData,
    uint32_t BufferIndex);

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FDCAN_LL_Exported_Functions
  * @{
  */

/** @addtogroup FDCAN_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the FDCAN registers to their default reset values.
  * @param  FDCANx FDCAN Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: FDCAN registers are de-initialized
  *          - ERROR: FDCAN registers are not de-initialized
  */
ErrorStatus LL_FDCAN_DeInit(const FDCAN_GlobalTypeDef* FDCANx) {
    ErrorStatus status = ERROR;

    /* Check the parameters */
    assert_param(IS_LL_FDCAN_ALL_INSTANCE(FDCANx));

#if defined(FDCAN1)
    if(FDCANx == FDCAN1) {
        /* Force reset of FDCAN clock */
        LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_FDCAN1);

        /* Release reset of FDCAN clock */
        LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_FDCAN1);

        status = SUCCESS;
    }
#endif /* FDCAN1 */

    return status;
}

/**
  * @brief  Initialize the FDCAN registers according to the specified parameters in FDCAN_InitStruct.
  * @param  FDCANx FDCAN Instance
  * @param  FDCAN_InitStruct pointer to a @ref LL_FDCAN_InitTypeDef structure
  * @param  MessageRAM pointer to a @ref LL_FDCAN_MessageRAMTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: FDCAN registers are initialized
  *          - ERROR: FDCAN registers are not initialized
  */
ErrorStatus LL_FDCAN_Init(
    FDCAN_GlobalTypeDef* FDCANx,
    const LL_FDCAN_InitTypeDef* FDCAN_InitStruct,
    LL_FDCAN_MessageRAMTypeDef* MessageRAM) {
    ErrorStatus status = ERROR;
    uint32_t counter;

    /* Check the parameters */
    assert_param(IS_LL_FDCAN_ALL_INSTANCE(FDCANx));
    assert_param(IS_LL_FDCAN_CKDIV(FDCAN_InitStruct->ClockDivider));
    assert_param(IS_LL_FDCAN_FRAME_FORMAT(FDCAN_InitStruct->FrameFormat));
    assert_param(IS_LL_FDCAN_MODE(FDCAN_InitStruct->Mode));
    assert_param(IS_LL_FDCAN_STATE(FDCAN_InitStruct->AutoRetransmission));
    assert_param(IS_LL_FDCAN_STATE(FDCAN_InitStruct->TransmitPause));
    assert_param(IS_LL_FDCAN_STATE(FDCAN_InitStruct->ProtocolException));
    assert_param(IS_LL_FDCAN_NOMINAL_PRESCALER(FDCAN_InitStruct->NominalPrescaler));
    assert_param(IS_LL_FDCAN_NOMINAL_SJW(FDCAN_InitStruct->NominalSyncJumpWidth));
    assert_param(IS_LL_FDCAN_NOMINAL_TSEG1(FDCAN_InitStruct->NominalTimeSeg1));
    assert_param(IS_LL_FDCAN_NOMINAL_TSEG2(FDCAN_InitStruct->NominalTimeSeg2));
    assert_param(IS_LL_FDCAN_DATA_PRESCALER(FDCAN_InitStruct->DataPrescaler));
    assert_param(IS_LL_FDCAN_DATA_SJW(FDCAN_InitStruct->DataSyncJumpWidth));
    assert_param(IS_LL_FDCAN_DATA_TSEG1(FDCAN_InitStruct->DataTimeSeg1));
    assert_param(IS_LL_FDCAN_DATA_TSEG2(FDCAN_InitStruct->DataTimeSeg2));
    assert_param(IS_LL_FDCAN_MAX_VALUE(FDCAN_InitStruct->StdFiltersNbr, SRAMCAN_FLS_NBR));
    assert_param(IS_LL_FDCAN_MAX_VALUE(FDCAN_InitStruct->ExtFiltersNbr, SRAMCAN_FLE_NBR));
    assert_param(IS_LL_FDCAN_TX_FIFO_QUEUE_MODE(FDCAN_InitStruct->TxFifoQueueMode));

    /* Exit from sleep mode */
    LL_FDCAN_ExitSleep(FDCANx);

    counter = LL_FDCAN_TIMEOUT_VALUE;
    while(LL_FDCAN_IsActiveFlag_CSA(FDCANx) != 0UL) {
        if(counter == 0UL) {
            return ERROR;
        }
        counter--;
    }

    /* Request initialization mode */
    LL_FDCAN_RequestInit(FDCANx);

    counter = LL_FDCAN_TIMEOUT_VALUE;
    while(LL_FDCAN_IsActiveFlag_INIT(FDCANx) == 0UL) {
        if(counter == 0UL) {
            return ERROR;
        }
        counter--;
    }

    /* Enable configuration change */
    LL_FDCAN_EnableConfigurationChange(FDCANx);

    LL_FDCAN_SetClockDivider(FDCAN_InitStruct->ClockDivider);

    MODIFY_REG(
        FDCANx->CCCR,
        FDCAN_CCCR_DAR | FDCAN_CCCR_TXP | FDCAN_CCCR_PXHD,
        FDCAN_InitStruct->AutoRetransmission | FDCAN_InitStruct->TransmitPause |
            FDCAN_InitStruct->ProtocolException);

    LL_FDCAN_SetFrameFormat(FDCANx, FDCAN_InitStruct->FrameFormat);

    /* Reset operating mode */
    CLEAR_BIT(FDCANx->CCCR, FDCAN_CCCR_TEST | FDCAN_CCCR_MON | FDCAN_CCCR_ASM);
    CLEAR_BIT(FDCANx->TEST, FDCAN_TEST_LBCK);

    if(FDCAN_InitStruct->Mode == LL_FDCAN_MODE_RESTRICTED_OPERATION) {
        SET_BIT(FDCANx->CCCR, FDCAN_CCCR_ASM);
    } else if(FDCAN_InitStruct->Mode != LL_FDCAN_MODE_NORMAL) {
        if(FDCAN_InitStruct->Mode != LL_FDCAN_MODE_BUS_MONITORING) {
            SET_BIT(FDCANx->CCCR, FDCAN_CCCR_TEST);
            SET_BIT(FDCANx->TEST, FDCAN_TEST_LBCK);

            if(FDCAN_InitStruct->Mode == LL_FDCAN_MODE_INTERNAL_LOOPBACK) {
                SET_BIT(FDCANx->CCCR, FDCAN_CCCR_MON);
            }
        } else {
            SET_BIT(FDCANx->CCCR, FDCAN_CCCR_MON);
        }
    } else {
        /* Nothing to do: normal mode */
    }

    LL_FDCAN_SetNominalBitTiming(
        FDCANx,
        FDCAN_InitStruct->NominalPrescaler,
        FDCAN_InitStruct->NominalSyncJumpWidth,
        FDCAN_InitStruct->NominalTimeSeg1,
        FDCAN_InitStruct->NominalTimeSeg2);

    LL_FDCAN_SetDataBitTiming(
        FDCANx,
        FDCAN_InitStruct->DataPrescaler,
        FDCAN_InitStruct->DataSyncJumpWidth,
        FDCAN_InitStruct->DataTimeSeg1,
        FDCAN_InitStruct->DataTimeSeg2);

    LL_FDCAN_SetTxFifoQueueMode(FDCANx, FDCAN_InitStruct->TxFifoQueueMode);

    LL_FDCAN_ConfigMessageRAM(
        FDCANx, FDCAN_InitStruct->StdFiltersNbr, FDCAN_InitStruct->ExtFiltersNbr, MessageRAM);

    status = SUCCESS;

    return status;
}

/**
  * @brief  Set each @ref LL_FDCAN_InitTypeDef field to default value.
  * @param  FDCAN_InitStruct pointer to a @ref LL_FDCAN_InitTypeDef structure
  * @retval None
  */
void LL_FDCAN_StructInit(LL_FDCAN_InitTypeDef* FDCAN_InitStruct) {
    FDCAN_InitStruct->ClockDivider = LL_FDCAN_CLOCK_DIV1;
    FDCAN_InitStruct->FrameFormat = LL_FDCAN_FRAME_CLASSIC;
    FDCAN_InitStruct->Mode = LL_FDCAN_MODE_NORMAL;
    FDCAN_InitStruct->AutoRetransmission = LL_FDCAN_AUTO_RETRANSMISSION_ENABLE;
    FDCAN_InitStruct->TransmitPause = LL_FDCAN_TRANSMIT_PAUSE_DISABLE;
    FDCAN_InitStruct->ProtocolException = LL_FDCAN_PROTOCOL_EXCEPTION_ENABLE;
    FDCAN_InitStruct->NominalPrescaler = 1U;
    FDCAN_InitStruct->NominalSyncJumpWidth = 1U;
    FDCAN_InitStruct->NominalTimeSeg1 = 2U;
    FDCAN_InitStruct->NominalTimeSeg2 = 2U;
    FDCAN_InitStruct->DataPrescaler = 1U;
    FDCAN_InitStruct->DataSyncJumpWidth = 1U;
    FDCAN_InitStruct->DataTimeSeg1 = 1U;
    FDCAN_InitStruct->DataTimeSeg2 = 1U;
    FDCAN_InitStruct->StdFiltersNbr = 0U;
    FDCAN_InitStruct->ExtFiltersNbr = 0U;
    FDCAN_InitStruct->TxFifoQueueMode = LL_FDCAN_TX_FIFO_OPERATION;
}

/**
  * @brief  Set each @ref LL_FDCAN_MessageRAMTypeDef field to default value.
  * @param  MessageRAM pointer to a @ref LL_FDCAN_MessageRAMTypeDef structure
  * @retval None
  */
void LL_FDCAN_MessageRAMStructInit(LL_FDCAN_MessageRAMTypeDef* MessageRAM) {
    MessageRAM->StandardFilterSA = SRAMCAN_BASE + SRAMCAN_FLSSA;
    MessageRAM->ExtendedFilterSA = SRAMCAN_BASE + SRAMCAN_FLESA;
    MessageRAM->RxFIFO0SA = SRAMCAN_BASE + SRAMCAN_RF0SA;
    MessageRAM->RxFIFO1SA = SRAMCAN_BASE + SRAMCAN_RF1SA;
    MessageRAM->TxEventFIFOSA = SRAMCAN_BASE + SRAMCAN_TEFSA;
    MessageRAM->TxFIFOQSA = SRAMCAN_BASE + SRAMCAN_TFQSA;
}

/**
  * @}
  */

/** @addtogroup FDCAN_LL_EF_Message_RAM
  * @{
  */

/**
  * @brief  Configure the FDCAN message RAM block addresses and filter list sizes.
  * @param  FDCANx FDCAN Instance
  * @param  StdFiltersNbr Number of standard filters
  * @param  ExtFiltersNbr Number of extended filters
  * @param  MessageRAM pointer to a @ref LL_FDCAN_MessageRAMTypeDef structure
  * @retval None
  */
void LL_FDCAN_ConfigMessageRAM(
    FDCAN_GlobalTypeDef* FDCANx,
    uint32_t StdFiltersNbr,
    uint32_t ExtFiltersNbr,
    LL_FDCAN_MessageRAMTypeDef* MessageRAM) {
    assert_param(IS_LL_FDCAN_ALL_INSTANCE(FDCANx));
    assert_param(IS_LL_FDCAN_MAX_VALUE(StdFiltersNbr, SRAMCAN_FLS_NBR));
    assert_param(IS_LL_FDCAN_MAX_VALUE(ExtFiltersNbr, SRAMCAN_FLE_NBR));

    LL_FDCAN_MessageRAMStructInit(MessageRAM);
    LL_FDCAN_SetFilterListSize(FDCANx, StdFiltersNbr, ExtFiltersNbr);
    LL_FDCAN_FlushMessageRAM();
}

/**
  * @brief  Flush the fixed FDCAN message RAM area.
  * @retval None
  */
void LL_FDCAN_FlushMessageRAM(void) {
    uint32_t ram_counter;

    for(ram_counter = SRAMCAN_BASE; ram_counter < (SRAMCAN_BASE + SRAMCAN_SIZE);
        ram_counter += 4U) {
        *(uint32_t*)ram_counter = 0x00000000UL;
    }
}

/**
  * @brief  Configure an FDCAN reception filter in message RAM.
  * @param  MessageRAM pointer to a @ref LL_FDCAN_MessageRAMTypeDef structure
  * @param  FilterConfig pointer to a @ref LL_FDCAN_FilterTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: filter is configured
  *          - ERROR: filter is not configured
  */
ErrorStatus LL_FDCAN_ConfigFilter(
    const LL_FDCAN_MessageRAMTypeDef* MessageRAM,
    const LL_FDCAN_FilterTypeDef* FilterConfig) {
    uint32_t filter_element_w1;
    uint32_t filter_element_w2;
    uint32_t* filter_address;

    assert_param(IS_LL_FDCAN_ID_TYPE(FilterConfig->IdType));
    assert_param(IS_LL_FDCAN_FILTER_CFG(FilterConfig->FilterConfig));

    if(FilterConfig->IdType == LL_FDCAN_STANDARD_ID) {
        assert_param(IS_LL_FDCAN_MAX_VALUE(FilterConfig->FilterIndex, SRAMCAN_FLS_NBR - 1U));
        assert_param(IS_LL_FDCAN_MAX_VALUE(FilterConfig->FilterID1, 0x7FFU));
        assert_param(IS_LL_FDCAN_MAX_VALUE(FilterConfig->FilterID2, 0x7FFU));
        assert_param(IS_LL_FDCAN_STD_FILTER_TYPE(FilterConfig->FilterType));

        filter_element_w1 =
            ((FilterConfig->FilterType << 30U) | (FilterConfig->FilterConfig << 27U) |
             (FilterConfig->FilterID1 << 16U) | FilterConfig->FilterID2);

        filter_address = (uint32_t*)(MessageRAM->StandardFilterSA +
                                     (FilterConfig->FilterIndex * SRAMCAN_FLS_SIZE));
        *filter_address = filter_element_w1;
    } else {
        assert_param(IS_LL_FDCAN_MAX_VALUE(FilterConfig->FilterIndex, SRAMCAN_FLE_NBR - 1U));
        assert_param(IS_LL_FDCAN_MAX_VALUE(FilterConfig->FilterID1, 0x1FFFFFFFU));
        assert_param(IS_LL_FDCAN_MAX_VALUE(FilterConfig->FilterID2, 0x1FFFFFFFU));
        assert_param(IS_LL_FDCAN_EXT_FILTER_TYPE(FilterConfig->FilterType));

        filter_element_w1 = ((FilterConfig->FilterConfig << 29U) | FilterConfig->FilterID1);
        filter_element_w2 = ((FilterConfig->FilterType << 30U) | FilterConfig->FilterID2);

        filter_address = (uint32_t*)(MessageRAM->ExtendedFilterSA +
                                     (FilterConfig->FilterIndex * SRAMCAN_FLE_SIZE));
        *filter_address = filter_element_w1;
        filter_address++;
        *filter_address = filter_element_w2;
    }

    return SUCCESS;
}

/**
  * @brief  Add a message to the Tx FIFO/Queue and activate transmission request.
  * @param  FDCANx FDCAN Instance
  * @param  MessageRAM pointer to a @ref LL_FDCAN_MessageRAMTypeDef structure
  * @param  TxHeader pointer to a @ref LL_FDCAN_TxHeaderTypeDef structure
  * @param  TxData pointer to a buffer containing the payload
  * @param  TxBufferIndex pointer to the Tx buffer bit index used for this request.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: message is queued
  *          - ERROR: Tx FIFO/Queue is full
  */
ErrorStatus LL_FDCAN_AddMessageToTxFifoQ(
    FDCAN_GlobalTypeDef* FDCANx,
    const LL_FDCAN_MessageRAMTypeDef* MessageRAM,
    const LL_FDCAN_TxHeaderTypeDef* TxHeader,
    const uint8_t* TxData,
    uint32_t* TxBufferIndex) {
    uint32_t put_index;
    uint32_t tx_buffer_index;

    assert_param(IS_LL_FDCAN_ALL_INSTANCE(FDCANx));
    assert_param(IS_LL_FDCAN_ID_TYPE(TxHeader->IdType));
    if(TxHeader->IdType == LL_FDCAN_STANDARD_ID) {
        assert_param(IS_LL_FDCAN_MAX_VALUE(TxHeader->Identifier, 0x7FFU));
    } else {
        assert_param(IS_LL_FDCAN_MAX_VALUE(TxHeader->Identifier, 0x1FFFFFFFU));
    }
    assert_param(IS_LL_FDCAN_FRAME_TYPE(TxHeader->TxFrameType));
    assert_param(IS_LL_FDCAN_DLC(TxHeader->DataLength));
    assert_param(IS_LL_FDCAN_ESI(TxHeader->ErrorStateIndicator));
    assert_param(IS_LL_FDCAN_BRS(TxHeader->BitRateSwitch));
    assert_param(IS_LL_FDCAN_FDF(TxHeader->FDFormat));
    assert_param(IS_LL_FDCAN_EFC(TxHeader->TxEventFifoControl));
    assert_param(IS_LL_FDCAN_MAX_VALUE(TxHeader->MessageMarker, 0xFFU));

    if(LL_FDCAN_IsActiveFlag_TxFifoFull(FDCANx) != 0UL) {
        return ERROR;
    }

    put_index = LL_FDCAN_GetTxFifoQueuePutIndex(FDCANx);
    tx_buffer_index = (1UL << put_index);

    FDCAN_CopyMessageToRAM(MessageRAM, TxHeader, TxData, put_index);
    LL_FDCAN_AddTxRequest(FDCANx, tx_buffer_index);

    if(TxBufferIndex != NULL) {
        *TxBufferIndex = tx_buffer_index;
    }

    return SUCCESS;
}

/**
  * @brief  Get an FDCAN frame from an Rx FIFO message RAM element.
  * @param  FDCANx FDCAN Instance
  * @param  MessageRAM pointer to a @ref LL_FDCAN_MessageRAMTypeDef structure
  * @param  RxFifo This parameter can be a value of @ref FDCAN_LL_EC_RX_FIFO
  * @param  RxHeader pointer to a @ref LL_FDCAN_RxHeaderTypeDef structure
  * @param  RxData pointer to a buffer where payload will be copied
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: message is read
  *          - ERROR: Rx FIFO is empty
  */
ErrorStatus LL_FDCAN_GetRxMessage(
    FDCAN_GlobalTypeDef* FDCANx,
    const LL_FDCAN_MessageRAMTypeDef* MessageRAM,
    uint32_t RxFifo,
    LL_FDCAN_RxHeaderTypeDef* RxHeader,
    uint8_t* RxData) {
    uint32_t* rx_address;
    uint8_t* pdata;
    uint32_t byte_counter;
    uint32_t get_index = 0U;

    assert_param(IS_LL_FDCAN_ALL_INSTANCE(FDCANx));
    assert_param(IS_LL_FDCAN_RX_FIFO(RxFifo));

    if(RxFifo == LL_FDCAN_RX_FIFO0) {
        if(READ_BIT(FDCANx->RXF0S, FDCAN_RXF0S_F0FL) == 0UL) {
            return ERROR;
        }

        if((READ_BIT(FDCANx->RXF0S, FDCAN_RXF0S_F0F) >> FDCAN_RXF0S_F0F_Pos) == 1UL) {
            if((READ_BIT(FDCANx->RXGFC, FDCAN_RXGFC_F0OM) >> FDCAN_RXGFC_F0OM_Pos) ==
               LL_FDCAN_RX_FIFO_OVERWRITE) {
                get_index = 1U;
            }
        }

        get_index += (READ_BIT(FDCANx->RXF0S, FDCAN_RXF0S_F0GI) >> FDCAN_RXF0S_F0GI_Pos);
        rx_address = (uint32_t*)(MessageRAM->RxFIFO0SA + (get_index * SRAMCAN_RF0_SIZE));
    } else {
        if(READ_BIT(FDCANx->RXF1S, FDCAN_RXF1S_F1FL) == 0UL) {
            return ERROR;
        }

        if((READ_BIT(FDCANx->RXF1S, FDCAN_RXF1S_F1F) >> FDCAN_RXF1S_F1F_Pos) == 1UL) {
            if((READ_BIT(FDCANx->RXGFC, FDCAN_RXGFC_F1OM) >> FDCAN_RXGFC_F1OM_Pos) ==
               LL_FDCAN_RX_FIFO_OVERWRITE) {
                get_index = 1U;
            }
        }

        get_index += (READ_BIT(FDCANx->RXF1S, FDCAN_RXF1S_F1GI) >> FDCAN_RXF1S_F1GI_Pos);
        rx_address = (uint32_t*)(MessageRAM->RxFIFO1SA + (get_index * SRAMCAN_RF1_SIZE));
    }

    RxHeader->IdType = *rx_address & FDCAN_ELEMENT_MASK_XTD;
    if(RxHeader->IdType == LL_FDCAN_STANDARD_ID) {
        RxHeader->Identifier = ((*rx_address & FDCAN_ELEMENT_MASK_STDID) >> 18U);
    } else {
        RxHeader->Identifier = (*rx_address & FDCAN_ELEMENT_MASK_EXTID);
    }

    RxHeader->RxFrameType = (*rx_address & FDCAN_ELEMENT_MASK_RTR);
    RxHeader->ErrorStateIndicator = (*rx_address & FDCAN_ELEMENT_MASK_ESI);

    rx_address++;

    RxHeader->RxTimestamp = (*rx_address & FDCAN_ELEMENT_MASK_TS);
    RxHeader->DataLength = ((*rx_address & FDCAN_ELEMENT_MASK_DLC) >> 16U);
    RxHeader->BitRateSwitch = (*rx_address & FDCAN_ELEMENT_MASK_BRS);
    RxHeader->FDFormat = (*rx_address & FDCAN_ELEMENT_MASK_FDF);
    RxHeader->FilterIndex = ((*rx_address & FDCAN_ELEMENT_MASK_FIDX) >> 24U);
    RxHeader->IsFilterMatchingFrame = ((*rx_address & FDCAN_ELEMENT_MASK_ANMF) >> 31U);

    rx_address++;

    pdata = (uint8_t*)rx_address;
    for(byte_counter = 0U; byte_counter < DLCtoBytes[RxHeader->DataLength]; byte_counter++) {
        RxData[byte_counter] = pdata[byte_counter];
    }

    if(RxFifo == LL_FDCAN_RX_FIFO0) {
        WRITE_REG(FDCANx->RXF0A, get_index);
    } else {
        WRITE_REG(FDCANx->RXF1A, get_index);
    }

    return SUCCESS;
}

/**
  * @brief  Convert an FDCAN data length code to a number of payload bytes.
  * @param  DataLength This parameter can be a value of @ref FDCAN_LL_EC_DATA_LENGTH
  * @retval Number of bytes.
  */
uint32_t LL_FDCAN_DLCToBytes(uint32_t DataLength) {
    assert_param(IS_LL_FDCAN_DLC(DataLength));
    return DLCtoBytes[DataLength];
}

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Copy Tx message to the message RAM.
  * @param  MessageRAM pointer to a @ref LL_FDCAN_MessageRAMTypeDef structure
  * @param  TxHeader pointer to a @ref LL_FDCAN_TxHeaderTypeDef structure
  * @param  TxData pointer to a buffer containing the payload
  * @param  BufferIndex index of the buffer to be configured
  * @retval None
  */
static void FDCAN_CopyMessageToRAM(
    const LL_FDCAN_MessageRAMTypeDef* MessageRAM,
    const LL_FDCAN_TxHeaderTypeDef* TxHeader,
    const uint8_t* TxData,
    uint32_t BufferIndex) {
    uint32_t tx_element_w1;
    uint32_t tx_element_w2;
    uint32_t* tx_address;
    uint32_t byte_counter;

    if(TxHeader->IdType == LL_FDCAN_STANDARD_ID) {
        tx_element_w1 =
            (TxHeader->ErrorStateIndicator | LL_FDCAN_STANDARD_ID | TxHeader->TxFrameType |
             (TxHeader->Identifier << 18U));
    } else {
        tx_element_w1 =
            (TxHeader->ErrorStateIndicator | LL_FDCAN_EXTENDED_ID | TxHeader->TxFrameType |
             TxHeader->Identifier);
    }

    tx_element_w2 =
        ((TxHeader->MessageMarker << 24U) | TxHeader->TxEventFifoControl | TxHeader->FDFormat |
         TxHeader->BitRateSwitch | (TxHeader->DataLength << 16U));

    tx_address = (uint32_t*)(MessageRAM->TxFIFOQSA + (BufferIndex * SRAMCAN_TFQ_SIZE));

    *tx_address = tx_element_w1;
    tx_address++;
    *tx_address = tx_element_w2;
    tx_address++;

    for(byte_counter = 0U; byte_counter < DLCtoBytes[TxHeader->DataLength]; byte_counter += 4U) {
        *tx_address =
            (((uint32_t)TxData[byte_counter + 3U] << 24U) |
             ((uint32_t)TxData[byte_counter + 2U] << 16U) |
             ((uint32_t)TxData[byte_counter + 1U] << 8U) | (uint32_t)TxData[byte_counter]);
        tx_address++;
    }
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(FDCAN1) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
