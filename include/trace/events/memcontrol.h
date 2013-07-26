#undef TRACE_SYSTEM
#define TRACE_SYSTEM memcontrol

#if !defined(_TRACE_MEMCONTROL_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_MEMCONTROL_H

#include <linux/types.h>
#include <linux/tracepoint.h>

TRACE_EVENT(mem_cgroup_mark_inode_dirty,
	TP_PROTO(struct inode *inode),

	TP_ARGS(inode),

	TP_STRUCT__entry(
		__field(unsigned long, ino)
		__field(unsigned short, css_id)
		),

	TP_fast_assign(
		__entry->ino = inode->i_ino;
		__entry->css_id =
			inode->i_mapping ? inode->i_mapping->i_memcg : 0;
		),

	TP_printk("ino=%ld css_id=%d", __entry->ino, __entry->css_id)
)

#endif /* _TRACE_MEMCONTROL_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
