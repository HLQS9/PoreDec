  // 0X20814 push {r4, r5, lr}
  mult_addr = sp - 0x4
  *[ram]mult_addr = lr
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r5
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r4
  mult_addr = mult_addr - 0x4
  sp = mult_addr + 0x4
  // 0X20818 sub sp, sp, #0x14
  unique_2e80_4 = 0x14 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x14 <= sp
  tmpOV = sborrow(sp, 0x14)
  sp = sp - 0x14
  tmpNG = sp s< 0x0
  tmpZR = sp == 0x0
  // 0X2081C mov r2, #0x10
  unique_2e80_4 = 0x10 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  r2 = 0x10
  tmpNG = r2 s< 0x0
  tmpZR = r2 == 0x0
  tmpCY = shift_carry
  tmpOV = OV
  // 0X20820 mov r5, r0
  r5 = r0
  // 0X20824 mov r1, #0
  unique_2e80_4 = 0x0 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  r1 = 0x0
  tmpNG = r1 s< 0x0
  tmpZR = r1 == 0x0
  tmpCY = shift_carry
  tmpOV = OV
  // 0X20828 mov r0, sp
  r0 = sp
  // 0X2082C bl #0xb004
  lr = 0x20830
  call ram_b004_4
  // 0X20830 mov r1, sp
  r1 = sp
  // 0X20834 mov r0, r5
  r0 = r5
  // 0X20838 bl #0xb3cf8
  lr = 0x2083c
  call ram_b3cf8_4
  // 0X2083C mov r0, sp
  r0 = sp
  // 0X20840 mov r4, sp
  r4 = sp
  // 0X20844 bl #0x4d530
  lr = 0x20848
  call ram_4d530_4
  // 0X20848 cmp r0, #0
  unique_2e80_4 = 0x0 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x0 <= r0
  tmpOV = sborrow(r0, 0x0)
  unique_42800_4 = r0 - 0x0
  tmpNG = unique_42800_4 s< 0x0
  tmpZR = unique_42800_4 == 0x0
  CY = tmpCY
  ZR = tmpZR
  NG = tmpNG
  OV = tmpOV
  if (!ZR) {
    // 0X20850 mov r0, sp
    r0 = sp
    // 0X20854 bl #0xb07c
    lr = 0x20858
    call ram_b07c_4
    // 0X20858 bl #0x4e87c
    lr = 0x2085c
    call ram_4e87c_4
    // 0X2085C sxth r0, r0
    unique_7100_4 = r0
    r0 = sext(unique_7100_2)
  }
  // 0X20860 add sp, sp, #0x14
  unique_2e80_4 = 0x14 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = carry(sp, 0x14)
  tmpOV = scarry(sp, 0x14)
  sp = sp + 0x14
  tmpNG = sp s< 0x0
  tmpZR = sp == 0x0
  // 0X20864 pop {r4, r5, pc}
  mult_addr = sp
  r4 = *[ram]mult_addr
  mult_addr = mult_addr + 0x4
  r5 = *[ram]mult_addr
  mult_addr = mult_addr + 0x4
  pc = *[ram]mult_addr
  mult_addr = mult_addr + 0x4
  sp = mult_addr
  unique_0_4 = pc & 0x1
  ISAModeSwitch = unique_0_4 != 0x0
  TB = ISAModeSwitch
  pc = pc & 0xfffffffe
  return pc
