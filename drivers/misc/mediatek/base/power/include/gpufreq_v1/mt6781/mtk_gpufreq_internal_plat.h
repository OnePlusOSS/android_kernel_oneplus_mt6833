/*
 * Copyright (C) 2020 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */

#ifndef ___MT_GPUFREQ_INTERNAL_PLAT_H___
#define ___MT_GPUFREQ_INTERNAL_PLAT_H___

/**************************************************
 *  0:     all on when mtk probe init (freq/ Vgpu/ Vsram_gpu)
 *         disable DDK power on/off callback
 **************************************************/
//MT6781_TODO disable bringup  enable POWER CTL & DVFS
#define MT_GPUFREQ_POWER_CTL_ENABLE	1

/**************************************************
 * (DVFS_ENABLE, CUST_CONFIG)
 * (1, 1) -> DVFS enable and init to CUST_INIT_OPP
 * (1, 0) -> DVFS enable
 * (0, 1) -> DVFS disable but init to CUST_INIT_OPP (do DVFS only onces)
 * (0, 0) -> DVFS disable
 **************************************************/
//MT6781_TODO disable bringup  enable POWER CTL & DVFS
#define MT_GPUFREQ_DVFS_ENABLE          1
#define MT_GPUFREQ_CUST_CONFIG          0
#define MT_GPUFREQ_CUST_INIT_OPP        (g_opp_table_segment_1[16].gpufreq_khz)

/**************************************************
 * DVFS Setting
 **************************************************/
#define NUM_OF_OPP_IDX (sizeof(g_opp_table_segment_1) / \
			sizeof(g_opp_table_segment_1[0]))

/* On opp table, low vgpu will use the same vsram.
 * And hgih vgpu will have the same diff with vsram.
 *
 * if (vgpu <= FIXED_VSRAM_VOLT_THSRESHOLD) {
 *     vsram = FIXED_VSRAM_VOLT;
 * } else {
 *     vsram = vgpu + FIXED_VSRAM_VOLT_DIFF;
 * }
 */
#define FIXED_VSRAM_VOLT                (85000)
#define FIXED_VSRAM_VOLT_THSRESHOLD     (75000)
#define FIXED_VSRAM_VOLT_DIFF           (10000)

/**************************************************
 * MT6366 PMIC Setting
 **************************************************/
/* PMIC hardware range:
 * vgpu      0.55 ~ 1.1V
 * vsram_gpu 0.6 ~ 1.2V
 */
#define VGPU_MAX_VOLT                   (110000)        /* mV x 100 */
#define VGPU_MIN_VOLT                   (55000)         /* mV x 100 */
#define VSRAM_GPU_MAX_VOLT              (120000)        /* mV x 100 */
#define VSRAM_GPU_MIN_VOLT              (60000)         /* mV x 100 */
#define PMIC_STEP                       (625)           /* mV x 100 */
/*
 * (100)mv <= (VSRAM - VGPU) <= (250)mV
 */
#define BUCK_DIFF_MAX                   (25000)         /* mV x 100 */
#define BUCK_DIFF_MIN                   (10000)             /* mV x 100 */

/**************************************************
 * Clock Setting
 **************************************************/
#define POSDIV_2_MAX_FREQ               (1900000)       /* KHz */
#define POSDIV_2_MIN_FREQ               (750000)        /* KHz */
#define POSDIV_4_MAX_FREQ               (950000)        /* KHz */
#define POSDIV_4_MIN_FREQ               (375000)        /* KHz */
#define POSDIV_8_MAX_FREQ               (475000)        /* KHz */
#define POSDIV_8_MIN_FREQ               (187500)        /* KHz */
#define POSDIV_16_MAX_FREQ              (237500)        /* KHz */
#define POSDIV_16_MIN_FREQ              (125000)        /* KHz */
#define POSDIV_SHIFT                    (24)            /* bit */
#define DDS_SHIFT                       (14)            /* bit */
#define TO_MHZ_HEAD                     (100)
#define TO_MHZ_TAIL                     (10)
#define ROUNDING_VALUE                  (5)
#define MFGPLL_FIN                      (26)            /* MHz */
#define MFGPLL_FH_PLL                   FH_PLL4
#define MFGPLL_CON0                     (g_apmixed_base + 0x250)
#define MFGPLL_CON1                     (g_apmixed_base + 0x254)
#define MFGPLL_PWR_CON0                 (g_apmixed_base + 0x25C)

/**************************************************
 * Reference Power Setting
 **************************************************/
#define GPU_ACT_REF_POWER               (1307)                /* mW  */
#define GPU_ACT_REF_FREQ                (950000)              /* KHz */
#define GPU_ACT_REF_VOLT                (90000)               /* mV x 100 */
#define PTPOD_DISABLE_VOLT              (75000)

// MT6781_PORTING_TODO check below power settings @{
/**************************************************
 * Battery Over Current Protect
 **************************************************/
#define MT_GPUFREQ_BATT_OC_PROTECT              1
#define MT_GPUFREQ_BATT_OC_LIMIT_FREQ           (485000)        /* KHz */

/**************************************************
 * Battery Percentage Protect
 **************************************************/
#define MT_GPUFREQ_BATT_PERCENT_PROTECT         0
#define MT_GPUFREQ_BATT_PERCENT_LIMIT_FREQ      (485000)        /* KHz */

/**************************************************
 * Low Battery Volume Protect
 **************************************************/
#define MT_GPUFREQ_LOW_BATT_VOLT_PROTECT        1
#define MT_GPUFREQ_LOW_BATT_VOLT_LIMIT_FREQ     (485000)        /* KHz */

//@}

/**************************************************
 * DFD Dump
 **************************************************/
// MT6781_TODO check dfd
#define MT_GPUFREQ_DFD_ENABLE 1
#define MT_GPUFREQ_DFD_DEBUG 0

/**************************************************
 * GPM (GIMP: GPU Idle To Max Protector)
 **************************************************/
#define MT_GPUFREQ_GPM_ENABLE 0

/**************************************************
 * PTPOD Calibration
 **************************************************/
#define MT_GPUFREQ_PTPOD_CALIBRATION_ENABLE 0

#define FM_HF_FMFG_CK 3
#define FM_AD_MFGPLL_CK 26

/**************************************************
 * Register Manipulations
 **************************************************/
#define READ_REGISTER_UINT32(reg)	\
	(*(unsigned int * const)(reg))
#define WRITE_REGISTER_UINT32(reg, val)	\
	((*(unsigned int * const)(reg)) = (val))
#define INREG32(x)	\
	READ_REGISTER_UINT32((unsigned int *)((void *)(x)))
#define OUTREG32(x, y)	\
	WRITE_REGISTER_UINT32((unsigned int *)((void *)(x)), (unsigned int)(y))
#define SETREG32(x, y)	\
	OUTREG32(x, INREG32(x)|(y))
#define CLRREG32(x, y)	\
	OUTREG32(x, INREG32(x)&~(y))
#define MASKREG32(x, y, z)	\
	OUTREG32(x, (INREG32(x)&~(y))|(z))
#define DRV_Reg32(addr)				INREG32(addr)
#define DRV_WriteReg32(addr, data)	OUTREG32(addr, data)
#define DRV_SetReg32(addr, data)	SETREG32(addr, data)
#define DRV_ClrReg32(addr, data)	CLRREG32(addr, data)

/**************************************************
 * Proc Node Definition
 **************************************************/
#ifdef CONFIG_PROC_FS
#define PROC_FOPS_RW(name)	\
	static int mt_ ## name ## _proc_open(	\
			struct inode *inode,	\
			struct file *file)	\
	{	\
		return single_open(	\
				file,	\
				mt_ ## name ## _proc_show,	\
				PDE_DATA(inode));	\
	}	\
	static const struct file_operations mt_ ## name ## _proc_fops =	\
	{	\
		.owner = THIS_MODULE,	\
		.open = mt_ ## name ## _proc_open,	\
		.read = seq_read,	\
		.llseek = seq_lseek,	\
		.release = single_release,	\
		.write = mt_ ## name ## _proc_write,	\
	}
#define PROC_FOPS_RO(name)	\
	static int mt_ ## name ## _proc_open(	\
			struct inode *inode,	\
			struct file *file)	\
	{	\
		return single_open(	\
				file,	\
				mt_ ## name ## _proc_show,	\
				PDE_DATA(inode));	\
	}	\
	static const struct file_operations mt_ ## name ## _proc_fops =	\
	{	\
		.owner = THIS_MODULE,	\
		.open = mt_ ## name ## _proc_open,	\
		.read = seq_read,	\
		.llseek = seq_lseek,	\
		.release = single_release,	\
	}
#define PROC_ENTRY(name) \
	{__stringify(name), &mt_ ## name ## _proc_fops}
#endif

/**************************************************
 * Operation Definition
 **************************************************/
#define VOLT_NORMALIZATION(volt)	\
	((volt % 625) ? (volt - (volt % 625) + 625) : volt)
#ifndef MIN
#define MIN(x, y)	(((x) < (y)) ? (x) : (y))
#endif

#define GPUOP(khz, vgpu, vsram, post_divider, aging_margin)	\
	{							\
		.gpufreq_khz = khz,				\
		.gpufreq_vgpu = vgpu,				\
		.gpufreq_vsram = vsram,				\
		.gpufreq_post_divider = post_divider,		\
		.gpufreq_aging_margin = aging_margin,		\
	}

/**************************************************
 * Enumerations
 **************************************************/
/*MT6781_PORTING_TODO: check the segment settings*/
enum g_segment_id_enum {
	MT6781_SEGMENT = 1,
};

enum g_posdiv_power_enum  {
	POSDIV_POWER_1 = 0,
	POSDIV_POWER_2,
	POSDIV_POWER_4,
	POSDIV_POWER_8,
	POSDIV_POWER_16,
};
enum g_clock_source_enum  {
	CLOCK_MAIN = 0,
	CLOCK_SUB,
};

enum g_limit_enable_enum  {
	LIMIT_DISABLE = 0,
	LIMIT_ENABLE,
};

enum {
	GPUFREQ_LIMIT_PRIO_NONE,	/* the lowest priority */
	GPUFREQ_LIMIT_PRIO_1,
	GPUFREQ_LIMIT_PRIO_2,
	GPUFREQ_LIMIT_PRIO_3,
	GPUFREQ_LIMIT_PRIO_4,
	GPUFREQ_LIMIT_PRIO_5,
	GPUFREQ_LIMIT_PRIO_6,
	GPUFREQ_LIMIT_PRIO_7,
	GPUFREQ_LIMIT_PRIO_8		/* the highest priority */
};

struct gpudvfs_limit {
	unsigned int kicker;
	char *name;
	unsigned int prio;
	unsigned int upper_idx;
	unsigned int upper_enable;
	unsigned int lower_idx;
	unsigned int lower_enable;
};

#define LIMIT_IDX_DEFAULT -1

struct gpudvfs_limit limit_table[] = {
	{KIR_STRESS,		"STRESS",	GPUFREQ_LIMIT_PRIO_8,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_PROC,			"PROC",		GPUFREQ_LIMIT_PRIO_7,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_PTPOD,			"PTPOD",	GPUFREQ_LIMIT_PRIO_6,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_THERMAL,		"THERMAL",	GPUFREQ_LIMIT_PRIO_5,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_BATT_OC,		"BATT_OC",	GPUFREQ_LIMIT_PRIO_5,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_BATT_LOW,		"BATT_LOW",	GPUFREQ_LIMIT_PRIO_5,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_BATT_PERCENT,	"BATT_PERCENT",	GPUFREQ_LIMIT_PRIO_5,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_PBM,			"PBM",		GPUFREQ_LIMIT_PRIO_5,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_POLICY,		"POLICY",	GPUFREQ_LIMIT_PRIO_4,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
};

/**************************************************
 * Structures
 **************************************************/
struct opp_table_info {
	unsigned int gpufreq_khz;
	unsigned int gpufreq_vgpu;
	unsigned int gpufreq_vsram;
	enum g_posdiv_power_enum gpufreq_post_divider;
	unsigned int gpufreq_aging_margin;
};
struct g_clk_info {
	struct clk *clk_mux;
	struct clk *clk_main_parent;
	struct clk *clk_sub_parent;
	struct clk *subsys_mfg_cg;
	struct clk *mtcmos_mfg_async;
	struct clk *mtcmos_mfg;
	struct clk *mtcmos_mfg_core0;
	struct clk *mtcmos_mfg_core1;
};
struct g_pmic_info {
	struct regulator *reg_vgpu;
	struct regulator *reg_vsram_gpu;
};

/**************************************************
 * External functions declaration
 **************************************************/
extern bool mtk_get_gpu_loading(unsigned int *pLoading);
extern unsigned int mt_get_abist_freq(unsigned int idx);
extern unsigned int mt_get_ckgen_freq(unsigned int ID);

/**************************************************
 * global value definition
 **************************************************/
struct opp_table_info *g_opp_table;

/**************************************************
 * PTPOD definition
 **************************************************/
unsigned int g_ptpod_opp_idx_table_segment[] = {
	0, 16, 19, 22,
	25, 28, 30, 32,
	34, 36, 38, 40,
	42, 44, 46, 48
};

/**************************************************
 * GPU OPP table definition
 **************************************************/
struct opp_table_info g_opp_table_segment_0[] = {
	GPUOP(950000, 90000, 100000, POSDIV_POWER_4, 625), /* 0 sign off */
	GPUOP(940000, 89375, 99375,  POSDIV_POWER_4, 625), /* 1 */
	GPUOP(930000, 88750, 98750,  POSDIV_POWER_4, 625), /* 2 */
	GPUOP(920000, 88125, 98125,  POSDIV_POWER_4, 625), /* 3 */
	GPUOP(910000, 87500, 97500,  POSDIV_POWER_4, 625), /* 4 */
	GPUOP(900000, 86875, 96875,  POSDIV_POWER_4, 625), /* 5 */
	GPUOP(890000, 86250, 96250,  POSDIV_POWER_4, 625), /* 6 */
	GPUOP(880000, 85625, 95625,  POSDIV_POWER_4, 625), /* 7 */
	GPUOP(870000, 85000, 95000,  POSDIV_POWER_4, 625), /* 8 */
	GPUOP(860000, 84375, 94375,  POSDIV_POWER_4, 625), /* 9 */
	GPUOP(850000, 83750, 93750,  POSDIV_POWER_4, 625), /*10 */
	GPUOP(840000, 83125, 93125,  POSDIV_POWER_4, 625), /*11 */
	GPUOP(830000, 82500, 92500,  POSDIV_POWER_4, 625), /*12 */
	GPUOP(820000, 81875, 91875,  POSDIV_POWER_4, 625), /*13 */
	GPUOP(810000, 81250, 91250,  POSDIV_POWER_4, 625), /*14 */
	GPUOP(800000, 80625, 90625,  POSDIV_POWER_4, 625), /*15 */
	GPUOP(790000, 80000, 90000,  POSDIV_POWER_4, 625), /*16 sign off */
	GPUOP(775000, 79375, 89375,  POSDIV_POWER_4, 625), /*17 */
	GPUOP(761000, 78750, 88750,  POSDIV_POWER_4, 625), /*18 */
	GPUOP(746000, 78125, 88125,  POSDIV_POWER_4, 625), /*19 */
	GPUOP(732000, 77500, 87500,  POSDIV_POWER_4, 625), /*20 */
	GPUOP(718000, 76875, 86875,  POSDIV_POWER_4, 625), /*21 */
	GPUOP(703000, 76250, 86250,  POSDIV_POWER_4, 625), /*22 */
	GPUOP(689000, 75625, 85625,  POSDIV_POWER_4, 625), /*23 */
	GPUOP(675000, 75000, 85000,  POSDIV_POWER_4, 625), /*24 */
	GPUOP(660000, 74375, 85000,  POSDIV_POWER_4, 625), /*25 */
	GPUOP(646000, 73750, 85000,  POSDIV_POWER_4, 625), /*26 */
	GPUOP(631000, 73125, 85000,  POSDIV_POWER_4, 625), /*27 */
	GPUOP(617000, 72500, 85000,  POSDIV_POWER_4, 625), /*28 */
	GPUOP(603000, 71875, 85000,  POSDIV_POWER_4, 625), /*29 */
	GPUOP(588000, 71250, 85000,  POSDIV_POWER_4, 625), /*30 */
	GPUOP(574000, 70625, 85000,  POSDIV_POWER_4, 625), /*31 */
	GPUOP(560000, 70000, 85000,  POSDIV_POWER_4, 625), /*32 sign off */
	GPUOP(543000, 69375, 85000,  POSDIV_POWER_4, 625), /*33 */
	GPUOP(527000, 68750, 85000,  POSDIV_POWER_4, 625), /*34 */
	GPUOP(511000, 68125, 85000,  POSDIV_POWER_4, 625), /*35 */
	GPUOP(495000, 67500, 85000,  POSDIV_POWER_4, 625), /*36 */
	GPUOP(478000, 66875, 85000,  POSDIV_POWER_4, 625), /*37 */
	GPUOP(462000, 66250, 85000,  POSDIV_POWER_4, 625), /*38 */
	GPUOP(446000, 65625, 85000,  POSDIV_POWER_4, 625), /*39 */
	GPUOP(430000, 65000, 85000,  POSDIV_POWER_4, 625), /*40 */
	GPUOP(413000, 64375, 85000,  POSDIV_POWER_4, 625), /*41 */
	GPUOP(397000, 63750, 85000,  POSDIV_POWER_4, 625), /*42 */
	GPUOP(381000, 63125, 85000,  POSDIV_POWER_4, 625), /*43 */
	GPUOP(365000, 62500, 85000,  POSDIV_POWER_8, 625), /*44 */
	GPUOP(348000, 61875, 85000,  POSDIV_POWER_8, 625), /*45 */
	GPUOP(332000, 61250, 85000,  POSDIV_POWER_8, 625), /*46 */
	GPUOP(316000, 60625, 85000,  POSDIV_POWER_8, 625), /*47 */
	GPUOP(300000, 60000, 85000,  POSDIV_POWER_8, 625), /*48 sign off */
};

/*voltage + 50mv*/
struct opp_table_info g_opp_table_segment_1[] = {
	GPUOP(950000, 95000, 100000, POSDIV_POWER_4, 625), /* 0 sign off */
	GPUOP(940000, 94375, 99375,  POSDIV_POWER_4, 625), /* 1 */
	GPUOP(930000, 93750, 98750,  POSDIV_POWER_4, 625), /* 2 */
	GPUOP(920000, 93125, 98125,  POSDIV_POWER_4, 625), /* 3 */
	GPUOP(910000, 92500, 97500,  POSDIV_POWER_4, 625), /* 4 */
	GPUOP(900000, 91875, 96875,  POSDIV_POWER_4, 625), /* 5 */
	GPUOP(890000, 91250, 96250,  POSDIV_POWER_4, 625), /* 6 */
	GPUOP(880000, 90625, 95625,  POSDIV_POWER_4, 625), /* 7 */
	GPUOP(870000, 90000, 95000,  POSDIV_POWER_4, 625), /* 8 */
	GPUOP(860000, 89375, 94375,  POSDIV_POWER_4, 625), /* 9 */
	GPUOP(850000, 88750, 93750,  POSDIV_POWER_4, 625), /*10 */
	GPUOP(840000, 88125, 93125,  POSDIV_POWER_4, 625), /*11 */
	GPUOP(830000, 87500, 92500,  POSDIV_POWER_4, 625), /*12 */
	GPUOP(820000, 86875, 91875,  POSDIV_POWER_4, 625), /*13 */
	GPUOP(810000, 86250, 91250,  POSDIV_POWER_4, 625), /*14 */
	GPUOP(800000, 85625, 90625,  POSDIV_POWER_4, 625), /*15 */
	GPUOP(790000, 85000, 90000,  POSDIV_POWER_4, 625), /*16 sign off */
	GPUOP(775000, 84375, 89375,  POSDIV_POWER_4, 625), /*17 */
	GPUOP(761000, 83750, 88750,  POSDIV_POWER_4, 625), /*18 */
	GPUOP(746000, 83125, 88125,  POSDIV_POWER_4, 625), /*19 */
	GPUOP(732000, 82500, 87500,  POSDIV_POWER_4, 625), /*20 */
	GPUOP(718000, 81875, 86875,  POSDIV_POWER_4, 625), /*21 */
	GPUOP(703000, 81250, 86250,  POSDIV_POWER_4, 625), /*22 */
	GPUOP(689000, 80625, 85625,  POSDIV_POWER_4, 625), /*23 */
	GPUOP(675000, 80000, 85000,  POSDIV_POWER_4, 625), /*24 */
	GPUOP(660000, 79375, 85000,  POSDIV_POWER_4, 625), /*25 */
	GPUOP(646000, 78750, 85000,  POSDIV_POWER_4, 625), /*26 */
	GPUOP(631000, 78125, 85000,  POSDIV_POWER_4, 625), /*27 */
	GPUOP(617000, 77500, 85000,  POSDIV_POWER_4, 625), /*28 */
	GPUOP(603000, 76875, 85000,  POSDIV_POWER_4, 625), /*29 */
	GPUOP(588000, 76250, 85000,  POSDIV_POWER_4, 625), /*30 */
	GPUOP(574000, 75625, 85000,  POSDIV_POWER_4, 625), /*31 */
	GPUOP(560000, 75000, 85000,  POSDIV_POWER_4, 625), /*32 sign off */
	GPUOP(543000, 74375, 85000,  POSDIV_POWER_4, 625), /*33 */
	GPUOP(527000, 73125, 85000,  POSDIV_POWER_4, 625), /*34 */
	GPUOP(511000, 72500, 85000,  POSDIV_POWER_4, 625), /*35 */
	GPUOP(495000, 71250, 85000,  POSDIV_POWER_4, 625), /*36 */
	GPUOP(478000, 70625, 85000,  POSDIV_POWER_4, 625), /*37 */
	GPUOP(462000, 69375, 85000,  POSDIV_POWER_4, 625), /*38 */
	GPUOP(446000, 68750, 85000,  POSDIV_POWER_4, 625), /*39 */
	GPUOP(430000, 67500, 85000,  POSDIV_POWER_4, 625), /*40 */
	GPUOP(413000, 66875, 85000,  POSDIV_POWER_4, 625), /*41 */
	GPUOP(397000, 65625, 85000,  POSDIV_POWER_4, 625), /*42 */
	GPUOP(381000, 65000, 85000,  POSDIV_POWER_4, 625), /*43 */
	GPUOP(365000, 63750, 85000,  POSDIV_POWER_8, 625), /*44 */
	GPUOP(348000, 63125, 85000,  POSDIV_POWER_8, 625), /*45 */
	GPUOP(332000, 61875, 85000,  POSDIV_POWER_8, 625), /*46 */
	GPUOP(316000, 61250, 85000,  POSDIV_POWER_8, 625), /*47 */
	GPUOP(300000, 60000, 85000,  POSDIV_POWER_8, 625), /*48 sign off */
};

#endif /* ___MT_GPUFREQ_INTERNAL_PLAT_H___ */
