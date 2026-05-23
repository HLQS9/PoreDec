
int FUN_00020814(undefined4 param_1)

{
  short sVar1;
  int iVar2;
  char acStack_20 [20];
  
  memset(acStack_20,0,0x10);
  FUN_000b3cf8(param_1,acStack_20);
  iVar2 = FUN_0004d530(acStack_20);
  if (iVar2 != 0) {
    inet_addr(acStack_20);
    sVar1 = FUN_0004e87c();
    iVar2 = (int)sVar1;
  }
  return iVar2;
}

