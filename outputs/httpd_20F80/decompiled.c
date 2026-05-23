  // 0X20F80 push {r4, r5, r6, lr}
  mult_addr = sp - 0x4
  *[ram]mult_addr = lr
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r6
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r5
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r4
  mult_addr = mult_addr - 0x4
  sp = mult_addr + 0x4
  // 0X20F84 mov r5, r0
  r5 = r0
  // 0X20F88 ldr r6, [pc, #0xb8]
  r6 = *[ram]0x21048
  // 0X20F8C sub sp, sp, #0x78
  unique_2e80_4 = 0x78 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x78 <= sp
  tmpOV = sborrow(sp, 0x78)
  sp = sp - 0x78
  tmpNG = sp s< 0x0
  tmpZR = sp == 0x0
  // 0X20F90 mov r4, r1
  r4 = r1
  // 0X20F94 ldr r0, [r6, #4]
  unique_8280_4 = r6 + 0x4
  r0 = *[ram]unique_8280_4
  // 0X20F98 cmp r2, #0
  unique_2e80_4 = 0x0 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x0 <= r2
  tmpOV = sborrow(r2, 0x0)
  unique_42800_4 = r2 - 0x0
  tmpNG = unique_42800_4 s< 0x0
  tmpZR = unique_42800_4 == 0x0
  CY = tmpCY
  ZR = tmpZR
  NG = tmpNG
  OV = tmpOV
  // 0X20F9C cmpne r0, #0
  unique_1a80_1 = !ZR
  unique_2680_1 = !unique_1a80_1
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
    // 0X20FA4 bl #0xb25c
    lr = 0x20fa8
    call ram_b25c_4
    // 0X20FA8 mov r3, #0
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
    // 0X20FAC str r3, [r6, #4]
    unique_8280_4 = r6 + 0x4
    *[ram]unique_8280_4 = r3
  }
  // 0X20FB0 ldr r3, [pc, #0x90]
  r3 = *[ram]0x21048
  // 0X20FB4 ldr r3, [r3, #4]
  unique_8280_4 = r3 + 0x4
  r3 = *[ram]unique_8280_4
  // 0X20FB8 cmp r3, #0
  unique_2e80_4 = 0x0 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x0 <= r3
  tmpOV = sborrow(r3, 0x0)
  unique_42800_4 = r3 - 0x0
  tmpNG = unique_42800_4 s< 0x0
  tmpZR = unique_42800_4 == 0x0
  CY = tmpCY
  ZR = tmpZR
  NG = tmpNG
  OV = tmpOV
  // 0X20FBC bne #0x21038
  unique_1a80_1 = !ZR
  if (unique_1a80_1) {
LAB_21038:
    // 0X21038 ldr r3, [pc, #8]
    r3 = *[ram]0x21048
    // 0X2103C ldr r0, [r3, #4]
    unique_8280_4 = r3 + 0x4
    r0 = *[ram]unique_8280_4
    // 0X21040 add sp, sp, #0x78
    unique_2e80_4 = 0x78 >> 0x1f
    unique_2f00_1 = 0x0 == 0x0
    unique_2f80_1 = unique_2f00_1 && CY
    unique_3000_1 = 0x0 != 0x0
    unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
    unique_3100_1 = unique_3000_1 && unique_3080_1
    shift_carry = unique_2f80_1 || unique_3100_1
    tmpCY = carry(sp, 0x78)
    tmpOV = scarry(sp, 0x78)
    sp = sp + 0x78
    tmpNG = sp s< 0x0
    tmpZR = sp == 0x0
    // 0X21044 pop {r4, r5, r6, pc}
    mult_addr = sp
    r4 = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
    r5 = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
    r6 = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
    pc = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
    sp = mult_addr
    unique_0_4 = pc & 0x1
    ISAModeSwitch = unique_0_4 != 0x0
    TB = ISAModeSwitch
    pc = pc & 0xfffffffe
    return pc
  } else {
LAB_20FC0:
    // 0X20FC0 bl #0x4df7c
    lr = 0x20fc4
    call ram_4df7c_4
    // 0X20FC4 cmp r0, #1
    unique_2e80_4 = 0x1 >> 0x1f
    unique_2f00_1 = 0x0 == 0x0
    unique_2f80_1 = unique_2f00_1 && CY
    unique_3000_1 = 0x0 != 0x0
    unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
    unique_3100_1 = unique_3000_1 && unique_3080_1
    shift_carry = unique_2f80_1 || unique_3100_1
    tmpCY = 0x1 <= r0
    tmpOV = sborrow(r0, 0x1)
    unique_42800_4 = r0 - 0x1
    tmpNG = unique_42800_4 s< 0x0
    tmpZR = unique_42800_4 == 0x0
    CY = tmpCY
    ZR = tmpZR
    NG = tmpNG
    OV = tmpOV
    // 0X20FC8 cmpeq r4, #1
    unique_2680_1 = !ZR
    unique_2e80_4 = 0x1 >> 0x1f
    unique_2f00_1 = 0x0 == 0x0
    unique_2f80_1 = unique_2f00_1 && CY
    unique_3000_1 = 0x0 != 0x0
    unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
    unique_3100_1 = unique_3000_1 && unique_3080_1
    shift_carry = unique_2f80_1 || unique_3100_1
    tmpCY = 0x1 <= r4
    tmpOV = sborrow(r4, 0x1)
    unique_42800_4 = r4 - 0x1
    tmpNG = unique_42800_4 s< 0x0
    tmpZR = unique_42800_4 == 0x0
    CY = tmpCY
    ZR = tmpZR
    NG = tmpNG
    OV = tmpOV
    // 0X20FCC bne #0x21008
    unique_1a80_1 = !ZR
    if (!unique_1a80_1) {
      // 0X20FD0 add r6, sp, #0x68
      unique_2e80_4 = 0x68 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      tmpCY = carry(sp, 0x68)
      tmpOV = scarry(sp, 0x68)
      r6 = sp + 0x68
      tmpNG = r6 s< 0x0
      tmpZR = r6 == 0x0
      // 0X20FD4 bl #0x58600
      lr = 0x20fd8
      call ram_58600_4
      // 0X20FD8 mov r1, r6
      r1 = r6
      // 0X20FDC mov r0, r5
      r0 = r5
      // 0X20FE0 add r5, sp, #4
      unique_2e80_4 = 0x4 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      tmpCY = carry(sp, 0x4)
      tmpOV = scarry(sp, 0x4)
      r5 = sp + 0x4
      tmpNG = r5 s< 0x0
      tmpZR = r5 == 0x0
      // 0X20FE4 bl #0xb3cf8
      lr = 0x20fe8
      call ram_b3cf8_4
      // 0X20FE8 bl #0xa61e0
      lr = 0x20fec
      call ram_a61e0_4
      // 0X20FEC ldr r1, [pc, #0x58]
      r1 = *[ram]0x2104c
      // 0X20FF0 mov r2, r0
      r2 = r0
      // 0X20FF4 mov r3, r6
      r3 = r6
      // 0X20FF8 mov r0, r5
      r0 = r5
      // 0X20FFC bl #0xb0e8
      lr = 0x21000
      call ram_b0e8_4
      // 0X21000 mov r0, r5
      r0 = r5
      // 0X21004 bl #0xaa1c
      lr = 0x21008
      call ram_aa1c_4
    }
    // 0X21008 mov r0, r4
    r0 = r4
    // 0X2100C bl #0x20ef8
    lr = 0x21010
    call ram_20ef8_4
    // 0X21010 bl #0xaba8
    lr = 0x21014
    call ram_aba8_4
    // 0X21014 ldr r3, [pc, #0x2c]
    r3 = *[ram]0x21048
    // 0X21018 mov r5, r0
    r5 = r0
    // 0X2101C str r0, [r3, #4]
    unique_8280_4 = r3 + 0x4
    *[ram]unique_8280_4 = r0
    // 0X21020 mov r0, r4
    r0 = r4
    // 0X21024 bl #0x20ef8
    lr = 0x21028
    call ram_20ef8_4
    // 0X21028 mov r1, #0
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
    // 0X2102C mov r2, r0
    r2 = r0
    // 0X21030 mov r0, r5
    r0 = r5
    // 0X21034 bl #0xb004
    lr = 0x21038
    call ram_b004_4
LAB_21038:
    // 0X21038 ldr r3, [pc, #8]
    r3 = *[ram]0x21048
    // 0X2103C ldr r0, [r3, #4]
    unique_8280_4 = r3 + 0x4
    r0 = *[ram]unique_8280_4
    // 0X21040 add sp, sp, #0x78
    unique_2e80_4 = 0x78 >> 0x1f
    unique_2f00_1 = 0x0 == 0x0
    unique_2f80_1 = unique_2f00_1 && CY
    unique_3000_1 = 0x0 != 0x0
    unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
    unique_3100_1 = unique_3000_1 && unique_3080_1
    shift_carry = unique_2f80_1 || unique_3100_1
    tmpCY = carry(sp, 0x78)
    tmpOV = scarry(sp, 0x78)
    sp = sp + 0x78
    tmpNG = sp s< 0x0
    tmpZR = sp == 0x0
    // 0X21044 pop {r4, r5, r6, pc}
    mult_addr = sp
    r4 = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
    r5 = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
    r6 = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
    pc = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
    sp = mult_addr
    unique_0_4 = pc & 0x1
    ISAModeSwitch = unique_0_4 != 0x0
    TB = ISAModeSwitch
    pc = pc & 0xfffffffe
    return pc
  }
