  // 0X10420 push {fp, lr}
  mult_addr = sp - 0x4
  *[ram]mult_addr = lr
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r11
  mult_addr = mult_addr - 0x4
  sp = mult_addr + 0x4
  // 0X10424 add fp, sp, #4
  unique_2e80_4 = 0x4 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = carry(sp, 0x4)
  tmpOV = scarry(sp, 0x4)
  r11 = sp + 0x4
  tmpNG = r11 s< 0x0
  tmpZR = r11 == 0x0
  // 0X10428 sub sp, sp, #8
  unique_2e80_4 = 0x8 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x8 <= sp
  tmpOV = sborrow(sp, 0x8)
  sp = sp - 0x8
  tmpNG = sp s< 0x0
  tmpZR = sp == 0x0
  // 0X1042C str r0, [fp, #-8]
  unique_8380_4 = r11 + 0xfffffff8
  *[ram]unique_8380_4 = r0
  // 0X10430 str r1, [fp, #-0xc]
  unique_8380_4 = r11 + 0xfffffff4
  *[ram]unique_8380_4 = r1
  // 0X10434 ldr r0, [pc, #0xc]
  r0 = *[ram]0x10448
  // 0X10438 bl #0x10304
  lr = 0x1043c
  call ram_10304_4
  while (1) {
    // 0X1043C ldr r0, [pc, #8]
    r0 = *[ram]0x1044c
    // 0X10440 bl #0x10304
    lr = 0x10444
    call ram_10304_4
  }
