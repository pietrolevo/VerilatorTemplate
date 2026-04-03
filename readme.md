# Verilator Template
## Required tools
### Verilator
High‑performance Verilog simulator used to compile and run cycle‑accurate C++ models.
```bash
sudo apt update
sudo apt install verilator
```
## GTKWave
Waveform viewer for inspecting dump files generated during simulation.
```bash
sudo apt install gtkwave
```
## Yosys
Open‑source RTL synthesis framework used to elaborate Verilog designs and produce netlists.
```bash
sudo apt install yosys
```
## Node.js + npm
JavaScript runtime and package manager required to run tools like netlistsvg
```bash
sudo apt install nodejs npm
```
## netlistsvg
Utility that converts Yosys JSON netlists into clean and readable SVG schematics.
```bash
sudo npm install -g netlistsvg
```

## Structure
Inside your project folder you should have at least the following: 
- src/ : contains your .v or .sv source files 
- tb/ : contains your .cpp testbenches
- Makefile : type "make help" on terminal to see commands
- auto.tcl : adds first level signals to gtkwave automatically
- (optional) netlist/ : if you use Yosys contains your netlist

---

This template also includes 2 modules examples and their testbenches.

combinational example:
- nand2.v
- tb_nand2.cpp

sequential example:
- dff_async.v
- tb_dff.cpp

If you already know how to work just delete the examples and keep makefile and other folders.


