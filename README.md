# alsa-quadcapture
Workaround to make Roland Quad-Capture (UA-55) in 48kHz on Linux

> [!WARNING]
> This is a trial and error discovery which works with my hardware,
> I don't guarantee it will work for you or damage your hardware.

## How to
Set your quad-capture in 58Khz to do so you will need windows or mac using their [application](https://www.roland.com/global/products/quad-capture/downloads/).

Download your [Linux Kernel source](https://github.com/torvalds/linux).
Available also with patches in your distribution.

Update `quirks-table.h` file in `sound/usb` replacing Quad-capture entry.

### Add to Kernel
Compile and install the Kernel ([tutorial](https://davidaugustat.com/linux/how-to-compile-linux-kernel-on-ubuntu))

### Compile and insert
Alternative to add to Kernel, compilation is faster and can test "on fly".
With this method each time the machine is restarted the custom module is removed.

Add to Makefile in `sound/usb`

```makefile
all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean

load:
	sudo rmmod snd_usb_audio; \
	sudo insmod snd-usb-audio.ko

unload:
	sudo rmmod snd_usb_audio; \
	sudo modprobe -a snd_usb_audio
```

Run `make all`

Run `make load`

## How does it work
It seems that Quad-Capture is persisting the rate inside the hardware (not sure if this is class compliant).

I discovered that by changing the `altsetting` to 2 it is possible to access the 48khz. (we can imagine 3 is for 96kHz etc..)

ep_attr seems to work better with USB_ENDPOINT_XFER_ISOC value.

## Moving forward
It would be great if somehow ALSA can switch altsetting depending on how the Quad-capture frequence is set.

Ideally Alsa should also be able to switch the frequency set inside the Quadcapture (not sure how this work with ASIO).

## Use Case
I hacked this workaround as I am playing Rocksmith 2014 on Linux which supports only 48kHz.

I use QJackCtl which works perfectly.

Kudos to [rs_asio](https://github.com/mdias/rs_asio) who made it possible to play realtime.

If you are interested to run Rocksmith 2014 on Linux I highly recomment to read [this reddit](https://www.reddit.com/r/rocksmith/comments/jxngpx/howto_rocksmith_2014_on_linux_with_steamproton/)