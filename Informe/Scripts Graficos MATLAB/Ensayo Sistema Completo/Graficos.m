%LEG1_90 = readtable('LEG1-90.CSV');
%LEG2_90 = readtable('LEG2-90.CSV');
%OUTPUT_90 = readtable('OUTPUT-90.CSV');
%ConRc = importdata('ConRc.txt','\t');

t1 = (readtable('7 - Vrect.CSV').Var4 - min(readtable('7 - Vrect.CSV').Var4))*10^6;
t2 = (readtable('7 - Vp.CSV').Var4 - min(readtable('7 - Vp.CSV').Var4))*10^6;

% DC 50% / RL 100ohm / Vin 30V
Vrect = readtable('7 - Vrect.CSV').Var5;     
ILf = readtable('7 - ILf.CSV').Var5;
Vp = readtable('7 - Vp.CSV').Var5;
Iout = mean(ILf);

set(0,'defaultTextInterpreter','none');
set(groot,'defaultAxesTickLabelInterpreter','none'); 

%% Fase 0° %%

%subplot(2,1,1);
%set(gca, 'FontName', 'Montserrat');
%t = title('Tensión rectificada y corriente de inductor');
%t.FontSize = 20;
yyaxis left;
plot(t1, smoothdata(Vrect,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
axis([0 50 (min(Vrect)-0.1*(abs(max(Vrect)-min(Vrect)))) (max(Vrect)+0.1*(abs(max(Vrect)-min(Vrect))))]);
yyaxis right;
plot(t1, smoothdata(ILf,'gaussian',5), 'LineWidth', 1, 'Color','#A54100'); hold on; grid on;
%yl=yline(Iout,':','LineWidth', 1.5,'Color','#A54100');
f = gcf;
f.Position = [100 100 600 240]      % Posición y tamaño de la ventana
ax = gca;
ax.FontName = 'Montserrat Medium';
ylabel('Corriente [A]', 'FontName', 'Montserrat SemiBold');
axis([0 50 (min(ILf)-0.1*(abs(max(ILf)-min(ILf)))) (max(ILf)+0.1*(abs(max(ILf)-min(ILf))))]);

% subplot(2,1,2);
% plot(t2, smoothdata(Vp,'gaussian',5), 'LineWidth', 1.5, 'Color', '#0064A5'); hold on; grid on;
% %plot(t_leg, smoothdata(VprimarioMinus,'gaussian',5)-30, 'LineWidth',1.5); hold on; grid on;
% ax = gca;
% ax.FontName = 'Montserrat Medium';
% xlabel('Tiempo [us]', 'FontName', 'Montserrat SemiBold');
% ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
% axis([0 50 (min(Vp)-0.1*(abs(max(Vp)-min(Vp)))) (max(Vp)+0.1*(abs(max(Vp)-min(Vp))))]);
