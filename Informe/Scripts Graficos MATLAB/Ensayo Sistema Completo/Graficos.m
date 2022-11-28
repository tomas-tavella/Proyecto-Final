
% 15V / DC50 / RL100
En1.t50 = (readtable('15V/1 - DC50.RL100 - VRECT.CSV').Var4 - min(readtable('15V/1 - DC50.RL100 - VRECT.CSV').Var4))*10^6;
En1.t100 = (readtable('15V/1 - DC50.RL100 - IOUT.CSV').Var4 - min(readtable('15V/1 - DC50.RL100 - IOUT.CSV').Var4))*10^6;
En1.Vrect = readtable('15V/1 - DC50.RL100 - VRECT.CSV').Var5;
En1.ILf = readtable('15V/1 - DC50.RL100 - ILF.CSV').Var5;
En1.Vs = readtable('15V/1 - DC50.RL100 - VS.CSV').Var5;
En1.Vout = readtable('15V/1 - DC50.RL100 - VOUT.CSV').Var5;
En1.Iout = readtable('15V/1 - DC50.RL100 - IOUT.CSV').Var5;
En1.IoutVrect = readtable('15V/1 - DC50.RL100 - IOUT(VRECT).CSV').Var5;
En1.IoutMean = 0.239*ones(2500,1);
% Iin 0.42A , Pin 6.3W , Vout 24.25V , Iout 239mA , Pout 5.78W

% 15V / DC50 / RL50
En2.t50 = (readtable('15V/2 - DC50.RL50 - VRECT.CSV').Var4 - min(readtable('15V/2 - DC50.RL50 - VRECT.CSV').Var4))*10^6;
En2.Vrect = readtable('15V/2 - DC50.RL50 - VRECT.CSV').Var5;
En2.ILf = readtable('15V/2 - DC50.RL50 - ILF.CSV').Var5;
En2.IoutMean = 0.470*ones(2500,1);
% Iin 0.82A , Pin 12.3W , Vout 23.72V , Iout 470mA , Pout 11.15W

% 15V / DC75 / RL100
En5.t50 = (readtable('15V/5 - DC75.RL100 - VRECT.CSV').Var4 - min(readtable('15V/5 - DC75.RL100 - VRECT.CSV').Var4))*10^6;
En5.t100 = (readtable('15V/5 - DC75.RL100 - IOUT.CSV').Var4 - min(readtable('15V/5 - DC75.RL100 - IOUT.CSV').Var4))*10^6;
En5.Vrect = readtable('15V/5 - DC75.RL100 - VRECT.CSV').Var5;
En5.ILf = readtable('15V/5 - DC75.RL100 - ILF.CSV').Var5;
En5.Vs = readtable('15V/5 - DC75.RL100 - VS.CSV').Var5;
En5.Vout = readtable('15V/5 - DC75.RL100 - VOUT.CSV').Var5;
En5.Iout = readtable('15V/5 - DC75.RL100 - IOUT.CSV').Var5;
En5.IoutVrect = readtable('15V/5 - DC75.RL100 - IOUT(VRECT).CSV').Var5;
En5.IoutMean = 0.366*ones(2500,1);
% Iin 0.97A , Pin 14.55W , Vout 37.09V , Iout 366mA , Pout 13.58W

% 30V / DC50 / RL100
En7.t50 = (readtable('30V/7 - DC50.RL100 - VRECT.CSV').Var4 - min(readtable('30V/7 - DC50.RL100 - VRECT.CSV').Var4))*10^6;
En7.t100 = (readtable('30V/7 - DC50.RL100 - IOUT.CSV').Var4 - min(readtable('30V/7 - DC50.RL100 - IOUT.CSV').Var4))*10^6;
En7.Vrect = readtable('30V/7 - DC50.RL100 - VRECT.CSV').Var5;
En7.ILf = readtable('30V/7 - DC50.RL100 - ILF.CSV').Var5;
En7.Vs = readtable('30V/7 - DC50.RL100 - VS.CSV').Var5;
En7.Vout = readtable('30V/7 - DC50.RL100 - VOUT.CSV').Var5;
En7.Iout = readtable('30V/7 - DC50.RL100 - IOUT.CSV').Var5;
En7.IoutVrect = readtable('30V/7 - DC50.RL100 - IOUT(VRECT).CSV').Var5;
En7.IoutMean = 0.491*ones(2500,1);
% Iin 0.87A , Pin 26.1W , Vout 49.63V , Iout 491mA , Pout 24.38W

% 30V / DC50 / RL30
En9.t50 = (readtable('30V/9 - DC50.RL30 - VRECT.CSV').Var4 - min(readtable('30V/9 - DC50.RL30 - VRECT.CSV').Var4))*10^6;
En9.Vrect = readtable('30V/9 - DC50.RL30 - VRECT.CSV').Var5;
En9.ILf = readtable('30V/9 - DC50.RL30 - ILF.CSV').Var5;
En9.IoutMean = 1.584*ones(2500,1);
% Iin 2.76A , Pin 82.8W , Vout 47.63V , Iout 1.584A , Pout 75.44W

% 30V / DC25 / RL30
En10.t50 = (readtable('30V/10 - DC25.RL30 - VRECT.CSV').Var4 - min(readtable('30V/10 - DC25.RL30 - VRECT.CSV').Var4))*10^6;
En10.Vrect = readtable('30V/10 - DC25.RL30 - VRECT.CSV').Var5;
En10.ILf = readtable('30V/10 - DC25.RL30 - ILF.CSV').Var5;
En10.IoutMean = 0.928*ones(2500,1);
% Iin 2.76A , Pin 82.8W , Vout 47.63V , Iout 0.928A , Pout 75.44W

set(0,'defaultTextInterpreter','none');
set(groot,'defaultAxesTickLabelInterpreter','none'); 

%% Caso I %%

subplot(2,1,1);
yyaxis left;
plot(En1.t50, smoothdata(En1.Vrect,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
yline(24.25,':','24,2 V', 'LineWidth', 1.5, 'Color','#0064A5','FontSize',9,'LabelHorizontalAlignment','right');
ax = gca;
ax.FontName = 'Noto Sans Medium';
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
%xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En1.Vrect)-0.1*(abs(max(En1.Vrect)-min(En1.Vrect)))) (max(En1.Vrect)+0.1*(abs(max(En1.Vrect)-min(En1.Vrect))))]);
yyaxis right;
plot(En1.t50, smoothdata(En1.ILf,'gaussian',5), 'LineWidth', 1, 'Color','#A54100'); hold on; grid on;
plot(En1.t50, circshift(En1.IoutMean,200),':','LineWidth', 1.5, 'Color','#A54100');
text(0.5,0.267,'0,24 A','Color','#A54100');
ylabel('Corriente [A]','FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En1.ILf)-0.1*(abs(max(En1.ILf)-min(En1.ILf)))) (max(En1.ILf)+0.1*(abs(max(En1.ILf)-min(En1.ILf))))]);

subplot(2,1,2);
plot(En1.t50, smoothdata(En1.Vs,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
%plot(En1.t100, smoothdata(En1.Vout,'gaussian',5),'--' , 'LineWidth', 1, 'Color','#0064A5');
ax = gca;
ax.FontName = 'Noto Sans Medium';
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En1.Vs)-0.05*(abs(max(En1.Vs)-min(En1.Vs)))) (max(En1.Vs)+0.05*(abs(max(En1.Vs)-min(En1.Vs))))]);
f = gcf;
f.Position = [100 100 428 310]      % Posición y tamaño de la ventana

%% Caso II %%

%subplot(2,1,1);
yyaxis left;
plot(En2.t50, smoothdata(En2.Vrect,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
yline(23.72,':','23,7 V', 'LineWidth', 1.5, 'Color','#0064A5','FontSize',9,'LabelHorizontalAlignment','right');
ax = gca;
ax.FontName = 'Noto Sans Medium';
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En2.Vrect)-0.1*(abs(max(En2.Vrect)-min(En2.Vrect)))) (max(En2.Vrect)+0.1*(abs(max(En2.Vrect)-min(En2.Vrect))))]);
yyaxis right;
plot(En2.t50, smoothdata(En2.ILf,'gaussian',5), 'LineWidth', 1, 'Color','#A54100'); hold on; grid on;
plot(En2.t50, circshift(En2.IoutMean,200),':','LineWidth', 1.5, 'Color','#A54100');
text(0.5,0.497,'0,47 A','Color','#A54100');
ylabel('Corriente [A]','FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En2.ILf)-0.1*(abs(max(En2.ILf)-min(En2.ILf)))) (max(En2.ILf)+0.1*(abs(max(En2.ILf)-min(En2.ILf))))]);
f = gcf;
f.Position = [100 100 428 156]      % Posición y tamaño de la ventana

%% Caso V %%

subplot(2,1,1);
yyaxis left;
plot(En5.t50, smoothdata(En5.Vrect,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
yline(37.09,':','37 V', 'LineWidth', 1.5, 'Color','#0064A5','FontSize',9,'LabelHorizontalAlignment','right','LabelVerticalAlignment','bottom');
ax = gca;
ax.FontName = 'Noto Sans Medium';
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
%xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En5.Vrect)-0.1*(abs(max(En5.Vrect)-min(En5.Vrect)))) (max(En5.Vrect)+0.1*(abs(max(En5.Vrect)-min(En5.Vrect))))]);
yyaxis right;
plot(En5.t50, smoothdata(En5.ILf,'gaussian',5), 'LineWidth', 1, 'Color','#A54100'); hold on; grid on;
plot(En5.t50, circshift(En5.IoutMean,200),':','LineWidth', 1.5, 'Color','#A54100');
text(0.5,0.388,'0,37 A','Color','#A54100');
ylabel('Corriente [A]','FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En5.ILf)-0.1*(abs(max(En5.ILf)-min(En5.ILf)))) (max(En5.ILf)+0.1*(abs(max(En5.ILf)-min(En5.ILf))))]);

subplot(2,1,2);
plot(En5.t100, smoothdata(circshift(En5.Vs,-310),'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
%plot(En5.t100, smoothdata(En5.Vout,'gaussian',5),'--' , 'LineWidth', 1, 'Color','#0064A5');
ax = gca;
ax.FontName = 'Noto Sans Medium';
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En5.Vs)-0.05*(abs(max(En5.Vs)-min(En5.Vs)))) (max(En5.Vs)+0.05*(abs(max(En5.Vs)-min(En5.Vs))))]);
f = gcf;
f.Position = [100 100 428 315]      % Posición y tamaño de la ventana

%% Caso VII %%

subplot(2,1,1);
yyaxis left;
plot(En7.t50, smoothdata(En7.Vrect,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
yline(49.63,':','49,6 V', 'LineWidth', 1.5, 'Color','#0064A5','FontSize',9,'LabelHorizontalAlignment','right');
ax = gca;
ax.FontName = 'Noto Sans Medium';
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
%xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En7.Vrect)-0.1*(abs(max(En7.Vrect)-min(En7.Vrect)))) (max(En7.Vrect)+0.1*(abs(max(En7.Vrect)-min(En7.Vrect))))]);
yyaxis right;
plot(En7.t50, smoothdata(En7.ILf,'gaussian',5), 'LineWidth', 1, 'Color','#A54100'); hold on; grid on;
plot(En7.t50, circshift(En7.IoutMean,200),':','LineWidth', 1.5, 'Color','#A54100');
text(0.5,0.545,'0,49 A','Color','#A54100');
ylabel('Corriente [A]','FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En7.ILf)-0.1*(abs(max(En7.ILf)-min(En7.ILf)))) (max(En7.ILf)+0.1*(abs(max(En7.ILf)-min(En7.ILf))))]);

subplot(2,1,2);
plot(En7.t100, smoothdata(circshift(En7.Vs,0),'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
%plot(En7.t100, smoothdata(En7.Vout,'gaussian',5),'--' , 'LineWidth', 1, 'Color','#0064A5');
ax = gca;
ax.FontName = 'Noto Sans Medium';
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En7.Vs)-0.05*(abs(max(En7.Vs)-min(En7.Vs)))) (max(En7.Vs)+0.05*(abs(max(En7.Vs)-min(En7.Vs))))]);
f = gcf;
f.Position = [100 100 428 315]      % Posición y tamaño de la ventana

%% Caso IX %%

%subplot(2,1,1);
yyaxis left;
plot(En9.t50, smoothdata(En9.Vrect,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
yline(47.63,':','47,6 V', 'LineWidth', 1.5, 'Color','#0064A5','FontSize',9,'LabelHorizontalAlignment','right','LabelVerticalAlignment','bottom');
ax = gca;
ax.FontName = 'Noto Sans Medium';
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En9.Vrect)-0.1*(abs(max(En9.Vrect)-min(En9.Vrect)))) (max(En9.Vrect)+0.1*(abs(max(En9.Vrect)-min(En9.Vrect))))]);
yyaxis right;
plot(En9.t50, smoothdata(En9.ILf,'gaussian',5), 'LineWidth', 1, 'Color','#A54100'); hold on; grid on;
plot(En9.t50, circshift(En9.IoutMean,200),':','LineWidth', 1.5, 'Color','#A54100');
text(0.5,1.645,'1,58 A','Color','#A54100');
%yl=yline(Iout,':','LineWidth', 1.5,'Color','#A54100');
ylabel('Corriente [A]','FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En9.ILf)-0.1*(abs(max(En9.ILf)-min(En9.ILf)))) (max(En9.ILf)+0.1*(abs(max(En9.ILf)-min(En9.ILf))))]);
f = gcf;
f.Position = [100 100 428 156]      % Posición y tamaño de la ventana

%% Caso X %%

%subplot(2,1,1);
yyaxis left;
plot(En10.t50, smoothdata(En10.Vrect,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
yline(27.95,':','27,9 V', 'LineWidth', 1.5, 'Color','#0064A5','FontSize',9,'LabelHorizontalAlignment','right');
ax = gca;
ax.FontName = 'Noto Sans Medium';
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En10.Vrect)-0.1*(abs(max(En10.Vrect)-min(En10.Vrect)))) (max(En10.Vrect)+0.1*(abs(max(En10.Vrect)-min(En10.Vrect))))]);
yyaxis right;
plot(En10.t50, smoothdata(En10.ILf,'gaussian',5), 'LineWidth', 1, 'Color','#A54100'); hold on; grid on;
plot(En10.t50, circshift(En10.IoutMean,200),':','LineWidth', 1.5, 'Color','#A54100');
text(0.5,0.976,'0,93 A','Color','#A54100');
%yl=yline(Iout,':','LineWidth', 1.5,'Color','#A54100');
ylabel('Corriente [A]','FontName', 'Noto Sans SemiBold');
axis([0 50 (min(En10.ILf)-0.1*(abs(max(En10.ILf)-min(En10.ILf)))) (max(En10.ILf)+0.1*(abs(max(En10.ILf)-min(En10.ILf))))]);
f = gcf;
f.Position = [100 100 428 156]      % Posición y tamaño de la ventana

