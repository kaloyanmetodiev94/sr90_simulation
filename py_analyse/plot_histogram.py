import matplotlib.pyplot as plt
import numpy as np
import csv

def read_csv(filename):
	f=open(filename,'r')
	reader=csv.reader(f)
	data=next(reader)

	while data[0][0]=='#':
		data=next(reader)

	energy_list=[]
	pdg_list=[]
	energy_list.append(float(data[1]))
	pdg_list.append(float(data[2]))
	for r in reader:
		energy_list.append(float(r[1]))
		pdg_list.append(float(r[2]))
		data=next(reader)

	return energy_list,pdg_list
energy,pdg=read_csv('../build/hits_0_nt_TrackerHitsCollection.csv')
plt.hist(energy,bins=40)
plt.title('PDG: '+str(set(pdg)))
plt.xlabel('Energy (MeV)')
plt.show()
