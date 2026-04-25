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

#if VM_COVERAGE
#include "verilated_cov.h"
#endif

/*
  define maximum simulation time and initialize time to 0,
  both in picoseconds(10^-12), remember 1000ps = 1ns.
  Initialize the clock period when it is on and off(if Ton=Toff).
*/
const vluint64_t MAX_SIM_TIME = 100;
vluint64_t t = 0;
const int CLOCK_PERIOD = 4;


void init_dut(Vdff_async* dut) {
  dut->clk_i = 0;
  dut->rst_i = 0;
  dut->d_i   = 0;
}


void clock_proc(Vdff_async* dut) {
  if ((t % (CLOCK_PERIOD/2)) == 0) {
    dut->clk_i = !dut->clk_i;
  }
}


void reset_proc(Vdff_async* dut) {
  bool rst1 = (t < 4);
  bool rst2 = (t >= 50 && t < 70);
  bool rst3 = (t == 90);

  dut->rst_i = rst1 || rst2 || rst3;
}


void vector_proc(Vdff_async* dut) {
  if (t == 10) dut->d_i = 1;
  if (t == 20) dut->d_i = 0;
  if (t == 30) dut->d_i = 1;
  if (t == 55) dut->d_i = 0;
  if (t == 75) dut->d_i = 1;
}


void check_assertions(Vdff_async* dut) {
  if (t == 12) assert(dut->q_o == 1 && "ERROR: expected q_o=1");
  if (t == 22) assert(dut->q_o == 0 && "ERROR: expected q_o=0");
  if (t == 32) assert(dut->q_o == 1 && "ERROR: expected q_o=1");
  if (t == 55) assert(dut->q_o == 0 && "ERROR: expected q_o=0");
  if (t == 77) assert(dut->q_o == 1 && "ERROR: expected q_o=1");
}


int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    // create an istance of the dut
    Vdff_async* dut = new Vdff_async;

    // initialize all inputs
    init_dut(dut);

    // Waveform
    VerilatedVcdC* tfp = new VerilatedVcdC;
    Verilated::traceEverOn(true);

    dut->trace(tfp, 99);
    tfp->open("dump.vcd");

    while (!Verilated::gotFinish() && t < MAX_SIM_TIME) {
      /*
        if syncronous reset->
          reset_proc(dut);
          clock_proc(dut);
        so always put reset before clock process in c++
      */
      
      // Reset
      reset_proc(dut);

      // clock 
      clock_proc(dut);

      // vectors
      vector_proc(dut);

      // evaluate signals
      dut->eval();

      // assert block
      check_assertions(dut);

      //  Dump waveform
      tfp->dump(t);

      t++;
    }

    tfp->close();

    #if VM_COVERAGE
      VerilatedCov::write("coverage/sim_cov.dat");
    #endif

    delete dut;

    return 0;
}
