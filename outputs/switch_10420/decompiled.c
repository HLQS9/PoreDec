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
  // 0X10434 ldr r3, [fp, #-8]
  unique_8380_4 = r11 + 0xfffffff8
  r3 = *[ram]unique_8380_4
  // 0X10438 cmp r3, #2
  unique_2e80_4 = 0x2 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x2 <= r3
  tmpOV = sborrow(r3, 0x2)
  unique_42800_4 = r3 - 0x2
  tmpNG = unique_42800_4 s< 0x0
  tmpZR = unique_42800_4 == 0x0
  CY = tmpCY
  ZR = tmpZR
  NG = tmpNG
  OV = tmpOV
  // 0X1043C bgt #0x10450
  unique_2300_1 = !ZR
  unique_2380_1 = NG == OV
  unique_2480_1 = unique_2300_1 && unique_2380_1
  if (unique_2480_1) {
LAB_10450:
    // 0X10450 ldr r3, [fp, #-8]
    unique_8380_4 = r11 + 0xfffffff8
    r3 = *[ram]unique_8380_4
    // 0X10454 cmp r3, #5
    unique_2e80_4 = 0x5 >> 0x1f
    unique_2f00_1 = 0x0 == 0x0
    unique_2f80_1 = unique_2f00_1 && CY
    unique_3000_1 = 0x0 != 0x0
    unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
    unique_3100_1 = unique_3000_1 && unique_3080_1
    shift_carry = unique_2f80_1 || unique_3100_1
    tmpCY = 0x5 <= r3
    tmpOV = sborrow(r3, 0x5)
    unique_42800_4 = r3 - 0x5
    tmpNG = unique_42800_4 s< 0x0
    tmpZR = unique_42800_4 == 0x0
    CY = tmpCY
    ZR = tmpZR
    NG = tmpNG
    OV = tmpOV
    if (ZR) {
LAB_1046C:
      // 0X1046C ldr r0, [pc, #0x24]
      r0 = *[ram]0x10498
      // 0X10470 bl #0x10304
      lr = 0x10474
      call ram_10304_4
      // 0X10484 mov r3, #0
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
      // 0X10488 mov r0, r3
      r0 = r3
      // 0X1048C sub sp, fp, #4
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
      // 0X10490 pop {fp, pc}
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
    } else {
LAB_1045C:
      // 0X10478 ldr r0, [pc, #0x1c]
      r0 = *[ram]0x1049c
      // 0X1047C bl #0x10304
      lr = 0x10480
      call ram_10304_4
      // 0X10480 mov r0, r0
      r0 = r0
      // 0X10484 mov r3, #0
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
      // 0X10488 mov r0, r3
      r0 = r3
      // 0X1048C sub sp, fp, #4
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
      // 0X10490 pop {fp, pc}
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
    }
  } else {
LAB_10440:
    // 0X10440 ldr r3, [fp, #-8]
    unique_8380_4 = r11 + 0xfffffff8
    r3 = *[ram]unique_8380_4
    // 0X10444 cmp r3, #0
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
    // 0X10448 bgt #0x10460
    unique_2300_1 = !ZR
    unique_2380_1 = NG == OV
    unique_2480_1 = unique_2300_1 && unique_2380_1
    if (unique_2480_1) {
LAB_10460:
      // 0X10460 ldr r0, [pc, #0x2c]
      r0 = *[ram]0x10494
      // 0X10464 bl #0x10304
      lr = 0x10468
      call ram_10304_4
      // 0X10484 mov r3, #0
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
      // 0X10488 mov r0, r3
      r0 = r3
      // 0X1048C sub sp, fp, #4
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
      // 0X10490 pop {fp, pc}
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
    } else {
LAB_1044C:
      // 0X10478 ldr r0, [pc, #0x1c]
      r0 = *[ram]0x1049c
      // 0X1047C bl #0x10304
      lr = 0x10480
      call ram_10304_4
      // 0X10480 mov r0, r0
      r0 = r0
      // 0X10484 mov r3, #0
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
      // 0X10488 mov r0, r3
      r0 = r3
      // 0X1048C sub sp, fp, #4
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
      // 0X10490 pop {fp, pc}
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
    }
  }
