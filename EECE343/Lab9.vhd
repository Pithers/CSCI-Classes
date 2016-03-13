--Slot.vhd
--Brandon Smith, John-Mark Mamalakis

------------------------------------------------------------------------------------
-------------------Main Entity, Define Pins Here------------------------------------
------------------------------------------------------------------------------------
Library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;
entity slot is
port (	-------------Variables for switches etc---------------
		reset, clk, reset_v, play, stop_rot		: in 	std_logic;
		
		
		------------Seven Segment Pins--------------------
		seg0, seg1, seg2, seg3	: out	std_logic_vector (6 downto 0);
		------------------LEDs----------------------------
		led1							: out std_logic_vector (8 downto 0);
		-----------------LCD Pins-------------------------
		LCD_RS, LCD_E          	: OUT	STD_LOGIC;
		LCD_RW                 	: OUT STD_LOGIC;
		LCD_ON                 	: OUT	STD_LOGIC;
		LCD_BLON               	: OUT STD_LOGIC;
		DATA_BUS               	: INOUT STD_LOGIC_VECTOR(7 DOWNTO 0);
		------------------VGA Pins--------------------------
		
        VGA_Red,VGA_Green,VGA_Blue,VGA_HSync,VGA_VSync,video_blank_out,Video_clock_out	:OUT std_logic);
end slot;
architecture ckt of slot is
	------------------------------------------Signals Go Here----------------------------------
	TYPE state0 is (R0_0, R0_1, R0_2, R0_3, R0_4, R0_5, R0_6, R0_7, R0_8, R0_9);
	TYPE state1 is (R1_0, R1_1, R1_2, R1_3, R1_4, R1_5, R1_6, R1_7, R1_8, R1_9);
	TYPE state2 is (R2_0, R2_1, R2_2, R2_3, R2_4, R2_5, R2_6, R2_7, R2_8, R2_9);
	signal R0_state: state0;
	signal R1_state: state1;
	signal R2_state: state2;

	signal m1, m0, m2, m3: 										std_logic_vector (3 downto 0);
	signal seg_data0, seg_data1, seg_data2, seg_data3: std_logic_vector (6 downto 0);
	signal clkout: 												std_logic;
	signal clkout1:												std_logic;
	signal clkout2:												std_logic;
	signal sLCD_RS: 												std_logic;
	signal sLCD_E: 												std_logic;
	signal sLCD_RW: 												std_logic;
	signal sLCD_ON: 												std_logic;
	signal sLCD_BLON: 											std_logic;
	signal Hex_Display_Data: 									std_logic_vector((2*4)-1 DOWNTO 0);
	signal chip: 													std_logic;
	signal drink: 													std_logic;
	signal st: 														std_logic_vector(11 downto 0);
	signal pixel_row_sig, pixel_column_sig: 				STD_LOGIC_VECTOR(9 DOWNTO 0);
	signal out_sig: 												STD_LOGIC;
	signal red_sig,green_sig,blue_sig,vert_sync_sig:	STD_LOGIC;
	
	signal slot_counter1: integer range 0 to 1;
	signal slot_counter2: integer range 0 to 1;
	signal slot_counter3: integer range 0 to 2;
	signal coin : integer range 0 to 1;
	-----------------------------------------------------------------------------------

	--------------------------------Components Go Here----------------------------------------
	component slowclk is
		port(	clk: in std_logic;
				clkout: out std_logic);
	end component;
	
	component slowclk1 is
		port(	clk: in std_logic;
				clkout: out std_logic);
	end component;
	
	component slowclk2 is
		port(	clk: in std_logic;
				clkout: out std_logic);
	end component;
	
	component LCD_Display is
	port(	reset, CLOCK_50        : IN  	STD_LOGIC;
			Hex_Display_Data       : IN  	STD_LOGIC_VECTOR((2*4)-1 DOWNTO 0);
			LCD_RS, LCD_E          : OUT 	STD_LOGIC;
			LCD_RW                 : OUT 	STD_LOGIC;
			LCD_ON                 : OUT 	STD_LOGIC;
			LCD_BLON               : OUT 	STD_LOGIC;
			DATA_BUS               : INOUT 	STD_LOGIC_VECTOR(7 DOWNTO 0));
	end component;
	
	component vga_sync
	port(   clock_50Mhz, red, green, blue			: IN STD_LOGIC;
			red_out, green_out, blue_out, horiz_sync_out, 
			vert_sync_out, video_on, pixel_clock	: OUT STD_LOGIC;
			pixel_row, pixel_column					: OUT STD_LOGIC_VECTOR(9 DOWNTO 0));
	end component;
	
	component char_ROM
	port(	character_address		: IN	STD_LOGIC_VECTOR(5 DOWNTO 0);
			font_row, font_col		: IN 	STD_LOGIC_VECTOR(2 DOWNTO 0);
			rom_mux_output			: OUT	STD_LOGIC);
	end component;
	
	COMPONENT ball
	port(	pixel_row, pixel_column	: IN 	std_logic_vector(9 DOWNTO 0);
			Red,Green,Blue 			: OUT 	std_logic;
			Vert_sync				: IN 	std_logic);
	END COMPONENT;
	-----------------------------------------------------------------------------------
	
	------------------------------------Assign Variables to Components-----------------
	begin
	stage1:  slowclk port map(clk, clkout);
	stage3:  slowclk1 port map(clk, clkout1);
	stage4:  slowclk2 port map(clk, clkout2);
	stage2: LCD_Display port map(reset, clk, Hex_Display_Data, sLCD_RS, sLCD_E, sLCD_RW, sLCD_ON, sLCD_BLON, DATA_BUS);
	sync0:vga_sync port map(clk, red_sig,green_sig,blue_sig, VGA_Red,VGA_Green,VGA_Blue,
                        VGA_HSync, vert_sync_sig,video_blank_out,Video_clock_out,pixel_row_sig, 
                        pixel_column_sig);

	-----------------------------------------------------------------------------------

	-----------------------------VGA Stuff---------------------------------------------
	VGA_VSync<=vert_sync_sig;
	--green_sig <= '1'; --WON
	--blue_sig <= '1'; 
	--red_sig <= '0';	  
	-----------------------------------------------------------------------------------
	
	-------------------------LCD Stuff-------------------------------------------------
	LCD_E <= sLCD_E;
	LCD_RS <= sLCD_RS;
	LCD_RW <= sLCD_RW;
	LCD_ON <= sLCD_ON;
	LCD_BLON <= sLCD_BLON;
	
	--Hex_Display_Data <= "00000001"; --PLAY?
	--Hex_Display_Data <= "00000010"; --WIN!
	--Hex_Display_Data <= "00000100"; --LOSE PLAY AGAIN?
	-----------------------------------------------------------------------------------
	
	---------------------------SLOT stuff---------------------------------------------


	process(clkout, clkout1, clkout2, play, stop_rot , m0, m1, m2)
	begin	
		IF(play'event and play = '1' and coin = 0) THEN
			coin <= 1;
				
		end if ;
		
		IF(stop_rot'event and stop_rot = '1') then
			if((slot_counter1 = 0) and (slot_counter2 = 0) and (slot_counter3 = 0))then
				slot_counter1 <=1;
			elsif((slot_counter1 = 1) and (slot_counter2 = 0) and (slot_counter3 = 0))then
				slot_counter2 <=1;
			elsif((slot_counter1 = 1) and (slot_counter2 = 1) and (slot_counter3 = 0))then
				slot_counter3 <=1;
			elsif((slot_counter1 = 1) and (slot_counter2 = 1) and (slot_counter3 = 1))then
				slot_counter3 <=2;	
			else
			slot_counter1 <= 0;
			slot_counter2 <= 0;
			slot_counter3 <= 0;
			
			end if;
		end if;
		--- rotor 1; 
		if((clkout'event and clkout = '1' and coin = 1) and slot_counter1 < 1) THEN
			case R0_state is
				when R0_0 =>
					R0_state <= R0_1;
					st(3)<='0'; 
					st(2)<='0'; 
					st(1)<='0'; 
					st(0)<='0';
				when R0_1 =>
					st(3)<='0'; 
					st(2)<='0'; 
					st(1)<='0'; 
					st(0)<='1'; --1
					R0_state <= R0_4;

				when R0_4 =>
					st(3)<='0'; 
					st(2)<='1'; 
					st(1)<= '0'; 
					st(0) <= '0'; --4

					R0_state <= R0_7;

				when R0_7 =>
					st(3)<='0'; 
					st(2)<='1'; 
					st(1)<= '1'; 
					st(0) <= '1'; --7

					R0_state <= R0_6;


				when R0_6 =>
					st(3)<='0'; 
					st(2)<='1'; 
					st(1)<= '1'; 
					st(0)<= '0'; --6				

					R0_state <= R0_3;

				when R0_3 =>
					st(3)<='0'; 
					st(2)<='0'; 
					st(1)<= '1'; 
					st(0) <= '1'; --3

					R0_state <= R0_5;

				when R0_5 =>
					st(3)<='0'; 
					st(2)<='1'; 
					st(1)<= '0'; 
					st(0) <= '1';--5

					R0_state <= R0_9;

				when R0_9 =>
					st(3)<='1'; 
					st(2)<='0'; 
					st(1)<= '0'; 
					st(0) <= '1';--9

					R0_state <= R0_8;

				when R0_8 =>
					st(3)<='1'; 
					st(2)<='0'; 
					st(1)<='0'; 
					st(0)<='0';--8	

					R0_state <= R0_2;

				when R0_2 =>
					st(3)<='0'; 
					st(2)<='0'; 
					st(1)<= '1'; 
					st(0)<= '0';--2

					R0_state <= R0_1;

				end case;
			end if;
			
			-----Rotor 2
		if((clkout1'event and clkout1 = '1' and coin = 1)and slot_counter2 <1) THEN
			case R1_state is
				when R1_0 =>
					R1_state <= R1_5;
					st(7)<='0'; 
					st(6)<='0'; 
					st(5)<='0'; 
					st(4)<='0';
				when R1_5 =>
					st(7)<='0'; 
					st(6)<='1'; 
					st(5)<='0'; 
					st(4)<='1'; --5

					R1_state <= R1_7;

				when R1_7 =>
					st(7)<='0'; 
					st(6)<='1'; 
					st(5)<='1'; 
					st(4)<='1';--7
	
					R1_state <= R1_8;

				when R1_8 =>
					st(7)<='1'; 
					st(6)<='0'; 
					st(5)<='0'; 
					st(4)<='0'; --8

					R1_state <= R1_3;

				when R1_3 =>
					st(7)<='0'; 
					st(6)<='0'; 
					st(5)<='1'; 
					st(4)<='1'; --3				

					R1_state <= R1_2;

				when R1_2 =>
					st(7)<='0'; 
					st(6)<='0'; 
					st(5)<='1'; 
					st(4)<='0'; --2

					R1_state <= R1_4;

				when R1_4 =>
					st(7)<='0'; 
					st(6)<='1'; 
					st(5)<='0'; 
					st(4)<='0';--4

					R1_state <= R1_9;

				when R1_9 =>
					st(7)<='1'; 
					st(6)<='0'; 
					st(5)<='0'; 
					st(4)<='1';--9

					R1_state <= R1_1;

				when R1_1 =>
					st(7)<='0'; 
					st(6)<='0'; 
					st(5)<='0'; 
					st(4)<='1';--1	

					R1_state <= R1_6;

				when R1_6 =>
					st(7)<='0'; 
					st(6)<='1'; 
					st(5)<='1'; 
					st(4)<='0';--6

					R1_state <= R1_5;

				end case;
			end if;
			
			
			-----Rotor 3
		if((clkout2'event and clkout2 = '1' and coin = 1) and slot_counter3 <1  ) THEN
			case R2_state is
				when R2_0 =>
					R2_state <= R2_8;
					st(11)<='0'; 
					st(10)<='0'; 
					st(9)<='0'; 
					st(8)<='0';
				when R2_8 =>
					st(11)<='1'; 
					st(10)<='0'; 
					st(9)<='0'; 
					st(8)<='0'; --8

					R2_state <= R2_1;

				when R2_1 =>
					st(11)<='0'; 
					st(10)<='0'; 
					st(9)<='0'; 
					st(8)<='1';--1

					R2_state <= R2_4;

				when R2_4 =>
					st(11)<='0'; 
					st(10)<='1'; 
					st(9)<='0'; 
					st(8)<='0'; --4

					R2_state <= R2_9;

				when R2_9 =>
					st(11)<='1'; 
					st(10)<='0'; 
					st(9)<='0'; 
					st(8)<='1'; --9				

					R2_state <= R2_7;

				when R2_7 =>
					st(11)<='0'; 
					st(10)<='1'; 
					st(9)<='1'; 
					st(8)<='1'; --7

					R2_state <= R2_3;

				when R2_3 =>
					st(11)<='0'; 
					st(10)<='0'; 
					st(9)<='1'; 
					st(8)<='1';--3

					R2_state <= R2_2;

				when R2_2 =>
					st(11)<='0'; 
					st(10)<='0'; 
					st(9)<='1'; 
					st(8)<='0';--2

					R2_state <= R2_6;

				when R2_6 =>
					st(11)<='0'; 
					st(10)<='1'; 
					st(9)<='1'; 
					st(8)<='0';--8	

					R2_state <= R2_5;

				when R2_5 =>
					st(11)<='0'; 
					st(10)<='1'; 
					st(9)<='0'; 
					st(8)<='1';--5

					R2_state <= R2_8;
				end case;
			end if;
			
			
			
	IF(stop_rot = '1' and slot_counter3 = 2) THEN
		if((m0 = m1) and (m1 = m2)) then
			green_sig <= '1';
			blue_sig <= '0'; 
			red_sig <= '0';
			Hex_Display_Data <= "00000010"; --WIN!
			R2_state <= R2_0;
			R1_state <= R1_0;
			R0_state <= R0_0;

			coin <= 0;
		else
			Hex_Display_Data <= "00000100"; --LOSE PLAY AGAIN?
			green_sig <= '0';
			blue_sig <= '0'; 
			red_sig <= '1';
			R2_state <= R2_0;
			R1_state <= R1_0;
			R0_state <= R0_0;

			coin <= 0;
			end if;
	else
			Hex_Display_Data <= "00000001";
			green_sig <= '0';
			blue_sig <= '1'; 
			red_sig <= '0';
	end if;	

			
		end process;
	----------------Assignments for Seven Segments-------------------------------------
	m2 <= st(11) & st(10) & st(9) & st(8);
	m1 <= st(7) & st(6) & st(5) & st(4);  --MSB
	m0 <= st(3) & st(2) & st(1) & st(0);  --LSB 7 seg display
	-------------------------------------------------FINISH THIS-----------
	--green_sig <= '1';
	--blue_sig <= '1'; 
	--red_sig <= '0';	
	--Hex_Display_Data <= "00000001"; --PLAY?
	--Hex_Display_Data <= "00000010"; --WIN!
	--Hex_Display_Data <= "00000100"; --LOSE PLAY AGAIN?
	
	
	
	
	seg0 <= NOT(seg_data0);
	seg1 <= NOT(seg_data1);
	seg2 <= NOT(seg_data2);
	seg3 <= NOT(seg_data3);

	process(clkout, reset_v)
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
		case m2 is					  
			when "0000" => seg_data2 <= "0111111";
			when "0001" => seg_data2 <= "0000110";
			when "0010" => seg_data2 <= "1011011";
			when "0011" => seg_data2 <= "1001111";
			when "0100" => seg_data2 <= "1100110";
			when "0101" => seg_data2 <= "1101101";
			when "0110" => seg_data2 <= "1111101";
			when "0111" => seg_data2 <= "0000111";
			when "1000" => seg_data2 <= "1111111";
			when "1001" => seg_data2 <= "1100111";
			when "1010" => seg_data2 <= "1110111";
			when "1011" => seg_data2 <= "1111100";
			when "1100" => seg_data2 <= "0111001";
			when "1101" => seg_data2 <= "1011110";
			when "1110" => seg_data2 <= "1111001";
			when others => seg_data2 <= "1110001";
		end case;
		case m3 is					  
			when "0000" => seg_data3 <= "0111111";
			when "0001" => seg_data3 <= "0000110";
			when "0010" => seg_data3 <= "1011011";
			when "0011" => seg_data3 <= "1001111";
			when "0100" => seg_data3 <= "1100110";
			when "0101" => seg_data3 <= "1101101";
			when "0110" => seg_data3 <= "1111101";
			when "0111" => seg_data3 <= "0000111";
			when "1000" => seg_data3 <= "1111111";
			when "1001" => seg_data3 <= "1100111";
			when "1010" => seg_data3 <= "1110111";
			when "1011" => seg_data3 <= "1111100";
			when "1100" => seg_data3 <= "0111001";
			when "1101" => seg_data3 <= "1011110";
			when "1110" => seg_data3 <= "1111001";
			when others => seg_data3 <= "1110001";
		end case;
	end process;
	------------------------------------------------------------------------------------
	
end ckt;	

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
---------------------------------slow clock1-----------------------------------------
------------------------------------------------------------------------------------
Library ieee;
use ieee.std_logic_1164.all;
entity slowclk1 is
	port(clk: in std_logic; clkout: out std_logic);
end slowclk1;
architecture ckt of slowclk1 is
begin 
	process(clk)
	variable cnt: integer range 0 to 5000000;  --clock speeds set here
	begin	
		if (clk'event and clk = '1') THEN
			if(cnt = 5000000) THEN				--same clock speed
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
---------------------------------slow clock2-----------------------------------------
------------------------------------------------------------------------------------
Library ieee;
use ieee.std_logic_1164.all;
entity slowclk2 is
	port(clk: in std_logic; clkout: out std_logic);
end slowclk2;
architecture ckt of slowclk2 is
begin 
	process(clk)
	variable cnt: integer range 0 to 15000000;  --clock speeds set here
	begin	
		if (clk'event and clk = '1') THEN
			if(cnt = 15000000) THEN				--same clock speed
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
----------------------------------LCD Define-------------------------------------------
------------------------------------------------------------------------------------ 
LIBRARY IEEE;
USE  IEEE.STD_LOGIC_1164.all;
USE  IEEE.STD_LOGIC_ARITH.all;
USE  IEEE.STD_LOGIC_UNSIGNED.all;

ENTITY LCD_Display IS
   GENERIC(Num_Hex_Digits: Integer:= 2); 

   PORT(reset, CLOCK_50       : IN  STD_LOGIC;
       Hex_Display_Data       : IN    STD_LOGIC_VECTOR((2*4)-1 DOWNTO 0);
       LCD_RS, LCD_E          : OUT STD_LOGIC;
       LCD_RW                 : OUT   STD_LOGIC;
       LCD_ON                 : OUT STD_LOGIC;
       LCD_BLON               : OUT STD_LOGIC;
       DATA_BUS               : INOUT  STD_LOGIC_VECTOR(7 DOWNTO 0));
      
END ENTITY LCD_Display;

ARCHITECTURE Behavior OF LCD_Display IS
	TYPE character_string IS ARRAY ( 0 TO 31 ) OF STD_LOGIC_VECTOR( 7 DOWNTO 0 );

	TYPE STATE_TYPE IS (HOLD, FUNC_SET, DISPLAY_ON, MODE_SET, Print_String,
               LINE2, RETURN_HOME, DROP_LCD_E, RESET1, RESET2, 
               RESET3, DISPLAY_OFF, DISPLAY_CLEAR);

	SIGNAL   state, next_command           : STATE_TYPE;
	SIGNAL   LCD_display_string            : character_string;

	-- Enter new ASCII hex data above for LCD Display

	SIGNAL   DATA_BUS_VALUE, Next_Char     : STD_LOGIC_VECTOR(7 DOWNTO 0);
	SIGNAL   CLK_COUNT_400HZ               : STD_LOGIC_VECTOR(19 DOWNTO 0);
	SIGNAL   CHAR_COUNT                    : STD_LOGIC_VECTOR(4 DOWNTO 0);
	SIGNAL   CLK_400HZ_Enable,LCD_RW_INT   : STD_LOGIC;
	SIGNAL   Line1_chars, Line2_chars      : STD_LOGIC_VECTOR(127 DOWNTO 0);
BEGIN

	LCD_ON      <= '1';
	LCD_BLON    <= '1';

	-- BIDIRECTIONAL TRI STATE LCD DATA BUS
   DATA_BUS <= DATA_BUS_VALUE WHEN LCD_RW_INT = '0' ELSE "ZZZZZZZZ";

	-- get next character in display string
   Next_Char <= LCD_display_string(CONV_INTEGER(CHAR_COUNT));
   LCD_RW <= LCD_RW_INT;
	
	--Hex_Display_Data <= "00000001"; --PLAY?
	--Hex_Display_Data <= "00000010"; --WIN!
	--Hex_Display_Data <= "00000100"; --LOSE PLAY AGAIN?
   
   PROCESS
   BEGIN

		IF Hex_Display_Data(0) = '1' then								--PLAY?
			LCD_display_string <= (
			X"05",X"C4",X"14",X"95",X"F3",X"20",
			X"20", X"20", X"20", X"20",
			X"35",X"20",X"20",X"20",X"20",X"20",
			--Line2
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20",
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20");
		elsif Hex_Display_Data(1) = '1' then							--WIN!
			LCD_display_string <= (
			X"75",X"94",X"E4",X"12",X"20",X"20",
			X"20", X"20", X"20", X"20",
			X"20",X"20",X"20",X"20",X"20",X"20",
			--Line2
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20",
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20");
		elsif Hex_Display_Data(2) = '1' then							--LOSE 
			LCD_display_string <= (											--PLAY AGAIN?
			X"C4",X"F4",X"35",X"54",X"12",X"50",
			X"55", X"52", X"43", X"48",
			X"41",X"53",X"46",X"44",X"20",X"20",
			--Line2
			X"05",X"C4",X"14",X"95",X"20",X"14",X"74",X"14",
			X"94",X"E4",X"F3",X"20",X"20",X"20",X"20",X"20");
		else	
			LCD_display_string <= (
			X"20",X"20",X"20",X"20",X"20",X"20",
			X"20", X"20", X"20", X"20",
			X"20",X"20",X"20",X"20",X"20",X"20",
			--Line2
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20",
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20");
		end if;
	
    WAIT UNTIL CLOCK_50'EVENT AND CLOCK_50 = '1';
      IF RESET = '0' THEN
       CLK_COUNT_400HZ <= X"00000";
       CLK_400HZ_Enable <= '0';
      ELSE
            IF CLK_COUNT_400HZ < X"0F424" THEN 
             CLK_COUNT_400HZ <= CLK_COUNT_400HZ + 1;
             CLK_400HZ_Enable <= '0';
            ELSE
             CLK_COUNT_400HZ <= X"00000";
             CLK_400HZ_Enable <= '1';
            END IF;
      END IF;
   END PROCESS;

   PROCESS (CLOCK_50, reset)
   BEGIN
      IF reset = '0' THEN
         state <= RESET1;
         DATA_BUS_VALUE <= X"38";
         next_command <= RESET2;
         LCD_E <= '1';
         LCD_RS <= '0';
         LCD_RW_INT <= '0';

      ELSIF CLOCK_50'EVENT AND CLOCK_50 = '1' THEN
-- State Machine to send commands and data to LCD DISPLAY         
        IF CLK_400HZ_Enable = '1' THEN
         CASE state IS
-- Set Function to 8-bit transfer and 2 line display with 5x8 Font size
-- see Hitachi HD44780 family data sheet for LCD command and timing details
            WHEN RESET1 =>
                  LCD_E <= '1';
                  LCD_RS <= '0';
                  LCD_RW_INT <= '0';
                  DATA_BUS_VALUE <= X"38";
                  state <= DROP_LCD_E;
                  next_command <= RESET2;
                  CHAR_COUNT <= "00000";
            WHEN RESET2 =>
                  LCD_E <= '1';
                  LCD_RS <= '0';
                  LCD_RW_INT <= '0';
                  DATA_BUS_VALUE <= X"38";
                  state <= DROP_LCD_E;
                  next_command <= RESET3;
            WHEN RESET3 =>
                  LCD_E <= '1';
                  LCD_RS <= '0';
                  LCD_RW_INT <= '0';
                  DATA_BUS_VALUE <= X"38";
                  state <= DROP_LCD_E;
                  next_command <= FUNC_SET;
-- EXTRA STATES ABOVE ARE NEEDED FOR RELIABLE PUSHBUTTON RESET OF LCD
            WHEN FUNC_SET =>
                  LCD_E <= '1';
                  LCD_RS <= '0';
                  LCD_RW_INT <= '0';
                  DATA_BUS_VALUE <= X"38";
                  state <= DROP_LCD_E;
                  next_command <= DISPLAY_OFF;
-- Turn off Display and Turn off cursor
            WHEN DISPLAY_OFF =>
                  LCD_E <= '1';
                  LCD_RS <= '0';
                  LCD_RW_INT <= '0';
                  DATA_BUS_VALUE <= X"08";
                  state <= DROP_LCD_E;
                  next_command <= DISPLAY_CLEAR;
-- Clear Display and Turn off cursor
            WHEN DISPLAY_CLEAR =>
                  LCD_E <= '1';
                  LCD_RS <= '0';
                  LCD_RW_INT <= '0';
                  DATA_BUS_VALUE <= X"01";
                  state <= DROP_LCD_E;
                  next_command <= DISPLAY_ON;
-- Turn on Display and Turn off cursor
            WHEN DISPLAY_ON =>
                  LCD_E <= '1';
                  LCD_RS <= '0';
                  LCD_RW_INT <= '0';
                  DATA_BUS_VALUE <= X"0C";
                  state <= DROP_LCD_E;
                  next_command <= MODE_SET;
-- Set write mode to auto increment address and move cursor to the right
            WHEN MODE_SET =>
                  LCD_E <= '1';
                  LCD_RS <= '0';
                  LCD_RW_INT <= '0';
                  DATA_BUS_VALUE <= X"06";
                  state <= DROP_LCD_E;
                  next_command <= Print_String;
-- Write ASCII hex character in first LCD character location
            WHEN Print_String =>
                  state <= DROP_LCD_E;
                  LCD_E <= '1';
                  LCD_RS <= '1';
                  LCD_RW_INT <= '0';
-- ASCII character to output
                  IF Next_Char(7 DOWNTO  4) /= X"0" THEN
                  DATA_BUS_VALUE <= Next_Char;
                  ELSE
-- Convert 4-bit value to an ASCII hex digit
                     IF Next_Char(3 DOWNTO 0) >9 THEN
-- ASCII A...F
                      DATA_BUS_VALUE <= X"4" & (Next_Char(3 DOWNTO 0)-9);
                     ELSE
-- ASCII 0...9
                      DATA_BUS_VALUE <= X"3" & Next_Char(3 DOWNTO 0);
                     END IF;
                  END IF;
                  state <= DROP_LCD_E;
-- Loop to send out 32 characters to LCD Display  (16 by 2 lines)
                  IF (CHAR_COUNT < 31) AND (Next_Char /= X"FE") THEN 
                   CHAR_COUNT <= CHAR_COUNT +1;
                  ELSE 
                   CHAR_COUNT <= "00000"; 
                  END IF;
-- Jump to second line?
                  IF CHAR_COUNT = 15 THEN next_command <= line2;
-- Return to first line?
                  ELSIF (CHAR_COUNT = 31) OR (Next_Char = X"FE") THEN 
                   next_command <= return_home; 
                  ELSE next_command <= Print_String; END IF;
-- Set write address to line 2 character 1
            WHEN LINE2 =>
                  LCD_E <= '1';
                  LCD_RS <= '0';
                  LCD_RW_INT <= '0';
                  DATA_BUS_VALUE <= X"C0";
                  state <= DROP_LCD_E;
                  next_command <= Print_String;
-- Return write address to first character postion on line 1
            WHEN RETURN_HOME =>
                  LCD_E <= '1';
                  LCD_RS <= '0';
                  LCD_RW_INT <= '0';
                  DATA_BUS_VALUE <= X"80";
                  state <= DROP_LCD_E;
                  next_command <= Print_String;
-- The next three states occur at the end of each command or data transfer to the LCD
-- Drop LCD E line - falling edge loads inst/data to LCD controller
            WHEN DROP_LCD_E =>
                  LCD_E <= '0';
                  state <= HOLD;
-- Hold LCD inst/data valid after falling edge of E line          
            WHEN HOLD =>
                  state <= next_command;
         END CASE;
        END IF;
      END IF;
   END PROCESS;
END Behavior;
------------------------------------------------------------------------------------
------------------------------------END---------------------------------------------
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
	PORT(	character_address			: IN	STD_LOGIC_VECTOR(5 DOWNTO 0);
			font_row, font_col			: IN 	STD_LOGIC_VECTOR(2 DOWNTO 0);
			rom_mux_output	: OUT	STD_LOGIC);
END Char_ROM;

ARCHITECTURE a OF Char_ROM IS
	SIGNAL	rom_data: STD_LOGIC_VECTOR(7 DOWNTO 0);
	SIGNAL	rom_address: STD_LOGIC_VECTOR(8 DOWNTO 0);
BEGIN
-- Small 8 by 8 Character Generator ROM for Video Display
-- Each character is 8 8-bits words of pixel data
 char_gen_rom: lpm_rom
      GENERIC MAP ( lpm_widthad => 9,
        lpm_numwords => 512,
        lpm_outdata => "UNREGISTERED",
        lpm_address_control => "UNREGISTERED",
-- Reads in mif file for character generator font data 
         lpm_file => "init.mif",
         lpm_width => 8)
      PORT MAP ( address => rom_address, q => rom_data);

rom_address <= character_address & font_row;
-- Mux to pick off correct rom data bit from 8-bit word
-- for on screen character generation
rom_mux_output <= rom_data ( (CONV_INTEGER(NOT font_col(2 downto 0))));

END a;
------------------------------------------------------------------------------------
--------------------------------END---------------------------------------------
------------------------------------------------------------------------------------

------------------------------------------------------------------------------------
-------------------------------BALL PACKAGE------------------------------------------
------------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
PACKAGE ball_package IS
COMPONENT ball
 PORT(pixel_row, pixel_column		: IN std_logic_vector(9 DOWNTO 0);
        Red,Green,Blue 				: OUT std_logic;
        Vert_sync	: IN std_logic);
END COMPONENT;
END ball_package;
------------------------------------------------------------------------------------
--------------------------------END---------------------------------------------
------------------------------------------------------------------------------------

------------------------------------------------------------------------------------
------------------------------BALL ENTITY------------------------------------------
------------------------------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;
USE  IEEE.STD_LOGIC_ARITH.all;
USE  IEEE.STD_LOGIC_UNSIGNED.all;

ENTITY ball IS

   PORT(	pixel_row, pixel_column		: IN std_logic_vector(9 DOWNTO 0);
			Red,Green,Blue 				: OUT std_logic;
			Vert_sync					: IN std_logic;
			pin 						: IN std_logic);
      
END ball;

architecture behavior of ball is

-- Video Display Signals   
SIGNAL Ball_on, Direction					: std_logic;
SIGNAL Size 									: std_logic_vector(9 DOWNTO 0);  
SIGNAL Ball_Y_motion, Ball_X_motion 	: std_logic_vector(9 DOWNTO 0);
SIGNAL Ball_Y_pos, Ball_X_pos				: std_logic_vector(9 DOWNTO 0);
SIGNAL counter									: std_logic_vector(3 DOWNTO 0);
SIGNAL counter_color 						:  std_logic_vector(2 DOWNTO 0);

BEGIN           

--Size <= CONV_STD_LOGIC_VECTOR(8,10);
--Ball_X_pos <= CONV_STD_LOGIC_VECTOR(320,10);

process (counter_color, pin)
begin
			IF(pin = '1') THEN
					Red <= '1';
					Green <= '1';
				   Blue <= '0';	
			Else
				IF(counter_color < "011") THEN
					Red <= NOT Ball_on;
					Green <= NOT Ball_on;
				   Blue <= '1';
				ELSIF ((counter_color > "011") AND (counter_color < "101")) THEN
					Red <= NOT Ball_on;
					Green <= '1';
				   Blue <= NOT Ball_on;	
				ELSE
					Red <= '1';
					Green <= NOT Ball_on;
				   Blue <= NOT Ball_on;	
				end IF;
			end if;
end process;

RGB_Display: Process (Ball_X_pos, Ball_Y_pos, pixel_column, pixel_row, Size)
BEGIN
			-- Set Ball_on ='1' to display ball
 IF ('0' & Ball_X_pos <= pixel_column + Size) AND
	 (Ball_X_pos + Size >= '0' & pixel_column) AND
	 ('0' & Ball_Y_pos <= pixel_row + Size) AND
	 (Ball_Y_pos + Size >= '0' & pixel_row ) THEN
 		Ball_on <= '1';
 	ELSE
 		Ball_on <= '0';
END IF;
END process RGB_Display;

Move_Ball: process
BEGIN
			-- Move ball once every vertical sync
	WAIT UNTIL vert_sync'event and vert_sync = '1';
			IF (counter = "1111") THEN
				counter <= "0000";
				Size <= CONV_STD_LOGIC_VECTOR(8,10);
			ELSIF counter > "0011" and counter < "1100" THEN
				Size <= Size + '1';
				counter <= counter + '1';
			ELSE
				counter <= counter + '1';
			END IF;
			
			IF (counter_color < "111" ) then
				counter_color <= counter_color + 1;
			else
				counter_color <= "000";
			end if;
			
			-- Bounce off top or bottom of screen
			IF ('0' & Ball_Y_pos) >= 480 - Size THEN
				Ball_Y_motion <= CONV_STD_LOGIC_VECTOR(-5,10);
			ELSIF Ball_Y_pos <= Size THEN
				Ball_Y_motion <= CONV_STD_LOGIC_VECTOR(5,10);
			--	IF (counter_color < "111" ) then
				--	counter_color <= counter_color + 1;
				--else
					--counter_color <= "000";
				--end if;
			END IF;
			
			-- Bounce off sides of screen
			IF ('0' & Ball_X_pos) >= 640 - Size THEN
				Ball_X_motion <= CONV_STD_LOGIC_VECTOR(-5,10);
			ELSIF Ball_X_pos <= Size THEN
				Ball_X_motion <= CONV_STD_LOGIC_VECTOR(5,10);	
				--IF (counter_color < "111" ) then
				--	counter_color <= counter_color + 1;
				--else
				--	counter_color <= "000";
				--end if;
			END IF;

			-- Compute next ball Y position
				Ball_Y_pos <= Ball_Y_pos + Ball_Y_motion;
			-- Compute next ball X position
				Ball_X_pos <= Ball_X_pos + Ball_X_motion;
				
END process Move_Ball;
END behavior;
------------------------------------------------------------------------------------
------------------------------------END---------------------------------------------
------------------------------------------------------------------------------------

