#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>

int main(int argc, char *argv[]){
  
  // Perform in infinite loop
 
    // ------------------------------------------------------------------------------
    // Input
    // ------------------------------------------------------------------------------
      
      // Check for any un-waited-for background processes in the same 
      // process group ID as smallsh
    
      // If stopped, smallsh sends SIGCONT signal and prints msg to stderr

      // If exited, print msg
    
      // If signaled, print msg
      
      // Any other child state changes are ignored
    
      // Print interactive prompt to stderr by expanding the PS1 parameter (printed 
      // before each new command)
      
      // After printing command prompt, get a line of input from stdin
      // using GETLINE(3)
     
        // If interrupted by a signal: 
      
          // print newline
          
          // print new command prompt (including checking for background processes)
         
          // reading line of input should continue (see CLEARERR(3) and reset errno)
  
    // ------------------------------------------------------------------------------
    // Word Splitting
    //
    // ------------------------------------------------------------------------------
   
      // Split line of input into words delimited by the chars in the IFS 
      // environment variable or " \t\n" if IFS is unset (NULL)
  
      // A minimum of 512 words shall be supported

    // ------------------------------------------------------------------------------
    // Expansion 
    //
    // ------------------------------------------------------------------------------
    
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
  
    // ------------------------------------------------------------------------------
    // Parsing 
    //
    // ------------------------------------------------------------------------------
    
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
    
    // ------------------------------------------------------------------------------
    // Execution
    //
    // ------------------------------------------------------------------------------
    
    // If no command word present
      // Not an error
      // Do not modify "$?"
      // Return silently to Input

    // If command to be executed is 'exit', takes one argument
    
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
  
    // Execute non-built-in commands using the appropriate 'EXEC(3)' function
  
    // Implement redirection operators '<' and '>'
  
    // Implement the '&' operator to run commands in the background
  
    // ------------------------------------------------------------------------------
    // Waiting
    //
    // ------------------------------------------------------------------------------

      // Implement custom behavior for SIGINT
  
      // Implement custom behavior for SIGTSTP
  
  return 0;

}
