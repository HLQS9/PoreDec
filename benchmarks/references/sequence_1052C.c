  // 0X1052C push {fp, lr}
  mult_addr = sp - 0x4
  *[ram]mult_addr = lr
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r11
  mult_addr = mult_addr - 0x4
  sp = mult_addr + 0x4
  // 0X10530 add fp, sp, #4
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
  // 0X10534 sub sp, sp, #0x20
  unique_2e80_4 = 0x20 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x20 <= sp
  tmpOV = sborrow(sp, 0x20)
  sp = sp - 0x20
  tmpNG = sp s< 0x0
  tmpZR = sp == 0x0
  // 0X10538 str r0, [fp, #-0x20]
  unique_8380_4 = r11 + 0xffffffe0
  *[ram]unique_8380_4 = r0
  // 0X1053C str r1, [fp, #-0x24]
  unique_8380_4 = r11 + 0xffffffdc
  *[ram]unique_8380_4 = r1
  // 0X10540 ldr r3, [pc, #0x6c]
  r3 = *[ram]0x105b4
  // 0X10544 ldr r3, [r3]
  unique_8280_4 = r3 + 0x0
  r3 = *[ram]unique_8280_4
  // 0X10548 str r3, [fp, #-8]
  unique_8380_4 = r11 + 0xfffffff8
  *[ram]unique_8380_4 = r3
  // 0X1054C mov r3, #0
  unique_2e80_4 = 0x0 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  r3 = 0x0
  tmpNG = r3 s< 0x0
  tmpZR = r3 == 0x0
  tmpCY = shift_carry
  tmpOV = OV
  // 0X10550 ldr r0, [pc, #0x60]
  r0 = *[ram]0x105b8
  // 0X10554 bl #0x10404
  lr = 0x10558
  call ram_10404_4
  // 0X10558 ldr r3, [pc, #0x5c]
  r3 = *[ram]0x105bc
  // 0X1055C sub ip, fp, #0x18
  unique_2e80_4 = 0x18 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x18 <= r11
  tmpOV = sborrow(r11, 0x18)
  r12 = r11 - 0x18
  tmpNG = r12 s< 0x0
  tmpZR = r12 == 0x0
  // 0X10560 ldm r3, {r0, r1, r2, r3}
  mult_addr = r3
  r0 = *[ram]mult_addr
  mult_addr = mult_addr + 0x4
  r1 = *[ram]mult_addr
  mult_addr = mult_addr + 0x4
  r2 = *[ram]mult_addr
  mult_addr = mult_addr + 0x4
  r3 = *[ram]mult_addr
  mult_addr = mult_addr + 0x4
  // 0X10564 stm ip, {r0, r1, r2, r3}
  mult_addr = r12
  *[ram]mult_addr = r0
  mult_addr = mult_addr + 0x4
  *[ram]mult_addr = r1
  mult_addr = mult_addr + 0x4
  *[ram]mult_addr = r2
  mult_addr = mult_addr + 0x4
  *[ram]mult_addr = r3
  mult_addr = mult_addr + 0x4
  // 0X10568 ldr r3, [pc, #0x50]
  r3 = *[ram]0x105c0
  // 0X1056C ldr r2, [r3]
  unique_8280_4 = r3 + 0x0
  r2 = *[ram]unique_8280_4
  // 0X10570 sub r3, fp, #0x18
  unique_2e80_4 = 0x18 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x18 <= r11
  tmpOV = sborrow(r11, 0x18)
  r3 = r11 - 0x18
  tmpNG = r3 s< 0x0
  tmpZR = r3 == 0x0
  // 0X10574 mov r1, r3
  r1 = r3
  // 0X10578 ldr r0, [pc, #0x44]
  r0 = *[ram]0x105c4
  // 0X1057C bl #0x1041c
  lr = 0x10580
  call ram_1041c_4
  // 0X10580 ldr r0, [pc, #0x40]
  r0 = *[ram]0x105c8
  // 0X10584 bl #0x10404
  lr = 0x10588
  call ram_10404_4
  // 0X10588 mov r3, #0
  unique_2e80_4 = 0x0 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  r3 = 0x0
  tmpNG = r3 s< 0x0
  tmpZR = r3 == 0x0
  tmpCY = shift_carry
  tmpOV = OV
  // 0X1058C ldr r2, [pc, #0x20]
  r2 = *[ram]0x105b4
  // 0X10590 ldr r1, [r2]
  unique_8280_4 = r2 + 0x0
  r1 = *[ram]unique_8280_4
  // 0X10594 ldr r2, [fp, #-8]
  unique_8380_4 = r11 + 0xfffffff8
  r2 = *[ram]unique_8380_4
  // 0X10598 eors r1, r2, r1
  shift_carry = CY
  r1 = r2 ^ r1
  tmpCY = shift_carry
  tmpOV = OV
  tmpNG = r1 s< 0x0
  tmpZR = r1 == 0x0
  CY = tmpCY
  ZR = tmpZR
  NG = tmpNG
  OV = tmpOV
  // 0X1059C mov r2, #0
  unique_2e80_4 = 0x0 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  r2 = 0x0
  tmpNG = r2 s< 0x0
  tmpZR = r2 == 0x0
  tmpCY = shift_carry
  tmpOV = OV
  if (!ZR) {
    // 0X105A4 bl #0x103f8
    lr = 0x105a8
    call ram_103f8_4
  }
  // 0X105A8 mov r0, r3
  r0 = r3
  // 0X105AC sub sp, fp, #4
  unique_2e80_4 = 0x4 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x4 <= r11
  tmpOV = sborrow(r11, 0x4)
  sp = r11 - 0x4
  tmpNG = sp s< 0x0
  tmpZR = sp == 0x0
  // 0X105B0 pop {fp, pc}
  mult_addr = sp
  r11 = *[ram]mult_addr
  mult_addr = mult_addr + 0x4
  pc = *[ram]mult_addr
  mult_addr = mult_addr + 0x4
  sp = mult_addr
  unique_0_4 = pc & 0x1
  ISAModeSwitch = unique_0_4 != 0x0
  TB = ISAModeSwitch
  pc = pc & 0xfffffffe
  return pc
