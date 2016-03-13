//Brandon Smith
//Hw 1
//Priority Mux

module priority_mux(d0, d1, d2, d3, d4, d5, sel1, sel2, sel3, sel4, sel5, out);
input d0, d1, d2, d3, d4, d5, sel1, sel2, sel3, sel4, sel5;
output out;
wire o1, o2, o3, o4;

mux21 stage1(.d0(d0), .d1(d1), .sel(sel1), .out(o1));
mux21 stage2(.d0(o1), .d1(d2), .sel(sel2), .out(o2));
mux21 stage3(.d0(o2), .d1(d3), .sel(sel3), .out(o3));
mux21 stage4(.d0(o3), .d1(d4), .sel(sel4), .out(o4));
mux21 stage5(.d0(o4), .d1(d5), .sel(sel5), .out(out));

endmodule
