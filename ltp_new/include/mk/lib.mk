#
#    library include Makefile.
#
#    Copyright (c) Linux Test Project, 2009-2020
#    Copyright (c) Cisco Systems Inc., 2009
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License along
#    with this program; if not, write to the Free Software Foundation, Inc.,
#    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#
# Ngie Cooper, July 2009
#
# Copyright (C) Cyril Hrubis <chrubis@suse.cz> 2012
#

# Makefile to include for libraries.

include $(top_srcdir)/include/mk/env_pre.mk
include $(top_srcdir)/include/mk/sparse.mk

INSTALL_DIR	:= $(libdir)

# An extension of generic_leaf_target, strictly for libraries.
.PHONY: install_headers

ifndef LIB
ifndef INTERNAL_LIB
$(error You must define LIB or INTERNAL_LIB when including this Makefile)
endif
endif

install_headers: $(addprefix $(DESTDIR)/$(includedir)/,$(notdir $(HEADER_FILES)))

INSTALL_MODE	?= 00664

# Hide the LIB target for internal libs on install
ifneq ($(MAKECMDGOALS),install)
LIB ?= $(INTERNAL_LIB)
endif

MAKE_TARGETS	+= $(LIB)

LIBSRCS		?= $(wildcard $(abs_srcdir)/*.c)
LIBSRCS		:= $(sort $(LIBSRCS))
LIBSRCS		:= $(abspath $(LIBSRCS))
LIBSRCS		:= $(subst $(abs_srcdir)/,,$(wildcard $(LIBSRCS)))
LIBSRCS		:= $(filter-out $(FILTER_OUT_LIBSRCS),$(LIBSRCS))

LIBOBJS		:= $(LIBSRCS:.c=.o)

CHECK_TARGETS	:= $(addprefix check-,$(notdir $(LIBSRCS:.c=)))

$(LIB): $(notdir $(LIBOBJS))
	@if [ -z "$(strip $^)" ] ; then \
		echo "Cowardly refusing to create empty archive"; \
		exit 1; \
	fi
ifdef VERBOSE
	$(if $(AR),$(AR),ar) -rc "$@" $^
	$(if $(RANLIB),$(RANLIB),ranlib) "$@"
else
	@echo "AR $@"
	@$(if $(AR),$(AR),ar) -rc "$@" $^
	@echo "RANLIB $@"
	@$(if $(RANLIB),$(RANLIB),ranlib) "$@"
endif

include $(top_srcdir)/include/mk/generic_leaf_target.mk
