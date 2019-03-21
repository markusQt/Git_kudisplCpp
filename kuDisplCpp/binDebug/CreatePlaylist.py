#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Diese Skript schreibt eine Playlist für das Programm KundendisplayCpp"""

import os

mediaPfad=''
listeBilder=[]
listeFilme=[]

def getAllMedia():
    globals()["mediaPfad"] = os.getcwd()+"/assets/"
    dateiListe = os.listdir(mediaPfad)
    for datei in dateiListe:
        dateiTyp = datei[datei.rfind("."):len(datei)]
        print ("Typ: " , dateiTyp)
        if dateiTyp == ".png" or dateiTyp == ".jpg" or dateiTyp == ".jpeg" :
            print("Ein Bild: " , str(datei))
            globals()["listeBilder"].append(str(datei))
        elif dateiTyp == ".mp4" or dateiTyp == ".ogg":
            print ("Ein Film :" ,str(datei))
            globals()["listeFilme"].append(str(datei))

def writePlaylist():
    theFile = open(globals()["mediaPfad"]+"Playlist.txt","w")
    if len(globals()["listeBilder"])>0:
         for n in range(0,len(globals()["listeBilder"])):
            print(str(globals()["listeBilder"][n])+"\n")
            theFile.write("Pic@"+str(globals()["listeBilder"][n])+"\n")
    if len(globals()["listeFilme"])>0:
         for n in range(0,len(globals()["listeFilme"])):
            theFile.write("Mov@"+str(globals()["listeFilme"][n])+"\n")
    theFile.close()
    
def main():
    getAllMedia()
    writePlaylist()


if (__name__ == '__main__'):
    main()
