%LEG1_90 = readtable('LEG1-90.CSV');
%LEG2_90 = readtable('LEG2-90.CSV');
%OUTPUT_90 = readtable('OUTPUT-90.CSV');
%ConRc = importdata('ConRc.txt','\t');

t = (readtable('OUTPUT-0.CSV').Var4 - min(readtable('OUTPUT-0.CSV').Var4))*10^6;

Vleg1_0 = readtable('LEG1-0.CSV').Var5;
Vleg2_0 = readtable('LEG2-0.CSV').Var5;
Voutput_0 = readtable('OUTPUT-0.CSV').Var5;

Vleg1_30 = readtable('LEG1-30.CSV').Var5;
Vleg2_30 = readtable('LEG2-30.CSV').Var5;
Voutput_30 = readtable('OUTPUT-30.CSV').Var5;

Vleg1_60 = readtable('LEG1-60.CSV').Var5;
Vleg2_60 = readtable('LEG2-60.CSV').Var5;
Voutput_60 = readtable('OUTPUT-60.CSV').Var5;

Vleg1_90 = readtable('LEG1-90.CSV').Var5;
Vleg2_90 = readtable('LEG2-90.CSV').Var5;
Voutput_90 = readtable('OUTPUT-90.CSV').Var5;

Vleg1_120 = readtable('LEG1-120.CSV').Var5;
Vleg2_120 = readtable('LEG2-120.CSV').Var5;
Voutput_120 = readtable('OUTPUT-120.CSV').Var5;

Vleg1_150 = readtable('LEG1-150.CSV').Var5;
Vleg2_150 = readtable('LEG2-150.CSV').Var5;
Voutput_150 = readtable('OUTPUT-150.CSV').Var5;

Vleg1_180 = readtable('LEG1-180.CSV').Var5;
Vleg2_180 = readtable('LEG2-180.CSV').Var5;
Voutput_180 = readtable('OUTPUT-180.CSV').Var5;

set(0,'defaultTextInterpreter','none');
set(groot,'defaultAxesTickLabelInterpreter','none'); 

%% Fase 0° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Noto Sans');
plot(t, smoothdata(Voutput_0,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Noto Sans Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
axis([0 100 -40 40]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_0,'gaussian',5), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_0,'gaussian',5), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Noto Sans Medium';
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
f = gcf;
f.Position = [100 100 450 340] 
axis([0 100 -10 40]);

%% Fase 30° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Noto Sans');
plot(t, smoothdata(Voutput_30,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Noto Sans Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
axis([0 100 -40 40]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_30,'gaussian',5), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_30,'gaussian',5), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Noto Sans Medium';
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
f = gcf;
f.Position = [100 100 450 340] 
axis([0 100 -10 40]);
%% Fase 60° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Noto Sans');
plot(t, smoothdata(Voutput_60,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Noto Sans Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
axis([0 100 -40 40]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_60,'gaussian',5), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_60,'gaussian',5), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Noto Sans Medium';
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
f = gcf;
f.Position = [100 100 450 340] 
axis([0 100 -10 40]);

%% Fase 90° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Noto Sans');
plot(t, smoothdata(Voutput_90,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Noto Sans Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
axis([0 100 -40 40]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_90,'gaussian',5), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_90,'gaussian',5), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Noto Sans Medium';
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
f = gcf;
f.Position = [100 100 450 340] 
axis([0 100 -10 40]);

%% Fase 120° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Noto Sans');
plot(t, smoothdata(Voutput_120,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Noto Sans Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
axis([0 100 -40 40]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_120,'gaussian',5), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_120,'gaussian',5), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Noto Sans Medium';
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
f = gcf;
f.Position = [100 100 450 340] 
axis([0 100 -10 40]);

%% Fase 150° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Noto Sans');
plot(t, smoothdata(Voutput_150,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Noto Sans Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
axis([0 100 -40 40]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_150,'gaussian',5), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_150,'gaussian',5), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Noto Sans Medium';
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
f = gcf;
f.Position = [100 100 450 340] 
axis([0 100 -10 40]);

%% Fase 180° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Noto Sans');
plot(t, smoothdata(Voutput_180,'gaussian',5), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Noto Sans Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
axis([0 100 -40 40]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_180,'gaussian',5), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_180,'gaussian',5), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Noto Sans Medium';
xlabel('Tiempo [μs]', 'FontName', 'Noto Sans SemiBold');
ylabel('Tensión [V]', 'FontName', 'Noto Sans SemiBold');
f = gcf;
f.Position = [100 100 450 340] 
axis([0 100 -10 40]);