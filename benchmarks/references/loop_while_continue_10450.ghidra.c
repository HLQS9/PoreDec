
undefined4 main(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int local_c;
  
  puts(DAT_000104c8);
  local_c = 0;
  while (local_c < 0x65) {
    local_c = local_c + 1;
    if (0x31 < local_c) {
      printf(DAT_000104cc,local_c,param_3,local_c,param_2,param_1);
    }
  }
  puts(DAT_000104d0);
  return 0;
}

