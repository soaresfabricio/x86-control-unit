main:
  pushl %ebp
  movl %esp, %ebp
  subl $16, %esp
  movl $197, -4(%ebp)
  movl -4(%ebp), %eax
  addl $8, %eax
  movl %eax, -8(%ebp)
  movl -8(%ebp), %eax
  subl $4, %eax
  movl %eax, -12(%ebp)
  movl -8(%ebp), %eax
  leave
  ret