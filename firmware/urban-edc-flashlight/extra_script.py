Import("env")


env.AddPostAction(
    # Execute the action when the hex file is built:
    "$BUILD_DIR/${PROGNAME}.hex",
    [
    # 1.rename it to ${PROGNAME}-OTA.hex for use in OTA updates.  This file includes the signature and version sections.
    #   This allows the OTA to verify the signature and version before updating the firmware.
    env.VerboseAction(" ".join([
        "mv", "$BUILD_DIR/${PROGNAME}.hex", "$BUILD_DIR/${PROGNAME}-OTA.hex"
        ]), "Building $BUILD_DIR/${PROGNAME}-OTA.hex"),
    # 2.remove the eeprom, signature and version sections for use in ISP/UPDI updates (avrdude fails on signature and version sections)
    env.VerboseAction(" ".join([
        "$OBJCOPY", "-O", "ihex",
        "--remove-section=.eeprom",
        "--remove-section=.signature",
        "--remove-section=.version",
        "$BUILD_DIR/${PROGNAME}.elf",
        "$BUILD_DIR/${PROGNAME}.hex"
        ]), "Building $BUILD_DIR/${PROGNAME}.hex")
    ]
)