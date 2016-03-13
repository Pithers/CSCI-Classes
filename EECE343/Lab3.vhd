--8bit adder

Library ieee;
use ieee.std_logic_1164.all;

entity bit8adder is
port (cin: in std_logic; x, y: in std_logic_vector (7 downto 0);
		seg0, seg1, seg2: out std_logic_vector (6 downto 0));
		end bit8adder;
		
architecture struct of bit8adder is
signal cout : std_logic; --outputs from the adders
signal s: std_logic_vector (7 downto 0);
signal m2, m1, m0: std_logic_vector (3 downto 0);
signal seg_data0, seg_data1, seg_data2: std_logic_vector (6 downto 0);
signal g: std_logic_vector (6 downto 0); -- cin(s) for other single bit adders

component fulladder is -- for multiple instantiations
port (cin, a, b : in std_logic; s, cout: out std_logic);
end component;

begin
stage1: fulladder port map (cin, x(0), y(0), s(0), g(0));
stage2: fulladder port map (g(0), x(1), y(1), s(1), g(1));
stage3: fulladder port map (g(1), x(2), y(2), s(2), g(2));
stage4: fulladder port map (g(2), x(3), y(3), s(3), g(3));
stage5: fulladder port map (g(3), x(4), y(4), s(4), g(4));
stage6: fulladder port map (g(4), x(5), y(5), s(5), g(5));
stage7: fulladder port map (g(5), x(6), y(6), s(6), g(6));
stage8: fulladder port map (g(6), x(7), y(7), s(7), cout);
m2 <= "000" & cout;  --carry out
m1 <= s(7) & s(6) & s(5) & s(4); --MSB
m0 <= s(3) & s(2) & s(1) & s(0);  --LSB 7 seg display

process(m2, m1, m0)
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
	when "1100" => seg_data0 <= "1111001";
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
	when "1100" => seg_data1 <= "1111001";
	when "1101" => seg_data1 <= "1011110";
	when "1110" => seg_data1 <= "1111001";
	when others => seg_data1 <= "1110001";
end case;
case m2 is
	when "0000" => seg_data2 <= "0111111";
	when "0001" => seg_data2 <= "0000110";
	when others => seg_data2 <= "0111111";
end case;
end process;

seg0 <= NOT(seg_data0);
seg1 <= NOT(seg_data1);
seg2 <= NOT(seg_data2);
end struct;

library ieee;
use ieee.std_logic_1164.all;
entity fulladder is
port (cin, a, b: in std_logic; s, cout: out std_logic);
end fulladder;

architecture ckt of fulladder is
begin
s<= (a xor b) xor cin;
cout <= (a and b) or (a and cin) or (b and cin);
end ckt;




