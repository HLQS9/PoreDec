  // 0X10450 push {fp, lr}
  mult_addr = sp - 0x4
  *[ram]mult_addr = lr
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r11
  mult_addr = mult_addr - 0x4
  sp = mult_addr + 0x4
  // 0X10454 add fp, sp, #4
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
  // 0X10458 sub sp, sp, #0x10
  unique_2e80_4 = 0x10 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x10 <= sp
  tmpOV = sborrow(sp, 0x10)
  sp = sp - 0x10
  tmpNG = sp s< 0x0
  tmpZR = sp == 0x0
  // 0X1045C str r0, [fp, #-0x10]
  unique_8380_4 = r11 + 0xfffffff0
  *[ram]unique_8380_4 = r0
  // 0X10460 str r1, [fp, #-0x14]
  unique_8380_4 = r11 + 0xffffffec
  *[ram]unique_8380_4 = r1
  // 0X10464 ldr r0, [pc, #0x3c]
  r0 = *[ram]0x104a8
  // 0X10468 bl #0x10334
  lr = 0x1046c
  call ram_10334_4
  // 0X1046C mov r3, #0
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
  // 0X10470 str r3, [fp, #-8]
  unique_8380_4 = r11 + 0xfffffff8
  *[ram]unique_8380_4 = r3
  // 0X10474 ldr r3, [fp, #-0x10]
  unique_8380_4 = r11 + 0xfffffff0
  r3 = *[ram]unique_8380_4
  // 0X10478 cmp r3, #1
  unique_2e80_4 = 0x1 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x1 <= r3
  tmpOV = sborrow(r3, 0x1)
  unique_42800_4 = r3 - 0x1
  tmpNG = unique_42800_4 s< 0x0
  tmpZR = unique_42800_4 == 0x0
  CY = tmpCY
  ZR = tmpZR
  NG = tmpNG
  OV = tmpOV
  // 0X1047C ble #0x1049c
  unique_2500_1 = NG != OV
  unique_2600_1 = ZR || unique_2500_1
  if (unique_2600_1) {
    do {
      // 0X1049C ldr r0, [pc, #0xc]
      r0 = *[ram]0x104b0
      // 0X104A0 bl #0x10334
      lr = 0x104a4
      call ram_10334_4
      // 0X10474 ldr r3, [fp, #-0x10]
      unique_8380_4 = r11 + 0xfffffff0
      r3 = *[ram]unique_8380_4
      // 0X10478 cmp r3, #1
      unique_2e80_4 = 0x1 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      tmpCY = 0x1 <= r3
      tmpOV = sborrow(r3, 0x1)
      unique_42800_4 = r3 - 0x1
      tmpNG = unique_42800_4 s< 0x0
      tmpZR = unique_42800_4 == 0x0
      CY = tmpCY
      ZR = tmpZR
      NG = tmpNG
      OV = tmpOV
      // 0X1047C ble #0x1049c
      unique_2500_1 = NG != OV
      unique_2600_1 = ZR || unique_2500_1
    } while (unique_2600_1);
  }
  do {
    // 0X10480 ldr r3, [fp, #-8]
    unique_8380_4 = r11 + 0xfffffff8
    r3 = *[ram]unique_8380_4
    // 0X10484 add r3, r3, #1
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
    // 0X10488 str r3, [fp, #-8]
    unique_8380_4 = r11 + 0xfffffff8
    *[ram]unique_8380_4 = r3
    // 0X1048C ldr r1, [fp, #-8]
    unique_8380_4 = r11 + 0xfffffff8
    r1 = *[ram]unique_8380_4
    // 0X10490 ldr r0, [pc, #0x14]
    r0 = *[ram]0x104ac
    // 0X10494 bl #0x10328
    lr = 0x10498
    call ram_10328_4
    // 0X10474 ldr r3, [fp, #-0x10]
    unique_8380_4 = r11 + 0xfffffff0
    r3 = *[ram]unique_8380_4
    // 0X10478 cmp r3, #1
    unique_2e80_4 = 0x1 >> 0x1f
    unique_2f00_1 = 0x0 == 0x0
    unique_2f80_1 = unique_2f00_1 && CY
    unique_3000_1 = 0x0 != 0x0
    unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
    unique_3100_1 = unique_3000_1 && unique_3080_1
    shift_carry = unique_2f80_1 || unique_3100_1
    tmpCY = 0x1 <= r3
    tmpOV = sborrow(r3, 0x1)
    unique_42800_4 = r3 - 0x1
    tmpNG = unique_42800_4 s< 0x0
    tmpZR = unique_42800_4 == 0x0
    CY = tmpCY
    ZR = tmpZR
    NG = tmpNG
    OV = tmpOV
    // 0X1047C ble #0x1049c
    unique_2500_1 = NG != OV
    unique_2600_1 = ZR || unique_2500_1
  } while (unique_2600_1);
  do {
    // 0X1049C ldr r0, [pc, #0xc]
    r0 = *[ram]0x104b0
    // 0X104A0 bl #0x10334
    lr = 0x104a4
    call ram_10334_4
    // 0X10474 ldr r3, [fp, #-0x10]
    unique_8380_4 = r11 + 0xfffffff0
    r3 = *[ram]unique_8380_4
    // 0X10478 cmp r3, #1
    unique_2e80_4 = 0x1 >> 0x1f
    unique_2f00_1 = 0x0 == 0x0
    unique_2f80_1 = unique_2f00_1 && CY
    unique_3000_1 = 0x0 != 0x0
    unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
    unique_3100_1 = unique_3000_1 && unique_3080_1
    shift_carry = unique_2f80_1 || unique_3100_1
    tmpCY = 0x1 <= r3
    tmpOV = sborrow(r3, 0x1)
    unique_42800_4 = r3 - 0x1
    tmpNG = unique_42800_4 s< 0x0
    tmpZR = unique_42800_4 == 0x0
    CY = tmpCY
    ZR = tmpZR
    NG = tmpNG
    OV = tmpOV
    // 0X1047C ble #0x1049c
    unique_2500_1 = NG != OV
    unique_2600_1 = ZR || unique_2500_1
  } while (unique_2600_1);
  while (1) {
    do {
      // 0X10480 ldr r3, [fp, #-8]
      unique_8380_4 = r11 + 0xfffffff8
      r3 = *[ram]unique_8380_4
      // 0X10484 add r3, r3, #1
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
      // 0X10488 str r3, [fp, #-8]
      unique_8380_4 = r11 + 0xfffffff8
      *[ram]unique_8380_4 = r3
      // 0X1048C ldr r1, [fp, #-8]
      unique_8380_4 = r11 + 0xfffffff8
      r1 = *[ram]unique_8380_4
      // 0X10490 ldr r0, [pc, #0x14]
      r0 = *[ram]0x104ac
      // 0X10494 bl #0x10328
      lr = 0x10498
      call ram_10328_4
      // 0X10474 ldr r3, [fp, #-0x10]
      unique_8380_4 = r11 + 0xfffffff0
      r3 = *[ram]unique_8380_4
      // 0X10478 cmp r3, #1
      unique_2e80_4 = 0x1 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      tmpCY = 0x1 <= r3
      tmpOV = sborrow(r3, 0x1)
      unique_42800_4 = r3 - 0x1
      tmpNG = unique_42800_4 s< 0x0
      tmpZR = unique_42800_4 == 0x0
      CY = tmpCY
      ZR = tmpZR
      NG = tmpNG
      OV = tmpOV
      // 0X1047C ble #0x1049c
      unique_2500_1 = NG != OV
      unique_2600_1 = ZR || unique_2500_1
    } while (unique_2600_1);
    do {
      // 0X1049C ldr r0, [pc, #0xc]
      r0 = *[ram]0x104b0
      // 0X104A0 bl #0x10334
      lr = 0x104a4
      call ram_10334_4
      // 0X10474 ldr r3, [fp, #-0x10]
      unique_8380_4 = r11 + 0xfffffff0
      r3 = *[ram]unique_8380_4
      // 0X10478 cmp r3, #1
      unique_2e80_4 = 0x1 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      tmpCY = 0x1 <= r3
      tmpOV = sborrow(r3, 0x1)
      unique_42800_4 = r3 - 0x1
      tmpNG = unique_42800_4 s< 0x0
      tmpZR = unique_42800_4 == 0x0
      CY = tmpCY
      ZR = tmpZR
      NG = tmpNG
      OV = tmpOV
      // 0X1047C ble #0x1049c
      unique_2500_1 = NG != OV
      unique_2600_1 = ZR || unique_2500_1
    } while (unique_2600_1);
  }
