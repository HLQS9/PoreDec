
void FUN_0004855c(byte *param_1)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  pbVar2 = param_1;
  do {
    iVar1 = toupper((uint)*pbVar2);
    pbVar3 = pbVar2 + 1;
    *pbVar2 = (byte)iVar1;
    pbVar2 = pbVar3;
  } while (pbVar3 != param_1 + 0x12);
  return;
}

