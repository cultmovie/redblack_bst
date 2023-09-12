TARGET := test
SRC := redblack_bst.c redblack_bst.h redblack_draw.c redblack_draw.h test.c

CFLAG := -g3 -O2 -Wall -std=c99
LDFLAG := -lgvc -lcgraph

$(TARGET) : $(SRC)
	gcc $(CFLAG) $(SHARED) $^ -o $@ $(LDFLAG)

clean :
	rm -f $(TARGET)
