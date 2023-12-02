from tkinter import *
def BMIS():
    H=float(Height_tb.get())/100
    W=float(Weight_tb.get())
    if(H>0 and W>0 ):
        Bmi=round(W/(H*H),2)
        IV.set(Bmi)
    else:
        IV.set("Enter correct values")

m_window = Tk()
m_window.geometry("400x400")
m_window.title('BMI Calculator')
m_window.config(bg='#EEEE76')

IV = IntVar()
s_window = Frame(m_window,padx=60,pady=60,bg='#CACAFF')
s_window.pack(expand=True)


Height_l =Label(
   s_window,
   text="Height(in Centimeters)",
    bg="#CACAFF"
)
Height_l.grid(row=3,column=1)
Height_tb=Entry(s_window)
Height_tb.grid(row=3,column=2)

Weight_l =Label(
   s_window,
   text="Weight(in Kgs)",
   bg='#CACAFF'
)
Weight_l.grid(row=5,column=1,pady=10)
Weight_tb=Entry(s_window)
Weight_tb.grid(row=5,column=2,pady=10)

Output_l=Label(
   s_window,
   text="Calculated BMI",
   bg='#CACAFF'
)
Output_l.grid(row=7,column=1,pady=10)
Output_tb = Entry(s_window,textvariable=IV)
Output_tb.grid(row=7,column=2,pady=18)

cal = Button(s_window,text='Calculate',command=BMIS)
cal.grid(row=8,column=2)

m_window.mainloop()