<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>

<!-- Centered title section with descriptive lines -->
<div align="center">
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
    - [Highlight 1](#highlight-1)
    - [Highlight 2](#highlight-2)
  - [Skills Used](#skills-used)
    - [Skill 1](#skill-1)
    - [Skill 2](#skill-2)
  - [References](#references)

</details>

## Project Description
This project is a UNIX-like command line shell written in the C programming language and designed to operate like well-known shells like bash. Smallsh is designed to perform common shell functions such as parsing commands, executing processes, and managing background tasks.

## Technologies Used
  - [![C-language][C-language]][C-language-url]
  - [![vim][vim]][vim-url]
  - [![C-99-std][C-99-std]][C-99-std-url]
  - [![Std-lib][Std-lib]][Std-lib-url]
  - [![Sys-calls][Sys-calls]][Sys-calls-url]

## Features
  - Provides an interactive command line interface for users to interact with.

  - Built-in commands `exit` and `cd`.

  - Built-in Input/output redirection with `<`, `>`, and `>>`.

  - Handles non-built-in commands using the appropriate `exec` functions.

  - Parameter expansion of `$$`, `$!`, `$$`, and `${param}` with appropriate values.

  - Run commands in the background using the `&` operator.

  - Customizable shell prompt using the `PS1` environment variable.

## Roadmap
Need to add or improve:
    
  - Input/Output Redirection needs fixing.
    
  - Checking for any un-waited for background processes.

  - Custom signal handling of `SIGINT` and `SIGTSTP`.
 

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Usage
Smallsh provides a command-line interface for users to execute commands. Here are some basic usage examples:

  - First, run the shell:
    ```
    ./smallsh
    ```

  - Run a command:
    ```
    $ ls -l
    ```

  - Redirect input and output:
    ```
    $ cat input.txt > output.txt
    ```

  - Run a command in the background:
    ```
    $ sleep 10 &
    ```

  - Change the current working directory:
    ```
    $ cd /path/to/directory
    ```

  - Exit the shell:
    ```
    $ exit
    ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Skills Used
#### Skill 1:
  - description
#### Skill 2:
  - description

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Author

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## References

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Markdown links -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[C-language]: https://img.shields.io/badge/Language-grey?style=for-the-badge&logo=c&logoColor=#A8B9CC
[C-language-url]: https://en.cppreference.com/

[vim]:https://img.shields.io/badge/Vim-grey?style=for-the-badge&logo=vim&logoColor=019733
[vim-url]: https://www.vim.org/

[C-99-std]: https://img.shields.io/badge/Standard_C99_(gcc)-grey?style=for-the-badge
[C-99-std-url]: https://en.cppreference.com/w/c/99

[std-lib]: https://img.shields.io/badge/C_Standard_Library-grey?style=for-the-badge
[std-lib-url]:https://en.cppreference.com/w/c/header

[Sys-calls]: https://img.shields.io/badge/System_Calls-grey?style=for-the-badge
[Sys-calls-url]: https://man7.org/linux/man-pages/man2/syscalls.2.html