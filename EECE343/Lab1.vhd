LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY led_circuit IS
PORT (SW : IN STD_LOGIC_VECTOR(17 DOWNTO 0);
		LEDR : OUT STD_LOGIC_VECTOR(17 DOWNTO 0));
END led_circuit;

ARCHITECTURE Behavior OF led_circuit IS
BEGIN
	LEDR <= SW;
END Behavior;
