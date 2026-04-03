/* 
  file: tb_dff.cpp
  author: Pietro Alberto Levo
  This file wants to make you understand how to make a simple tb for seq components
  in cpp with verilator, which can supports both verilog and system verilog.
*/

// include V<modulename>.h
#include "Vdff_async.h"
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
    Vdff_async* dut = new Vdff_async;

    // Waveform
    VerilatedVcdC* tfp = new VerilatedVcdC;
    Verilated::traceEverOn(true);

    dut->trace(tfp, 99);
    tfp->open("dump.vcd");

    while (!Verilated::gotFinish() && t < MAX_SIM_TIME) {

        // clock 
        if ((t % CLOCK_TON) == 0) {
          dut->clk_e = !dut->clk_e;
        }

        // Reset
        bool rst1 = (t < 4);
        bool rst2 = (t >= 50 && t < 70);

        dut->rst_e = rst1 || rst2;

        // vectors
        if (t == 10) {
            dut->d_e = 1;
        }
        if (t == 20) {
            dut->d_e = 0;
        }
        if (t == 30) {
            dut->d_e = 1;
        }
        if (t == 55) {
            dut->d_e = 0;
        }
        if (t == 75) {
            dut->d_e = 1;
        }

        // evaluate signals
        dut->eval();

        // assert block
        if (t == 12) {
          assert(dut->q_s == 1 && "ERROR: expected value was 1");
        }
        if (t == 22) {
          assert(dut->q_s == 0 && "ERROR: expected value was 0");
        }
        if (t == 32) {
          assert(dut->q_s == 1 && "ERROR: expected value was 1");
        }
        if (t == 55) {
          assert(dut->q_s == 0 && "ERROR: expected value was 0");
        }
        if (t == 77) {
          assert(dut->q_s == 1 && "ERROR: expected value was 1");
        }

        //  Dump waveform
        tfp->dump(t);

        t++;
    }

    tfp->close();
    delete dut;

    return 0;
}
