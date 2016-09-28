import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from random import randint

import sys
if sys.version_info[0] < 3:
    from Tkinter import *
    from Tkinter import ttk
    from Tkinter import messagebox

else:
    from tkinter import *
    from tkinter import ttk
    from tkinter import messagebox


# plotting function: clear current, plot & redraw
def plot(x, y):
    plt.clf()
    plt.plot(x,y)
    # just plt.draw() won't do it here, strangely
    plt.gcf().canvas.draw()


def onCalc(nEntry):
        errmsg = "Digite um número inteiro válido!"
        try:
            n = int(nEntry.get())
            x = np.arange(0.0,3.0,0.01)
            y = np.sin(2*np.pi*x+n)
            plot(x, y)

        except ValueError:
            messagebox.showerror("Entrada inválida", errmsg)
            return
        print(n)

# GUI
root = Tk()
root.title('Gráfico de frequência')
root.resizable(width=FALSE, height=FALSE)

nLabel = ttk.Label(root, text="N =")
nEntry = ttk.Entry(root, width=12)
nEntry.insert(0, "6")
draw_button = ttk.Button(root, text="Plot!", width=15, command = lambda:onCalc(nEntry))

#Layout
nLabel.grid(row=0,column=0, pady=5, sticky=N)
nEntry.grid(row=0,column=1, pady=5, padx=10, sticky=N)
draw_button.grid(row=0, column=0, padx=5, sticky="we")

# init figure
fig = plt.figure()

canvas = FigureCanvasTkAgg(fig, master=root)
toolbar = NavigationToolbar2TkAgg(canvas, root)
canvas.get_tk_widget().grid(row=0,column=2)
toolbar.grid(row=1,column=2)

root.mainloop()
