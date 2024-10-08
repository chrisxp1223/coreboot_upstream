/* SPDX-License-Identifier: GPL-2.0-only */

#include <intelblocks/systemagent.h>
#include <soc/iomap.h>
#include <soc/romstage.h>
#include <soc/systemagent.h>

void systemagent_early_init(void)
{
	static const struct sa_mmio_descriptor soc_fixed_pci_resources[] = {
		{ MCHBAR, MCH_BASE_ADDRESS, MCH_BASE_SIZE, "MCHBAR" },
		{ SAFBAR, SAF_BASE_ADDRESS, SAF_BASE_SIZE, "SAFBAR" },
		{ EPBAR, EP_BASE_ADDRESS, EP_BASE_SIZE, "EPBAR" },
	};

	static const struct sa_mmio_descriptor soc_fixed_mch_resources[] = {
		{ REGBAR, REG_BASE_ADDRESS, REG_BASE_SIZE, "REGBAR" },
	};

	/* Set Fixed MMIO address into PCI configuration space */
	sa_set_pci_bar(soc_fixed_pci_resources,
		       ARRAY_SIZE(soc_fixed_pci_resources));
	/* Set Fixed MMIO address into MCH base address */
	sa_set_mch_bar(soc_fixed_mch_resources,
		       ARRAY_SIZE(soc_fixed_mch_resources));
	/* Enable PAM registers */
	enable_pam_region();
}
