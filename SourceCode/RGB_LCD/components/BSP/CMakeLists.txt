set(src_dirs
            IIC
            LED
            XL9555
            RGBLCD)

set(include_dirs
            IIC
            LED
            XL9555
            RGBLCD)

set(requires
            driver
            esp_lcd
            esp_common
            log)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)