# BAR Memory Dumper

Maps 4 KB of a device’s PCI BAR and dumps it in Verilog-style to both the terminal and `output.txt`.  
**Secure Boot must be disabled** for direct PCI access.

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
