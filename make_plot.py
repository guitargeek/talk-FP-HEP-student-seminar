import uproot
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

df = uproot.open("data.root")["tree"].pandas.df()

def get_mass(leptons):
    leps = leptons.sort_values("pt")[-2:]
    pt_prod  = leps["pt"].prod()
    eta_diff = leps["eta"].diff().iloc[1]
    phi_diff = leps["phi"].diff().iloc[1]
    return np.sqrt(2*pt_prod*(np.cosh(eta_diff)-np.cos(phi_diff)))

mass = df.groupby("entry").apply(get_mass).values

plt.figure()
plt.hist(mass, bins=50, histtype='step')
plt.xlabel("dilepton mass [GeV]")
plt.savefig("dilepton_mass.png")
