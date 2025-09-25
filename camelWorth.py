from colorama import Fore, Style
import time

def camelGreet():
    """This function prints what this application does."""
    print(Fore.YELLOW + 'CAMEL WORTH CALCULATOR')
    print(Fore.CYAN + "Find out how many camels you are worth!")
    print(Fore.WHITE + "----------------------------------------------" + Style.RESET_ALL)

def printErr():
    """This function prints error message."""
    print(Fore.RED + "Wrong input, try again." + Style.RESET_ALL)

hairColor = ""
hairLen = ""
eyecolor = ""
body = ""
beard = ""
age = 0
sex = ""
height = 0

def calculate (sex, be, bo, ec, hl, hc, h, a):
    """This function calculates the camel worth based on input data."""
    points = 0
    if ec == "blue":
        points += 5
    elif ec == "green":
        points += 10
    elif ec == "mixed":
        points += 15
    else:
        points += 2

    if be == "none":
        points += 10
    elif be == "small":
        points += 12
    elif be == "medium":
        points += 15
    elif be == "full":
        points += 10

    if bo == "slim":
        points += 10
    elif bo == "fat":
        points += 6
    else:
        points += 20

    if hl == "bald":
        points += 5
    elif hl == "long":
        points += 3
    else:
        points += 10
    
    if hc == "brown":
        points +=8
    elif hc == "black":
        points +=10
    elif hc == "blond":
        points += 6
    else:
        points += 2

    if h <= 110:
        points += 2
    elif h <= 140:
        points +=5
    elif h<=160:
        points +=15
    elif h <= 180:
        points +=25
    elif h<= 190:
        points +=32
    elif h <= 209:
        points+=28
    elif h >= 210:
        points +=20
        
    if a <= 10:
        points += 8
    elif a <= 15:
        points += 10
    elif a <= 20:
        points += 20
    elif a <= 30:
        points += 25
    elif a <= 40:
        points += 15
    elif a <= 50:
        points += 10
    elif a <= 60:
        points += 5
    else:  
        points += 2
    
    if sex != "male":
        points == points/2
    return points

def getData():
    """This function gets the data from user."""
    beardOpt = ["none", "small", "medium", "full"]
    bodyOpt = ["slim", "fat", "muscle", "ripped"]
    eyecolorOpt = ["blue", "brown", "green", "mixed"]    
    hairLenOpt = ["bald", "short", "medium", "long"]
    hairColorOpt = ["brown", "black", "blond", "other"]
    
    while True:
        try:
            age = int(input("Enter your age: "))
            if 1 < age < 100:
                break
            else:
                printErr()
        except ValueError:
            printErr()

    while True:
        sex = input("male or female? ").lower()
        if sex in ["male", "female"]:
            break
        else:
            printErr()
    
    if sex == "male":
        while True:
            beard = input(f"beard {beardOpt}: ").lower()
            if beard in beardOpt:
                break
            else:
                printErr()

    while True:
        body = input(f"body {bodyOpt}: ").lower()
        if body in bodyOpt:
            break
        else:
            printErr()

    while True:
        eyecolor = input(f"eye color {eyecolorOpt}: ").lower()
        if eyecolor in eyecolorOpt:
            break
        else:
            printErr()

    while True:
        hairLen = input(f"hair length {hairLenOpt}: ").lower()
        if hairLen in hairLenOpt:
            break
        else:
            printErr()

    if hairLen != "bald":
        while True:
            hairColor = input(f"hair color {hairColorOpt}: ").lower()
            if hairColor in hairColorOpt:
                break
            else:
                printErr()

    while True:
        try:
            height = int(input("Enter your height: "))
            if 50 < height < 280:
                break
            else:
                printErr()
        except ValueError:
            printErr()

    print(Fore.GREEN + "\nData collected successfully!")
    print(Fore.BLUE + "Calculating", end="")
    for i in range(0, 20):
        print(".", end="")
        time.sleep(0.05)
    print("")
    camels = calculate(sex, beard, body, eyecolor, hairLen, hairColor, height, age)
    printResults(camels)


    
def printResults(x):
    """This function prints the results."""
    print(Fore.YELLOW + f"You are worth {x} camels.")

camelGreet()
getData()
