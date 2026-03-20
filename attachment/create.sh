#!/bin/bash

read -p 'Enter your image file name (.iso): ' IMG

qemu-img create -f qcow2 ubuntu_disk.qcow2 20G
qemu-system-x86_64 -m 4G -drive file=ubuntu_disk.qcow2 -cdrom $IMG -boot d
