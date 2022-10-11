################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/home/TTavella/ti/ccs1120/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/home/TTavella/Personal/Repositorios/Proyecto-Final/Firmware" --include_path="/home/TTavella/Personal/Repositorios/Proyecto-Final/Firmware/Includes/common" --include_path="/home/TTavella/Personal/Repositorios/Proyecto-Final/Firmware/Includes/headers" --include_path="/home/TTavella/ti/ccs1120/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/home/TTavella/ti/ccs1120/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/home/TTavella/Personal/Repositorios/Proyecto-Final/Firmware" --include_path="/home/TTavella/Personal/Repositorios/Proyecto-Final/Firmware/Includes/common" --include_path="/home/TTavella/Personal/Repositorios/Proyecto-Final/Firmware/Includes/headers" --include_path="/home/TTavella/ti/ccs1120/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


