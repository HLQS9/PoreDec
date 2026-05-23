
int FUN_000209ac(byte *param_1,char *param_2)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  char *__format;
  int iVar7;
  uint uVar8;
  char *__s;
  uint uVar9;
  byte local_1c [8];
  
  iVar5 = DAT_00020ab0;
  __s = param_2;
  while (*param_1 != 0) {
    iVar6 = 0;
    iVar7 = 0;
    do {
      bVar2 = *param_1;
      if (bVar2 != 0) {
        local_1c[iVar7] = bVar2;
        iVar6 = iVar6 + 1;
      }
      else {
        local_1c[iVar7] = 0;
      }
      iVar7 = iVar7 + 1;
      if (bVar2 != 0) {
        param_1 = param_1 + 1;
      }
    } while (iVar7 != 3);
    uVar1 = (uint)(local_1c[0] >> 2);
    uVar8 = (uint)(local_1c[1] >> 4) | (local_1c[0] & 3) << 4;
    uVar9 = (uint)(local_1c[2] >> 6) | (local_1c[1] & 0xf) << 2;
    if (iVar6 == 1) {
      sprintf(__s,DAT_00020ab4,(uint)*(byte *)(iVar5 + uVar1),(uint)*(byte *)(iVar5 + uVar8));
    }
    else {
      if (iVar6 == 2) {
        bVar2 = *(byte *)(iVar5 + uVar9);
        bVar3 = *(byte *)(iVar5 + uVar1);
        bVar4 = *(byte *)(iVar5 + uVar8);
        __format = DAT_00020ab8;
      }
      else {
        bVar2 = *(byte *)(iVar5 + uVar9);
        bVar3 = *(byte *)(iVar5 + uVar1);
        bVar4 = *(byte *)(iVar5 + uVar8);
        __format = DAT_00020abc;
      }
      sprintf(__s,__format,(uint)bVar3,(uint)bVar4,(uint)bVar2);
    }
    __s = __s + 4;
  }
  *__s = '\0';
  return (int)__s - (int)param_2;
}

