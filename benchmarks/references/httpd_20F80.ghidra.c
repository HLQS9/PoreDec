
undefined4 FUN_00020f80(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  size_t sVar3;
  void *__s;
  char acStack_84 [100];
  undefined auStack_20 [16];
  
  iVar1 = DAT_00021048;
  if (param_3 != 0 && *(void **)(DAT_00021048 + 4) != (void *)0x0) {
    free(*(void **)(DAT_00021048 + 4));
    *(undefined4 *)(iVar1 + 4) = 0;
  }
  if (*(int *)(DAT_00021048 + 4) == 0) {
    iVar1 = thunk_FUN_000a680c();
    if (iVar1 == 1 && param_2 == 1) {
      thunk_FUN_000681e4();
      FUN_000b3cf8(param_1,auStack_20);
      uVar2 = FUN_000a61e0();
      sprintf(acStack_84,DAT_0002104c,uVar2,auStack_20);
      system(acStack_84);
    }
    sVar3 = FUN_00020ef8(param_2);
    __s = malloc(sVar3);
    *(void **)(DAT_00021048 + 4) = __s;
    sVar3 = FUN_00020ef8(param_2);
    memset(__s,0,sVar3);
  }
  return *(undefined4 *)(DAT_00021048 + 4);
}

