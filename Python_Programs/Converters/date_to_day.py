inp = input("Enter the date in MM/DD/YYYY format :- ")
try:
    import datetime, calendar
    print(calendar.day_name[datetime.datetime.strptime(inp, "%m/%d/%Y").weekday()])
except ValueError as ex:
    print(f"The time data: '{inp}' does not match the format: 'MM/DD/YYYY'")
except:
    print("An unknown error has ocurred, please raise an issue")