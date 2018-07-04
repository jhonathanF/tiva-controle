################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
bibliotecas/gpioUtils.obj: ../bibliotecas/gpioUtils.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/jhonathan/workspace_v8/projeto2 Joystick" --include_path="/home/jhonathan/workspace_v8/projeto2 Joystick/bibliotecas" --include_path="/opt/ti/SW-TM4C-2.1.4.178/inc" --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="bibliotecas/gpioUtils.d_raw" --obj_directory="bibliotecas" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

bibliotecas/utilitarioTiva.obj: ../bibliotecas/utilitarioTiva.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/jhonathan/workspace_v8/projeto2 Joystick" --include_path="/home/jhonathan/workspace_v8/projeto2 Joystick/bibliotecas" --include_path="/opt/ti/SW-TM4C-2.1.4.178/inc" --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="bibliotecas/utilitarioTiva.d_raw" --obj_directory="bibliotecas" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


