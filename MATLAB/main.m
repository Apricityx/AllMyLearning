pyenv('Version','C:\Users\apric\AppData\Local\Programs\Python\Python311\python.exe')
clear classes; % 清除类定义的缓存
mod = py.importlib.import_module('RegressionModels'); % 导入Python脚本模块
py.importlib.reload(mod); % 重新加载Python脚本模块
addpath('./')

% j = 1;
% for i = 1:9
%     x = [0:0.01:4]
%     y = sin(x * i)
%     subplot(3,4,i)
%     plot (x,y)
%     if i % 3 == 0
%          j = j + 1;
%     end  
% end

% subplot(3,4,10)
% x = [1:10]
% y = [123,412,124,1241,4124,123,412,3214,123,421]
% bar(x,y)

% [x,y] = meshgrid(-5:0.1:5,-5:0.1:5);
% fz = (x.^3)/16 + (y.^2);
% [C,h] = contour(x,y,fz); % 这里的C是等高线的高度值，h是等高线的图形句柄
% set(h,'Showtext','on','TextStep',get(h,'LevelStep')*2); % 显示等高线的高度值
% surf(x,y,fz);
% syms x
% result = solve(x^114514+1==11, x)

% [x,y] = meshgrid(-5:0.1:5,-5:0.1:5);
% 初始化num和p值数组
% num = 0:00.1:100;
% p_values = zeros(size(num));

% % 假设arr是一个包含确定元素和num的数组
% % 这里我们用一个随机数组来模拟arr
% arr = [-1.23, 0.45, 1.34, -0.67, 0.99, -0.12, -2.45, 0.65, -0.88,num];

% % 计算每个num值对应的p值
% for i = 1:length(num)
%     arr(end) = num(i); % 将num的当前值赋给arr的最后一个元素
%     [~, p_values(i)] = lillietest(arr); % 计算p值
% end

% % 绘制p值关于num的图像
% plot(num, p_values, '-o');
% xlabel('num');
% ylabel('p值');
% title('p值关于num的变化');

% a = double(py.list([1,2,3,4]))



% years = double(py.RegressionModels.get_years())
% nums = double(py.RegressionModels.get_nums())
% test = py.RegressionModels.get_test()
% plot(years,nums,'o','MarkerSize',5,'MarkerFaceColor','#Add8E6')
% alpha = py.RegressionModels.get_alpha();
% beta = py.RegressionModels.get_beta1();

% x1 = [2000:0.01:2025];
% y1 = beta * x1 + alpha;
% hold on;
% plot(x1,y1,'o','MarkerSize',1,'MarkerFaceColor','#Add8E6');
[num,text,raw] = xlsread('./src/AHP Example.xlsx');
AHP(num)
