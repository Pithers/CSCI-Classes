all: main std hist

main: bsmith_p3_process.c
	gcc bsmith_p3_process.c -o test -lm -lrt -pthread 

std: bsmith_p3_std.c
	gcc bsmith_p3_std.c -o std -lm -pthread

hist: bsmith_p3_hist.c
	gcc bsmith_p3_hist.c -o hist -lm -pthread

clean:
	rm test
	rm hist
	rm std
