/* 
  file: tb_nand2.cpp
  author: Pietro Alberto Levo
  This file wants to make you understand how to make a simple tb for comb components
  in cpp with verilator, which can supports both verilog and system verilog.
*/

// include V<modulename>.h
#include "Vnand2.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "cassert"

/*
  define maximum simulation time and initialize time to 0,
  both in picoseconds(10^-12), remember 1000ps = 1ns.
  Initialize the clock period when it is on and off(if Ton=Toff).
*/
const vluint64_t MAX_SIM_TIME = 100;
vluint64_t t = 0;
const int CLOCK_TON = 2;

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    // create an istance of the dut
    Vnand2* dut = new Vnand2;

    // Waveform
    VerilatedVcdC* tfp = new VerilatedVcdC;
    Verilated::traceEverOn(true);

    dut->trace(tfp, 99);
    tfp->open("dump.vcd");

    while (!Verilated::gotFinish() && t < MAX_SIM_TIME) {

        // vectors
        if (t == 10) {
            dut->in1_e = 0; dut->in2_e = 0;
        }
        if (t == 17) {
            dut->in1_e = 0; dut->in2_e = 1;
        }
        if (t == 34) {
            dut->in1_e = 1; dut->in2_e = 0;
        }
        if (t == 55) {
            dut->in1_e = 1; dut->in2_e = 1;
        }
        if (t == 77) {
          dut->in1_e = 0;
        }

        // evaluate signals
        dut->eval();

        // assert block
        if (t == 10) {
          assert(dut->nand_s == 1 && "ERROR: expected value was 1");
        }
        if (t == 17) {
          assert(dut->nand_s == 1 && "ERROR: expected value was 1");
        }
        if (t == 34) {
          assert(dut->nand_s == 1 && "ERROR: expected value was 1");
        }
        if (t == 55) {
          assert(dut->nand_s == 0 && "ERROR: expected value was 0");
        }    
        if (t == 77) {
          assert(dut->nand_s == 1 && "ERROR: expected value was 1");
        }   
        
        // Dump waveform
        tfp->dump(t);

        t++;
    }

    tfp->close();
    delete dut;

    return 0;
}
