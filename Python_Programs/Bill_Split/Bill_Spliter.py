def interpret_Yes_No(strinp:str) -> bool:
	return ((strinp.lower() == "y") or ("yes" in strinp.lower()))

people = ["Nikhil", "Tejas", "Dylan", "Supran"]

do_loop = True
while do_loop:
	do_loop = interpret_Yes_No(input("Do you wish to continue? (Y/N): "))
