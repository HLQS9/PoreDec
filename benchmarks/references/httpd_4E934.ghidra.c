
undefined4 FUN_0004e934(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  void *__s2;
  void *__s2_00;
  uint uVar6;
  int iStack_28;
  undefined4 uStack_24;
  
  if (param_1 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    iVar5 = 0;
    iStack_28 = param_1;
    uStack_24 = param_2;
    FUN_0004e8bc(&iStack_28);
    uVar6 = 0;
    while (uVar4 = FUN_000a6200(), uVar6 < uVar4) {
      __s2_00 = (void *)(param_1 + iVar5);
      iVar2 = FUN_0004d6fc(__s2_00);
      if (iVar2 == 0) {
        return 0x1399;
      }
      iVar2 = memcmp(&iStack_28,__s2_00,6);
      if (iVar2 == 0) {
        return 0x139b;
      }
      iVar5 = iVar5 + 6;
      uVar6 = uVar6 + 1;
      __s2 = (void *)(param_1 + iVar5);
      for (uVar4 = uVar6; uVar3 = FUN_000a6200(), uVar4 < uVar3; uVar4 = uVar4 + 1) {
        iVar2 = memcmp(__s2_00,__s2,6);
        if (iVar2 == 0) {
          return 0x139a;
        }
        __s2 = (void *)((int)__s2 + 6);
      }
    }
    uVar1 = 0;
  }
  return uVar1;
}

