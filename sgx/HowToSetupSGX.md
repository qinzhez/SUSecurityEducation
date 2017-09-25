This document describes how to enable SGX on a MSI laptop
===


Check SGX feature
---

Read this page to learn how to check if SGX feature is equipped and enabled on your platform

https://jbeekman.nl/blog/2015/10/sgx-hardware-first-look/

Pay attention of bit18 of the word at offset 0x3a in MSR message. If it is not set, the SGX is not enabled in your platform. You need to first get it enabled. 


Enable SGX 
---

Some OEM has BIOS interface for user to enable SGX feature. MSI laptop doesn't have that. So we need to call a function named as "sgx_enable_device" to enable SGX. Unfortunately, this API is only available in Windows. So to enable SGX, we need to first run a sample code comes with SGX SDK for windows, and steps are: 1, Install Visual Studio 2013 2, Install Intel SGX SDK 3, Copy SampleEnclave to your directory 4, Open and build SampleEnclave solution.5, Run the solution 6, Reboot your machine.


Install Linux
---

To make MSI network card functional, we need to install Ubuntu version > 15.04.  To do that, we need to first select Legacy mode in BIOS boot menu. We could switch back to UEFI to boot to Windows. There's a graphics card problem with this new Ubuntu version, you may stuck at this message at bootup time - "fb switching to nouveaufb from vesa". To workaround that, edit your grub menu, add one option to the boot entry "nomodeset". When you get into the system, edit /boot/grub/grub.cfg to add the same option permanently.

 
