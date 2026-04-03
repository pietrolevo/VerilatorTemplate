# A simple template for projects using Verilator and GTKWave

### Structure
Inside your project folder you should have at least the following: 
- src/ : contains your .v or .sv source files 
- tb/ : contains your .cpp testbenches
- Makefile
- add_signals.tcl

---

This template also includes 2 modules examples and their testbenches.

combinational example:
- nand2.v
- tb_nand2.cpp

sequential example:
- dff_async.v
- tb_dff.cpp

---

If you already know how to work with verilog/System-verilog and testbenches in c++ then you can delete the examples and adjust the makefile based on your project files.

---
The TCL scripts add all top entity signals automatically to GTKWave, if you encounter problems change it based on your components or remove it from the project and the makefile. If you remove it you will need to add manually signals inside GTKWave to see them.