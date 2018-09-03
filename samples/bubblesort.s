main:
  pushl %ebp
  movl %esp, %ebp
  subl $64, %esp
  movl $1, -56(%ebp)
  movl $4, -52(%ebp)
  movl $2, -48(%ebp)
  movl $3, -44(%ebp)
  movl $10, -40(%ebp)
  movl $7, -36(%ebp)
  movl $5, -32(%ebp)
  movl $9, -28(%ebp)
  movl $8, -24(%ebp)
  movl $6, -20(%ebp)
  movl $10, -12(%ebp)
  movl $0, -4(%ebp)
  jmp .L2
.L6:
  movl -4(%ebp), %eax
  addl $1, %eax
  movl %eax, -8(%ebp)
  jmp .L3
.L5:
  movl -4(%ebp), %eax
  movl -56(%ebp,%eax,4), %edx
  movl -8(%ebp), %eax
  movl -56(%ebp,%eax,4), %eax
  cmpl %eax, %edx
  jle .L4
  movl -4(%ebp), %eax
  movl -56(%ebp,%eax,4), %eax
  movl %eax, -16(%ebp)
  movl -8(%ebp), %eax
  movl -56(%ebp,%eax,4), %edx
  movl -4(%ebp), %eax
  movl %edx, -56(%ebp,%eax,4)
  movl -8(%ebp), %eax
  movl -16(%ebp), %edx
  movl %edx, -56(%ebp,%eax,4)
.L4:
  addl $1, -8(%ebp)
.L3:
  movl -8(%ebp), %eax
  cmpl -12(%ebp), %eax
  jl .L5
  addl $1, -4(%ebp)
.L2:
  movl -4(%ebp), %eax
  cmpl -12(%ebp), %eax
  jl .L6
  movl -56(%ebp), %eax
  leave
  ret