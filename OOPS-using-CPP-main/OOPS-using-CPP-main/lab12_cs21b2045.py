from tkinter import *

def gradechange(grade):
    if grade== 'S' or grade== 's' :
        return 10
    elif grade== 'A' or grade== 'a' :
        return 9
    elif grade== 'B' or grade== 'b' :
        return 8
    elif grade== 'C' or grade== 'c' :
        return 7
    elif grade== 'D' or grade== 'd' :
        return 6
    elif grade== 'E' or grade== 'e' :
        return 5
    elif(grade== 'W' or grade== 'w' or grade== 'I' or grade== 'i' or grade== 'U' or grade== 'u'):
        return 0
    else:
        return -1

def Sgpa():
    S1_grade=gradechange(grade1.get())
    S2_grade=gradechange(grade2.get())
    S3_grade=gradechange(grade3.get())
    S4_grade=gradechange(grade4.get())
    if(S1_grade>=0 and S2_grade>=0 and S3_grade>=0 and S4_grade>=0):
        S1_credits=S1_grade*4
        subject1.set(S1_credits)
        S2_credits=S2_grade*4
        subject2.set(S2_credits)
        S3_credits=S3_grade*3
        subject3.set(S3_credits)
        S4_credits=S4_grade*4
        subject4.set(S4_credits)
        tcredits=(S1_credits + S2_credits + S3_credits + S4_credits)
        sgpa=round(tcredits/15,3)
        credit.set(tcredits)
        Sgp.set(sgpa)
    else:
        Sgp.set("Enter correct grades")

m_window = Tk()
m_window.geometry("750x400")
m_window.title("MARKSHEET")
s_window = Frame(m_window,padx=60,pady=60,bg='#CACAFF')
s_window.pack(expand=True)
name_lb=Label(s_window,text="Name",bg='#CACAFF')
name_lb.grid(row=0,column=1)
name_tf=Entry(s_window)
name_tf.grid(row=0,column=2)

regno_lb=Label(s_window,text="Reg.No",bg='#CACAFF')
regno_lb.grid(row=0,column=4)
regno_tf=Entry(s_window)
regno_tf.grid(row=0,column=5)

rno_lb= Label(s_window,text="Roll.No",bg='#CACAFF')
rno_lb.grid(row=1,column=1)
rno_tf=Entry(s_window)
rno_tf.grid(row=1,column=2,padx=10,pady=20)



sr=Label(s_window,text="Srl.No",bg='#CACAFF')
sr.grid(row=4,column=1)

subject=Label(s_window,text="Subject",bg='#CACAFF')
subject.grid(row=4,column=2)

grade=Label(s_window,text="Grade obtained",bg='#CACAFF')
grade.grid(row=4,column=3,padx=10)

sub_credits=Label(s_window,text="Sub Credit",bg='#CACAFF')
sub_credits.grid(row=4,column=4,padx=40)

Credit=Label(s_window,text="Credit obtained",bg='#CACAFF')
Credit.grid(row=4,column=5)

no1=Label(s_window,text='1',bg='#CACAFF')
no1.grid(row=5,column=1)

no2=Label(s_window,text='2',bg='#CACAFF')
no2.grid(row=6,column=1)

no3=Label(s_window,text='3',bg='#CACAFF')
no3.grid(row=7,column=1)

no4=Label(s_window,text='4',bg='#CACAFF')
no4.grid(row=8,column=1)

cs201=Label(s_window,text="CS 201",bg='#CACAFF')
cs201.grid(row=5,column=2)

cs202=Label(s_window,text="CS 202",bg='#CACAFF')
cs202.grid(row=6,column=2)

ma201=Label(s_window,text="MA 201",bg='#CACAFF')
ma201.grid(row=7,column=2)

ec201=Label(s_window,text="EC 201",bg='#CACAFF')
ec201.grid(row=8,column=2)

grade1=Entry(s_window)
grade1.grid(row=5,column=3)

grade2=Entry(s_window)
grade2.grid(row=6,column=3)

grade3=Entry(s_window)
grade3.grid(row=7,column=3)

grade4=Entry(s_window)
grade4.grid(row=8,column=3)

subcredit1=Label(s_window,text='4',bg='#CACAFF')
subcredit1.grid(row=5,column=4)

subcredit2=Label(s_window,text='4',bg='#CACAFF')
subcredit2.grid(row=6,column=4)

subcredit3=Label(s_window,text='3',bg='#CACAFF')
subcredit3.grid(row=7,column=4)

subcredit4=Label(s_window,text='4',bg='#CACAFF')
subcredit4.grid(row=8,column=4)

subject1 = IntVar()
subject2 = IntVar()
subject3 = IntVar()
subject4 = IntVar()
credit = IntVar()
Sgp = IntVar()

credit_obtained1=Entry(s_window,textvariable=subject1)
credit_obtained1.grid(row=5,column=5)

credit_obtained2=Entry(s_window,textvariable=subject2)
credit_obtained2.grid(row=6,column=5)

credit_obtained3=Entry(s_window,textvariable=subject3)
credit_obtained3.grid(row=7,column=5)

credit_obtained4=Entry(s_window,textvariable=subject4)
credit_obtained4.grid(row=8,column=5)

totalcredits=Label(s_window,text='Total Credits',bg='#CACAFF')
totalcredits.grid(row=9,column=4)

totalcredits_tf=Entry(s_window,textvariable=credit)
totalcredits_tf.grid(row=9,column=5)

sgpa=Label(s_window,text='SGPA',bg='#CACAFF')
sgpa.grid(row=10,column=4)
sgpa_tf=Entry(s_window,textvariable=Sgp)
sgpa_tf.grid(row=10,column=5)

submit=Button(s_window,text='SUBMIT',bg='green',command=Sgpa)
submit.grid(row=10,column=2)

m_window.mainloop()