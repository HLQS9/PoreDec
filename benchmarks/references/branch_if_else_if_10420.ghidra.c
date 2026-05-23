
undefined4 main(int param_1,int param_2)

{
  undefined4 uVar1;
  
  puts(DAT_00010490);
  if (param_1 < 2) {
    puts(DAT_00010494);
    uVar1 = 1;
  }
  else {
    if (**(char **)(param_2 + 4) == 'a') {
      puts(DAT_00010498);
    }
    puts(DAT_0001049c);
    uVar1 = 0;
  }
  return uVar1;
}

