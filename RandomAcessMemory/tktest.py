from tkinter import *
from tkinter import ttk


def plotGraph(nText, fText):
    try:
        value = int(nText.get())
        fText.set((value+5))
    except ValueError:
        print("ERRROUUU")


def instantiateIterface():
    top = Tk()
    nText = StringVar()
    fText = StringVar()
    fText.set("<placeholder>")
    top.title("Gráfico de frequência")
    top.resizable(0, 0)
    topFrame = ttk.Frame(top, padding="500 300")
    topFrame.grid(column=3, row=1)
    topFrame.rowconfigure(1, weight=1)

    # Labels
    n_label = ttk.Label(topFrame, text="N = ")
    n_label.grid(row=0)
    f_label = ttk.Label(topFrame, textvariable=fText)
    f_label.grid(column=3)
    n_entry = ttk.Entry(topFrame, textvariable=nText)
    n_entry.grid(column=1, row=0)
    n_entry.insert(0, "6")
    # Buttons
    conf_B = ttk.Button(topFrame, text="Calcular Gráfico", command=lambda: plotGraph(n_entry, fText))
    conf_B.grid(column=2)

    top.geometry("640x480")
    top.bind('<Return>', plotGraph)

    top.mainloop()


def main():

    instantiateIterface()


if __name__ == '__main__':
    main()
