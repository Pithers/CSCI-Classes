`timescale 1ns / 1ps
`define TEST_WIDTH 8
`define NUM_RANDOM_PATTERNS 10

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:		Brandon Smith
//
// Create Date:   16:21:10 02/05/2016
// Design Name:   priority_mux_6to1
// Module Name:   C:/Users/Brandon/Desktop/EECE 643/bsmith_hw2/mux_tb.v
// Project Name:  bsmith_hw2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: priority_mux_6to1
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module mux_tb;

	// Inputs
	reg [7:0] d0;
	reg [7:0] d1;
	reg [7:0] d2;
	reg [7:0] d3;
	reg [7:0] d4;
	reg [7:0] d5;
	reg [4:0] sel;

	// Outputs
	wire [7:0] d_out;
	
	// Variables
	integer error;
	integer i;

	// Instantiate the Unit Under Test (UUT)
	priority_mux_6to1 uut (
		.d0(d0), 
		.d1(d1), 
		.d2(d2), 
		.d3(d3), 
		.d4(d4), 
		.d5(d5), 
		.sel(sel), 
		.d_out(d_out)
	);

	initial begin
		$display("**************************************");
		$display("******** Beginning simulation ********");
		$display("**************************************");
	
		// Initialize Inputs
		error = 0;
		i = 0;
		d0 = 0;
		d1 = 0;
		d2 = 0;
		d3 = 0;
		d4 = 0;
		d5 = 0;
		sel = 0;

		// Wait 100 ns for global reset to finish
		#100;
		
		//Test a couple of known cases
		test(8'b01010101, 0, 0, 0, 0, 0, 5'b00000);
		test(0, 0, 0, 0, 0, 8'b11111111, 5'b11111);
		test(0, 0, 8'b11110000, 0, 0, 0, 5'b00011);
		test(0, 0, 8'b11110000, 0, 0, 0, 5'b00011);
		
		//Test random patterns
		for(i = 0; i < `NUM_RANDOM_PATTERNS; i = i + 1)
			test($random % 8, $random % 8, $random % 8, $random % 8, $random % 8, $random % 8, $random % 5);
		
		$display("**************************************");
		$display("[T=%d] Simulation complete", $time);
		$display("**************************************");
		$display("Total number of errors: %d", error);
		$display("**************************************");
		if(error == 0) begin
		$display("No errors, code passes");
		end
		else begin
		$display("Errors exist, code fails");
		end
		$display("**************************************");
		$stop;
	end
	
	task test(input [`TEST_WIDTH-1:0] i0, i1, i2, i3, i4, i5, input [4:0] isel);
		reg [`TEST_WIDTH-1:0] i_out;
		begin
			d0 = i0;
			d1 = i1;
			d2 = i2;
			d3 = i3;
			d4 = i4;
			d5 = i5;
			sel = isel;
			#100
			
			//Calculate what output should be based on inputs
			if(sel[4] == 1'b1) begin
				i_out = d5;
			end
			else if(sel[3] == 1'b1) begin
				i_out = d4;
			end
			else if(sel[2] == 1'b1) begin
				i_out = d3;
			end
			else if(sel[1] == 1'b1) begin
				i_out = d2;
			end
			else if(sel[0] == 1'b1) begin
				i_out = d1;
			end
			else begin
				i_out = d0;
			end
			
			//Check if actual output is the same as the theoretical output
			if(d_out != i_out) begin
				$display("ERROR: At time: %d        Expected output to be: %b, but output was: %b", $time, i_out, d_out);
				error = error + 1;
			end
			else begin
				$display("For inputs: d0: %b, d1: %b, d2: %b, d3: %b, d4: %b, d5: %b, sel: %b, output is correct", d0, d1, d2, d4, d4, d5, sel);
			end
		end
	endtask
endmodule

