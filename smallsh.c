#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>
#include <sys/types.h>

/* Macro for getting number of elements in an array */
#define arrlen(a) (sizeof(a) / sizeof (*a))

int main(){
  
  char *ps1_str = getenv("PS1");
  char *empty_str = "";
  char *line = NULL;
  size_t n = 0;
  ssize_t line_length = 0;

  // Command line executes in an infinite loop
  for (;;) {
  
    /* -------------------------------------------------------------------------------
     *  INPUT
     *
     * -----------------------------------------------------------------------------*/
  //input:;  
    // Check for any un-waited-for background processes in the same process group ID 
    // as smallsh
    
      // If stopped, smallsh sends SIGCONT signal and prints msg to stderr

      // If exited, print msg
    
      // If signaled, print msg
      
      // Any other child state changes are ignored
    
    // Print expanded PS1 parameter before each new command
    if (ps1_str == NULL) {
      if (fprintf(stderr, "%s", empty_str) < 0) goto exit;  // print empty string if PS1 was unset
    } else {
      if (fprintf(stderr, "%s", ps1_str) < 0) goto exit;
    }
      
    // After printing prompt line, get a line of input
    if ((line_length = getline(&line, &n, stdin)) == -1) goto exit;
    
    // If interrupted by a signal: 
      
        // print newline
          
        // print new command prompt (including checking for background processes)
         
        // reading line of input should continue (see CLEARERR(3) and reset errno)
  
    /* ------------------------------------------------------------------------------
     *  WORD SPLITTING
     *
     * ----------------------------------------------------------------------------*/
   
    // Split line of input into words delimited by the chars in the IFS 
    // environment variable or " \t\n" if IFS is unset (NULL)

  
      // A minimum of 512 words shall be supported

    /* ------------------------------------------------------------------------------
     * EXPANSION 
     *
     * ----------------------------------------------------------------------------*/
    
    // Parameter expansion of "$$", "$?", "$!", and "~". Expansion occurs in a 
    // forward direction in a single pass. Expanded text does not participate in 
    // token formation (expansion is not recursive). Each of the following is 
    // expanded within each word

    // Any occurence of "~/" at the beginning of a word is replaced with the value
    // the HOME environment variable. The "/" is retained. (See GETENV(3))
      
    // Any occurence of "$$" within a word is replaced with the process ID of the 
    // smallsh process (see GETPID(3))
      
    // Any occurence of "$?" within a word is replaced with the exit status of 
    // the last foreground command (see waiting). Defaults to "0"
      
    // Any occurence of "$!" within a word is replaced with the process ID of the
    // most recent background process (see waiting) Defaults to "" if no background
    // process ID is available
        
    // if an expanded environment variable is unset, interpret it as an empty
    // string (""). Includes PS1
  
    /* ------------------------------------------------------------------------------
     * PARSING 
     *
     * ----------------------------------------------------------------------------*/
    
    // The words are parsed syntactically into tokens in the following order. Tokens
    // recognized in a previous step do not take part in further parsing. 3) and 4) 
    // can occur in either order. All words not listed below shall be interpreted as
    // regular words and form the command to be executed and its arguments. The 
    // tokens below are not included as arguments:
    
    // 1) The first occurence of the word "#" and any additional words following are
    //    ignored as a comment
   
    // 2) If the last word is "&", the command runs in the background
  
    // 3) If the last word is immediately preceded by the word "<", interpret as a
    //    filename operand of the input redirection operator
 
    // 4) If the last word is immediately preceded by the word ">", interpret as a 
    //    filename operand of the output redirection operator
    
    /* ------------------------------------------------------------------------------
     * EXECUTION
     *
     * ----------------------------------------------------------------------------*/
    
    // If no command word present
      // Not an error
      // Do not modify "$?"
      // Return silently to Input

    // If command to be executed is 'exit', takes one argument
  exit:;
    // If no argument provided, arg implied to expanded "$?"
    
    // If more than one arg or arg is not an int, throw error
      
    // print "\nexit\n" to stderr
       
    // send SIGINT signal to all child processes in the same process group (see
    // KILL(2))
        
    // smallsh does need to wait for child processes, exit immediately
         
    // exit with specified or implied value (see EXIT(3))
         
    // exit loop

    // EOF on stdin will be interpreted as an implied 'exit $?' command
  
    // If command to be executed is 'cd', takes one argument
    
    // If not provided, arg is implied to be the expansion of "~/", the value of 
    // the HOME environment variable
    
    // If more than one arg, throw error
   
    // smallsh can change its own current working directory to the specified or
    // implied path (see CHDIR(2))
  
    // If operation fails, throw error
  
    // Otherwise, execute non-built-in commands using appropriate 'EXEC(3)' function
    
    // The command and arguments are executed in a new child process
   
    // If command name does not include "/", search for command in system's PATH
    // environment variable (see EXECVP(3))
  
    // Call FORK(2), and throw error on failure
 
    // Implement redirection operators '<' and '>'
  
    // In the child, reset signals to original states when smallsh was invoked.
    // Note: Not the same as SIG_DFL. See oldact in SIGACTION(2)

    // If a filename was specified as the operand to the input redirection operator
    // ("<"), open file for reading on stdin, and throw error on failure

    // If a filename was specified as the operand to the output redirection 
    // operator, open file for writing on stdout. 

      // If file does not exist, create with permissions 0777

      // Throw error if file cannot be opened or created for writing
  
    // Implement the '&' operator to run commands in the background
      
    // If child process fails to exec, throw error
    
      // When an error occurs in child, print informative error message to stderr and
      // exit with non-zero exit status
  
    /* ------------------------------------------------------------------------------
     * WAITING
     *
     * ----------------------------------------------------------------------------*/

    // Built-in commands skip waiting step
     
    // If a non-built-in was executed and the "&" operator was not present, smallsh
    // parent process performs a blocking wait (see WAITPID(2)) on the foreground
    // child process.
     
      // Set "$?" to the exit status of the waited-for command

      // If the waited-for command is terminated by a signal, set "$?" to 128 + [n]
      // where [n] is the number of the signal that caused the child process to 
      // terminate
        
    // If a child process is stopped, smallsh sends it the SIGCONT signal and 
    // prints a message to stderr (See KILL(2))

      // Update "$!" to the PID of the child process, as if it had been a 
      // background command
      // Smallsh no longer performs a block wait on this process, and it will 
      // continue to run in the background
      
    // Any other child state changes are ignored (e.g. WIFCONTINUED)
      
    // Otherwise, child process runs in background and parent smallsh process does
    // not wait on it
      
      // Running in the background is the default behavior of a forked process
        
      // "$!" should be set to the pid of such a process

    // Implement custom behavior for SIGINT (CTRL+C)
      // SIGINT is ignored (SIG_IGN) at all times except when reading a line of 
      // input in Step 1 INPUT, during which time it is registered to a signal 
      // handler that does nothing
    
      // When SIGINT is delivered by a terminal, terminal clears the current line
      // of input and reprints the prompt for the restarted line of input by 
      // registering a signal handler (that does nothing) to the SIGINT signal
    
      // When an uninterruptable system call (such as read()) is blocked and a 
      // signal with a custom handler arrives, the system call will fail with 
      // errno=ENITR (interrupted) after the signal handler returns. This allows us
      // to escape the blocked read operation in order to reprint the prompt.
  
    // Implement custom behavior for SIGTSTP
      // SIGSTP is ignored
      // Smallsh should set its disposition to SIG_IGN
  }

  return errno ? -1 : 0;

}
