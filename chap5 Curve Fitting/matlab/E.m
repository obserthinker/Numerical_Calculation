% function z=E(A,B,C,D,E)
% z= (A*cos(B*1)+C*sin(D*1)+E-66).^2+(A*cos(B*2)+C*sin(D*2)+E-66).^2+(A*cos(B*3)+C*sin(D*3)+E-65).^2+(A*cos(B*4)+C*sin(D*4)+E-64).^2+(A*cos(B*5)+C*sin(D*5)+E-63).^2+(A*cos(B*6)+C*sin(D*6)+E-63).^2+(A*cos(B*7)+C*sin(D*7)+E-62).^2+(A*cos(B*8)+C*sin(D*8)+E-61).^2+(A*cos(B*9)+C*sin(D*9)+E-60).^2+(A*cos(B*10)+C*sin(D*10)+E-60).^2+(A*cos(B*11)+C*sin(D*11)+E-59).^2+(A*cos(B*12)+C*sin(D*12)+E-58).^2+(A*cos(B*13)+C*sin(D*13)+E-58).^2+(A*cos(B*14)+C*sin(D*14)+E-58).^2+(A*cos(B*15)+C*sin(D*15)+E-58).^2+(A*cos(B*16)+C*sin(D*16)+E-58).^2+(A*cos(B*17)+C*sin(D*17)+E-57).^2+(A*cos(B*18)+C*sin(D*18)+E-57).^2+(A*cos(B*19)+C*sin(D*19)+E-57).^2+(A*cos(B*20)+C*sin(D*20)+E-58).^2+(A*cos(B*21)+C*sin(D*21)+E-60).^2+(A*cos(B*22)+C*sin(D*22)+E-64).^2+(A*cos(B*23)+C*sin(D*23)+E-67).^2+(A*cos(B*24)+C*sin(D*24)+E-68).^2+(A*cos(B*0)+C*sin(D*0)+E-0).^2;
function z=E(u)
A=u(1)
C=u(2)
z=(C.*exp(A)-2.5).^2;

