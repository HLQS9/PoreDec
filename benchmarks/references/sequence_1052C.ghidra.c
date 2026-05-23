
undefined4 main(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  char *pcStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  uint local_c;
  
  local_c = *DAT_000105b4;
  puts(DAT_000105b8);
  pcStack_1c = (char *)*DAT_000105bc;
  uStack_18 = DAT_000105bc[1];
  uStack_14 = DAT_000105bc[2];
  uStack_10 = DAT_000105bc[3];
  execve(DAT_000105c4,&pcStack_1c,(char **)*DAT_000105c0);
  iVar1 = puts(DAT_000105c8);
  if ((local_c ^ *DAT_000105b4) != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(iVar1,local_c ^ *DAT_000105b4,0,0,param_2,param_1);
  }
  return 0;
}

