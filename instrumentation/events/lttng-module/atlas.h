#undef TRACE_SYSTEM
#define TRACE_SYSTEM atlas 

#if !defined(LTTNG_TRACE_ATLAS_H) || defined(TRACE_HEADER_MULTI_READ)
#define LTTNG_TRACE_ATLAS_H

#ifndef __LTTNG_ATLAS_HAVE_SCHED_H
#define __LTTNG_ATLAS_HAVE_SCHED_H
#include "sched/sched.h"
#include <asm/tsc.h>
#endif

#include "../../../probes/lttng-tracepoint-event.h"

LTTNG_TRACEPOINT_EVENT_CLASS(atlas_job_template,
	TP_PROTO(struct atlas_job * j),
	TP_ARGS(j),
	TP_FIELDS(
		ctf_array_text(	char,	comm,		j->tsk->comm, TASK_COMM_LEN)
		ctf_integer(	pid_t,	tid,		task_pid_nr_ns(j->tsk, task_active_pid_ns(j->tsk)))
		ctf_integer(	int,	task_policy,	j->tsk->policy)
		ctf_integer(	int,	job_policy,	j->tree - j->tree->rq->atlas.jobs)
		ctf_integer(	u64,	id,		j->id)
		ctf_integer(	s64,	now,		ktime_to_ns(ktime_get()))
		ctf_integer(	s64,	sbegin,		ktime_to_ns(ktime_sub(j->deadline, ktime_sub(j->sexectime, j->rexectime))))
		ctf_integer(	s64,	sdeadline,	ktime_to_ns(j->sdeadline))
		ctf_integer(	s64,	deadline,	ktime_to_ns(j->deadline))
		ctf_integer(	s64,	rexectime,	ktime_to_ns(j->rexectime))
		ctf_integer(	s64,	sexectime,	ktime_to_ns(j->sexectime))
		ctf_integer(	s64,	exectime,	ktime_to_ns(j->exectime))
	)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_submit,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_done,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))

LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_update,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_updated,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_remove,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_migrate,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_migrated,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))

LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_start,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_soft_miss,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_hard_miss,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_select,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_deselect,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_job_template, atlas_job_slack,
                                TP_PROTO(struct atlas_job *j), TP_ARGS(j))

LTTNG_TRACEPOINT_EVENT_CLASS(atlas_task_template,
	TP_PROTO(struct task_struct * p),
	TP_ARGS(p),
	TP_FIELDS(
		ctf_array_text(	char,	comm,		p->comm, TASK_COMM_LEN)
		ctf_integer(	pid_t,	tid,		task_pid_nr_ns(p, task_active_pid_ns(p)))
		ctf_integer(	int,	task_policy,	p->policy)
	)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_task_template, atlas_task_sleep,
                                TP_PROTO(struct task_struct *p), TP_ARGS(p))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_task_template, atlas_task_wakeup,
                                TP_PROTO(struct task_struct *p), TP_ARGS(p))

LTTNG_TRACEPOINT_EVENT_CLASS(atlas_task_migrate_template,
	TP_PROTO(struct task_struct * p, int other_cpu),
	TP_ARGS(p, other_cpu),
	TP_FIELDS(
		ctf_array_text(	char,	comm,		p->comm, TASK_COMM_LEN)
		ctf_integer(	pid_t,	tid,		task_pid_nr_ns(p, task_active_pid_ns(p)))
		ctf_integer(	int,	task_policy,	p->policy)
		ctf_integer(	int,	other_cpu,	other_cpu)
	)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_task_migrate_template, atlas_task_migrate,
                                TP_PROTO(struct task_struct *p, int other_cpu),
                                TP_ARGS(p, other_cpu))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_task_migrate_template,
                                atlas_task_overload_pulled,
                                TP_PROTO(struct task_struct *p, int other_cpu),
                                TP_ARGS(p, other_cpu))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_task_migrate_template,
                                atlas_task_idle_balanced,
                                TP_PROTO(struct task_struct *p, int other_cpu),
                                TP_ARGS(p, other_cpu))

LTTNG_TRACEPOINT_EVENT_CLASS(atlas_probe_template,
	TP_PROTO(void * dummy),
	TP_ARGS(dummy),
	TP_FIELDS(
		ctf_integer(s64, now, ktime_to_ns(ktime_get()))
		ctf_integer(u64, cycles, get_cycles())
	)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_probe_template, atlas_probe_detach,
                                TP_PROTO(void *p), TP_ARGS(p))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_probe_template, atlas_probe_detached,
                                TP_PROTO(void *p), TP_ARGS(p))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_probe_template, atlas_probe_attach,
                                TP_PROTO(void *p), TP_ARGS(p))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_probe_template, atlas_probe_attached,
                                TP_PROTO(void *p), TP_ARGS(p))

LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_probe_template,
                                atlas_probe_overload_notify, TP_PROTO(void *p),
                                TP_ARGS(p))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_probe_template,
                                atlas_probe_overload_notified,
                                TP_PROTO(void *p), TP_ARGS(p))

LTTNG_TRACEPOINT_EVENT_CLASS(atlas_ipi_template,
	TP_PROTO(int cpu),
	TP_ARGS(cpu),
	TP_FIELDS(
		ctf_integer(s64, now, ktime_to_ns(ktime_get()))
		ctf_integer(u64, cycles, get_cycles())
		ctf_integer(int, cpu, cpu)
	)
)

LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_ipi_template, atlas_ipi_send,
                                TP_PROTO(int cpu), TP_ARGS(cpu))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_ipi_template, atlas_ipi_recv,
                                TP_PROTO(int cpu), TP_ARGS(cpu))
LTTNG_TRACEPOINT_EVENT_INSTANCE(atlas_ipi_template, atlas_ipi_handle,
                                TP_PROTO(int cpu), TP_ARGS(cpu))

#endif /* LTTNG_TRACE_ATLAS_H */

/* This part must be outside protection */
#include "../../../probes/define_trace.h"

