
undefined4 FUN_00021974(uint param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  
  puts(DAT_000219c4);
  iVar2 = DAT_000219c8;
  if (0x12 < param_1) {
    return 0;
  }
  do {
    if (*(uint *)(iVar2 + 4) == param_1) {
      *(undefined4 *)(iVar2 + 0x50) = param_2;
      return 1;
    }
    piVar1 = (int *)(iVar2 + 0x54);
    iVar2 = *piVar1;
  } while (*piVar1 != 0);
  return 0;
}

