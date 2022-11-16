/*
 * Copyright (C) 2021 MediaTek Inc.
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

#include <linux/clk.h>

#include "n3d_clk.h"
#include "n3d_util.h"

static struct SENINF_N3D_CLK_CTRL gn3d_clk_name[N3D_CLK_IDX_SYS_MAX_NUM] = {
	{"SCP_SYS_MDP"},
	{"SCP_SYS_CAM"},
	{"CAMSYS_SENINF_CGPDN"},
	{"CAMSYS_CAMTG_CGPDN"},
};

void n3d_clk_init(struct SENINF_N3D_CLK *pclk)
{
	int i;

	if (pclk->pplatform_device == NULL) {
		LOG_E("[%s] pdev is null\n", __func__);
		return;
	}
	/* get all possible using clocks */
	for (i = 0; i < N3D_CLK_IDX_SYS_MAX_NUM; i++) {
		pclk->clk_sel[i] = devm_clk_get(&pclk->pplatform_device->dev,
						gn3d_clk_name[i].pctrl);
		atomic_set(&pclk->enable_cnt[i], 0);

		if (IS_ERR(pclk->clk_sel[i])) {
			LOG_E("cannot get %d clock\n", i);
			return;
		}
	}
#ifdef CONFIG_PM_SLEEP
	wakeup_source_init(&pclk->n3d_wake_lock, "seninf_lock_wakelock");
#endif
	atomic_set(&pclk->wakelock_cnt, 0);
}

void n3d_clk_open(struct SENINF_N3D_CLK *pclk)
{
	int i;

	LOG_D("E\n");

	if (atomic_inc_return(&pclk->wakelock_cnt) == 1) {
#ifdef CONFIG_PM_SLEEP
		__pm_stay_awake(&pclk->n3d_wake_lock);
#endif
	}

	for (i = N3D_CLK_IDX_SYS_MIN_NUM;
		i < N3D_CLK_IDX_SYS_MAX_NUM;
		i++) {
		if (pclk->clk_sel[i] && IS_ERR(pclk->clk_sel[i])) {
			LOG_D("skip clk\n");
			continue;
		}
		if (clk_prepare_enable(pclk->clk_sel[i]))
			LOG_E("[CAMERA SENSOR N3D] failed sys idx= %d\n", i);
		else
			atomic_inc(&pclk->enable_cnt[i]);
	}
}

void n3d_clk_release(struct SENINF_N3D_CLK *pclk)
{
	int i = N3D_CLK_IDX_SYS_MAX_NUM;

	LOG_D("E\n");

	do {
		i--;
		for (; atomic_read(&pclk->enable_cnt[i]) > 0;) {
			clk_disable_unprepare(pclk->clk_sel[i]);
			atomic_dec(&pclk->enable_cnt[i]);
		}
	} while (i);

	if (atomic_dec_and_test(&pclk->wakelock_cnt)) {
#ifdef CONFIG_PM_SLEEP
		__pm_relax(&pclk->n3d_wake_lock);
#endif
	}
}

