#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>
#include <aio.h>

#define DIM(x) (sizeof(x)/sizeof(*(x)))

static const char     *sizes[]   = { "EiB", "PiB", "TiB", "GiB", "MiB", "KiB", "B" };
static const uint64_t  exbibytes = 1024ULL * 1024ULL * 1024ULL *
                                   1024ULL * 1024ULL * 1024ULL;

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
static char* response_util(int response_value);
static char* time_diff_util(time_t time_stamp);
static char* convert_size_util(uint64_t size);
static bool get_user_confirmation(void);
static void print_content(char *name);
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
  print_content(argv[1]);
 
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
  printf("Your permisions:          read: %s, write: %s, execute: %s\n", response_util(access(name, R_OK)), response_util(access(name, W_OK)), response_util(access(name, X_OK)));
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
  printf("File size converted:      %s\n", convert_size_util(sb->st_size));
  printf("Blocks allocated:         %lld\n",(long long) sb->st_blocks);
}
/* -------------------------------------------------------------------------------- */
 
static void print_laststch(const struct stat *sb){
  const time_t *last_change = &sb->st_ctime;
  printf("Last status change:       %s", ctime(last_change));
  char *state = time_diff_util(*last_change);
  printf("Time since:               %s", state);
  free(state);
}
/* -------------------------------------------------------------------------------- */
 
static void print_lastacc(const struct stat *sb){
  const time_t *last_access = &sb->st_atime;
  printf("Last file access:         %s", ctime(last_access));
  char *state = time_diff_util(*last_access);
  printf("Time since:               %s", state);
  free(state);
}
/* -------------------------------------------------------------------------------- */
 
static void print_lastmod(const struct stat *sb){
  const time_t *last_mod = &sb->st_mtime;
  printf("Last file modification:   %s", ctime(last_mod));
  char *state = time_diff_util(*last_mod);
  printf("Time since:               %s", state);
  free(state);
}
/* -------------------------------------------------------------------------------- */
 
static void print_name(const struct stat *sb, char *name){
  char* bname = basename(name);
  char *linkname;

  // r = readlink(name, linkname, sb.st_size + 1);
  printf("Name of the file:         %s\n", bname);

  // Check if file is a symbolic link
  struct stat link_info;
  lstat (name, &link_info);
  if (S_ISLNK(link_info.st_mode)) {
    ssize_t r;
    linkname = malloc(link_info.st_size + 1);
    r = readlink(name, linkname, link_info.st_size + 1);
    printf("File is symbolic link to: '%s'\n", linkname);
  } 
}
/* -------------------------------------------------------------------------------- */

static char* response_util(int response_value){
  if(response_value == 0){
      return "yes";
  }
  else {
      return "no";
  }
}
/* -------------------------------------------------------------------------------- */

static char* time_diff_util(time_t time_stamp) {
  char *result = (char *) malloc(sizeof(char) * 200);
  time_t curtime;
  time(&curtime);
  time_t timediff = (int) difftime(curtime, time_stamp);
  strftime(result, 200, "%H hours, %M minutes, %S seconds\n", gmtime( &timediff ));
  return result;
}
/* -------------------------------------------------------------------------------- */

static char* convert_size_util(uint64_t size) {
  char     *result = (char *) malloc(sizeof(char) * 20);
  uint64_t  multiplier = exbibytes;
  int i;

  for (i = 0; i < DIM(sizes); i++, multiplier /= 1024)
  {   
      if (size < multiplier)
          continue;
      if (size % multiplier == 0)
          sprintf(result, "%" PRIu64 " %s", size / multiplier, sizes[i]);
      else
          sprintf(result, "%.1f %s", (float) size / multiplier, sizes[i]);
      return result;
  }
  strcpy(result, "0");
  return result;
}
/* -------------------------------------------------------------------------------- */

static bool get_user_confirmation(void) {
  bool waiting_for_confirmation = true;
  char in;

  while(waiting_for_confirmation) {
    printf("Type (y/n): ");
    scanf(" %c",&in);
    getchar();

    if(in == 'y') {
      return true;
    }
    else if (in == 'n') {
      return false;
    }
  }
}

/* -------------------------------------------------------------------------------- */

static void print_content(char *name) {
  bool user_response;
  printf("\nDo you want to display its content?\n");
  user_response = get_user_confirmation();

  if(user_response) {
    printf("\nImplementation in progress...\n");
  } else{
    printf("\nMy work is done here...\n");
  }
}