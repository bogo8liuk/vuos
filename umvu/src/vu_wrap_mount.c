#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <sys/syscall.h>

#include <vu_log.h>
#include <umvu_peekpoke.h>
#include <hashtable.h>
#include <xcommon.h>
//#include <linux_32_64.h>
#include <arch_table.h>
#include <syscall_defs.h>
#include <vu_execute.h>
#include <service.h>
//#include <vu_tmpdir.h>
//#include <vu_fs.h>
#include <path_utils.h>
//#include <vu_file_table.h>
//#include <vu_fd_table.h>


void wi_mount(struct vuht_entry_t *ht, struct syscall_descriptor_t *sd) {
  int nested = sd->extra->nested;
  if (ht && !nested) {
		/* standard args */
		int ret_value;
		/* args */
		char *source = umvu_peekdup_path(sd->syscall_args[0]);
		char *target = sd->extra->path;
		char *filesystemtype = umvu_peekdup_path(sd->syscall_args[2]);
		unsigned long mountflags = sd->syscall_args[3];
		char *data = umvu_peekdup_path(sd->syscall_args[4]);
		/* fetch args */
		/* call */
		sd->action = SKIPIT;
		ret_value = service_syscall(ht, __VU_mount)(source, target, filesystemtype, mountflags, data);
		if (ret_value < 0) 
      sd->ret_value = -errno;
		xfree(source);
		xfree(filesystemtype);
		xfree(data);
		/* store results */
    sd->ret_value = ret_value;
	}
}

void wi_umount2(struct vuht_entry_t *ht, struct syscall_descriptor_t *sd) {
  int nested = sd->extra->nested;
		printk("umount %s %p\n", sd->extra->path, ht);
  if (ht && !nested) {
		/* standard args */
		int syscall_number = sd->syscall_number;
    int ret_value;
    /* args */
		char *target = sd->extra->path;
    int flags;
    /* fetch args */
		switch (syscall_number) {
#ifdef __NR_umount
			case __NR_umount: flags = 0;
												break;
#endif
			case __NR_umount2: flags = sd->syscall_args[1];
												 break;
		}
    sd->action = SKIPIT;
    ret_value = service_syscall(ht, __VU_umount2)(target, flags);
    if (ret_value < 0)
      sd->ret_value = -errno;
		else
			sd->ret_value = ret_value;
  }
}
