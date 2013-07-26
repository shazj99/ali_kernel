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

TRACE_EVENT(mem_cgroup_dirty_info,
	TP_PROTO(unsigned short css_id,
		 struct dirty_info *dirty_info),

	TP_ARGS(css_id, dirty_info),

	TP_STRUCT__entry(
		__field(unsigned short, css_id)
		__field(unsigned long, dirty_thresh)
		__field(unsigned long, background_thresh)
		__field(unsigned long, nr_file_dirty)
		__field(unsigned long, nr_writeback)
		__field(unsigned long, nr_unstable_nfs)
		),

	TP_fast_assign(
		__entry->css_id = css_id;
		__entry->dirty_thresh = dirty_info->dirty_thresh;
		__entry->background_thresh = dirty_info->background_thresh;
		__entry->nr_file_dirty = dirty_info->nr_file_dirty;
		__entry->nr_writeback = dirty_info->nr_writeback;
		__entry->nr_unstable_nfs = dirty_info->nr_unstable_nfs;
		),

	TP_printk("css_id=%d thresh=%ld bg_thresh=%ld dirty=%ld wb=%ld "
		  "unstable_nfs=%ld",
		  __entry->css_id,
		  __entry->dirty_thresh,
		  __entry->background_thresh,
		  __entry->nr_file_dirty,
		  __entry->nr_writeback,
		  __entry->nr_unstable_nfs)
)

#endif /* _TRACE_MEMCONTROL_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
