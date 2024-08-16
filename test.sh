if grub-file --is-x86-multiboot build/borialis.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi