  // 0X4E934 push {r0, r1, r4, r5, r6, r7, r8, sb, sl, lr}
  mult_addr = sp - 0x4
  *[ram]mult_addr = lr
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r10
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r9
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r8
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r7
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r6
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r5
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r4
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r1
  mult_addr = mult_addr - 0x4
  *[ram]mult_addr = r0
  mult_addr = mult_addr - 0x4
  sp = mult_addr + 0x4
  // 0X4E938 subs r8, r0, #0
  unique_2e80_4 = 0x0 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  tmpCY = 0x0 <= r0
  tmpOV = sborrow(r0, 0x0)
  r8 = r0 - 0x0
  tmpNG = r8 s< 0x0
  tmpZR = r8 == 0x0
  CY = tmpCY
  ZR = tmpZR
  NG = tmpNG
  OV = tmpOV
  // 0X4E93C mvneq r0, #0
  unique_2680_1 = !ZR
  unique_2e80_4 = 0x0 >> 0x1f
  unique_2f00_1 = 0x0 == 0x0
  unique_2f80_1 = unique_2f00_1 && CY
  unique_3000_1 = 0x0 != 0x0
  unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
  unique_3100_1 = unique_3000_1 && unique_3080_1
  shift_carry = unique_2f80_1 || unique_3100_1
  r0 = ~0x0
  tmpNG = r0 s< 0x0
  tmpZR = r0 == 0x0
  tmpCY = shift_carry
  tmpOV = OV
  if (ZR) {
    goto LAB_4E9F0
  } else {
LAB_4E944:
    // 0X4E944 mov r0, sp
    r0 = sp
    // 0X4E948 mov r4, #0
    unique_2e80_4 = 0x0 >> 0x1f
    unique_2f00_1 = 0x0 == 0x0
    unique_2f80_1 = unique_2f00_1 && CY
    unique_3000_1 = 0x0 != 0x0
    unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
    unique_3100_1 = unique_3000_1 && unique_3080_1
    shift_carry = unique_2f80_1 || unique_3100_1
    r4 = 0x0
    tmpNG = r4 s< 0x0
    tmpZR = r4 == 0x0
    tmpCY = shift_carry
    tmpOV = OV
    // 0X4E94C bl #0x4e8bc
    lr = 0x4e950
    call ram_4e8bc_4
    // 0X4E950 mov sl, r4
    r10 = r4
    // 0X4E954 mov sb, sp
    r9 = sp
    while (1) {
      // 0X4E9C8 bl #0xa6200
      lr = 0x4e9cc
      call ram_a6200_4
      // 0X4E9CC cmp sl, r0
      shift_carry = CY
      tmpCY = r0 <= r10
      tmpOV = sborrow(r10, r0)
      unique_42900_4 = r10 - r0
      tmpNG = unique_42900_4 s< 0x0
      tmpZR = unique_42900_4 == 0x0
      CY = tmpCY
      ZR = tmpZR
      NG = tmpNG
      OV = tmpOV
      // 0X4E9D0 blo #0x4e95c
      unique_1b80_1 = !CY
      if (unique_1b80_1) {
LAB_4E95C:
        // 0X4E95C add r7, r8, r4
        shift_carry = CY
        tmpCY = carry(r8, r4)
        tmpOV = scarry(r8, r4)
        r7 = r8 + r4
        tmpNG = r7 s< 0x0
        tmpZR = r7 == 0x0
        // 0X4E960 mov r0, r7
        r0 = r7
        // 0X4E964 bl #0x4d6fc
        lr = 0x4e968
        call ram_4d6fc_4
        // 0X4E968 cmp r0, #0
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
        if (ZR) {
LAB_4E9DC:
          // 0X4E9DC movw r0, #0x1399
          r0 = 0x1399
          goto LAB_4E9F0
        } else {
LAB_4E970:
          // 0X4E970 mov r0, sp
          r0 = sp
          // 0X4E974 mov r1, r7
          r1 = r7
          // 0X4E978 mov r2, #6
          unique_2e80_4 = 0x6 >> 0x1f
          unique_2f00_1 = 0x0 == 0x0
          unique_2f80_1 = unique_2f00_1 && CY
          unique_3000_1 = 0x0 != 0x0
          unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
          unique_3100_1 = unique_3000_1 && unique_3080_1
          shift_carry = unique_2f80_1 || unique_3100_1
          r2 = 0x6
          tmpNG = r2 s< 0x0
          tmpZR = r2 == 0x0
          tmpCY = shift_carry
          tmpOV = OV
          // 0X4E97C bl #0xb0ac
          lr = 0x4e980
          call ram_b0ac_4
          // 0X4E980 cmp r0, #0
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
          if (ZR) {
LAB_4E9E4:
            // 0X4E9E4 movw r0, #0x139b
            r0 = 0x139b
LAB_4E9F0:
            // 0X4E9F0 pop {r2, r3, r4, r5, r6, r7, r8, sb, sl, pc}
            mult_addr = sp
            r2 = *[ram]mult_addr
            mult_addr = mult_addr + 0x4
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
            r8 = *[ram]mult_addr
            mult_addr = mult_addr + 0x4
            r9 = *[ram]mult_addr
            mult_addr = mult_addr + 0x4
            r10 = *[ram]mult_addr
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
LAB_4E988:
            // 0X4E988 add sl, sl, #1
            unique_2e80_4 = 0x1 >> 0x1f
            unique_2f00_1 = 0x0 == 0x0
            unique_2f80_1 = unique_2f00_1 && CY
            unique_3000_1 = 0x0 != 0x0
            unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
            unique_3100_1 = unique_3000_1 && unique_3080_1
            shift_carry = unique_2f80_1 || unique_3100_1
            tmpCY = carry(r10, 0x1)
            tmpOV = scarry(r10, 0x1)
            r10 = r10 + 0x1
            tmpNG = r10 s< 0x0
            tmpZR = r10 == 0x0
            // 0X4E98C add r4, r4, #6
            unique_2e80_4 = 0x6 >> 0x1f
            unique_2f00_1 = 0x0 == 0x0
            unique_2f80_1 = unique_2f00_1 && CY
            unique_3000_1 = 0x0 != 0x0
            unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
            unique_3100_1 = unique_3000_1 && unique_3080_1
            shift_carry = unique_2f80_1 || unique_3100_1
            tmpCY = carry(r4, 0x6)
            tmpOV = scarry(r4, 0x6)
            r4 = r4 + 0x6
            tmpNG = r4 s< 0x0
            tmpZR = r4 == 0x0
            // 0X4E990 add r6, r8, r4
            shift_carry = CY
            tmpCY = carry(r8, r4)
            tmpOV = scarry(r8, r4)
            r6 = r8 + r4
            tmpNG = r6 s< 0x0
            tmpZR = r6 == 0x0
            // 0X4E994 mov r5, sl
            r5 = r10
            while (1) {
              // 0X4E9BC bl #0xa6200
              lr = 0x4e9c0
              call ram_a6200_4
              // 0X4E9C0 cmp r5, r0
              shift_carry = CY
              tmpCY = r0 <= r5
              tmpOV = sborrow(r5, r0)
              unique_42900_4 = r5 - r0
              tmpNG = unique_42900_4 s< 0x0
              tmpZR = unique_42900_4 == 0x0
              CY = tmpCY
              ZR = tmpZR
              NG = tmpNG
              OV = tmpOV
              // 0X4E9C4 blo #0x4e99c
              unique_1b80_1 = !CY
              if (!unique_1b80_1) {
                break
              }
              // 0X4E99C mov r1, r6
              r1 = r6
              // 0X4E9A0 mov r0, r7
              r0 = r7
              // 0X4E9A4 mov r2, #6
              unique_2e80_4 = 0x6 >> 0x1f
              unique_2f00_1 = 0x0 == 0x0
              unique_2f80_1 = unique_2f00_1 && CY
              unique_3000_1 = 0x0 != 0x0
              unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
              unique_3100_1 = unique_3000_1 && unique_3080_1
              shift_carry = unique_2f80_1 || unique_3100_1
              r2 = 0x6
              tmpNG = r2 s< 0x0
              tmpZR = r2 == 0x0
              tmpCY = shift_carry
              tmpOV = OV
              // 0X4E9A8 add r6, r6, #6
              unique_2e80_4 = 0x6 >> 0x1f
              unique_2f00_1 = 0x0 == 0x0
              unique_2f80_1 = unique_2f00_1 && CY
              unique_3000_1 = 0x0 != 0x0
              unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
              unique_3100_1 = unique_3000_1 && unique_3080_1
              shift_carry = unique_2f80_1 || unique_3100_1
              tmpCY = carry(r6, 0x6)
              tmpOV = scarry(r6, 0x6)
              r6 = r6 + 0x6
              tmpNG = r6 s< 0x0
              tmpZR = r6 == 0x0
              // 0X4E9AC bl #0xb0ac
              lr = 0x4e9b0
              call ram_b0ac_4
              // 0X4E9B0 cmp r0, #0
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
                // 0X4E9B8 add r5, r5, #1
                unique_2e80_4 = 0x1 >> 0x1f
                unique_2f00_1 = 0x0 == 0x0
                unique_2f80_1 = unique_2f00_1 && CY
                unique_3000_1 = 0x0 != 0x0
                unique_3080_1 = SUBPIECE unique_2e80_4, 0x0
                unique_3100_1 = unique_3000_1 && unique_3080_1
                shift_carry = unique_2f80_1 || unique_3100_1
                tmpCY = carry(r5, 0x1)
                tmpOV = scarry(r5, 0x1)
                r5 = r5 + 0x1
                tmpNG = r5 s< 0x0
                tmpZR = r5 == 0x0
                continue
              }
              // 0X4E9EC movw r0, #0x139a
              r0 = 0x139a
              goto LAB_4E9F0
            }
          }
        }
      } else {
LAB_4E9D4:
        // 0X4E9D4 mov r0, #0
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
        goto LAB_4E9F0
      }
    }
  }
