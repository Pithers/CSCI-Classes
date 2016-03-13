//Brandon Smith, John-Mark Mamalakis
//
//

module hw3 #(parameter DATA_WIDTH=32, MATRIX_SIZE=5) (input [MATRIX_SIZE*DATA_WIDTH-1:0] x, output [MATRIX_SIZE*DATA_WIDTH-1:0] y);
	wire [DATA_WIDTH-1:0] x_val [MATRIX_SIZE-1:0]; // x_val[MATRIX_SIZE-1] down to x_val[0] are the DATA_WIDTH-bit values
	reg [2*DATA_WIDTH-1:0] y_val [MATRIX_SIZE-1:0]; // Resulting y values
	
	reg [DATA_WIDTH - 1:0] a_val [MATRIX_SIZE - 1:0][MATRIX_SIZE-1 :0]; 	//This is the array holding the matrix values of A
	wire [2*DATA_WIDTH-1:0] p_res [MATRIX_SIZE-1:0][MATRIX_SIZE-1 :0]; 	//This is the array of wire holding the results of 
																								//every multiplication of array elements x and a.
	wire [2*DATA_WIDTH-1:0] sum [MATRIX_SIZE-1 :0][MATRIX_SIZE-2:0];		//This is the array of wires holding the summation
																								//of all of the multiplied elements.
	
	//This initial block fills the A matrix with all of the values based on the formula.
	integer k,m;
	initial begin
		for( k = MATRIX_SIZE - 1; k >=0; k=k-1) begin
			for( m = MATRIX_SIZE - 1; m >=0; m=m-1) begin
				a_val[k][m]= ((-1)**(k+m)) * (k+1) * (m+1); 
			end
		end
	end
		
	//Generate components for Matrix Multiplications y = A*x.
	genvar g,h,i,j;
	generate
		//unpack input x.
		for( g=MATRIX_SIZE-1; g>=0; g=g-1 ) begin : packing_loop_x
			assign x_val[g] = x[(g+1)*DATA_WIDTH-1:g*DATA_WIDTH];
		end
		
		//Runs for each element in y.		
		for( i=MATRIX_SIZE-1; i>=0; i=i-1 ) begin : main
			//Multiplies each row and column of matrices A and x for y[i].
			for( j=MATRIX_SIZE-1; j>=0; j=j-1 ) begin : multiply_loop
				multiplier #(.DATA_WIDTH(DATA_WIDTH)) multi(.a(a_val[i][j]), .b(x_val[j]), .p(p_res[i][j]));
			end
			//Calculates the sum all products for y[i].
			for( h=MATRIX_SIZE-1; h>=1; h=h-1 ) begin :accum_loop
				
				if(h == MATRIX_SIZE-1) begin
					assign sum[i][h-1] = p_res[i][h] + p_res[i][h-1];
				end
				else begin
					assign sum[i][h-1] = sum[i][h] + p_res[i][h-1];
				end
			end

			//Pack output y.
			assign y[DATA_WIDTH*(i+1)-1:DATA_WIDTH*i] = sum[i][0][DATA_WIDTH-1:0]; //y_val[i][DATA_WIDTH-1:0];
		end
	endgenerate

endmodule
