/* SPDX-License-Identifier: GPL-2.0-only */

/*
 * CFR enums and structs which are used to control SoC settings.
 */

#ifndef _TIGERLAKE_CFR_H_
#define _TIGERLAKE_CFR_H_

#include <drivers/option/cfr_frontend.h>
#include <soc/soc_chip.h>

/* FSP hyperthreading */
static const struct sm_object hyper_threading = SM_DECLARE_ENUM({
	.opt_name	= "hyper_threading",
	.ui_name	= "Hyper-Threading",
	.ui_helptext	= "Enable or disable Hyper-Threading",
	.default_value	= CONFIG(FSP_HYPERTHREADING),
	.values		= (const struct sm_enum_value[]) {
				{ "Disabled",		0	},
				{ "Enabled",		1	},
				SM_ENUM_VALUE_END		},
});

/* IGD Aperture Size */
static const struct sm_object igd_aperture = SM_DECLARE_ENUM({
	.opt_name	= "igd_aperture_size",
	.ui_name	= "IGD Aperture Size",
	.ui_helptext	= "Select the Aperture Size",
	.default_value	= IGD_AP_SZ_256MB,
	.values		= (const struct sm_enum_value[]) {
				{ " 128 MB",		IGD_AP_SZ_128MB		},
				{ " 256 MB",		IGD_AP_SZ_256MB		},
#if CONFIG(ALWAYS_ALLOW_ABOVE_4G_ALLOCATION)
				{ " 512 MB (4G MMIO)",	IGD_AP_SZ_4G_512MB	},
				{ "1024 MB (4G MMIO)",	IGD_AP_SZ_4G_1024MB	},
				{ "2048 MB (4G MMIO)",	IGD_AP_SZ_4G_2048MB	},
#else
				{ " 512 MB",		IGD_AP_SZ_512MB		},
#endif
				SM_ENUM_VALUE_END				},
});

/* IGD DVMT pre-allocated memory */
static const struct sm_object igd_dvmt = SM_DECLARE_ENUM({
	.opt_name	= "igd_dvmt_prealloc",
	.ui_name	= "IGD DVMT Size",
	.ui_helptext	= "Size of memory preallocated for internal graphics",
	.default_value	= IGD_SM_60MB,
	.values		= (const struct sm_enum_value[]) {
				{ " 32 MB",		IGD_SM_32MB	},
				{ " 60 MB",		IGD_SM_60MB	},
				{ " 64 MB",		IGD_SM_64MB	},
				{ " 96 MB",		IGD_SM_96MB	},
				{ "128 MB",		IGD_SM_128MB	},
				{ "160 MB",		IGD_SM_160MB	},
				SM_ENUM_VALUE_END			},
});

/* Legacy 8254 Timer */
static const struct sm_object legacy_8254_timer = SM_DECLARE_ENUM({
	.opt_name	= "legacy_8254_timer",
	.ui_name	= "Legacy 8254 Timer",
	.ui_helptext	= "Enable the legacy 8254 timer by disabling clock gating.",
	.default_value	= 0,
	.values		= (const struct sm_enum_value[]) {
				{ "Disabled",		0	},
				{ "Enabled",		1	},
				SM_ENUM_VALUE_END		},
});

/* S0ix Enable */
static const struct sm_object s0ix_enable = SM_DECLARE_ENUM({
	.opt_name	= "s0ix_enable",
	.ui_name	= "Modern Standby (S0ix)",
	.ui_helptext	= "Enabled: use Modern Standby / S0ix. Disabled: use APCI S3 sleep",
	.default_value	= 1,
	.values		= (const struct sm_enum_value[]) {
				{ "Disabled",		0	},
				{ "Enabled",		1	},
				SM_ENUM_VALUE_END		},
});

/* VT-d */
static const struct sm_object vtd = SM_DECLARE_ENUM({
	.opt_name	= "vtd",
	.ui_name	= "VT-d",
	.ui_helptext	= "Enable or disable Intel VT-d (virtualization)",
	.default_value	= 1,
	.values		= (const struct sm_enum_value[]) {
				{ "Disabled",		0	},
				{ "Enabled",		1	},
				SM_ENUM_VALUE_END		},
});

#endif /* _TIGERLAKE_CFR_H_ */
