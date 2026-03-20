#!/bin/bash

qemu-img create -f qcow2 ubuntu_disk.qcow2 20G
qemu-system-x86_64 -m 4G -drive file=ubuntu_disk.qcow2 -cdrom ubuntu-24.04.4-live-server-amd64.iso -boot d
