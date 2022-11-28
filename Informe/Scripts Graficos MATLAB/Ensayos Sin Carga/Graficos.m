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
%set(gca, 'FontName', 'Montserrat');
plot(t, smoothdata(Voutput_0,'gaussian',1), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Montserrat Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
axis([0 100 (min(Voutput_0)-0.1*(abs(max(Voutput_0)-min(Voutput_0)))) (max(Voutput_0)+0.1*(abs(max(Voutput_0)-min(Voutput_0))))]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_0,'gaussian',3), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_0,'gaussian',3), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Montserrat Medium';
xlabel('Tiempo [μs]', 'FontName', 'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
f = gcf;
f.Position = [100 100 428 330] 
axis([0 100 (min(Vleg1_0)-0.1*(abs(max(Vleg1_0)-min(Vleg1_0)))) (max(Vleg1_0)+0.1*(abs(max(Vleg1_0)-min(Vleg1_0))))]);

%% Fase 30° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Montserrat');
plot(t, smoothdata(Voutput_30,'gaussian',3), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Montserrat Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
axis([0 100 (min(Voutput_30)-0.1*(abs(max(Voutput_30)-min(Voutput_30)))) (max(Voutput_30)+0.1*(abs(max(Voutput_30)-min(Voutput_30))))]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_30,'gaussian',3), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_30,'gaussian',3), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Montserrat Medium';
xlabel('Tiempo [μs]', 'FontName', 'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
f = gcf;
f.Position = [100 100 428 330] 
axis([0 100 (min(Vleg1_30)-0.1*(abs(max(Vleg1_30)-min(Vleg1_30)))) (max(Vleg1_30)+0.1*(abs(max(Vleg1_30)-min(Vleg1_30))))]);
%% Fase 60° %%

subplot(2,1,1);

%set(gca, 'FontName', 'Montserrat');
plot(t, smoothdata(Voutput_60,'gaussian',3), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Montserrat Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
axis([0 100 (min(Voutput_60)-0.1*(abs(max(Voutput_60)-min(Voutput_60)))) (max(Voutput_60)+0.1*(abs(max(Voutput_60)-min(Voutput_60))))]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_60,'gaussian',3), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_60,'gaussian',3), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Montserrat Medium';
xlabel('Tiempo [μs]', 'FontName', 'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
f = gcf;
f.Position = [100 100 428 330] 
axis([0 100 (min(Vleg1_60)-0.1*(abs(max(Vleg1_60)-min(Vleg1_60)))) (max(Vleg1_60)+0.1*(abs(max(Vleg1_60)-min(Vleg1_60))))]);

%% Fase 90° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Montserrat');
plot(t, smoothdata(Voutput_90,'gaussian',3), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Montserrat Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
axis([0 100 (min(Voutput_90)-0.1*(abs(max(Voutput_90)-min(Voutput_90)))) (max(Voutput_90)+0.1*(abs(max(Voutput_90)-min(Voutput_90))))]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_90,'gaussian',3), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_90,'gaussian',3), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Montserrat Medium';
xlabel('Tiempo [μs]', 'FontName', 'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
f = gcf;
f.Position = [100 100 428 330] 
axis([0 100 (min(Vleg1_90)-0.1*(abs(max(Vleg1_90)-min(Vleg1_90)))) (max(Vleg1_90)+0.1*(abs(max(Vleg1_90)-min(Vleg1_90))))]);

%% Fase 120° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Montserrat');
plot(t, smoothdata(Voutput_120,'gaussian',3), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Montserrat Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
axis([0 100 (min(Voutput_120)-0.1*(abs(max(Voutput_120)-min(Voutput_120)))) (max(Voutput_120)+0.1*(abs(max(Voutput_120)-min(Voutput_120))))]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_120,'gaussian',3), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_120,'gaussian',3), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Montserrat Medium';
xlabel('Tiempo [μs]', 'FontName', 'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
f = gcf;
f.Position = [100 100 428 330] 
axis([0 100 (min(Vleg1_120)-0.1*(abs(max(Vleg1_120)-min(Vleg1_120)))) (max(Vleg1_120)+0.1*(abs(max(Vleg1_120)-min(Vleg1_120))))]);

%% Fase 150° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Montserrat');
plot(t, smoothdata(Voutput_150,'gaussian',3), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Montserrat Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
axis([0 100 (min(Voutput_150)-0.1*(abs(max(Voutput_150)-min(Voutput_150)))) (max(Voutput_150)+0.1*(abs(max(Voutput_150)-min(Voutput_150))))]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_150,'gaussian',3), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_150,'gaussian',3), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Montserrat Medium';
xlabel('Tiempo [μs]', 'FontName', 'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
f = gcf;
f.Position = [100 100 428 330] 
axis([0 100 (min(Vleg1_150)-0.1*(abs(max(Vleg1_150)-min(Vleg1_150)))) (max(Vleg1_150)+0.1*(abs(max(Vleg1_150)-min(Vleg1_150))))]);

%% Fase 180° %%

subplot(2,1,1);
%set(gca, 'FontName', 'Montserrat');
plot(t, smoothdata(Voutput_180,'gaussian',3), 'LineWidth', 1, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Montserrat Medium';
%xlabel('Tiempo [μs]', 'FontName',   'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
axis([0 100 (min(Voutput_180)-0.1*(abs(max(Voutput_180)-min(Voutput_180)))) (max(Voutput_180)+0.1*(abs(max(Voutput_180)-min(Voutput_180))))]);

subplot(2,1,2);
plot(t, smoothdata(Vleg1_180,'gaussian',3), 'LineWidth', 1, 'Color', '#0064A5'); hold on; grid on;
plot(t, smoothdata(Vleg2_180,'gaussian',3), 'LineWidth', 1, 'Color', '#A54100'); hold on; grid on;
%legend('v_p^+','v_p^-','Location','south','Orientation','horizontal');
ax = gca;
ax.FontName = 'Montserrat Medium';
xlabel('Tiempo [μs]', 'FontName', 'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
f = gcf;
f.Position = [100 100 428 330] 
axis([0 100 (min(Vleg1_180)-0.1*(abs(max(Vleg1_180)-min(Vleg1_180)))) (max(Vleg1_180)+0.1*(abs(max(Vleg1_180)-min(Vleg1_180))))]);