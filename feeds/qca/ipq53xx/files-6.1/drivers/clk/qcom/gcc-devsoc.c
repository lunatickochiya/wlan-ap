// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2018,2020 The Linux Foundation. All rights reserved.
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/clk-provider.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>

#include <dt-bindings/clock/qcom,devsoc-gcc.h>
#include <dt-bindings/reset/qcom,devsoc-gcc.h>

#include "clk-alpha-pll.h"
#include "clk-branch.h"
#include "clk-rcg.h"
#include "clk-regmap.h"
#include "clk-regmap-divider.h"
#include "clk-regmap-mux.h"
#include "clk-regmap-phy-mux.h"
#include "common.h"
#include "reset.h"

static int clk_dummy_is_enabled(struct clk_hw *hw)
{
	return 1;
};

static int clk_dummy_enable(struct clk_hw *hw)
{
	return 0;
};

static void clk_dummy_disable(struct clk_hw *hw)
{
	return;
};

static u8 clk_dummy_get_parent(struct clk_hw *hw)
{
	return 0;
};

static int clk_dummy_set_parent(struct clk_hw *hw, u8 index)
{
	return 0;
};

static int clk_dummy_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	return 0;
};

static int clk_dummy_determine_rate(struct clk_hw *hw,
		struct clk_rate_request *req)
{
	return 0;
};

static unsigned long clk_dummy_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	return parent_rate;
};

static const struct clk_ops clk_dummy_ops = {
	.is_enabled = clk_dummy_is_enabled,
	.enable = clk_dummy_enable,
	.disable = clk_dummy_disable,
	.get_parent = clk_dummy_get_parent,
	.set_parent = clk_dummy_set_parent,
	.set_rate = clk_dummy_set_rate,
	.recalc_rate = clk_dummy_recalc_rate,
	.determine_rate = clk_dummy_determine_rate,
};

#define DEFINE_DUMMY_CLK(clk_name)                              \
	(&(struct clk_regmap) {                                         \
	 .hw.init = &(struct clk_init_data){                     \
	 .name = #clk_name,                              \
	 .parent_names = (const char *[]){ "xo"},        \
	 .num_parents = 1,                               \
	 .ops = &clk_dummy_ops,                          \
	 },                                                      \
	 })

static struct clk_regmap *gcc_devsoc_dummy_clks[] = {
	[GPLL0_MAIN] = DEFINE_DUMMY_CLK(gpll0_main),
	[GPLL0] = DEFINE_DUMMY_CLK(gpll0),
	[GPLL4_MAIN] = DEFINE_DUMMY_CLK(gpll4_main),
	[GPLL4] = DEFINE_DUMMY_CLK(gpll4),
	[GPLL2_MAIN] = DEFINE_DUMMY_CLK(gpll2_main),
	[GPLL2] = DEFINE_DUMMY_CLK(gpll2),
	[GCC_SLEEP_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_sleep_clk_src),
	[GCC_APSS_AHB_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_apss_ahb_clk_src),
	[GCC_APSS_AXI_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_apss_axi_clk_src),
	[GCC_APSS_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_apss_ahb_clk),
	[GCC_APSS_AXI_CLK] = DEFINE_DUMMY_CLK(gcc_apss_axi_clk),
	[GCC_CPUSS_TRIG_CLK] = DEFINE_DUMMY_CLK(gcc_cpuss_trig_clk),
	[GCC_GEMNOC_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_gemnoc_ahb_clk),
	[GCC_GEMNOC_ANOC_CLK] = DEFINE_DUMMY_CLK(gcc_gemnoc_anoc_clk),
	[GCC_GEMNOC_APSS_CLK] = DEFINE_DUMMY_CLK(gcc_gemnoc_apss_clk),
	[GCC_GEMNOC_CNOC_CLK] = DEFINE_DUMMY_CLK(gcc_gemnoc_cnoc_clk),
	[GCC_GEMNOC_NSSNOC_CLK] = DEFINE_DUMMY_CLK(gcc_gemnoc_nssnoc_clk),
	[GCC_GEMNOC_Q6_AXI_CLK] = DEFINE_DUMMY_CLK(gcc_gemnoc_q6_axi_clk),
	[GCC_GEMNOC_QOSGEN_EXTREF_CLK] = DEFINE_DUMMY_CLK(gcc_gemnoc_qosgen_extref_clk),
	[GCC_GEMNOC_SNOC_CLK] = DEFINE_DUMMY_CLK(gcc_gemnoc_snoc_clk),
	[GCC_GEMNOC_TS_CLK] = DEFINE_DUMMY_CLK(gcc_gemnoc_ts_clk),
	[GCC_GEMNOC_XO_DBG_CLK] = DEFINE_DUMMY_CLK(gcc_gemnoc_xo_dbg_clk),
	[GCC_LLCC_TPDM_CFG_CLK] = DEFINE_DUMMY_CLK(gcc_llcc_tpdm_cfg_clk),
	[GCC_DEBUG_CLK] = DEFINE_DUMMY_CLK(gcc_debug_clk),
	[GCC_USB0_EUD_AT_CLK] = DEFINE_DUMMY_CLK(gcc_usb0_eud_at_clk),
	[GCC_PCIE0_AXI_M_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie0_axi_m_clk_src),
	[GCC_PCIE0_AXI_M_CLK] = DEFINE_DUMMY_CLK(gcc_pcie0_axi_m_clk),
	[GCC_PCIE1_AXI_M_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie1_axi_m_clk_src),
	[GCC_PCIE1_AXI_M_CLK] = DEFINE_DUMMY_CLK(gcc_pcie1_axi_m_clk),
	[GCC_PCIE2_AXI_M_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie2_axi_m_clk_src),
	[GCC_PCIE2_AXI_M_CLK] = DEFINE_DUMMY_CLK(gcc_pcie2_axi_m_clk),
	[GCC_PCIE3_AXI_M_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie3_axi_m_clk_src),
	[GCC_PCIE3_AXI_M_CLK] = DEFINE_DUMMY_CLK(gcc_pcie3_axi_m_clk),
	[GCC_PCIE0_AXI_S_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie0_axi_s_clk_src),
	[GCC_PCIE0_AXI_S_BRIDGE_CLK] = DEFINE_DUMMY_CLK(gcc_pcie0_axi_s_bridge_clk),
	[GCC_PCIE0_AXI_S_CLK] = DEFINE_DUMMY_CLK(gcc_pcie0_axi_s_clk),
	[GCC_PCIE1_AXI_S_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie1_axi_s_clk_src),
	[GCC_PCIE1_AXI_S_BRIDGE_CLK] = DEFINE_DUMMY_CLK(gcc_pcie1_axi_s_bridge_clk),
	[GCC_PCIE1_AXI_S_CLK] = DEFINE_DUMMY_CLK(gcc_pcie1_axi_s_clk),
	[GCC_PCIE2_AXI_S_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie2_axi_s_clk_src),
	[GCC_PCIE2_AXI_S_BRIDGE_CLK] = DEFINE_DUMMY_CLK(gcc_pcie2_axi_s_bridge_clk),
	[GCC_PCIE2_AXI_S_CLK] = DEFINE_DUMMY_CLK(gcc_pcie2_axi_s_clk),
	[GCC_PCIE3_AXI_S_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie3_axi_s_clk_src),
	[GCC_PCIE3_AXI_S_BRIDGE_CLK] = DEFINE_DUMMY_CLK(gcc_pcie3_axi_s_bridge_clk),
	[GCC_PCIE3_AXI_S_CLK] = DEFINE_DUMMY_CLK(gcc_pcie3_axi_s_clk),
	[GCC_PCIE0_PIPE_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie0_pipe_clk_src),
	[GCC_PCIE0_PIPE_CLK] = DEFINE_DUMMY_CLK(gcc_pcie0_pipe_clk),
	[GCC_PCIE1_PIPE_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie1_pipe_clk_src),
	[GCC_PCIE1_PIPE_CLK] = DEFINE_DUMMY_CLK(gcc_pcie1_pipe_clk),
	[GCC_PCIE2_PIPE_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie2_pipe_clk_src),
	[GCC_PCIE2_PIPE_CLK] = DEFINE_DUMMY_CLK(gcc_pcie2_pipe_clk),
	[GCC_PCIE3_PIPE_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie3_pipe_clk_src),
	[GCC_PCIE3_PIPE_CLK] = DEFINE_DUMMY_CLK(gcc_pcie3_pipe_clk),
	[GCC_PCIE_AUX_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie_aux_clk_src),
	[GCC_PCIE0_AUX_CLK] = DEFINE_DUMMY_CLK(gcc_pcie0_aux_clk),
	[GCC_PCIE1_AUX_CLK] = DEFINE_DUMMY_CLK(gcc_pcie1_aux_clk),
	[GCC_PCIE2_AUX_CLK] = DEFINE_DUMMY_CLK(gcc_pcie2_aux_clk),
	[GCC_PCIE3_AUX_CLK] = DEFINE_DUMMY_CLK(gcc_pcie3_aux_clk),
	[GCC_PCIE0_RCHNG_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie0_rchng_clk_src),
	[GCC_PCIE0_RCHNG_CLK] = DEFINE_DUMMY_CLK(gcc_pcie0_rchng_clk),
	[GCC_PCIE1_RCHNG_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie1_rchng_clk_src),
	[GCC_PCIE1_RCHNG_CLK] = DEFINE_DUMMY_CLK(gcc_pcie1_rchng_clk),
	[GCC_PCIE2_RCHNG_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie2_rchng_clk_src),
	[GCC_PCIE2_RCHNG_CLK] = DEFINE_DUMMY_CLK(gcc_pcie2_rchng_clk),
	[GCC_PCIE3_RCHNG_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcie3_rchng_clk_src),
	[GCC_PCIE3_RCHNG_CLK] = DEFINE_DUMMY_CLK(gcc_pcie3_rchng_clk),
	[GCC_PCIE0_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_pcie0_ahb_clk),
	[GCC_PCIE1_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_pcie1_ahb_clk),
	[GCC_PCIE2_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_pcie2_ahb_clk),
	[GCC_PCIE3_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_pcie3_ahb_clk),
	[GCC_USB0_AUX_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_usb0_aux_clk_src),
	[GCC_USB0_AUX_CLK] = DEFINE_DUMMY_CLK(gcc_usb0_aux_clk),
	[GCC_USB0_MASTER_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_usb0_master_clk_src),
	[GCC_USB0_MASTER_CLK] = DEFINE_DUMMY_CLK(gcc_usb0_master_clk),
	[GCC_USB0_MOCK_UTMI_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_usb0_mock_utmi_clk_src),
	[GCC_USB0_MOCK_UTMI_DIV_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_usb0_mock_utmi_div_clk_src),
	[GCC_USB0_MOCK_UTMI_CLK] = DEFINE_DUMMY_CLK(gcc_usb0_mock_utmi_clk),
	[GCC_USB0_PIPE_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_usb0_pipe_clk_src),
	[GCC_USB0_PIPE_CLK] = DEFINE_DUMMY_CLK(gcc_usb0_pipe_clk),
	[GCC_USB0_PHY_CFG_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_usb0_phy_cfg_ahb_clk),
	[GCC_USB0_SLEEP_CLK] = DEFINE_DUMMY_CLK(gcc_usb0_sleep_clk),
	[GCC_SDCC1_APPS_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_sdcc1_apps_clk_src),
	[GCC_SDCC1_APPS_CLK] = DEFINE_DUMMY_CLK(gcc_sdcc1_apps_clk),
	[GCC_SDCC1_ICE_CORE_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_sdcc1_ice_core_clk_src),
	[GCC_SDCC1_ICE_CORE_CLK] = DEFINE_DUMMY_CLK(gcc_sdcc1_ice_core_clk),
	[GCC_SDCC1_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_sdcc1_ahb_clk),
	[GCC_PCNOC_BFDCD_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcnoc_bfdcd_clk_src),
	[GCC_NSSCFG_CLK] = DEFINE_DUMMY_CLK(gcc_nsscfg_clk),
	[GCC_NSSNOC_NSSCC_CLK] = DEFINE_DUMMY_CLK(gcc_nssnoc_nsscc_clk),
	[GCC_NSSCC_CLK] = DEFINE_DUMMY_CLK(gcc_nsscc_clk),
	[GCC_NSSNOC_PCNOC_1_CLK] = DEFINE_DUMMY_CLK(gcc_nssnoc_pcnoc_1_clk),
	[GCC_QDSS_DAP_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_dap_ahb_clk),
	[GCC_QDSS_CFG_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_cfg_ahb_clk),
	[GCC_SNOC_PCNOC_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_snoc_pcnoc_ahb_clk),
	[GCC_ANOC_PCNOC_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_anoc_pcnoc_ahb_clk),
	[GCC_QDSS_USB_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_usb_clk),
	[GCC_QPIC_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_qpic_ahb_clk),
	[GCC_QPIC_CLK] = DEFINE_DUMMY_CLK(gcc_qpic_clk),
	[GCC_Q6_AXIS_CLK] = DEFINE_DUMMY_CLK(gcc_q6_axis_clk),
	[GCC_MDIO_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_mdio_ahb_clk),
	[GCC_MPM_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_mpm_ahb_clk),
	[GCC_PRNG_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_prng_ahb_clk),
	[GCC_UNIPHY0_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_uniphy0_ahb_clk),
	[GCC_UNIPHY1_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_uniphy1_ahb_clk),
	[GCC_UNIPHY2_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_uniphy2_ahb_clk),
	[GCC_CMN_12GPLL_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_cmn_12gpll_ahb_clk),
	[GCC_CMN_12GPLL_APU_CLK] = DEFINE_DUMMY_CLK(gcc_cmn_12gpll_apu_clk),
	[GCC_SYSTEM_NOC_BFDCD_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_system_noc_bfdcd_clk_src),
	[GCC_NSSNOC_SNOC_CLK] = DEFINE_DUMMY_CLK(gcc_nssnoc_snoc_clk),
	[GCC_NSSNOC_SNOC_1_CLK] = DEFINE_DUMMY_CLK(gcc_nssnoc_snoc_1_clk),
	[GCC_QDSS_ETR_USB_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_etr_usb_clk),
	[GCC_SYS_NOC_AXI_CLK] = DEFINE_DUMMY_CLK(gcc_sys_noc_axi_clk),
	[GCC_ANOC0_AXI_CLK] = DEFINE_DUMMY_CLK(gcc_anoc0_axi_clk),
	[GCC_IMEM_AXI_CLK] = DEFINE_DUMMY_CLK(gcc_imem_axi_clk),
	[GCC_WCSS_AHB_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_wcss_ahb_clk_src),
	[GCC_WCSS_AXI_M_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_wcss_axi_m_clk_src),
	[GCC_QDSS_AT_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qdss_at_clk_src),
	[GCC_NSSNOC_ATB_CLK] = DEFINE_DUMMY_CLK(gcc_nssnoc_atb_clk),
	[GCC_QDSS_AT_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_at_clk),
	[GCC_SYS_NOC_AT_CLK] = DEFINE_DUMMY_CLK(gcc_sys_noc_at_clk),
	[GCC_PCNOC_AT_CLK] = DEFINE_DUMMY_CLK(gcc_pcnoc_at_clk),
	[GCC_QDSS_EUD_AT_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_eud_at_clk),
	[GCC_QDSS_STM_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qdss_stm_clk_src),
	[GCC_QDSS_STM_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_stm_clk),
	[GCC_QDSS_TRACECLKIN_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qdss_traceclkin_clk_src),
	[GCC_QDSS_TRACECLKIN_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_traceclkin_clk),
	[GCC_QDSS_TSCTR_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qdss_tsctr_clk_src),
	[GCC_QDSS_TSCTR_DIV2_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_tsctr_div2_clk),
	[GCC_QDSS_TS_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_ts_clk),
	[GCC_SNOC_TS_CLK] = DEFINE_DUMMY_CLK(gcc_snoc_ts_clk),
	[GCC_QDSS_TSCTR_DIV4_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_tsctr_div4_clk),
	[GCC_NSS_TS_CLK] = DEFINE_DUMMY_CLK(gcc_nss_ts_clk),
	[GCC_QDSS_TSCTR_DIV8_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_tsctr_div8_clk),
	[GCC_PCNOC_TS_CLK] = DEFINE_DUMMY_CLK(gcc_pcnoc_ts_clk),
	[GCC_QDSS_TSCTR_DIV16_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_tsctr_div16_clk),
	[GCC_QDSS_DAP_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_dap_clk),
	[GCC_QDSS_APB2JTAG_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_apb2jtag_clk),
	[GCC_QDSS_TSCTR_DIV3_CLK] = DEFINE_DUMMY_CLK(gcc_qdss_tsctr_div3_clk),
	[GCC_QPIC_IO_MACRO_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qpic_io_macro_clk_src),
	[GCC_QPIC_IO_MACRO_CLK] = DEFINE_DUMMY_CLK(gcc_qpic_io_macro_clk),
	[GCC_Q6_AXI_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_q6_axi_clk_src),
	[GCC_NSSNOC_MEMNOC_BFDCD_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_nssnoc_memnoc_bfdcd_clk_src),
	[GCC_NSSNOC_MEMNOC_CLK] = DEFINE_DUMMY_CLK(gcc_nssnoc_memnoc_clk),
	[GCC_NSSNOC_MEM_NOC_1_CLK] = DEFINE_DUMMY_CLK(gcc_nssnoc_mem_noc_1_clk),
	[GCC_LPASS_AXIM_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_lpass_axim_clk_src),
	[GCC_LPASS_CORE_AXIM_CLK] = DEFINE_DUMMY_CLK(gcc_lpass_core_axim_clk),
	[GCC_PCNOC_LPASS_CLK] = DEFINE_DUMMY_CLK(gcc_pcnoc_lpass_clk),
	[GCC_LPASS_SWAY_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_lpass_sway_clk_src),
	[GCC_LPASS_SWAY_CLK] = DEFINE_DUMMY_CLK(gcc_lpass_sway_clk),
	[GCC_SNOC_LPASS_CFG_CLK] = DEFINE_DUMMY_CLK(gcc_snoc_lpass_cfg_clk),
	[GCC_ADSS_PWM_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_adss_pwm_clk_src),
	[GCC_ADSS_PWM_CLK] = DEFINE_DUMMY_CLK(gcc_adss_pwm_clk),
	[GCC_AGGRNOC_ATB_CLK] = DEFINE_DUMMY_CLK(gcc_aggrnoc_atb_clk),
	[GP1_CLK_SRC] = DEFINE_DUMMY_CLK(gp1_clk_src),
	[GP2_CLK_SRC] = DEFINE_DUMMY_CLK(gp2_clk_src),
	[GP3_CLK_SRC] = DEFINE_DUMMY_CLK(gp3_clk_src),
	[GCC_GP1_CLK] = DEFINE_DUMMY_CLK(gcc_gp1_clk),
	[GCC_GP2_CLK] = DEFINE_DUMMY_CLK(gcc_gp2_clk),
	[GCC_GP3_CLK] = DEFINE_DUMMY_CLK(gcc_gp3_clk),
	[GCC_DDRSS_SMS_SLOW_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_ddrss_sms_slow_clk_src),
	[GCC_DDRSS_SMS_SLOW_CLK] = DEFINE_DUMMY_CLK(gcc_ddrss_sms_slow_clk),
	[GCC_XO_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_xo_clk_src),
	[GCC_NSSNOC_XO_DCD_CLK] = DEFINE_DUMMY_CLK(gcc_nssnoc_xo_dcd_clk),
	[GCC_XO_CLK] = DEFINE_DUMMY_CLK(gcc_xo_clk),
	[GCC_NSSNOC_QOSGEN_REF_CLK] = DEFINE_DUMMY_CLK(gcc_nssnoc_qosgen_ref_clk),
	[GCC_NSSNOC_TIMEOUT_REF_CLK] = DEFINE_DUMMY_CLK(gcc_nssnoc_timeout_ref_clk),
	[GCC_XO_DIV4_CLK] = DEFINE_DUMMY_CLK(gcc_xo_div4_clk),
	[GCC_SPDM_FF_CLK] = DEFINE_DUMMY_CLK(gcc_spdm_ff_clk),
	[GCC_UNIPHY0_SYS_CLK] = DEFINE_DUMMY_CLK(gcc_uniphy0_sys_clk),
	[GCC_UNIPHY1_SYS_CLK] = DEFINE_DUMMY_CLK(gcc_uniphy1_sys_clk),
	[GCC_UNIPHY2_SYS_CLK] = DEFINE_DUMMY_CLK(gcc_uniphy2_sys_clk),
	[GCC_CMN_12GPLL_SYS_CLK] = DEFINE_DUMMY_CLK(gcc_cmn_12gpll_sys_clk),
	[GCC_UNIPHY_SYS_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_uniphy_sys_clk_src),
	[GCC_NSS_TS_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_nss_ts_clk_src),
	[GCC_ANOC_PCIE0_1LANE_M_CLK] = DEFINE_DUMMY_CLK(gcc_anoc_pcie0_1lane_m_clk),
	[GCC_ANOC_PCIE1_1LANE_M_CLK] = DEFINE_DUMMY_CLK(gcc_anoc_pcie1_1lane_m_clk),
	[GCC_ANOC_PCIE2_2LANE_M_CLK] = DEFINE_DUMMY_CLK(gcc_anoc_pcie2_2lane_m_clk),
	[GCC_ANOC_PCIE3_2LANE_M_CLK] = DEFINE_DUMMY_CLK(gcc_anoc_pcie3_2lane_m_clk),
	[GCC_CNOC_PCIE0_1LANE_S_CLK] = DEFINE_DUMMY_CLK(gcc_cnoc_pcie0_1lane_s_clk),
	[GCC_CNOC_PCIE1_1LANE_S_CLK] = DEFINE_DUMMY_CLK(gcc_cnoc_pcie1_1lane_s_clk),
	[GCC_CNOC_PCIE2_2LANE_S_CLK] = DEFINE_DUMMY_CLK(gcc_cnoc_pcie2_2lane_s_clk),
	[GCC_CNOC_PCIE3_2LANE_S_CLK] = DEFINE_DUMMY_CLK(gcc_cnoc_pcie3_2lane_s_clk),
	[GCC_CNOC_APSS_AHB_CLK]	= DEFINE_DUMMY_CLK(gcc_cnoc_apss_ahb_clk),
	[GCC_CNOC_QDSS_STM_AXI_CLK] = DEFINE_DUMMY_CLK(gcc_cnoc_qdss_stm_axi_clk),
	[GCC_CNOC_QOSGEN_EXTREF_CLK] = DEFINE_DUMMY_CLK(gcc_cnoc_qosgen_extref_clk),
	[GCC_CNOC_TME_CFG_CLK] = DEFINE_DUMMY_CLK(gcc_cnoc_tme_cfg_clk),
	[GCC_CNOC_USB_CLK] = DEFINE_DUMMY_CLK(gcc_cnoc_usb_clk),
#ifdef CONFIG_QCOM_NON_SECURE_PIL
	[GCC_CNOC_WCSS_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_cnoc_wcss_ahb_clk),
#endif
	[GCC_QX_CLK] = DEFINE_DUMMY_CLK(gcc_qx_clk),
	[GCC_QUPV3_2X_CORE_CLK] = DEFINE_DUMMY_CLK(gcc_qupv3_2x_core_clk),
	[GCC_QUPV3_AHB_MST_CLK] = DEFINE_DUMMY_CLK(gcc_qupv3_ahb_mst_clk),
	[GCC_QUPV3_AHB_SLV_CLK] = DEFINE_DUMMY_CLK(gcc_qupv3_ahb_slv_clk),
	[GCC_QUPV3_CORE_CLK] = DEFINE_DUMMY_CLK(gcc_qupv3_core_clk),
	[GCC_QUPV3_SLEEP_CLK] = DEFINE_DUMMY_CLK(gcc_qupv3_sleep_clk),
	[GCC_QUPV3_I2C0_CLK] = DEFINE_DUMMY_CLK(gcc_qupv3_i2c0_clk),
	[GCC_QUPV3_I2C1_CLK] = DEFINE_DUMMY_CLK(gcc_qupv3_i2c1_clk),
	[GCC_QUPV3_SPI0_CLK] = DEFINE_DUMMY_CLK(gcc_qupv3_spi0_clk),
	[GCC_QUPV3_SPI1_CLK] = DEFINE_DUMMY_CLK(gcc_qupv3_spi1_clk),
	[GCC_QUPV3_UART0_CLK] = DEFINE_DUMMY_CLK(gcc_qupv3_uart0_clk),
	[GCC_QUPV3_UART1_CLK] = DEFINE_DUMMY_CLK(gcc_qupv3_uart1_clk),
	[GCC_RBCPR_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_rbcpr_ahb_clk),
	[GCC_RBCPR_CLK] = DEFINE_DUMMY_CLK(gcc_rbcpr_clk),
	[GCC_PCNOC_WAPSS_CLK] = DEFINE_DUMMY_CLK(gcc_pcnoc_wapss_clk),
	[GCC_SNOC_WAPSS_CLK] = DEFINE_DUMMY_CLK(gcc_snoc_wapss_clk),
	[GCC_PCNOC_DIV4_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_pcnoc_div4_clk_src),
	[GCC_QDSS_DAP_DIV6_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qdss_dap_div6_clk_src),
	[GCC_ANOC0_AXI_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_anoc0_axi_clk_src),
	[GCC_QX_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qx_clk_src),
	[GCC_QPIC_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qpic_clk_src),
	[GCC_QUPV3_2X_CORE_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qupv3_2x_core_clk_src),
	[GCC_QUPV3_I2C0_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qupv3_i2c0_clk_src),
	[GCC_QUPV3_I2C1_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qupv3_i2c1_clk_src),
	[GCC_QUPV3_SPI0_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qupv3_spi0_clk_src),
        [GCC_QUPV3_SPI1_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qupv3_spi1_clk_src),
	[GCC_QUPV3_UART0_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qupv3_uart0_clk_src),
        [GCC_QUPV3_UART1_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_qupv3_uart1_clk_src),
	[GCC_RBCPR_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_rbcpr_clk_src),
	[GCC_ACC_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_acc_clk_src),
	[GCC_SEC_CTRL_CLK_SRC] = DEFINE_DUMMY_CLK(gcc_sec_ctrl_clk_src),
#ifdef CONFIG_QCOM_NON_SECURE_PIL
	[GCC_Q6_TSCTR_1TO2_CLK] = DEFINE_DUMMY_CLK(gcc_q6_tsctr_1to2_clk),
	[GCC_Q6SS_TRIG_CLK] = DEFINE_DUMMY_CLK(gcc_q6ss_trig_clk),
	[GCC_Q6_AHB_S_CLK] = DEFINE_DUMMY_CLK(gcc_q6_ahb_s_clk),
	[GCC_Q6_AHB_CLK] = DEFINE_DUMMY_CLK(gcc_q6_ahb_clk),
	[GCC_Q6SS_ATBM_CLK] = DEFINE_DUMMY_CLK(gcc_q6ss_atbm_clk),
	[GCC_Q6_AXIM_CLK] = DEFINE_DUMMY_CLK(gcc_q6_axim_clk),
	[GCC_Q6SS_BOOT_CLK] = DEFINE_DUMMY_CLK(gcc_q6ss_boot_clk),
	[GCC_WCSS_ECAHB_CLK] = DEFINE_DUMMY_CLK(gcc_wcss_ecahb_clk),
	[GCC_Q6SS_PCLKDBG_CLK] = DEFINE_DUMMY_CLK(gcc_q6ss_pclkdbg_clk),
#endif
};

static const struct qcom_reset_map gcc_devsoc_resets[] = {
	[GCC_QUPV3_BCR] = { 0x01000, 0 },
	[GCC_QUPV3_I2C0_BCR] = { 0x02000, 0 },
	[GCC_QUPV3_UART0_BCR] = { 0x02020, 0 },
	[GCC_QUPV3_I2C1_BCR] = { 0x03000, 0 },
	[GCC_QUPV3_UART1_BCR] = { 0x03028, 0 },
	[GCC_QUPV3_SPI0_BCR] = { 0x04000, 0 },
	[GCC_QUPV3_SPI1_BCR] = { 0x05000, 0 },
	[GCC_IMEM_BCR] = { 0x0e000, 0 },
	[GCC_TME_BCR] = { 0x100000, 0 },
	[GCC_DDRSS_BCR] = { 0x11000, 0 },
	[GCC_PRNG_BCR] = { 0x13020, 0 },
	[GCC_BOOT_ROM_BCR] = { 0x13028, 0 },
	[GCC_NSS_BCR] = { 0x17000, 0 },
	[GCC_MDIO_BCR] = { 0x1703c, 0 },
	[GCC_UNIPHY0_BCR] = { 0x17044, 0 },
	[GCC_UNIPHY1_BCR] = { 0x17054, 0 },
	[GCC_UNIPHY2_BCR] = { 0x17064, 0 },
#ifdef CONFIG_QCOM_NON_SECURE_PIL
	[GCC_WCSS_Q6_BCR] = { 0x18000, 0 },
#endif
	[GCC_WCSS_BCR] = { 0x18004, 0 },
	[GCC_WAPSS_BCR] = { 0x18008, 0 },
	[GCC_SEC_CTRL_BCR] = { 0x1a000, 0 },
	[GCC_TME_SEC_BUS_BCR] = { 0xa1030, 0 },
	[GCC_ADSS_BCR] = { 0x1c000, 0 },
	[GCC_LPASS_BCR] = { 0x27000, 0 },
	[GCC_PCIE0_BCR] = { 0x28000, 0 },
	[GCC_PCIE0_LINK_DOWN_BCR] = { 0x28054, 0 },
	[GCC_PCIE0PHY_PHY_BCR] = { 0x2805c, 0 },
	[GCC_PCIE0_PHY_BCR] = { 0x28060, 0 },
	[GCC_PCIE1_BCR] = { 0x29000, 0 },
	[GCC_PCIE1_LINK_DOWN_BCR] = { 0x29054, 0 },
	[GCC_PCIE1PHY_PHY_BCR] = { 0x2905c, 0 },
	[GCC_PCIE1_PHY_BCR] = { 0x29060, 0 },
	[GCC_PCIE2_BCR] = { 0x2a000, 0 },
	[GCC_PCIE2_LINK_DOWN_BCR] = { 0x2a054, 0 },
	[GCC_PCIE2PHY_PHY_BCR] = { 0x2a05c, 0 },
	[GCC_PCIE2_PHY_BCR] = { 0x2a060, 0 },
	[GCC_PCIE3_BCR] = { 0x2b000, 0 },
	[GCC_PCIE3_LINK_DOWN_BCR] = { 0x2b054, 0 },
	[GCC_PCIE3PHY_PHY_BCR] = { 0x2b05c, 0 },
	[GCC_PCIE3_PHY_BCR] = { 0x2b060, 0 },
	[GCC_USB_BCR] = { 0x2c000, 0 },
	[GCC_QUSB2_0_PHY_BCR] = { 0x2c068, 0 },
	[GCC_USB0_PHY_BCR] = { 0x2c06c, 0 },
	[GCC_USB3PHY_0_PHY_BCR] = { 0x2c070, 0 },
	[GCC_QDSS_BCR] = { 0x2d000, 0 },
	[GCC_SNOC_BCR] = { 0x2e000, 0 },
	[GCC_ANOC_BCR] = { 0x2e074, 0 },
	[GCC_PCNOC_BCR] = { 0x31000, 0 },
	[GCC_PCNOC_BUS_TIMEOUT0_BCR] = { 0x31030, 0 },
	[GCC_PCNOC_BUS_TIMEOUT1_BCR] = { 0x31038, 0 },
	[GCC_PCNOC_BUS_TIMEOUT2_BCR] = { 0x31040, 0 },
	[GCC_PCNOC_BUS_TIMEOUT3_BCR] = { 0x31048, 0 },
	[GCC_PCNOC_BUS_TIMEOUT4_BCR] = { 0x31050, 0 },
	[GCC_PCNOC_BUS_TIMEOUT5_BCR] = { 0x31058, 0 },
	[GCC_PCNOC_BUS_TIMEOUT6_BCR] = { 0x31060, 0 },
	[GCC_PCNOC_BUS_TIMEOUT7_BCR] = { 0x31068, 0 },
	[GCC_PCNOC_BUS_TIMEOUT8_BCR] = { 0x31070, 0 },
	[GCC_PCNOC_BUS_TIMEOUT9_BCR] = { 0x31078, 0 },
	[GCC_QPIC_BCR] = { 0x32000, 0 },
	[GCC_SDCC_BCR] = { 0x33000, 0 },
	[GCC_DCC_BCR] = { 0x35000, 0 },
	[GCC_SPDM_BCR] = { 0x36000, 0 },
	[GCC_MPM_BCR] = { 0x37000, 0 },
	[GCC_APC0_VOLTAGE_DROOP_DETECTOR_BCR] = { 0x38000, 0 },
	[GCC_RBCPR_BCR] = { 0x39000, 0 },
	[GCC_CMN_BLK_BCR] = { 0x3a000, 0 },
	[GCC_TCSR_BCR] = { 0x3d000, 0 },
	[GCC_TLMM_BCR] = { 0x3e000, 0 },
	[GCC_QUPV3_AHB_MST_ARES] = { 0x01014, 2 },
	[GCC_QUPV3_CORE_ARES] = { 0x01018, 2 },
	[GCC_QUPV3_2X_CORE_ARES] = { 0x01020, 2 },
	[GCC_QUPV3_SLEEP_ARES] = { 0x01028, 2 },
	[GCC_QUPV3_AHB_SLV_ARES] = { 0x0102c, 2 },
	[GCC_QUPV3_I2C0_ARES] = { 0x02024, 2 },
	[GCC_QUPV3_UART0_ARES] = { 0x02040, 2 },
	[GCC_QUPV3_I2C1_ARES] = { 0x03024, 2 },
	[GCC_QUPV3_UART1_ARES] = { 0x03040, 2 },
	[GCC_QUPV3_SPI0_ARES] = { 0x04020, 2 },
	[GCC_QUPV3_SPI1_ARES] = { 0x05020, 2 },
	[GCC_DEBUG_ARES] = { 0x06068, 2 },
	[GCC_GP1_ARES] = { 0x08018, 2 },
	[GCC_GP2_ARES] = { 0x09018, 2 },
	[GCC_GP3_ARES] = { 0x0a018, 2 },
	[GCC_IMEM_AXI_ARES] = { 0x0e004, 2 },
	[GCC_IMEM_CFG_AHB_ARES] = { 0x0e00c, 2 },
	[GCC_TME_ARES] = { 0x100b4, 2 },
	[GCC_TME_TS_ARES] = { 0x100c0, 2 },
	[GCC_TME_SLOW_ARES] = { 0x100d0, 2 },
	[GCC_TME_RTC_TOGGLE_ARES] = { 0x100d8, 2 },
	[GCC_TIC_ARES] = { 0x12004, 2 },
	[GCC_PRNG_AHB_ARES] = { 0x13024, 2 },
	[GCC_BOOT_ROM_AHB_ARES] = { 0x1302c, 2 },
	[GCC_NSSNOC_ATB_ARES] = { 0x17014, 2 },
	[GCC_NSS_TS_ARES] = { 0x17018, 2 },
	[GCC_NSSNOC_QOSGEN_REF_ARES] = { 0x1701c, 2 },
	[GCC_NSSNOC_TIMEOUT_REF_ARES] = { 0x17020, 2 },
	[GCC_NSSNOC_MEMNOC_ARES] = { 0x17024, 2 },
	[GCC_NSSNOC_SNOC_ARES] = { 0x17028, 2 },
	[GCC_NSSCFG_ARES] = { 0x1702c, 2 },
	[GCC_NSSNOC_NSSCC_ARES] = { 0x17030, 2 },
	[GCC_NSSCC_ARES] = { 0x17034, 2 },
	[GCC_MDIO_AHB_ARES] = { 0x17040, 2 },
	[GCC_UNIPHY0_SYS_ARES] = { 0x17048, 2 },
	[GCC_UNIPHY0_AHB_ARES] = { 0x1704c, 2 },
	[GCC_UNIPHY1_SYS_ARES] = { 0x17058, 2 },
	[GCC_UNIPHY1_AHB_ARES] = { 0x1705c, 2 },
	[GCC_UNIPHY2_SYS_ARES] = { 0x17068, 2 },
	[GCC_UNIPHY2_AHB_ARES] = { 0x1706c, 2 },
	[GCC_NSSNOC_XO_DCD_ARES] = { 0x17074, 2 },
	[GCC_NSSNOC_SNOC_1_ARES] = { 0x1707c, 2 },
	[GCC_NSSNOC_PCNOC_1_ARES] = { 0x17080, 2 },
	[GCC_NSSNOC_MEMNOC_1_ARES] = { 0x17084, 2 },
	[GCC_DDRSS_ATB_ARES] = { 0x19004, 2 },
	[GCC_DDRSS_AHB_ARES] = { 0x19008, 2 },
	[GCC_GEMNOC_AHB_ARES] = { 0x1900c, 2 },
	[GCC_GEMNOC_Q6_AXI_ARES] = { 0x19010, 2 },
	[GCC_GEMNOC_NSSNOC_ARES] = { 0x19014, 2 },
	[GCC_GEMNOC_SNOC_ARES] = { 0x19018, 2 },
	[GCC_GEMNOC_APSS_ARES] = { 0x1901c, 2 },
	[GCC_GEMNOC_QOSGEN_EXTREF_ARES] = { 0x19024, 2 },
	[GCC_GEMNOC_TS_ARES] = { 0x19028, 2 },
	[GCC_DDRSS_SMS_SLOW_ARES] = { 0x1902c, 2 },
	[GCC_GEMNOC_CNOC_ARES] = { 0x19038, 2 },
	[GCC_GEMNOC_XO_DBG_ARES] = { 0x19040, 2 },
	[GCC_GEMNOC_ANOC_ARES] = { 0x19048, 2 },
	[GCC_DDRSS_LLCC_ATB_ARES] = { 0x1904c, 2 },
	[GCC_LLCC_TPDM_CFG_ARES] = { 0x19050, 2 },
	[GCC_TME_BUS_ARES] = { 0x1a014, 2 },
	[GCC_SEC_CTRL_ACC_ARES] = { 0x1a018, 2 },
	[GCC_SEC_CTRL_ARES] = { 0x1a020, 2 },
	[GCC_SEC_CTRL_SENSE_ARES] = { 0x1a028, 2 },
	[GCC_SEC_CTRL_AHB_ARES] = { 0x1a038, 2 },
	[GCC_SEC_CTRL_BOOT_ROM_PATCH_ARES] = { 0x1a03c, 2 },
	[GCC_ADSS_PWM_ARES] = { 0x1c00c, 2 },
	[GCC_TME_ATB_ARES] = { 0x1e030, 2 },
	[GCC_TME_DBGAPB_ARES] = { 0x1e034, 2 },
	[GCC_TME_DEBUG_ARES] = { 0x1e038, 2 },
	[GCC_TME_AT_ARES] = { 0x1e03C, 2 },
	[GCC_TME_APB_ARES] = { 0x1e040, 2 },
	[GCC_TME_DMI_DBG_HS_ARES] = { 0x1e044, 2 },
	[GCC_APSS_AHB_ARES] = { 0x24014, 2 },
	[GCC_APSS_AXI_ARES] = { 0x24018, 2 },
	[GCC_CPUSS_TRIG_ARES] = { 0x2401c, 2 },
	[GCC_APSS_DBG_ARES] = { 0x2402c, 2 },
	[GCC_APSS_TS_ARES] = { 0x24030, 2 },
	[GCC_APSS_ATB_ARES] = { 0x24034, 2 },
	[GCC_Q6_AXIM_ARES] = { 0x2500c, 2 },
	[GCC_Q6_AXIS_ARES] = { 0x25010, 2 },
	[GCC_Q6_AHB_ARES] = { 0x25014, 2 },
	[GCC_Q6_AHB_S_ARES] = { 0x25018, 2 },
	[GCC_Q6SS_ATBM_ARES] = { 0x2501c, 2 },
	[GCC_Q6_TSCTR_1TO2_ARES] = { 0x25020, 2 },
	[GCC_Q6SS_PCLKDBG_ARES] = { 0x25024, 2 },
	[GCC_Q6SS_TRIG_ARES] = { 0x25028, 2 },
	[GCC_Q6SS_BOOT_CBCR_ARES] = { 0x2502c, 2 },
	[GCC_WCSS_DBG_IFC_APB_ARES] = { 0x25038, 2 },
	[GCC_WCSS_DBG_IFC_ATB_ARES] = { 0x2503c, 2 },
	[GCC_WCSS_DBG_IFC_NTS_ARES] = { 0x25040, 2 },
	[GCC_WCSS_DBG_IFC_DAPBUS_ARES] = { 0x25044, 2 },
	[GCC_WCSS_DBG_IFC_APB_BDG_ARES] = { 0x25048, 2 },
	[GCC_WCSS_DBG_IFC_NTS_BDG_ARES] = { 0x25050, 2 },
	[GCC_WCSS_DBG_IFC_DAPBUS_BDG_ARES] = { 0x25054, 2 },
	[GCC_WCSS_ECAHB_ARES] = { 0x25058, 2 },
	[GCC_WCSS_ACMT_ARES] = { 0x2505c, 2 },
	[GCC_WCSS_AHB_S_ARES] = { 0x25060, 2 },
	[GCC_WCSS_AXI_M_ARES] = { 0x25064, 2 },
	[GCC_PCNOC_WAPSS_ARES] = { 0x25080, 2 },
	[GCC_SNOC_WAPSS_ARES] = { 0x25090, 2 },
	[GCC_LPASS_SWAY_ARES] = { 0x27014, 2 },
	[GCC_LPASS_CORE_AXIM_ARES] = { 0x27018, 2 },
	[GCC_PCIE0_AHB_ARES] = { 0x28030, 2 },
	[GCC_PCIE0_AXI_M_ARES] = { 0x28038, 2 },
	[GCC_PCIE0_AXI_S_ARES] = { 0x28040, 2 },
	[GCC_PCIE0_AXI_S_BRIDGE_ARES] = { 0x28048, 2},
	[GCC_PCIE0_PIPE_ARES] = { 0x28068, 2},
	[GCC_PCIE0_AUX_ARES] = { 0x28070, 2 },
	[GCC_PCIE1_AHB_ARES] = { 0x29030, 2 },
	[GCC_PCIE1_AXI_M_ARES] = { 0x29038, 2 },
	[GCC_PCIE1_AXI_S_ARES] = { 0x29040, 2 },
	[GCC_PCIE1_AXI_S_BRIDGE_ARES] = { 0x29048, 2} ,
	[GCC_PCIE1_PIPE_ARES] = { 0x29068, 2 },
	[GCC_PCIE1_AUX_ARES] = { 0x29074, 2 },
	[GCC_PCIE2_AHB_ARES] = { 0x2a030, 2 },
	[GCC_PCIE2_AXI_M_ARES] = { 0x2a038, 2 },
	[GCC_PCIE2_AXI_S_ARES] = { 0x2a040, 2 },
	[GCC_PCIE2_AXI_S_BRIDGE_ARES] = { 0x2a048, 2 },
	[GCC_PCIE2_PIPE_ARES] = { 0x2a068, 2 },
	[GCC_PCIE2_AUX_ARES] = { 0x2a078, 2 },
	[GCC_PCIE3_AHB_ARES] = { 0x2b030, 2 },
	[GCC_PCIE3_AXI_M_ARES] = { 0x2b038, 2 },
	[GCC_PCIE3_AXI_S_ARES] = { 0x2b040, 2 },
	[GCC_PCIE3_AXI_S_BRIDGE_ARES] = { 0x2b048, 2 },
	[GCC_PCIE3_PIPE_ARES] = { 0x2b068, 2 },
	[GCC_PCIE3_AUX_ARES] = { 0x2b07C, 2 },
	[GCC_USB0_MASTER_ARES] = { 0x2c044, 2 },
	[GCC_USB0_AUX_ARES] = { 0x2c04c, 2 },
	[GCC_USB0_MOCK_UTMI_ARES] = { 0x2c050, 2 },
	[GCC_USB0_PIPE_ARES] = { 0x2c054, 2 },
	[GCC_USB0_SLEEP_ARES] = { 0x2c058, 2 },
	[GCC_USB0_PHY_CFG_AHB_ARES] = { 0x2c05c, 2 },
	[GCC_QDSS_AT_ARES] = { 0x2d034, 2 },
	[GCC_QDSS_STM_ARES] = { 0x2d03C, 2 },
	[GCC_QDSS_TRACECLKIN_ARES] = { 0x2d040, 2 },
	[GCC_QDSS_TSCTR_DIV2_ARES] = { 0x2d044, 2 },
	[GCC_QDSS_TSCTR_DIV3_ARES] = { 0x2d048, 2 },
	[GCC_QDSS_TSCTR_DIV4_ARES] = { 0x2d04c, 2 },
	[GCC_QDSS_TSCTR_DIV8_ARES] = { 0x2d050, 2 },
	[GCC_QDSS_TSCTR_DIV16_ARES] = { 0x2d054, 2 },
	[GCC_QDSS_DAP_ARES] = { 0x2d058, 2 },
	[GCC_QDSS_APB2JTAG_ARES] = { 0x2d05c, 2 },
	[GCC_QDSS_ETR_USB_ARES] = { 0x2d060, 2 },
	[GCC_QDSS_DAP_AHB_ARES] = { 0x2d064, 2 },
	[GCC_QDSS_CFG_AHB_ARES] = { 0x2d068, 2 },
	[GCC_QDSS_EUD_AT_ARES] = { 0x2d06c, 2 },
	[GCC_QDSS_TS_ARES] = { 0x2d078, 2 },
	[GCC_QDSS_USB_ARES] = { 0x2d07c, 2 },
	[GCC_SYS_NOC_AXI_ARES] = { 0x2e01c, 2 },
	[GCC_SNOC_QOSGEN_EXTREF_ARES] = { 0x2e020, 2 },
	[GCC_CNOC_LPASS_CFG_ARES] = { 0x2e028, 2 },
	[GCC_SYS_NOC_AT_ARES] = { 0x2e038, 2 },
	[GCC_SNOC_PCNOC_AHB_ARES] = { 0x2e03c, 2 },
	[GCC_SNOC_TME_ARES] = { 0x2e05c, 2 },
	[GCC_SNOC_XO_DCD_ARES] = { 0x2e060, 2 },
	[GCC_SNOC_TS_ARES] = { 0x2e068, 2 },
	[GCC_ANOC0_AXI_ARES] = { 0x2e078, 2 },
	[GCC_ANOC_PCIE0_1LANE_M_ARES] = { 0x2e07c, 2 },
	[GCC_ANOC_PCIE2_2LANE_M_ARES] = { 0x2e080, 2 },
	[GCC_ANOC_PCIE1_1LANE_M_ARES] = { 0x2e084, 2 },
	[GCC_ANOC_PCIE3_2LANE_M_ARES] = { 0x2e090, 2 },
	[GCC_ANOC_PCNOC_AHB_ARES] = { 0x2e094, 2 },
	[GCC_ANOC_QOSGEN_EXTREF_ARES] = { 0x2e098, 2 },
	[GCC_ANOC_XO_DCD_ARES] = { 0x2e09C, 2 },
	[GCC_SNOC_XO_DBG_ARES] = { 0x2e0a0, 2 },
	[GCC_AGGRNOC_ATB_ARES] = { 0x2e0ac, 2 },
	[GCC_AGGRNOC_TS_ARES] = { 0x2e0b0, 2 },
	[GCC_USB0_EUD_AT_ARES] = { 0x30004, 2 },
	[GCC_PCNOC_TIC_ARES] = { 0x31014, 2 },
	[GCC_PCNOC_AHB_ARES] = { 0x31018, 2 },
	[GCC_PCNOC_XO_DBG_ARES] = { 0x3101c, 2 },
	[GCC_SNOC_LPASS_ARES] = { 0x31020, 2 },
	[GCC_PCNOC_AT_ARES] = { 0x31024, 2 },
	[GCC_PCNOC_XO_DCD_ARES] = { 0x31028, 2 },
	[GCC_PCNOC_TS_ARES] = { 0x3102c, 2 },
	[GCC_PCNOC_BUS_TIMEOUT0_AHB_ARES] = { 0x31034, 2 },
	[GCC_PCNOC_BUS_TIMEOUT1_AHB_ARES] = { 0x3103c, 2 },
	[GCC_PCNOC_BUS_TIMEOUT2_AHB_ARES] = { 0x31044, 2 },
	[GCC_PCNOC_BUS_TIMEOUT3_AHB_ARES] = { 0x3104c, 2 },
	[GCC_PCNOC_BUS_TIMEOUT4_AHB_ARES] = { 0x31054, 2 },
	[GCC_PCNOC_BUS_TIMEOUT5_AHB_ARES] = { 0x3105c, 2 },
	[GCC_PCNOC_BUS_TIMEOUT6_AHB_ARES] = { 0x31064, 2 },
	[GCC_PCNOC_BUS_TIMEOUT7_AHB_ARES] = { 0x3106c, 2 },
	[GCC_Q6_AXIM_RESET] = { 0x2506c, 0 },
	[GCC_Q6_AXIS_RESET] = { 0x2506c, 1 },
	[GCC_Q6_AHB_S_RESET] = { 0x2506c, 2 },
	[GCC_Q6_AHB_RESET] = { 0x2506c, 3 },
	[GCC_Q6SS_DBG_RESET] = { 0x2506c, 4 },
	[GCC_WCSS_ECAHB_RESET] = { 0x25070, 0 },
	[GCC_WCSS_DBG_BDG_RESET] = { 0x25070, 1 },
	[GCC_WCSS_DBG_RESET] = { 0x25070, 2 },
	[GCC_WCSS_AXI_M_RESET] = { 0x25070, 3 },
	[GCC_WCSS_AHB_S_RESET] = { 0x25070, 4 },
	[GCC_WCSS_ACMT_RESET] = { 0x25070, 5 },
	[GCC_WCSSAON_RESET] = { 0x25074, 0 },
	[GCC_PCIE0_PIPE_RESET] = { 0x28058, 0 },
	[GCC_PCIE0_CORE_STICKY_RESET] = { 0x28058, 1 },
	[GCC_PCIE0_AXI_S_STICKY_RESET] = { 0x28058, 2 },
	[GCC_PCIE0_AXI_S_RESET] = { 0x28058, 3 },
	[GCC_PCIE0_AXI_M_STICKY_RESET] = { 0x28058, 4 },
	[GCC_PCIE0_AXI_M_RESET] = { 0x28058, 5 },
	[GCC_PCIE0_AUX_RESET] = { 0x28058, 6 },
	[GCC_PCIE0_AHB_RESET] = { 0x28058, 7 },
	[GCC_PCIE1_PIPE_RESET] = { 0x29058, 0 },
	[GCC_PCIE1_CORE_STICKY_RESET] = { 0x29058, 1 },
	[GCC_PCIE1_AXI_S_STICKY_RESET] = { 0x29058, 2 },
	[GCC_PCIE1_AXI_S_RESET] = { 0x29058, 3 },
	[GCC_PCIE1_AXI_M_STICKY_RESET] = { 0x29058, 4 },
	[GCC_PCIE1_AXI_M_RESET] = { 0x29058, 5 },
	[GCC_PCIE1_AUX_RESET] = { 0x29058, 6 },
	[GCC_PCIE1_AHB_RESET] = { 0x29058, 7 },
	[GCC_PCIE2_PIPE_RESET] = { 0x2a058, 0 },
	[GCC_PCIE2_CORE_STICKY_RESET] = { 0x2a058, 1 },
	[GCC_PCIE2_AXI_S_STICKY_RESET] = { 0x2a058, 2 },
	[GCC_PCIE2_AXI_S_RESET] = { 0x2a058, 3 },
	[GCC_PCIE2_AXI_M_STICKY_RESET] = { 0x2a058, 4 },
	[GCC_PCIE2_AXI_M_RESET] = { 0x2a058, 5 },
	[GCC_PCIE2_AUX_RESET] = { 0x2a058, 6 },
	[GCC_PCIE2_AHB_RESET] = { 0x2a058, 7 },
	[GCC_PCIE3_PIPE_RESET] = { 0x2b058, 0 },
	[GCC_PCIE3_CORE_STICKY_RESET] = { 0x2b058, 1 },
	[GCC_PCIE3_AXI_S_STICKY_RESET] = { 0x2b058, 2 },
	[GCC_PCIE3_AXI_S_RESET] = { 0x2b058, 3 },
	[GCC_PCIE3_AXI_M_STICKY_RESET] = { 0x2b058, 4 },
	[GCC_PCIE3_AXI_M_RESET] = { 0x2b058, 5 },
	[GCC_PCIE3_AUX_RESET] = { 0x2b058, 6 },
	[GCC_PCIE3_AHB_RESET] = { 0x2b058, 7 },
	[GCC_NSS_PARTIAL_RESET] = { 0x17078, 0 },

};

static const struct of_device_id gcc_devsoc_match_table[] = {
        { .compatible = "qcom,devsoc-gcc" },
        { }
};
MODULE_DEVICE_TABLE(of, gcc_devsoc_match_table);

static const struct regmap_config gcc_devsoc_regmap_config = {
	.reg_bits       = 32,
	.reg_stride     = 4,
	.val_bits       = 32,
	.max_register   = 0x841f0,
	.fast_io        = true,
};

static const struct qcom_cc_desc gcc_devsoc_dummy_desc = {
	.config = &gcc_devsoc_regmap_config,
	.clks = gcc_devsoc_dummy_clks,
	.num_clks = ARRAY_SIZE(gcc_devsoc_dummy_clks),
	.resets = gcc_devsoc_resets,
	.num_resets = ARRAY_SIZE(gcc_devsoc_resets),
};

static int gcc_devsoc_probe(struct platform_device *pdev)
{
	return qcom_cc_probe(pdev, &gcc_devsoc_dummy_desc);
}

static struct platform_driver gcc_devsoc_driver = {
	.probe = gcc_devsoc_probe,
	.driver = {
		.name   = "qcom,gcc-devsoc",
		.of_match_table = gcc_devsoc_match_table,
	},
};

static int __init gcc_devsoc_init(void)
{
	return platform_driver_register(&gcc_devsoc_driver);
}
core_initcall(gcc_devsoc_init);

static void __exit gcc_devsoc_exit(void)
{
	platform_driver_unregister(&gcc_devsoc_driver);
}
module_exit(gcc_devsoc_exit);

MODULE_DESCRIPTION("Qualcomm Technologies, Inc. GCC DEVSOC Driver");
MODULE_LICENSE("GPLv2");
