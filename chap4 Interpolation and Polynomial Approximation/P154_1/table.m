syms x
f = sin(x)
p5 = taylor(f,x,'ExpansionPoint',0,'Order',5)
p7 = taylor(f,x,'ExpansionPoint',0,'Order',7)
p9 = taylor(f,x,'ExpansionPoint',0,'Order',9)
t = linspace(-1,1,11)
a1 = sin(t)
a2 = subs(p5,t)
a3 = subs(p7,t)
a4 = subs(p9,t)