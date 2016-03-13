--EECE 343 Lab 2
--John-Mark Mamalakis
--Brandon Smith

Library ieee;
use ieee.std_logic_1164.all;

entity lab2segd IS
PORT(s: in std_logic_vector (2 downto 0); 
	hexZ: out std_logic_vector (0 to 6));
	end lab2segd;
	
architecture ckt of lab2segd is
begin
hexZ(0) <= NOT((s(0) AND ((NOT s(1)) OR (NOT s(2)))) OR (NOT s(0) AND s(1) AND (NOT s(2))));
hexZ(1) <= NOT((NOT s(0) AND (NOT s(1)) AND s(2)) OR (s(0) AND (s(1) OR (NOT s(2)))));
hexZ(2) <= NOT((NOT s(0) AND (NOT s(1)) AND s(2)) OR (s(0) AND (s(1) OR (NOT s(2)))));
hexZ(3) <= NOT((s(0) XOR s(1)) OR (s(0) AND s(1) AND (NOT s(2))));
hexZ(4) <= NOT((s(0) XOR s(1)) OR (NOT s(0) AND NOT s(1) AND s(2)));
hexZ(5) <= NOT(s(2) OR (s(0) XOR s(1)));
hexZ(6) <= NOT((NOT(s(0)) AND (NOT s(1)) AND s(2)) OR (NOT s(0) AND (NOT s(2)) AND s(1)) OR (s(0) AND s(1)));
end ckt;
