# Advanced File I/O

### The difference between system functions stat(2), fstat(2) and lstat(2)

These functions return information about a file, in the buffer pointed to by buf.  No permissions are required on the file itself, but—in the case of ```stat()```, ```fstatat()```, and ```lstat()``` execute  (search)  permission is required on all of the directories in pathname that lead to the file.

```stat()``` retrieve information about the file pointed to by pathname

```fstat()``` is  identical to ```stat()```, except that if pathname is a symbolic link, then it returns information about the link itself, not the file that it refers to.

```lstat()```  is identical to ```stat()```, except that  the  file  about  which  information  is  to  be retrieved is specified by the file descriptor fd.

### Struct stat

```
struct stat {
     dev_t     st_dev;         /* ID of device containing file */
     ino_t     st_ino;         /* inode number */
     mode_t    st_mode;        /* protection */
     nlink_t   st_nlink;       /* number of hard links */
     uid_t     st_uid;         /* user ID of owner */
     gid_t     st_gid;         /* group ID of owner */
     dev_t     st_rdev;        /* device ID (if special file) */
     off_t     st_size;        /* total size, in bytes */
     blksize_t st_blksize;     /* blocksize for filesystem I/O */
     blkcnt_t  st_blocks;      /* number of 512B blocks allocated */

     struct timespec st_atim;  /* time of last access */
     struct timespec st_mtim;  /* time of last modification */
     struct timespec st_ctim;  /* time of last status change */

 #define st_atime st_atim.tv_sec      /* Backward compatibility */
 #define st_mtime st_mtim.tv_sec
 #define st_ctime st_ctim.tv_sec
 };
 ```
```S_IFMT``` flag for ```st_mode``` field represents mask for file type

### The difference between system functions getpwuid(3), getgrgid(3) and getlogin(3)

```getpwuid()``` function returns a pointer to a structure containing the broken-out fields of  the  record  in  the password database that matches the user ID uid.

```
struct passwd {
     char   *pw_name;       /* username */
     char   *pw_passwd;     /* user password */
     uid_t   pw_uid;        /* user ID */
     gid_t   pw_gid;        /* group ID */
     char   *pw_gecos;      /* user information */
     char   *pw_dir;        /* home directory */
     char   *pw_shell;      /* shell program */
 };
```

```getgrgid()``` function returns a pointer to a structure containing the broken-out  fields of the record in the group database that matches the group ID gid.

```
struct group {
     char   *gr_name;        /* group name */
     char   *gr_passwd;      /* group password */
     gid_t   gr_gid;         /* group ID */
     char  **gr_mem;         /* NULL-terminated array of pointers
                                to names of group members */
 };
```

```getlogin()``` returns  a  pointer  to a string containing the name of the user logged in on the controlling terminal of the process,  or  a  null pointer if this information cannot be determined.  The string is statically allocated and might be overwritten on subsequent  calls  to  this function or to cuserid().

### The difference between system functions time(2), strftime(3) and difftime(3)

```time()``` returns  the  time  as  the  number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).

```strftime()``` function  formats the broken-down time tm according to the format specification format and places the result in the  character array s of size max.

```difftime()``` function returns the number of seconds elapsed between time time1 and time time0, represented as a double.  Each of the  times is  specified  in calendar time, which means its value is a measurement (in seconds) relative to the Epoch, 1970-01-01 00:00:00 +0000 (UTC).

### readlink(2)

```readlink()``` places  the  contents  of the symbolic link pathname in the buffer buf, which has size bufsiz.  readlink() does not append  a  null byte  to  buf.   It  will  truncate the contents (to a length of bufsiz characters), in case the buffer is too small to hold all  of  the  contents.

### Library functions aio_read(3), aio_write(3), aio_error(3), aio_return(3), aio_suspend(3)

```aio_read()``` 
