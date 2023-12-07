<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>

<!-- Centered Title Section-->
<div align="center">
  <!-- Title Section Links -->
  <p>
    <a href="www.linkedin.com/in/lubrano-alexander">
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
  <h1 align="center">Smallsh</h1>
  <p align="center">
    <b>A Custom UNIX-like Shell Implemented in C</b>
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

<!-- Technologies Used -->
## Technologies Used

  - [![c-language][c-language]][c-language-url]
  - [![vim][vim]][vim-url]
  - [![c-99-std][c-99-std]][c-99-std-url]
  - [![std-lib][std-lib]][std-lib-url]
  - [![sys-calls][sys-calls]][sys-calls-url]

<!-- Features -->
## Features

  - Interactive command line interface for users to interact with.

  - Parses user commands into semantic tokens to carry out the command.

  - Runs every command as a child process.
  
  - Implements the built-in commands `exit` and `cd`.

  - Handles non-built-in commands using the appropriate `EXEC(3)` functions.

  - Run commands in the background using the `&` operator.

  - (Mostly finished) Parameter expansion of `$$`, `$?`, `$!`, and `${param}` with appropriate environment variable values.

  - (Unfinished) Built-in Input/Output redirection operators `<`, `>`, and `>>`.

  - (Unfinished) Custom signal handling of `SIGINT` and `SIGTSTP`

  - Does **not** recognize fancy format specifiers used in the `PS1` environment variable, so the user's prompt output may look odd or not appear. See fix in Usage.

<!-- Usage -->
## Usage

Smallsh provides a command-line interface for users to execute commands. Here are some basic usage examples. For the following examples, :

  - Run the shell, then enter some commands:

    ```bash
    ~/dir$ ./smallsh
    $ ls
    file1.txt  file2.txt  file3.txt  smallsh
    $ echo "Hello, smallsh!"
    Hello, smallsh!
    $ exit
    ~/dir$
    ```

  - Run built-in commands:

    - **`cd`**

      - Used to change the current working directory. Can be given an optional directory path as an argument. If not provided, defaults to change to the home directory.

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
    
    - **`exit`**

      - Used to exit the smallsh shell. Can be given an optional exit status code as an argument. If not provided, defaults to an exit status of `0`.

        ```bash
        $ exit
        ~/dir$ echo $?
        0
        ~/dir$ ./smallsh
        $ exit 1234
        ~/dir$ echo $?
        1234
        ```

  - Parameter expansion of environment variables:

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

  - Run a command in the background:

    - To execute a command in the background, append `&` to a command. Smallsh will execute it in the background, allowing user to continue using the shell without waiting for the command to finish.

      ```bash
      $ sleep 5 &
      $ ls
      file1.txt  file2.txt  file3.txt  smallsh
      $ ls
      Child process 3333 done. Exit status 0.
      file1.txt  file2.txt  file3.txt  smallsh    
      ```

  - (Unfinished) Redirect input and output with `<`, `>`, and `>>`:

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

  - (Unfinished) Custom signal handling
    
    - **`SIGTSTP`** (Ctrl-z)
      - Normally would cause a process to be stopped immediately. This signal is ignored by smallsh. The assignment specifications stated that the smallsh process should not respond to it by setting its disposition to `SIG_IGN`.

    - **`SIGINT`** (Ctrl-c)
      - Normally would cause a process to exit immediately. This signal is ignored by smallsh except when waiting for input.
      - If the user presses ctrl-c while smallsh is waiting for input, it will print a new prompt and wait for input again.

        ```bash
        $ ^C # does not show up when typed, only a visual representation
        $ 
        $ 
        $ 
        ```

  - **FIX**: Odd or nonexistent prompt:

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

  - C language and its libraries

  - String manipulation and tokenization

  - Command-line interface development

  - UNIX system calls for file I/O and child processes

  - Error handling of called functions for crash protection

  - Dynamic memory management

  - Managing parent and child processes
  
  - Shell scripting and makefile usage

<!-- Contact -->
## Contact

Alexander Lubrano - [lubrano.alexander@gmail.com][email] - [LinkedIn][linkedin-url]

Project Link: [https://github.com/lubranoa/CS344-SMALLSH-Project][repo-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Acknowledgements -->
## Acknowledgments
  
  - [C reference on CPP Reference][c-ref-url]
  - [Linux Man Pages Online][man-url]
  - [Vim Cheat Sheet][cheat-url]
  - [Shields.io][shields-url]
  - [Simple Icons][icons-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Markdown links -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[c-language]: https://img.shields.io/badge/Language-grey?style=for-the-badge&logo=c&logoColor=#A8B9CC
[c-language-url]: https://en.cppreference.com/

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
[c-ref-url]: https://en.cppreference.com/w/c
[shields-url]: https://shields.io/
[icons-url]: https://simpleicons.org/