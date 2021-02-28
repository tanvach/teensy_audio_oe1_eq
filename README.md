# Teensy Audio OE-1 Audio EQ
Teensy Audio board based hardware EQ for Tectonic BMR off ear headphones (OE-1).

# Hardware
- Teensy Audio board (https://www.pjrc.com/store/teensy3_audio.html)
- Teensy 4.0 (https://www.pjrc.com/store/teensy40.html)

You need to solder a 3.5mm audio plug to LINEIN on the Audio Board.

# Software
- Teensyduino (https://www.pjrc.com/teensy/teensyduino.html)

# Steps
- Solder the audio board to Teensy 4.0.
- Install Teensyduino and open the .ino file.
- Upload sketch.
- Connect usb power, the DSP should just work.

# Recommendation
- Use the shortest possible audio and USB cable. You can get a short (~6 inch) USB-C to micro-USB on Amazon. This reduces ground loop increase audio quality.