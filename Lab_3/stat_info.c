#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
/* -------------------------------------------------------------------------------- */
 
static void print_type(struct stat *sb);
static void print_ino(const struct stat *sb);
static void print_perms(const struct stat *sb, char *name);
static void print_linkc(const struct stat *sb);
static void print_owner(const struct stat *sb);
static void print_size(const struct stat *sb);
static void print_laststch(const struct stat *sb);
static void print_lastacc(const struct stat *sb);
static void print_lastmod(const struct stat *sb);
static void print_name(const struct stat *sb, char *name);
static char* response_helper(int);
static char* time_diff_helper(time_t);
/* -------------------------------------------------------------------------------- */
 
int  main(int argc, char *argv[])
{
  struct stat sb;
 
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
 
  if (stat(argv[1], &sb) == -1) {
    perror("stat");
    exit(EXIT_SUCCESS);
  }
 
  print_type(&sb);
  print_name(&sb, argv[1]);
  print_ino(&sb);
  print_perms(&sb, argv[1]);
  print_linkc(&sb);
  print_owner(&sb);
  print_size(&sb);
  print_laststch(&sb);
  print_lastacc(&sb);
  print_lastmod(&sb);
 
  exit(EXIT_SUCCESS);
}
/* -------------------------------------------------------------------------------- */
 
static void print_type(struct stat *sb){
  printf("File type:                ");
  switch (sb->st_mode & S_IFMT) {
  case S_IFMT:   printf("bit field\n");               break;
  case S_IFSOCK: printf("socket\n");                  break;
  case S_IFLNK:  printf("symbolic link\n");           break;
  case S_IFREG:  printf("regular file\n");            break;
  case S_IFBLK:  printf("block device\n");            break;
  case S_IFCHR:  printf("character device\n");        break;
  case S_IFIFO:  printf("FIFO\n");                    break;
  default:       printf("unknown?\n");                break;
  }
}
/* -------------------------------------------------------------------------------- */
 
static void print_ino(const struct stat *sb){
  printf("I-node number:            %ld\n", (long) sb->st_ino);
}
/* -------------------------------------------------------------------------------- */
 
static void print_perms(const struct stat *sb, char *name){
  printf("Mode:                     %lo (octal)\n", (unsigned long) sb->st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
  printf("Your permisions:          read: %s, write: %s, execute: %s\n", response_helper(access(name, R_OK)), response_helper(access(name, W_OK)), response_helper(access(name, X_OK)));
}
/* -------------------------------------------------------------------------------- */
 
static void print_linkc(const struct stat *sb){
  printf("Link count:               %ld\n", (long) sb->st_nlink);
}
/* -------------------------------------------------------------------------------- */
 
static void print_owner(const struct stat *sb){

  uid_t uid = sb->st_uid;
  gid_t gid = sb->st_gid;
  struct passwd * user_info = getpwuid(uid);
  struct group * group_info = getgrgid(gid);

  printf("Ownership:                %s(%ld)   %s(%ld)\n", user_info->pw_name, (long) uid, group_info->gr_name, (long) gid);
}
/* -------------------------------------------------------------------------------- */
 
static void print_size(const struct stat *sb){
  printf("Preferred I/O block size: %ld bytes\n", (long) sb->st_blksize);
  printf("File size:                %lld bytes\n",(long long) sb->st_size);
  printf("Blocks allocated:         %lld\n",(long long) sb->st_blocks);
}
/* -------------------------------------------------------------------------------- */
 
static void print_laststch(const struct stat *sb){
  const time_t *last_change = &sb->st_ctime;
  printf("Last status change:       %s", ctime(last_change));
  printf("Time since:               %s", time_diff_helper(*last_change));
}
/* -------------------------------------------------------------------------------- */
 
static void print_lastacc(const struct stat *sb){
  const time_t *last_access = &sb->st_atime;
  printf("Last file access:         %s", ctime(last_access));
  printf("Time since:               %s", time_diff_helper(*last_access));
}
/* -------------------------------------------------------------------------------- */
 
static void print_lastmod(const struct stat *sb){
  const time_t *last_mod = &sb->st_mtime;
  printf("Last file modification:   %s", ctime(last_mod));
  printf("Time since:               %s", time_diff_helper(*last_mod));
}
/* -------------------------------------------------------------------------------- */
 
static void print_name(const struct stat *sb, char *name){
  char* bname = basename(name);
  printf("Name of the file:         %s\n", bname);
}
/* -------------------------------------------------------------------------------- */

static char* response_helper(int response_value){
  if(response_value == 0){
      return "yes";
  }
  else {
      return "no";
  }
}
/* -------------------------------------------------------------------------------- */

static char* time_diff_helper(time_t time_stamp) {
  char *result = (char *) malloc(sizeof(char) * 200);
  time_t curtime;
  time(&curtime);
  time_t timediff = (int) difftime(curtime, time_stamp);
  strftime(result, 200, "%H hours, %M minutes, %S seconds\n", gmtime( &timediff ));
  return result;
}