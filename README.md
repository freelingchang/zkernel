mkernel
=======

This is a minimalist kernel which prints "`my first kernel`" on the screen and then hangs.

* The kernel is multi-boot compliant and loads with GRUB.


#### Build ####

```
./build.sh
```
#### Run ####

```
qemu-system-i386 -kernel kernel
```


#### Get to boot ####
GRUB requires your kernel executable to be of the pattern `kernel-<version>`.

So, rename the kernel:

```
mv kernel kernel-701
```

Copy it to your boot partition (assuming you are superuser):

```
cp kernel-701 /boot/kernel-701
```

Configure your grub/grub2 similar to what is given in `_grub_grub2_config` folder of [mkernel repo](http://github.com/arjun024/mkernel).

Reboot.

Voila!

![kernel screenshot](http://31.media.tumblr.com/1afd75b433b13df613fa0c2301977893/tumblr_inline_ncy1p0kSGj1rivrqc.png "Screenshot")
