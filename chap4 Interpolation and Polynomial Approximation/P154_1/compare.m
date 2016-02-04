syms x
f = sin(x)
p5 = taylor(f,x,'ExpansionPoint',0,'Order',5)
p7 = taylor(f,x,'ExpansionPoint',0,'Order',7)
p9 = taylor(f,x,'ExpansionPoint',0,'Order',9)
t = [-1:0.001:1];
h1 = plot(t,sin(t),'r')
hold on
h2 = plot(t,subs(p5,t),'-g')
hold on
h3 = plot(t,subs(p7,t),'--b')
hold on
h4 = plot(t,subs(p9,t),':m')
legend([h1,h2,h3,h4],'sin(x)','P_5','P_7','P_9','Location','northwest')
xlabel('x')
ylabel('sin(x)')
title('sin(x),P_5(x),P_7(x),P_9(x)ÔÚ[-1,1]Ö®¼äÍ¼Ïñ')