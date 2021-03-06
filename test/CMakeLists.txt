cmake_minimum_required(VERSION 3.0)

set(MCU TM4C123GH6PM)
set(REV TM4C123_RA1)
set(TARGET **target name**)
set(TIVAWARE_PATH **/path/to/TivaWare**)

#-----------------------------------------------------------------------------#

set(SERIES TIVA)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

set(CPU -mcpu=cortex-m4)
set(FPU -mfpu=fpv4-sp-d16)
set(FLOAT -mfloat-abi=hard)

set(CMAKE_EXE_LINKER_FLAGS "${CPU} ${FPU} ${FLOAT} \
							-T ${CMAKE_CURRENT_SOURCE_DIR}/linker_config.ld \
							--entry ResetISR \
							-Wl,--relax,--gc-sections")

#-----------------------------------------------------------------------------#

option(FLASH "Flash the MCU" OFF)

#-----------------------------------------------------------------------------#

if (FLASH)
	message("[Flashing]")

	add_custom_target(flash ALL lm4flash ${CMAKE_CURRENT_SOURCE_DIR}/bin/${TARGET}.bin)

else ()
	message("[Build]")

	add_subdirectory(**pathA pathB**)

	add_executable(${TARGET} src/startup_gcc.c **source files**)

	target_link_libraries(${TARGET} ${TIVAWARE_PATH}/driverlib/gcc/libdriver.a
									**lib**
	)

	target_include_directories(${TARGET} PUBLIC ${TIVAWARE_PATH} 
												**dirs**
	)

#-----------------------------------------------------------------------------#

	target_compile_options(${TARGET} PUBLIC -std=gnu11
											-mthumb
											${CPU}
											${FPU}
											${FLOAT}
											-ffunction-sections 
											-fdata-sections    
											-MD                                         
											-pedantic           
											-O2
											-Wall
											-Werror
	)

	target_compile_definitions(${TARGET} PUBLIC TARGET_IS_${REV}
												PART_${MCU}
	)

#-----------------------------------------------------------------------------#

	set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME ${TARGET}.axf)
	add_custom_target(strip ALL arm-none-eabi-strip ${TARGET}.axf DEPENDS ${TARGET})
	add_custom_target(bin ALL arm-none-eabi-objcopy -O binary ${TARGET}.axf ${TARGET}.bin DEPENDS strip)
	#add_custom_target(eeprom arm-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O binary ${TARGET}.axf ${TARGET}.eep DEPENDS strip)
	add_custom_target(size ALL arm-none-eabi-size --format=gnu ${TARGET}.axf DEPENDS strip)

	#set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${TARGET}.hex;${TARGET}.eeprom;${TARGET}.lst")

#-----------------------------------------------------------------------------#

	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}.bin DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

endif()