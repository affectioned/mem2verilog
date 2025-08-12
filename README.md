# mem2verilog

**If you daily-drive Windows:** You can make a persistent Ubuntu USB boot drive with [Rufus](https://rufus.ie/) that saves your data, so you can boot into Linux, run this tool, and then return to Windows without losing anything on your Ubuntu setup.

**If you’re new to compiling C on Linux:** Follow this guide to learn how to create and build the `.c` file:  
[https://medium.com/@filip.melka/your-first-c-program-on-linux-a-quick-guide-with-vim-and-vscodium-bc941228d4b2](https://medium.com/@filip.melka/your-first-c-program-on-linux-a-quick-guide-with-vim-and-vscodium-bc941228d4b2)

**About the code:** Based on the [DMA-CFW-Guide](https://github.com/Silverr12/DMA-CFW-Guide?tab=readme-ov-file#6-tlp-emulation) snippet, but improved for easier copy-pasting of larger BAR dumps.

----------

Maps 4 KB of a PCI BAR and dumps it in Verilog format to both terminal and `output.txt`.  
**Root required** & **Secure Boot must be disabled**.

## Build

```bash
gcc -o bardump bar.c
```

## Usage

```bash
sudo ./bardump <device_or_file>
# Example:
sudo ./bardump /sys/bus/pci/devices/0000:01:00.0/resource0
```

## Example Output

```
Opening File : /sys/bus/pci/devices/0000:01:00.0/resource0
PCI Memory mapped to: 0x7f8b2b1d4000.
16'h0000 : rd_rsp_data <= 32'hDEADBEEF;
16'h0004 : rd_rsp_data <= 32'h12345678;
...
```
