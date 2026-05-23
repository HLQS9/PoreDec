"""
ELF加载器实现
"""
from typing import Optional
from elftools.elf.elffile import ELFFile


__all__ = ["ELFLoader", "ArchitectureException"]


class ArchitectureException(Exception):
    """当遇到不支持的架构时，抛出此异常"""


class ELFLoader:
    """ELF文件的加载器"""

    def __init__(self, filename):
        self.elf = elf = ELFFile(open(filename, "rb"))
        self.arch = elf.get_machine_arch()
        self.bits = elf.elfclass
        self.entry = elf.header.e_entry

        self.curr_address = self.entry
        self.curr_segment = None
        self.curr_offset = 0
        self.seek(self.entry)

    def seek(self, vaddr):
        """让加载器跳转到给定的虚拟程序地址
        :param vaddr: 虚拟程序地址
        """
        for segment in self.elf.iter_segments():
            if segment.header.p_type == "PT_LOAD":
                if (
                    segment.header.p_vaddr
                    <= vaddr
                    < segment.header.p_vaddr + segment.header.p_memsz
                ):
                    self.curr_segment = segment
                    self.curr_offset = vaddr - segment.header.p_vaddr
                    self.curr_address = vaddr
                    return True
        return False

    def read(self, size) -> Optional[bytes]:
        """
        从当前位置读取指定长度的数据。需要先通过 meth:`seek` 跳转到目标地址

        :param size: 要读取的数据长度。
        :return: 读取的数据，如果当前段为空则返回 None。
        """
        if self.curr_segment is None:
            return None
        if self.curr_offset + size > self.curr_segment.header.p_memsz:
            size = self.curr_segment.header.p_memsz - self.curr_offset
        data = self.curr_segment.data()[self.curr_offset : self.curr_offset + size]
        self.curr_offset += size
        self.curr_address += size
        return data
