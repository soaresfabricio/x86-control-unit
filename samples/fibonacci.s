fib:
  pushl %ebp
  movl %esp, %ebp
  pushl %ebx
  subl $4, %esp
  cmpl $1, 8(%ebp)
  jg .L2
  movl $1, %eax
  jmp .L3
.L2:
  movl 8(%ebp), %eax
  subl $1, %eax
  subl $12, %esp
  pushl %eax
  call fib
  addl $16, %esp
  movl %eax, %ebx
  movl 8(%ebp), %eax
  subl $2, %eax
  subl $12, %esp
  pushl %eax
  call fib
  addl $16, %esp
  addl %ebx, %eax
.L3:
  movl -4(%ebp), %ebx
  leave
  ret
main:
  leal 4(%esp), %ecx
  andl $-16, %esp
  pushl -4(%ecx)
  pushl %ebp
  movl %esp, %ebp
  pushl %ecx
  subl $20, %esp
  movl $5, -12(%ebp)
  subl $12, %esp
  pushl -12(%ebp)
  call fib
  addl $16, %esp
  movl %eax, -16(%ebp)
  subl $12, %esp
  pushl $1
  call fib
  addl $16, %esp
  movl %eax, -20(%ebp)
  movl -16(%ebp), %edx
  movl -20(%ebp), %eax
  addl %eax, %edx
  movl -12(%ebp), %eax
  addl %edx, %eax
  movl -4(%ebp), %ecx
  leave
  leal -4(%ecx), %esp
  ret