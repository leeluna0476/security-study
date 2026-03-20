# Ubuntu Installation on Virtual x86_64 using QEMU
## 1. Create a Disk Space for the Machine
```bash
qemu-img create -f qcow2 ubuntu_disk.qcow2 20G
```
## 2. Boot an Ubuntu Installer
```bash
qemu-system-x86_64 -m 4G -drive file=ubuntu_disk.qcow2 -cdrom ubuntu-24.04.4-live-server-amd64.iso -boot d
```
- `-m`: main memory space
- `-drive file=...`: a virtual disk space created on `1.`
- `-cdrom`: OS image
- `-boot d`: boot from the cdrom by priority
  - you will see the OS installation page
## 3. Start the Machine after Intallation
```bash
qemu-system-x86_64 -m 4G -drive file=ubuntu_disk.qcow2 -cdrom ubuntu-24.04.4-live-server-amd64.iso
```
- no `-boot d`.
  - boots from the disk which has the OS installed on it
