
undefined4 * FUN_000b3fe0(undefined4 *param_1,char *param_2)

{
  short sVar1;
  size_t sVar2;
  size_t sVar3;
  char *__s;
  
  if (param_1 != (undefined4 *)0x0) {
    if (param_2 == (char *)0x0) {
      param_1 = (undefined4 *)0x0;
    }
    else {
      sVar2 = strlen(param_2);
      do {
        param_1 = (undefined4 *)param_1[1];
        if (param_1 == (undefined4 *)0x0) {
          return (undefined4 *)0x0;
        }
        __s = (char *)*param_1;
      } while (((__s == (char *)0x0) || (sVar3 = strlen(__s), sVar3 != sVar2)) ||
              (sVar1 = FUN_000ca900(__s,param_2,sVar2), sVar1 != 0));
    }
  }
  return param_1;
}

