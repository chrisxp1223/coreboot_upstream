# SPDX-License-Identifier: GPL-2.0-only

ifeq ($(CONFIG_NORTHBRIDGE_INTEL_HASWELL),y)

bootblock-y += bootblock.c

ramstage-y += memmap.c
ramstage-y += northbridge.c
ramstage-y += pcie.c
ramstage-y += gma.c

ramstage-y += acpi.c
ramstage-y += minihd.c

romstage-y += memmap.c
romstage-y += romstage.c
romstage-y += early_init.c
romstage-y += report_platform.c
romstage-y += raminit_shared.c

postcar-y += memmap.c

ifeq ($(CONFIG_USE_NATIVE_RAMINIT),y)
romstage-y += early_dmi.c early_pcie.c vcu_mailbox.c
subdirs-y  += native_raminit

else
ifeq ($(CONFIG_USE_BROADWELL_MRC),y)
romstage-y += early_dmi.c early_pcie.c vcu_mailbox.c
subdirs-y  += broadwell_mrc

else
subdirs-y  += haswell_mrc
endif
endif

endif
