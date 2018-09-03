main:
  pushl %ebp
  movl %esp, %ebp
  subl $32, %esp
  movl $10, -24(%ebp)
  movl $11, -20(%ebp)
  movl $12, -16(%ebp)
  movl $197, -12(%ebp)
  cmpl $99, -12(%ebp)
  jg .L2
  movl $134, -4(%ebp)
  jmp .L3
.L2:
  movl $26, -4(%ebp)
.L3:
  movl $0, -8(%ebp)
  jmp .L4
.L5:
  movl -12(%ebp), %edx
  movl -4(%ebp), %eax
  addl %eax, %edx
  movl -8(%ebp), %eax
  movl %edx, -24(%ebp,%eax,4)
  addl $1, -8(%ebp)
.L4:
  cmpl $2, -8(%ebp)
  jle .L5
  movl -16(%ebp), %eax
  addl $18, %eax
  movl %eax, -12(%ebp)
  movl -4(%ebp), %eax
  leave
  ret