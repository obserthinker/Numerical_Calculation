syms x
T_4 = 1+x+(x^2)/2+(x^3)/6+(x^4)/24;
R = (12+6*x+x^2)/(12-6*x+x^2);
f = exp(x);
t =linspace(-1,4,6000);
h1 = plot(t,subs(f,t),'r')
hold on
h2 = plot(t,subs(T_4,t),'-g')
hold on
h3 = plot(t,subs(R,t),'--b')
legend([h1,h2,h3],'e^x','T_4','R_{2,2}','Location','northwest')
xlabel('x')