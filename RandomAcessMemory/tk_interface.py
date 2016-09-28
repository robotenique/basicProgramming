from tkinter import *
from tkinter import ttk


def plotGraph(nText,fText):
    try:
        value = int(nText.get())
        fText.set((value+5))
    except ValueError:
        print("ERRROUUU")

def instantiateIterface():
    top = Tk()
    nText = StringVar()
    fText = StringVar()

    top.title("Gráfico de frequência")

    topFrame = ttk.Frame(top, padding="3 3 12 12")
    topFrame.grid(column=0, row=0, sticky=(N, W, E, S))
    topFrame.columnconfigure(0, weight=1)
    topFrame.rowconfigure(0, weight=1)

    n_entry = ttk.Entry(topFrame, width=7, textvariable=nText)
    n_entry.grid(column=2, row=1, sticky=(W, E))

    f_label = ttk.Label(topFrame, textvariable=fText)
    f_label.grid(column=2, row=2, sticky=(W, E))
    c_button = ttk.Button(topFrame, text="Calcular", command=lambda: plotGraph(nText, fText))
    c_button.grid(column=3, row=3, sticky=W)
    ttk.Label(top, text="nText").grid(column=3, row=1, sticky=W)
    ttk.Label(top, text="text2").grid(column=1, row=2, sticky=E)
    ttk.Label(top, text="text3").grid(column=3, row=2, sticky=W)

    for child in topFrame.winfo_children():
        child.grid_configure(padx=5, pady=5)

    n_entry.focus()
    top.bind('<Return>', plotGraph)

    top.mainloop()


def main():

    instantiateIterface()


if __name__ == '__main__':
    main()
