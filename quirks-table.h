// REPLACE this with entry in this file in your kernel
// USB_DEVICE(0x0582, 0x012f), =/ Quad-Capure UA-55
{
	/* workaround for 48khz */
	USB_DEVICE(0x0582, 0x012f),
	.driver_info = (unsigned long) & (const struct snd_usb_audio_quirk) {
		/* .vendor_name = "Roland", */
		/* .product_name = "QUAD-CAPTURE", */
		.ifnum = QUIRK_ANY_INTERFACE,
		.type = QUIRK_COMPOSITE,
		.data = (const struct snd_usb_audio_quirk[]) {
			{
				.ifnum = 0,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (const struct audioformat) {
					.formats = SNDRV_PCM_FMTBIT_S32_LE,
					.channels = 4,
					.iface = 0,
					.altsetting = 2, // this is for 48khz original value 1
					.altset_idx = 1,
					.endpoint = 0x05,
					.ep_attr = USB_ENDPOINT_XFER_ISOC, // original value 0x05,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (unsigned int[]) { 48000 }
				}
			},
			{
				.ifnum = 1,
				.type = QUIRK_AUDIO_FIXED_ENDPOINT,
				.data = & (const struct audioformat) {
					.formats = SNDRV_PCM_FMTBIT_S32_LE,
					.channels = 6,
					.iface = 1,
					.altsetting = 2, // same as above original value is 1
					.altset_idx = 1,
					.endpoint = 0x85,
					.ep_attr = 0x25,
					.rates = SNDRV_PCM_RATE_48000,
					.rate_min = 48000,
					.rate_max = 48000,
					.nr_rates = 1,
					.rate_table = (unsigned int[]) { 48000 }
				}
			},
			{
				.ifnum = 2,
				.type = QUIRK_MIDI_FIXED_ENDPOINT,
				.data = & (const struct snd_usb_midi_endpoint_info) {
					.out_cables = 0x0001,
					.in_cables  = 0x0001
				}
			},
			{
				.ifnum = 3,
				.type = QUIRK_IGNORE_INTERFACE
			},
			{
				.ifnum = 4,
				.type = QUIRK_IGNORE_INTERFACE
			},
			{
				.ifnum = -1
			}
		}
	}
},