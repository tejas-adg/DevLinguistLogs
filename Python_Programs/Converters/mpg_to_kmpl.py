# Defining constants, sourced from the Windows Calculator lol
mile_to_km = 1.609344
km_to_mile = 0.621371

liter_to_gal = 0.264172
gal_to_liter = 3.785412

# As this file only converts two different units, we can accept the input unit as well
inp = input("Enter the mileage followed by the unit (mpg/kmpl) :- ")

# To separate the value from the unit, we just see where the numbers end
# and where the first letter is from there
for pos, letter in enumerate(inp):
	if ord(letter) not in range(48, 58):
		break

for letter in inp[(pos + 1):]:
	if ord(letter) in range(65, 91) or ord(letter) in range(97, 123):
		break

# Here, we just check the first letter as that is sufficient enough
# to differentiate b/w "mpg" and "kmpl"
if letter.lower()  == 'm':
	print(f"{inp[:pos]} mpg to kmpl is: {(int(inp[:pos]) * (mile_to_km / gal_to_liter))}")
elif letter.lower() == 'k':
	print(f"{inp[:pos]} kmpl to mpg is: {(int(inp[:pos]) * (km_to_mile / liter_to_gal))}")