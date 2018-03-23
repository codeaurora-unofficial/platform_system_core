/*
 * Copyright (C) 2007 The Android Open Source Project
 * Copyright (c) 2009,2015 The Linux Foundation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This file is used to define the properties of the filesystem
** images generated by build tools (mkbootfs and mkyaffs2image) and
** by the device side of adb.
*/

#ifndef _ANDROID_FILESYSTEM_CONFIG_H_
#define _ANDROID_FILESYSTEM_CONFIG_H_

#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

/* This is the master Users and Groups config for the platform.
** DO NOT EVER RENUMBER.
*/

#define AID_ROOT             0  /* traditional unix root user */
#define AID_DAEMON           1
#define AID_BIN              2
#define AID_SYS              3
#define AID_ADM              4
#define AID_TTY              5
#define AID_DISK             6
#define AID_KMEM            15
#define AID_WWWDATA         33
#define AID_BACKUP          34
#define AID_SHADOW          42
#define AID_UTMP            43
#define AID_DIAG            53
#define AID_SDCARD        1015
#define AID_REBOOTERS     1301
#define AID_NOBODY       65534

#if !defined(EXCLUDE_FS_CONFIG_STRUCTURES)
struct android_id_info {
    const char *name;
    unsigned aid;
};

static const struct android_id_info android_ids[] = {
    { "root",      AID_ROOT, },
    { "daemon",    AID_DAEMON, },
    { "bin",       AID_BIN, },
    { "sys",       AID_SYS, },
    { "adm",       AID_ADM, },
    { "tty",       AID_TTY, },
    { "disk",      AID_DISK, },
    { "kmem",      AID_KMEM, },
    { "www-data",  AID_WWWDATA, },
    { "backup",    AID_BACKUP, },
    { "shadow",    AID_SHADOW, },
    { "utmp",      AID_UTMP, },
    { "diag",      AID_DIAG, },
    { "sdcard",    AID_SDCARD, },
    { "rebooters", AID_REBOOTERS, },
    { "nobody",    AID_NOBODY, },
};

#define android_id_count \
    (sizeof(android_ids) / sizeof(android_ids[0]))

struct fs_path_config {
    unsigned mode;
    unsigned uid;
    unsigned gid;

    const char *prefix;
};

/* system appears as rootfs / on MDM */
/* userdata appears as /data on MDM   */

/* Rules for directories.
** These rules are applied based on "first match", so they
** should start with the most specific path and work their
** way up to the root.
*/

static struct fs_path_config android_dirs[] = {
    { 00770, AID_WWWDATA,   AID_WWWDATA,   "system/WEBSERVER" },
    { 00770, AID_WWWDATA,   AID_WWWDATA,   "system/www" },
    { 01755, AID_ROOT,      AID_ROOT,      "system/tmp" },
    { 00755, AID_ROOT,      AID_ROOT,      0 },
};

/* Rules for files.
** These rules are applied based on "first match", so they
** should start with the most specific path and work their
** way up to the root. Prefixes ending in * denotes wildcard
** and will allow partial matches.
*/
static struct fs_path_config android_files[] = {
    /* rootfs permissions */
    { 00755, AID_ROOT,      AID_ROOT,      "system/bin/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/sbin/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/lib/*" },

    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/rc.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/rc0.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/rc1.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/rc2.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/rc3.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/rc4.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/rc5.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/rc6.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/rcS.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/avahi/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/disconnect" },
    { 00600, AID_ROOT,      AID_ROOT,      "system/etc/group-" },
    { 00600, AID_ROOT,      AID_ROOT,      "system/etc/gshadow" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/init.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/mdev/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/network/if-down-up.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/network/if-post-down.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/network/if-pre-up.d/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/network/if-up.d/*" },
    { 00600, AID_ROOT,      AID_ROOT,      "system/etc/passwd-" },
    { 00600, AID_ROOT,      AID_ROOT,      "system/etc/ppp/chap-secrets" },
    { 00600, AID_ROOT,      AID_ROOT,      "system/etc/ppp/pap-secrets" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/ppp/*" },
    { 00600, AID_ROOT,      AID_ROOT,      "system/etc/securetty" },
    { 00600, AID_ROOT,      AID_ROOT,      "system/etc/shadow" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/etc/udhcpc.d/*" },
    { 00644, AID_ROOT,      AID_ROOT,      "system/etc/*" },
    { 04755, AID_ROOT,      AID_ROOT,      "system/usr/bin/chage" },
    { 04755, AID_ROOT,      AID_ROOT,      "system/usr/bin/chfn.shadow" },
    { 04755, AID_ROOT,      AID_ROOT,      "system/usr/bin/chsh.shadow" },
    { 04755, AID_ROOT,      AID_ROOT,      "system/usr/bin/newgrp.shadow" },
    { 04755, AID_ROOT,      AID_ROOT,      "system/usr/bin/su" },
    { 04755, AID_ROOT,      AID_ROOT,      "system/usr/sbin/pppd" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/usr/bin/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/usr/sbin/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/usr/lib/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/usr/kernel-tests/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "system/usr/tests/*" },
    { 00644, AID_ROOT,      AID_ROOT,      "system/usr/*" },
    { 00644, AID_ROOT,      AID_ROOT,      "system/*" },

    /* /usr permissions */

    /* suid binaries */
    { 04755, AID_ROOT,      AID_ROOT,      "userdata/bin/chage" },
    { 04755, AID_ROOT,      AID_ROOT,      "userdata/bin/chfn.shadow" },
    { 04755, AID_ROOT,      AID_ROOT,      "userdata/bin/chsh.shadow" },
    { 04755, AID_ROOT,      AID_ROOT,      "userdata/bin/newgrp.shadow" },
    { 04755, AID_ROOT,      AID_ROOT,      "userdata/bin/su" },
    { 04755, AID_ROOT,      AID_ROOT,      "userdata/sbin/pppd" },

    { 00755, AID_ROOT,      AID_ROOT,      "userdata/bin/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "userdata/sbin/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "userdata/lib/*" },
    { 00755, AID_ROOT,      AID_ROOT,      "userdata/kernel-tests/*" },
    { 00644, AID_ROOT,      AID_ROOT,      "userdata/*" },

    { 00644, AID_ROOT,      AID_ROOT,       0 },
};

static inline void fs_config(const char *path, int dir,
                             unsigned *uid, unsigned *gid, unsigned *mode)
{
    struct fs_path_config *pc;
    int plen;

    pc = dir ? android_dirs : android_files;
    plen = strlen(path);
    for(; pc->prefix; pc++){
        int len = strlen(pc->prefix);
        if (dir) {
            if(plen < len) continue;
            if(!strncmp(pc->prefix, path, len)) break;
            continue;
        }
        /* If name ends in * then allow partial matches. */
        if (pc->prefix[len -1] == '*') {
            if(!strncmp(pc->prefix, path, len - 1)) break;
        } else if (plen == len){
            if(!strncmp(pc->prefix, path, len)) break;
        }
    }
    *uid = pc->uid;
    *gid = pc->gid;
    *mode = (*mode & (~07777)) | pc->mode;

#if 0
    fprintf(stderr,"< '%s' '%s' %d %d %o >\n",
            path, pc->prefix ? pc->prefix : "", *uid, *gid, *mode);
#endif
}
#endif
#endif
