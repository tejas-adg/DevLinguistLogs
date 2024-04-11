# Aaryan Mehra
#Computer Arch Project 1
R_type = { 
    # for R type instructions
      "100000"  : "add",
      "100001"  : "addu",
      "100100"  : "and",
      "001000"  : "jr",
      "100111"  : "nor",
      "100101"  : "or",
      "101010"  : "slt",
      "101011"  : "sltu",
      "000000"  : "sll",
      "000010"  : "srl",
      "100010"  : "sub",
      "100011"  : "subu"
    }

I_type = {
    # for I type instructions
    "001000"  : "addi",
    "001001"  : "addiu",
    "001100"  : "andi",
    "000100"  : "beq",
    "000101"  : "bne",
    "100100"  : "lbu",
    "100101"  : "lhu",
    "110000"  : "ll",
    "001111"  : "lui",
    "100011"  : "lw",
    "001101"  : "ori",
    "001010"  : "slti",
    "001011"  : "sltiu",
    "101000"  : "sb",
    "111000"  : "sc",
    "101001"  : "sh",
    "101011"  : "sw"
    }

registers = {
    # binary values corresponding to all the registers 

      "00000"  : "$zero",
      "00001"  : "$at",
      "00010"  : "$v0",
      "00011"  : "$v1",

      "00100"  : "$a0",
      "00101"  : "$a1",
      "00110"  : "$a2",
      "00111"  : "$a3",

      "01000"  : "$t0",
      "01001"  : "$t1",
      "01010"  : "$t2",
      "01011"  : "$t3",
      "01100"  : "$t4",
      "01101"  : "$t5",
      "01110"  : "$t6",
      "01111"  : "$t7",
    
      "10000"  : "$s0",
      "10001"  : "$s1",
      "10010"  : "$s2",
      "10011"  : "$s3",
      "10100"  : "$s4",
      "10101"  : "$s5",
      "10110"  : "$s6",
      "10111"  : "$s7",

      "11000"  : "$t8",
      "11001"  : "$t9",

      "11010"  : "$k0",
      "11011"  : "$k1",

      "11100"  : "$gp",
      "11101"  : "$sp",
      "11110"  : "$fp",
      "11111"  : "$ra"
    }

# reading the data from the file
def ReadingData (Data):
     access = open(Data)
     val = access.readlines()
     val = [int(i[:-1], 16) for i in val]
     return val


 #checking for the op code 
def checkingOP_code (val):
    #values form 0 to 6
    #for R type
     if val[:6] == "000000":
         return False
     # else for I type
     else:
         return True


#getting 32 bits
def x32(x):
    return  '0'*(32-len(bin(x)[2:]))+bin(x)[2:]

def main(m):
    count = 0
    conditional_statement_count = -1
    position = ''
    disassemble = []
    if_exists = any([I_type.get(i[:6], "none") in ['bne', 'beq'] for i in m])
    if if_exists:
        disassemble.append("Addr_0000:")
    for i in m:
        if ((count == conditional_statement_count) and (if_exists)):
            disassemble.append(position)
        if checkingOP_code(i):
            if I_type[i[:6]] in ['addi','addu', 'slti','sltiu','andi','ori']:
                disassemble.append("\t" + I_type[i[:6]] + "\t" + registers[i[11:16]] + "," + registers[i[6:11]] + ',' + str(int(i[16:32], 2)))

            elif I_type[i[:6]] in ['lbu','lhu','sb','sw','sh','sc']:
                disassemble.append("\t" + I_type[i[:6]] + "\t" + registers[i[11:16]] + "," + str(int(i[16:32], 2)) + '(' + registers[i[6:11]] + ')')

            elif I_type[i[:6]] in ["beq", "bne"]:
                if ((count + 1) + int(i[16:32], 2)) < len(m):
                    disassemble.append("\t" + I_type[i[:6]] + "\t" + registers[i[6:11]] + "," + registers[i[11:16]] + ",Addr_" + str(count * 4))
                    conditional_statement_count = (count + 1) + int(i[16:32], 2)
                    position = "Addr_" + str(count * 4) + ":";
                else:
                    disassemble.append("\t" + I_type[i[:6]] + "\t" + registers[i[6:11]] + "," + registers[i[11:16]] + ",Addr_0000")
            elif I_type[i[:6]] == 'lw':
                disassemble.append("\t" + I_type[i[:6]] + "\t" + registers[i[11:16]] + "," + str(int(i[16:32], 2)) + '(' + registers[i[6:11]] + ')')
                count -= 1
                conditional_statement_count -= 1


        else:
            if R_type[i[26:32]] in ["add", "addu", "sub", "subu", "and", "or", "nor", "slt", "sltu"]:
                disassemble.append("\t" + R_type[i[26:32]] + "\t" + registers[i[16:21]] + "," + registers[i[6:11]] + ',' + registers[i[11:16]])
                

            elif R_type[i[26:32]] in ["sll", "srl"]:
                disassemble.append("\t" + R_type[i[26:32]] + "\t" + registers[i[16:21]] + "," + registers[i[11:16]] + ',' + str(int(i[21:26], 2)))
        count += 1
    disassemble = [i + '\n' for i in disassemble]
    f = open("output.txt", 'w')
    f.writelines(disassemble)
    f.close()

ret_val = ReadingData(r"D:\tejas\Documents\GitHub\Code_of_Codswallop\Python_Programs\MIPS_Dissassembler\test_case1.obj")
ret_val = [x32(i) for i in ret_val]

import pprint

pprint.pprint(ret_val);

main(ret_val)