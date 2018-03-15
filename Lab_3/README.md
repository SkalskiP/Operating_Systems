# Advanced File I/O

### The difference between system functions stat(), fstat() and lstat()

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
