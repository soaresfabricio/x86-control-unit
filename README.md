### Description

As part of a homework assignment for my Computer Architecture course, I was asked to develop a small [control unit](https://en.wikipedia.org/wiki/Control_unit) simulator capable of running some self-created assembly language. I started it up with a [GAS inspired syntax](https://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax) and later decided to build a full parser around it. 

#### Features

- **7 registers**: "eax", "ebp", "esp", "eip", "edx", "ebx" and "ecx";
- **20 opcodes**: "addl", "andl", "leave", "movl", "pushl", "ret", "subl", "cmpl", "incl", "jg", "jle", "jmp", "leal", "call", "sall", "decl", "imull", "nop", "jl", "jge";
- Dumping of stack (memory) and register to .txt files by the end of execution;
- Counting of the number of cycles.

#### How to run it

You must have [cmake](https://cmake.org) and a C++ compiler installed. `cd` into the folder that contains this cloned repository and run the following command on a terminal:

```sh
$ cmake .
```

#### How to get generate compatible assembly

Although some examples are to be found on the `samples` folder, you can easily use some piece of C code and a C compiler (like GCC) to generate some assembly that will (*most likely*) run on this simulator. For a file named `input.c`, this can be done through the following command:

```shell
gcc -S -m32 -fno-leading-underscore input.c
```

`-m32` generates code with only x86 opcodes and `-fno-leading-underscore` will remove underscore from the beginning of directives and labels (some compilers may have it turned on by default).

------

Have fun!