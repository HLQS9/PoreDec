
undefined4 main(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 local_c;
  
  puts(DAT_000104b4);
  for (local_c = 0; local_c < 10; local_c = local_c + 1) {
    printf(DAT_000104b8,local_c,param_3,local_c,param_2,param_1);
  }
  puts(DAT_000104bc);
  return 0;
}

