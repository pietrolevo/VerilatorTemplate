module dff_async (
  input clk_i,
  input rst_i,
  input d_i,
  output reg q_o
);

always @(posedge clk_i or posedge rst_i) begin
  if (rst_i)
    q_o <= 1'b0;
  else
    q_o <= d_i;
end

endmodule
