
package require ::quartus::project
load_package report
load_package flow

set need_to_close_project 0
set make_assignments 1
%%TYPE%% -revision %%TOP%% %%TOP%%
set need_to_close_project 1

set_global_assignment -name FAMILY "Stratix V"
set_global_assignment -name DEVICE 5SEEBF45I2
set_global_assignment -name TOP_LEVEL_ENTITY %%TOP%%
set_global_assignment -name ORIGINAL_QUARTUS_VERSION 16.0.2
set_global_assignment -name PROJECT_CREATION_TIME_DATE "14:10:10  NOVEMBER 04, 2016"
set_global_assignment -name LAST_QUARTUS_VERSION 16.0.2
set_global_assignment -name PROJECT_OUTPUT_DIRECTORY output_files
set_global_assignment -name MIN_CORE_JUNCTION_TEMP "-40"
set_global_assignment -name MAX_CORE_JUNCTION_TEMP 100
set_global_assignment -name DEVICE_FILTER_PIN_COUNT 1932
set_global_assignment -name DEVICE_FILTER_SPEED_GRADE FASTEST
set_global_assignment -name ERROR_CHECK_FREQUENCY_DIVISOR 256
set_global_assignment -name EDA_SIMULATION_TOOL "ModelSim-Altera (Verilog)"
set_global_assignment -name EDA_TIME_SCALE "1 ps" -section_id eda_simulation
set_global_assignment -name EDA_OUTPUT_DATA_FORMAT "VERILOG HDL" -section_id eda_simulation

set_global_assignment -name POWER_PRESET_COOLING_SOLUTION "23 MM HEAT SINK WITH 200 LFPM AIRFLOW"
set_global_assignment -name POWER_BOARD_THERMAL_MODEL "NONE (CONSERVATIVE)"
set_global_assignment -name PARTITION_NETLIST_TYPE SOURCE -section_id Top
set_global_assignment -name PARTITION_FITTER_PRESERVATION_LEVEL PLACEMENT_AND_ROUTING -section_id Top
set_global_assignment -name PARTITION_COLOR 16764057 -section_id Top
set_instance_assignment -name PARTITION_HIERARCHY root_partition -to | -section_id Top
