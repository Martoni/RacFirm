# RacFirm
firmware

# Install

More info on this [blog note](http://www.fabienm.eu/wordpress/?p=1573)

```
cd ~/zephyrproject
git clone https://github.com/Martoni/RacFirm.git
```

## Compile

```
cd ~/zephyrproject/zephyr/
west build -p auto -b longan_nano ../RacFirm/
```

## Download

```
cd ~/zephyrproject/zephyr/
dfu-util -d28e9:0189 -s 0x8000000:leave -a 0 -D build/zephyr/zephyr.bin
```
