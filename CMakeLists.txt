cmake_minimum_required(VERSION 3.0)

set(TARGET utils)

#-----------------------------------------------------------------------------#

add_library(${TARGET} STATIC src/utils_tiva.c
					${TIVAWARE_PATH}/utils/uartstdio.c)

target_link_libraries(${TARGET} ${TIVAWARE_PATH}/driverlib/gcc/libdriver.a
)

target_include_directories(${TARGET} PRIVATE ${TIVAWARE_PATH} 
											include
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