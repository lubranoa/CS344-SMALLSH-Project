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

  - Provides an interactive command line interface for users to interact with.

  - Built-in commands `exit` and `cd`.

  - Handles non-built-in commands using the appropriate `EXEC(3)` functions.

  - Run commands in the background using the `&` operator.

  - (Mostly finished) Parameter expansion of `$$`, `$?`, `$!`, and `${param}` with appropriate environment variable values.

  - (Unfinished) Built-in Input/Output redirection operators `<`, `>`, and `>>`.

  - (Unfinished) Custom signal handling of `SIGINT` and `SIGTSTP`

  - Does **not** recognize format specifiers used in the `PS1` environment variable, so the user's prompt output may look odd or not appear. See fix in Usage.

<!-- Usage -->
## Usage

Smallsh provides a command-line interface for users to execute commands. Here are some basic usage examples:

  - Run the shell, then run commands:

    ```bash
    ~/smallsh$ ./smallsh
    $ ls
    file1.txt  file2.txt  file3.txt
    $ echo "Hello, smallsh"
    Hello, smallsh
    ```

  - Run built-in commands:

    - The `cd` command changes the current working directory.
    - The `exit` command can be provided with an optional exit code. Otherwise, the default value is `0`.

    ```bash
    $ cd /path/to/directory
    $ cd ..
    $ exit 2
    ~/smallsh$
    ```

  - Redirect input and output with `<`, `>`, and `>>`:

    ```bash
    $ cat < input.txt
    $ ls > output.txt
    $ echo "Append text" >> output.txt
    ```

  - Parameter expansion of environment variables:

    - **`$$`**: Replaced by the process ID (PID) of the running smallsh program.
    - **`$?`**: Replaced by the exit status of the last foreground command.
    - **`$?`**: Replaced by the process ID of the of the most recent background process.
    - **`${param}`**: Replaced with the value of the corresponding environment variable named `parameter`.

    ```bash
    $ echo "Smallsh PID: $$"
    $ echo "Exit status of last foreground command: $?"
    $ echo "Last background process PID: $!"
    $ echo "Home directory: ${HOME}"
    ```

  - Run a command in the background:

    - Executes in the background, allowing user to continue using the shell without waiting for the command to finish

    ```bash
    $ sleep 10 &
    $ ls
    file1.txt  file2.txt  file3.txt
    $ 
    ```

  - Fix for odd or nonexistent prompt:

    - Alter the value of the `PS1` environment variable in the `.bashrc` file to something more simple (make a backup of your `.bashrc` file before editing).
    - Use a temporary `PS1` variable:
    
    ```bash
    ~/smallsh$ PS1=">>> " ./smallsh
    >>> ls
    file1.txt file2.txt file3.txt
    >>> 
    ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

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