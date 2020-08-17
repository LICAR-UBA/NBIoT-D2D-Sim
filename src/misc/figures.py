import csv
from matplotlib import pyplot as plt
filename1 = 'urban-spaces.csv'
#filename2 = 'suburban.csv'


with open(filename1) as f:
    reader = csv.reader(f)
    header_row = next(reader)
    edrs = []
    for row in reader:
        if row[1]=='':
            continue
        edr = row[2]
        edrs.append(edr)  
    
    #Plot Data
    fig = plt.figure(dpi = 128, figsize = (10,6))
    plt.plot(edrs, c = 'red') #Line 1
    #Format Plot
    plt.title("Primeros edrs", fontsize = 24)
    plt.xlabel('',fontsize = 16)
    plt.ylabel("EDR", fontsize = 16)
    plt.tick_params(axis = 'both', which = 'major' , labelsize = 16)
    plt.show()
