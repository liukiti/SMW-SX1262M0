set(CORE_SRCS
  src/Buffer.cpp
  src/SMW_SX1262M0.cpp
  src/utils.cpp
  )
set(includedirs
  src
  )

set(srcs ${CORE_SRCS})
set(priv_includes )#cores/esp32/libb64)
set(requires arduino)#spi_flash mbedtls mdns esp_adc_cal wifi_provisioning nghttp wpa_supplicant)
set(priv_requires )#fatfs nvs_flash app_update spiffs bootloader_support openssl bt esp_ipc esp_hid)

idf_component_register(INCLUDE_DIRS ${includedirs} PRIV_INCLUDE_DIRS ${priv_includes} SRCS ${srcs} REQUIRES ${requires} PRIV_REQUIRES ${priv_requires})
