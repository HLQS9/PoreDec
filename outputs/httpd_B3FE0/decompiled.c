  // 0XB3FE0 push {r3, r4, r5, r6, r7, lr}
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
  *[ram]mult_addr = r3
  mult_addr = mult_addr - 0x4
  sp = mult_addr + 0x4
  // 0XB3FE4 subs r4, r0, #0
  unique_2e80_4 = 0x0 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x0 <= r0
  tmpOV = sborrow(r0, 0x0)
  r4 = r0 - 0x0
  tmpNG = r4 s< 0x0
  tmpZR = r4 == 0x0
  CY = tmpCY
  ZR = tmpZR
  NG = tmpNG
  OV = tmpOV
  // 0XB3FE8 mov r5, r1
  r5 = r1
  if (ZR) {
    goto LAB_B4050
  } else {
LAB_B3FF0:
    // 0XB3FF0 cmp r1, #0
    unique_2e80_4 = 0x0 >> 0x1f
    unique_2f00_1 = 0x0 == 0x0
    unique_2f80_1 = unique_2f00_1 && CY
    unique_3000_1 = 0x0 != 0x0
    unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
    unique_3100_1 = unique_3000_1 && unique_3080_1
    shift_carry = unique_2f80_1 || unique_3100_1
    tmpCY = 0x0 <= r1
    tmpOV = sborrow(r1, 0x0)
    unique_42800_4 = r1 - 0x0
    tmpNG = unique_42800_4 s< 0x0
    tmpZR = unique_42800_4 == 0x0
    CY = tmpCY
    ZR = tmpZR
    NG = tmpNG
    OV = tmpOV
    // 0XB3FF4 moveq r4, r1
    unique_2680_1 = !ZR
    r4 = r1
    if (ZR) {
      goto LAB_B4050
    } else {
LAB_B3FFC:
      // 0XB3FFC mov r0, r1
      r0 = r1
      // 0XB4000 bl #0xac2c
      lr = 0xb4004
      call ram_ac2c_4
      // 0XB4004 mov r6, r0
      r6 = r0
      // 0XB4044 ldr r4, [r4, #4]
      unique_8280_4 = r4 + 0x4
      r4 = *[ram]unique_8280_4
      // 0XB4048 cmp r4, #0
      unique_2e80_4 = 0x0 >> 0x1f
      unique_2f00_1 = 0x0 == 0x0
      unique_2f80_1 = unique_2f00_1 && CY
      unique_3000_1 = 0x0 != 0x0
      unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
      unique_3100_1 = unique_3000_1 && unique_3080_1
      shift_carry = unique_2f80_1 || unique_3100_1
      tmpCY = 0x0 <= r4
      tmpOV = sborrow(r4, 0x0)
      unique_42800_4 = r4 - 0x0
      tmpNG = unique_42800_4 s< 0x0
      tmpZR = unique_42800_4 == 0x0
      CY = tmpCY
      ZR = tmpZR
      NG = tmpNG
      OV = tmpOV
      // 0XB404C bne #0xb400c
      unique_1a80_1 = !ZR
      if (unique_1a80_1) {
LAB_B400C:
        while (1) {
          // 0XB400C ldr r7, [r4]
          unique_8280_4 = r4 + 0x0
          r7 = *[ram]unique_8280_4
          // 0XB4010 cmp r7, #0
          unique_2e80_4 = 0x0 >> 0x1f
          unique_2f00_1 = 0x0 == 0x0
          unique_2f80_1 = unique_2f00_1 && CY
          unique_3000_1 = 0x0 != 0x0
          unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
          unique_3100_1 = unique_3000_1 && unique_3080_1
          shift_carry = unique_2f80_1 || unique_3100_1
          tmpCY = 0x0 <= r7
          tmpOV = sborrow(r7, 0x0)
          unique_42800_4 = r7 - 0x0
          tmpNG = unique_42800_4 s< 0x0
          tmpZR = unique_42800_4 == 0x0
          CY = tmpCY
          ZR = tmpZR
          NG = tmpNG
          OV = tmpOV
          if (!ZR) {
            break
          }
          // 0XB4044 ldr r4, [r4, #4]
          unique_8280_4 = r4 + 0x4
          r4 = *[ram]unique_8280_4
          // 0XB4048 cmp r4, #0
          unique_2e80_4 = 0x0 >> 0x1f
          unique_2f00_1 = 0x0 == 0x0
          unique_2f80_1 = unique_2f00_1 && CY
          unique_3000_1 = 0x0 != 0x0
          unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
          unique_3100_1 = unique_3000_1 && unique_3080_1
          shift_carry = unique_2f80_1 || unique_3100_1
          tmpCY = 0x0 <= r4
          tmpOV = sborrow(r4, 0x0)
          unique_42800_4 = r4 - 0x0
          tmpNG = unique_42800_4 s< 0x0
          tmpZR = unique_42800_4 == 0x0
          CY = tmpCY
          ZR = tmpZR
          NG = tmpNG
          OV = tmpOV
          // 0XB404C bne #0xb400c
          unique_1a80_1 = !ZR
          if (!unique_1a80_1) {
            break
          }
        }
      } else {
        goto LAB_B4050
      }
    }
  }
LAB_B4050:
  // 0XB4050 mov r0, r4
  r0 = r4
  // 0XB4054 pop {r3, r4, r5, r6, r7, pc}
  mult_addr = sp
  r3 = *[ram]mult_addr
  mult_addr = mult_addr + 0x4
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
