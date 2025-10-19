def b(txt):
   while txt.find(" ") != -1:
      txt = txt.upper(txt.find(" "))
   txt = txt.replace(" ", "")
   print(txt)

b("To je proměnná v Pythonu")