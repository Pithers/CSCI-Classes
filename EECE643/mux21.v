//Brandon Smith
//Hw 1
//2 to 1 Mux module

module mux21(d0, d1, sel, out);
input d0, d1, sel;
output out;

assign out = (d0 & ~sel) | (d1 & sel);

endmodule
