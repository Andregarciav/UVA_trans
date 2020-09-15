prr_dist = [93.9 92.8 93 93.3 90.4
        67 67 69 68 72
        51 26 42 33 49
        0 0 0 0 0
        0 0 0 0 0];
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
    saveas(gcf,'uva_white_trans', 'svg')
    hold off


dR = [8.1 8.08 8.1 8.12 7.87
    5.82 5.83 6.05 5.96 6.28
    4.46 1.43 3.62 2.18 2.06
    0 0 0 0 0
    0 0 0 0 0];
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
    saveas(gcf,'uva_white_dataRate', 'svg')
hold off