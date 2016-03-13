--ps2.vhd
--Brandon Smith, John-Mark Mamalakis

------------------------------------------------------------------------------------
-------------------Main Entity, Define Pins Here------------------------------------
------------------------------------------------------------------------------------
Library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity ps2 is
	port(	------------Keyboard variables----------------------
			keyboard_clk, keyboard_data: IN std_logic;
			------------Variables for switches etc---------------
			clk			: in 	std_logic;
			------------Seven Segment Pins--------------------
			seg0, seg1	: out	std_logic_vector (6 downto 0);
			------------------VGA Pins--------------------------
			VGA_Red,VGA_Green,VGA_Blue,VGA_HSync,VGA_VSync,video_blank_out,Video_clock_out	:OUT std_logic);
end ps2;

Architecture keyboard_scan of ps2 is

------------------------------------------Signals Go Here----------------------------------
	signal st: 											std_logic_vector (7 downto 0);
	signal m1, m0: 										std_logic_vector (3 downto 0);
	signal seg_data0, seg_data1:						std_logic_vector (6 downto 0);
	signal clkout: 										std_logic;
	signal Hex_Display_Data: 							std_logic_vector((2*4)-1 DOWNTO 0);
	signal pixel_row_sig, pixel_column_sig: 			STD_LOGIC_VECTOR(9 DOWNTO 0);
	signal red_sig,green_sig,blue_sig,vert_sync_sig, h_sync_sig:	STD_LOGIC;
	signal out_sig: 									STD_LOGIC;
	signal INCNT										:std_logic_vector(3 downto 0);
	signal SHIFTIN										:std_logic_vector(8 downto 0);
	signal READ_CHAR									:std_logic;
	signal INFLAG, ready_set							:std_logic;
	signal keyboard_clk_filtered						:std_logic;
	signal filter										:std_logic_vector(7 downto 0);
	
	signal scan_code 	:std_logic_vector(7 DOWNTO 0);
   signal scan_ready	:std_logic;
	signal clock_25Mhz, reset, read: std_logic;
	signal char_row_synch: std_logic_vector (2 DOWNTO 0);
	signal char_col_synch: std_logic_vector (2 DOWNTO 0);
	signal c_sig: std_logic;
	signal addr: std_logic_vector(9 DOWNTO 0);
	signal c_col: std_logic_vector(2 DOWNTO 0);
	signal c: std_logic_vector (5 downto 0);
	
	signal keyboard_case : std_logic_vector (7 downto 0);
-----------------------------------------------------------------------------------

--------------------------------Components Go Here----------------------------------------
	component slowclk is
		port(	clk: in std_logic;
				clkout: out std_logic);
	end component;
	
	component vga_sync
	port( clock_50Mhz, red, green, blue							: IN STD_LOGIC;
			red_out, green_out, blue_out, horiz_sync_out, 
			vert_sync_out, video_on, pixel_clock				: OUT STD_LOGIC;
			pixel_row, pixel_column									: OUT STD_LOGIC_VECTOR(9 DOWNTO 0));
	end component;
	
	component char_ROM
	port(	character_address			: IN	STD_LOGIC_VECTOR(9 DOWNTO 0);
			font_col						: IN 	STD_LOGIC_VECTOR(2 DOWNTO 0);
			clock							: IN  STD_LOGIC;
			rom_mux_output				: OUT	STD_LOGIC);
	end component;
-----------------------------------------------------------------------------------

begin
	------------------------------------Assign Variables to Components-----------------
		stage1:  slowclk port map(clk, clkout);
		sync0:	vga_sync port map(clk, red_sig,green_sig,blue_sig, VGA_Red,VGA_Green,VGA_Blue,
									h_sync_sig, vert_sync_sig,video_blank_out,c_sig,pixel_row_sig, 
									pixel_column_sig);
		stage2:  char_ROM port map(addr, c_col, c_sig, out_sig);
	-----------------------------------------------------------------------------------
	
	-----------------------------VGA Stuff---------------------------------------------
	VGA_VSync<=vert_sync_sig;
	VGA_HSync<=h_sync_sig;
	Video_clock_out <= c_sig;
	green_sig <= out_sig;
	blue_sig <= '0';
	red_sig <= '1'; 
	c_col <= pixel_column_sig(2 DOWNTO 0);		--Draw character columnwise
	addr <= c & pixel_row_sig(3 DOWNTO 0);		--Draw character rowwise
	--c <= "00" & "0000";								--Character to display
	-----------------------------------------------------------------------------------
	
	----------------Assignments for Seven Segments-------------------------------------
	m1 <= st(7) & st(6) & st(5) & st(4);  --MSB
	m0 <= st(3) & st(2) & st(1) & st(0);  --LSB 7 seg display
	seg0 <= NOT(seg_data0);
	seg1 <= NOT(seg_data1);
	
	process(clkout)
	begin
		case m0 is					  
			when "0000" => seg_data0 <= "0111111";
			when "0001" => seg_data0 <= "0000110";
			when "0010" => seg_data0 <= "1011011";
			when "0011" => seg_data0 <= "1001111";
			when "0100" => seg_data0 <= "1100110";
			when "0101" => seg_data0 <= "1101101";
			when "0110" => seg_data0 <= "1111101";
			when "0111" => seg_data0 <= "0000111";
			when "1000" => seg_data0 <= "1111111";
			when "1001" => seg_data0 <= "1100111";
			when "1010" => seg_data0 <= "1110111";
			when "1011" => seg_data0 <= "1111100";
			when "1100" => seg_data0 <= "0111001";
			when "1101" => seg_data0 <= "1011110";
			when "1110" => seg_data0 <= "1111001";
			when others => seg_data0 <= "1110001";
		end case;
		case m1 is					  
			when "0000" => seg_data1 <= "0111111";
			when "0001" => seg_data1 <= "0000110";
			when "0010" => seg_data1 <= "1011011";
			when "0011" => seg_data1 <= "1001111";
			when "0100" => seg_data1 <= "1100110";
			when "0101" => seg_data1 <= "1101101";
			when "0110" => seg_data1 <= "1111101";
			when "0111" => seg_data1 <= "0000111";
			when "1000" => seg_data1 <= "1111111";
			when "1001" => seg_data1 <= "1100111";
			when "1010" => seg_data1 <= "1110111";
			when "1011" => seg_data1 <= "1111100";
			when "1100" => seg_data1 <= "0111001";
			when "1101" => seg_data1 <= "1011110";
			when "1110" => seg_data1 <= "1111001";
			when others => seg_data1 <= "1110001";
		end case;
	end process;
	-------------------------------------------------
	
	------------------------------------Keyboard Stuff--------------------------------------------
	process(read, ready_set) --
	begin	
		IF (read = '1')THEN
			scan_ready <= '0';
		ELSIF (ready_set'event and ready_set = '1')THEN
			scan_ready <= '1';
		END IF;
	end process;
	
	--Clock_filter:
	process	
		begin
		wait until c_sig'event and c_sig ='1';
			filter(6 Downto 0) <= filter (7 Downto 1);
			filter(7) <= keyboard_clk;
			IF (filter = "11111111") THEN
				keyboard_clk_filtered <= '1';
			ELSIF (filter = "00000000") THEN
				keyboard_clk_filtered <= '0';
			END IF;
	end process;
	
	process
	begin
		wait until (keyboard_clk_filtered'event and keyboard_clk_filtered = '1');
		IF (reset = '1')THEN	
			INCNT <="0000";
			READ_CHAR <= '0';
		ELSE
			IF (keyboard_data = '0' and READ_CHAR = '0')THEN
				READ_CHAR <= '1';
				ready_set <= '0';
			ELSE
				IF (READ_CHAR ='1')THEN	
					IF (INCNT < "1001") THEN
						INCNT <= INCNT +1;
						SHIFTIN(7 DOWNTO 0) <= SHIFTIN (8 DOWNTO 1);
						SHIFTIN(8) <= keyboard_data;
						ready_set <= '0';
					ELSE	
						keyboard_case <= SHIFTIN(7 DOWNTO 0);
						--key_out <= keyboard_case;
						READ_CHAR <= '0';
						ready_set <= '1';
						INCNT <= "0000";
					END IF;
				END IF;
			END IF;
		END IF;
	END process;
	
	
process(keyboard_case)	
begin	
	
	case keyboard_case is
		-----TOP ROW OF KEYS ---- 1234567890------------------------------------------------
		when "00010110" =>-- KEY 2 is '1'		HEX 16	00010110
			st(7 downto 4)<= "0001"; --1
			st(3 downto 0)<= "0110"; --6
			c <= "00" & "0001";								--Character to display
			
		when "00011110" =>-- KEY 3 is '2'  		HEX 1E	00011110	
			st(7 downto 4)<= "0001"; --1
			st(3 downto 0)<= "1110"; --E
			c <= "00" & "0010";								--Character to display
			
		when "00100110" =>-- KEY 4 is '3'		HEX 26	00100110
			st(7 downto 4)<= "0010"; --2
			st(3 downto 0)<= "0110"; --6
			c <= "00" & "0011";								--Character to display
			
		when "00100101" =>-- KEY 5 is '4'		HEX 25	00100101
			st(7 downto 4)<= "0010"; --2
			st(3 downto 0)<= "0101"; --5
			c <= "00" & "0100";								--Character to display
			
		when "00101110" =>-- KEY 6 is '5'		HEX 2E	00101110
			st(7 downto 4)<= "0010"; --2
			st(3 downto 0)<= "1110"; --E
			c <= "00" & "0101";								--Character to display
			
		when "00110110" =>-- KEY 7 is '6'		HEX 36	00110110
			st(7 downto 4)<= "0011"; --3
			st(3 downto 0)<= "0110"; --6
			c <= "00" & "0110";								--Character to display
			
		when "00111101" =>-- KEY 8 is '7'		HEX 3D	00111101
			st(7 downto 4)<= "0011"; --3
			st(3 downto 0)<= "1101"; --D
			c <= "00" & "0111";								--Character to display
			
		when "00111110" =>-- KEY 9 is '8'		HEX 3E	00111110
			st(7 downto 4)<= "0011"; --3
			st(3 downto 0)<= "1110"; --E
			c <= "00" & "1000";								--Character to display
			
		when "01000110" =>-- KEY 10 is '9'		HEX 46	01000110
			st(7 downto 4)<= "0100"; --4
			st(3 downto 0)<= "0110"; --6
			c <= "00" & "1001";								--Character to display
			
		when "01000101" =>-- KEY 11 is '0'		HEX 45	01000101
			st(7 downto 4)<= "0100"; --4
			st(3 downto 0)<= "0101"; --5
			c <= "00" & "0000";								--Character to display

		-----2ND ROW OF KEYS ---- QWERTYUIOP -----------------------------------------------
		when "00010101" =>-- KEY 17 is Q			HEX 15	00010101	
			st(7 downto 4)<= "0001"; --1
			st(3 downto 0)<= "0101"; --5
			c <= "01" & "1010";								--Character to display
			
		when "00011101" =>-- KEY 18 is W			HEX 1D	00011101
			st(7 downto 4)<= "0001"; --1
			st(3 downto 0)<= "1101"; --D
			c <= "10" & "0000";								--Character to display
			
		when "00100100" =>-- KEY 19 is E			HEX 24	00100100
			st(7 downto 4)<= "0010"; --2
			st(3 downto 0)<= "0100"; --4
			c <= "00" & "1110";								--Character to display
			
		when "00101101" =>-- KEY 20 is R			HEX 2D	00101101
			st(7 downto 4)<= "0010"; --2
			st(3 downto 0)<= "1101"; --D
			c <= "01" & "1011";								--Character to display
			
		when "00101100" =>-- KEY 21 is T			HEX 2C	00101100
			st(7 downto 4)<= "0010"; --2			
			st(3 downto 0)<= "1100"; --C
			c <= "01" & "1101";								--Character to display
			
		when "00110101" =>-- KEY 22 is Y			HEX 35	00110101
			st(7 downto 4)<= "0011"; --3
			st(3 downto 0)<= "0101"; --5
			c <= "10" & "0010";								--Character to display
			
		when "00111100" =>-- KEY 23 is U			HEX 3C	00111100
			st(7 downto 4)<= "0011"; --3
			st(3 downto 0)<= "1100"; --C
			c <= "01" & "1110";								--Character to display
			
		when "01000011" =>-- KEY 24 is I			HEX 43	01000011
			st(7 downto 4)<= "0100"; --4
			st(3 downto 0)<= "0011"; --3
			c <= "01" & "0010";								--Character to display
			
		when "01000100" =>-- KEY 25 is O			HEX 44	01000100
			st(7 downto 4)<= "0100"; --4
			st(3 downto 0)<= "0100"; --4
			c <= "01" & "1000";								--Character to display
			
		when "01001101" =>-- KEY 26 is P			HEX 4D	01001101
			st(7 downto 4)<= "0100"; --4
			st(3 downto 0)<= "1101"; --D
			c <= "01" & "1001";								--Character to display
			

		-----3ND ROW OF KEYS ---- ASDFGHJKL -----------------------------------------------
		when "00011100" =>-- KEY 31 is A			HEX 1C	00011100
			st(7 downto 4)<= "0001"; --1
			st(3 downto 0)<= "1100"; --C
			c <= "00" & "1010";								--Character to display
			
		when "00011011" =>-- KEY 32 is S			HEX 1B	00011011
			st(7 downto 4)<= "0001"; --1
			st(3 downto 0)<= "1011"; --B
			c <= "01" & "1100";								--Character to display
			
		when "00100011" =>-- KEY 33 is D			HEX 23	00100011
			st(7 downto 4)<= "0010"; --2
			st(3 downto 0)<= "0011"; --3
			c <= "00" & "1101";								--Character to display
			
		when "00101011" =>-- KEY 34 is F			HEX 2B	00101011
			st(7 downto 4)<= "0010"; --2
			st(3 downto 0)<= "1011"; --B
			c <= "00" & "1111";								--Character to display
			
		when "00110100" =>-- KEY 35 is G			HEX 34	00110100
			st(7 downto 4)<= "0011"; --3
			st(3 downto 0)<= "0100"; --4
			c <= "01" & "0000";								--Character to display
			
		when "00110011" =>-- KEY 36 is H			HEX 33	00110011
			st(7 downto 4)<= "0011"; --3
			st(3 downto 0)<= "0011"; --3
			c <= "01" & "0001";								--Character to display
			
		when "00111011" =>-- KEY 37 is J			HEX 3B	00111011
			st(7 downto 4)<= "0011"; --3
			st(3 downto 0)<= "1011"; --B
			c <= "01" & "0011";								--Character to display
			
		when "01000010" =>-- KEY 38 is K			HEX 42	01000010
			st(7 downto 4)<= "0100"; --4
			st(3 downto 0)<= "0010"; --2
			c <= "01" & "0100";								--Character to display
			
		when "01001011" =>-- KEY 39 is L			HEX 4B	01001011
			st(7 downto 4)<= "0100"; --4
			st(3 downto 0)<= "1011"; --B
			c <= "01" & "0101";								--Character to display
						
		-----BOTTOM ROW OF KEYS ---- ZXCVBNM -----------------------------------------------		
		when "00011010" =>-- KEY 46 is Z			HEX 1A	00011010
			st(7 downto 4)<= "0001"; --1
			st(3 downto 0)<= "1010"; --A
			c <= "10" & "0011";								--Character to display
			
		when "00100010" =>-- KEY 47 is X			HEX 22	00100010
			st(7 downto 4)<= "0010"; --2
			st(3 downto 0)<= "0010"; --2
			c <= "10" & "0001";								--Character to display
			
		when "00100001" =>-- KEY 48 is C			HEX 21	00100001
			st(7 downto 4)<= "0010"; --2
			st(3 downto 0)<= "0001"; --1		
			c <= "00" & "1100";								--Character to display
				
		when "00101010" =>-- KEY 49 is V			HEX 2A	00101010
			st(7 downto 4)<= "0010"; --2
			st(3 downto 0)<= "1010"; --A	
			c <= "01" & "1111";								--Character to display
			
		when "00110010" =>-- KEY 50 is B			HEX 32	00110010
			st(7 downto 4)<= "0011"; --3
			st(3 downto 0)<= "0010"; --2		
			c <= "00" & "1011";								--Character to display
			
		when "00110001" =>-- KEY 51 is N			HEX 31	00110001
			st(7 downto 4)<= "0011"; --3
			st(3 downto 0)<= "0001"; --1
			c <= "01" & "0111";								--Character to display
			
		when "00111010" =>-- KEY 52 is M			HEX 3A	00111010
			st(7 downto 4)<= "0011"; --3
			st(3 downto 0)<= "1010"; --A
			c <= "01" & "0110";								--Character to display
			
		when others =>
			st(7 downto 4)<= "1111"; 
			st(3 downto 0)<= "1111"; 
			c <= "11" & "1111";								--Character to display
		end case;
end process;
	
	-----------------------------------------------------------------------------------
END keyboard_scan;

------------------------------------------------------------------------------------
---------------------------------slow clock-----------------------------------------
------------------------------------------------------------------------------------
Library ieee;
use ieee.std_logic_1164.all;
entity slowclk is
	port(clk: in std_logic; clkout: out std_logic);
end slowclk;
architecture ckt of slowclk is
begin 
	process(clk)
	variable cnt: integer range 0 to 25000000;  --clock speeds set here
	begin	
		if (clk'event and clk = '1') THEN
			if(cnt = 2500000) THEN				--same clock speed
				cnt:= 0;
				clkout <= '1';
			else
				cnt:= cnt + 1;
				clkout <= '0';
			end if;
		end if;
	end process;
end ckt;
------------------------------------------------------------------------------------
------------------------------------END-------------------------------------------
------------------------------------------------------------------------------------

------------------------------------------------------------------------------------
----------------------------VGA SYNCH------------------------------------------
------------------------------------------------------------------------------------
library IEEE;
use  IEEE.STD_LOGIC_1164.all;
use  IEEE.STD_LOGIC_ARITH.all;
use  IEEE.STD_LOGIC_UNSIGNED.all;
ENTITY VGA_SYNC IS
	PORT(	clock_50Mhz, red, green, blue		: IN	STD_LOGIC;
			red_out, green_out, blue_out, horiz_sync_out, 
			vert_sync_out, video_on, pixel_clock	: OUT	STD_LOGIC;
			pixel_row, pixel_column: OUT STD_LOGIC_VECTOR(9 DOWNTO 0));
END VGA_SYNC;

ARCHITECTURE a OF VGA_SYNC IS
	SIGNAL horiz_sync, vert_sync,clock_25Mhz : STD_LOGIC;
	SIGNAL video_on_int, video_on_v, video_on_h : STD_LOGIC;
	SIGNAL h_count, v_count :STD_LOGIC_VECTOR(9 DOWNTO 0);
--
-- To select a different screen resolution, clock rate, and refresh rate
-- pick a set of new video timing constant values from table at end of code section
-- enter eight new sync timing constants below and
-- adjust PLL frequency output to pixel clock rate from table
-- using MegaWizard to edit video_PLL.vhd
-- Horizontal Timing Constants  
	CONSTANT H_pixels_across: 	Natural := 640;
	CONSTANT H_sync_low: 		Natural := 664;
	CONSTANT H_sync_high: 		Natural := 760;
	CONSTANT H_end_count: 		Natural := 800;
-- Vertical Timing Constants
	CONSTANT V_pixels_down: 	Natural := 480;
	CONSTANT V_sync_low: 		Natural := 491;
	CONSTANT V_sync_high: 		Natural := 493;
	CONSTANT V_end_count: 		Natural := 525;
--
BEGIN
--
---- PLL below is used to generate the pixel clock frequency
---- Uses UP 3's 48Mhz USB clock for PLL's input clock

-- video_on is high only when RGB pixel data is being displayed
-- used to blank color signals at screen edges during retrace
video_on_int <= video_on_H AND video_on_V;
-- output pixel clock and video on for external user logic

video_on <= video_on_int;

CLOCK_25M : PROCESS(clock_50Mhz)
BEGIN
   IF (clock_50Mhz' EVENT AND clock_50Mhz='1') THEN
		clock_25MHz<= clock_25MHz XOR '1';
   END IF;
END PROCESS CLOCK_25M;
	
pixel_clock<=clock_25Mhz;
	
a1: PROCESS
BEGIN
	
WAIT UNTIL(clock_25Mhz'EVENT) AND (clock_25Mhz='1');
--Generate Horizontal and Vertical Timing Signals for Video Signal
-- H_count counts pixels (#pixels across + extra time for sync signals)
-- 
--  Horiz_sync  ------------------------------------__________--------
--  H_count     0                 #pixels            sync low      end
--
	IF (h_count = H_end_count) THEN
   		h_count <= "0000000000";
	ELSE
   		h_count <= h_count + 1;
	END IF;

--Generate Horizontal Sync Signal using H_count
	IF (h_count <= H_sync_high) AND (h_count >= H_sync_low) THEN
 	  	horiz_sync <= '0';
	ELSE
 	  	horiz_sync <= '1';
	END IF;

--V_count counts rows of pixels (#pixel rows down + extra time for V sync signal)
--  
--  Vert_sync      -----------------------------------------------_______------------
--  V_count         0                        last pixel row      V sync low       end
--
	IF (v_count >= V_end_count) AND (h_count >= H_sync_low) THEN
   		v_count <= "0000000000";
	ELSIF (h_count = H_sync_low) THEN
   		v_count <= v_count + 1;
	END IF;

-- Generate Vertical Sync Signal using V_count
	IF (v_count <= V_sync_high) AND (v_count >= V_sync_low) THEN
   		vert_sync <= '0';
	ELSE
  		vert_sync <= '1';
	END IF;

-- Generate Video on Screen Signals for Pixel Data
-- Video on = 1 indicates pixel are being displayed
-- Video on = 0 retrace - user logic can update pixel
-- memory without needing to read memory for display
	IF (h_count < H_pixels_across) THEN
   		video_on_h <= '1';
   		pixel_column <= h_count;
	ELSE
	   	video_on_h <= '0';
	END IF;

	IF (v_count <= V_pixels_down) THEN
   		video_on_v <= '1';
   		pixel_row <= v_count;
	ELSE
   		video_on_v <= '0';
	END IF;

-- Put all video signals through DFFs to eliminate any small timing delays that cause a blurry image
		horiz_sync_out <= horiz_sync;
		vert_sync_out <= vert_sync;
-- 		Also turn off RGB color signals at edge of screen during vertical and horizontal retrace
		red_out <= red AND video_on_int;
		green_out <= green AND video_on_int;
		blue_out <= blue AND video_on_int;

END PROCESS a1;
END a;
------------------------------------------------------------------------------------
-------------------------------------END--------------------------------------------
------------------------------------------------------------------------------------

------------------------------------------------------------------------------------
------------------------------VGA SYNCH PACKAGE-------------------------------------
------------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_unsigned.all;

PACKAGE vga_sync_package IS
COMPONENT vga_sync
PORT(	clock_50Mhz, red, green, blue		: IN	STD_LOGIC;
			red_out, green_out, blue_out, horiz_sync_out, 
			vert_sync_out, video_on, pixel_clock	: OUT	STD_LOGIC;
			pixel_row, pixel_column: OUT STD_LOGIC_VECTOR(9 DOWNTO 0));
END COMPONENT;
END vga_sync_package;
------------------------------------------------------------------------------------
---------------------------------END---------------------------------------------
------------------------------------------------------------------------------------

------------------------------------------------------------------------------------
------------------------------CHARACTER ROM-----------------------------------------
------------------------------------------------------------------------------------
library IEEE;
use  IEEE.STD_LOGIC_1164.all;
use  IEEE.STD_LOGIC_ARITH.all;
use  IEEE.STD_LOGIC_UNSIGNED.all;
LIBRARY lpm;
USE lpm.lpm_components.ALL;

ENTITY Char_ROM IS
	PORT(	character_address			: IN	STD_LOGIC_VECTOR(9 DOWNTO 0);
			font_col						: IN 	STD_LOGIC_VECTOR(2 DOWNTO 0);
			clock							: IN  STD_LOGIC;
			rom_mux_output				: OUT	STD_LOGIC);
END Char_ROM;

ARCHITECTURE a OF Char_ROM IS
	SIGNAL	rom_data: STD_LOGIC_VECTOR(7 DOWNTO 0);
	SIGNAL	rom_address: STD_LOGIC_VECTOR(9 DOWNTO 0);
BEGIN
-- Small 8 by 8 Character Generator ROM for Video Display
-- Each character is 8 8-bits words of pixel data
		char_gen_rom: lpm_rom
      GENERIC MAP ( 	lpm_widthad => 10,
							lpm_numwords => 576,
							lpm_outdata => "UNREGISTERED",
							lpm_address_control => "REGISTERED",
							-- Reads in mif file for character generator font data 
							lpm_file => "char.mif",
							lpm_width => 8)
      PORT MAP(inclock => clock, address => rom_address, q => rom_data);

rom_address <= character_address;
-- Mux to pick off correct rom data bit from 8-bit word
-- for on screen character generation
rom_mux_output <= rom_data((CONV_INTEGER(NOT font_col(2 downto 0))));

END a;
------------------------------------------------------------------------------------
--------------------------------END---------------------------------------------
------------------------------------------------------------------------------------
			
		
			