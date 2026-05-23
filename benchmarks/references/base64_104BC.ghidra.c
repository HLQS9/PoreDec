
int base64_encode(int param_1,uint param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  undefined local_16;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_14 = 0;
  local_16 = 0;
  local_c = 0;
  for (local_10 = 0; local_10 < param_2; local_10 = local_10 + 1) {
    bVar1 = *(byte *)(param_1 + local_10);
    if (local_14 == 2) {
      local_14 = 0;
      iVar2 = local_c + 1;
      *(undefined *)(param_3 + local_c) =
           *(undefined *)(DAT_00010758 + ((local_16 & 0xf) << 2 | (uint)(bVar1 >> 6)));
      local_c = local_c + 2;
      *(undefined *)(param_3 + iVar2) = *(undefined *)(DAT_00010758 + (bVar1 & 0x3f));
    }
    else if (local_14 < 3) {
      if (local_14 == 0) {
        local_14 = 1;
        *(undefined *)(param_3 + local_c) = *(undefined *)(DAT_00010758 + (uint)(bVar1 >> 2));
        local_c = local_c + 1;
      }
      else if (local_14 == 1) {
        local_14 = 2;
        *(undefined *)(param_3 + local_c) =
             *(undefined *)(DAT_00010758 + ((local_16 & 3) << 4 | (uint)(bVar1 >> 4)));
        local_c = local_c + 1;
      }
    }
    local_16 = bVar1;
  }
  if (local_14 == 1) {
    *(undefined *)(param_3 + local_c) = *(undefined *)(DAT_00010758 + (local_16 & 3) * 0x10);
    iVar2 = local_c + 2;
    *(undefined *)(param_3 + local_c + 1) = 0x3d;
    local_c = local_c + 3;
    *(undefined *)(param_3 + iVar2) = 0x3d;
  }
  else if (local_14 == 2) {
    iVar2 = local_c + 1;
    *(undefined *)(param_3 + local_c) = *(undefined *)(DAT_00010758 + (local_16 & 0xf) * 4);
    local_c = local_c + 2;
    *(undefined *)(param_3 + iVar2) = 0x3d;
  }
  *(undefined *)(param_3 + local_c) = 0;
  return local_c;
}

