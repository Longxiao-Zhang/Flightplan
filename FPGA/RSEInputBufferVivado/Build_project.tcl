open_project RSEInputBufferVivado/RSEInputBufferVivado.xpr

set ip_repo_path [file normalize "RSEInputBufferVivado/RSEInputBufferVivado.srcs"]
ipx::package_project -root_dir $ip_repo_path -vendor upenn.edu -library user -taxonomy /UserIP -force
set_property name RSEInputBufferVivado [ipx::current_core]
set_property display_name RSEInputBufferVivado_v1_0 [ipx::current_core]
set_property description "Input buffer for RSE booster" [ipx::current_core]
ipx::infer_bus_interface clk_line xilinx.com:signal:clock_rtl:1.0 [ipx::current_core]
ipx::associate_bus_interfaces -busif axis_in -clock clk_line [ipx::current_core]
ipx::associate_bus_interfaces -busif axis_out -clock clk_line [ipx::current_core]
ipx::add_bus_parameter POLARITY [ipx::get_bus_interfaces clk_line_rst -of_objects [ipx::current_core]]
set_property value ACTIVE_HIGH [ipx::get_bus_parameters POLARITY -of_objects [ipx::get_bus_interfaces clk_line_rst -of_objects [ipx::current_core]]]
ipx::create_xgui_files [ipx::current_core]
ipx::update_checksums [ipx::current_core]
ipx::save_core [ipx::current_core]
set_property ip_repo_paths $ip_repo_path [current_project]
update_ip_catalog

close_project

