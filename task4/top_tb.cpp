//#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"
#include "Vtop.h"

int main (int argc, char **argv, char **ev){
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    
    //init top verilog instance
    Vtop* top = new Vtop;

    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp,99);
    tfp->open ("counter.vcd");

    //init Vbuddy
    if(vbdOpen()!=1) return (-1);
    vbdHeader("lab 1: Counter");
    //initialize simulation inputs
    top->clk = 1;
    top->rst = 0;
    top->en = 1;
    //run simulation for many clock cycles
    for(i=0; i<200;i++){

        //dump variables into VCD file and toggle clock
        for(clk=0; clk<2; clk++){
            tfp-> dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
            }

        // ++++ send count value to Vbuddy

        vbdCycle(i+1);
        
        //end of Vbuddy output section
        vbdHex(3, (int(top->bcd) >> 8) & 0xF);
        vbdHex(2, (int(top->bcd) >> 4) & 0xF);
        vbdHex(1, (int(top->bcd)) & 0xF);
        
        
        //change input stimuli

          if (Verilated::gotFinish()) exit(0);
    }

    vbdClose(); //++++
    tfp->close();
    exit(0);
}


