  // 0X21974 push {r3, r4, r5, lr}
  mult_addr = sp - 0x4
  *[ram]mult_addr = lr
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r5
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r4
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r3
  mult_addr = mult_addr - 0x4
  sp = mult_addr + 0x4
  // 0X21978 mov r4, r0
  r4 = r0
  // 0X2197C ldr r0, [pc, #0x40]
  r0 = *[ram]0x219c4
  // 0X21980 mov r5, r1
  r5 = r1
  // 0X21984 bl #0xb31c
  lr = 0x21988
  call ram_b31c_4
  // 0X21988 cmp r4, #0x12
  unique_2e80_4 = 0x12 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x12 <= r4
  tmpOV = sborrow(r4, 0x12)
  unique_42800_4 = r4 - 0x12
  tmpNG = unique_42800_4 s< 0x0
  tmpZR = unique_42800_4 == 0x0
  CY = tmpCY
  ZR = tmpZR
  NG = tmpNG
  OV = tmpOV
  // 0X2198C bhi #0x219bc
  unique_1e00_1 = !ZR
  unique_1f00_1 = CY && unique_1e00_1
  if (unique_1f00_1) {
LAB_219BC:
    // 0X219BC mov r0, #0
    unique_2e80_4 = 0x0 >> 0x1f
    unique_2f00_1 = 0x0 == 0x0
    unique_2f80_1 = unique_2f00_1 && CY
    unique_3000_1 = 0x0 != 0x0
    unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
    unique_3100_1 = unique_3000_1 && unique_3080_1
    shift_carry = unique_2f80_1 || unique_3100_1
    r0 = 0x0
    tmpNG = r0 s< 0x0
    tmpZR = r0 == 0x0
    tmpCY = shift_carry
    tmpOV = OV
    // 0X219C0 pop {r3, r4, r5, pc}
    mult_addr = sp
    r3 = *[ram]mult_addr
    mult_addr = mult_addr + 0x4
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
  } else {
LAB_21990:
    // 0X21990 ldr r0, [pc, #0x30]
    r0 = *[ram]0x219c8
    // 0X21994 ldr r3, [r0, #4]
    unique_8280_4 = r0 + 0x4
    r3 = *[ram]unique_8280_4
    // 0X21998 cmp r3, r4
    shift_carry = CY
    tmpCY = r4 <= r3
    tmpOV = sborrow(r3, r4)
    unique_42900_4 = r3 - r4
    tmpNG = unique_42900_4 s< 0x0
    tmpZR = unique_42900_4 == 0x0
    CY = tmpCY
    ZR = tmpZR
    NG = tmpNG
    OV = tmpOV
    if (ZR) {
LAB_219B0:
      // 0X219B0 str r5, [r0, #0x50]
      unique_8280_4 = r0 + 0x50
      *[ram]unique_8280_4 = r5
      // 0X219B4 mov r0, #1
      unique_2e80_4 = 0x1 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      r0 = 0x1
      tmpNG = r0 s< 0x0
      tmpZR = r0 == 0x0
      tmpCY = shift_carry
      tmpOV = OV
      // 0X219B8 pop {r3, r4, r5, pc}
      mult_addr = sp
      r3 = *[ram]mult_addr
      mult_addr = mult_addr + 0x4
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
    } else {
LAB_219A0:
      while (1) {
        // 0X219A0 ldr r0, [r0, #0x54]
        unique_8280_4 = r0 + 0x54
        r0 = *[ram]unique_8280_4
        // 0X219A4 cmp r0, #0
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
        // 0X219A8 bne #0x21994
        unique_1a80_1 = !ZR
        if (!unique_1a80_1) {
          break
        }
        // 0X21994 ldr r3, [r0, #4]
        unique_8280_4 = r0 + 0x4
        r3 = *[ram]unique_8280_4
        // 0X21998 cmp r3, r4
        shift_carry = CY
        tmpCY = r4 <= r3
        tmpOV = sborrow(r3, r4)
        unique_42900_4 = r3 - r4
        tmpNG = unique_42900_4 s< 0x0
        tmpZR = unique_42900_4 == 0x0
        CY = tmpCY
        ZR = tmpZR
        NG = tmpNG
        OV = tmpOV
        if (ZR) {
          break
        }
      }
    }
  }
