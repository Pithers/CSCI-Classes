--Brandon Smith, John Mark, Counter program
Library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity vending is
port (reset, clk, reset_v: in std_logic;
		load_data: in std_logic_vector (3 downto 0);
		buy: in std_logic_vector (1 downto 0);
		seg0, seg1, seg2, seg3: out std_logic_vector (6 downto 0);
		led1: out std_logic_vector (8 downto 0);
		LCD_RS, LCD_E          : OUT STD_LOGIC;
      LCD_RW                 : OUT   STD_LOGIC;
      LCD_ON                 : OUT STD_LOGIC;
      LCD_BLON               : OUT STD_LOGIC;
      DATA_BUS               : INOUT  STD_LOGIC_VECTOR(7 DOWNTO 0));
end vending;
		
architecture struct of vending is

TYPE s_state is (s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17, s18, s19, s20);
signal state: s_state;

signal m1, m0, m2, m3: std_logic_vector (3 downto 0);
signal seg_data0, seg_data1, seg_data2, seg_data3: std_logic_vector (6 downto 0);
signal clkout: std_logic;
signal sLCD_RS: std_logic;
signal sLCD_E: std_logic;
signal sLCD_RW: std_logic;
signal sLCD_ON: std_logic;
signal sLCD_BLON: std_logic;
signal Hex_Display_Data: std_logic_vector((2*4)-1 DOWNTO 0);
signal chip: std_logic;
signal drink: std_logic;
signal st: std_logic_vector(8 downto 0);

component slowclk is
	port(clk: in std_logic;
		  clkout: out std_logic);
end component;

component LCD_Display is
port(reset, CLOCK_50       	: IN  STD_LOGIC;
       Hex_Display_Data       : IN    STD_LOGIC_VECTOR((2*4)-1 DOWNTO 0);
       LCD_RS, LCD_E          : OUT STD_LOGIC;
       LCD_RW                 : OUT   STD_LOGIC;
       LCD_ON                 : OUT STD_LOGIC;
       LCD_BLON               : OUT STD_LOGIC;
       DATA_BUS               : INOUT  STD_LOGIC_VECTOR(7 DOWNTO 0));
end component;

begin
stage1: slowclk port map(clk, clkout);
stage2: LCD_Display port map(reset, clk, Hex_Display_Data, sLCD_RS, sLCD_E, sLCD_RW, sLCD_ON, sLCD_BLON, DATA_BUS);

--*******************************************
--Hex Segments
seg0 <= NOT(seg_data0);
seg1 <= NOT(seg_data1);
seg2 <= NOT(seg_data2);
seg3 <= NOT(seg_data3);

--LCD Display
--Hex_Display_Data <= m1 & m0;	--change this
--*******************************************

--LCD Setup
LCD_E <= sLCD_E;
LCD_RS <= sLCD_RS;
LCD_RW <= sLCD_RW;
LCD_ON <= sLCD_ON;
LCD_BLON <= sLCD_BLON;

m2 <= "000" & st(8);
m1 <= st(7) & st(6) & st(5) & st(4); --MSB
m0 <= st(3) & st(2) & st(1) & st(0);  --LSB 7 seg display

process(clkout, reset_v)
begin
	
	--load case
	if(reset_v = '0') then
		if(clkout'event and clkout = '1') THEN
			--Hex_Display_Data <= "00000001"; means home screen
			--Hex_Display_Data <= "00000010"; means bought chips
			--Hex_Display_Data <= "00000100"; means bought drink
			--Hex_Display_Data <= "00001000"; means money rejected
			--Hex_Display_Data <= "00010000"; means not enough money
			case state is
				when s0 =>
					chip <= '0';  --0 cents
					drink <= '0';
					Hex_Display_Data <= "00000001";
					st <= "000000000";
					led1 <= "000000000";
					if(buy(0) = '1') then Hex_Display_Data <= "00010000"; state <= s0;
					elsif(buy(1) = '1') then Hex_Display_Data <= "00010000"; state <= s0;
					elsif(load_data(0) = '0') then state <= s1; 
					elsif(load_data(1) = '0') then state <= s2; 
					elsif(load_data(2) = '0') then state <= s5; 
					elsif(load_data(3) = '0') then state <= s20; 
					else state <= s0; end if;
				when s1 => 
					chip <= '0'; --5 cents
					drink <= '0';
					st <= "000000101";
					led1 <= "000000001";
					if(buy(0) = '1') then Hex_Display_Data <= "00010000"; state <= s1;
					elsif(buy(1) = '1') then Hex_Display_Data <= "00010000"; state <= s1;
					elsif(load_data(0) = '0') then state <= s2; 
					elsif(load_data(1) = '0') then state <= s3; 
					elsif(load_data(2) = '0') then state <= s6; 
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s1;
					else state <= s1; end if;
				when s2 => 
					chip <= '0'; --10 cents
					drink <= '0';	
					st <= "000010000";
					led1 <= "000000010";
					if(buy(0) = '1') then Hex_Display_Data <= "00010000"; state <= s2;
					elsif(buy(1) = '1') then Hex_Display_Data <= "00010000"; state <= s2;
					elsif(load_data(0) = '0') then state <= s3; 
					elsif(load_data(1) = '0') then state <= s4; 
					elsif(load_data(2) = '0') then state <= s7; 
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s2;
					else state <= s2; end if;
				when s3 => 
					chip <= '0'; --15 cents
					drink <= '0';
					st <= "000010101";
					led1 <= "000000011";
					if(buy(0) = '1') then Hex_Display_Data <= "00010000"; state <= s3;
					elsif(buy(1) = '1') then Hex_Display_Data <= "00010000"; state <= s3;
					elsif(load_data(0) = '0') then state <= s4;
					elsif(load_data(1) = '0') then state <= s5;
					elsif(load_data(2) = '0') then state <= s8;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s3;
					else state <= s3; end if;
				when s4 => 
					chip <= '0'; --20 cents
					drink <= '0';	
					st <= "000100000";
					led1 <= "000000100";	
					if(buy(0) = '1') then Hex_Display_Data <= "00010000"; state <= s4;
					elsif(buy(1) = '1') then Hex_Display_Data <= "00010000"; state <= s4;
					elsif(load_data(0) = '0') then state <= s5;
					elsif(load_data(1) = '0') then state <= s6;
					elsif(load_data(2) = '0') then state <= s9;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s4;
					else state <= s4; end if;
				when s5 => 
					chip <= '0'; --25 cents
					drink <= '0';
					st <= "000100101";
					led1 <= "000000101";
					if(buy(0) = '1') then Hex_Display_Data <= "00010000"; state <= s5;
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "0000";
					elsif(load_data(0) = '0') then state <= s6;
					elsif(load_data(1) = '0') then state <= s7;
					elsif(load_data(2) = '0') then state <= s10;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s5;
					else state <= s5; end if;
				when s6 =>	
					chip <= '0'; --30 cents
					drink <= '0';
					st <= "000110000";
					led1 <= "000000110";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "0000";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "0001";
					elsif(load_data(0) = '0') then state <= s7;
					elsif(load_data(1) = '0') then state <= s8;
					elsif(load_data(2) = '0') then state <= s11;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s6;
					else state <= s6; end if;
				when s7 =>	
					chip <= '0'; --35 cents
					drink <= '0';
					st <= "000110101";
					led1 <= "000000111";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "0001";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "0010";
					elsif(load_data(0) = '0') then state <= s8;
					elsif(load_data(1) = '0') then state <= s9;
					elsif(load_data(2) = '0') then state <= s12;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s7;
					else state <= s7; end if;
				when s8 =>	
					chip <= '0'; --40 cents
					drink <= '0';
					st <= "001000000";
					led1 <= "000001000";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "0010";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "0011";
					elsif(load_data(0) = '0') then state <= s9;
					elsif(load_data(1) = '0') then state <= s10;
					elsif(load_data(2) = '0') then state <= s13;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s8;
					else state <= s8; end if;
				when s9 =>	
					chip <= '0'; --45 cents
					drink <= '0';
					st <= "001000101";
					led1 <= "000001001";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "0011";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "0100";
					elsif(load_data(0) = '0') then state <= s10;
					elsif(load_data(1) = '0') then state <= s11;
					elsif(load_data(2) = '0') then state <= s14;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s9;
					else state <= s9; end if;
				when s10 =>	
					chip <= '0'; --50 cents
					drink <= '0';
					st <= "001010000";
					led1 <= "000001010";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "0100";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "0101";
					elsif(load_data(0) = '0') then state <= s11;
					elsif(load_data(1) = '0') then state <= s12;
					elsif(load_data(2) = '0') then state <= s15;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s10;
					else state <= s10; end if;
				when s11 =>	
					chip <= '0'; --55 cents
					drink <= '0';
					st <= "001010101";
					led1 <= "000001011";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "0101";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "0110";
					elsif(load_data(0) = '0') then state <= s12;
					elsif(load_data(1) = '0') then state <= s13;
					elsif(load_data(2) = '0') then state <= s16;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s11;
					else state <= s11; end if;
				when s12 =>	
					chip <= '0'; --60 cents
					drink <= '0';
					st <= "001100000";
					led1 <= "000001100";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "0110";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "0111";
					elsif(load_data(0) = '0') then state <= s13;
					elsif(load_data(1) = '0') then state <= s14;
					elsif(load_data(2) = '0') then state <= s17;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s12;
					else state <= s12; end if;
				when s13 =>	
					chip <= '0'; --65 cents
					drink <= '0';
					st <= "001100101";
					led1 <= "000001101";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "0111";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "1000";
					elsif(load_data(0) = '0') then state <= s14;
					elsif(load_data(1) = '0') then state <= s15;
					elsif(load_data(2) = '0') then state <= s18;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s13;
					else state <= s13; end if;
				when s14 =>	
					chip <= '0'; --70 cents
					drink <= '0';
					st <= "001110110";
					led1 <= "000001110";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "1000";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "1001";
					elsif(load_data(0) = '0') then state <= s15;
					elsif(load_data(1) = '0') then state <= s16;
					elsif(load_data(2) = '0') then state <= s19;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s14;
					else state <= s14; end if;
				when s15 =>	
					chip <= '0'; --75 cents
					drink <= '0';
					st <= "001110101";
					led1 <= "000001111";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "1001";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "1010";
					elsif(load_data(0) = '0') then state <= s16;
					elsif(load_data(1) = '0') then state <= s17;
					elsif(load_data(2) = '0') then state <= s20;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s15;
					else state <= s15; end if;
				when s16 =>	
					chip <= '0'; --80 cents
					drink <= '0';
					st <= "010000000";
					led1 <= "000010000";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "1010";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "1011";
					elsif(load_data(0) = '0') then state <= s17;
					elsif(load_data(1) = '0') then state <= s18;
					elsif(load_data(2) = '0') then Hex_Display_Data <= "00001000"; state <= s16;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s16;
					else state <= s16; end if;
				when s17 =>	
					chip <= '0'; --85 cents
					drink <= '0';
					st <= "010000101";
					led1 <= "000010001";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "1011";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "1100";
					elsif(load_data(0) = '0') then state <= s18;
					elsif(load_data(1) = '0') then state <= s19;
					elsif(load_data(2) = '0') then Hex_Display_Data <= "00001000"; state <= s17;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s17;
					else state <= s17; end if;
				when s18 =>	
					chip <= '0'; --90 cents
					drink <= '0';
					st <= "010010000";
					led1 <= "000010010";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "1100";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "1101";
					elsif(load_data(0) = '0') then state <= s19;
					elsif(load_data(1) = '0') then state <= s20;
					elsif(load_data(2) = '0') then Hex_Display_Data <= "00001000"; state <= s18;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s18;
					else state <= s18; end if;
				when s19 =>	
					chip <= '0'; --95 cents
					drink <= '0';
					st <= "010010101";
					led1 <= "000010011";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "1101";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "1110";
					elsif(load_data(0) = '0') then state <= s20;
					elsif(load_data(1) = '0') then Hex_Display_Data <= "00001000"; state <= s19;
					elsif(load_data(2) = '0') then Hex_Display_Data <= "00001000"; state <= s19;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s19;
					else state <= s19; end if;
				when s20 =>
					chip <= '0';  --1 dollar
					drink <= '0';
					st <= "100000000";
					led1 <= "000010100";
					if(buy(0) = '1') then Hex_Display_Data <= "00000010"; chip <= '1'; state <= s0; m3 <= "1110";
					elsif(buy(1) = '1') then Hex_Display_Data <= "00000100"; drink <= '1'; state <= s0; m3 <= "1111";
					elsif(load_data(0) = '0') then Hex_Display_Data <= "00001000"; state <= s20;
					elsif(load_data(1) = '0') then Hex_Display_Data <= "00001000"; state <= s20;
					elsif(load_data(2) = '0') then Hex_Display_Data <= "00001000"; state <= s20;
					elsif(load_data(3) = '0') then Hex_Display_Data <= "00001000"; state <= s20;
					else state <= s20; end if;
				end case;
			end if;
	else
		state <= s0;
		chip <= '0';
		drink <= '0';
		Hex_Display_Data <= "00000001";
		led1 <= "000000000";
		m3 <= "0000";
	end if;
	
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
end struct;

--slow clock 
Library ieee;
use ieee.std_logic_1164.all;
entity slowclk is
	port(clk: in std_logic; clkout: out std_logic);
end slowclk;

architecture ckt of slowclk is
begin 
	process(clk)
	variable cnt: integer range 0 to 25000000; -- clock speeds set here
	begin	
		if (clk'event and clk = '1') THEN
			if(cnt = 25000000) THEN					--same clock speed
				cnt:= 0;
				clkout <= '1';
			else
				cnt:= cnt + 1;
				clkout <= '0';
			end if;
		end if;
	end process;
end ckt;
	

---- 
LIBRARY IEEE;
USE  IEEE.STD_LOGIC_1164.all;
USE  IEEE.STD_LOGIC_ARITH.all;
USE  IEEE.STD_LOGIC_UNSIGNED.all;

ENTITY LCD_Display IS
-- Enter number of live Hex hardware data values to display
-- (do not count ASCII character constants)
   GENERIC(Num_Hex_Digits: Integer:= 2); 
-----------------------------------------------------------------------
-- LCD Displays 16 Characters on 2 lines
-- LCD_display string is an ASCII character string entered in hex for 
-- the two lines of the  LCD Display   (See ASCII to hex table below)
-- Edit LCD_Display_String entries above to modify display
-- Enter the ASCII character's 2 hex digit equivalent value
-- (see table below for ASCII hex values)
-- To display character assign ASCII value to LCD_display_string(x)
-- To skip a character use X"20" (ASCII space)
-- To dislay "live" hex values from hardware on LCD use the following: 
--   make array element for that character location X"0" & 4-bit field from Hex_Display_Data
--   state machine sees X"0" in high 4-bits & grabs the next lower 4-bits from Hex_Display_Data input
--   and performs 4-bit binary to ASCII conversion needed to print a hex digit
--   Num_Hex_Digits must be set to the count of hex data characters (ie. "00"s) in the display
--   Connect hardware bits to display to Hex_Display_Data input
-- To display less than 32 characters, terminate string with an entry of X"FE"
--  (fewer characters may slightly increase the LCD's data update rate)
------------------------------------------------------------------- 
--                        ASCII HEX TABLE
--  Hex                 Low Hex Digit
-- Value  0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
------\----------------------------------------------------------------
--H  2 |  SP  !   "   #   $   %   &   '   (   )   *   +   ,   -   .   /
--i  3 |  0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?
--g  4 |  @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O
--h  5 |  P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _
--   6 |  `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o
--   7 |  p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~ DEL
-----------------------------------------------------------------------
-- Example "A" is row 4 column 1, so hex value is X"41"
-- *see LCD Controller's Datasheet for other graphics characters available
--
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
SIGNAL   CHAR_COUNT                 : STD_LOGIC_VECTOR(4 DOWNTO 0);
SIGNAL   CLK_400HZ_Enable,LCD_RW_INT   : STD_LOGIC;
SIGNAL   Line1_chars, Line2_chars      : STD_LOGIC_VECTOR(127 DOWNTO 0);
BEGIN

LCD_ON      <= '1';
LCD_BLON    <= '1';

--LCD_display_string <= (
-- ASCII hex values for LCD Display
-- Enter Live Hex Data Values from hardware here
-- LCD DISPLAYS THE FOLLOWING:
------------------------------
--| Count=XX                  |
--| DE2                       |
------------------------------
-- Line 1& Hex_Display_Data(7 DOWNTO 4)
--   X"43",X"4F",X"44",X"45",X"20",X"52",
--   X"45", X"41", X"44", X"3A",
--   X"20",X"20",X"20",X"20",X"20",X"20",
-- Line 2
--   X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20",
--   X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20");

-- BIDIRECTIONAL TRI STATE LCD DATA BUS
   DATA_BUS <= DATA_BUS_VALUE WHEN LCD_RW_INT = '0' ELSE "ZZZZZZZZ";

-- get next character in display string
   Next_Char <= LCD_display_string(CONV_INTEGER(CHAR_COUNT));
   LCD_RW <= LCD_RW_INT;
	
			--Hex_Display_Data <= "00000001"; means home screen
			--Hex_Display_Data <= "00000010"; means bought chips
			--Hex_Display_Data <= "00000100"; means bought drink
			--Hex_Display_Data <= "00001000"; means money rejected
   
   PROCESS
   BEGIN
		IF Hex_Display_Data(0) = '1' then
			LCD_display_string <= (
			X"43",X"4F",X"4C",X"41",X"20",X"3D",
			X"20", X"24", X"2E", X"32",
			X"35",X"20",X"20",X"20",X"20",X"20",
			--Line2
			X"43",X"48",X"49",X"50",X"20",X"3D",X"20",X"24",
			X"2E",X"33",X"30",X"20",X"20",X"20",X"20",X"20");
		elsif Hex_Display_Data(1) = '1' then
			LCD_display_string <= (
			X"43",X"48",X"49",X"50",X"20",X"50",
			X"55", X"52", X"43", X"48",
			X"41",X"53",X"46",X"44",X"20",X"20",
			--Line2
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20",
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20");
		elsif Hex_Display_Data(2) = '1' then
			LCD_display_string <= (
			X"43",X"4F",X"4C",X"41",X"20",X"50",
			X"55", X"52", X"43", X"48",
			X"41",X"53",X"46",X"44",X"20",X"20",
			--Line2
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20",
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20");		
		elsif Hex_Display_Data(3) = '1' then
			LCD_display_string <= (
			X"4D",X"4F",X"4E",X"45",X"59",X"20",
			X"52", X"45", X"4A", X"45",
			X"43",X"54",X"45",X"44",X"20",X"20",
			--Line2
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20",
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20");
		elsif Hex_Display_Data(4) = '1' then
			LCD_display_string <= (
			X"4E",X"4F",X"54",X"20",X"45",X"4E",
			X"4F", X"55", X"47", X"48",
			X"20",X"20",X"20",X"20",X"20",X"20",
			--Line2
			X"4D",X"4F",X"4E",X"45",X"59",X"20",X"20",X"20",
			X"20",X"20",X"20",X"20",X"20",X"20",X"20",X"20");
		else	
			LCD_display_string <= (
			X"4E",X"41",X"20",X"20",X"20",X"20",
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