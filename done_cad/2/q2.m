figure  %建立窗口
h = figure  %h为窗口句柄，将figure赋给h

%首先进行绕y轴pi/6的旋转，生成50帧的动画来展示。
for i=1:50
    %t为旋转变换矩阵，t左乘坐标矩阵即为对坐标进行绕y轴正方向逆时针旋转。
    t=[1,0,0;0,cos(i*pi/600),-sin(i*pi/600);0,sin(i*pi/600),cos(i*pi/600)];
    %cube为plot3命令中画出正方体端点的矩阵
    t=t*cube;%对正方体进行旋转
    %画出旋转后的图像
    plot3(t(1,:),t(2,:),t(3,:));
    %在图像中给坐标轴贴标签
    xlabel('X');
    ylabel('Y');
    zlabel('Z');
    %由于不知道怎么画出从原点伸开的xyz轴，所以用网格来在观看的时候判断是否绕轴旋转
    grid;
    %按照常用的角度观察旋转，更容易理解动画
    view(64,22)
    %设置坐标轴范围，用来固定坐标轴
    axis([-0.7 1.5 -0.7 1.5 -0.7 1.5]) 
    %获取每一帧的动画
    A(i)=getframe(h);%在制作第二个视频的时候注释掉
end
%制作输出avi视频文件
% movie2avi(A,'x_movie2avi','compression','None');
% movie(A)

aa = t; %y轴旋转之后的立方体保存在aa中
for i=51:100 %动画设置为50帧。在录制绕z轴旋转的视频时改为1：50，制作全过程的时候改为51：100
    %t为绕z轴旋转变换矩阵
    t=[cos((i-50)*pi/300),sin((i-50)*pi/300),0;-sin((i-50)*pi/300),cos((i-50)*pi/300),0;0,0,1];
    %对aa进行旋转变换
    t=t*aa;
    %画出旋转变换之后的立方体
    plot3(t(1,:),t(2,:),t(3,:));
%       在图像中给坐标轴贴标签
    xlabel('X');
    ylabel('Y');
    zlabel('Z');
%     由于不知道怎么画出从原点伸开的xyz轴，所以用网格来在观看的时候判断是否绕轴旋转
    grid;
%     按照常用的角度观察旋转，更容易理解动画
    view(64,22)
%     设置坐标轴范围，用来固定坐标轴
    axis([-0.7 1.5 -0.7 1.5 -0.7 1.5]) 
%     获取每一帧的动画
    A(i)=getframe(h);
end
% movie(A)
movie2avi(A,'z_movie2avi','compression','none');%制作绕y轴或者全部视频的时候注释掉
movie2avi(A,'all_movie2avi','compression','none');%制作单个旋转的时候注释掉