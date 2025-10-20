'''
Konstanty v Pythonu

Konstanta je vlastně speciální typ proměnné, jejíž hodnota nemůže být změněna.
V Pythonu jsou konstanty obvykle deklarovány a přiřazovány v modulu, který bývá importován do souboru aplikace.
Konstanty jsou pojmenovány velkými písmeny a jednotlivá slova jsou oddělována podtržítky.
'''

EARTH_GRAVITY = 9.807 #ms
MOON_GRAVITY = 1.622 #ms
SPEED_OF_LIGHT = 299792458 #ms
SPEED_OF_SOUND = 343 #ms
''' 
Úkol:
1. Doplňte správně hodnoty uvedených konstant.
2. Doplňte physics.py o několik výpočtových funkcí (opatřené docstrings), v nichž využijete minimálně všechny výše uvedené konstanty.
Samozřejmě můžete své řešení rozšířit i o jiné fyzikální konstanty.
3. Vytvořte z tohoto souboru samostatný modul v Pythonu podle návodu, který si sami najdete na internetu.      
4. Vytvořte vlastní aplikaci myapp.py, do níž tento modul importujte. Demonstrujte v ní na jednoduchých příkladech využití vámi
připravených funkcí.  
'''

def weightOnMoon(w):
    """calculates your weight if you lived on the MOON.
    Input in Kg.
    Output in Kg."""
    return w/EARTH_GRAVITY*MOON_GRAVITY

def storm(dif) :
    """calculates how far is the storm based on the delay between light of sound of lighting. 
    Input in seconds.
    Output in meters."""
    return int(SPEED_OF_SOUND * dif)

def daBOOM(far):
    """Based on how far the explosion happened, calculates when the sound wave will hit.
    Input distance in Km.
    Output in seconds.
    """
    return far*1000 / SPEED_OF_SOUND

def lightYearDistance ():
    """calculates how manz km does light past in 1 year.
    No input.
    Output in Km."""
    return int((SPEED_OF_LIGHT * 365 * 24 * 3600) / 1000)
