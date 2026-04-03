module dff_async (
  input clk_e,
  input rst_e,
  input d_e,
  output reg q_s
);

always @(posedge clk_e or posedge rst_e) begin
  if (rst_e)
    q_s <= 1'b0;
  else
    q_s <= d_e;
end

endmodule
