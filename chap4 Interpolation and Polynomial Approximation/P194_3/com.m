syms x
T = x+(x^3)/3+2*(x^5)/15+17*(x^7)/315+62*(x^9)/2835
R = (x^5+945*x-105*x^3)/(945+15*x^4-420*x^2)
f = tan(x);
t =linspace(-1.6,1.6,6000);
h1 = plot(t,subs(f,t),'r');
hold on
h2 = plot(t,subs(T,t),'-g');
hold on
h3 = plot(t,subs(R,t),'--b');

legend([h1,h2,h3],'tan(x)','T_9','R_{5,4}','Location','northwest')
xlabel('x')
ylabel('tan(x)')
