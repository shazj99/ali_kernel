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

TRACE_EVENT(should_writeback_mem_cgroup_inode,
	TP_PROTO(struct inode *inode,
		 unsigned short css_id,
		 bool shared_inodes,
		 bool wb),

	TP_ARGS(inode, css_id, shared_inodes, wb),

	TP_STRUCT__entry(
		__field(unsigned long, ino)
		__field(unsigned short, inode_css_id)
		__field(unsigned short, css_id)
		__field(bool, shared_inodes)
		__field(bool, wb)
	),

	TP_fast_assign(
		__entry->ino = inode->i_ino;
		__entry->inode_css_id =
			inode->i_mapping ? inode->i_mapping->i_memcg : 0;
		__entry->css_id = css_id;
		__entry->shared_inodes = shared_inodes;
		__entry->wb = wb;
	),

	TP_printk("ino=%ld inode_css_id=%d css_id=%d shared_inodes=%d wb=%d",
		  __entry->ino,
		  __entry->inode_css_id,
		  __entry->css_id,
		  __entry->shared_inodes,
		  __entry->wb)
)

TRACE_EVENT(mem_cgroups_over_bground_dirty_thresh,
	TP_PROTO(bool over_limit,
		 unsigned short first_id),

	TP_ARGS(over_limit, first_id),

	TP_STRUCT__entry(
		__field(bool, over_limit)
		__field(unsigned short, first_id)
	),

	TP_fast_assign(
		__entry->over_limit = over_limit;
		__entry->first_id = first_id;
	),

	TP_printk("over_limit=%d first_css_id=%d", __entry->over_limit,
		  __entry->first_id)
)

DECLARE_EVENT_CLASS(mem_cgroup_consider_writeback,
	TP_PROTO(unsigned short css_id,
		 struct backing_dev_info *bdi,
		 unsigned long nr_reclaimable,
		 unsigned long thresh,
		 bool over_limit),

	TP_ARGS(css_id, bdi, nr_reclaimable, thresh, over_limit),

	TP_STRUCT__entry(
		__field(unsigned short, css_id)
		__field(struct backing_dev_info *, bdi)
		__field(unsigned long, nr_reclaimable)
		__field(unsigned long, thresh)
		__field(bool, over_limit)
	),

	TP_fast_assign(
		__entry->css_id = css_id;
		__entry->bdi = bdi;
		__entry->nr_reclaimable = nr_reclaimable;
		__entry->thresh = thresh;
		__entry->over_limit = over_limit;
	),

	TP_printk("css_id=%d bdi=%p nr_reclaimable=%ld thresh=%ld "
		  "over_limit=%d", __entry->css_id, __entry->bdi,
		  __entry->nr_reclaimable, __entry->thresh, __entry->over_limit)
)

#define DEFINE_MEM_CGROUP_CONSIDER_WRITEBACK_EVENT(name) \
DEFINE_EVENT(mem_cgroup_consider_writeback, name, \
	TP_PROTO(unsigned short id, \
		 struct backing_dev_info *bdi, \
		 unsigned long nr_reclaimable, \
		 unsigned long thresh, \
		 bool over_limit), \
	TP_ARGS(id, bdi, nr_reclaimable, thresh, over_limit) \
)

DEFINE_MEM_CGROUP_CONSIDER_WRITEBACK_EVENT(mem_cgroup_consider_bg_writeback);
DEFINE_MEM_CGROUP_CONSIDER_WRITEBACK_EVENT(mem_cgroup_consider_fg_writeback);

TRACE_EVENT(mem_cgroup_fg_writeback,
	TP_PROTO(unsigned long write_chunk,
		 long nr_written,
		 unsigned short css_id,
		 bool shared_inodes),

	TP_ARGS(write_chunk, nr_written, css_id, shared_inodes),

	TP_STRUCT__entry(
		__field(unsigned long, write_chunk)
		__field(long, nr_written)
		__field(unsigned short, css_id)
		__field(bool, shared_inodes)
	),

	TP_fast_assign(
		__entry->write_chunk = write_chunk;
		__entry->nr_written = nr_written;
		__entry->css_id = css_id;
		__entry->shared_inodes = shared_inodes;
	),

	TP_printk("css_id=%d write_chunk=%ld nr_written=%ld shared_inodes=%d",
		  __entry->css_id,
		  __entry->write_chunk,
		  __entry->nr_written,
		  __entry->shared_inodes)
)

TRACE_EVENT(mem_cgroup_enable_shared_writeback,
	TP_PROTO(unsigned short css_id),

	TP_ARGS(css_id),

	TP_STRUCT__entry(
		__field(unsigned short, css_id)
		),

	TP_fast_assign(
		__entry->css_id = css_id;
		),

	TP_printk("enabling shared writeback for memcg %d", __entry->css_id)
)

#endif /* _TRACE_MEMCONTROL_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
