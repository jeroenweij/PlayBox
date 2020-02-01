
    add_subdirectory(avr)
    add_subdirectory(arduino)
    add_subdirectory(fastled)

    set(script "avr-tools.sh")

    configure_file (${script} ${script})
    add_custom_target(hexify ALL
        ./${script}
        "hexify"
        COMMENT "Generating HEX image"
        DEPENDS ${CMAKE_PROJECT_NAME})

    add_custom_target(size ALL
        ./${script}
        "size"
        COMMENT "Calculatin image size"
        DEPENDS hexify)

    add_custom_target(upload
        ./${script}
        "upload"
        COMMENT "Uploading using bootloader"
        DEPENDS size)

    add_custom_target(burn
        ./${script}
        "burn"
        COMMENT "Uploading using programmer"
        DEPENDS size)

    add_custom_target(bootloader
        ./${script}
        "bootloader"
        COMMENT "Uploading bootloader")

