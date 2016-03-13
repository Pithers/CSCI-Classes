--Brandon Smith, John Mark, Counter program
Library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity counter is
port (clk, enable, load, up_down: in std_logic;
		load_data: in std_logic_vector (7 downto 0);
		seg0, seg1: out std_logic_vector (6 downto 0);
		led1: out std_logic_vector (7 downto 0));
end counter;
		
architecture struct of counter is
signal s: std_logic_vector (7 downto 0);
signal m1, m0: std_logic_vector (3 downto 0);
signal seg_data0, seg_data1: std_logic_vector (6 downto 0);
signal clkout: std_logic;

component slowclk is
	port(clk: in std_logic;
		  clkout: out std_logic);
end component;

begin
stage1: slowclk port map(clk, clkout);

m1 <= s(7) & s(6) & s(5) & s(4); --MSB
m0 <= s(3) & s(2) & s(1) & s(0);  --LSB 7 seg display

led1 <= s;

process(clkout, enable, load, up_down)
begin

	--deals with clkout, enable, and up_down
	if(clkout'event and clkout = '1') THEN
		if(enable = '1' and up_down = '1') THEN
			if(s = "11111111") THEN
				s <= "00000000";
			else
				s <= s+'1';
			end if;
		elsif (enable = '1' and up_down = '0') THEN
			if(s = "00000000") THEN
				s <= "11111111";
			else
				s <= s-'1';
			end if;
		END IF;
	END IF;
	
	--load case
	if(load = '1') THEN
		s<= load_data;
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
end process;

seg0 <= NOT(seg_data0);
seg1 <= NOT(seg_data1);
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
	variable cnt: integer range 0 to 12500000; -- clock speeds set here
	begin	
		if (clk'event and clk = '1') THEN
			if(cnt = 12500000) THEN					--same clock speed
				cnt:= 0;
				clkout <= '1';
			else
				cnt:= cnt + 1;
				clkout <= '0';
			end if;
		end if;
	end process;
end ckt;
	
		
