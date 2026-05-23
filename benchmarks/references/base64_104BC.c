  // 0X104BC str fp, [sp, #-4]!
  sp = sp + 0xfffffffc
  *[ram]sp = r11
  // 0X104C0 add fp, sp, #0
  unique_2e80_4 = 0x0 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = carry(sp, 0x0)
  tmpOV = scarry(sp, 0x0)
  r11 = sp + 0x0
  tmpNG = r11 s< 0x0
  tmpZR = r11 == 0x0
  // 0X104C4 sub sp, sp, #0x24
  unique_2e80_4 = 0x24 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x24 <= sp
  tmpOV = sborrow(sp, 0x24)
  sp = sp - 0x24
  tmpNG = sp s< 0x0
  tmpZR = sp == 0x0
  // 0X104C8 str r0, [fp, #-0x18]
  unique_8380_4 = r11 + 0xffffffe8
  *[ram]unique_8380_4 = r0
  // 0X104CC str r1, [fp, #-0x1c]
  unique_8380_4 = r11 + 0xffffffe4
  *[ram]unique_8380_4 = r1
  // 0X104D0 str r2, [fp, #-0x20]
  unique_8380_4 = r11 + 0xffffffe0
  *[ram]unique_8380_4 = r2
  // 0X104D4 mov r3, #0
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
  // 0X104D8 str r3, [fp, #-0x10]
  unique_8380_4 = r11 + 0xfffffff0
  *[ram]unique_8380_4 = r3
  // 0X104DC mov r3, #0
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
  // 0X104E0 strb r3, [fp, #-0x12]
  unique_8380_4 = r11 + 0xffffffee
  unique_70c00_1 = SUBPIECE r3, 0x0
  *[ram]unique_8380_4 = unique_70c00_1
  // 0X104E4 mov r3, #0
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
  // 0X104E8 str r3, [fp, #-8]
  unique_8380_4 = r11 + 0xfffffff8
  *[ram]unique_8380_4 = r3
  // 0X104EC ldr r3, [fp, #-8]
  unique_8380_4 = r11 + 0xfffffff8
  r3 = *[ram]unique_8380_4
  // 0X104F0 str r3, [fp, #-0xc]
  unique_8380_4 = r11 + 0xfffffff4
  *[ram]unique_8380_4 = r3
  while (1) {
    // 0X10650 ldr r2, [fp, #-0xc]
    unique_8380_4 = r11 + 0xfffffff4
    r2 = *[ram]unique_8380_4
    // 0X10654 ldr r3, [fp, #-0x1c]
    unique_8380_4 = r11 + 0xffffffe4
    r3 = *[ram]unique_8380_4
    // 0X10658 cmp r2, r3
    shift_carry = CY
    tmpCY = r3 <= r2
    tmpOV = sborrow(r2, r3)
    unique_42900_4 = r2 - r3
    tmpNG = unique_42900_4 s< 0x0
    tmpZR = unique_42900_4 == 0x0
    CY = tmpCY
    ZR = tmpZR
    NG = tmpNG
    OV = tmpOV
    // 0X1065C blo #0x104f8
    unique_1b80_1 = !CY
    if (unique_1b80_1) {
      // 0X104F8 ldr r2, [fp, #-0x18]
      unique_8380_4 = r11 + 0xffffffe8
      r2 = *[ram]unique_8380_4
      // 0X104FC ldr r3, [fp, #-0xc]
      unique_8380_4 = r11 + 0xfffffff4
      r3 = *[ram]unique_8380_4
      // 0X10500 add r3, r2, r3
      shift_carry = CY
      tmpCY = carry(r2, r3)
      tmpOV = scarry(r2, r3)
      r3 = r2 + r3
      tmpNG = r3 s< 0x0
      tmpZR = r3 == 0x0
      // 0X10504 ldrb r3, [r3]
      unique_8280_4 = r3 + 0x0
      unique_43880_1 = *[ram]unique_8280_4
      r3 = zext(unique_43880_1)
      // 0X10508 strb r3, [fp, #-0x11]
      unique_8380_4 = r11 + 0xffffffef
      unique_70c00_1 = SUBPIECE r3, 0x0
      *[ram]unique_8380_4 = unique_70c00_1
      // 0X1050C ldr r3, [fp, #-0x10]
      unique_8380_4 = r11 + 0xfffffff0
      r3 = *[ram]unique_8380_4
      // 0X10510 cmp r3, #2
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
      if (ZR) {
        // 0X105C8 mov r3, #0
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
        // 0X105CC str r3, [fp, #-0x10]
        unique_8380_4 = r11 + 0xfffffff0
        *[ram]unique_8380_4 = r3
        // 0X105D0 ldrb r3, [fp, #-0x12]
        unique_8380_4 = r11 + 0xffffffee
        unique_43880_1 = *[ram]unique_8380_4
        r3 = zext(unique_43880_1)
        // 0X105D4 lsl r3, r3, #2
        unique_3280_4 = 0x20 - 0x2
        unique_3300_4 = r3 >> unique_3280_4
        unique_3400_4 = unique_3300_4 & 0x1
        shift_carry = SUBPIECE unique_3400_4, 0x0
        unique_3580_4 = r3 << 0x2
        r3 = unique_3580_4
        tmpNG = r3 s< 0x0
        tmpZR = r3 == 0x0
        tmpCY = shift_carry
        tmpOV = OV
        // 0X105D8 and r2, r3, #0x3c
        unique_2e80_4 = 0x3c >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        r2 = r3 & 0x3c
        tmpCY = shift_carry
        tmpOV = OV
        tmpNG = r2 s< 0x0
        tmpZR = r2 == 0x0
        // 0X105DC ldrb r3, [fp, #-0x11]
        unique_8380_4 = r11 + 0xffffffef
        unique_43880_1 = *[ram]unique_8380_4
        r3 = zext(unique_43880_1)
        // 0X105E0 lsr r3, r3, #6
        unique_3800_4 = 0x6 - 0x1
        unique_3880_4 = r3 >> unique_3800_4
        unique_3980_4 = unique_3880_4 & 0x1
        shift_carry = SUBPIECE unique_3980_4, 0x0
        unique_3b00_4 = r3 >> 0x6
        r3 = unique_3b00_4
        tmpNG = r3 s< 0x0
        tmpZR = r3 == 0x0
        tmpCY = shift_carry
        tmpOV = OV
        // 0X105E4 and r3, r3, #0xff
        unique_2e80_4 = 0xff >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        r3 = r3 & 0xff
        tmpCY = shift_carry
        tmpOV = OV
        tmpNG = r3 s< 0x0
        tmpZR = r3 == 0x0
        // 0X105E8 and r3, r3, #3
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
        // 0X105EC orr r2, r2, r3
        shift_carry = CY
        r2 = r2 | r3
        tmpCY = shift_carry
        tmpOV = OV
        tmpNG = r2 s< 0x0
        tmpZR = r2 == 0x0
        // 0X105F0 ldr r3, [fp, #-8]
        unique_8380_4 = r11 + 0xfffffff8
        r3 = *[ram]unique_8380_4
        // 0X105F4 add r1, r3, #1
        unique_2e80_4 = 0x1 >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        tmpCY = carry(r3, 0x1)
        tmpOV = scarry(r3, 0x1)
        r1 = r3 + 0x1
        tmpNG = r1 s< 0x0
        tmpZR = r1 == 0x0
        // 0X105F8 str r1, [fp, #-8]
        unique_8380_4 = r11 + 0xfffffff8
        *[ram]unique_8380_4 = r1
        // 0X105FC ldr r1, [fp, #-0x20]
        unique_8380_4 = r11 + 0xffffffe0
        r1 = *[ram]unique_8380_4
        // 0X10600 add r3, r1, r3
        shift_carry = CY
        tmpCY = carry(r1, r3)
        tmpOV = scarry(r1, r3)
        r3 = r1 + r3
        tmpNG = r3 s< 0x0
        tmpZR = r3 == 0x0
        // 0X10604 ldr r1, [pc, #0x14c]
        r1 = *[ram]0x10758
        // 0X10608 ldrb r2, [r1, r2]
        unique_8480_4 = r1 + r2
        unique_43880_1 = *[ram]unique_8480_4
        r2 = zext(unique_43880_1)
        // 0X1060C strb r2, [r3]
        unique_8280_4 = r3 + 0x0
        unique_70c00_1 = SUBPIECE r2, 0x0
        *[ram]unique_8280_4 = unique_70c00_1
        // 0X10610 ldrb r3, [fp, #-0x11]
        unique_8380_4 = r11 + 0xffffffef
        unique_43880_1 = *[ram]unique_8380_4
        r3 = zext(unique_43880_1)
        // 0X10614 and r2, r3, #0x3f
        unique_2e80_4 = 0x3f >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        r2 = r3 & 0x3f
        tmpCY = shift_carry
        tmpOV = OV
        tmpNG = r2 s< 0x0
        tmpZR = r2 == 0x0
        // 0X10618 ldr r3, [fp, #-8]
        unique_8380_4 = r11 + 0xfffffff8
        r3 = *[ram]unique_8380_4
        // 0X1061C add r1, r3, #1
        unique_2e80_4 = 0x1 >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        tmpCY = carry(r3, 0x1)
        tmpOV = scarry(r3, 0x1)
        r1 = r3 + 0x1
        tmpNG = r1 s< 0x0
        tmpZR = r1 == 0x0
        // 0X10620 str r1, [fp, #-8]
        unique_8380_4 = r11 + 0xfffffff8
        *[ram]unique_8380_4 = r1
        // 0X10624 ldr r1, [fp, #-0x20]
        unique_8380_4 = r11 + 0xffffffe0
        r1 = *[ram]unique_8380_4
        // 0X10628 add r3, r1, r3
        shift_carry = CY
        tmpCY = carry(r1, r3)
        tmpOV = scarry(r1, r3)
        r3 = r1 + r3
        tmpNG = r3 s< 0x0
        tmpZR = r3 == 0x0
        // 0X1062C ldr r1, [pc, #0x124]
        r1 = *[ram]0x10758
        // 0X10630 ldrb r2, [r1, r2]
        unique_8480_4 = r1 + r2
        unique_43880_1 = *[ram]unique_8480_4
        r2 = zext(unique_43880_1)
        // 0X10634 strb r2, [r3]
        unique_8280_4 = r3 + 0x0
        unique_70c00_1 = SUBPIECE r2, 0x0
        *[ram]unique_8280_4 = unique_70c00_1
        // 0X10638 mov r0, r0
        r0 = r0
      } else {
        // 0X10518 ldr r3, [fp, #-0x10]
        unique_8380_4 = r11 + 0xfffffff0
        r3 = *[ram]unique_8380_4
        // 0X1051C cmp r3, #2
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
        // 0X10520 bgt #0x1063c
        unique_2300_1 = !ZR
        unique_2380_1 = NG == OV
        unique_2480_1 = unique_2300_1 && unique_2380_1
        if (unique_2480_1) {
          // 0X1063C ldrb r3, [fp, #-0x11]
          unique_8380_4 = r11 + 0xffffffef
          unique_43880_1 = *[ram]unique_8380_4
          r3 = zext(unique_43880_1)
          // 0X10640 strb r3, [fp, #-0x12]
          unique_8380_4 = r11 + 0xffffffee
          unique_70c00_1 = SUBPIECE r3, 0x0
          *[ram]unique_8380_4 = unique_70c00_1
          // 0X10644 ldr r3, [fp, #-0xc]
          unique_8380_4 = r11 + 0xfffffff4
          r3 = *[ram]unique_8380_4
          // 0X10648 add r3, r3, #1
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
          // 0X1064C str r3, [fp, #-0xc]
          unique_8380_4 = r11 + 0xfffffff4
          *[ram]unique_8380_4 = r3
          continue
        }
        // 0X10524 ldr r3, [fp, #-0x10]
        unique_8380_4 = r11 + 0xfffffff0
        r3 = *[ram]unique_8380_4
        // 0X10528 cmp r3, #0
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
        if (ZR) {
          // 0X10540 mov r3, #1
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
          // 0X10544 str r3, [fp, #-0x10]
          unique_8380_4 = r11 + 0xfffffff0
          *[ram]unique_8380_4 = r3
          // 0X10548 ldrb r3, [fp, #-0x11]
          unique_8380_4 = r11 + 0xffffffef
          unique_43880_1 = *[ram]unique_8380_4
          r3 = zext(unique_43880_1)
          // 0X1054C lsr r3, r3, #2
          unique_3800_4 = 0x2 - 0x1
          unique_3880_4 = r3 >> unique_3800_4
          unique_3980_4 = unique_3880_4 & 0x1
          shift_carry = SUBPIECE unique_3980_4, 0x0
          unique_3b00_4 = r3 >> 0x2
          r3 = unique_3b00_4
          tmpNG = r3 s< 0x0
          tmpZR = r3 == 0x0
          tmpCY = shift_carry
          tmpOV = OV
          // 0X10550 and r3, r3, #0xff
          unique_2e80_4 = 0xff >> 0x1f
          unique_2f00_1 = 0x0 == 0x0
          unique_2f80_1 = unique_2f00_1 && CY
          unique_3000_1 = 0x0 != 0x0
          unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
          unique_3100_1 = unique_3000_1 && unique_3080_1
          shift_carry = unique_2f80_1 || unique_3100_1
          r3 = r3 & 0xff
          tmpCY = shift_carry
          tmpOV = OV
          tmpNG = r3 s< 0x0
          tmpZR = r3 == 0x0
          // 0X10554 and r2, r3, #0x3f
          unique_2e80_4 = 0x3f >> 0x1f
          unique_2f00_1 = 0x0 == 0x0
          unique_2f80_1 = unique_2f00_1 && CY
          unique_3000_1 = 0x0 != 0x0
          unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
          unique_3100_1 = unique_3000_1 && unique_3080_1
          shift_carry = unique_2f80_1 || unique_3100_1
          r2 = r3 & 0x3f
          tmpCY = shift_carry
          tmpOV = OV
          tmpNG = r2 s< 0x0
          tmpZR = r2 == 0x0
          // 0X10558 ldr r3, [fp, #-8]
          unique_8380_4 = r11 + 0xfffffff8
          r3 = *[ram]unique_8380_4
          // 0X1055C add r1, r3, #1
          unique_2e80_4 = 0x1 >> 0x1f
          unique_2f00_1 = 0x0 == 0x0
          unique_2f80_1 = unique_2f00_1 && CY
          unique_3000_1 = 0x0 != 0x0
          unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
          unique_3100_1 = unique_3000_1 && unique_3080_1
          shift_carry = unique_2f80_1 || unique_3100_1
          tmpCY = carry(r3, 0x1)
          tmpOV = scarry(r3, 0x1)
          r1 = r3 + 0x1
          tmpNG = r1 s< 0x0
          tmpZR = r1 == 0x0
          // 0X10560 str r1, [fp, #-8]
          unique_8380_4 = r11 + 0xfffffff8
          *[ram]unique_8380_4 = r1
          // 0X10564 ldr r1, [fp, #-0x20]
          unique_8380_4 = r11 + 0xffffffe0
          r1 = *[ram]unique_8380_4
          // 0X10568 add r3, r1, r3
          shift_carry = CY
          tmpCY = carry(r1, r3)
          tmpOV = scarry(r1, r3)
          r3 = r1 + r3
          tmpNG = r3 s< 0x0
          tmpZR = r3 == 0x0
          // 0X1056C ldr r1, [pc, #0x1e4]
          r1 = *[ram]0x10758
          // 0X10570 ldrb r2, [r1, r2]
          unique_8480_4 = r1 + r2
          unique_43880_1 = *[ram]unique_8480_4
          r2 = zext(unique_43880_1)
          // 0X10574 strb r2, [r3]
          unique_8280_4 = r3 + 0x0
          unique_70c00_1 = SUBPIECE r2, 0x0
          *[ram]unique_8280_4 = unique_70c00_1
        } else {
          // 0X10530 ldr r3, [fp, #-0x10]
          unique_8380_4 = r11 + 0xfffffff0
          r3 = *[ram]unique_8380_4
          // 0X10534 cmp r3, #1
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
          if (ZR) {
            // 0X1057C mov r3, #2
            unique_2e80_4 = 0x2 >> 0x1f
            unique_2f00_1 = 0x0 == 0x0
            unique_2f80_1 = unique_2f00_1 && CY
            unique_3000_1 = 0x0 != 0x0
            unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
            unique_3100_1 = unique_3000_1 && unique_3080_1
            shift_carry = unique_2f80_1 || unique_3100_1
            r3 = 0x2
            tmpNG = r3 s< 0x0
            tmpZR = r3 == 0x0
            tmpCY = shift_carry
            tmpOV = OV
            // 0X10580 str r3, [fp, #-0x10]
            unique_8380_4 = r11 + 0xfffffff0
            *[ram]unique_8380_4 = r3
            // 0X10584 ldrb r3, [fp, #-0x12]
            unique_8380_4 = r11 + 0xffffffee
            unique_43880_1 = *[ram]unique_8380_4
            r3 = zext(unique_43880_1)
            // 0X10588 lsl r3, r3, #4
            unique_3280_4 = 0x20 - 0x4
            unique_3300_4 = r3 >> unique_3280_4
            unique_3400_4 = unique_3300_4 & 0x1
            shift_carry = SUBPIECE unique_3400_4, 0x0
            unique_3580_4 = r3 << 0x4
            r3 = unique_3580_4
            tmpNG = r3 s< 0x0
            tmpZR = r3 == 0x0
            tmpCY = shift_carry
            tmpOV = OV
            // 0X1058C and r2, r3, #0x30
            unique_2e80_4 = 0x30 >> 0x1f
            unique_2f00_1 = 0x0 == 0x0
            unique_2f80_1 = unique_2f00_1 && CY
            unique_3000_1 = 0x0 != 0x0
            unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
            unique_3100_1 = unique_3000_1 && unique_3080_1
            shift_carry = unique_2f80_1 || unique_3100_1
            r2 = r3 & 0x30
            tmpCY = shift_carry
            tmpOV = OV
            tmpNG = r2 s< 0x0
            tmpZR = r2 == 0x0
            // 0X10590 ldrb r3, [fp, #-0x11]
            unique_8380_4 = r11 + 0xffffffef
            unique_43880_1 = *[ram]unique_8380_4
            r3 = zext(unique_43880_1)
            // 0X10594 lsr r3, r3, #4
            unique_3800_4 = 0x4 - 0x1
            unique_3880_4 = r3 >> unique_3800_4
            unique_3980_4 = unique_3880_4 & 0x1
            shift_carry = SUBPIECE unique_3980_4, 0x0
            unique_3b00_4 = r3 >> 0x4
            r3 = unique_3b00_4
            tmpNG = r3 s< 0x0
            tmpZR = r3 == 0x0
            tmpCY = shift_carry
            tmpOV = OV
            // 0X10598 and r3, r3, #0xff
            unique_2e80_4 = 0xff >> 0x1f
            unique_2f00_1 = 0x0 == 0x0
            unique_2f80_1 = unique_2f00_1 && CY
            unique_3000_1 = 0x0 != 0x0
            unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
            unique_3100_1 = unique_3000_1 && unique_3080_1
            shift_carry = unique_2f80_1 || unique_3100_1
            r3 = r3 & 0xff
            tmpCY = shift_carry
            tmpOV = OV
            tmpNG = r3 s< 0x0
            tmpZR = r3 == 0x0
            // 0X1059C and r3, r3, #0xf
            unique_2e80_4 = 0xf >> 0x1f
            unique_2f00_1 = 0x0 == 0x0
            unique_2f80_1 = unique_2f00_1 && CY
            unique_3000_1 = 0x0 != 0x0
            unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
            unique_3100_1 = unique_3000_1 && unique_3080_1
            shift_carry = unique_2f80_1 || unique_3100_1
            r3 = r3 & 0xf
            tmpCY = shift_carry
            tmpOV = OV
            tmpNG = r3 s< 0x0
            tmpZR = r3 == 0x0
            // 0X105A0 orr r2, r2, r3
            shift_carry = CY
            r2 = r2 | r3
            tmpCY = shift_carry
            tmpOV = OV
            tmpNG = r2 s< 0x0
            tmpZR = r2 == 0x0
            // 0X105A4 ldr r3, [fp, #-8]
            unique_8380_4 = r11 + 0xfffffff8
            r3 = *[ram]unique_8380_4
            // 0X105A8 add r1, r3, #1
            unique_2e80_4 = 0x1 >> 0x1f
            unique_2f00_1 = 0x0 == 0x0
            unique_2f80_1 = unique_2f00_1 && CY
            unique_3000_1 = 0x0 != 0x0
            unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
            unique_3100_1 = unique_3000_1 && unique_3080_1
            shift_carry = unique_2f80_1 || unique_3100_1
            tmpCY = carry(r3, 0x1)
            tmpOV = scarry(r3, 0x1)
            r1 = r3 + 0x1
            tmpNG = r1 s< 0x0
            tmpZR = r1 == 0x0
            // 0X105AC str r1, [fp, #-8]
            unique_8380_4 = r11 + 0xfffffff8
            *[ram]unique_8380_4 = r1
            // 0X105B0 ldr r1, [fp, #-0x20]
            unique_8380_4 = r11 + 0xffffffe0
            r1 = *[ram]unique_8380_4
            // 0X105B4 add r3, r1, r3
            shift_carry = CY
            tmpCY = carry(r1, r3)
            tmpOV = scarry(r1, r3)
            r3 = r1 + r3
            tmpNG = r3 s< 0x0
            tmpZR = r3 == 0x0
            // 0X105B8 ldr r1, [pc, #0x198]
            r1 = *[ram]0x10758
            // 0X105BC ldrb r2, [r1, r2]
            unique_8480_4 = r1 + r2
            unique_43880_1 = *[ram]unique_8480_4
            r2 = zext(unique_43880_1)
            // 0X105C0 strb r2, [r3]
            unique_8280_4 = r3 + 0x0
            unique_70c00_1 = SUBPIECE r2, 0x0
            *[ram]unique_8280_4 = unique_70c00_1
          } else {
          }
        }
      }
      // 0X1063C ldrb r3, [fp, #-0x11]
      unique_8380_4 = r11 + 0xffffffef
      unique_43880_1 = *[ram]unique_8380_4
      r3 = zext(unique_43880_1)
      // 0X10640 strb r3, [fp, #-0x12]
      unique_8380_4 = r11 + 0xffffffee
      unique_70c00_1 = SUBPIECE r3, 0x0
      *[ram]unique_8380_4 = unique_70c00_1
      // 0X10644 ldr r3, [fp, #-0xc]
      unique_8380_4 = r11 + 0xfffffff4
      r3 = *[ram]unique_8380_4
      // 0X10648 add r3, r3, #1
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
      // 0X1064C str r3, [fp, #-0xc]
      unique_8380_4 = r11 + 0xfffffff4
      *[ram]unique_8380_4 = r3
      continue
    }
    // 0X10660 ldr r3, [fp, #-0x10]
    unique_8380_4 = r11 + 0xfffffff0
    r3 = *[ram]unique_8380_4
    // 0X10664 cmp r3, #1
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
    if (ZR) {
      // 0X1067C ldrb r3, [fp, #-0x12]
      unique_8380_4 = r11 + 0xffffffee
      unique_43880_1 = *[ram]unique_8380_4
      r3 = zext(unique_43880_1)
      // 0X10680 lsl r3, r3, #4
      unique_3280_4 = 0x20 - 0x4
      unique_3300_4 = r3 >> unique_3280_4
      unique_3400_4 = unique_3300_4 & 0x1
      shift_carry = SUBPIECE unique_3400_4, 0x0
      unique_3580_4 = r3 << 0x4
      r3 = unique_3580_4
      tmpNG = r3 s< 0x0
      tmpZR = r3 == 0x0
      tmpCY = shift_carry
      tmpOV = OV
      // 0X10684 and r2, r3, #0x30
      unique_2e80_4 = 0x30 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      r2 = r3 & 0x30
      tmpCY = shift_carry
      tmpOV = OV
      tmpNG = r2 s< 0x0
      tmpZR = r2 == 0x0
      // 0X10688 ldr r3, [fp, #-8]
      unique_8380_4 = r11 + 0xfffffff8
      r3 = *[ram]unique_8380_4
      // 0X1068C add r1, r3, #1
      unique_2e80_4 = 0x1 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      tmpCY = carry(r3, 0x1)
      tmpOV = scarry(r3, 0x1)
      r1 = r3 + 0x1
      tmpNG = r1 s< 0x0
      tmpZR = r1 == 0x0
      // 0X10690 str r1, [fp, #-8]
      unique_8380_4 = r11 + 0xfffffff8
      *[ram]unique_8380_4 = r1
      // 0X10694 ldr r1, [fp, #-0x20]
      unique_8380_4 = r11 + 0xffffffe0
      r1 = *[ram]unique_8380_4
      // 0X10698 add r3, r1, r3
      shift_carry = CY
      tmpCY = carry(r1, r3)
      tmpOV = scarry(r1, r3)
      r3 = r1 + r3
      tmpNG = r3 s< 0x0
      tmpZR = r3 == 0x0
      // 0X1069C ldr r1, [pc, #0xb4]
      r1 = *[ram]0x10758
      // 0X106A0 ldrb r2, [r1, r2]
      unique_8480_4 = r1 + r2
      unique_43880_1 = *[ram]unique_8480_4
      r2 = zext(unique_43880_1)
      // 0X106A4 strb r2, [r3]
      unique_8280_4 = r3 + 0x0
      unique_70c00_1 = SUBPIECE r2, 0x0
      *[ram]unique_8280_4 = unique_70c00_1
      // 0X106A8 ldr r3, [fp, #-8]
      unique_8380_4 = r11 + 0xfffffff8
      r3 = *[ram]unique_8380_4
      // 0X106AC add r2, r3, #1
      unique_2e80_4 = 0x1 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      tmpCY = carry(r3, 0x1)
      tmpOV = scarry(r3, 0x1)
      r2 = r3 + 0x1
      tmpNG = r2 s< 0x0
      tmpZR = r2 == 0x0
      // 0X106B0 str r2, [fp, #-8]
      unique_8380_4 = r11 + 0xfffffff8
      *[ram]unique_8380_4 = r2
      // 0X106B4 ldr r2, [fp, #-0x20]
      unique_8380_4 = r11 + 0xffffffe0
      r2 = *[ram]unique_8380_4
      // 0X106B8 add r3, r2, r3
      shift_carry = CY
      tmpCY = carry(r2, r3)
      tmpOV = scarry(r2, r3)
      r3 = r2 + r3
      tmpNG = r3 s< 0x0
      tmpZR = r3 == 0x0
      // 0X106BC mov r2, #0x3d
      unique_2e80_4 = 0x3d >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      r2 = 0x3d
      tmpNG = r2 s< 0x0
      tmpZR = r2 == 0x0
      tmpCY = shift_carry
      tmpOV = OV
      // 0X106C0 strb r2, [r3]
      unique_8280_4 = r3 + 0x0
      unique_70c00_1 = SUBPIECE r2, 0x0
      *[ram]unique_8280_4 = unique_70c00_1
      // 0X106C4 ldr r3, [fp, #-8]
      unique_8380_4 = r11 + 0xfffffff8
      r3 = *[ram]unique_8380_4
      // 0X106C8 add r2, r3, #1
      unique_2e80_4 = 0x1 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      tmpCY = carry(r3, 0x1)
      tmpOV = scarry(r3, 0x1)
      r2 = r3 + 0x1
      tmpNG = r2 s< 0x0
      tmpZR = r2 == 0x0
      // 0X106CC str r2, [fp, #-8]
      unique_8380_4 = r11 + 0xfffffff8
      *[ram]unique_8380_4 = r2
      // 0X106D0 ldr r2, [fp, #-0x20]
      unique_8380_4 = r11 + 0xffffffe0
      r2 = *[ram]unique_8380_4
      // 0X106D4 add r3, r2, r3
      shift_carry = CY
      tmpCY = carry(r2, r3)
      tmpOV = scarry(r2, r3)
      r3 = r2 + r3
      tmpNG = r3 s< 0x0
      tmpZR = r3 == 0x0
      // 0X106D8 mov r2, #0x3d
      unique_2e80_4 = 0x3d >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      r2 = 0x3d
      tmpNG = r2 s< 0x0
      tmpZR = r2 == 0x0
      tmpCY = shift_carry
      tmpOV = OV
      // 0X106DC strb r2, [r3]
      unique_8280_4 = r3 + 0x0
      unique_70c00_1 = SUBPIECE r2, 0x0
      *[ram]unique_8280_4 = unique_70c00_1
    } else {
      // 0X1066C ldr r3, [fp, #-0x10]
      unique_8380_4 = r11 + 0xfffffff0
      r3 = *[ram]unique_8380_4
      // 0X10670 cmp r3, #2
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
      if (ZR) {
        // 0X106E4 ldrb r3, [fp, #-0x12]
        unique_8380_4 = r11 + 0xffffffee
        unique_43880_1 = *[ram]unique_8380_4
        r3 = zext(unique_43880_1)
        // 0X106E8 lsl r3, r3, #2
        unique_3280_4 = 0x20 - 0x2
        unique_3300_4 = r3 >> unique_3280_4
        unique_3400_4 = unique_3300_4 & 0x1
        shift_carry = SUBPIECE unique_3400_4, 0x0
        unique_3580_4 = r3 << 0x2
        r3 = unique_3580_4
        tmpNG = r3 s< 0x0
        tmpZR = r3 == 0x0
        tmpCY = shift_carry
        tmpOV = OV
        // 0X106EC and r2, r3, #0x3c
        unique_2e80_4 = 0x3c >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        r2 = r3 & 0x3c
        tmpCY = shift_carry
        tmpOV = OV
        tmpNG = r2 s< 0x0
        tmpZR = r2 == 0x0
        // 0X106F0 ldr r3, [fp, #-8]
        unique_8380_4 = r11 + 0xfffffff8
        r3 = *[ram]unique_8380_4
        // 0X106F4 add r1, r3, #1
        unique_2e80_4 = 0x1 >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        tmpCY = carry(r3, 0x1)
        tmpOV = scarry(r3, 0x1)
        r1 = r3 + 0x1
        tmpNG = r1 s< 0x0
        tmpZR = r1 == 0x0
        // 0X106F8 str r1, [fp, #-8]
        unique_8380_4 = r11 + 0xfffffff8
        *[ram]unique_8380_4 = r1
        // 0X106FC ldr r1, [fp, #-0x20]
        unique_8380_4 = r11 + 0xffffffe0
        r1 = *[ram]unique_8380_4
        // 0X10700 add r3, r1, r3
        shift_carry = CY
        tmpCY = carry(r1, r3)
        tmpOV = scarry(r1, r3)
        r3 = r1 + r3
        tmpNG = r3 s< 0x0
        tmpZR = r3 == 0x0
        // 0X10704 ldr r1, [pc, #0x4c]
        r1 = *[ram]0x10758
        // 0X10708 ldrb r2, [r1, r2]
        unique_8480_4 = r1 + r2
        unique_43880_1 = *[ram]unique_8480_4
        r2 = zext(unique_43880_1)
        // 0X1070C strb r2, [r3]
        unique_8280_4 = r3 + 0x0
        unique_70c00_1 = SUBPIECE r2, 0x0
        *[ram]unique_8280_4 = unique_70c00_1
        // 0X10710 ldr r3, [fp, #-8]
        unique_8380_4 = r11 + 0xfffffff8
        r3 = *[ram]unique_8380_4
        // 0X10714 add r2, r3, #1
        unique_2e80_4 = 0x1 >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        tmpCY = carry(r3, 0x1)
        tmpOV = scarry(r3, 0x1)
        r2 = r3 + 0x1
        tmpNG = r2 s< 0x0
        tmpZR = r2 == 0x0
        // 0X10718 str r2, [fp, #-8]
        unique_8380_4 = r11 + 0xfffffff8
        *[ram]unique_8380_4 = r2
        // 0X1071C ldr r2, [fp, #-0x20]
        unique_8380_4 = r11 + 0xffffffe0
        r2 = *[ram]unique_8380_4
        // 0X10720 add r3, r2, r3
        shift_carry = CY
        tmpCY = carry(r2, r3)
        tmpOV = scarry(r2, r3)
        r3 = r2 + r3
        tmpNG = r3 s< 0x0
        tmpZR = r3 == 0x0
        // 0X10724 mov r2, #0x3d
        unique_2e80_4 = 0x3d >> 0x1f
        unique_2f00_1 = 0x0 == 0x0
        unique_2f80_1 = unique_2f00_1 && CY
        unique_3000_1 = 0x0 != 0x0
        unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
        unique_3100_1 = unique_3000_1 && unique_3080_1
        shift_carry = unique_2f80_1 || unique_3100_1
        r2 = 0x3d
        tmpNG = r2 s< 0x0
        tmpZR = r2 == 0x0
        tmpCY = shift_carry
        tmpOV = OV
        // 0X10728 strb r2, [r3]
        unique_8280_4 = r3 + 0x0
        unique_70c00_1 = SUBPIECE r2, 0x0
        *[ram]unique_8280_4 = unique_70c00_1
        // 0X1072C mov r0, r0
        r0 = r0
      } else {
      }
    }
    // 0X10730 ldr r2, [fp, #-0x20]
    unique_8380_4 = r11 + 0xffffffe0
    r2 = *[ram]unique_8380_4
    // 0X10734 ldr r3, [fp, #-8]
    unique_8380_4 = r11 + 0xfffffff8
    r3 = *[ram]unique_8380_4
    // 0X10738 add r3, r2, r3
    shift_carry = CY
    tmpCY = carry(r2, r3)
    tmpOV = scarry(r2, r3)
    r3 = r2 + r3
    tmpNG = r3 s< 0x0
    tmpZR = r3 == 0x0
    // 0X1073C mov r2, #0
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
    // 0X10740 strb r2, [r3]
    unique_8280_4 = r3 + 0x0
    unique_70c00_1 = SUBPIECE r2, 0x0
    *[ram]unique_8280_4 = unique_70c00_1
    // 0X10744 ldr r3, [fp, #-8]
    unique_8380_4 = r11 + 0xfffffff8
    r3 = *[ram]unique_8380_4
    // 0X10748 mov r0, r3
    r0 = r3
    // 0X1074C add sp, fp, #0
    unique_2e80_4 = 0x0 >> 0x1f
    unique_2f00_1 = 0x0 == 0x0
    unique_2f80_1 = unique_2f00_1 && CY
    unique_3000_1 = 0x0 != 0x0
    unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
    unique_3100_1 = unique_3000_1 && unique_3080_1
    shift_carry = unique_2f80_1 || unique_3100_1
    tmpCY = carry(r11, 0x0)
    tmpOV = scarry(r11, 0x0)
    sp = r11 + 0x0
    tmpNG = sp s< 0x0
    tmpZR = sp == 0x0
    // 0X10750 pop {fp}
    unique_8800_4 = sp
    sp = sp + 0x4
    r11 = *[ram]unique_8800_4
    // 0X10754 bx lr
    unique_0_4 = lr & 0x1
    ISAModeSwitch = unique_0_4 != 0x0
    TB = ISAModeSwitch
    pc = lr & 0xfffffffe
    return pc
  }
