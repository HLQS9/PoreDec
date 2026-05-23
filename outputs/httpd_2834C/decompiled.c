  // 0X2834C str lr, [sp, #-4]!
  sp = sp + 0xfffffffc
  *[ram]sp = lr
  // 0X28350 sub sp, sp, #0x34
  unique_2e80_4 = 0x34 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x34 <= sp
  tmpOV = sborrow(sp, 0x34)
  sp = sp - 0x34
  tmpNG = sp s< 0x0
  tmpZR = sp == 0x0
  // 0X28354 bl #0x53650
  lr = 0x28358
  call ram_53650_4
  // 0X28358 cmp r0, #0x50
  unique_2e80_4 = 0x50 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x50 <= r0
  tmpOV = sborrow(r0, 0x50)
  unique_42800_4 = r0 - 0x50
  tmpNG = unique_42800_4 s< 0x0
  tmpZR = unique_42800_4 == 0x0
  CY = tmpCY
  ZR = tmpZR
  NG = tmpNG
  OV = tmpOV
  if (!ZR) {
    // 0X28360 bl #0x53650
    lr = 0x28364
    call ram_53650_4
    // 0X28364 cmp r0, #0
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
      // 0X2836C ldr r3, [pc, #0x68]
      r3 = *[ram]0x283dc
      // 0X28370 mov r2, #0
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
      // 0X28374 ldr r0, [pc, #0x64]
      r0 = *[ram]0x283e0
      // 0X28378 mov r1, #0xcb
      unique_2e80_4 = 0xcb >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      r1 = 0xcb
      tmpNG = r1 s< 0x0
      tmpZR = r1 == 0x0
      tmpCY = shift_carry
      tmpOV = OV
      // 0X2837C str r2, [sp, #4]
      unique_8280_4 = sp + 0x4
      *[ram]unique_8280_4 = r2
      // 0X28380 str r3, [sp]
      unique_8280_4 = sp + 0x0
      *[ram]unique_8280_4 = r3
      // 0X28384 mov r3, #1
      unique_2e80_4 = 0x1 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      r3 = 0x1
      tmpNG = r3 s< 0x0
      tmpZR = r3 == 0x0
      tmpCY = shift_carry
      tmpOV = OV
      // 0X28388 str r3, [sp, #8]
      unique_8280_4 = sp + 0x8
      *[ram]unique_8280_4 = r3
      // 0X2838C add r3, r3, r3
      shift_carry = CY
      tmpCY = carry(r3, r3)
      tmpOV = scarry(r3, r3)
      r3 = r3 + r3
      tmpNG = r3 s< 0x0
      tmpZR = r3 == 0x0
      // 0X28390 str r3, [sp, #0xc]
      unique_8280_4 = sp + 0xc
      *[ram]unique_8280_4 = r3
      // 0X28394 add r3, r3, #1
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
      // 0X28398 str r3, [sp, #0x10]
      unique_8280_4 = sp + 0x10
      *[ram]unique_8280_4 = r3
      // 0X2839C add r3, r3, #1
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
      // 0X283A0 str r3, [sp, #0x14]
      unique_8280_4 = sp + 0x14
      *[ram]unique_8280_4 = r3
      // 0X283A4 add r3, r3, #1
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
      // 0X283A8 str r3, [sp, #0x18]
      unique_8280_4 = sp + 0x18
      *[ram]unique_8280_4 = r3
      // 0X283AC add r3, r3, #1
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
      // 0X283B0 str r3, [sp, #0x1c]
      unique_8280_4 = sp + 0x1c
      *[ram]unique_8280_4 = r3
      // 0X283B4 add r3, r3, #1
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
      // 0X283B8 str r3, [sp, #0x20]
      unique_8280_4 = sp + 0x20
      *[ram]unique_8280_4 = r3
      // 0X283BC add r3, r3, #1
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
      // 0X283C0 str r3, [sp, #0x24]
      unique_8280_4 = sp + 0x24
      *[ram]unique_8280_4 = r3
      // 0X283C4 add r3, r3, #1
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
      // 0X283C8 str r3, [sp, #0x28]
      unique_8280_4 = sp + 0x28
      *[ram]unique_8280_4 = r3
      // 0X283CC mov r3, #0x800
      unique_2e80_4 = 0x800 >> 0x1f
      unique_2f00_1 = 0xb == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0xb != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      r3 = 0x800
      tmpNG = r3 s< 0x0
      tmpZR = r3 == 0x0
      tmpCY = shift_carry
      tmpOV = OV
      // 0X283D0 bl #0xb36f4
      lr = 0x283d4
      call ram_b36f4_4
    }
  }
  // 0X283D4 add sp, sp, #0x34
  unique_2e80_4 = 0x34 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = carry(sp, 0x34)
  tmpOV = scarry(sp, 0x34)
  sp = sp + 0x34
  tmpNG = sp s< 0x0
  tmpZR = sp == 0x0
  // 0X283D8 ldm sp!, {pc}
  mult_addr = sp
  pc = *[ram]mult_addr
  mult_addr = mult_addr + 0x4
  sp = mult_addr
  unique_0_4 = pc & 0x1
  ISAModeSwitch = unique_0_4 != 0x0
  TB = ISAModeSwitch
  pc = pc & 0xfffffffe
  return pc
