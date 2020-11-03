#!/bin/bash -ex

ACTION=$1
TOOLS=""
AVRDIR="avr"
BOOTLOADER="${CMAKE_CURRENT_SOURCE_DIR}/bootloader/Caterina-Leonardo.hex"
PORT=""
HEXFILE=$(realpath "/home/jweij/Downloads/brilliant_pebbles_bf01d633.hex")
ELFFILE="${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf"

error ()
{
    echo -e "\033[1m$1\033[0m"
    exit 1
}

detect_port ()
{
    if [ -d /dev/serial ]; then

        if ls /dev/serial/by-id/usb-Adafruit_Feather* 1> /dev/null 2>&1; then
            PORT=$(ls /dev/serial/by-id/usb-Adafruit_Feather* | head -n1)
            PORT=$(readlink -f $PORT)
        else
            error "Could not detect ThijsBox devices"
        fi


    else
        error "Could not detect serial devices"
    fi
}

reset () 
{
    detect_port
    
    # reset the Arduino
    stty -F "$PORT" 1200 
    sleep 0.5

    # wait for it...
    while :; do
      sleep 0.5
      [ -c "$PORT" ] && break
    done
}

size ()
{
    SIZEDATA=$($AVRDIR/bin/avr-size -C --mcu=atmega32u4 "$ELFFILE" 2>&1)

    PROGRAM=$(grep "Program:" <<<"$SIZEDATA")
    DATA=$(grep "Data:" <<<"$SIZEDATA")
    
    echo -e "\033[1mFirmware Size:\033[0m  [$PROGRAM]  [$DATA] on atmega32u4"
}

hexify ()
{
    $AVRDIR/bin/avr-objcopy -O ihex -R .eeprom $ELFFILE $HEXFILE
}

upload ()
{
    reset
    $AVRDIR/bin/avrdude -C$AVRDIR/etc/avrdude.conf -v -patmega32u4 -cavr109 -P$PORT -b57600 -D -Uflash:w:$HEXFILE
}

burn ()
{
    reset
    $AVRDIR/bin/avrdude -C$AVRDIR/etc/avrdude.conf -v -patmega32u4 -cusbasp -Pusb -Uflash:w:$HEXFILE:i
}

bootloader ()
{
    if [ -f "$BOOTLOADER" ]; then
        reset
        $AVRDIR/bin/avrdude -C$AVRDIR/etc/avrdude.conf -v -patmega32u4 -cusbasp -Pusb -e -Ulock:w:0x3F:m -Uefuse:w:0xcb:m -Uhfuse:w:0xd8:m -Ulfuse:w:0xff:m 
        $AVRDIR/bin/avrdude -C$AVRDIR/etc/avrdude.conf -v -patmega32u4 -cusbasp -Pusb -e Uflash:w:Caterina-Leonardo.hex:i -Ulock:w:0x2F:m
    else 
        error "Bootloader file does not exist"
    fi
}


if [ "$ACTION" == "hexify" ]; then
    hexify
elif [ "$ACTION" == "size" ]; then
    size
elif [ "$ACTION" == "upload" ]; then
    upload
elif [ "$ACTION" == "burn" ]; then
    burn
elif [ "$ACTION" == "bootloader" ]; then
    bootloader
else
    error "Unknown argument $ACTION"
fi

