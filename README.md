# The calc Programming Language

This is the main repository for the **calc** programming language and its tools,
documentation and standard library.

## Goals and Principles

The main goal of the **calc** project is to design and develop a programming
language able to represent in an efficent and syntactically good-looking way
mathematical models, problems and algorithm, ensuring high-level abstraction
mechanisms, portability, memory safety and efficiency, capable to produce
optimized and performance-critical software.

Another big goal of this project is to implement, natively, interoperation with
programs and libraries written in **C** and **C++**, to ensure the possibility
of integrate **calc** project in alredy-existent **C**/**C++** projects.

> NOTE: Achivement of these goals will be the last step of the experimental
> phase of the **calc** programming language. Until that moment the language
> will go through many and radical changes.

The language will be designed following these principles and paradigms:
  - ***Imperative***, the programmer have the control of the machine *by the
    program*, if something can be done, the programmer can do it, with effects
    and consequences, but without explicit limitations (only suggestions).
  - ***Functional***, each problem has sub-problems that can be divided into
    small sequences of actions, some actions influencing the others by modifying
    or completing them.
  - ***Objective***, each concrete problem can be abstracted into a virtual,
    decomposable and composable representation, which can evolve during execution,
    bringing with it its own information about the problem to be solved.
  - ***Modular***, each solved problem contains the solution, which can be used
    by other more complex problems to avoid ‘reinventing the wheel’.

Some of those principles and paradigms can sometimes collide, but a programmer
shouldn't have more ways to do the same thing in the same way, so each concept
of **calc** has its own meaning and narrow support for what the concept is for:
*functions* are tools to transform data and informations, *objects* are instantiable
containers of *methods* related to *attributes*, *modules* are independent or
dependent components that can be used by a program to recycle code and other
constructions like *control flows*, *structures*, *enumerations* and *unions* serves
to organize code, data and informations.
