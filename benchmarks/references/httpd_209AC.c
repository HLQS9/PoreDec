  // 0X209AC push {r4, r5, r6, r7, lr}
  mult_addr = sp - 0x4
  *[ram]mult_addr = lr
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r7
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r6
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r5
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r4
  mult_addr = mult_addr - 0x4
  sp = mult_addr + 0x4
  // 0X209B0 mov r6, r0
  r6 = r0
  // 0X209B4 sub sp, sp, #0x14
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
  // 0X209B8 mov r7, r1
  r7 = r1
  // 0X209BC mov r5, r1
  r5 = r1
  // 0X209C0 ldr r4, [pc, #0xe8]
  r4 = *[ram]0x20ab0
  while (1) {
    // 0X20A94 ldrb r3, [r6]
    unique_8280_4 = r6 + 0x0
    unique_43880_1 = *[ram]unique_8280_4
    r3 = zext(unique_43880_1)
    // 0X20A98 cmp r3, #0
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
    // 0X20A9C bne #0x209c8
    unique_1a80_1 = !ZR
    if (unique_1a80_1) {
      // 0X209C8 mov r1, #0
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
      // 0X209CC mov r3, r1
      r3 = r1
      do {
        // 0X209D0 ldrb r2, [r6]
        unique_8280_4 = r6 + 0x0
        unique_43880_1 = *[ram]unique_8280_4
        r2 = zext(unique_43880_1)
        // 0X209D4 add r0, sp, #0xc
        unique_2e80_4 = 0xc >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        tmpCY = carry(sp, 0xc)
        tmpOV = scarry(sp, 0xc)
        r0 = sp + 0xc
        tmpNG = r0 s< 0x0
        tmpZR = r0 == 0x0
        // 0X209D8 cmp r2, #0
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
        // 0X209DC strbne r2, [r0, r3]
        unique_1a80_1 = !ZR
        unique_2680_1 = !unique_1a80_1
        unique_8480_4 = r0 + r3
        unique_70c00_1 = SUBPIECE r2, 0x0
        *[ram]unique_8480_4 = unique_70c00_1
        // 0X209E0 addne r1, r1, #1
        unique_1a80_1 = !ZR
        unique_2680_1 = !unique_1a80_1
        unique_2e80_4 = 0x1 >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        tmpCY = carry(r1, 0x1)
        tmpOV = scarry(r1, 0x1)
        r1 = r1 + 0x1
        tmpNG = r1 s< 0x0
        tmpZR = r1 == 0x0
        // 0X209E4 strbeq r2, [r0, r3]
        unique_2680_1 = !ZR
        unique_8480_4 = r0 + r3
        unique_70c00_1 = SUBPIECE r2, 0x0
        *[ram]unique_8480_4 = unique_70c00_1
        // 0X209E8 add r3, r3, #1
        unique_2e80_4 = 0x1 >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        tmpCY = carry(r3, 0x1)
        tmpOV = scarry(r3, 0x1)
        r3 = r3 + 0x1
        tmpNG = r3 s< 0x0
        tmpZR = r3 == 0x0
        // 0X209EC addne r6, r6, #1
        unique_1a80_1 = !ZR
        unique_2680_1 = !unique_1a80_1
        unique_2e80_4 = 0x1 >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        tmpCY = carry(r6, 0x1)
        tmpOV = scarry(r6, 0x1)
        r6 = r6 + 0x1
        tmpNG = r6 s< 0x0
        tmpZR = r6 == 0x0
        // 0X209F0 cmp r3, #3
        unique_2e80_4 = 0x3 >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        tmpCY = 0x3 <= r3
        tmpOV = sborrow(r3, 0x3)
        unique_42800_4 = r3 - 0x3
        tmpNG = unique_42800_4 s< 0x0
        tmpZR = unique_42800_4 == 0x0
        CY = tmpCY
        ZR = tmpZR
        NG = tmpNG
        OV = tmpOV
        // 0X209F4 bne #0x209d0
        unique_1a80_1 = !ZR
      } while (unique_1a80_1);
      // 0X209F8 ldrb ip, [sp, #0xd]
      unique_8280_4 = sp + 0xd
      unique_43880_1 = *[ram]unique_8280_4
      r12 = zext(unique_43880_1)
      // 0X209FC cmp r1, #1
      unique_2e80_4 = 0x1 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      tmpCY = 0x1 <= r1
      tmpOV = sborrow(r1, 0x1)
      unique_42800_4 = r1 - 0x1
      tmpNG = unique_42800_4 s< 0x0
      tmpZR = unique_42800_4 == 0x0
      CY = tmpCY
      ZR = tmpZR
      NG = tmpNG
      OV = tmpOV
      // 0X20A00 ldrb r3, [sp, #0xc]
      unique_8280_4 = sp + 0xc
      unique_43880_1 = *[ram]unique_8280_4
      r3 = zext(unique_43880_1)
      // 0X20A04 lsr r0, ip, #4
      unique_3800_4 = 0x4 - 0x1
      unique_3880_4 = r12 >> unique_3800_4
      unique_3980_4 = unique_3880_4 & 0x1
      shift_carry = SUBPIECE unique_3980_4, 0x0
      unique_3b00_4 = r12 >> 0x4
      r0 = unique_3b00_4
      tmpNG = r0 s< 0x0
      tmpZR = r0 == 0x0
      tmpCY = shift_carry
      tmpOV = OV
      // 0X20A08 and ip, ip, #0xf
      unique_2e80_4 = 0xf >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      r12 = r12 & 0xf
      tmpCY = shift_carry
      tmpOV = OV
      tmpNG = r12 s< 0x0
      tmpZR = r12 == 0x0
      // 0X20A0C lsr r2, r3, #2
      unique_3800_4 = 0x2 - 0x1
      unique_3880_4 = r3 >> unique_3800_4
      unique_3980_4 = unique_3880_4 & 0x1
      shift_carry = SUBPIECE unique_3980_4, 0x0
      unique_3b00_4 = r3 >> 0x2
      r2 = unique_3b00_4
      tmpNG = r2 s< 0x0
      tmpZR = r2 == 0x0
      tmpCY = shift_carry
      tmpOV = OV
      // 0X20A10 and r3, r3, #3
      unique_2e80_4 = 0x3 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      r3 = r3 & 0x3
      tmpCY = shift_carry
      tmpOV = OV
      tmpNG = r3 s< 0x0
      tmpZR = r3 == 0x0
      // 0X20A14 orr r3, r0, r3, lsl #4
      unique_3280_4 = 0x20 - 0x4
      unique_3300_4 = r3 >> unique_3280_4
      unique_3400_4 = unique_3300_4 & 0x1
      shift_carry = SUBPIECE unique_3400_4, 0x0
      unique_3580_4 = r3 << 0x4
      r3 = r0 | unique_3580_4
      tmpCY = shift_carry
      tmpOV = OV
      tmpNG = r3 s< 0x0
      tmpZR = r3 == 0x0
      // 0X20A18 ldrb r0, [sp, #0xe]
      unique_8280_4 = sp + 0xe
      unique_43880_1 = *[ram]unique_8280_4
      r0 = zext(unique_43880_1)
      // 0X20A1C lsr lr, r0, #6
      unique_3800_4 = 0x6 - 0x1
      unique_3880_4 = r0 >> unique_3800_4
      unique_3980_4 = unique_3880_4 & 0x1
      shift_carry = SUBPIECE unique_3980_4, 0x0
      unique_3b00_4 = r0 >> 0x6
      lr = unique_3b00_4
      tmpNG = lr s< 0x0
      tmpZR = lr == 0x0
      tmpCY = shift_carry
      tmpOV = OV
      // 0X20A20 orr ip, lr, ip, lsl #2
      unique_3280_4 = 0x20 - 0x2
      unique_3300_4 = r12 >> unique_3280_4
      unique_3400_4 = unique_3300_4 & 0x1
      shift_carry = SUBPIECE unique_3400_4, 0x0
      unique_3580_4 = r12 << 0x2
      r12 = lr | unique_3580_4
      tmpCY = shift_carry
      tmpOV = OV
      tmpNG = r12 s< 0x0
      tmpZR = r12 == 0x0
      if (ZR) {
        // 0X20A34 mov r0, r5
        r0 = r5
        // 0X20A38 ldr r1, [pc, #0x74]
        r1 = *[ram]0x20ab4
        // 0X20A3C ldrb r2, [r4, r2]
        unique_8480_4 = r4 + r2
        unique_43880_1 = *[ram]unique_8480_4
        r2 = zext(unique_43880_1)
        // 0X20A40 ldrb r3, [r4, r3]
        unique_8480_4 = r4 + r3
        unique_43880_1 = *[ram]unique_8480_4
        r3 = zext(unique_43880_1)
        // 0X20A44 bl #0xb0e8
        lr = 0x20a48
        call ram_b0e8_4
      } else {
        // 0X20A28 cmp r1, #2
        unique_2e80_4 = 0x2 >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        tmpCY = 0x2 <= r1
        tmpOV = sborrow(r1, 0x2)
        unique_42800_4 = r1 - 0x2
        tmpNG = unique_42800_4 s< 0x0
        tmpZR = unique_42800_4 == 0x0
        CY = tmpCY
        ZR = tmpZR
        NG = tmpNG
        OV = tmpOV
        // 0X20A2C bne #0x20a68
        unique_1a80_1 = !ZR
        if (unique_1a80_1) {
          // 0X20A68 ldrb r1, [r4, ip]
          unique_8480_4 = r4 + r12
          unique_43880_1 = *[ram]unique_8480_4
          r1 = zext(unique_43880_1)
          // 0X20A6C and r0, r0, #0x3f
          unique_2e80_4 = 0x3f >> 0x1f
          unique_2f00_1 = 0x0 == 0x0
          unique_2f80_1 = unique_2f00_1 && CY
          unique_3000_1 = 0x0 != 0x0
          unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
          unique_3100_1 = unique_3000_1 && unique_3080_1
          shift_carry = unique_2f80_1 || unique_3100_1
          r0 = r0 & 0x3f
          tmpCY = shift_carry
          tmpOV = OV
          tmpNG = r0 s< 0x0
          tmpZR = r0 == 0x0
          // 0X20A70 ldrb r2, [r4, r2]
          unique_8480_4 = r4 + r2
          unique_43880_1 = *[ram]unique_8480_4
          r2 = zext(unique_43880_1)
          // 0X20A74 ldrb r3, [r4, r3]
          unique_8480_4 = r4 + r3
          unique_43880_1 = *[ram]unique_8480_4
          r3 = zext(unique_43880_1)
          // 0X20A78 str r1, [sp]
          unique_8280_4 = sp + 0x0
          *[ram]unique_8280_4 = r1
          // 0X20A7C ldrb r1, [r4, r0]
          unique_8480_4 = r4 + r0
          unique_43880_1 = *[ram]unique_8480_4
          r1 = zext(unique_43880_1)
          // 0X20A80 mov r0, r5
          r0 = r5
          // 0X20A84 str r1, [sp, #4]
          unique_8280_4 = sp + 0x4
          *[ram]unique_8280_4 = r1
          // 0X20A88 ldr r1, [pc, #0x2c]
          r1 = *[ram]0x20abc
        } else {
          // 0X20A4C ldrb r1, [r4, ip]
          unique_8480_4 = r4 + r12
          unique_43880_1 = *[ram]unique_8480_4
          r1 = zext(unique_43880_1)
          // 0X20A50 mov r0, r5
          r0 = r5
          // 0X20A54 ldrb r2, [r4, r2]
          unique_8480_4 = r4 + r2
          unique_43880_1 = *[ram]unique_8480_4
          r2 = zext(unique_43880_1)
          // 0X20A58 ldrb r3, [r4, r3]
          unique_8480_4 = r4 + r3
          unique_43880_1 = *[ram]unique_8480_4
          r3 = zext(unique_43880_1)
          // 0X20A5C str r1, [sp]
          unique_8280_4 = sp + 0x0
          *[ram]unique_8280_4 = r1
          // 0X20A60 ldr r1, [pc, #0x50]
          r1 = *[ram]0x20ab8
        }
        // 0X20A8C bl #0xb0e8
        lr = 0x20a90
        call ram_b0e8_4
      }
      // 0X20A90 add r5, r5, #4
      unique_2e80_4 = 0x4 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      tmpCY = carry(r5, 0x4)
      tmpOV = scarry(r5, 0x4)
      r5 = r5 + 0x4
      tmpNG = r5 s< 0x0
      tmpZR = r5 == 0x0
      continue
    }
    // 0X20AA0 strb r3, [r5]
    unique_8280_4 = r5 + 0x0
    unique_70c00_1 = SUBPIECE r3, 0x0
    *[ram]unique_8280_4 = unique_70c00_1
    // 0X20AA4 rsb r0, r7, r5
    shift_carry = CY
    tmpCY = r7 <= r5
    tmpOV = sborrow(r5, r7)
    r0 = r5 - r7
    tmpNG = r0 s< 0x0
    tmpZR = r0 == 0x0
    // 0X20AA8 add sp, sp, #0x14
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
    // 0X20AAC pop {r4, r5, r6, r7, pc}
    mult_addr = sp
    r4 = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
    r5 = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
    r6 = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
    r7 = *[ram]mult_addr
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
