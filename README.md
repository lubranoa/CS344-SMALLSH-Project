<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>

<!-- Centered Title Section-->
<div align="center">
  <!-- Title Section Links -->
  <p>
    <a href="https://www.linkedin.com/in/lubrano-alexander">
      <img src="https://img.shields.io/badge/LinkedIn-0A66C2?style=for-the-badge&logo=linkedin" alt="linkedin link" />
    </a>
    <a href="https://lubranoa.github.io">
      <img src="https://img.shields.io/badge/Personal_Site-47b51b?style=for-the-badge" alt="personal website link" />
    </a>
    <a href="https://github.com/lubranoa">
      <img src="https://img.shields.io/badge/GitHub-8A2BE2?style=for-the-badge&logo=github" alt="github profile link" />
    </a>
  </p>
  <br />
  <!-- Titles and Subtitles -->
  <h1 align="center">Custom Shell with Command Parsing and Process Handling</h1>
  <p align="center">
    <b>A UNIX-like command line shell designed to operate like well-known shells such as bash</b>
  </p>
  <p align="center">
    Spring 2023 · <a href="https://ecampus.oregonstate.edu/soc/ecatalog/ecoursedetail.htm?subject=CS&coursenumber=344&termcode=ALL">CS 344 Operating Systems</a> · Oregon State University
  </p>
  <br />
</div>

<!-- Table of Contents -->
<details>
  <summary>Table of Contents</summary>
    
  - [Project Description](#project-description)
  - [Technologies Used](#technologies-used)
  - [Features](#features)
  - [Usage](#usage)
  - [Skills Applied](#skills-applied)
  - [Contact](#contact)
  - [Acknowledgments](#acknowledgments)

</details>

<!-- Project Description -->
## Project Description

This project is a UNIX-like command line shell written in the C programming language and designed to operate like well-known shells like bash. Smallsh is designed to perform common shell functions such as parsing commands, executing processes, and managing background tasks.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Technologies Used -->
## Technologies Used

  - [![c-language][c-language]][c-language-url]
  - [![c-99-std][c-99-std]][c-99-std-url]
  - [![std-lib][std-lib]][std-lib-url]
  - [![sys-calls][sys-calls]][sys-calls-url]
  - [![vim][vim]][vim-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Features -->
## Features

- Provides an interactive command-line interface for executing user commands.

- Parses user input into tokens for command and argument handling.

- Executes commands as child processes and includes built-in commands such as `exit` and `cd`.

- Enables background process execution with the `&` operator.

- Expands parameters like `$$`, `$?`, `$!`, and `${param}` in user commands. [Mostly finished]

- Planned input/output redirection using `<`, `>`, and `>>` operators. [Unfinished]

- Planned for custom signal handling of `SIGINT` and `SIGTSTP`. [Unfinished]

- Includes a workaround for handling advanced `PS1` environment variable format specifiers (see Usage section for details).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Usage -->
## Usage

Smallsh provides a command-line interface for users to execute commands.

### Compilation

To compile the `smallsh` program, navigate to the project directory and run:

```bash
gcc --std=gnu99 -o smallsh smallsh.c
```

This command compiles the source code into an executable named `smallsh`.

### Running the Shell
To run the shell after compiling, start the shell by executing ```./smallsh``` and a prompt will appear where commands can be entered:

    ```bash
    ~/dir$ ./smallsh
    $ ls
    file1.txt  file2.txt  file3.txt  smallsh
    $ echo "Hello, smallsh!"
    Hello, smallsh!
    $ exit
    ~/dir$
    ```

### Executing Commands

- Built-in Commands:

  - **`cd`**: Changes the current working directory to the specified directory. Without arguments, it defaults to the home directory.

      ```bash
      $ pwd
      /home/user/dir
      $ cd /path/to/directory
      $ cd ..
      $ pwd
      /path/to/directory
      $ cd
      $ pwd
      /home/user
      ```
  
  - **`exit`**: Terminates the shell. Can be given an optional exit status code as an argument. If not provided, defaults to an exit status of `0`.

      ```bash
      $ exit
      ~/dir$ echo $?
      0
      ~/dir$ ./smallsh
      $ exit 1234
      ~/dir$ echo $?
      1234
      ```

- External Commands:

  - Enter any valid system command (e.g., `ls`, `echo`) to execute it. The shell will create a child process to run the command.

- Run a command in the background:

  - To execute a command in the background, append `&` to a command. The shell will execute the command in the background and return control to the prompt immediately.

    ```bash
    $ sleep 5 &
    $ ls
    file1.txt  file2.txt  file3.txt  smallsh
    $ ls
    Child process 3333 done. Exit status 0.
    file1.txt  file2.txt  file3.txt  smallsh    
    ```

### Parameter expansion of environment variables:

- **`$$`**: Replaced by the process ID (PID) of the running smallsh program.

- **`$?`**: Replaced by the exit status of the last foreground command.

- **`$?`**: Replaced by the process ID of the of the most recent background process.

- **`${param}`**: Replaced with the value of the corresponding environment variable named `parameter`.

  ```bash
  $ echo "Smallsh PID: $$"
  Smallsh PID: 1234
  $ echo "Exit status of last foreground command: $?"
  Exit status of last foreground command: 0
  $ echo "Last background process PID: $!"
  Last background process PID: 5678
  $ echo "Home directory: ${HOME}"
  Home directory: /home/user
  ```

### (Unfinished) Input/Output Redirection:
    
- **`<`**: Redirects standard input to a file.

- **`>`**: Redirects standard output to a file, overwriting the file if it exists.

- **`>>`**: Redirects standard output to a file, appending to the file if it exists.

  ```bash
  $ cat < input.txt
  Hello, smallsh!
  $ ls > output.txt
  $ cat < output.txt
  file1.txt  file2.txt  file3.txt  smallsh
  $ echo "Append text" >> output.txt
  $ cat < output.txt
  file1.txt  file2.txt  file3.txt  smallshAppend text
  ```

### (Unfinished) Custom signal handling
    
- **`SIGTSTP`** (Ctrl+z)
  - Normally would cause a process to be stopped immediately. This signal is ignored by smallsh. The assignment specifications stated that the smallsh process should not respond to it by setting its disposition to `SIG_IGN`.

- **`SIGINT`** (Ctrl+c)
  - Normally would cause a process to exit immediately. This signal is ignored by smallsh except when waiting for input.
  - If the user presses ctrl-c while smallsh is waiting for input, it will print a new prompt and wait for input again.

    ```bash
    $ ^C # does not show up when typed, only a visual representation
    $ 
    $ 
    $ 
    ```

### Fix for prompt text (if nonexistent or is a long line of format specifiers):

- Alter the value of the `PS1` environment variable in the `.bashrc` file to something more simple (make a backup of your `.bashrc` file before editing).
- Use a temporary `PS1` variable:

  ```bash
  ~/dir$ ./smallsh
  \n\[\]\u\[\]@\[\]\H\[\]:\[\]\w\n\[\]\$\[\] ls
  file1.txt  file2.txt  file3.txt  smallsh
  \n\[\]\u\[\]@\[\]\H\[\]:\[\]\w\n\[\]\$\[\] exit
  ~/dir$ PS1=">>> " ./smallsh
  >>> ls
  file1.txt  file2.txt  file3.txt  smallsh
  >>> 
  ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Skills Applied -->
## Skills Applied

- Developed a custom UNIX-like shell using the C programming language.

- Gained experience with parsing and tokenizing user input for command processing.

- Implemented parent and child process management using UNIX system calls.

- Applied dynamic memory allocation techniques for managing runtime data structures.

- Practiced error handling to ensure robust execution of built-in and external commands.

- Learned to work with process IDs and environment variables for parameter expansion.

- Built a deeper knowledge of the C Standard Library and low-level programming concepts.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Contact -->
## Contact

Alexander Lubrano - [lubrano.alexander@gmail.com][email] - [LinkedIn][linkedin-url]

Project Link: [https://github.com/lubranoa/CS344-SMALLSH-Project][repo-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Acknowledgments -->
## Acknowledgments
  
  - [C reference on CPP Reference][c-language-url]
  - [Linux Man Pages Online][man-url]
  - [Vim Cheat Sheet][cheat-url]
  - [Shields.io][shields-url]
  - [Simple Icons][icons-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Markdown links -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[c-language]: https://img.shields.io/badge/Language-grey?style=for-the-badge&logo=c&logoColor=#A8B9CC
[c-language-url]: https://en.cppreference.com/w/c

[vim]:https://img.shields.io/badge/Vim-grey?style=for-the-badge&logo=vim&logoColor=019733
[vim-url]: https://www.vim.org/

[c-99-std]: https://img.shields.io/badge/Standard_C99_(gcc)-grey?style=for-the-badge
[c-99-std-url]: https://en.cppreference.com/w/c/99

[std-lib]: https://img.shields.io/badge/C_Standard_Library-grey?style=for-the-badge
[std-lib-url]:https://en.cppreference.com/w/c/header

[sys-calls]: https://img.shields.io/badge/Linux_System_Calls-grey?style=for-the-badge
[sys-calls-url]: https://man7.org/linux/man-pages/man2/syscalls.2.html

[email]: mailto:lubrano.alexander@gmail.com
[linkedin-url]: https://linkedin.com/in/lubrano-alexander
[repo-url]: https://github.com/lubranoa/CS344-SMALLSH-Project

[cheat-url]: https://vim.rtorr.com/
[man-url]: https://man7.org/linux/man-pages/index.html
[shields-url]: https://shields.io/
[icons-url]: https://simpleicons.org/