mod_removal_space.la: mod_removal_space.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_removal_space.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_removal_space.la
