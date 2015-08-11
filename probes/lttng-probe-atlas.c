/*
 * probes/lttng-probe-atlas.c
 *
 * LTTng ATLAS probes.
 *
 * Copyright (C) 2010-2012 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 * Copyright (C) 2015 Hannes Weisbach <hannes.weisbach@tu-dresden.de> 
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; only
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <linux/module.h>
#include "../lttng-tracer.h"

/*
 * Create the tracepoint static inlines from the kernel to validate that our
 * trace event macros match the kernel we run on.
 * File is in <linux>/kernel/sched/. Include <linux>/kernel, to disambiguate
 * <linux>/kernel/sched/sched.h against <linux>/include/sched.h
 */
#include "sched/atlas_trace.h"
#include "../wrapper/tracepoint.h"

/*
 * Create LTTng tracepoint probes.
 */
#define LTTNG_PACKAGE_BUILD
#define CREATE_TRACE_POINTS
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH ../instrumentation/events/lttng-module
#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_FILE atlas

#include "../instrumentation/events/lttng-module/atlas.h"

MODULE_LICENSE("GPL and additional rights");
MODULE_AUTHOR("Hannes Weisbach <hannes.weisbach@tu-dresden.de");
MODULE_DESCRIPTION("LTTng ATLAS probes");
MODULE_VERSION(__stringify(LTTNG_MODULES_MAJOR_VERSION) "."
	__stringify(LTTNG_MODULES_MINOR_VERSION) "."
	__stringify(LTTNG_MODULES_PATCHLEVEL_VERSION)
	LTTNG_MODULES_EXTRAVERSION);
