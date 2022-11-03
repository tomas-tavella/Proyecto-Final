DatosCH1 = readtable('F0015CH1.CSV');
DatosCH2 = readtable('F0015CH2.CSV');
DatosSalida = readtable('F0022CH1.CSV');
%ConRc = importdata('ConRc.txt','\t');

t_leg = (DatosCH1.Var4 - min(DatosCH1.Var4))*10^6;
t_primario = (DatosSalida.Var4 - min(DatosSalida.Var4))*10^6;
VprimarioPlus = DatosCH1.Var5;
VprimarioMinus = DatosCH2.Var5;
Vprimario = DatosSalida.Var5;

%%
set(0,'defaultTextInterpreter','none');
set(groot,'defaultAxesTickLabelInterpreter','none'); 

subplot(3,1,1);
%set(gca, 'FontName', 'Montserrat');
plot(t_primario, smoothdata(Vprimario,'gaussian',5), 'LineWidth', 1.5, 'Color','#0064A5'); hold on; grid on;
ax = gca;
ax.FontName = 'Montserrat Medium';
%xlabel('Tiempo [us]', 'FontName', 'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
axis([0 100 -40 40]);

subplot(3,1,2);
plot(t_leg, smoothdata(VprimarioPlus,'gaussian',5), 'LineWidth', 1.5, 'Color', '#0064A5'); hold on; grid on;
%plot(t_leg, smoothdata(VprimarioMinus,'gaussian',5)-30, 'LineWidth',1.5); hold on; grid on;
ax = gca;
ax.FontName = 'Montserrat Medium';
%xlabel('Tiempo [us]', 'FontName', 'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
axis([0 100 -10 40]);

subplot(3,1,3);
plot(t_leg, smoothdata(VprimarioMinus,'gaussian',5), 'LineWidth', 1.5, 'Color', '#A54100'); hold on; grid on;
%plot(t_leg, smoothdata(VprimarioMinus,'gaussian',5)-30, 'LineWidth',1.5); hold on; grid on;
ax = gca;
ax.FontName = 'Montserrat Medium';
xlabel('Tiempo [us]', 'FontName', 'Montserrat SemiBold');
ylabel('Tensión [V]', 'FontName', 'Montserrat SemiBold');
axis([0 100 -10 40]);