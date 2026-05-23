
undefined4 main(int param_1,int param_2)

{
  undefined4 local_c;
  
  puts(DAT_00010490);
  for (local_c = 0; local_c < param_1; local_c = local_c + 1) {
    puts(*(char **)(param_2 + local_c * 4));
  }
  return 0;
}

