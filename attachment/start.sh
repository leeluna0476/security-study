#!/bin/bash

read -p 'Enter your disk name: ' DISK
read -p 'Enter your port number for ssh: ' SSHPORT
qemu-system-x86_64 -m 4G -drive file=$DISK -netdev user,id=net0,hostfwd=tcp::$SSHPORT-:22 -device virtio-net-pci,netdev=net0
