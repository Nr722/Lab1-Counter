module counter#(
    parameter WIDTH = 8
)(
    //interface signal
    input logic clk, //clock
    input logic rst, //reset
    input logic en, //counter enable
    output logic [WIDTH-1:0]    count   //count output
);

always_ff @ (posedge clk)
 if (rst) count <= {WIDTH{1'b0}};
 else count <= count + {{WIDTH-1{1'b0}}, en}; //forms width-1 bits of 0
endmodule
