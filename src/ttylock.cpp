
/* 
#    $Id: ttylock.cpp,v 1.6 2006/04/05 17:10:03 kfstark Exp $
#
#    Copyright (C) 2000 US Geological Survey
#    Written by Keith F. Stark
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
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#    C++/Qt stuff
#    Copyright (C) 2012  Paul Campbell <paul@taniwha.com>
*/

#include "ttylock.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

ttylock::ttylock(QString t)
{
    tty = t.trimmed();
    locked=0;
}

ttylock::~ttylock()
{
    if (locked)
	    unlock();
}

bool
ttylock::lock()
{
	int old_mask, pid;
	bool ret = true;

	if(get_names(tty) < 0) 
		return false;

	old_mask = umask(0);
	pid = getpid();

	if (write_lock(pid_name, pid) < 0) {
		umask(old_mask);
		return false;
	}
	umask(old_mask);

	if (link(pid_name.toAscii(), dev_name.toAscii()) < 0) {
		if ((ret = check_lock(dev_name, getpid())) >= 0)
			goto quit;
	}
 quit:
	if(!ret)
		unlink(dev_name.toAscii());
	unlink(pid_name.toAscii());
	locked = ret;
	return ret;
}

void
ttylock::unlock()
{
	locked = 0;
	if(get_names(tty) < 0) 
		return;
	if (check_lock(dev_name, 0) == 0)
		unlink(dev_name.toAscii());
}

bool
ttylock::write_lock(QString dev, int my_pid )
{
	FILE *lock;

	if ((lock = ::fopen(dev.toAscii(), "w")) == NULL) 
		return false;
	::fprintf(lock, "%10d\n", my_pid);
	::fclose(lock);
	return true;
}

bool
ttylock::check_lock(QString file, int wrk_pid)
{
	char file_pid[12];
	int fd;
	int fpid;

	if ((fd = ::open( file.toAscii(), O_RDONLY)) < 0) 
		return false;
	if (::read(fd, &file_pid, sizeof(file_pid)) != sizeof( file_pid )-1) 
		return false;
	::close(fd);
	/*
	 * If this is a child pid, we have already rewritten
	 * a linked lockfile.
	 */
	file_pid[10] = '\0';
	fpid = ::atoi(file_pid);
	if(fpid == wrk_pid)
		return true;

	if (fpid != ::getpid()) {
		errno = 0;
		if (::kill(fpid, 0) == 0 ) {
			return false;
		}
		::unlink(file.toAscii());
	}
	return true;
}

bool
ttylock::get_names( QString dev )
{
	DIR *dev_dir;
	struct stat mystat;
	struct dirent *dir_p;
	unsigned node;
	int is_sym;
	QString lock_name;

	/*
	 * Mark the names as undefined.
	 */
	pid_name = "";
	dev_name = "";

	/* 
	 * Scan past the path portion of 'dev' if it was included in
	 * 'dev'.
	 */
	int l = dev.lastIndexOf("/");
	if (l < 0) {
		lock_name = dev;
	} else {
		lock_name = dev.mid(l+1,-1);
	}
	if (lock_name.isEmpty())
		return false;
	dev_name = DEV_PATH+lock_name;

	is_sym = 0;
	if (lstat(dev_name.toAscii(), &mystat) >= 0) 
		is_sym = S_ISLNK( mystat.st_mode );

	if (stat(dev_name.toAscii(), &mystat ) < 0) 
		return false;
	
	dev_name = "";

	pid_name = QString(LOCK_PATH)+"LCK.."+QString::number(getpid());

	node = mystat.st_ino;
	if(is_sym) {
		if ((dev_dir = opendir(DEV_PATH)) != NULL) {
			while ((dir_p = readdir(dev_dir)) != NULL) {
				if(dir_p->d_ino == node) {
					lock_name = dir_p->d_name;
					break;
				}
			}
			closedir( dev_dir );
		}
	}
	
	dev_name = QString(LOCK_PATH)+"LCK.."+lock_name;
	return true;
}

