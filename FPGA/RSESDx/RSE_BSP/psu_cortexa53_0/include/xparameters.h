#ifndef XPARAMETERS_H   /* prevent circular inclusions */
#define XPARAMETERS_H   /* by using protection macros */

/* Definition for CPU ID */
#define XPAR_CPU_ID 0

/* Definitions for peripheral PSU_CORTEXA53_0 */
#define XPAR_PSU_CORTEXA53_0_CPU_CLK_FREQ_HZ 1333320000
#define XPAR_PSU_CORTEXA53_0_TIMESTAMP_CLK_FREQ 33333000


/******************************************************************/

/* Canonical definitions for peripheral PSU_CORTEXA53_0 */
#define XPAR_CPU_CORTEXA53_0_CPU_CLK_FREQ_HZ 1333320000
#define XPAR_CPU_CORTEXA53_0_TIMESTAMP_CLK_FREQ 33333000


/******************************************************************/

 /* Definition for PSS REF CLK FREQUENCY */
#define XPAR_PSU_PSS_REF_CLK_FREQ_HZ 33333000U

#include "xparameters_ps.h"

#define XPS_BOARD_ZCU102


/* Number of Fabric Resets */
#define XPAR_NUM_FABRIC_RESETS 2

#define STDIN_BASEADDRESS 0xFE800000
#define STDOUT_BASEADDRESS 0xFE800000

/******************************************************************/

/* Definitions for driver AXIPMON */
#define XPAR_XAXIPMON_NUM_INSTANCES 4

/* Definitions for peripheral PSU_APM_0 */
#define XPAR_PSU_APM_0_DEVICE_ID 0
#define XPAR_PSU_APM_0_BASEADDR 0xFD0B0000
#define XPAR_PSU_APM_0_HIGHADDR 0xFD0BFFFF
#define XPAR_PSU_APM_0_GLOBAL_COUNT_WIDTH 32
#define XPAR_PSU_APM_0_METRICS_SAMPLE_COUNT_WIDTH 32
#define XPAR_PSU_APM_0_ENABLE_EVENT_COUNT 1
#define XPAR_PSU_APM_0_NUM_MONITOR_SLOTS 6
#define XPAR_PSU_APM_0_NUM_OF_COUNTERS 10
#define XPAR_PSU_APM_0_HAVE_SAMPLED_METRIC_CNT 1
#define XPAR_PSU_APM_0_ENABLE_EVENT_LOG 0
#define XPAR_PSU_APM_0_FIFO_AXIS_DEPTH 32
#define XPAR_PSU_APM_0_FIFO_AXIS_TDATA_WIDTH 56
#define XPAR_PSU_APM_0_FIFO_AXIS_TID_WIDTH 1
#define XPAR_PSU_APM_0_METRIC_COUNT_SCALE 1
#define XPAR_PSU_APM_0_ENABLE_ADVANCED 1
#define XPAR_PSU_APM_0_ENABLE_PROFILE 0
#define XPAR_PSU_APM_0_ENABLE_TRACE 0
#define XPAR_PSU_APM_0_S_AXI4_BASEADDR 0x00000000
#define XPAR_PSU_APM_0_S_AXI4_HIGHADDR 0x00000000
#define XPAR_PSU_APM_0_ENABLE_32BIT_FILTER_ID 1


/* Definitions for peripheral PSU_APM_1 */
#define XPAR_PSU_APM_1_DEVICE_ID 1
#define XPAR_PSU_APM_1_BASEADDR 0xFFA00000
#define XPAR_PSU_APM_1_HIGHADDR 0xFFA0FFFF
#define XPAR_PSU_APM_1_GLOBAL_COUNT_WIDTH 32
#define XPAR_PSU_APM_1_METRICS_SAMPLE_COUNT_WIDTH 32
#define XPAR_PSU_APM_1_ENABLE_EVENT_COUNT 1
#define XPAR_PSU_APM_1_NUM_MONITOR_SLOTS 1
#define XPAR_PSU_APM_1_NUM_OF_COUNTERS 3
#define XPAR_PSU_APM_1_HAVE_SAMPLED_METRIC_CNT 1
#define XPAR_PSU_APM_1_ENABLE_EVENT_LOG 0
#define XPAR_PSU_APM_1_FIFO_AXIS_DEPTH 32
#define XPAR_PSU_APM_1_FIFO_AXIS_TDATA_WIDTH 56
#define XPAR_PSU_APM_1_FIFO_AXIS_TID_WIDTH 1
#define XPAR_PSU_APM_1_METRIC_COUNT_SCALE 1
#define XPAR_PSU_APM_1_ENABLE_ADVANCED 1
#define XPAR_PSU_APM_1_ENABLE_PROFILE 0
#define XPAR_PSU_APM_1_ENABLE_TRACE 0
#define XPAR_PSU_APM_1_S_AXI4_BASEADDR 0x00000000
#define XPAR_PSU_APM_1_S_AXI4_HIGHADDR 0x00000000
#define XPAR_PSU_APM_1_ENABLE_32BIT_FILTER_ID 1


/* Definitions for peripheral PSU_APM_2 */
#define XPAR_PSU_APM_2_DEVICE_ID 2
#define XPAR_PSU_APM_2_BASEADDR 0xFFA10000
#define XPAR_PSU_APM_2_HIGHADDR 0xFFA1FFFF
#define XPAR_PSU_APM_2_GLOBAL_COUNT_WIDTH 32
#define XPAR_PSU_APM_2_METRICS_SAMPLE_COUNT_WIDTH 32
#define XPAR_PSU_APM_2_ENABLE_EVENT_COUNT 1
#define XPAR_PSU_APM_2_NUM_MONITOR_SLOTS 1
#define XPAR_PSU_APM_2_NUM_OF_COUNTERS 3
#define XPAR_PSU_APM_2_HAVE_SAMPLED_METRIC_CNT 1
#define XPAR_PSU_APM_2_ENABLE_EVENT_LOG 0
#define XPAR_PSU_APM_2_FIFO_AXIS_DEPTH 32
#define XPAR_PSU_APM_2_FIFO_AXIS_TDATA_WIDTH 56
#define XPAR_PSU_APM_2_FIFO_AXIS_TID_WIDTH 1
#define XPAR_PSU_APM_2_METRIC_COUNT_SCALE 1
#define XPAR_PSU_APM_2_ENABLE_ADVANCED 1
#define XPAR_PSU_APM_2_ENABLE_PROFILE 0
#define XPAR_PSU_APM_2_ENABLE_TRACE 0
#define XPAR_PSU_APM_2_S_AXI4_BASEADDR 0x00000000
#define XPAR_PSU_APM_2_S_AXI4_HIGHADDR 0x00000000
#define XPAR_PSU_APM_2_ENABLE_32BIT_FILTER_ID 1


/* Definitions for peripheral PSU_APM_5 */
#define XPAR_PSU_APM_5_DEVICE_ID 3
#define XPAR_PSU_APM_5_BASEADDR 0xFD490000
#define XPAR_PSU_APM_5_HIGHADDR 0xFD49FFFF
#define XPAR_PSU_APM_5_GLOBAL_COUNT_WIDTH 32
#define XPAR_PSU_APM_5_METRICS_SAMPLE_COUNT_WIDTH 32
#define XPAR_PSU_APM_5_ENABLE_EVENT_COUNT 1
#define XPAR_PSU_APM_5_NUM_MONITOR_SLOTS 1
#define XPAR_PSU_APM_5_NUM_OF_COUNTERS 3
#define XPAR_PSU_APM_5_HAVE_SAMPLED_METRIC_CNT 1
#define XPAR_PSU_APM_5_ENABLE_EVENT_LOG 0
#define XPAR_PSU_APM_5_FIFO_AXIS_DEPTH 32
#define XPAR_PSU_APM_5_FIFO_AXIS_TDATA_WIDTH 56
#define XPAR_PSU_APM_5_FIFO_AXIS_TID_WIDTH 1
#define XPAR_PSU_APM_5_METRIC_COUNT_SCALE 1
#define XPAR_PSU_APM_5_ENABLE_ADVANCED 1
#define XPAR_PSU_APM_5_ENABLE_PROFILE 0
#define XPAR_PSU_APM_5_ENABLE_TRACE 0
#define XPAR_PSU_APM_5_S_AXI4_BASEADDR 0x00000000
#define XPAR_PSU_APM_5_S_AXI4_HIGHADDR 0x00000000
#define XPAR_PSU_APM_5_ENABLE_32BIT_FILTER_ID 1


/******************************************************************/

/* Canonical definitions for peripheral PSU_APM_0 */
#define XPAR_AXIPMON_0_DEVICE_ID XPAR_PSU_APM_0_DEVICE_ID
#define XPAR_AXIPMON_0_BASEADDR 0xFD0B0000
#define XPAR_AXIPMON_0_HIGHADDR 0xFD0BFFFF
#define XPAR_AXIPMON_0_GLOBAL_COUNT_WIDTH 32
#define XPAR_AXIPMON_0_METRICS_SAMPLE_COUNT_WIDTH 32
#define XPAR_AXIPMON_0_ENABLE_EVENT_COUNT 1
#define XPAR_AXIPMON_0_NUM_MONITOR_SLOTS 6
#define XPAR_AXIPMON_0_NUM_OF_COUNTERS 10
#define XPAR_AXIPMON_0_HAVE_SAMPLED_METRIC_CNT 1
#define XPAR_AXIPMON_0_ENABLE_EVENT_LOG 0
#define XPAR_AXIPMON_0_FIFO_AXIS_DEPTH 32
#define XPAR_AXIPMON_0_FIFO_AXIS_TDATA_WIDTH 56
#define XPAR_AXIPMON_0_FIFO_AXIS_TID_WIDTH 1
#define XPAR_AXIPMON_0_METRIC_COUNT_SCALE 1
#define XPAR_AXIPMON_0_ENABLE_ADVANCED 1
#define XPAR_AXIPMON_0_ENABLE_PROFILE 0
#define XPAR_AXIPMON_0_ENABLE_TRACE 0
#define XPAR_AXIPMON_0_S_AXI4_BASEADDR 0x00000000
#define XPAR_AXIPMON_0_S_AXI4_HIGHADDR 0x00000000
#define XPAR_AXIPMON_0_ENABLE_32BIT_FILTER_ID 1

/* Canonical definitions for peripheral PSU_APM_1 */
#define XPAR_AXIPMON_1_DEVICE_ID XPAR_PSU_APM_1_DEVICE_ID
#define XPAR_AXIPMON_1_BASEADDR 0xFFA00000
#define XPAR_AXIPMON_1_HIGHADDR 0xFFA0FFFF
#define XPAR_AXIPMON_1_GLOBAL_COUNT_WIDTH 32
#define XPAR_AXIPMON_1_METRICS_SAMPLE_COUNT_WIDTH 32
#define XPAR_AXIPMON_1_ENABLE_EVENT_COUNT 1
#define XPAR_AXIPMON_1_NUM_MONITOR_SLOTS 1
#define XPAR_AXIPMON_1_NUM_OF_COUNTERS 3
#define XPAR_AXIPMON_1_HAVE_SAMPLED_METRIC_CNT 1
#define XPAR_AXIPMON_1_ENABLE_EVENT_LOG 0
#define XPAR_AXIPMON_1_FIFO_AXIS_DEPTH 32
#define XPAR_AXIPMON_1_FIFO_AXIS_TDATA_WIDTH 56
#define XPAR_AXIPMON_1_FIFO_AXIS_TID_WIDTH 1
#define XPAR_AXIPMON_1_METRIC_COUNT_SCALE 1
#define XPAR_AXIPMON_1_ENABLE_ADVANCED 1
#define XPAR_AXIPMON_1_ENABLE_PROFILE 0
#define XPAR_AXIPMON_1_ENABLE_TRACE 0
#define XPAR_AXIPMON_1_S_AXI4_BASEADDR 0x00000000
#define XPAR_AXIPMON_1_S_AXI4_HIGHADDR 0x00000000
#define XPAR_AXIPMON_1_ENABLE_32BIT_FILTER_ID 1

/* Canonical definitions for peripheral PSU_APM_2 */
#define XPAR_AXIPMON_2_DEVICE_ID XPAR_PSU_APM_2_DEVICE_ID
#define XPAR_AXIPMON_2_BASEADDR 0xFFA10000
#define XPAR_AXIPMON_2_HIGHADDR 0xFFA1FFFF
#define XPAR_AXIPMON_2_GLOBAL_COUNT_WIDTH 32
#define XPAR_AXIPMON_2_METRICS_SAMPLE_COUNT_WIDTH 32
#define XPAR_AXIPMON_2_ENABLE_EVENT_COUNT 1
#define XPAR_AXIPMON_2_NUM_MONITOR_SLOTS 1
#define XPAR_AXIPMON_2_NUM_OF_COUNTERS 3
#define XPAR_AXIPMON_2_HAVE_SAMPLED_METRIC_CNT 1
#define XPAR_AXIPMON_2_ENABLE_EVENT_LOG 0
#define XPAR_AXIPMON_2_FIFO_AXIS_DEPTH 32
#define XPAR_AXIPMON_2_FIFO_AXIS_TDATA_WIDTH 56
#define XPAR_AXIPMON_2_FIFO_AXIS_TID_WIDTH 1
#define XPAR_AXIPMON_2_METRIC_COUNT_SCALE 1
#define XPAR_AXIPMON_2_ENABLE_ADVANCED 1
#define XPAR_AXIPMON_2_ENABLE_PROFILE 0
#define XPAR_AXIPMON_2_ENABLE_TRACE 0
#define XPAR_AXIPMON_2_S_AXI4_BASEADDR 0x00000000
#define XPAR_AXIPMON_2_S_AXI4_HIGHADDR 0x00000000
#define XPAR_AXIPMON_2_ENABLE_32BIT_FILTER_ID 1

/* Canonical definitions for peripheral PSU_APM_5 */
#define XPAR_AXIPMON_3_DEVICE_ID XPAR_PSU_APM_5_DEVICE_ID
#define XPAR_AXIPMON_3_BASEADDR 0xFD490000
#define XPAR_AXIPMON_3_HIGHADDR 0xFD49FFFF
#define XPAR_AXIPMON_3_GLOBAL_COUNT_WIDTH 32
#define XPAR_AXIPMON_3_METRICS_SAMPLE_COUNT_WIDTH 32
#define XPAR_AXIPMON_3_ENABLE_EVENT_COUNT 1
#define XPAR_AXIPMON_3_NUM_MONITOR_SLOTS 1
#define XPAR_AXIPMON_3_NUM_OF_COUNTERS 3
#define XPAR_AXIPMON_3_HAVE_SAMPLED_METRIC_CNT 1
#define XPAR_AXIPMON_3_ENABLE_EVENT_LOG 0
#define XPAR_AXIPMON_3_FIFO_AXIS_DEPTH 32
#define XPAR_AXIPMON_3_FIFO_AXIS_TDATA_WIDTH 56
#define XPAR_AXIPMON_3_FIFO_AXIS_TID_WIDTH 1
#define XPAR_AXIPMON_3_METRIC_COUNT_SCALE 1
#define XPAR_AXIPMON_3_ENABLE_ADVANCED 1
#define XPAR_AXIPMON_3_ENABLE_PROFILE 0
#define XPAR_AXIPMON_3_ENABLE_TRACE 0
#define XPAR_AXIPMON_3_S_AXI4_BASEADDR 0x00000000
#define XPAR_AXIPMON_3_S_AXI4_HIGHADDR 0x00000000
#define XPAR_AXIPMON_3_ENABLE_32BIT_FILTER_ID 1


/******************************************************************/

/* Definitions for driver CSUDMA */
#define XPAR_XCSUDMA_NUM_INSTANCES 1

/* Definitions for peripheral PSU_CSUDMA */
#define XPAR_PSU_CSUDMA_DEVICE_ID 0
#define XPAR_PSU_CSUDMA_BASEADDR 0xFFC80000
#define XPAR_PSU_CSUDMA_HIGHADDR 0xFFC9FFFF
#define XPAR_PSU_CSUDMA_CSUDMA_CLK_FREQ_HZ 0


/******************************************************************/

/* Canonical definitions for peripheral PSU_CSUDMA */
#define XPAR_XCSUDMA_0_DEVICE_ID XPAR_PSU_CSUDMA_DEVICE_ID
#define XPAR_XCSUDMA_0_BASEADDR 0xFFC80000
#define XPAR_XCSUDMA_0_HIGHADDR 0xFFC9FFFF
#define XPAR_XCSUDMA_0_CSUDMA_CLK_FREQ_HZ 0


/******************************************************************/

/* Definitions for driver DDRCPSU */
#define XPAR_XDDRCPSU_NUM_INSTANCES 1

/* Definitions for peripheral PSU_DDRC_0 */
#define XPAR_PSU_DDRC_0_DEVICE_ID 0
#define XPAR_PSU_DDRC_0_BASEADDR 0xFD070000
#define XPAR_PSU_DDRC_0_HIGHADDR 0xFD070FFF
#define XPAR_PSU_DDRC_0_HAS_ECC 0
#define XPAR_PSU_DDRC_0_DDRC_CLK_FREQ_HZ 399996000


/******************************************************************/

/* Canonical definitions for peripheral PSU_DDRC_0 */
#define XPAR_DDRCPSU_0_DEVICE_ID XPAR_PSU_DDRC_0_DEVICE_ID
#define XPAR_DDRCPSU_0_BASEADDR 0xFD070000
#define XPAR_DDRCPSU_0_HIGHADDR 0xFD070FFF
#define XPAR_DDRCPSU_0_DDRC_CLK_FREQ_HZ 399996000


/******************************************************************/


/* Definitions for peripheral PSU_AFI_0 */
#define XPAR_PSU_AFI_0_S_AXI_BASEADDR 0xFD360000
#define XPAR_PSU_AFI_0_S_AXI_HIGHADDR 0xFD36FFFF


/* Definitions for peripheral PSU_AFI_1 */
#define XPAR_PSU_AFI_1_S_AXI_BASEADDR 0xFD370000
#define XPAR_PSU_AFI_1_S_AXI_HIGHADDR 0xFD37FFFF


/* Definitions for peripheral PSU_AFI_2 */
#define XPAR_PSU_AFI_2_S_AXI_BASEADDR 0xFD380000
#define XPAR_PSU_AFI_2_S_AXI_HIGHADDR 0xFD38FFFF


/* Definitions for peripheral PSU_AFI_3 */
#define XPAR_PSU_AFI_3_S_AXI_BASEADDR 0xFD390000
#define XPAR_PSU_AFI_3_S_AXI_HIGHADDR 0xFD39FFFF


/* Definitions for peripheral PSU_AFI_4 */
#define XPAR_PSU_AFI_4_S_AXI_BASEADDR 0xFD3A0000
#define XPAR_PSU_AFI_4_S_AXI_HIGHADDR 0xFD3AFFFF


/* Definitions for peripheral PSU_AFI_5 */
#define XPAR_PSU_AFI_5_S_AXI_BASEADDR 0xFD3B0000
#define XPAR_PSU_AFI_5_S_AXI_HIGHADDR 0xFD3BFFFF


/* Definitions for peripheral PSU_AFI_6 */
#define XPAR_PSU_AFI_6_S_AXI_BASEADDR 0xFF9B0000
#define XPAR_PSU_AFI_6_S_AXI_HIGHADDR 0xFF9BFFFF


/* Definitions for peripheral PSU_APU */
#define XPAR_PSU_APU_S_AXI_BASEADDR 0xFD5C0000
#define XPAR_PSU_APU_S_AXI_HIGHADDR 0xFD5CFFFF


/* Definitions for peripheral PSU_CCI_GPV */
#define XPAR_PSU_CCI_GPV_S_AXI_BASEADDR 0xFD6E0000
#define XPAR_PSU_CCI_GPV_S_AXI_HIGHADDR 0xFD6EFFFF


/* Definitions for peripheral PSU_CCI_REG */
#define XPAR_PSU_CCI_REG_S_AXI_BASEADDR 0xFD5E0000
#define XPAR_PSU_CCI_REG_S_AXI_HIGHADDR 0xFD5EFFFF


/* Definitions for peripheral PSU_CRF_APB */
#define XPAR_PSU_CRF_APB_S_AXI_BASEADDR 0xFD1A0000
#define XPAR_PSU_CRF_APB_S_AXI_HIGHADDR 0xFD2DFFFF


/* Definitions for peripheral PSU_CRL_APB */
#define XPAR_PSU_CRL_APB_S_AXI_BASEADDR 0xFF5E0000
#define XPAR_PSU_CRL_APB_S_AXI_HIGHADDR 0xFF85FFFF


/* Definitions for peripheral PSU_CTRL_IPI */
#define XPAR_PSU_CTRL_IPI_S_AXI_BASEADDR 0xFF380000
#define XPAR_PSU_CTRL_IPI_S_AXI_HIGHADDR 0xFF3FFFFF


/* Definitions for peripheral PSU_DDR_0 */
#define XPAR_PSU_DDR_0_S_AXI_BASEADDR 0x00000000
#define XPAR_PSU_DDR_0_S_AXI_HIGHADDR 0x7FFFFFFF


/* Definitions for peripheral PSU_DDR_PHY */
#define XPAR_PSU_DDR_PHY_S_AXI_BASEADDR 0xFD080000
#define XPAR_PSU_DDR_PHY_S_AXI_HIGHADDR 0xFD08FFFF


/* Definitions for peripheral PSU_DDR_QOS_CTRL */
#define XPAR_PSU_DDR_QOS_CTRL_S_AXI_BASEADDR 0xFD090000
#define XPAR_PSU_DDR_QOS_CTRL_S_AXI_HIGHADDR 0xFD09FFFF


/* Definitions for peripheral PSU_DDR_XMPU0_CFG */
#define XPAR_PSU_DDR_XMPU0_CFG_S_AXI_BASEADDR 0xFD000000
#define XPAR_PSU_DDR_XMPU0_CFG_S_AXI_HIGHADDR 0xFD00FFFF


/* Definitions for peripheral PSU_DDR_XMPU1_CFG */
#define XPAR_PSU_DDR_XMPU1_CFG_S_AXI_BASEADDR 0xFD010000
#define XPAR_PSU_DDR_XMPU1_CFG_S_AXI_HIGHADDR 0xFD01FFFF


/* Definitions for peripheral PSU_DDR_XMPU2_CFG */
#define XPAR_PSU_DDR_XMPU2_CFG_S_AXI_BASEADDR 0xFD020000
#define XPAR_PSU_DDR_XMPU2_CFG_S_AXI_HIGHADDR 0xFD02FFFF


/* Definitions for peripheral PSU_DDR_XMPU3_CFG */
#define XPAR_PSU_DDR_XMPU3_CFG_S_AXI_BASEADDR 0xFD030000
#define XPAR_PSU_DDR_XMPU3_CFG_S_AXI_HIGHADDR 0xFD03FFFF


/* Definitions for peripheral PSU_DDR_XMPU4_CFG */
#define XPAR_PSU_DDR_XMPU4_CFG_S_AXI_BASEADDR 0xFD040000
#define XPAR_PSU_DDR_XMPU4_CFG_S_AXI_HIGHADDR 0xFD04FFFF


/* Definitions for peripheral PSU_DDR_XMPU5_CFG */
#define XPAR_PSU_DDR_XMPU5_CFG_S_AXI_BASEADDR 0xFD050000
#define XPAR_PSU_DDR_XMPU5_CFG_S_AXI_HIGHADDR 0xFD05FFFF


/* Definitions for peripheral PSU_EFUSE */
#define XPAR_PSU_EFUSE_S_AXI_BASEADDR 0xFFCC0000
#define XPAR_PSU_EFUSE_S_AXI_HIGHADDR 0xFFCCFFFF


/* Definitions for peripheral PSU_FPD_GPV */
#define XPAR_PSU_FPD_GPV_S_AXI_BASEADDR 0xFD700000
#define XPAR_PSU_FPD_GPV_S_AXI_HIGHADDR 0xFD7FFFFF


/* Definitions for peripheral PSU_FPD_SLCR */
#define XPAR_PSU_FPD_SLCR_S_AXI_BASEADDR 0xFD610000
#define XPAR_PSU_FPD_SLCR_S_AXI_HIGHADDR 0xFD68FFFF


/* Definitions for peripheral PSU_FPD_SLCR_SECURE */
#define XPAR_PSU_FPD_SLCR_SECURE_S_AXI_BASEADDR 0xFD690000
#define XPAR_PSU_FPD_SLCR_SECURE_S_AXI_HIGHADDR 0xFD6CFFFF


/* Definitions for peripheral PSU_FPD_XMPU_CFG */
#define XPAR_PSU_FPD_XMPU_CFG_S_AXI_BASEADDR 0xFD5D0000
#define XPAR_PSU_FPD_XMPU_CFG_S_AXI_HIGHADDR 0xFD5DFFFF


/* Definitions for peripheral PSU_FPD_XMPU_SINK */
#define XPAR_PSU_FPD_XMPU_SINK_S_AXI_BASEADDR 0xFD4F0000
#define XPAR_PSU_FPD_XMPU_SINK_S_AXI_HIGHADDR 0xFD4FFFFF


/* Definitions for peripheral PSU_GPU */
#define XPAR_PSU_GPU_S_AXI_BASEADDR 0xFD4B0000
#define XPAR_PSU_GPU_S_AXI_HIGHADDR 0xFD4BFFFF


/* Definitions for peripheral PSU_IOU_SCNTR */
#define XPAR_PSU_IOU_SCNTR_S_AXI_BASEADDR 0xFF250000
#define XPAR_PSU_IOU_SCNTR_S_AXI_HIGHADDR 0xFF25FFFF


/* Definitions for peripheral PSU_IOU_SCNTRS */
#define XPAR_PSU_IOU_SCNTRS_S_AXI_BASEADDR 0xFF260000
#define XPAR_PSU_IOU_SCNTRS_S_AXI_HIGHADDR 0xFF26FFFF


/* Definitions for peripheral PSU_IOUSECURE_SLCR */
#define XPAR_PSU_IOUSECURE_SLCR_S_AXI_BASEADDR 0xFF240000
#define XPAR_PSU_IOUSECURE_SLCR_S_AXI_HIGHADDR 0xFF24FFFF


/* Definitions for peripheral PSU_IOUSLCR_0 */
#define XPAR_PSU_IOUSLCR_0_S_AXI_BASEADDR 0xFF180000
#define XPAR_PSU_IOUSLCR_0_S_AXI_HIGHADDR 0xFF23FFFF


/* Definitions for peripheral PSU_LPD_SLCR */
#define XPAR_PSU_LPD_SLCR_S_AXI_BASEADDR 0xFF410000
#define XPAR_PSU_LPD_SLCR_S_AXI_HIGHADDR 0xFF4AFFFF


/* Definitions for peripheral PSU_LPD_SLCR_SECURE */
#define XPAR_PSU_LPD_SLCR_SECURE_S_AXI_BASEADDR 0xFF4B0000
#define XPAR_PSU_LPD_SLCR_SECURE_S_AXI_HIGHADDR 0xFF4DFFFF


/* Definitions for peripheral PSU_LPD_XPPU */
#define XPAR_PSU_LPD_XPPU_S_AXI_BASEADDR 0xFF980000
#define XPAR_PSU_LPD_XPPU_S_AXI_HIGHADDR 0xFF99FFFF


/* Definitions for peripheral PSU_LPD_XPPU_SINK */
#define XPAR_PSU_LPD_XPPU_SINK_S_AXI_BASEADDR 0xFF9C0000
#define XPAR_PSU_LPD_XPPU_SINK_S_AXI_HIGHADDR 0xFF9CFFFF


/* Definitions for peripheral PSU_MBISTJTAG */
#define XPAR_PSU_MBISTJTAG_S_AXI_BASEADDR 0xFFCF0000
#define XPAR_PSU_MBISTJTAG_S_AXI_HIGHADDR 0xFFCFFFFF


/* Definitions for peripheral PSU_MESSAGE_BUFFERS */
#define XPAR_PSU_MESSAGE_BUFFERS_S_AXI_BASEADDR 0xFF990000
#define XPAR_PSU_MESSAGE_BUFFERS_S_AXI_HIGHADDR 0xFF99FFFF


/* Definitions for peripheral PSU_OCM */
#define XPAR_PSU_OCM_S_AXI_BASEADDR 0xFF960000
#define XPAR_PSU_OCM_S_AXI_HIGHADDR 0xFF96FFFF


/* Definitions for peripheral PSU_OCM_RAM_0 */
#define XPAR_PSU_OCM_RAM_0_S_AXI_BASEADDR 0xFFFC0000
#define XPAR_PSU_OCM_RAM_0_S_AXI_HIGHADDR 0xFFFFFFFF


/* Definitions for peripheral PSU_OCM_XMPU_CFG */
#define XPAR_PSU_OCM_XMPU_CFG_S_AXI_BASEADDR 0xFFA70000
#define XPAR_PSU_OCM_XMPU_CFG_S_AXI_HIGHADDR 0xFFA7FFFF


/* Definitions for peripheral PSU_PMU_GLOBAL_0 */
#define XPAR_PSU_PMU_GLOBAL_0_S_AXI_BASEADDR 0xFFD80000
#define XPAR_PSU_PMU_GLOBAL_0_S_AXI_HIGHADDR 0xFFDBFFFF


/* Definitions for peripheral PSU_R5_0_ATCM_GLOBAL */
#define XPAR_PSU_R5_0_ATCM_GLOBAL_S_AXI_BASEADDR 0xFFE00000
#define XPAR_PSU_R5_0_ATCM_GLOBAL_S_AXI_HIGHADDR 0xFFE0FFFF


/* Definitions for peripheral PSU_R5_0_BTCM_GLOBAL */
#define XPAR_PSU_R5_0_BTCM_GLOBAL_S_AXI_BASEADDR 0xFFE20000
#define XPAR_PSU_R5_0_BTCM_GLOBAL_S_AXI_HIGHADDR 0xFFE2FFFF


/* Definitions for peripheral PSU_R5_1_ATCM_GLOBAL */
#define XPAR_PSU_R5_1_ATCM_GLOBAL_S_AXI_BASEADDR 0xFFE90000
#define XPAR_PSU_R5_1_ATCM_GLOBAL_S_AXI_HIGHADDR 0xFFE9FFFF


/* Definitions for peripheral PSU_R5_1_BTCM_GLOBAL */
#define XPAR_PSU_R5_1_BTCM_GLOBAL_S_AXI_BASEADDR 0xFFEB0000
#define XPAR_PSU_R5_1_BTCM_GLOBAL_S_AXI_HIGHADDR 0xFFEBFFFF


/* Definitions for peripheral PSU_R5_TCM_RAM_GLOBAL */
#define XPAR_PSU_R5_TCM_RAM_GLOBAL_S_AXI_BASEADDR 0xFFE00000
#define XPAR_PSU_R5_TCM_RAM_GLOBAL_S_AXI_HIGHADDR 0xFFE3FFFF


/* Definitions for peripheral PSU_RPU */
#define XPAR_PSU_RPU_S_AXI_BASEADDR 0xFF9A0000
#define XPAR_PSU_RPU_S_AXI_HIGHADDR 0xFF9AFFFF


/* Definitions for peripheral PSU_RSA */
#define XPAR_PSU_RSA_S_AXI_BASEADDR 0xFFCE0000
#define XPAR_PSU_RSA_S_AXI_HIGHADDR 0xFFCEFFFF


/* Definitions for peripheral PSU_SERDES */
#define XPAR_PSU_SERDES_S_AXI_BASEADDR 0xFD400000
#define XPAR_PSU_SERDES_S_AXI_HIGHADDR 0xFD47FFFF


/* Definitions for peripheral PSU_SIOU */
#define XPAR_PSU_SIOU_S_AXI_BASEADDR 0xFD3D0000
#define XPAR_PSU_SIOU_S_AXI_HIGHADDR 0xFD3DFFFF


/* Definitions for peripheral PSU_SMMU_GPV */
#define XPAR_PSU_SMMU_GPV_S_AXI_BASEADDR 0xFD800000
#define XPAR_PSU_SMMU_GPV_S_AXI_HIGHADDR 0xFDFFFFFF


/* Definitions for peripheral PSU_SMMU_REG */
#define XPAR_PSU_SMMU_REG_S_AXI_BASEADDR 0xFD5F0000
#define XPAR_PSU_SMMU_REG_S_AXI_HIGHADDR 0xFD5FFFFF


/* Definitions for peripheral XXV_ETHERNET_0 */
#define XPAR_XXV_ETHERNET_0_BASEADDR 0x80000000
#define XPAR_XXV_ETHERNET_0_HIGHADDR 0x8000FFFF


/******************************************************************/

/* Definitions for driver GPIOPS */
#define XPAR_XGPIOPS_NUM_INSTANCES 1

/* Definitions for peripheral PSU_GPIO_0 */
#define XPAR_PSU_GPIO_0_DEVICE_ID 0
#define XPAR_PSU_GPIO_0_BASEADDR 0xFF0A0000
#define XPAR_PSU_GPIO_0_HIGHADDR 0xFF0AFFFF


/******************************************************************/

/* Canonical definitions for peripheral PSU_GPIO_0 */
#define XPAR_XGPIOPS_0_DEVICE_ID XPAR_PSU_GPIO_0_DEVICE_ID
#define XPAR_XGPIOPS_0_BASEADDR 0xFF0A0000
#define XPAR_XGPIOPS_0_HIGHADDR 0xFF0AFFFF


/******************************************************************/

#define  XPAR_XIPIPSU_NUM_INSTANCES  1

/* Parameter definitions for peripheral psu_ipi_0 */
#define  XPAR_PSU_IPI_0_DEVICE_ID  0
#define  XPAR_PSU_IPI_0_BASE_ADDRESS  0xFF300000
#define  XPAR_PSU_IPI_0_BIT_MASK  0x00000001
#define  XPAR_PSU_IPI_0_BUFFER_INDEX  2
#define  XPAR_PSU_IPI_0_INT_ID  67

/* Canonical definitions for peripheral psu_ipi_0 */
#define  XPAR_XIPIPSU_0_DEVICE_ID	XPAR_PSU_IPI_0_DEVICE_ID
#define  XPAR_XIPIPSU_0_BASE_ADDRESS	XPAR_PSU_IPI_0_BASE_ADDRESS
#define  XPAR_XIPIPSU_0_BIT_MASK	XPAR_PSU_IPI_0_BIT_MASK
#define  XPAR_XIPIPSU_0_BUFFER_INDEX	XPAR_PSU_IPI_0_BUFFER_INDEX
#define  XPAR_XIPIPSU_0_INT_ID	XPAR_PSU_IPI_0_INT_ID

#define  XPAR_XIPIPSU_NUM_TARGETS  7

#define  XPAR_PSU_IPI_0_BIT_MASK  0x00000001
#define  XPAR_PSU_IPI_0_BUFFER_INDEX  2
#define  XPAR_PSU_IPI_1_BIT_MASK  0x00000100
#define  XPAR_PSU_IPI_1_BUFFER_INDEX  0
#define  XPAR_PSU_IPI_2_BIT_MASK  0x00000200
#define  XPAR_PSU_IPI_2_BUFFER_INDEX  1
#define  XPAR_PSU_IPI_3_BIT_MASK  0x00010000
#define  XPAR_PSU_IPI_3_BUFFER_INDEX  7
#define  XPAR_PSU_IPI_4_BIT_MASK  0x00020000
#define  XPAR_PSU_IPI_4_BUFFER_INDEX  7
#define  XPAR_PSU_IPI_5_BIT_MASK  0x00040000
#define  XPAR_PSU_IPI_5_BUFFER_INDEX  7
#define  XPAR_PSU_IPI_6_BIT_MASK  0x00080000
#define  XPAR_PSU_IPI_6_BUFFER_INDEX  7
/* Target List for referring to processor IPI Targets */

#define  XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK  XPAR_PSU_IPI_0_BIT_MASK
#define  XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_INDEX  0

#define  XPAR_XIPIPS_TARGET_PSU_CORTEXA53_1_CH0_MASK  XPAR_PSU_IPI_0_BIT_MASK
#define  XPAR_XIPIPS_TARGET_PSU_CORTEXA53_1_CH0_INDEX  0

#define  XPAR_XIPIPS_TARGET_PSU_CORTEXA53_2_CH0_MASK  XPAR_PSU_IPI_0_BIT_MASK
#define  XPAR_XIPIPS_TARGET_PSU_CORTEXA53_2_CH0_INDEX  0

#define  XPAR_XIPIPS_TARGET_PSU_CORTEXA53_3_CH0_MASK  XPAR_PSU_IPI_0_BIT_MASK
#define  XPAR_XIPIPS_TARGET_PSU_CORTEXA53_3_CH0_INDEX  0

#define  XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK  XPAR_PSU_IPI_1_BIT_MASK
#define  XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_INDEX  1

#define  XPAR_XIPIPS_TARGET_PSU_CORTEXR5_1_CH0_MASK  XPAR_PSU_IPI_2_BIT_MASK
#define  XPAR_XIPIPS_TARGET_PSU_CORTEXR5_1_CH0_INDEX  2

#define  XPAR_XIPIPS_TARGET_PSU_PMU_0_CH0_MASK  XPAR_PSU_IPI_3_BIT_MASK
#define  XPAR_XIPIPS_TARGET_PSU_PMU_0_CH0_INDEX  3
#define  XPAR_XIPIPS_TARGET_PSU_PMU_0_CH1_MASK  XPAR_PSU_IPI_4_BIT_MASK
#define  XPAR_XIPIPS_TARGET_PSU_PMU_0_CH1_INDEX  4
#define  XPAR_XIPIPS_TARGET_PSU_PMU_0_CH2_MASK  XPAR_PSU_IPI_5_BIT_MASK
#define  XPAR_XIPIPS_TARGET_PSU_PMU_0_CH2_INDEX  5
#define  XPAR_XIPIPS_TARGET_PSU_PMU_0_CH3_MASK  XPAR_PSU_IPI_6_BIT_MASK
#define  XPAR_XIPIPS_TARGET_PSU_PMU_0_CH3_INDEX  6

/* Definitions for driver RTCPSU */
#define XPAR_XRTCPSU_NUM_INSTANCES 1

/* Definitions for peripheral PSU_RTC */
#define XPAR_PSU_RTC_DEVICE_ID 0
#define XPAR_PSU_RTC_BASEADDR 0xFFA60000
#define XPAR_PSU_RTC_HIGHADDR 0xFFA6FFFF


/******************************************************************/

/* Canonical definitions for peripheral PSU_RTC */
#define XPAR_XRTCPSU_0_DEVICE_ID XPAR_PSU_RTC_DEVICE_ID
#define XPAR_XRTCPSU_0_BASEADDR 0xFFA60000
#define XPAR_XRTCPSU_0_HIGHADDR 0xFFA6FFFF


/******************************************************************/

/* Definitions for driver SCUGIC */
#define XPAR_XSCUGIC_NUM_INSTANCES 1

/* Definitions for peripheral PSU_ACPU_GIC */
#define XPAR_PSU_ACPU_GIC_DEVICE_ID 0
#define XPAR_PSU_ACPU_GIC_BASEADDR 0xF9020000
#define XPAR_PSU_ACPU_GIC_HIGHADDR 0xF9020FFF
#define XPAR_PSU_ACPU_GIC_DIST_BASEADDR 0xF9010000


/******************************************************************/

/* Canonical definitions for peripheral PSU_ACPU_GIC */
#define XPAR_SCUGIC_0_DEVICE_ID 0
#define XPAR_SCUGIC_0_CPU_BASEADDR 0xF9020000
#define XPAR_SCUGIC_0_CPU_HIGHADDR 0xF9020FFF
#define XPAR_SCUGIC_0_DIST_BASEADDR 0xF9010000


/******************************************************************/

/* Definitions for driver SYSMONPSU */
#define XPAR_XSYSMONPSU_NUM_INSTANCES 1

/* Definitions for peripheral PSU_AMS */
#define XPAR_PSU_AMS_DEVICE_ID 0
#define XPAR_PSU_AMS_BASEADDR 0xFFA50000
#define XPAR_PSU_AMS_HIGHADDR 0xFFA5FFFF


/******************************************************************/

/* Canonical definitions for peripheral PSU_AMS */
#define XPAR_XSYSMONPSU_0_DEVICE_ID XPAR_PSU_AMS_DEVICE_ID
#define XPAR_XSYSMONPSU_0_BASEADDR 0xFFA50000
#define XPAR_XSYSMONPSU_0_HIGHADDR 0xFFA5FFFF


/******************************************************************/

/* Definitions for driver ZDMA */
#define XPAR_XZDMA_NUM_INSTANCES 16

/* Definitions for peripheral PSU_ADMA_0 */
#define XPAR_PSU_ADMA_0_DEVICE_ID 0
#define XPAR_PSU_ADMA_0_BASEADDR 0xFFA80000
#define XPAR_PSU_ADMA_0_DMA_MODE 1
#define XPAR_PSU_ADMA_0_HIGHADDR 0xFFA8FFFF
#define XPAR_PSU_ADMA_0_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_ADMA_1 */
#define XPAR_PSU_ADMA_1_DEVICE_ID 1
#define XPAR_PSU_ADMA_1_BASEADDR 0xFFA90000
#define XPAR_PSU_ADMA_1_DMA_MODE 1
#define XPAR_PSU_ADMA_1_HIGHADDR 0xFFA9FFFF
#define XPAR_PSU_ADMA_1_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_ADMA_2 */
#define XPAR_PSU_ADMA_2_DEVICE_ID 2
#define XPAR_PSU_ADMA_2_BASEADDR 0xFFAA0000
#define XPAR_PSU_ADMA_2_DMA_MODE 1
#define XPAR_PSU_ADMA_2_HIGHADDR 0xFFAAFFFF
#define XPAR_PSU_ADMA_2_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_ADMA_3 */
#define XPAR_PSU_ADMA_3_DEVICE_ID 3
#define XPAR_PSU_ADMA_3_BASEADDR 0xFFAB0000
#define XPAR_PSU_ADMA_3_DMA_MODE 1
#define XPAR_PSU_ADMA_3_HIGHADDR 0xFFABFFFF
#define XPAR_PSU_ADMA_3_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_ADMA_4 */
#define XPAR_PSU_ADMA_4_DEVICE_ID 4
#define XPAR_PSU_ADMA_4_BASEADDR 0xFFAC0000
#define XPAR_PSU_ADMA_4_DMA_MODE 1
#define XPAR_PSU_ADMA_4_HIGHADDR 0xFFACFFFF
#define XPAR_PSU_ADMA_4_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_ADMA_5 */
#define XPAR_PSU_ADMA_5_DEVICE_ID 5
#define XPAR_PSU_ADMA_5_BASEADDR 0xFFAD0000
#define XPAR_PSU_ADMA_5_DMA_MODE 1
#define XPAR_PSU_ADMA_5_HIGHADDR 0xFFADFFFF
#define XPAR_PSU_ADMA_5_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_ADMA_6 */
#define XPAR_PSU_ADMA_6_DEVICE_ID 6
#define XPAR_PSU_ADMA_6_BASEADDR 0xFFAE0000
#define XPAR_PSU_ADMA_6_DMA_MODE 1
#define XPAR_PSU_ADMA_6_HIGHADDR 0xFFAEFFFF
#define XPAR_PSU_ADMA_6_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_ADMA_7 */
#define XPAR_PSU_ADMA_7_DEVICE_ID 7
#define XPAR_PSU_ADMA_7_BASEADDR 0xFFAF0000
#define XPAR_PSU_ADMA_7_DMA_MODE 1
#define XPAR_PSU_ADMA_7_HIGHADDR 0xFFAFFFFF
#define XPAR_PSU_ADMA_7_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_GDMA_0 */
#define XPAR_PSU_GDMA_0_DEVICE_ID 8
#define XPAR_PSU_GDMA_0_BASEADDR 0xFD500000
#define XPAR_PSU_GDMA_0_DMA_MODE 0
#define XPAR_PSU_GDMA_0_HIGHADDR 0xFD50FFFF
#define XPAR_PSU_GDMA_0_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_GDMA_1 */
#define XPAR_PSU_GDMA_1_DEVICE_ID 9
#define XPAR_PSU_GDMA_1_BASEADDR 0xFD510000
#define XPAR_PSU_GDMA_1_DMA_MODE 0
#define XPAR_PSU_GDMA_1_HIGHADDR 0xFD51FFFF
#define XPAR_PSU_GDMA_1_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_GDMA_2 */
#define XPAR_PSU_GDMA_2_DEVICE_ID 10
#define XPAR_PSU_GDMA_2_BASEADDR 0xFD520000
#define XPAR_PSU_GDMA_2_DMA_MODE 0
#define XPAR_PSU_GDMA_2_HIGHADDR 0xFD52FFFF
#define XPAR_PSU_GDMA_2_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_GDMA_3 */
#define XPAR_PSU_GDMA_3_DEVICE_ID 11
#define XPAR_PSU_GDMA_3_BASEADDR 0xFD530000
#define XPAR_PSU_GDMA_3_DMA_MODE 0
#define XPAR_PSU_GDMA_3_HIGHADDR 0xFD53FFFF
#define XPAR_PSU_GDMA_3_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_GDMA_4 */
#define XPAR_PSU_GDMA_4_DEVICE_ID 12
#define XPAR_PSU_GDMA_4_BASEADDR 0xFD540000
#define XPAR_PSU_GDMA_4_DMA_MODE 0
#define XPAR_PSU_GDMA_4_HIGHADDR 0xFD54FFFF
#define XPAR_PSU_GDMA_4_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_GDMA_5 */
#define XPAR_PSU_GDMA_5_DEVICE_ID 13
#define XPAR_PSU_GDMA_5_BASEADDR 0xFD550000
#define XPAR_PSU_GDMA_5_DMA_MODE 0
#define XPAR_PSU_GDMA_5_HIGHADDR 0xFD55FFFF
#define XPAR_PSU_GDMA_5_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_GDMA_6 */
#define XPAR_PSU_GDMA_6_DEVICE_ID 14
#define XPAR_PSU_GDMA_6_BASEADDR 0xFD560000
#define XPAR_PSU_GDMA_6_DMA_MODE 0
#define XPAR_PSU_GDMA_6_HIGHADDR 0xFD56FFFF
#define XPAR_PSU_GDMA_6_ZDMA_CLK_FREQ_HZ 0


/* Definitions for peripheral PSU_GDMA_7 */
#define XPAR_PSU_GDMA_7_DEVICE_ID 15
#define XPAR_PSU_GDMA_7_BASEADDR 0xFD570000
#define XPAR_PSU_GDMA_7_DMA_MODE 0
#define XPAR_PSU_GDMA_7_HIGHADDR 0xFD57FFFF
#define XPAR_PSU_GDMA_7_ZDMA_CLK_FREQ_HZ 0


/******************************************************************/

/* Canonical definitions for peripheral PSU_ADMA_0 */
#define XPAR_XZDMA_0_DEVICE_ID XPAR_PSU_ADMA_0_DEVICE_ID
#define XPAR_XZDMA_0_BASEADDR 0xFFA80000
#define XPAR_XZDMA_0_DMA_MODE 1
#define XPAR_XZDMA_0_HIGHADDR 0xFFA8FFFF
#define XPAR_XZDMA_0_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_ADMA_1 */
#define XPAR_XZDMA_1_DEVICE_ID XPAR_PSU_ADMA_1_DEVICE_ID
#define XPAR_XZDMA_1_BASEADDR 0xFFA90000
#define XPAR_XZDMA_1_DMA_MODE 1
#define XPAR_XZDMA_1_HIGHADDR 0xFFA9FFFF
#define XPAR_XZDMA_1_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_ADMA_2 */
#define XPAR_XZDMA_2_DEVICE_ID XPAR_PSU_ADMA_2_DEVICE_ID
#define XPAR_XZDMA_2_BASEADDR 0xFFAA0000
#define XPAR_XZDMA_2_DMA_MODE 1
#define XPAR_XZDMA_2_HIGHADDR 0xFFAAFFFF
#define XPAR_XZDMA_2_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_ADMA_3 */
#define XPAR_XZDMA_3_DEVICE_ID XPAR_PSU_ADMA_3_DEVICE_ID
#define XPAR_XZDMA_3_BASEADDR 0xFFAB0000
#define XPAR_XZDMA_3_DMA_MODE 1
#define XPAR_XZDMA_3_HIGHADDR 0xFFABFFFF
#define XPAR_XZDMA_3_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_ADMA_4 */
#define XPAR_XZDMA_4_DEVICE_ID XPAR_PSU_ADMA_4_DEVICE_ID
#define XPAR_XZDMA_4_BASEADDR 0xFFAC0000
#define XPAR_XZDMA_4_DMA_MODE 1
#define XPAR_XZDMA_4_HIGHADDR 0xFFACFFFF
#define XPAR_XZDMA_4_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_ADMA_5 */
#define XPAR_XZDMA_5_DEVICE_ID XPAR_PSU_ADMA_5_DEVICE_ID
#define XPAR_XZDMA_5_BASEADDR 0xFFAD0000
#define XPAR_XZDMA_5_DMA_MODE 1
#define XPAR_XZDMA_5_HIGHADDR 0xFFADFFFF
#define XPAR_XZDMA_5_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_ADMA_6 */
#define XPAR_XZDMA_6_DEVICE_ID XPAR_PSU_ADMA_6_DEVICE_ID
#define XPAR_XZDMA_6_BASEADDR 0xFFAE0000
#define XPAR_XZDMA_6_DMA_MODE 1
#define XPAR_XZDMA_6_HIGHADDR 0xFFAEFFFF
#define XPAR_XZDMA_6_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_ADMA_7 */
#define XPAR_XZDMA_7_DEVICE_ID XPAR_PSU_ADMA_7_DEVICE_ID
#define XPAR_XZDMA_7_BASEADDR 0xFFAF0000
#define XPAR_XZDMA_7_DMA_MODE 1
#define XPAR_XZDMA_7_HIGHADDR 0xFFAFFFFF
#define XPAR_XZDMA_7_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_GDMA_0 */
#define XPAR_XZDMA_8_DEVICE_ID XPAR_PSU_GDMA_0_DEVICE_ID
#define XPAR_XZDMA_8_BASEADDR 0xFD500000
#define XPAR_XZDMA_8_DMA_MODE 0
#define XPAR_XZDMA_8_HIGHADDR 0xFD50FFFF
#define XPAR_XZDMA_8_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_GDMA_1 */
#define XPAR_XZDMA_9_DEVICE_ID XPAR_PSU_GDMA_1_DEVICE_ID
#define XPAR_XZDMA_9_BASEADDR 0xFD510000
#define XPAR_XZDMA_9_DMA_MODE 0
#define XPAR_XZDMA_9_HIGHADDR 0xFD51FFFF
#define XPAR_XZDMA_9_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_GDMA_2 */
#define XPAR_XZDMA_10_DEVICE_ID XPAR_PSU_GDMA_2_DEVICE_ID
#define XPAR_XZDMA_10_BASEADDR 0xFD520000
#define XPAR_XZDMA_10_DMA_MODE 0
#define XPAR_XZDMA_10_HIGHADDR 0xFD52FFFF
#define XPAR_XZDMA_10_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_GDMA_3 */
#define XPAR_XZDMA_11_DEVICE_ID XPAR_PSU_GDMA_3_DEVICE_ID
#define XPAR_XZDMA_11_BASEADDR 0xFD530000
#define XPAR_XZDMA_11_DMA_MODE 0
#define XPAR_XZDMA_11_HIGHADDR 0xFD53FFFF
#define XPAR_XZDMA_11_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_GDMA_4 */
#define XPAR_XZDMA_12_DEVICE_ID XPAR_PSU_GDMA_4_DEVICE_ID
#define XPAR_XZDMA_12_BASEADDR 0xFD540000
#define XPAR_XZDMA_12_DMA_MODE 0
#define XPAR_XZDMA_12_HIGHADDR 0xFD54FFFF
#define XPAR_XZDMA_12_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_GDMA_5 */
#define XPAR_XZDMA_13_DEVICE_ID XPAR_PSU_GDMA_5_DEVICE_ID
#define XPAR_XZDMA_13_BASEADDR 0xFD550000
#define XPAR_XZDMA_13_DMA_MODE 0
#define XPAR_XZDMA_13_HIGHADDR 0xFD55FFFF
#define XPAR_XZDMA_13_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_GDMA_6 */
#define XPAR_XZDMA_14_DEVICE_ID XPAR_PSU_GDMA_6_DEVICE_ID
#define XPAR_XZDMA_14_BASEADDR 0xFD560000
#define XPAR_XZDMA_14_DMA_MODE 0
#define XPAR_XZDMA_14_HIGHADDR 0xFD56FFFF
#define XPAR_XZDMA_14_ZDMA_CLK_FREQ_HZ 0

/* Canonical definitions for peripheral PSU_GDMA_7 */
#define XPAR_XZDMA_15_DEVICE_ID XPAR_PSU_GDMA_7_DEVICE_ID
#define XPAR_XZDMA_15_BASEADDR 0xFD570000
#define XPAR_XZDMA_15_DMA_MODE 0
#define XPAR_XZDMA_15_HIGHADDR 0xFD57FFFF
#define XPAR_XZDMA_15_ZDMA_CLK_FREQ_HZ 0


/******************************************************************/

#endif  /* end of protection macro */
