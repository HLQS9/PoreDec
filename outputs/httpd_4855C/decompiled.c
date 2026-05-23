  // 0X4855C push {r3, r4, r5, lr}
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
  // 0X48560 mov r4, r0
  r4 = r0
  // 0X48564 add r5, r0, #0x12
  unique_2e80_4 = 0x12 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = carry(r0, 0x12)
  tmpOV = scarry(r0, 0x12)
  r5 = r0 + 0x12
  tmpNG = r5 s< 0x0
  tmpZR = r5 == 0x0
  // 0X48568 ldrb r0, [r4]
  unique_8280_4 = r4 + 0x0
  unique_43880_1 = *[ram]unique_8280_4
  r0 = zext(unique_43880_1)
  // 0X4856C bl #0xaa10
  lr = 0x48570
  call ram_aa10_4
  // 0X48570 strb r0, [r4], #1
  unique_8800_4 = r4
  r4 = r4 + 0x1
  unique_70c00_1 = SUBPIECE r0, 0x0
  *[ram]unique_8800_4 = unique_70c00_1
  // 0X48574 cmp r4, r5
  shift_carry = CY
  tmpCY = r5 <= r4
  tmpOV = sborrow(r4, r5)
  unique_42900_4 = r4 - r5
  tmpNG = unique_42900_4 s< 0x0
  tmpZR = unique_42900_4 == 0x0
  CY = tmpCY
  ZR = tmpZR
  NG = tmpNG
  OV = tmpOV
  // 0X48578 bne #0x48568
  unique_1a80_1 = !ZR
  if (unique_1a80_1) {
    do {
      // 0X48568 ldrb r0, [r4]
      unique_8280_4 = r4 + 0x0
      unique_43880_1 = *[ram]unique_8280_4
      r0 = zext(unique_43880_1)
      // 0X4856C bl #0xaa10
      lr = 0x48570
      call ram_aa10_4
      // 0X48570 strb r0, [r4], #1
      unique_8800_4 = r4
      r4 = r4 + 0x1
      unique_70c00_1 = SUBPIECE r0, 0x0
      *[ram]unique_8800_4 = unique_70c00_1
      // 0X48574 cmp r4, r5
      shift_carry = CY
      tmpCY = r5 <= r4
      tmpOV = sborrow(r4, r5)
      unique_42900_4 = r4 - r5
      tmpNG = unique_42900_4 s< 0x0
      tmpZR = unique_42900_4 == 0x0
      CY = tmpCY
      ZR = tmpZR
      NG = tmpNG
      OV = tmpOV
      // 0X48578 bne #0x48568
      unique_1a80_1 = !ZR
    } while (unique_1a80_1);
  }
  // 0X4857C pop {r3, r4, r5, pc}
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
