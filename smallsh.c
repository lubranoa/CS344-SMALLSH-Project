#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

#ifndef MAX_WORDS
#define MAX_WORDS 512
#endif

#define EMPTY_STR ""
#define NULL_IFS_STR " \t\n"
#define HOME_STR "~/"
#define SMSH_PID_STR "$$"
#define EX_STAT_STR "$?"
#define BKGR_PID_STR "$!"
#define DEFAULT_EX_STAT "0"

char *words[MAX_WORDS];
size_t wordsplit(char const *line);
char * expand(char const *word, char const *bgpid, char const *pid, char const *status);

int main(int argc, char *argv[])
{
  int length;
  if ((length = snprintf(0, 0, "%d", getpid())) < 0) err(1, "snprintf");
  char *smallsh_pid = malloc(sizeof *smallsh_pid * (length + 1));
  if (sprintf(smallsh_pid, "%d", getpid()) < 0) err(1, "sprintf");
  
  char *fg_cmd_status = DEFAULT_EX_STAT;
  char *bg_pid = EMPTY_STR;
  pid_t child_pid = -5;
  int child_status = -5;

  FILE *input = stdin;
  char *input_fn = "(stdin)";
  if (argc == 2) {
    input_fn = argv[1];
    input = fopen(input_fn, "re");
    if (!input) err(1, "%s", input_fn);
  } else if (argc > 2) {
    errx(1, "too many arguments");
  }

  char *line = NULL;
  size_t n = 0;
  for (;;) {
prompt:;
    /* TODO: Manage background processes */
    //if (child_pid > 0) {
    //  if (WIFEXITED(child_status)) fprintf(stderr, "Child provess %d done. Exit status %d.\n", child_pid, WEXITSTATUS(child_status));
    //  else if (WIFSIGNALED(child_status)) fprintf(stderr, "Child process %d done. Signaled %d.\n", child_pid, WTERMSIG(child_status));
    //}
    /* TODO: prompt */
    if (input == stdin) {
      char *ps1_str = getenv("PS1");
      if (ps1_str == NULL) ps1_str = EMPTY_STR;
      if (fprintf(stderr, "%s", ps1_str) < 0) err(1, "fprintf");
    }
    ssize_t line_len = getline(&line, &n, input);
    if (line_len < 0) {
      if (!feof(input)) {
        err(1, "%s", input_fn);
      } else {
        exit(0);
      }
    }
    memset(words, '\0', sizeof words);
    size_t nwords = wordsplit(line);
    for (size_t i = 0; i < nwords; ++i) {
      //fprintf(stderr, "Word %zu: %s  -->  ", i, words[i]);
      char *exp_word = expand(words[i], bg_pid, smallsh_pid, fg_cmd_status);
      free(words[i]);
      words[i] = exp_word;
      //fprintf(stderr, "%s\n", words[i]);
    }
    int bg = 0,
        rd = 0,
        wr = 0,
        ap = 0;
    char *new_words[MAX_WORDS] = {NULL};

    if (nwords > 1) {
      for (size_t i = nwords - 1; i > 0; --i) {
        if (strcmp(words[i], "&") == 0) {
          bg = 1;
          words[i] = NULL;
        }
        else if (strcmp(words[i], "<") == 0) rd = 1;
        else if (strcmp(words[i], ">") == 0) wr = 1;
        else if (strcmp(words[i], ">>") == 0) ap = 1;
      }
    }
    if (words[0] == NULL) goto prompt;

    if (strncmp(words[0], "exit", 4) == 0) {
      int exit_num;
      if (words[2] != NULL) errx(1, "exit: too many arguments");
      if (words[1] != NULL) {
        for (int i = 0; i < strlen(words[1]); ++i) {
          if (words[1][i] < 48 || words[1][i] > 57) errx(1, "exit: argument contained non-digits");
        }
        exit_num = atoi(words[1]);
      } else {
        exit_num = atoi(fg_cmd_status);
      }
      exit(exit_num);
    } 
    else if (strncmp(words[0], "cd", 2) == 0) {
      int dir;
      char *home_dir = getenv("HOME");
      if (words[2] != NULL) err(1, "cd: too many arguments");
      if (words[1] == NULL) {
        dir = chdir(home_dir);
      } else {
        dir = chdir(words[1]);
      }
      if (dir == -1) err(1, "chdir");
    } 
    else {
      child_pid = fork();

      switch(child_pid) {
        case -1:
          err(1, "fork");
          break;
        case 0:
          execvp(words[0], words);
          err(1, "execvp");
          break;
        default:
          if (bg == 0) {
            child_pid = waitpid(child_pid, &child_status, 0);
            if (child_pid == -1) err(1, "waitpid");
            if ((length = snprintf(0, 0, "%d", child_pid)) < 0) err(1, "snprintf");
            char *pid = malloc(sizeof *pid * (length + 1));
            if (sprintf(pid, "%d", child_pid) < 0) err(1, "sprintf");
            bg_pid = pid;
            if (WIFEXITED(child_status)) {
              if ((length = snprintf(0, 0, "%d", WEXITSTATUS(child_status))) < 0) err(1, "snprintf");
              char *status = malloc(sizeof *status * (length + 1));
              if (status == NULL) err(1, "malloc");
              if (sprintf(status, "%d", WEXITSTATUS(child_status)) < 0) err(1, "sprintf");
              fg_cmd_status = status;
            } 
            else {
              if ((length = snprintf(0, 0, "%d", 128 + WTERMSIG(child_status))) < 0) err(1, "snprintf");
              char *status = malloc(sizeof *status * (length + 1));
              if (sprintf(status, "%d", 128 + WTERMSIG(child_status)) < 0) err(1, "sprintf");
              fg_cmd_status = status;
            }
            child_pid = -5;
            child_status = -5;
          } 
          else {
            if ((length = snprintf(0, 0, "%d", child_pid)) < 0) err(1, "snprintf");
            char *pid = malloc(sizeof *pid * (length + 1));
            if (sprintf(pid, "%d", child_pid) < 0) err(1, "sprintf");
            bg_pid = pid;
            waitpid(child_pid, &child_status, WNOHANG);
          }
          
          break;
      }
    }
  }
  free(smallsh_pid);
  exit(0);
}

char *words[MAX_WORDS] = {0};

/* Splits a string into words delimited by whitespace. Recognizes
 * comments as '#' at the beginning of a word, and backslash escapes.
 *
 * Returns number of words parsed, and updates the words[] array
 * with pointers to the words, each as an allocated string.
 */
size_t 
wordsplit(char const *line) {
  size_t wlen = 0;
  size_t wind = 0;

  char const *c = line;
  for (;*c && isspace(*c); ++c); /* discard leading space */

  for (; *c;) {
    if (wind == MAX_WORDS) break;
    /* read a word */
    if (*c == '#') break;
    for (;*c && !isspace(*c); ++c) {
      if (*c == '\\') ++c;
      void *tmp = realloc(words[wind], sizeof **words * (wlen + 2));
      if (!tmp) err(1, "realloc");
      words[wind] = tmp;
      words[wind][wlen++] = *c; 
      words[wind][wlen] = '\0';
    }
    ++wind;
    wlen = 0;
    for (;*c && isspace(*c); ++c);
  }
  return wind;
}


/* Find next instance of a parameter within a word. Sets
 * start and end pointers to the start and end of the parameter
 * token.
 */
char
param_scan(char const *word, char const **start, char const **end)
{
  static char const *prev;
  if (!word) word = prev;
  
  char ret = 0;
  *start = 0;
  *end = 0;
  for (char const *s = word; *s && !ret; ++s) {
    s = strchr(s, '$');
    if (!s) break;
    switch (s[1]) {
    case '$':
    case '!':
    case '?':
      ret = s[1];
      *start = s;
      *end = s + 2;
      break;
    case '{':;
      char *e = strchr(s + 2, '}');
      if (e) {
        ret = s[1];
        *start = s;
        *end = e + 1;
      }
      break;
    }
  }
  prev = *end;
  return ret;
}

/* Simple string-builder function. Builds up a base
 * string by appending supplied strings/character ranges
 * to it.
 */
char *
build_str(char const *start, char const *end)
{
  static size_t base_len = 0;
  static char *base = 0;

  if (!start) {
    /* Reset; new base string, return old one */
    char *ret = base;
    base = NULL;
    base_len = 0;
    return ret;
  }
  /* Append [start, end) to base string 
   * If end is NULL, append whole start string to base string.
   * Returns a newly allocated string that the caller must free.
   */
  size_t n = end ? end - start : strlen(start);
  size_t newsize = sizeof *base *(base_len + n + 1);
  void *tmp = realloc(base, newsize);
  if (!tmp) err(1, "realloc");
  base = tmp;
  memcpy(base + base_len, start, n);
  base_len += n;
  base[base_len] = '\0';

  return base;
}

/* Expands all instances of $! $$ $? and ${param} in a string 
 * Returns a newly allocated string that the caller must free
 */
char *
expand(char const *word, char const *bgpid, char const *pid, char const *status)
{
  char const *pos = word;
  char const *start, *end;
  char c = param_scan(pos, &start, &end);
  free(build_str(NULL, NULL));
  build_str(pos, start);
  while (c) {
    if (c == '!') build_str(bgpid, NULL);
    else if (c == '$') build_str(pid, NULL);
    else if (c == '?') build_str(status, NULL);
    else if (c == '{') {
      char* env_str = getenv(build_str(start + 2, end - 1));
      free(build_str(NULL, NULL));
      build_str(env_str, NULL);
    }
    pos = end;
    c = param_scan(pos, &start, &end);
    build_str(pos, start);
  }
  return build_str(start, NULL);
}

