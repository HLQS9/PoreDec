
undefined4 main(int param_1,int param_2)

{
  undefined4 uVar1;
  
  puts(DAT_0001049c);
  if (param_1 == 2) {
    if (**(char **)(param_2 + 4) == 'a') {
      puts(DAT_000104a4);
    }
    else {
      puts(DAT_000104a8);
    }
    puts(DAT_000104ac);
    uVar1 = 0;
  }
  else {
    puts(DAT_000104a0);
    uVar1 = 1;
  }
  return uVar1;
}

