prr_dist = [98.5 99.65 99.54 94.4 94.8
        100 99.77 99.65 99.88 100
        99.77 99.88 99.54 99.65 99.19
        95 92.6 92.9 92.2 91.1
        86 87 90 90 89];
prr  = ones (1,5);
distancia = [0.1 0.2 0.4 0.6 0.8];

for i = 1:5
    prr(i) = mean(prr_dist(i,:));
end

figure(1)
    hold on
    title('PRR UVA-BLUE LEDs', 'Fontsize', 13)
    plot(distancia,prr/100,'-s','LineWidth',3)
    ylim([0 1])
    xlim([0 1])
    xlabel('Distance (m)')%,'Fontsize', 30, 'LineWidth',5,'fontweight','bold')
    ylabel('PRR')%,'Fontsize', 30, 'LineWidth',5,'fontweight','bold')
    ax = gca;
    ax.XAxis.LineWidth = 3;
    ax.YAxis.LineWidth = 3;
    ax.XAxis.FontWeight = 'bold';
    ax.YAxis.FontWeight = 'bold';
    ax.XAxis.FontSize = 13;
    ax.YAxis.FontSize = 13;
    saveas(gcf,'uva_blue_trans', 'svg')
    hold off


dR = [8.57 8.67 8.67 8.22 8.25
    8.71 8.68 8.67 8.7 8.71
    8.68 8.67 8.66 8.67 8.63
    8.26 8.06 8.09 8.02 7.83
    7.53 7.61 7.8 7.8 7.8];
data_rate  = ones (1,5);

for i = 1:5
    data_rate(i) = mean(dR(i,:));
end

figure(2)
    hold on
    title('Data Rate', 'Fontsize', 13)
    plot(distancia,data_rate,'-s','LineWidth',3)
    ylim([0 15])
    xlim([0 1])
    xlabel('Distance (m)')%,'Fontsize', 30, 'LineWidth',5,'fontweight','bold')
    ylabel('Data Rate (Kbps)')%,'Fontsize', 30, 'LineWidth',5,'fontweight','bold')
    ax = gca;
    ax.XAxis.LineWidth = 3;
    ax.YAxis.LineWidth = 3;
    ax.XAxis.FontWeight = 'bold';
    ax.YAxis.FontWeight = 'bold';
    ax.XAxis.FontSize = 13;
    ax.YAxis.FontSize = 13;
    saveas(gcf,'uva_blue_dataRate', 'svg')
hold off