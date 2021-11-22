import sys
import os
import pandas
import numpy
import matplotlib.pyplot as plot
import math

class readFile:
    # Read CSV file 
    def csv(fileName, path):
        return pandas.read_csv(path+"/"+fileName, index_col=False, squeeze=True, names=['time', 'volts'])        
    # Read Trn file.reaXT file
    def txt(fileName, path):
        with open(path+"/"+fileName, "r") as file:
            return file.readlines()

# Write to file
def writeFile(fileName, path, samplesPerBit, binstring):
    with open(path+"/"+fileName, "w") as file:
        file.write(getFrq(fileName)+"\n")
        file.write(str(samplesPerBit)+"\n")
        file.write(binstring+"\n")

# Get frequency from file name
def getFrq(fileName):
    cod = getFrqCode(fileName)
    if cod == "1":
        return "10 Hz"
    elif cod == "02":
        return "30 Hz"
    return "50 Hz"

# Convert to binary string
def wordSended():
    word = "lesc" #TODO: change to receive word by parameter
    bin_word = bytearray(word, 'utf-8')
    byte_list = []
    for byte in bin_word:
        byte_list.append(bin(byte))
    palavra = ""
    for bit_word in byte_list:
        if int(bit_word[0])==0:
            palavra = palavra+"0"
        elif int(bit_word[0])==1:
            palavra = palavra+"1"
        for i in range(2, 9):
            if int(bit_word[i])==0:
                palavra = palavra+"0"
            elif int(bit_word[i])==1:
                palavra = palavra+"1"
    return palavra

# Get frequency code from file name
def getFrqCode(fileName):
    fileName = fileName.split("_")
    fileName = fileName[1].split("s")
    return fileName[0]

# Get how many samples measure per bit
def getSamplesPerData(fileName, dtData):
    frq = [10,30,50]
    dt =[]
    for aux in frq:
        dt.append(1/aux)
    frqcode = getFrqCode(fileName)
    if frqcode == "1":
        return dt[0]/dtData
    elif frqcode == "02":
        return dt[1]/dtData
    return dt[2]/dtData

# Convert data captured in volts to a binary string
def stringBinaria(data, limiteAlto, limiteBaixo):
    binlist = ""
    for b in data:
        if b >= limiteAlto:
            binlist += "1"
        if b <= limiteBaixo:
            binlist += "0"
    return binlist

# Duplicate the bits from a biniry string
def dobraString(palavra):
    aux = ""
    for i in range(0,len(palavra)):
        aux += palavra[i]
        aux += palavra[i]
    return aux

# Retunes position of the first "0" in binary string
def getBeginstr(stringInteira):
    begin = 0
    while stringInteira[begin] != "0":
        begin += 1
    return int(begin)

# Retunes position of end in binary string
def getEndstr(stringInteira):
    for i in range(len(stringInteira)):
        if stringInteira[i] == "0":
            last = i
    return int(last + 4)

# Create the dicionary
def createDicBytes():
    d = ['2cm','8cm','12cm','16cm']
    frq = ['10 Hz','50 Hz']
    atrib = ['tempo_inicio', 'tempo_fim', 'bits_recebidos', 'bits_erros', 'BER', 'throughput', 'throughput']
    dicionario = {}
    for item in d:
        dicionario[item] = {}
        for f in frq:
            dicionario[item][f] = {}
            for a in atrib:
                dicionario[item][f][a] = 0.0
    return dicionario

# Get distance from file name
def getDistance(fileName):
    fileName  = fileName.split("0")
    return fileName[0]

# Get levenstein distance
def levenshtein_ratio_and_distance(s, t, ratio_calc = False):
    rows = len(s)+1
    cols = len(t)+1
    distance = numpy.zeros((rows,cols),dtype = int)
    for i in range(1, rows):
        for k in range(1,cols):
            distance[i][0] = i
            distance[0][k] = k
    for col in range(1, cols):
        for row in range(1, rows):
            if s[row-1] == t[col-1]:
                cost = 0
            else:
                if ratio_calc == True:
                    cost = 2
                else:
                    cost = 1
            distance[row][col] = min(distance[row-1][col] + 1,     
                                 distance[row][col-1] + 1,         
                                 distance[row-1][col-1] + cost)    
    if ratio_calc == True:
        Ratio = ((len(s)+len(t)) - distance[row][col]) / (len(s)+len(t))
        return Ratio
    else:
        return format(distance[row][col])
    
####### begin of the script ###########    
wordBin = wordSended()
dir = "filtrado"
dirconverted = "binString"
files = os.listdir(dir)
for file in files:
    vector = readFile.csv(file, dir)
    dt_data = vector['time'][1] - vector['time'][0]
    samples_per_data = getSamplesPerData(file, dt_data)
    maximo = max(vector['volts'])
    minimo = min(vector['volts'])
    media = (maximo + minimo)/2
    treshold_high = media + (media*0.2)
    treshold_low = media - (media*0.2)
    rawstring = stringBinaria(vector['volts'], treshold_high, treshold_low)
    writeFile(file, dirconverted, samples_per_data, rawstring)
    # plot.plot(vector['volts'])
    # plot.show()

files = os.listdir(dirconverted)
wordDoble = dobraString(wordBin)
lenWordBin = len(wordBin)
bytestransmitidos = createDicBytes()
for file in files:
    time = []
    fileContend = readFile.txt(file, dirconverted)
    vector = readFile.csv(file, dir)
    if fileContend[1].strip("\n") == "2.0":
        for i in vector['time']:
            time.append(i)
        aux = fileContend[2]
        comeco = getBeginstr(aux)
        fim = getEndstr(aux)
        tamanho = fim - comeco
        if fim >= len(time):
            bytestransmitidos[getDistance(file)][fileContend[0].strip("\n")]['tempo_fim'] = float(vector['time'][-1:])
        else:
            bytestransmitidos[getDistance(file)][fileContend[0].strip("\n")]['tempo_fim'] = float(vector['time'][fim])
        bytestransmitidos[getDistance(file)][fileContend[0].strip("\n")]['tempo_inicio'] = float(vector['time'][comeco])
        bytestransmitidos[getDistance(file)][fileContend[0].strip("\n")]['bits_recebidos'] += tamanho/2
        aux = aux[comeco:fim]
        corretas = aux.count(wordDoble)
        aux = aux.replace(wordDoble,"")
        stringsErros = math.ceil(len(aux)/(lenWordBin*2))
        for i in range(stringsErros):
            if len(aux) < len(wordDoble):
                bytestransmitidos[getDistance(file)][fileContend[0].strip("\n")]['bits_erros'] += int(levenshtein_ratio_and_distance(aux, wordDoble))/2
            else:
                bytestransmitidos[getDistance(file)][fileContend[0].strip("\n")]['bits_erros'] += int(levenshtein_ratio_and_distance(aux[:len(wordDoble)], wordDoble))/2
                aux = aux[len(wordDoble):]
for dist in bytestransmitidos:
    for frq in bytestransmitidos[dist]:
        bytestransmitidos[dist][frq]['BER'] = bytestransmitidos[dist][frq]['bits_erros'] / bytestransmitidos[dist][frq]['bits_recebidos']
        bytestransmitidos[dist][frq]['throughput'] = (bytestransmitidos[dist][frq]['bits_recebidos'] - bytestransmitidos[dist][frq]['bits_erros']) / (bytestransmitidos[dist][frq]['tempo_fim'] - bytestransmitidos[dist][frq]['tempo_inicio'])
print(bytestransmitidos)
vazao_10 = []
vazao_50 = []
ber_10 = []
ber_50 = []
dist = []
for dst in bytestransmitidos:
    vazao_10.append(bytestransmitidos[dst]['10 Hz']['throughput'])
    vazao_50.append(bytestransmitidos[dst]['50 Hz']['throughput'])
    ber_10.append(bytestransmitidos[dst]['10 Hz']['BER'])
    ber_50.append(bytestransmitidos[dst]['50 Hz']['BER'])
    dist.append(dst)
print("Throughput 10 Hz: " + str(vazao_10))
print("Throughput 50 Hz: " + str(vazao_50))
print("BER 10 Hz: " + str(ber_10))
print("BER 50 Hz: " + str(ber_50))
print("distancia: " + str(dist))
with open("dados.txt", "w") as file:
    file.write("Throughput 10 Hz: " + str(vazao_10))
    file.write("Throughput 50 Hz: " + str(vazao_50))
    file.write("BER 10 Hz: " + str(ber_10))
    file.write("BER 50 Hz: " + str(ber_50))
    file.write("distancia: " + str(dist))
    file.write(str(bytestransmitidos))
with open("vazao_10.txt","w") as file:
    for i in vazao_10:
        file.write(str(i))
with open("vazao_50.txt","w") as file:
    for i in vazao_50:
        file.write(str(i))
with open("ber_10.txt","w") as file:
    for i in ber_10:
        file.write(str(i))
with open("ber_50.txt","w") as file:
    for i in ber_50:
        file.write(str(i))
with open("distancia.txt","w") as file:
    for i in dist:
        file.write(str(i))