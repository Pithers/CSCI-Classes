//Brandon Smith, John-Mark Mamalakis
//Even though we know that you Professor Kredo made this file.
//Especially this file...


module hw3_tb ();
	// These are here for your reference and as an example.
	// I will not test your submissions with any other values
	// of MATRIX_SIZE and DATA_WIDTH.
	localparam MATRIX_SIZE = 5;
	localparam DATA_WIDTH = 32;

	// Individual components of x and y
	reg signed [DATA_WIDTH-1:0] x_vals [MATRIX_SIZE-1:0];
	wire signed [DATA_WIDTH-1:0] y_vals [MATRIX_SIZE-1:0];

	// Count of errors for each test case
	integer error_count;

	integer i;

	// DUT input and output
	wire [MATRIX_SIZE*DATA_WIDTH-1:0] x, y;

	/////////////////////////
	// Tasks and functions
	/////////////////////////
	
	// Set all x_vals to the given value val
	task set_all_x( input [DATA_WIDTH-1:0] val );
		integer i;
	begin
		for( i = MATRIX_SIZE-1; i>=0; i=i-1 )
			x_vals[i] = val;
	end
	endtask

	// Set all x_vals to a random value
	task set_random_x;
		integer i;
	begin
		for( i = MATRIX_SIZE-1; i>=0; i=i-1 )
			x_vals[i] = $random;
	end
	endtask

	// Verify the matrix multiplication results against the analytical result
	task verify_results;
		reg signed [2*DATA_WIDTH-1:0] expected;
		integer r, c;
	begin
		#5;
		for( r = MATRIX_SIZE-1; r>=0; r=r-1 ) begin

			// Compute the analytical expected value
			expected = 0;
			for( c = MATRIX_SIZE-1; c>=0; c=c-1 ) begin
				expected = expected + (-1)**(r+c)*(r+1)*(c+1) * x_vals[c];
			end

			if( y_vals[r] != expected[DATA_WIDTH-1:0] ) begin
				error_count = error_count + 1;
				$display("[T=%t] Incorrect result for y(%d). Expected %b and got %b.", $time, r, expected, y_vals[r]);
			end
			#5;
		end
	end
	endtask

	// Instantiate the DUT
	hw3 #(.MATRIX_SIZE(MATRIX_SIZE), .DATA_WIDTH(DATA_WIDTH)) uut (.x(x), .y(y));

	////////////////////////////////
	// Start of testbench body
	////////////////////////////////
	initial begin
		// Check A*0 = 0
		error_count = 0;
		set_all_x(0);
		verify_results();
		$display("[T=%t] %d total errors checking A*0 != 0.", $time, error_count);

		// Verify each matrix entry
		error_count = 0;
		for( i=MATRIX_SIZE-1; i>=0; i=i-1 ) begin
			set_all_x(0);
			x_vals[i] = 1;
			verify_results();
		end
		$display("[T=%t] %d total errors checking matrix coefficients.", $time, error_count);

		// Check vector of all 1's
		error_count = 0;
		set_all_x(1);
		verify_results();
		$display("[T=%t] %d total errors checking all-1 inputs.", $time, error_count);

		// Check random inputs
		for( i=MATRIX_SIZE-1; i>=0; i=i-1) begin
			error_count = 0;
			set_random_x();
			verify_results();
			$display("[T=%t] %d total errors for random input test %d.", $time, error_count, i);
		end

		#5 $finish;
	end

	// Associate x to x_vals and y to y_vals
	genvar i_gen;
	generate
		for( i_gen=MATRIX_SIZE-1; i_gen>=0; i_gen=i_gen-1 ) begin : packing_loop
			assign x[(i_gen+1)*DATA_WIDTH-1:i_gen*DATA_WIDTH] = x_vals[i_gen];
			assign y_vals[i_gen] = y[(i_gen+1)*DATA_WIDTH-1:i_gen*DATA_WIDTH];
		end
	endgenerate
endmodule
